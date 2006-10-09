//#include <iostream>
#include "AlpsLicense.h"

#ifndef AlpsTreeNode_h_
#define AlpsTreeNode_h_

#include <utility>
#include <vector>
//#include <queue>

#include "CoinError.hpp"
#include "CoinBuffer.h"
#include "CoinUtility.h"

#include "AlpsDataPool.h"  
#include "AlpsKnowledge.h"
#include "AlpsModel.h"
#include "AlpsPriorityQueue.h"
#include "AlpsSolution.h"

//#define AlpsNodeIndex_t int
typedef int AlpsNodeIndex_t;

class AlpsKnowledgeBroker;


//#############################################################################
/** The possible stati for the search nodes. */
//#############################################################################

enum AlpsNodeStatus {
   AlpsNodeStatusCandidate,
   AlpsNodeStatusEvaluated,
   AlpsNodeStatusPregnant,
   AlpsNodeStatusBranched,
   AlpsNodeStatusFathomed
};

//#############################################################################
/** A class to refer to the description of a search tree node.
 *FIXME* : write a better doc...
 */
//#############################################################################

class AlpsNodeDesc {
 protected:

  /** A pointer to model. */
  const AlpsModel* model_;

 public:
  AlpsNodeDesc() 
    : 
    model_(AlpsDataPool::getModel()) 
    {}

  AlpsNodeDesc(const AlpsModel* m) 
    : 
    model_(m) 
    {}

  virtual ~AlpsNodeDesc() {}

  inline const AlpsModel* getModel() const { return model_; }

  inline void setModel(AlpsModel* m) { model_ = m; m = NULL; }
};


//#############################################################################
/** This class holds one node of the search tree. Note that the generic search
    procedure doesn't know anything about the nodes in the
    tree other than their index, lower bound, etc. Other application-specific
    data is contained in derived classes, but is not needed for the basic
    operation of the search tree.*/
//#############################################################################

class AlpsTreeNode : public AlpsKnowledge { 
 private:
   AlpsTreeNode(const AlpsTreeNode&);
   AlpsTreeNode& operator=(const AlpsTreeNode&);

 protected:
   /** Whether the node is being worked on at the moment */
   bool               active_;

   /** The unique index of the tree node (across the whole search tree).*/
   AlpsNodeIndex_t    index_;

   /** The depth of the node (in the whole tree -- the root is at level 0). */
   int                level_;

   /** The priority of this node in the queue */
   double             priority_;
   
   /** The parent of the tree node. */
   AlpsTreeNode*      parent_;

   /** The number of children. */
   int                numChildren_;
   
   /** The array of pointers to the children. */
#if defined(ALPS_MAX_CHILD_NUM) // *FIXME* : Do we want ifdefs?
   AlpsTreeNode*      children_[ALPS_MAX_CHILD_NUM];
#else
   AlpsTreeNode**     children_;
#endif

   /** The actual description of the tree node. */
   AlpsNodeDesc*      desc_;

   /** The current status of the node. */
   AlpsNodeStatus     status_;

   /** A pointer to the knowledge broker of the process where this node is
       processed. */
   AlpsKnowledgeBroker*  knowledgeBroker_;

 public:
   AlpsTreeNode() :
      active_(false),
      index_(-1),
      level_(-1),
      priority_(-1),
      parent_(0),
      numChildren_(0),
#if defined(ALPS_MAX_CHILD_NUM) // *FIXME* : Do we want ifdefs?
      // AlpsTreeNode*     children_[ALPS_MAX_CHILD_NUM];
#else
      children_(0),
#endif
      desc_(0),
      status_(AlpsNodeStatusCandidate),
      knowledgeBroker_(0) { }

   virtual ~AlpsTreeNode() {
#if ! defined(ALPS_MAX_CHILD_NUM)
      delete[] children_;
#endif

      if (desc_ != 0) {
	delete desc_;  desc_ = 0;
      }
   }
      
   //--------------------------------------------------------------------------
   bool operator<(const AlpsTreeNode& compNode)
      { return priority_ < compNode.getPriority(); }

   //--------------------------------------------------------------------------
   /** methods to access/set the knwoledge broker */
   inline AlpsKnowledgeBroker*  getKnowledgeBroker() 
     { return knowledgeBroker_; }
   inline void setKnowledgeBroker(AlpsKnowledgeBroker* kb) 
     { knowledgeBroker_ = kb; }

   //--------------------------------------------------------------------------
   /** The purpose of this function is be able to create the children of a node
       after branching. */
   /* FIXME: I think that we probably want the argument to be a diff'd
      description, but this is open to debate. Maybe we should
      overload this method and have a version that creates a diff'd
      description, as well as one that creates an explicit
      description. */
   virtual AlpsTreeNode* createNewTreeNode(AlpsNodeDesc*& desc) const = 0;

   //--------------------------------------------------------------------------
   /** Query/set the current status. */
   ///@{
   inline AlpsNodeStatus getStatus() const { return status_; }
   inline void setStatus(const AlpsNodeStatus stat) { status_ = stat; }
   ///@}

   /** Query functions about specific stati. */
   ///@{
   inline bool isCandidate() const {
      return status_ == AlpsNodeStatusCandidate; }
   inline bool isEvaluated() const {
      return status_ == AlpsNodeStatusEvaluated; }
   inline bool isPregnant() const  {
      return status_ == AlpsNodeStatusPregnant; }
   inline bool isBranched() const  {
      return status_ == AlpsNodeStatusBranched; }
   inline bool isFathomed() const  {
      return status_ == AlpsNodeStatusFathomed; }
   ///@}

   /** Query/set node in-process indicator. */
   ///@{
   inline bool isActive() const { return active_; }
   inline void setActive(const bool yesno) { active_ = yesno; }
   ///@}

   /** Query/set node identifier (unique within subtree). */
   ///@{
   inline AlpsNodeIndex_t getIndex() const { return index_; }
   inline void setIndex(const AlpsNodeIndex_t index) { index_ = index; }
   ///@}
   
   /** Query/set what level the search tree node is at. */
   ///@{
   inline int getLevel() const { return level_; }
   inline void setLevel(const int level) { level_ = level; }
   ///@}

   /** Query/set the priority of the node. */
   ///@{
   inline double getPriority() const { return priority_; }
   inline void setPriority(const double priority) { priority_ = priority; }
   ///@}

   /** Query/set what the number of children. */
   ///@{
   inline int getNumChildren() const { return numChildren_; }
   inline void setNumChildren(const int numChildren) {
      numChildren_ = numChildren;
#if ! defined(ALPS_MAX_CHILD_NUM)
      children_ = new AlpsTreeNode*[numChildren_];
#endif
   }
   ///@}

   // *FIXME* : Sanity check. Maybe we should check that the argument is in
   // the correct range, but how do we do that? This makes the code
   // inefficient so it should be done with #ifdefs so it can be compiled
   // out. But in that case, we should move this code to the implementation
   // file and it won't get inlined anymore.

   /** Query/set pointer to the ith child. */
   ///@{
   inline AlpsTreeNode* getChild(const int i) const { return children_[i]; }
   //FIXME: Compiler complains about this second declaration. Not sure how to
   //declare a const and a non-const version of a function with the same
   //arguments...
   // /** Returns a const pointer to the ith child. */
   // const AlpsTreeNode* getChild(const int i) const { return children_[i]; }
   inline void setChild(const int i, AlpsTreeNode* node)
      { children_[i] = node; }
   ///@}

   /** Remove the pointer to given child from the list of children. This
       method deletes the child as well. An error is thrown if the argument is
       not a pointer to a child. */
   void removeChild(AlpsTreeNode*& child) throw(CoinError);

   /** Add a child to the list of children for this node. */
   void addChild(AlpsTreeNode*& child);

   /** Removes all the descendants of the node. We might want to do this in
       some cases where we are cutting out a subtree and replacing it with
       another one. */
   void removeDescendants();

   /** Set the parent of the node */
   inline AlpsTreeNode* getParent() { return parent_; }
   inline void setParent(AlpsTreeNode* parent) { parent_ = parent; }

   /** 
    *  Perform the processing of the node. For branch and bound, this would
    *  mean performing the bounding operation. The minimum requirement for
    *  this method is that it set the status of the node.
    *  <ul>
    *  <li> active_ flag is set
    *  <li> the description is explicit
    *  <li> status_ is not pregnant nor fathomed
    *  </ul>
    *  
    *  The status of the node is set to one of the following (and children may
    *  be internally stored, etc.):
    *  <ul>
    *  <li> [candidate:] the node is put back into the priority queue for
    *  later processing
    *  <li> [evaluated:] the node is put back into the priority queue for
    *  later branching
    *  <li> [pregnant:] the node has already decided how to branch and will
    *  give birth to the children when instructed with the \c branch()
    *  function which will be the next method invoked for the node.
    *  <li> [fathomed:] the node will not be further considered in this phase.
    *  </ul>
    */
   virtual void process() = 0;

   /** This method must be invoked on a \c pregnant node (which has all the
       information needed to create the children) and should create the
       children in the data structure of the node. The stati of the children
       can be any of the ones \c process() can return.  The third component 
       is the \c priority.

       NOTE: This method may be almost empty if the descriptions of the
       children were created when the node became pregnant. In that case this
       routine is pretty much just copying data. */
   virtual std::vector< CoinTriple<AlpsNodeDesc*, AlpsNodeStatus, double> > 
      branch() = 0;

};


//#############################################################################
/** This class is used to implement the comparison for the priority queue.   */
//#############################################################################

class nodeCompare {

 public:

   inline bool operator()(const AlpsTreeNode* node1,
			  const AlpsTreeNode* node2) const {
      return(node1->getPriority() > node2->getPriority());
   }
};

//#############################################################################
/** The node pool which stores candidate nodes */
//#############################################################################
class AlpsNodePool : public AlpsKnowledgePool {

 private:
  AlpsNodePool(const AlpsNodePool&);
  AlpsNodePool& operator=(const AlpsNodePool&);
  //  std::priority_queue < AlpsTreeNode*, std::vector<AlpsTreeNode*>,
  //                      nodeCompare > candidateList_;
  AlpsPriorityQueue< AlpsTreeNode*, std::vector<AlpsTreeNode*>,
                     nodeCompare > candidateList_;

 public:
   AlpsNodePool() {}
   virtual ~AlpsNodePool() {}
   
   /** Query the number of knowledges in the pool. */
   inline int getNumKnowledges() const { return candidateList_.size(); }
  
   /** Check whether there are still node in the node pool. */
   inline bool hasKnowledge() const{ return ! (candidateList_.empty()); }

   /** Get a node from node pool, doesn't remove it from the pool*/
   inline std::pair<const AlpsKnowledge*, double> getKnowledge() const {
     return std::make_pair( candidateList_.top(), 
			    candidateList_.top()->getPriority() );
   }

   /** Remove a node from the pool*/
   inline void popKnowledge() {
     candidateList_.pop();
   }

   /** Add a node to node pool. The node pool takes over the 
       ownership of the node */
   inline void addKnowledge(const AlpsKnowledge* node, double priority=0) {
     const AlpsTreeNode * nn = static_cast<const AlpsTreeNode*>(node);
     //     if(!nn) {
       AlpsTreeNode * nonnn = const_cast<AlpsTreeNode*>(nn);
       candidateList_.push(nonnn);
       //     }
       //    else 
       // std::cout << "Add node failed\n";
     //     else
     // throw CoinError();
   }

   inline const AlpsPriorityQueue< AlpsTreeNode*, 
     std::vector<AlpsTreeNode*>, nodeCompare >& 
     getCandidateList() const { return candidateList_; }

};

#endif

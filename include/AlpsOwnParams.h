#include "AlpsLicense.h"

#ifndef AlpsOwnParams_h
#define AlpsOwnParams_h

#include "AlpsKnowledge.h"
#include "AlpsParameter.h"

//#############################################################################

//class AlpsEncoded;

//** Parameters used in Alps. */
class AlpsOwnParams : public AlpsParameterSet {
 public:
  /** Character parameters. All of these variable are used as booleans
      (ture = 1, false = 0). */
  enum chrParams{
    // The dummy is needed so the allocation won't try for 0 entries.
    /** Input date from file or not. */
    inputFromFile,
    /** Master balances the workload of hubs: centralized. */
    interClusterBalance,
    /** Hub balances the workload of workers: receiver initialized. */
    intraClusterBalance,
    ///
    endOfChrParams
  };

  /** Integer paramters. */
  enum intParams{
    /** The total number of processes that are launched. */
    processNum,
    /** The number of hubs. */
    hubNum,
    /** The number of nodes initially generated by the master. */
    masterInitNodeNum,
    /** The number of nodes initially generated by each hub. */
    hubInitNodeNum,
    /** The size/number of nodes of a unit work. */
    unitWorkNodes,
    /** The max num of solution can be stored in a solution pool. */
    maxNumSolustion,
    /** The size of memory allocated for small size message. */
    smallSize, 
    /** The size of memory allocated for medium size message. */
    mediumSize,
    /** The size of memory allocated for large size message. */
    largeSize,
    /** The size of extra memory allocated for a buffer. */
    bufSpare,
    /** If the num of nodes in the node pool of a worker is no more than
	this threshold, this worker will not share work with others. */
    minNodeNum,
    /** Display option: 
     *   0 [No display]; 
     *   1 [Display nodes under nodeInterval]. */
    display,
    /** Node log interval. */
    nodeInterval,
    /** Number of the "key" nodes that are used in determining workload. */
    keyNodeNum,
    ///
    endOfIntParams
  };

  /** Double parameters. */
  enum dblParams{
    /** The time length of a unit work. */
    unitWorkTime, 
    /** The time period for master to do loading balance/termination check. */
    masterBalancePeriod,
    /** The time period for hubs to report its load, msg count to master. */
    hubReportPeriod,
    /** The time period for workers to ask for load if needed. */
    workerAskPeriod,
    /** The exponent of the formula to calculate workload. */
    rho,
    /** If less than this number, it is considered zero workload. */
    zeroLoad,
    /** The threshold of load below which a worker will request load. */
    needLoadThreshold,
    /** It is between 1.0 - infty. When the workload in process is more than 
	the average workload timing donorThreshold, it is a donor in load 
	balancing. */
    donorThreshold,
    /** It is between 0.0 - 1.0. When the workload in process is less than 
	the average workload timing receiverThreshold, it is a receiver. */
    receiverThreshold,
    ///
    endOfDblParams
  };

  /** String parameters. */
  enum strParams{
    dataFile,
    ///
    endOfStrParams
  };

  /** There are no string array parameters. */
  enum strArrayParams{
    strArrayDummy,
    ///
    endOfStrArrayParams
  };

 public:

  /**@name Constructors. */
  /*@{*/
  /** The default constructor creates a parameter set with from the template
      argument structure. The keyword list is created and the defaults are
      set. */
  AlpsOwnParams() :
    AlpsParameterSet(
    static_cast<int>(endOfChrParams),
    static_cast<int>(endOfIntParams),
    static_cast<int>(endOfDblParams),
    static_cast<int>(endOfStrParams),
    static_cast<int>(endOfStrArrayParams)
    )
    {
      createKeywordList();
      setDefaultEntries();
    }
  /*@}*/
  
  AlpsOwnParams& operator=(const AlpsOwnParams& x) {
    // no need to delete anything, since the size of (almost) everything is
    // the same, just copy over
    // -- The static_cast is needed to satisfy the more picky IBM Visual Age
    //    C++ compiler
    std::copy(x.cpar_, x.cpar_ + static_cast<int>(endOfChrParams),
	      cpar_);
    std::copy(x.ipar_, x.ipar_ + static_cast<int>(endOfIntParams),
	      ipar_);
    std::copy(x.dpar_, x.dpar_ + static_cast<int>(endOfDblParams),
	      dpar_);
    std::copy(x.spar_, x.spar_ + static_cast<int>(endOfStrParams),
	      spar_);
    std::copy(x.sapar_,
	      x.sapar_ + static_cast<int>(endOfStrArrayParams),
	      sapar_);
    return *this;
  }
  
  /** Method for creating the list of keyword looked for in the parameter
      file. */
  virtual void createKeywordList();
  /** Method for setting the default values for the parameters. */
  virtual void setDefaultEntries();

 public:
  //===========================================================================
  /** For user application: 
   *   Following code are do NOT need to change. 
   *   The reason can not put following functions in base class 
   *   <CODE> AlpsParameterSet </CODE> is:
   *
   *   <CODE> chrParams </CODE> and <CODE> endOfChrParams </CODE> etc. 
   *   can NOT be declared in base class.
   */
  //===========================================================================
 

  /**@name Query methods     
     The members of the parameter set can be queried for using the overloaded
     entry() method. Using the example in the class
     documentation the user can get a parameter with the
     "<code>param.entry(USER_par::parameter_name)</code>" expression.
  */
  /*@{*/
  ///
  inline char
    entry(const chrParams key) const { return cpar_[key]; }
  ///
  inline int
    entry(const intParams key) const { return ipar_[key]; }
  ///
  inline double
    entry(const dblParams key) const { return dpar_[key]; }
  ///
  inline const AlpsString&
    entry(const strParams key) const { return spar_[key]; }
  ///
  inline const AlpsVec<AlpsString>&
    entry(const strArrayParams key) const { return sapar_[key]; }
  /*@}*/

  //---------------------------------------------------------------------------
  /// char* is true(1) or false(0), not used
  void setEntry(const chrParams key, const char * val) {
    cpar_[key] = atoi(val); }
  /// char is true(1) or false(0), not used
  void setEntry(const chrParams key, const char val) {
    cpar_[key] = val; }
  /// This method is the one that ever been used.
  void setEntry(const chrParams key, const bool val) {
    cpar_[key] = val; }
  ///
  void setEntry(const intParams key, const char * val) {
    ipar_[key] = atoi(val); }
  ///
  void setEntry(const intParams key, const int val) {
    ipar_[key] = val; }
  ///
  void setEntry(const dblParams key, const char * val) {
    dpar_[key] = atof(val); }
  ///
  void setEntry(const dblParams key, const double val) {
    dpar_[key] = val; }
  ///
  void setEntry(const strParams key, const char * val) {
    spar_[key] = val; }
  ///
  void setEntry(const strArrayParams key, const char *val) {
    sapar_[key].push_back(val); }

  //---------------------------------------------------------------------------

  /**@name Packing/unpacking methods */
  /*@{*/
  /** Pack the parameter set into buf. */
  void pack(AlpsEncoded& buf) {
    buf.writeRep(cpar_, endOfChrParams)
      .writeRep(ipar_, endOfIntParams)
      .writeRep(dpar_, endOfDblParams);
    for (int i = 0; i < endOfStrParams; ++i)
      buf.writeRep(spar_[i]);
    for (int i = 0; i < endOfStrArrayParams; ++i) {
      buf.writeRep(sapar_[i].size());
      for (size_t j = 0; j < sapar_[i].size(); ++j)
	buf.writeRep(sapar_[i][j]);
    }
  }
  /** Unpack the parameter set from buf. */
  void unpack(AlpsEncoded& buf) {
    int dummy;
    // No need to allocate the arrays, they are of fixed length
    dummy = static_cast<int>(endOfChrParams);
    buf.readRep(cpar_, dummy, false);
    dummy = static_cast<int>(endOfIntParams);
    buf.readRep(ipar_, dummy, false);
    dummy = static_cast<int>(endOfDblParams);
    buf.readRep(dpar_, dummy, false);
    for (int i = 0; i < endOfStrParams; ++i)
      buf.readRep(spar_[i]);
    for (int i = 0; i < endOfStrArrayParams; ++i) {
      size_t str_size;
      buf.readRep(str_size);
      sapar_[i].reserve(str_size);
      for (size_t j = 0; j < str_size; ++j){
	sapar_[i].unchecked_push_back(AlpsString());
	buf.readRep(sapar_[i].back());
      }
    }
  }
  /*@}*/

};

#endif

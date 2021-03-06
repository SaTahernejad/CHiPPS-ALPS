ALPS Version 2.0 README
=======================

Welcome to ALPS. Alps is distributed under the Eclipse Public License and is
freely redistributable. All source code and documentation is Copyright
2001-2017 by Lehigh University, Yan Xu, Aykut Bulut, and Ted Ralphs. This
README may be distributed freely.

TESTING STATUS
==============

[![Build Status](https://travis-ci.org/coin-or/CHiPPS-ALPS.svg?branch=master)](https://travis-ci.org/coin-or/CHiPPS-ALPS)

[![Build status](https://ci.appveyor.com/api/projects/status/aj8ibib6m4sphnwh?svg=true)](https://ci.appveyor.com/project/tkralphs/chipps-alps)

DOWNLOAD
========

Binaries available as part of the [CHiPPS-BLIS](http://github.com/coin-or/CHiPPS-BLIS) binary distribution on [BinTray](http://bintray.com):

[ ![Download](https://api.bintray.com/packages/coin-or/download/CHiPPS-BLIS/images/download.svg?version=0.94) ](https://bintray.com/coin-or/download/CHiPPS-BLIS/0.94/link)

CITE
====

[![DOI](https://zenodo.org/badge/23726893.svg)](https://zenodo.org/badge/latestdoi/23726893)

WHAT IS ALPS?
=============

Alps is a framework for implementing parallel graph search algorithms. Its
methodology generalizes many of the notions of an LP-based branch-and-bound
algorithm, allowing the implementation of a wide range of algorithms with a
simplified interface. Alps implements the search handling methods required for
implementing large-scale, data-intensive parallel search algorithms, such as
those used for solving discrete optimization problems. It is the base layer of
the CHiPPS (COIN High Performance Parallel Search) library hierarchy that will
includes a library for solving mixed integer linear programs (BLIS).

PROJECT WEB PAGE
================

https://github.com/coin-or/CHiPPS-ALPS

DOCUMENTATION
=============

The html documentation of the classes in Alps (See INSTALL) can be created
readily. A user's guide that is under preparation can show users how to 
develop an application based Alps and how to use existing applications.

INSTALLATION
============

Please see the INSTALL file for a guide to install Alps.

CURRENT TESTING STATUS
======================

1. Configurations
   - Serial: Well tested.
   - LAMMPI: Well tested.
   - MPICH: Well tested.

2. Applications (See INSTALL)
   - Abc: Alps Branch and Cut (A simple generic MILP solver): Well tested.
   - Knap: Knapsack solver: Well tested.

SUPPORT
=======

1. Authors

Source Code:

Yan Xu (yax2@lehigh.edu)
Aykut Bulut (aykutblt@gmail.com) 
Ted Ralphs (ted@lehigh.edu), Project Manager

Original Conceptual Design:

Yan Xu (yax2@lehigh.edu)
Ted Ralphs (ted@lehigh.edu), Project Manager
Laci Ladanyi (ladanyi@us.ibm.com)
Matt Saltzman (mjs@clemson.edu)

2. Bug Reports and Other Issues

Bug reports should be reported on the CHiPPS GitHub web site at

https://github.com/coin-or/CHiPPS-ALPS/issues/new

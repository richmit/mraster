// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      utest_ramCanvasTpl.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-24
 @brief     unit tests for ramCanvasTpl on 64-bit little endian hardware -- like ia64/x86_64.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 2022, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software
     without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
  @endparblock
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "mjrmath.hpp"

#if 1

// |        | <typename inT, typename maxT>    inT         numberWrap                 (inT inNum, maxT maxOutValue)                           |
// |        | <typename realType>              realType    realWrap                   (realType aReal, realType maxOutValue)                  |
// |        | <typename inT, typename maxT>    inT         intClamp                   (inT inInt, maxT maxOutValue)                           |
// |        | <typename realType>              realType    unitClamp                  (realType aReal)                                        |
// |        |                                  double      interpolateLinear          (double v1, double v2, double w)                        |
// |        |                                  double      interpolateLinearAnglesDeg (double v1, double v2, double w)                        |
// |        |                                  int         intLinMap                  (int anInt, int maxOutValue, int maxInValue)            |
// |        | <typename numTx, typename numTy> numTy       genLinMap                  (numTx x, numTx x1, numTx x2, numTy y1, numTy y2)       |
// |        |                                  int         unitTooIntLinMap           (double aDouble, int maxOutValue)                       |
// |        | <typename numType>               numType     max3                       (numType x1, numType x2, numType x3)                    |
// |        | <typename numType>               numType     min4                       (numType x1, numType x2, numType x3, numType x4)        |
// |        |                                  std::string fmtInt                     (int inInt, int width, char fill)                       |
// | DIRECT |                                  double      evalBiPoly                 (std::vector<double> const& biPoly, double x, double y) |


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(maxExpBiPoly) {
  // normal cases
  for(int i=2; i<=100; i++) 
    BOOST_TEST_CHECK(mjr::maxExpBiPoly((i+1)*(i+1)) == i);
  // one too small to be a poly
  for(int i=2; i<=100; i++) 
    BOOST_TEST_CHECK(mjr::maxExpBiPoly((i+1)*(i+1)-1) == -3);
  // one too big to be a poly
  for(int i=2; i<100; i++) 
    BOOST_TEST_CHECK(mjr::maxExpBiPoly((i+1)*(i+1)+1) == -3);
  // too big to support
  BOOST_TEST_CHECK(mjr::maxExpBiPoly((100+1)*(100+1)+1) == -1);
  BOOST_TEST_CHECK(mjr::maxExpBiPoly((101+1)*(101+1))   == -1);
  // too small to support
  BOOST_TEST_CHECK(mjr::maxExpBiPoly(0) == -2);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(evalBiPoly, * boost::unit_test::tolerance(0.00001)) {

  std::vector<double> BiPoly01 {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<double> BiPoly02 {9, 8, 7, 6, 5, 4, 3, 2, 1};

  std::vector<double> BiPoly03 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  std::vector<double> BiPoly04 {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  //------------------------------------------------------------------------------------------------------------------------------------------------------------
                                                       
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly01, 0, 0) ==    9);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly01, 0, 1) ==   24);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly01, 1, 0) ==   18);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly01, 1, 1) ==   45);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly01, 2, 3) ==  282);

  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly02, 0, 0) ==    1);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly02, 0, 1) ==    6);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly02, 1, 0) ==   12);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly02, 1, 1) ==   45);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly02, 2, 3) ==  628);
                                                          
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly03, 0, 0) ==   16);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly03, 0, 1) ==   58);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly03, 1, 0) ==   40);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly03, 1, 1) ==  136);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly03, 2, 3) == 2630);

  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly04, 0, 0) ==    1);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly04, 0, 1) ==   10);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly04, 1, 0) ==   28);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly04, 1, 1) ==  136);
  BOOST_TEST_CHECK(mjr::evalBiPoly(BiPoly04, 2, 3) == 7570);
}

#endif


/** @endcond */



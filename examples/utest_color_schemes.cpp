// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      utest_color_schemes.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-11
 @brief     Unit tests for basic color schemes.@EOL
 @keywords  boost
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

#include "ramCanvas.hpp"

BOOST_AUTO_TEST_CASE(csCubeHelix_tpl, * boost::unit_test::tolerance(0.01)) {

  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.25).getC0() == 0.085);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.25).getC1() == 0.325);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.25).getC2() == 0.298);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.50).getC0() == 0.628);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.50).getC1() == 0.475);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.50).getC2() == 0.286);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.75).getC0() == 0.780);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.75).getC1() == 0.702);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHstd::c(0.75).getC2() == 0.929);


  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.25).getC0() == 0.280);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.25).getC1() == 0.202);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.25).getC2() == 0.429);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.50).getC0() == 0.372);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.50).getC1() == 0.525);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.50).getC2() == 0.714);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.75).getC0() == 0.585);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.75).getC1() == 0.825);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHblu::c(0.75).getC2() == 0.798);


  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.25).getC0() == 0.388);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.25).getC1() == 0.163);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.25).getC2() == 0.342);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.50).getC0() == 0.684);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.50).getC1() == 0.384);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.50).getC2() == 0.623);

  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.75).getC0() == 0.888);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.75).getC1() == 0.663);
  BOOST_TEST_CHECK(mjr::color3c64F::csCHvio::c(0.75).getC2() == 0.842);

  typedef mjr::colorTpl<double, 3, 2, 1, 0> permcolor3c64F;

  BOOST_TEST_CHECK(permcolor3c64F::csCHstd::c(0.25).getC2() == 0.085);
  BOOST_TEST_CHECK(permcolor3c64F::csCHstd::c(0.25).getC1() == 0.325);
  BOOST_TEST_CHECK(permcolor3c64F::csCHstd::c(0.25).getC0() == 0.298);

}

BOOST_AUTO_TEST_CASE(cmpRGBcornerDGradiant_csCColdeRainbow, * boost::unit_test::tolerance(0.01)) {
  // for(csIt x=0;x<ct::csCColdeRainbow::numC;x++) 
  //   ct::csCColdeRainbow::c(x) === ct().cmpRGBcornerDGradiant(x, "RYGCBMR");    
}
/** @endcond */

// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      set_cs_csCubeHelix.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-25
 @brief     Unit tests for basic color methods.@EOL
 @keywords  boost
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 2022-2025, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

#include <gtest/gtest.h>
#include "MRcolor.hpp"

#if !(MISSING_P1907R1)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(set_cs_csCubeHelix, float64) {

  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.25).getC0(),  0.085,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.25).getC1(),  0.325,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.25).getC2(),  0.298,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.50).getC0(),  0.628,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.50).getC1(),  0.475,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.50).getC2(),  0.286,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.75).getC0(),  0.780,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.75).getC1(),  0.702,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHstd::c(0.75).getC2(),  0.929,    0.01);


  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.25).getC0(),  0.280,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.25).getC1(),  0.202,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.25).getC2(),  0.429,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.50).getC0(),  0.372,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.50).getC1(),  0.525,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.50).getC2(),  0.714,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.75).getC0(),  0.585,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.75).getC1(),  0.825,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHblu::c(0.75).getC2(),  0.798,    0.01);


  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.25).getC0(),  0.388,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.25).getC1(),  0.163,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.25).getC2(),  0.342,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.50).getC0(),  0.684,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.50).getC1(),  0.384,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.50).getC2(),  0.623,    0.01);

  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.75).getC0(),  0.888,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.75).getC1(),  0.663,    0.01);
  EXPECT_NEAR(mjr::color3c64F::csCHvio::c(0.75).getC2(),  0.842,    0.01);

  typedef mjr::colorTpl<double, 3, 2, 1, 0> permcolor3c64F;

  EXPECT_NEAR(permcolor3c64F::csCHstd::c(0.25).getC2(),  0.085,    0.01);
  EXPECT_NEAR(permcolor3c64F::csCHstd::c(0.25).getC1(),  0.325,    0.01);
  EXPECT_NEAR(permcolor3c64F::csCHstd::c(0.25).getC0(),  0.298,    0.01);
}

#endif

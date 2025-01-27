// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_comp_distX.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-25
 @brief     Unit tests for basic color methods.@EOL
 @keywords  gtest
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_distX, unsigned8) {

  mjr::colorRGBA8b   aColor;
  mjr::colorRGBA8b   bColor;

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*4), 0.00001);
  EXPECT_EQ(aColor.distSumAbs(bColor),  mjr::colorRGBA8b::maxChanVal*4);
  EXPECT_EQ(aColor.distMaxAbs(bColor),  mjr::colorRGBA8b::maxChanVal);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*4), 0.00001);
  EXPECT_EQ(bColor.distSumAbs(aColor),  mjr::colorRGBA8b::maxChanVal*4);
  EXPECT_EQ(bColor.distMaxAbs(aColor),  mjr::colorRGBA8b::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToWhite();

  EXPECT_NEAR(aColor.distHypot( bColor),  0, 0.00001);
  EXPECT_EQ(aColor.distSumAbs(bColor),  0);
  EXPECT_EQ(aColor.distMaxAbs(bColor),  0);

  EXPECT_NEAR(bColor.distHypot( aColor),  0, 0.00001);
  EXPECT_EQ(bColor.distSumAbs(aColor),  0);
  EXPECT_EQ(bColor.distMaxAbs(aColor),  0);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToCyan();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*3), 0.0001);
  EXPECT_EQ(aColor.distSumAbs(bColor),  mjr::colorRGBA8b::maxChanVal*3);
  EXPECT_EQ(aColor.distMaxAbs(bColor),  mjr::colorRGBA8b::maxChanVal);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA8b::maxChanVal*mjr::colorRGBA8b::maxChanVal*3), 0.0001);
  EXPECT_EQ(bColor.distSumAbs(aColor),  mjr::colorRGBA8b::maxChanVal*3);
  EXPECT_EQ(bColor.distMaxAbs(aColor),  mjr::colorRGBA8b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_distX, float32) {

  mjr::colorRGBA32F   aColor;
  mjr::colorRGBA32F   bColor;

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*4), 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  mjr::colorRGBA32F::maxChanVal*4, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*4), 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  mjr::colorRGBA32F::maxChanVal*4, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  bColor.setToWhite();

  EXPECT_NEAR(aColor.distHypot( bColor),  0, 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  0, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  0, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  0, 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  0, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  0, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToCyan();
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*3), 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  mjr::colorRGBA32F::maxChanVal*3, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(mjr::colorRGBA32F::maxChanVal*mjr::colorRGBA32F::maxChanVal*3), 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  mjr::colorRGBA32F::maxChanVal*3, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  mjr::colorRGBA32F::maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setChansRGBA(0.5, 0.5, 0.5, 0.5);
  bColor.setToBlack();

  EXPECT_NEAR(aColor.distHypot( bColor),  std::sqrt(0.5*0.5*4), 0.00001);
  EXPECT_NEAR(aColor.distSumAbs(bColor),  0.5*4, 0.00001);
  EXPECT_NEAR(aColor.distMaxAbs(bColor),  0.5, 0.00001);

  EXPECT_NEAR(bColor.distHypot( aColor),  std::sqrt(0.5*0.5*4), 0.00001);
  EXPECT_NEAR(bColor.distSumAbs(aColor),  0.5*4, 0.00001);
  EXPECT_NEAR(bColor.distMaxAbs(aColor),  0.5, 0.00001);
}

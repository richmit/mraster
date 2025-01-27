// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_rgb_constant.cpp
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
TEST(c_set_rgb_constant, unsigned8) {

  mjr::colorRGBA8b   aColor; // integer color with imperfect mask

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToBlack();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToWhite();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToRed();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToRed();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToGreen();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToGreen();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToBlue();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToBlue();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.minChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToCyan();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToCyan();
  EXPECT_EQ(aColor.getC0(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToMagenta();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToMagenta();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToYellow();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToYellow();
  EXPECT_EQ(aColor.getC0(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.maxChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.minChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToBlack();
  aColor.setToHalf();
  EXPECT_EQ(aColor.getC0(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.meanChanVal);

  ////////////////////////////////////////////////////////////////////////////////
  aColor.setToWhite();
  aColor.setToHalf();
  EXPECT_EQ(aColor.getC0(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC1(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC2(),  aColor.meanChanVal);
  EXPECT_EQ(aColor.getC3(),  aColor.meanChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_rgb_constant, unsigned64) {

  mjr::colorRGBA64b  bColor; // integer color without mask

  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToBlack();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToWhite();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToRed();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToRed();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToGreen();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToGreen();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToBlue();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToBlue();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.minChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToCyan();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToCyan();
  EXPECT_EQ(bColor.getC0(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToMagenta();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToMagenta();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToYellow();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToYellow();
  EXPECT_EQ(bColor.getC0(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.maxChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.minChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.maxChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  bColor.setToHalf();
  EXPECT_EQ(bColor.getC0(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.meanChanVal);
  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  bColor.setToHalf();
  EXPECT_EQ(bColor.getC0(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC1(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC2(),  bColor.meanChanVal);
  EXPECT_EQ(bColor.getC3(),  bColor.meanChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_rgb_constant, float32) {

  mjr::colorRGBA32F  cColor; // floating point color with mask

  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToBlack();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToWhite();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToRed();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToRed();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToGreen();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToGreen();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToBlue();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToBlue();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.minChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToCyan();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToCyan();
  EXPECT_NEAR(cColor.getC0(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToMagenta();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToMagenta();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToYellow();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToYellow();
  EXPECT_NEAR(cColor.getC0(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.maxChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.minChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.maxChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToBlack();
  cColor.setToHalf();
  EXPECT_NEAR(cColor.getC0(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.meanChanVal, 0.00001);  ////////////////////////////////////////////////////////////////////////////////  cColor.setToWhite();
  cColor.setToHalf();
  EXPECT_NEAR(cColor.getC0(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  cColor.meanChanVal, 0.00001);
  EXPECT_NEAR(cColor.getC3(),  cColor.meanChanVal, 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_rgb_constant, float64) {

  mjr::colorRGBA64F  dColor; // floating point color without mask

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToBlack();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToWhite();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToRed();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToRed();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToGreen();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToGreen();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToBlue();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToBlue();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.minChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToCyan();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToCyan();
  EXPECT_NEAR(dColor.getC0(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToMagenta();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToMagenta();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToYellow();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToYellow();
  EXPECT_NEAR(dColor.getC0(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.maxChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.minChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.maxChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToBlack();
  dColor.setToHalf();
  EXPECT_NEAR(dColor.getC0(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.meanChanVal, 0.00001);

  ////////////////////////////////////////////////////////////////////////////////
  dColor.setToWhite();
  dColor.setToHalf();
  EXPECT_NEAR(dColor.getC0(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC1(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC2(),  dColor.meanChanVal, 0.00001);
  EXPECT_NEAR(dColor.getC3(),  dColor.meanChanVal, 0.00001);
}

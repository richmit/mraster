// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_tfrm_arith.cpp
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
TEST(c_tfrm_arith, unsigned8) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;
  mjr::colorRGB8b dColor;
  mjr::colorRGB8b cColor;

  aColor.setRGBfromLogPackIntARGB(0xFF00FF);
  bColor.setRGBfromLogPackIntARGB(0x00FFFF);
  dColor.setRGBfromLogPackIntARGB(0x0100FF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0xFF);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0xFF);

  EXPECT_EQ(dColor.getRed(),    0x01);
  EXPECT_EQ(dColor.getGreen(),  0x00);
  EXPECT_EQ(dColor.getBlue(),   0xFF);

  cColor=aColor;
  cColor.tfrmMix(0.0, bColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMix(0.5, bColor);
  EXPECT_EQ(cColor.getC0(),  0x7F);
  EXPECT_EQ(cColor.getC1(),  0x7F);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMix(1.0, bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor = aColor;
  cColor.tfrmInvert();
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmAdd(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0xFE); // Overflow wrap

  cColor = aColor;
  cColor.tfrmAddClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0xFF); // Overflow clamp

  cColor = aColor;
  cColor.tfrmMult(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x01); // Overflow wrap

  cColor = aColor;
  cColor.tfrmMultClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0xFF); // Overflow clamp

  cColor = aColor;
  cColor.tfrmDiv(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF); // NOOP as bot=0
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x01);

  cColor = aColor;
  cColor.tfrmMod(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF); // NOOP as bot=0
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x01); // Underflow wrap
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmDiffClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x00); // Overflow clamp
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmAbsDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmSqDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0x01); // Overflow wrap
  EXPECT_EQ(cColor.getGreen(),  0x01); // Overflow wrap
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmNegDiffClamp(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00); // Overflow clamp
  EXPECT_EQ(cColor.getGreen(),  0xFF);
  EXPECT_EQ(cColor.getBlue(),   0x00);

  cColor = aColor;
  cColor.tfrmAddDivClamp(bColor, dColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x02);

  cColor = aColor;
  cColor.tfrmSignDiff(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0x00);
  EXPECT_EQ(cColor.getBlue(),   0x7F);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_tfrm_arith, float32) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;
  mjr::colorRGB32F dColor;
  mjr::colorRGB32F cColor;

  aColor.setChansRGB(2.0, 0.0, 2.0);
  bColor.setChansRGB(0.0, 2.0, 2.0);
  dColor.setChansRGB(0.0, 2.0, 2.0);

  cColor=aColor;
  cColor.tfrmMix(0.0, bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMix(0.5, bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMix(1.0, bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor = aColor;
  cColor.tfrmInvert();
  EXPECT_NEAR(cColor.getC0(),  -1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),   1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  -1.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAdd(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  4.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAddClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001); // clamped to maxChanVal
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001); // clamped to maxChanVal
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001); // clamped to maxChanVal

  cColor = aColor;
  cColor.tfrmMult(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  4.0, 0.00001);

  cColor = aColor;
  cColor.tfrmMultClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001); // clamped to maxChanVal

  cColor = aColor;
  cColor.tfrmDiv(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // NOOP as bot=0
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001);

  cColor = aColor;
  cColor.tfrmMod(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // NOOP as bot=0
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),   2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  -2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),   0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmDiffClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // Clamp on bottom only
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001); //clamped to minChanVal
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAbsDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmSqDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),  4.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  4.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmNegDiffClamp(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001); // Underflow clamp bottom
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor = aColor;
  cColor.tfrmAddDivClamp(bColor, dColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001); // NOOP bot=0
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001); // Overflow clamp at top

  cColor = aColor;
  cColor.tfrmSignDiff(bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.5, 0.00001);
}

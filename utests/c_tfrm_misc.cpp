// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_tfrm_misc.cpp
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_tfrm_misc, unsigned8) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;
  mjr::colorRGB8b dColor;
  mjr::colorRGB8b cColor;

  aColor.setRGBfromLogPackIntARGB(0xFF00FF);
  bColor.setRGBfromLogPackIntARGB(0x00FFFF);
  dColor.setRGBfromLogPackIntARGB(0x0100FF);

  cColor.setToBlack();
  cColor.tfrmCopy(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMaxI(bColor); // Intensity equal, NOOP
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMinI(bColor); // Intensity equal, NOOP
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMax(bColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmMin(bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmSaw(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00000100), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FFFFFF));
  EXPECT_EQ(cColor.getC0(),  0x01);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmStep(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00000100), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FFFFFF));
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmDirac(bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmDiracTot(bColor);
  EXPECT_EQ(cColor.getC0(),  0x00);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0x00);

  cColor=aColor;
  cColor.tfrmDiracTot(aColor);
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=aColor;
  cColor.tfrmFuzzyDirac(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00FE01F0), mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00010101));
  EXPECT_EQ(cColor.getC0(),  0xFF);
  EXPECT_EQ(cColor.getC1(),  0xFF);
  EXPECT_EQ(cColor.getC2(),  0x00);

  cColor=aColor;
  cColor.tfrmMean(bColor);
  EXPECT_EQ(cColor.getC0(),  0x7f);
  EXPECT_EQ(cColor.getC1(),  0x7f);
  EXPECT_EQ(cColor.getC2(),  0xFF);

  cColor=dColor;
  cColor.tfrmGmean(mjr::colorRGB8b().setRGBfromLogPackIntARGB(0x00030102));
  EXPECT_EQ(cColor.getC0(),  0x01);
  EXPECT_EQ(cColor.getC1(),  0x00);
  EXPECT_EQ(cColor.getC2(),  0x16);

  cColor=aColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_EQ(cColor.getC0(),  0x48);
  EXPECT_EQ(cColor.getC1(),  0x48);
  EXPECT_EQ(cColor.getC2(),  0x48);

  cColor=bColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_EQ(cColor.getC0(),  0xC8);
  EXPECT_EQ(cColor.getC1(),  0xC8);
  EXPECT_EQ(cColor.getC2(),  0xC8);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_tfrm_misc, fLoat32) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;
  mjr::colorRGB32F dColor;
  mjr::colorRGB32F cColor;

  aColor.setChansRGB(2.0, 0.0, 2.0);
  bColor.setChansRGB(0.0, 2.0, 2.0);
  dColor.setChansRGB(0.0, 1.0, 2.0);

  cColor.setToBlack();
  cColor.tfrmCopy(aColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMaxI(bColor); // Intensity equal, NOOP
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMinI(bColor); // Intensity equal, NOOP
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=dColor;
  cColor.tfrmMaxI(aColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMax(bColor);
  EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMin(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  // cColor=dColor;
  // cColor.tfrmSaw(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0000100), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FFFFFF));
  // EXPECT_NEAR(cColor.getC0(),  0x01, 0.00001);
  // EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  // EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  // cColor=dColor;
  // cColor.tfrmStep(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0000100), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FFFFFF));
  // EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  // EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  // EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmDirac(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001);

  cColor=aColor;
  cColor.tfrmDiracTot(bColor);
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor=aColor;
  cColor.tfrmDiracTot(aColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.0, 0.00001);

  // cColor=aColor;
  // cColor.tfrmFuzzyDirac(mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0FE01F0), mjr::colorRGB32F().setRGBfromLogPackIntARGB(0.0010101));
  // EXPECT_NEAR(cColor.getC0(),  2.0, 0.00001);
  // EXPECT_NEAR(cColor.getC1(),  2.0, 0.00001);
  // EXPECT_NEAR(cColor.getC2(),  0.0, 0.00001);

  cColor=aColor;
  cColor.tfrmMean(bColor);
  EXPECT_NEAR(cColor.getC0(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=dColor;
  cColor.tfrmGmean(mjr::colorRGB32F().setChansRGB(8.0, 25.0, 2.0));
  EXPECT_NEAR(cColor.getC0(),  0.0, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  5.0, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  2.0, 0.00001);

  cColor=aColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_NEAR(cColor.getC0(),  0.569599986, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  0.569599986, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  0.569599986, 0.00001);

  cColor=bColor;
  cColor.tfrmGreyScaleRGB();
  EXPECT_NEAR(cColor.getC0(),  1.57480001, 0.00001);
  EXPECT_NEAR(cColor.getC1(),  1.57480001, 0.00001);
  EXPECT_NEAR(cColor.getC2(),  1.57480001, 0.00001);
}

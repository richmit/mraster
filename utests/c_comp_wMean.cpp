// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_comp_wMean.cpp
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
TEST(c_comp_wMean, unsigned8) {

  mjr::colorRGBA8b a1Color(10, 20, 30, 40);
  mjr::colorRGBA8b a2Color(10, 30, 20, 40);
  mjr::colorRGBA8b a3Color(40, 20, 30, 10);
  mjr::colorRGBA8b a4Color(90, 70, 10, 20);

  mjr::colorRGBA8b aColor;
  mjr::colorRGBA8b cColor;

 ////////////////////////////////////////////////////////////////////////////////

 aColor.wMean(1.0F, 1.0F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  20);
 EXPECT_EQ(aColor.getC1(),  50);
 EXPECT_EQ(aColor.getC2(),  50);
 EXPECT_EQ(aColor.getC3(),  80);

 aColor.wMean(1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color);
 EXPECT_EQ(aColor.getC0(),  60);
 EXPECT_EQ(aColor.getC1(),  70);
 EXPECT_EQ(aColor.getC2(),  80);
 EXPECT_EQ(aColor.getC3(),  90);

 aColor.wMean(1.0F, 1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color, a4Color);
 EXPECT_EQ(aColor.getC0(),  150);
 EXPECT_EQ(aColor.getC1(),  140);
 EXPECT_EQ(aColor.getC2(),   90);
 EXPECT_EQ(aColor.getC3(),  110);

 aColor.wMean(0.1F, 1.0F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  11);
 EXPECT_EQ(aColor.getC1(),  32);
 EXPECT_EQ(aColor.getC2(),  23);
 EXPECT_EQ(aColor.getC3(),  44);

 aColor.wMean(0.1F, 1.0F, 1.0F, a1Color, a2Color, a3Color);
 EXPECT_EQ(aColor.getC0(),  51);
 EXPECT_EQ(aColor.getC1(),  52);
 EXPECT_EQ(aColor.getC2(),  53);
 EXPECT_EQ(aColor.getC3(),  54);

 aColor.wMean(0.1F, 1.0F, 1.0F, 1.0F, a1Color, a2Color, a3Color, a4Color);
 EXPECT_EQ(aColor.getC0(),  141);
 EXPECT_EQ(aColor.getC1(),  122);
 EXPECT_EQ(aColor.getC2(),   63);
 EXPECT_EQ(aColor.getC3(),   74);

 ////////////////////////////////////////////////////////////////////////////////
 aColor.uMean(0.25F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  static_cast<int>(.25*10+.75*10));
 EXPECT_EQ(aColor.getC1(),  static_cast<int>(.25*20+.75*30));
 EXPECT_EQ(aColor.getC2(),  static_cast<int>(.25*30+.75*20));
 EXPECT_EQ(aColor.getC3(),  static_cast<int>(.25*40+.75*40));

 aColor.uMean(0.15F, 0.25F, a1Color, a2Color, a3Color);
 EXPECT_EQ(aColor.getC0(),  static_cast<int>(.15F*10+.25F*10+0.6F*40));
 EXPECT_EQ(aColor.getC1(),  static_cast<int>(.15F*20+.25F*30+0.6F*20));
 EXPECT_EQ(aColor.getC2(),  static_cast<int>(.15F*30+.25F*20+0.6F*30));
 EXPECT_EQ(aColor.getC3(),  static_cast<int>(.15F*40+.25F*40+0.6F*10));

 aColor.uMean(0.15F, 0.25F, 0.35F, a1Color, a2Color, a3Color, a4Color);
 EXPECT_EQ(aColor.getC0(),  static_cast<int>(.15F*10+.25F*10+0.35*40+0.25F*90));
 EXPECT_EQ(aColor.getC1(),  static_cast<int>(.15F*20+.25F*30+0.35*20+0.25F*70));
 EXPECT_EQ(aColor.getC2(),  static_cast<int>(.15F*30+.25F*20+0.35*30+0.25F*10));
 EXPECT_EQ(aColor.getC3(),  static_cast<int>(.15F*40+.25F*40+0.35*10+0.25F*20));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_wMean, float32) {

  mjr::colorRGBA32F bColor;
  mjr::colorRGBA32F b1Color(10, 20, 30, 40);
  mjr::colorRGBA32F b2Color(10, 30, 20, 40);
  mjr::colorRGBA32F b3Color(40, 20, 30, 10);
  mjr::colorRGBA32F b4Color(90, 70, 10, 20);

 bColor.wMean(1.0F, 1.0F, b1Color, b2Color);
 EXPECT_NEAR(bColor.getC0(),  20, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  50, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  50, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  80, 0.00001);

 bColor.wMean(1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color);
 EXPECT_NEAR(bColor.getC0(),  60, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  70, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  80, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  90, 0.00001);

 bColor.wMean(1.0F, 1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color, b4Color);
 EXPECT_NEAR(bColor.getC0(),  150, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  140, 0.00001);
 EXPECT_NEAR(bColor.getC2(),   90, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  110, 0.00001);

 bColor.wMean(0.1F, 1.0F, b1Color, b2Color);
 EXPECT_NEAR(bColor.getC0(),  11, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  32, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  23, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  44, 0.00001);

 bColor.wMean(0.1F, 1.0F, 1.0F, b1Color, b2Color, b3Color);
 EXPECT_NEAR(bColor.getC0(),  51, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  52, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  53, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  54, 0.00001);

 bColor.wMean(0.1F, 1.0F, 1.0F, 1.0F, b1Color, b2Color, b3Color, b4Color);
 EXPECT_NEAR(bColor.getC0(),  141, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  122, 0.00001);
 EXPECT_NEAR(bColor.getC2(),   63, 0.00001);
 EXPECT_NEAR(bColor.getC3(),   74, 0.00001);

 bColor.uMean(0.2F, b1Color, b2Color);
 EXPECT_NEAR(bColor.getC0(),  .2*10+.8*10, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  .2*20+.8*30, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  .2*30+.8*20, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  .2*40+.8*40, 0.00001);

 bColor.uMean(0.1F, 0.3F, b1Color, b2Color, b3Color);
 EXPECT_NEAR(bColor.getC0(),  .1*10+.3*10+0.6*40, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  .1*20+.3*30+0.6*20, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  .1*30+.3*20+0.6*30, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  .1*40+.3*40+0.6*10, 0.00001);

 bColor.uMean(0.1F, 0.3F, 0.4F, b1Color, b2Color, b3Color, b4Color);
 EXPECT_NEAR(bColor.getC0(),  .1*10+.3*10+0.4*40+0.2*90, 0.00001);
 EXPECT_NEAR(bColor.getC1(),  .1*20+.3*30+0.4*20+0.2*70, 0.00001);
 EXPECT_NEAR(bColor.getC2(),  .1*30+.3*20+0.4*30+0.2*10, 0.00001);
 EXPECT_NEAR(bColor.getC3(),  .1*40+.3*40+0.4*10+0.2*20, 0.00001);
}

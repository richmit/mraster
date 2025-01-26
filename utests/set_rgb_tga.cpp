// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      set_rgb_tga.cpp
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
TEST(set_rgb_tga16, unsigned8) {
  mjr::colorRGBA8b aColor;
  mjr::colorRGB8b  bColor;

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0x00);

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0x0000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0xFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA16bit(0xAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(set_rgb_tga24, unsigned8) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGB8b  bColor;

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0xFF);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0xFF);

  bColor.setToBlack();
  bColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0xCC);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0xCC);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(bColor.getRed(),    0x00);
  EXPECT_EQ(bColor.getGreen(),  0x00);
  EXPECT_EQ(bColor.getBlue(),   0x00);

  EXPECT_EQ(bColor.getC0(),     0x00);
  EXPECT_EQ(bColor.getC1(),     0x00);
  EXPECT_EQ(bColor.getC2(),     0x00);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(bColor.getRed(),    0xFF);
  EXPECT_EQ(bColor.getGreen(),  0xFF);
  EXPECT_EQ(bColor.getBlue(),   0xFF);

  EXPECT_EQ(bColor.getC0(),     0xFF);
  EXPECT_EQ(bColor.getC1(),     0xFF);
  EXPECT_EQ(bColor.getC2(),     0xFF);

  bColor.setToWhite();
  bColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(bColor.getRed(),    0xAA);
  EXPECT_EQ(bColor.getGreen(),  0xBB);
  EXPECT_EQ(bColor.getBlue(),   0xCC);

  EXPECT_EQ(bColor.getC0(),     0xAA);
  EXPECT_EQ(bColor.getC1(),     0xBB);
  EXPECT_EQ(bColor.getC2(),     0xCC);

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0xFF);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0xFF);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToBlack();
  aColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0xCC);
  EXPECT_EQ(aColor.getAlpha(),  0x00);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0x00);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00000000);

  EXPECT_EQ(aColor.getRed(),    0x00);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0x00);
  EXPECT_EQ(aColor.getC1(),     0x00);
  EXPECT_EQ(aColor.getC2(),     0x00);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00FFFFFF);

  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0xFF);
  EXPECT_EQ(aColor.getBlue(),   0xFF);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xFF);
  EXPECT_EQ(aColor.getC1(),     0xFF);
  EXPECT_EQ(aColor.getC2(),     0xFF);
  EXPECT_EQ(aColor.getC3(),     0xFF);

  aColor.setToWhite();
  aColor.setRGBcmpGreyTGA24bit(0x00CCAABB);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0xCC);
  EXPECT_EQ(aColor.getAlpha(),  0xFF);

  EXPECT_EQ(aColor.getC0(),     0xAA);
  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xFF);
}

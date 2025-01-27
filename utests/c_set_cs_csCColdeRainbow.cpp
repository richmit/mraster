// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_cs_csCColdeRainbow.cpp
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
TEST(c_set_cs_csCColdeRainbow, float_in_unsigned8_out) {

  mjr::colorRGBA8b  aColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csCColdeRainbow::c(aColor, 0.0);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(   0/1530.0).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 255/1530.0).isEqualRGB(aColor.setToYellow()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 510/1530.0).isEqualRGB(aColor.setToGreen()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 765/1530.0).isEqualRGB(aColor.setToCyan()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1020/1530.0).isEqualRGB(aColor.setToBlue()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1275/1530.0).isEqualRGB(aColor.setToMagenta()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1530/1530.0).isEqualRGB(aColor.setToRed()));

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(2.0).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(3.0).isEqualRGB(aColor.setToRed()));

  for(double i=0.0; i<1.0; i=i+0.001) // EXPECT_EQ x 1000
    EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(i).isEqualRGB(aColor.cmpRGBcornerCGradiant(i, "RYGCBMR")));

  aColor.cmpRGBcornerCGradiant(10/1530.0, "RYGCBMR");
  EXPECT_EQ(aColor.getRed(),    0xff);
  EXPECT_EQ(aColor.getGreen(),  10);
  EXPECT_EQ(aColor.getBlue(),   0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_cs_csCColdeRainbow, float_in_float32_out) {

  mjr::colorRGBA32F bColor;

  ////////////////////////////////////////////////////////////////////////////////

  bColor.setToWhite();
  mjr::colorRGBA32F::csCColdeRainbow::c(bColor, 0.0F);
  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA32F::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::minChanVal); // Corner colors set ALL channels -- primary colors set them all to minChanVal

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(   0/1530.0).isCloseRGB(bColor.setToRed(),     0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c( 255/1530.0).isCloseRGB(bColor.setToYellow(),  0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c( 510/1530.0).isCloseRGB(bColor.setToGreen(),   0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c( 765/1530.0).isCloseRGB(bColor.setToCyan(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1020/1530.0).isCloseRGB(bColor.setToBlue(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1275/1530.0).isCloseRGB(bColor.setToMagenta(), 0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1530/1530.0).isCloseRGB(bColor.setToRed(),     0.000001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(2.0).isCloseRGB(bColor.setToRed(),             0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(3.0).isCloseRGB(bColor.setToRed(),             0.000001F));

  for(double i=0.0; i<1.0; i=i+0.001) // TEST x 1000
    EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(i).isCloseRGB(bColor.cmpRGBcornerCGradiant(i, "RYGCBMR"), 0.000001F));

  bColor.cmpRGBcornerCGradiant(10/1530.0, "RYGCBMR");
  EXPECT_NEAR(bColor.getRed(),    1,               0.00001);
  EXPECT_NEAR(bColor.getGreen(),  0.0392156862745, 0.00001);
  EXPECT_NEAR(bColor.getBlue(),   0,               0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_FUN_csCColdeRainbow, int_in_float32_out) {

  mjr::colorRGBA32F bColor;

  bColor.setToWhite();
  mjr::colorRGBA32F::csCColdeRainbow::c(bColor, 0u);
  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA32F::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA32F::minChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal); // unchanged

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(0*0x100000000ul).isCloseRGB(bColor.setToRed(),      0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(1*0x100000000ul).isCloseRGB(bColor.setToYellow(),   0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(2*0x100000000ul).isCloseRGB(bColor.setToGreen(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(3*0x100000000ul).isCloseRGB(bColor.setToCyan(),     0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(4*0x100000000ul).isCloseRGB(bColor.setToBlue(),     0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(5*0x100000000ul).isCloseRGB(bColor.setToMagenta(),  0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(6*0x100000000ul).isCloseRGB(bColor.setToRed(),      0.000001F));

  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(6*0x100000000ul+1).isCloseRGB(bColor.setToRed(),    0.000001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(7*0x100000000ul+1).isCloseRGB(bColor.setToYellow(), 0.000001F));

  for(uint64_t i=0; i<0x600000000; i=i+0x600000)  // TEST x 4096
    EXPECT_TRUE(mjr::colorRGBA32F::csCColdeRainbow::c(i).isCloseRGB(bColor.cmpRGBcornerDGradiant(i, "RYGCBMR"), 0.000001F));

  bColor.cmpRGBcornerDGradiant(168430090, "RYGCBMR");
  EXPECT_NEAR(bColor.getRed(),    1,               0.00001);
  EXPECT_NEAR(bColor.getGreen(),  0.0392156862745, 0.00001);
  EXPECT_NEAR(bColor.getBlue(),   0,               0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_FUN_csCColdeRainbow, int_in_unsigned8_out) {

  mjr::colorRGBA8b  aColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csCColdeRainbow::c(aColor, 0u);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // unchanged

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(   0u).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 255u).isEqualRGB(aColor.setToYellow()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 510u).isEqualRGB(aColor.setToGreen()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c( 765u).isEqualRGB(aColor.setToCyan()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1020u).isEqualRGB(aColor.setToBlue()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1275u).isEqualRGB(aColor.setToMagenta()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1530u).isEqualRGB(aColor.setToRed()));

  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1531u).isEqualRGB(aColor.setToRed()));
  EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(1786u).isEqualRGB(aColor.setToYellow()));

  for(unsigned int i=0; i<1531; i++)   // EXPECT_EQ x 1531
    EXPECT_TRUE(mjr::colorRGBA8b::csCColdeRainbow::c(i).isEqualRGB(aColor.cmpRGBcornerDGradiant(i, "RYGCBMR")));

  aColor.cmpRGBcornerDGradiant(10u, "RYGCBMR");
  EXPECT_EQ(aColor.getRed(),    0xff);
  EXPECT_EQ(aColor.getGreen(),  10);
  EXPECT_EQ(aColor.getBlue(),   0);
}

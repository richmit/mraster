// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_cs_csFPcircular12.cpp
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
TEST(c_set_cs_csFPcircular12, int_in_float32_out) {

  mjr::colorRGBA32F bColor;

  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 0).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 1).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x7D/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 2).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 3).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 4).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xCC/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 5).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xFF/255.0F, 0xB2/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 6).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0xFF/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 7).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x7D/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 8).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 9).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(10).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(11).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x7D/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0);
  EXPECT_NEAR(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal, 0.0001); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0);
  EXPECT_NEAR(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal, 0.0001); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_cs_csFPcircular12, int_in_unsigned8_out) {

  mjr::colorRGBA8b  aColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 0).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 1).isEqualRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 2).isEqualRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 3).isEqualRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 4).isEqualRGB(aColor.setChansRGB(0x66, 0xCC, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 5).isEqualRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 6).isEqualRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 7).isEqualRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 8).isEqualRGB(aColor.setChansRGB(0x00, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 9).isEqualRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(10).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(11).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D)));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(12).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x00))); // wrap
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(13).isEqualRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(14).isEqualRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(15).isEqualRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(16).isEqualRGB(aColor.setChansRGB(0x66, 0xCC, 0x00)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(17).isEqualRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(18).isEqualRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(19).isEqualRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(20).isEqualRGB(aColor.setChansRGB(0x00, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(21).isEqualRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(22).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF)));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(23).isEqualRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D)));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0);
  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0);
  EXPECT_EQ(aColor.getRed(),     0xFF);
  EXPECT_EQ(aColor.getGreen(),   0x00);
  EXPECT_EQ(aColor.getBlue(),    0x00);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_FUN_csFPcircular12, float_in_unsigned8_out) {

  mjr::colorRGBA8b  aColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 0/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 1/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 2/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 3/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 4/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xCC, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 5/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 6/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 7/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 8/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c( 9/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(10/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(11/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0x7D), 2));

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 1/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x7D, 0x00), 2)); // wrap
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 2/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 3/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0xFF, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 4/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xCC, 0x00), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 5/11.0F).isCloseRGB(aColor.setChansRGB(0x66, 0xFF, 0xB2), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 6/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0xFF, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 7/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x7D, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 8/11.0F).isCloseRGB(aColor.setChansRGB(0x00, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+ 9/11.0F).isCloseRGB(aColor.setChansRGB(0x7D, 0x00, 0xFF), 2));
  EXPECT_TRUE(mjr::colorRGBA8b::csFPcircular12::c(1+10/11.0F).isCloseRGB(aColor.setChansRGB(0xFF, 0x00, 0xFF), 2));

////////////////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0.0F);
  EXPECT_EQ(aColor.getRed(),    0xFF);
  EXPECT_EQ(aColor.getGreen(),  0x00);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),    mjr::colorRGBA8b::minChanVal); // Not set!

  aColor.setToWhite();
  mjr::colorRGBA8b::csFPcircular12::c(aColor, 0.0F);
  EXPECT_EQ(aColor.getRed(),     0xFF);
  EXPECT_EQ(aColor.getGreen(),   0x00);
  EXPECT_EQ(aColor.getBlue(),    0x00);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal); // Not set!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_FUN_csFPcircular12, float_in_float32_out) {

  mjr::colorRGBA32F bColor;

////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 0/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 1/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x7D/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 2/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 3/11.0F).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0xFF/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 4/11.0F).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xCC/255.0F, 0x00/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 5/11.0F).isCloseRGB(bColor.setChansRGB(0x66/255.0F, 0xFF/255.0F, 0xB2/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 6/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0xFF/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 7/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x7D/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 8/11.0F).isCloseRGB(bColor.setChansRGB(0x00/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c( 9/11.0F).isCloseRGB(bColor.setChansRGB(0x7D/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(10/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0xFF/255.0F), 0.00001F));
  EXPECT_TRUE(mjr::colorRGBA32F::csFPcircular12::c(11/11.0F).isCloseRGB(bColor.setChansRGB(0xFF/255.0F, 0x00/255.0F, 0x7D/255.0F), 0.00001F));

////////////////////////////////////////////////////////////////////////////////

  bColor.setToBlack();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0.0F);
  EXPECT_NEAR(bColor.getAlpha(),    mjr::colorRGBA32F::minChanVal, 0.0001); // Not set!

  bColor.setToWhite();
  mjr::colorRGBA32F::csCBSpectral::c(bColor, 0.0F);
  EXPECT_NEAR(bColor.getAlpha(),  mjr::colorRGBA32F::maxChanVal, 0.0001); // Not set!
}

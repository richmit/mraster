// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      set_chan_argb.cpp
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
TEST(set_chan_argb, unsigned8) {

  // For these tests we are mostly concerned with R, G, B, & A being
  // put in the right places.  Conversions between double/byte and
  // clrChanT are tested pretty well elsewhere.

  typedef mjr::colorTpl<mjr::colChanI8, 4, 1, 2, 3, 0> colorARGB8;
  colorARGB8 aColor;

  aColor.setToBlack();
  aColor.setRed(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha(colorARGB8::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB8::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB8::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB8::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_byte(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_byte(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_dbl(0.25, 0.50, 0.75, 1.00);

  EXPECT_EQ(aColor.getChan(0),       0xFF);
  EXPECT_EQ(aColor.getChan(1),       0x3F);
  EXPECT_EQ(aColor.getChan(2),       0x7F);
  EXPECT_EQ(aColor.getChan(3),       0xBF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_dbl(1.00, 0.25, 0.50);

  EXPECT_EQ(aColor.getChan(0),       0x00);
  EXPECT_EQ(aColor.getChan(1),       0xFF);
  EXPECT_EQ(aColor.getChan(2),       0x3F);
  EXPECT_EQ(aColor.getChan(3),       0x7F);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(colorARGB8::clrChanTup4(1, 2, 3, 4));

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(colorARGB8::clrChanTup3(1, 2, 3));

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(set_chan_argb, unsigned16) {

  typedef mjr::colorTpl<mjr::colChanI16, 4, 1, 2, 3, 0> colorARGB16;
  colorARGB16 aColor;

  aColor.setToBlack();
  aColor.setRed(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setGreen(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setBlue(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha(colorARGB16::maxChanVal);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_byte(255);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setRed_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setGreen_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

  aColor.setToBlack();
  aColor.setBlue_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::maxChanVal);

  aColor.setToBlack();
  aColor.setAlpha_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       colorARGB16::maxChanVal);
  EXPECT_EQ(aColor.getChan(1),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(2),       colorARGB16::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       colorARGB16::minChanVal);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_byte(1, 2, 3, 4);

  EXPECT_EQ(aColor.getChan(0),       1028);
  EXPECT_EQ(aColor.getChan(1),       257);
  EXPECT_EQ(aColor.getChan(2),       514);
  EXPECT_EQ(aColor.getChan(3),       771);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_byte(1, 2, 3);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       257);
  EXPECT_EQ(aColor.getChan(2),       514);
  EXPECT_EQ(aColor.getChan(3),       771);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA_dbl(0.25, 0.50, 0.75, 1.00);

  EXPECT_EQ(aColor.getChan(0),       0xFFFF);
  EXPECT_EQ(aColor.getChan(1),       0x3FFF);
  EXPECT_EQ(aColor.getChan(2),       0x7FFF);
  EXPECT_EQ(aColor.getChan(3),       0xBFFF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB_dbl(1.00, 0.25, 0.50);

  EXPECT_EQ(aColor.getChan(0),       0x0000);
  EXPECT_EQ(aColor.getChan(1),       0xFFFF);
  EXPECT_EQ(aColor.getChan(2),       0x3FFF);
  EXPECT_EQ(aColor.getChan(3),       0x7FFF);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGBA(colorARGB16::clrChanTup4(1, 2, 3, 4));

  EXPECT_EQ(aColor.getChan(0),       4);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);

//////////////////////////////////////////////////////////////////////

  aColor.setToBlack();
  aColor.setChansRGB(colorARGB16::clrChanTup3(1, 2, 3));

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(1),       1);
  EXPECT_EQ(aColor.getChan(2),       2);
  EXPECT_EQ(aColor.getChan(3),       3);
}

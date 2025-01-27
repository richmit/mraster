// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_cs_csPLY.cpp
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

#if !(MISSING_P1907R1)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_FUN_csPLY, float_in_unsigned8_out) {

  mjr::colorRGBA8b aColor;

  aColor.setToWhite();
  mjr::colorRGBA8b::csPLYgrey::c(aColor, 0.0);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::maxChanVal); // unchanged

  aColor.setToBlack();
  mjr::colorRGBA8b::csPLYgrey::c(aColor, 0.0);
  EXPECT_EQ(aColor.getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getBlue(),   mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(aColor.getAlpha(),  mjr::colorRGB8b::minChanVal); // unchanged

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.0).getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.0).getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.0).getBlue(),   mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.5).getRed(),    mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.5).getGreen(),  mjr::colorRGB8b::meanChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(0.5).getBlue(),   mjr::colorRGB8b::meanChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(1.0).getRed(),    mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(1.0).getGreen(),  mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYgrey::c(1.0).getBlue(),   mjr::colorRGB8b::maxChanVal);

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.0).getRed(),    mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.0).getGreen(),  mjr::colorRGB8b::minChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.0).getBlue(),   mjr::colorRGB8b::minChanVal);

  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.5).getRed(),    0x3F); // 255 * 0.5 * 0.5 = 63.75
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.5).getGreen(),  0x3F);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(0.5).getBlue(),   0x3F);

  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(1.0).getRed(),    mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(1.0).getGreen(),  mjr::colorRGB8b::maxChanVal);
  EXPECT_EQ(mjr::colorRGB8b::csPLYquad::c(1.0).getBlue(),   mjr::colorRGB8b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_FUN_csPLY, float_in_float32_out) {
  typedef mjr::colorRGB64F::csPLY_tpl< 10.6666666666667, -16.000000000000,  6.3333333333333, 0.00000000000000,                    // [[0.0, 0.00000], [0.25, 0.750000], [0.50, 0.500000], [1.0, 1.00000]];
                                       -9.3333333333333,  13.000000000000, -4.6666666666666, 1.00000000000000,                    // [[0.0, 1.00000], [0.25, 0.500000], [0.50, 0.750000], [1.0, 0.00000]];
                                        4.4117333333333,  -5.902400000000,  1.9936666666666, 0.28480000000000> csPLYfoo;          // [[0.0, 0.28480], [0.25, 0.483250], [0.50, 0.357500], [1.0, 0.78780]]

  EXPECT_NEAR(csPLYfoo::c(0.00).getRed(),    0.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.00).getGreen(),  1.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.00).getBlue(),   0.284800, 0.00001);

  EXPECT_NEAR(csPLYfoo::c(0.25).getRed(),    0.750000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.25).getGreen(),  0.500000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.25).getBlue(),   0.483250, 0.00001);

  EXPECT_NEAR(csPLYfoo::c(0.50).getRed(),    0.500000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.50).getGreen(),  0.750000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(0.50).getBlue(),   0.357500, 0.00001);

  EXPECT_NEAR(csPLYfoo::c(1.00).getRed(),    1.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(1.00).getGreen(),  0.000000, 0.00001);
  EXPECT_NEAR(csPLYfoo::c(1.00).getBlue(),   0.787800, 0.00001);
}

#endif

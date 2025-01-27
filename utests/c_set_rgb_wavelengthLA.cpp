// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_rgb_wavelengthLA.cpp
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
TEST(c_set_rgb_wavelengthLA, unsigned8) {

  mjr::colorRGBA8b  aColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_EQ(aColor.getRed(),    0xda);
  EXPECT_EQ(aColor.getGreen(),  0xff);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  aColor.minChanVal);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_EQ(aColor.getRed(),    0xda);
  EXPECT_EQ(aColor.getGreen(),  0xff);
  EXPECT_EQ(aColor.getBlue(),   0x00);
  EXPECT_EQ(aColor.getAlpha(),  aColor.maxChanVal);

  //  MJR TODO NOTE: Add non-int input tests
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_rgb_wavelengthLA, float32) {

  mjr::colorRGBA32F aColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_NEAR(aColor.getRed(),    0.857142866,       0.00001);
  EXPECT_NEAR(aColor.getGreen(),  1.000000000,       0.00001);
  EXPECT_NEAR(aColor.getBlue(),   0.000000000,       0.00001);
  EXPECT_NEAR(aColor.getAlpha(),  aColor.minChanVal, 0.00001);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthLA(570);
  EXPECT_NEAR(aColor.getRed(),    0.857142866,       0.00001);
  EXPECT_NEAR(aColor.getGreen(),  1.000000000,       0.00001);
  EXPECT_NEAR(aColor.getBlue(),   0.000000000,       0.00001);
  EXPECT_NEAR(aColor.getAlpha(),  aColor.maxChanVal, 0.00001);

  //  MJR TODO NOTE: Add non-int input tests
}

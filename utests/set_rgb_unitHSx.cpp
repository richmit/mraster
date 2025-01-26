// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      set_rgb_unitHSx.cpp
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
TEST(set_rgb_unitHSx, unsigned8) {

  mjr::colorRGB8b aColor;
  mjr::colorRGB8b bColor;

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0.5);
  bColor.setToRed();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL( 60/360.0, 1, 0.5);
  bColor.setToYellow();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(120/360.0, 1, 0.5);
  bColor.setToGreen();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0.5);
  bColor.setToCyan();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(240/360.0, 1, 0.5);
  bColor.setToBlue();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(300/360.0, 1, 0.5);
  bColor.setToMagenta();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 1.0);
  bColor.setToRed();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV( 60/360.0, 1, 1.0);
  bColor.setToYellow();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV( 420/360.0, 1, 1.0);
  bColor.setToYellow();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(120/360.0, 1, 1.0);
  bColor.setToGreen();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 1.0);
  bColor.setToCyan();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(240/360.0, 1, 1.0);
  bColor.setToBlue();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(300/360.0, 1, 1.0);
  bColor.setToMagenta();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSL(180/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromUnitHSV(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(set_rgb_unitHSx, float32) {

  mjr::colorRGB32F aColor;
  mjr::colorRGB32F bColor;

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0.5);
  bColor.setToRed();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL( 60/360.0, 1, 0.5);
  bColor.setToYellow();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL( 420/360.0, 1, 0.5);
  bColor.setToYellow();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(120/360.0, 1, 0.5);
  bColor.setToGreen();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0.5);
  bColor.setToCyan();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(240/360.0, 1, 0.5);
  bColor.setToBlue();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(300/360.0, 1, 0.5);
  bColor.setToMagenta();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 1.0);
  bColor.setToRed();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV( 60/360.0, 1, 1.0);
  bColor.setToYellow();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(120/360.0, 1, 1.0);
  bColor.setToGreen();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 1, 1.0);
  bColor.setToCyan();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(240/360.0, 1, 1.0);
  bColor.setToBlue();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(300/360.0, 1, 1.0);
  bColor.setToMagenta();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(  0/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSL(180/360.0, 1, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

////////////////////////////////////////////////////////////////////////////////

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 0, 1);
  bColor.setToWhite();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(  0/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 0, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(  0/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);

  aColor.setRGBfromUnitHSV(180/360.0, 1, 0);
  bColor.setToBlack();
  EXPECT_NEAR(aColor.getRed(),    bColor.getRed(),   0.0001);
  EXPECT_NEAR(aColor.getGreen(),  bColor.getGreen(), 0.0001);
  EXPECT_NEAR(aColor.getBlue(),   bColor.getBlue(),  0.0001);
}

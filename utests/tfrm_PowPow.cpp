// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      tfrm_PowPow.cpp
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
TEST(tfrm_PowPow, unsigned8) {
  mjr::colorRGB8b  aColor;
  mjr::colorRGBA8b bColor;

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn(5.0);
  EXPECT_EQ(aColor.getRed(),    0); // No op zero
  EXPECT_EQ(aColor.getGreen(),  19);
  EXPECT_EQ(aColor.getBlue(),   24);

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn(1.0);
  EXPECT_EQ(aColor.getRed(),    0); // No op zero
  EXPECT_EQ(aColor.getGreen(),  3);
  EXPECT_EQ(aColor.getBlue(),   4);

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn1();
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  3);
  EXPECT_EQ(aColor.getBlue(),   5);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqr();
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  9);
  EXPECT_EQ(aColor.getBlue(),   39);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqrt();
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  112);
  EXPECT_EQ(aColor.getBlue(),   159);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(2.0);
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  9);
  EXPECT_EQ(aColor.getBlue(),   39);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(0.5);
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  112);
  EXPECT_EQ(aColor.getBlue(),   159);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_EQ(aColor.getRed(),    0);
  EXPECT_EQ(aColor.getGreen(),  9);
  EXPECT_EQ(aColor.getBlue(),   159);

  bColor.setToWhite();
  bColor.setChansRGB(0, 50, 100);
  bColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_EQ(bColor.getRed(),    0);
  EXPECT_EQ(bColor.getGreen(),  9);
  EXPECT_EQ(bColor.getBlue(),   159);
  EXPECT_EQ(bColor.getAlpha(),  0xff);

  bColor.setToBlack();
  bColor.setChansRGB(0, 50, 100);
  bColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_EQ(bColor.getRed(),    0);
  EXPECT_EQ(bColor.getGreen(),  9);
  EXPECT_EQ(bColor.getBlue(),   159);
  EXPECT_EQ(bColor.getAlpha(),  0x00);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(tfrm_PowPow, float32) {

  mjr::colorRGB32F aColor;

  aColor.setChansRGB(0, 50, 148);
  aColor.tfrmLn(5.0);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001); // No op zero
  EXPECT_NEAR(aColor.getGreen(),  19.5601150272, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   24.9860613688, 0.00001);

  aColor.setChansRGB(0, -1, 148);
  aColor.tfrmLn(1.0);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001); // No op zero
  EXPECT_NEAR(aColor.getGreen(),  -1,            0.00001); // No op negative
  EXPECT_NEAR(aColor.getBlue(),   4.99721227376, 0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmLn1();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  3.93182563272, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   4.61512051684, 0.00001);

  aColor.setChansRGB(0, -2, 100);
  aColor.tfrmLn1();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001); // No op zero
  EXPECT_NEAR(aColor.getGreen(), -2.0,           0.00001); // No op negative
  EXPECT_NEAR(aColor.getBlue(),   4.61512051684, 0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqr();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  2500,          0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10000,         0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowSqrt();
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  7.07106781,    0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10,            0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(2.0);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  2500,          0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10000,         0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPow(0.5);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  7.07106781,    0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10,            0.00001);

  aColor.setChansRGB(0, 50, 100);
  aColor.tfrmStdPowRGB(1, 2.0, 0.5);
  EXPECT_NEAR(aColor.getRed(),    0,             0.00001);
  EXPECT_NEAR(aColor.getGreen(),  2500,          0.00001);
  EXPECT_NEAR(aColor.getBlue(),   10,            0.00001);
}

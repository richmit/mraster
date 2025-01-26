// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_tfrm_GryLevScl.cpp
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
TEST(c_tfrm_GryLevScl, unsigned8) {

  mjr::colorRGB8b  aColor;
  mjr::colorRGBA8b cColor;

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2, 4);
  EXPECT_EQ(aColor.getRed(),    24);
  EXPECT_EQ(aColor.getGreen(),  44);
  EXPECT_EQ(aColor.getBlue(),   54);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2.5, 4);
  EXPECT_EQ(aColor.getRed(),    29);
  EXPECT_EQ(aColor.getGreen(),  54);
  EXPECT_EQ(aColor.getBlue(),   66);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_EQ(aColor.getRed(),    24);
  EXPECT_EQ(aColor.getGreen(),  54);
  EXPECT_EQ(aColor.getBlue(),   77);

  cColor.setToWhite();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_EQ(cColor.getRed(),    24);
  EXPECT_EQ(cColor.getGreen(),  54);
  EXPECT_EQ(cColor.getBlue(),   77);
  EXPECT_EQ(cColor.getAlpha(),  0xff);

  cColor.setToBlack();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_EQ(cColor.getRed(),    24);
  EXPECT_EQ(cColor.getGreen(),  54);
  EXPECT_EQ(cColor.getBlue(),   77);
  EXPECT_EQ(cColor.getAlpha(),  0x00);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_tfrm_GryLevScl, float32) {

  mjr::colorRGB32F  aColor;
  mjr::colorRGBA32F cColor;

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2, 4);
  EXPECT_NEAR(aColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(aColor.getGreen(),  44.0, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   54.0, 0.00001);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScale(2.5, 4);
  EXPECT_NEAR(aColor.getRed(),    29.0, 0.00001);
  EXPECT_NEAR(aColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   66.5, 0.00001);

  aColor.setChansRGB(10, 20, 25);
  aColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_NEAR(aColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(aColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(aColor.getBlue(),   77.0, 0.00001);

  cColor.setToWhite();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_NEAR(cColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(cColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   77.0, 0.00001);
  EXPECT_NEAR(cColor.getAlpha(),   1.0, 0.00001);

  cColor.setToBlack();
  cColor.setChansRGB(10, 20, 25);
  cColor.tfrmLinearGreyLevelScaleRGB(2, 4, 2.5, 4, 3, 2);
  EXPECT_NEAR(cColor.getRed(),    24.0, 0.00001);
  EXPECT_NEAR(cColor.getGreen(),  54.0, 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   77.0, 0.00001);
  EXPECT_NEAR(cColor.getAlpha(),   0.0, 0.00001);
}

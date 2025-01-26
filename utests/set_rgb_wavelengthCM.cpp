// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      set_rgb_wavelengthCM.cpp
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
TEST(set_rgb_wavelengthCM, unsigned8) {

  mjr::colorRGBA8b  aColor;
  mjr::colorRGBA8b  bColor;

  aColor.setToBlack();
  aColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    173);
  EXPECT_EQ(aColor.getGreen(),  189);
  EXPECT_EQ(aColor.getBlue(),   2);
  EXPECT_EQ(aColor.getAlpha(),  aColor.minChanVal);

  aColor.setToWhite();
  aColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    173);
  EXPECT_EQ(aColor.getGreen(),  189);
  EXPECT_EQ(aColor.getBlue(),   2);
  EXPECT_EQ(aColor.getAlpha(),  aColor.maxChanVal);

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::FLOOR);
  bColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::CEILING);
  bColor.setRGBfromWavelengthCM(575);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(571, mjr::colorRGBA8b::cmfInterpolationEnum::NEAREST);
  bColor.setRGBfromWavelengthCM(570);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(574, mjr::colorRGBA8b::cmfInterpolationEnum::NEAREST);
  bColor.setRGBfromWavelengthCM(575);
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setRGBfromWavelengthCM(572, mjr::colorRGBA8b::cmfInterpolationEnum::LINEAR);
  EXPECT_EQ(aColor.getRed(),    182);
  EXPECT_EQ(aColor.getGreen(),  181);
  EXPECT_EQ(aColor.getBlue(),   0);

  aColor.setRGBfromWavelengthCM(572, mjr::colorRGBA8b::cmfInterpolationEnum::BUMP);
  EXPECT_EQ(aColor.getRed(),    167);
  EXPECT_EQ(aColor.getGreen(),  169);
  EXPECT_EQ(aColor.getBlue(),   0);

  //  MJR TODO NOTE TEST: Add non-int input cases
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(set_rgb_wavelengthCM, float32) {

  mjr::colorRGBA32F cColor;
  mjr::colorRGBA32F dColor;

  cColor.setToBlack();
  cColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    0.679159,          0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.743843,          0.00001);
  EXPECT_NEAR(cColor.getBlue(),   0.00798483,        0.00001);
  EXPECT_NEAR(cColor.getAlpha(),  cColor.minChanVal, 0.00001);

  cColor.setToWhite();
  cColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    0.679159,          0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.743843,          0.00001);
  EXPECT_NEAR(cColor.getBlue(),   0.00798483,        0.00001);
  EXPECT_NEAR(cColor.getAlpha(),  cColor.maxChanVal, 0.00001);

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::FLOOR);
  dColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::CEILING);
  dColor.setRGBfromWavelengthCM(575);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(571, mjr::colorRGBA32F::cmfInterpolationEnum::NEAREST);
  dColor.setRGBfromWavelengthCM(570);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(574, mjr::colorRGBA32F::cmfInterpolationEnum::NEAREST);
  dColor.setRGBfromWavelengthCM(575);
  EXPECT_NEAR(cColor.getRed(),    dColor.getRed(),   0.00001);
  EXPECT_NEAR(cColor.getGreen(),  dColor.getGreen(), 0.00001);
  EXPECT_NEAR(cColor.getBlue(),   dColor.getBlue(),  0.00001);

  cColor.setRGBfromWavelengthCM(572, mjr::colorRGBA32F::cmfInterpolationEnum::LINEAR);
  EXPECT_NEAR(cColor.getRed(),    0.713749886,       0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.710754037,       0.00001);
  EXPECT_NEAR(cColor.getBlue(),   0.00187643478,     0.00001);

  cColor.setRGBfromWavelengthCM(572, mjr::colorRGBA32F::cmfInterpolationEnum::BUMP);
  EXPECT_NEAR(cColor.getRed(),    0.654946387,       0.00001);
  EXPECT_NEAR(cColor.getGreen(),  0.662842572,       0.00001);
  EXPECT_NEAR(cColor.getBlue(),   3.4287558e-07,     0.00001);

  //  MJR TODO NOTE TEST: Add non-int input cases
}

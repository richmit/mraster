// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_comp_distDeltaE1976.cpp
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
TEST(c_comp_distDeltaE1976, unsigned8) {

  mjr::colorRGBA8b   aColor;
  mjr::colorRGBA8b   bColor;

  aColor.setToWhite();
  bColor.setToBlack();
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  100.0, 0.0001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  100.0, 0.0001);
  aColor.setToWhite();
  bColor.setToWhite();
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  0.0, 0.0001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  0.0, 0.0001);
  aColor.setToBlack();
  bColor.setChansRGB(128, 64, 192);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  87.0379, 0.001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  87.0382, 0.0001);
  aColor.setToBlack();
  bColor.setChansRGB(128, 128, 128);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  53.585, 0.0001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  53.585, 0.0001);
  aColor.setToBlack();
  bColor.setChansRGB(32, 64, 128);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  50.1239, 0.01);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  50.1239, 0.01);
  aColor.setToWhite();
  bColor.setChansRGB(32, 64, 128);
  EXPECT_NEAR(aColor.distDeltaE1976(bColor),  82.8934, 0.001);
  EXPECT_NEAR(aColor.distDeltaE1994(bColor),  82.8807, 0.01);
}

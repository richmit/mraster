// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_bool_isBlack.cpp
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
TEST(c_bool_isBlack, unsigned8) {
  mjr::colorRGB8b   aColor; // integer color with imperfect mask
  mjr::colorRGBA8b  bColor; // integer color with perfect mask
  aColor.setToBlack();
  bColor.setToBlack();
  EXPECT_TRUE(aColor.isBlackRGB());
  EXPECT_TRUE(bColor.isBlackRGB());
  EXPECT_TRUE(aColor.isBlack());
  EXPECT_TRUE(bColor.isBlack());
  aColor.setChanToMax(0);
  bColor.setChanToMax(0);
  EXPECT_FALSE(aColor.isBlackRGB());
  EXPECT_FALSE(bColor.isBlackRGB());
  EXPECT_FALSE(aColor.isBlack());
  EXPECT_FALSE(bColor.isBlack());
  aColor.setToWhite();
  bColor.setToWhite();
  EXPECT_FALSE(aColor.isBlackRGB());
  EXPECT_FALSE(bColor.isBlackRGB());
  EXPECT_FALSE(aColor.isBlack());
  EXPECT_FALSE(bColor.isBlack());
  bColor.setChansRGBA(0, 0, 0, 1);
  EXPECT_TRUE(bColor.isBlackRGB());
  EXPECT_FALSE(bColor.isBlack());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_bool_isBlack, unsigned64) {
  mjr::colorRGB64b  cColor; // integer color without mask
  cColor.setToBlack();
  EXPECT_TRUE(cColor.isBlackRGB());
  EXPECT_TRUE(cColor.isBlack());
  cColor.setChanToMax(0);
  EXPECT_FALSE(cColor.isBlackRGB());
  EXPECT_FALSE(cColor.isBlack());
  cColor.setToWhite();
  EXPECT_FALSE(cColor.isBlackRGB());
  EXPECT_FALSE(cColor.isBlack());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_bool_isBlack, float32) {
  mjr::colorRGB32F  dColor; // floating point color with mask
  mjr::colorRGBA32F fColor; // floating point color with perfect mask
  dColor.setToBlack();
  fColor.setToBlack();
  EXPECT_TRUE(dColor.isBlackRGB());
  EXPECT_TRUE(fColor.isBlackRGB());
  EXPECT_TRUE(dColor.isBlack());
  EXPECT_TRUE(fColor.isBlack());
  dColor.setChanToMax(0);
  fColor.setChanToMax(0);
  EXPECT_FALSE(dColor.isBlackRGB());
  EXPECT_FALSE(fColor.isBlackRGB());
  EXPECT_FALSE(dColor.isBlack());
  EXPECT_FALSE(fColor.isBlack());
  dColor.setToWhite();
  fColor.setToWhite();
  EXPECT_FALSE(dColor.isBlackRGB());
  EXPECT_FALSE(fColor.isBlackRGB());
  EXPECT_FALSE(dColor.isBlack());
  EXPECT_FALSE(fColor.isBlack());
  fColor.setChansRGBA(0, 0, 0, 1);
  EXPECT_TRUE(fColor.isBlackRGB());
  EXPECT_FALSE(fColor.isBlack());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_bool_isBlack, float64) {
  mjr::colorRGB64F  gColor; // floating point color without mask
  gColor.setToBlack();
  EXPECT_TRUE(gColor.isBlackRGB());
  EXPECT_TRUE(gColor.isBlack());
  gColor.setChanToMax(0);
  EXPECT_FALSE(gColor.isBlackRGB());
  EXPECT_FALSE(gColor.isBlack());
  gColor.setToWhite();
  EXPECT_FALSE(gColor.isBlackRGB());
  EXPECT_FALSE(gColor.isBlack());
}

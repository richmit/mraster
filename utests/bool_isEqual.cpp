// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      bool_isEqual.cpp
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
TEST(bool_isEqual, unsigned8) {

  mjr::colorRGB8b   aLcolor; // integer color with imperfect mask
  mjr::colorRGBA8b  bLcolor; // integer color with perfect mask

  mjr::colorRGB8b   aRcolor; // integer color with imperfect mask
  mjr::colorRGBA8b  bRcolor; // integer color with perfect mask

  aLcolor.setToBlack();
  bLcolor.setToBlack();
  aRcolor.setToBlack();
  bRcolor.setToBlack();
  EXPECT_TRUE(aLcolor.isEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isEqual(bRcolor));
  EXPECT_FALSE(aLcolor.isNotEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isNotEqual(bRcolor));
  EXPECT_TRUE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_TRUE(bLcolor.isEqualRGB(bRcolor));
  aLcolor.setChanToMax(0);
  bLcolor.setChanToMax(0);
  EXPECT_FALSE(aLcolor.isEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isEqual(bRcolor));
  EXPECT_TRUE(aLcolor.isNotEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isNotEqual(bRcolor));
  EXPECT_FALSE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_FALSE(bLcolor.isEqualRGB(bRcolor));
  aRcolor.setChanToMax(0);
  bRcolor.setChanToMax(0);
  EXPECT_TRUE(aLcolor.isEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isEqual(bRcolor));
  EXPECT_FALSE(aLcolor.isNotEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isNotEqual(bRcolor));
  EXPECT_TRUE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_TRUE(bLcolor.isEqualRGB(bRcolor));
  aLcolor.setToWhite();
  bLcolor.setToWhite();
  EXPECT_FALSE(aLcolor.isEqual(aRcolor));
  EXPECT_FALSE(bLcolor.isEqual(bRcolor));
  EXPECT_TRUE(aLcolor.isNotEqual(aRcolor));
  EXPECT_TRUE(bLcolor.isNotEqual(bRcolor));
  EXPECT_FALSE(aLcolor.isEqualRGB(aRcolor));
  EXPECT_FALSE(bLcolor.isEqualRGB(bRcolor));
  bLcolor.setChansRGBA(1, 2, 3, 4);
  bRcolor.setChansRGBA(1, 2, 3, 5);
  EXPECT_FALSE(bLcolor.isEqual(bRcolor));
  EXPECT_TRUE(bLcolor.isEqualRGB(bRcolor));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(bool_isEqual, unsigned64) {
  mjr::colorRGB64b  cLcolor; // integer color without mask
  mjr::colorRGB64b  cRcolor; // integer color without mask

  cLcolor.setToBlack();
  cRcolor.setToBlack();
  EXPECT_TRUE(cLcolor.isEqual(cRcolor));
  EXPECT_FALSE(cLcolor.isNotEqual(cRcolor));
  EXPECT_TRUE(cLcolor.isEqualRGB(cRcolor));
  cLcolor.setChanToMax(0);
  EXPECT_FALSE(cLcolor.isEqual(cRcolor));
  EXPECT_TRUE(cLcolor.isNotEqual(cRcolor));
  EXPECT_FALSE(cLcolor.isEqualRGB(cRcolor));
  cRcolor.setChanToMax(0);
  EXPECT_TRUE(cLcolor.isEqual(cRcolor));
  EXPECT_FALSE(cLcolor.isNotEqual(cRcolor));
  EXPECT_TRUE(cLcolor.isEqualRGB(cRcolor));
  cLcolor.setToWhite();
  EXPECT_FALSE(cLcolor.isEqual(cRcolor));
  EXPECT_TRUE(cLcolor.isNotEqual(cRcolor));
  EXPECT_FALSE(cLcolor.isEqualRGB(cRcolor));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(bool_isEqual, float32) {
  mjr::colorRGB32F  dLcolor; // floating point color with mask
  mjr::colorRGBA32F fLcolor; // floating point color with perfect mask

  mjr::colorRGB32F  dRcolor; // floating point color with mask
  mjr::colorRGBA32F fRcolor; // floating point color with perfect mask

  dLcolor.setToBlack();
  fLcolor.setToBlack();
  dRcolor.setToBlack();
  fRcolor.setToBlack();
  EXPECT_TRUE(dLcolor.isEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isEqual(fRcolor));
  EXPECT_FALSE(dLcolor.isNotEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isNotEqual(fRcolor));
  EXPECT_TRUE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_TRUE(fLcolor.isEqualRGB(fRcolor));
  dLcolor.setChanToMax(0);
  fLcolor.setChanToMax(0);
  EXPECT_FALSE(dLcolor.isEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isEqual(fRcolor));
  EXPECT_TRUE(dLcolor.isNotEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isNotEqual(fRcolor));
  EXPECT_FALSE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_FALSE(fLcolor.isEqualRGB(fRcolor));
  dRcolor.setChanToMax(0);
  fRcolor.setChanToMax(0);
  EXPECT_TRUE(dLcolor.isEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isEqual(fRcolor));
  EXPECT_FALSE(dLcolor.isNotEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isNotEqual(fRcolor));
  EXPECT_TRUE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_TRUE(fLcolor.isEqualRGB(fRcolor));
  dLcolor.setToWhite();
  fLcolor.setToWhite();
  EXPECT_FALSE(dLcolor.isEqual(dRcolor));
  EXPECT_FALSE(fLcolor.isEqual(fRcolor));
  EXPECT_TRUE(dLcolor.isNotEqual(dRcolor));
  EXPECT_TRUE(fLcolor.isNotEqual(fRcolor));
  EXPECT_FALSE(dLcolor.isEqualRGB(dRcolor));
  EXPECT_FALSE(fLcolor.isEqualRGB(fRcolor));
  fLcolor.setChansRGBA(1, 2, 3, 4);
  fRcolor.setChansRGBA(1, 2, 3, 5);
  EXPECT_FALSE(fLcolor.isEqual(fRcolor));
  EXPECT_TRUE(fLcolor.isEqualRGB(fRcolor));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(bool_isEqual, float64) {
  mjr::colorRGB64F  gLcolor; // floating point color without mask
  mjr::colorRGB64F  gRcolor; // floating point color without mask

  gLcolor.setToBlack();
  gRcolor.setToBlack();
  EXPECT_TRUE(gLcolor.isEqual(gRcolor));
  EXPECT_FALSE(gLcolor.isNotEqual(gRcolor));
  EXPECT_TRUE(gLcolor.isEqualRGB(gRcolor));
  gLcolor.setChanToMax(0);
  EXPECT_FALSE(gLcolor.isEqual(gRcolor));
  EXPECT_TRUE(gLcolor.isNotEqual(gRcolor));
  EXPECT_FALSE(gLcolor.isEqualRGB(gRcolor));
  gRcolor.setChanToMax(0);
  EXPECT_TRUE(gLcolor.isEqual(gRcolor));
  EXPECT_FALSE(gLcolor.isNotEqual(gRcolor));
  EXPECT_TRUE(gLcolor.isEqualRGB(gRcolor));
  gLcolor.setToWhite();
  EXPECT_FALSE(gLcolor.isEqual(gRcolor));
  EXPECT_TRUE(gLcolor.isNotEqual(gRcolor));
  EXPECT_FALSE(gLcolor.isEqualRGB(gRcolor));
}

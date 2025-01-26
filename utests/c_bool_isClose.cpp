// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_bool_isClose.cpp
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
TEST(c_bool_isClose, unsigned8) {

  mjr::colorRGB8b   aLcolor;
  mjr::colorRGBA8b  bLcolor;

  mjr::colorRGB8b   aRcolor;
  mjr::colorRGBA8b  bRcolor;

  aLcolor.setToBlack();
  bLcolor.setToBlack();

  aRcolor.setToBlack();
  bRcolor.setToBlack();

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isClose(bRcolor, 0));

  EXPECT_TRUE(aLcolor.isCloseRGB(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isCloseRGB(bRcolor, 0));

  aLcolor.setChanToMax(0);
  bLcolor.setChanToMax(0);

  EXPECT_FALSE(aLcolor.isClose(aRcolor, 0));
  EXPECT_FALSE(bLcolor.isClose(bRcolor, 0));

  EXPECT_FALSE(aLcolor.isCloseRGB(aRcolor, 0));
  EXPECT_FALSE(bLcolor.isCloseRGB(bRcolor, 0));

  aRcolor.setChanToMax(0);
  bRcolor.setChanToMax(0);

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isClose(bRcolor, 0));

  EXPECT_TRUE(aLcolor.isCloseRGB(aRcolor, 0));
  EXPECT_TRUE(bLcolor.isCloseRGB(bRcolor, 0));

  bRcolor.setChanToMax(3);

  EXPECT_FALSE(bLcolor.isClose(bRcolor, 0));

  EXPECT_TRUE(bLcolor.isCloseRGB(bRcolor, 0));

  aLcolor.setChansRGB(1, 2, 3);
  aRcolor.setChansRGB(1, 3, 4);

  EXPECT_FALSE(aLcolor.isClose(aRcolor, 0));
  EXPECT_FALSE(aRcolor.isClose(aLcolor, 0));

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 1));  // false only if a channel delta is GREATER THAN epsilon
  EXPECT_TRUE(aRcolor.isClose(aLcolor, 1));

  EXPECT_TRUE(aLcolor.isClose(aRcolor, 2));
  EXPECT_TRUE(aRcolor.isClose(aLcolor, 2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_bool_isClose, float32) {

  mjr::colorRGB32F  cLcolor;
  mjr::colorRGBA32F dLcolor;

  mjr::colorRGB32F  cRcolor;
  mjr::colorRGBA32F dRcolor;

  cLcolor.setToBlack();
  dLcolor.setToBlack();

  cRcolor.setToBlack();
  dRcolor.setToBlack();

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isClose(dRcolor, 0));

  EXPECT_TRUE(cLcolor.isCloseRGB(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isCloseRGB(dRcolor, 0));

  cLcolor.setChanToMax(0);
  dLcolor.setChanToMax(0);

  EXPECT_FALSE(cLcolor.isClose(cRcolor, 0));
  EXPECT_FALSE(dLcolor.isClose(dRcolor, 0));

  EXPECT_FALSE(cLcolor.isCloseRGB(cRcolor, 0));
  EXPECT_FALSE(dLcolor.isCloseRGB(dRcolor, 0));

  cRcolor.setChanToMax(0);
  dRcolor.setChanToMax(0);

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isClose(dRcolor, 0));

  EXPECT_TRUE(cLcolor.isCloseRGB(cRcolor, 0));
  EXPECT_TRUE(dLcolor.isCloseRGB(dRcolor, 0));

  dRcolor.setChanToMax(3);

  EXPECT_FALSE(dLcolor.isClose(dRcolor, 0));

  EXPECT_TRUE(dLcolor.isCloseRGB(dRcolor, 0));

  cLcolor.setChansRGB(1, 2, 3);
  cRcolor.setChansRGB(1, 3, 4);

  EXPECT_FALSE(cLcolor.isClose(cRcolor, 0.0F));
  EXPECT_FALSE(cRcolor.isClose(cLcolor, 0.0F));

  EXPECT_FALSE(cLcolor.isClose(cRcolor, 0.9999F));
  EXPECT_FALSE(cRcolor.isClose(cLcolor, 0.9999F));

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 1.0F));  // Edge case is ill-defined for FP arithmetic, but OK here as we used numbers that are exactly representable -- might fail on other hardware.
  EXPECT_TRUE(cRcolor.isClose(cLcolor, 1.0F));

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 1.0001F));
  EXPECT_TRUE(cRcolor.isClose(cLcolor, 1.0001F));

  EXPECT_TRUE(cLcolor.isClose(cRcolor, 2.0F));
  EXPECT_TRUE(cRcolor.isClose(cLcolor, 2.0F));
}

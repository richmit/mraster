 // -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_tfrm_logic.cpp
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
TEST(c_tfrm_logic, unsigned8_cover) {

  mjr::colorRGBA8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorRGBA8b cColor;

  aColor.setRGBAfromLogPackIntRGBA(0xAABBCCDD);
  bColor.setRGBAfromLogPackIntRGBA(0x11223344);

  EXPECT_EQ(aColor.getRed(),    0xAA);
  EXPECT_EQ(aColor.getGreen(),  0xBB);
  EXPECT_EQ(aColor.getBlue(),   0xCC);
  EXPECT_EQ(aColor.getAlpha(),  0xDD);

  EXPECT_EQ(bColor.getRed(),    0x11);
  EXPECT_EQ(bColor.getGreen(),  0x22);
  EXPECT_EQ(bColor.getBlue(),   0x33);
  EXPECT_EQ(bColor.getAlpha(),  0x44);

  cColor = aColor;
  cColor.tfrmNot();
  EXPECT_EQ(cColor.getRed(),    0x55);
  EXPECT_EQ(cColor.getGreen(),  0x44);
  EXPECT_EQ(cColor.getBlue(),   0x33);
  EXPECT_EQ(cColor.getAlpha(),  0x22);

  cColor = aColor;
  cColor.tfrmOr(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xBB);
  EXPECT_EQ(cColor.getBlue(),   0xFF);
  EXPECT_EQ(cColor.getAlpha(),  0xDD);

  cColor = aColor;
  cColor.tfrmNor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x44);
  EXPECT_EQ(cColor.getGreen(),  0x44);
  EXPECT_EQ(cColor.getBlue(),   0x00);
  EXPECT_EQ(cColor.getAlpha(),  0x22);

  cColor = aColor;
  cColor.tfrmAnd(bColor);
  EXPECT_EQ(cColor.getRed(),    0x00);
  EXPECT_EQ(cColor.getGreen(),  0x22);
  EXPECT_EQ(cColor.getBlue(),   0x00);
  EXPECT_EQ(cColor.getAlpha(),  0x44);

  cColor = aColor;
  cColor.tfrmNand(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFF);
  EXPECT_EQ(cColor.getGreen(),  0xDD);
  EXPECT_EQ(cColor.getBlue(),   0xFF);
  EXPECT_EQ(cColor.getAlpha(),  0xBB);

  cColor = aColor;
  cColor.tfrmXor(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0x99);
  EXPECT_EQ(cColor.getBlue(),   0xFF);
  EXPECT_EQ(cColor.getAlpha(),  0x99);

  cColor = aColor;
  cColor.tfrmNxor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x44);
  EXPECT_EQ(cColor.getGreen(),  0x66);
  EXPECT_EQ(cColor.getBlue(),   0x00);
  EXPECT_EQ(cColor.getAlpha(),  0x66);

//  MJR TODO NOTE  Add tfrmShiftL & tfrmShiftR
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_tfrm_logic, unsigned8_no_cover) {

  mjr::colorRGBA64b aColor;
  mjr::colorRGBA64b bColor;
  mjr::colorRGBA64b cColor;

  aColor.setChansRGBA(0xAAAAAAAAAAAAAAAAu, 0xBBBBBBBBBBBBBBBBu, 0xCCCCCCCCCCCCCCCCu, 0xDDDDDDDDDDDDDDDDu);
  bColor.setChansRGBA(0x1111111111111111u, 0x2222222222222222u, 0x3333333333333333u, 0x4444444444444444u);

  EXPECT_EQ(aColor.getRed(),    0xAAAAAAAAAAAAAAAAu);
  EXPECT_EQ(aColor.getGreen(),  0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(aColor.getBlue(),   0xCCCCCCCCCCCCCCCCu);
  EXPECT_EQ(aColor.getAlpha(),  0xDDDDDDDDDDDDDDDDu);

  EXPECT_EQ(bColor.getRed(),    0x1111111111111111u);
  EXPECT_EQ(bColor.getGreen(),  0x2222222222222222u);
  EXPECT_EQ(bColor.getBlue(),   0x3333333333333333u);
  EXPECT_EQ(bColor.getAlpha(),  0x4444444444444444u);

  cColor = aColor;
  cColor.tfrmNot();
  EXPECT_EQ(cColor.getRed(),    0x5555555555555555u);
  EXPECT_EQ(cColor.getGreen(),  0x4444444444444444u);
  EXPECT_EQ(cColor.getBlue(),   0x3333333333333333u);
  EXPECT_EQ(cColor.getAlpha(),  0x2222222222222222u);

  cColor = aColor;
  cColor.tfrmOr(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(cColor.getGreen(),  0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(cColor.getBlue(),   0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getAlpha(),  0xDDDDDDDDDDDDDDDDu);

  cColor = aColor;
  cColor.tfrmNor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x4444444444444444u);
  EXPECT_EQ(cColor.getGreen(),  0x4444444444444444u);
  EXPECT_EQ(cColor.getBlue(),   0x0000000000000000u);
  EXPECT_EQ(cColor.getAlpha(),  0x2222222222222222u);

  cColor = aColor;
  cColor.tfrmAnd(bColor);
  EXPECT_EQ(cColor.getRed(),    0x0000000000000000u);
  EXPECT_EQ(cColor.getGreen(),  0x2222222222222222u);
  EXPECT_EQ(cColor.getBlue(),   0x0000000000000000u);
  EXPECT_EQ(cColor.getAlpha(),  0x4444444444444444u);

  cColor = aColor;
  cColor.tfrmNand(bColor);
  EXPECT_EQ(cColor.getRed(),    0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getGreen(),  0xDDDDDDDDDDDDDDDDu);
  EXPECT_EQ(cColor.getBlue(),   0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getAlpha(),  0xBBBBBBBBBBBBBBBBu);

  cColor = aColor;
  cColor.tfrmXor(bColor);
  EXPECT_EQ(cColor.getRed(),    0xBBBBBBBBBBBBBBBBu);
  EXPECT_EQ(cColor.getGreen(),  0x9999999999999999u);
  EXPECT_EQ(cColor.getBlue(),   0xFFFFFFFFFFFFFFFFu);
  EXPECT_EQ(cColor.getAlpha(),  0x9999999999999999u);

  cColor = aColor;
  cColor.tfrmNxor(bColor);
  EXPECT_EQ(cColor.getRed(),    0x4444444444444444u);
  EXPECT_EQ(cColor.getGreen(),  0x6666666666666666u);
  EXPECT_EQ(cColor.getBlue(),   0x0000000000000000u);
  EXPECT_EQ(cColor.getAlpha(),  0x6666666666666666u);

//  MJR TODO NOTE  Add tfrmShiftL & tfrmShiftR
}

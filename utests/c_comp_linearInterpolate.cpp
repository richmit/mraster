// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_comp_linearInterpolate.cpp
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
TEST(c_comp_linearInterpolate, unsigned8) {

  mjr::colorRGBA8b a1Color(10, 20, 30, 40);
  mjr::colorRGBA8b a2Color(10, 30, 20, 40);
  mjr::colorRGBA8b a3Color(40, 20, 30, 10);
  mjr::colorRGBA8b a4Color(90, 70, 10, 20);

  mjr::colorRGBA8b aColor;
  mjr::colorRGBA8b cColor;

 ////////////////////////////////////////////////////////////////////////////////

 aColor.linearInterpolate(0.0, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  a1Color.getC0());
 EXPECT_EQ(aColor.getC1(),  a1Color.getC1());
 EXPECT_EQ(aColor.getC2(),  a1Color.getC2());
 EXPECT_EQ(aColor.getC3(),  a1Color.getC3());

 aColor.linearInterpolate(1.0, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  a2Color.getC0());
 EXPECT_EQ(aColor.getC1(),  a2Color.getC1());
 EXPECT_EQ(aColor.getC2(),  a2Color.getC2());
 EXPECT_EQ(aColor.getC3(),  a2Color.getC3());

 aColor.linearInterpolate(0.5, a1Color, a2Color);
 cColor.uMean(0.5F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  cColor.getC0());
 EXPECT_EQ(aColor.getC1(),  cColor.getC1());
 EXPECT_EQ(aColor.getC2(),  cColor.getC2());
 EXPECT_EQ(aColor.getC3(),  cColor.getC3());

 aColor.linearInterpolate(0.25, a1Color, a2Color);
 cColor.uMean(0.75F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  cColor.getC0());
 EXPECT_EQ(aColor.getC1(),  cColor.getC1());
 EXPECT_EQ(aColor.getC2(),  cColor.getC2());
 EXPECT_EQ(aColor.getC3(),  cColor.getC3());

 aColor.linearInterpolate(0.75, a1Color, a2Color);
 cColor.uMean(0.25F, a1Color, a2Color);
 EXPECT_EQ(aColor.getC0(),  cColor.getC0());
 EXPECT_EQ(aColor.getC1(),  cColor.getC1());
 EXPECT_EQ(aColor.getC2(),  cColor.getC2());
 EXPECT_EQ(aColor.getC3(),  cColor.getC3());
}

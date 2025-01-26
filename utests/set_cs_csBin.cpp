// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      set_cs_csBin.cpp
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
TEST(set_cs_csBin, int_in_unsigned8_out) {

  mjr::colorRGB8b   a0Color, a1Color;

  a0Color.setToBlack();
  a1Color.setToWhite();

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(0).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(2).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(4).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(6).isEqualRGB(a0Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(8).isEqualRGB(a0Color));

  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(1).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(3).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(5).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(7).isEqualRGB(a1Color));
  EXPECT_TRUE(mjr::colorRGB8b::csBin01::c(9).isEqualRGB(a1Color));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(set_cs_csBin, int_in_float32_out) {

  mjr::colorRGB32F  b0Color, b1Color;

  b0Color.setToBlack();
  b1Color.setToWhite();

  ////////////////////////////////////////////////////////////////////////////////

  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(0).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(2).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(4).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(6).isEqualRGB(b0Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(8).isEqualRGB(b0Color));

  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(1).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(3).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(5).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(7).isEqualRGB(b1Color));
  EXPECT_TRUE(mjr::colorRGB32F::csBin01::c(9).isEqualRGB(b1Color));
}

// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_comp_MinMax.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-25
 @brief     Unit tests for basic color methods.@EOL
 @keywords  gtest
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
TEST(c_comp_MinMax, unsigned8) {
  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 11).getMaxC(),                                             11);
  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 11).getMaxRGB(),                                           7);

  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 1).getMinC(),                                              1);
  EXPECT_EQ(mjr::colorRGBA8b(2, 5, 7, 1).getMinRGB(),                                            2);

  EXPECT_EQ(mjr::colorRGB8b(2, 5, 7).getMaxC(),                                                  7);
  EXPECT_EQ(mjr::colorRGB32F(2, 5, 7).getMaxC(),                                                 7);

  EXPECT_EQ(mjr::colorRGB8b(2, 5, 7).getMinC(),                                                  2);
  EXPECT_EQ(mjr::colorRGB32F(2, 5, 7).getMinC(),                                                 2);

  mjr::color2c8b aColor; aColor.setC0(5); aColor.setC1(2);
  mjr::color2c8b bColor; bColor.setC0(5); bColor.setC1(2);

  EXPECT_EQ(aColor.getMaxC(),                                                                    5);
  EXPECT_EQ(bColor.getMaxC(),                                                                    5);

  EXPECT_EQ(aColor.getMinC(),                                                                    2);
  EXPECT_EQ(bColor.getMinC(),                                                                    2);

  EXPECT_EQ(mjr::colorRGBA8b(2).getMaxC(),                                                       2);

  EXPECT_EQ(mjr::colorRGBA8b(2).getMinC(),                                                       2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_comp_MinMax, float32) {
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).getMaxC(),                                          11, 0.000001);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 11).getMaxRGB(),                                        7, 0.000001);

  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 1).getMinC(),                                           1, 0.000001);
  EXPECT_NEAR(mjr::colorRGBA32F(2, 5, 7, 1).getMinRGB(),                                         2, 0.000001);

  EXPECT_EQ(mjr::colorRGB8b(2, 5, 7).getMaxC(),                                                  7);
  EXPECT_EQ(mjr::colorRGB32F(2, 5, 7).getMaxC(),                                                 7);

  EXPECT_EQ(mjr::colorRGB8b(2, 5, 7).getMinC(),                                                  2);
  EXPECT_EQ(mjr::colorRGB32F(2, 5, 7).getMinC(),                                                 2);

  mjr::color2c8b aColor; aColor.setC0(5); aColor.setC1(2);
  mjr::color2c8b bColor; bColor.setC0(5); bColor.setC1(2);

  EXPECT_EQ(aColor.getMaxC(),                                                                    5);
  EXPECT_EQ(bColor.getMaxC(),                                                                    5);

  EXPECT_EQ(aColor.getMinC(),                                                                    2);
  EXPECT_EQ(bColor.getMinC(),                                                                    2);

  EXPECT_NEAR(mjr::colorRGBA32F(2).getMaxC(),                                                    2, 0.000001);

  EXPECT_NEAR(mjr::colorRGBA32F(2).getMinC(),                                                    2, 0.000001);
}

// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_chan_gen.cpp
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
TEST(c_set_chan_gen, color4c8b) {

  mjr::color4c8b aColor;

  aColor.setToBlack();
  aColor.setChan(0, 11);
  aColor.setChan(1, 22);
  aColor.setChan(2, 33);
  aColor.setChan(3, 44);

  EXPECT_EQ(aColor.getChan(0),       11);
  EXPECT_EQ(aColor.getChan(1),       22);
  EXPECT_EQ(aColor.getChan(2),       33);
  EXPECT_EQ(aColor.getChan(3),       44);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  33);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0(55);
  aColor.setC1(66);
  aColor.setC2(77);
  aColor.setC3(88);

  EXPECT_EQ(aColor.getChan(0),       55);
  EXPECT_EQ(aColor.getChan(1),       66);
  EXPECT_EQ(aColor.getChan(2),       77);
  EXPECT_EQ(aColor.getChan(3),       88);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  55);
  EXPECT_EQ(aColor.getChan_byte(1),  66);
  EXPECT_EQ(aColor.getChan_byte(2),  77);
  EXPECT_EQ(aColor.getChan_byte(3),  88);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChans(99);

  EXPECT_EQ(aColor.getChan(0),       99);
  EXPECT_EQ(aColor.getChan(1),       99);
  EXPECT_EQ(aColor.getChan(2),       99);
  EXPECT_EQ(aColor.getChan(3),       99);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  99);
  EXPECT_EQ(aColor.getChan_byte(1),  99);
  EXPECT_EQ(aColor.getChan_byte(2),  99);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB(33, 44, 55);

  EXPECT_EQ(aColor.getChan(0),       33);
  EXPECT_EQ(aColor.getChan(1),       44);
  EXPECT_EQ(aColor.getChan(2),       55);
  EXPECT_EQ(aColor.getChan(3),       99);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  33);
  EXPECT_EQ(aColor.getChan_byte(1),  44);
  EXPECT_EQ(aColor.getChan_byte(2),  55);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA(11, 22, 33, 44);

  EXPECT_EQ(aColor.getChan(0),       11);
  EXPECT_EQ(aColor.getChan(1),       22);
  EXPECT_EQ(aColor.getChan(2),       33);
  EXPECT_EQ(aColor.getChan(3),       44);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  33);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_gen, color4c16b) {
  mjr::color4c16b aColor;

  aColor.setToBlack();
  aColor.setChan(0, 1024);
  aColor.setChan(1, 2048);
  aColor.setChan(2, 4096);
  aColor.setChan(3, 8192);

  EXPECT_EQ(aColor.getChan(0),       1024);
  EXPECT_EQ(aColor.getChan(1),       2048);
  EXPECT_EQ(aColor.getChan(2),       4096);
  EXPECT_EQ(aColor.getChan(3),       8192);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x03);
  EXPECT_EQ(aColor.getChan_byte(1),  0x07);
  EXPECT_EQ(aColor.getChan_byte(2),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x1f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0(8192);
  aColor.setC1(4096);
  aColor.setC2(2048);
  aColor.setC3(1024);

  EXPECT_EQ(aColor.getChan(0),       8192);
  EXPECT_EQ(aColor.getChan(1),       4096);
  EXPECT_EQ(aColor.getChan(2),       2048);
  EXPECT_EQ(aColor.getChan(3),       1024);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x1f);
  EXPECT_EQ(aColor.getChan_byte(1),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(2),  0x07);
  EXPECT_EQ(aColor.getChan_byte(3),  0x03);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChans(32768);

  EXPECT_EQ(aColor.getChan(0),       32768);
  EXPECT_EQ(aColor.getChan(1),       32768);
  EXPECT_EQ(aColor.getChan(2),       32768);
  EXPECT_EQ(aColor.getChan(3),       32768);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x7f);
  EXPECT_EQ(aColor.getChan_byte(1),  0x7f);
  EXPECT_EQ(aColor.getChan_byte(2),  0x7f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x7f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB(4096, 8192, 16384);

  EXPECT_EQ(aColor.getChan(0),       4096);
  EXPECT_EQ(aColor.getChan(1),       8192);
  EXPECT_EQ(aColor.getChan(2),       16384);
  EXPECT_EQ(aColor.getChan(3),       32768);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(1),  0x1f);
  EXPECT_EQ(aColor.getChan_byte(2),  0x3f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x7f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA(1024, 2048, 4096, 8192);

  EXPECT_EQ(aColor.getChan(0),       1024);
  EXPECT_EQ(aColor.getChan(1),       2048);
  EXPECT_EQ(aColor.getChan(2),       4096);
  EXPECT_EQ(aColor.getChan(3),       8192);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0x03);
  EXPECT_EQ(aColor.getChan_byte(1),  0x07);
  EXPECT_EQ(aColor.getChan_byte(2),  0x0f);
  EXPECT_EQ(aColor.getChan_byte(3),  0x1f);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  //Corners
  aColor.setChans(0);

  EXPECT_EQ(aColor.getChan(0),       0);
  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());

  EXPECT_EQ(aColor.getChan_dbl(0),  0.0);
  EXPECT_EQ(aColor.getChan_dbl(0),  aColor.getC0_dbl());

  aColor.setChans(65535);

  EXPECT_EQ(aColor.getChan(0),       65535);
  EXPECT_EQ(aColor.getChan(0),       aColor.getC1());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC1_byte());

  EXPECT_EQ(aColor.getChan_dbl(0),  1.0);
  EXPECT_EQ(aColor.getChan_dbl(0),  aColor.getC1_dbl());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_gen, color4c64F) {

  mjr::color4c64F aColor;

  aColor.setToBlack();
  aColor.setChan(0, 0.25);
  aColor.setChan(1, 0.50);
  aColor.setChan(2, 0.75);
  aColor.setChan(3, 1.00);

  EXPECT_NEAR(aColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       1.00, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),   63);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  191);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0(1.00);
  aColor.setC1(0.75);
  aColor.setC2(0.50);
  aColor.setC3(0.25);

  EXPECT_NEAR(aColor.getChan(0),       1.00, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.25, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  191);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  63);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChans(0.0);

  EXPECT_NEAR(aColor.getChan(0),       0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB(0.75, 0.50, 1.0);

  EXPECT_NEAR(aColor.getChan(0),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       1.00, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.00, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),  191);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA(0.25, 0.50, 0.75, 1.00);

  EXPECT_NEAR(aColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.75, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       1.00, 0.000001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.000001);

  EXPECT_EQ(aColor.getChan_byte(0),   63);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  191);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());
}

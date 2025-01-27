// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_chan_hex.cpp
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
TEST(c_set_chan_hex, color4c8b) {

  mjr::color4c8b aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aabbccdd");
  EXPECT_EQ(aColor.getC0(),  0xAA);
  EXPECT_EQ(aColor.getC1(),  0xBB);
  EXPECT_EQ(aColor.getC2(),  0xCC);
  EXPECT_EQ(aColor.getC3(),  0xDD);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbccdd");
  EXPECT_EQ(aColor.getC0(),  0xBB);
  EXPECT_EQ(aColor.getC1(),  0xCC);
  EXPECT_EQ(aColor.getC2(),  0xDD);
  EXPECT_EQ(aColor.getC3(),  0xFF);

  aColor.setToWhite();
  aColor.setChans("#aa");
  EXPECT_EQ(aColor.getC0(),  0xAA);
  EXPECT_EQ(aColor.getC1(),  0xFF);
  EXPECT_EQ(aColor.getC2(),  0xFF);
  EXPECT_EQ(aColor.getC3(),  0xFF);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  EXPECT_EQ(aColor.getC0(),  0xFF);
  EXPECT_EQ(aColor.getC1(),  0xFF);
  EXPECT_EQ(aColor.getC2(),  0xFF);
  EXPECT_EQ(aColor.getC3(),  0xFF);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbccdd", true);
  EXPECT_EQ(aColor.getC0(),  0xBB);
  EXPECT_EQ(aColor.getC1(),  0xCC);
  EXPECT_EQ(aColor.getC2(),  0xDD);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#aa", true);
  EXPECT_EQ(aColor.getC0(),  0xAA);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#a", true);
  EXPECT_EQ(aColor.getC0(),  0x0000);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_hex, color4c16b) {

  mjr::color4c16b aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aaaabbbbccccdddd");
  EXPECT_EQ(aColor.getC0(),  0xAAAA);
  EXPECT_EQ(aColor.getC1(),  0xBBBB);
  EXPECT_EQ(aColor.getC2(),  0xCCCC);
  EXPECT_EQ(aColor.getC3(),  0xDDDD);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbbbccccdddd");
  EXPECT_EQ(aColor.getC0(),  0xBBBB);
  EXPECT_EQ(aColor.getC1(),  0xCCCC);
  EXPECT_EQ(aColor.getC2(),  0xDDDD);
  EXPECT_EQ(aColor.getC3(),  0xFFFF);

  aColor.setToWhite();
  aColor.setChans("#aaaa");
  EXPECT_EQ(aColor.getC0(),  0xAAAA);
  EXPECT_EQ(aColor.getC1(),  0xFFFF);
  EXPECT_EQ(aColor.getC2(),  0xFFFF);
  EXPECT_EQ(aColor.getC3(),  0xFFFF);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  EXPECT_EQ(aColor.getC0(),  0xFFFF);
  EXPECT_EQ(aColor.getC1(),  0xFFFF);
  EXPECT_EQ(aColor.getC2(),  0xFFFF);
  EXPECT_EQ(aColor.getC3(),  0xFFFF);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbbbccccdddd", true);
  EXPECT_EQ(aColor.getC0(),  0xBBBB);
  EXPECT_EQ(aColor.getC1(),  0xCCCC);
  EXPECT_EQ(aColor.getC2(),  0xDDDD);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#aaaa", true);
  EXPECT_EQ(aColor.getC0(),  0xAAAA);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);

  aColor.setToWhite();
  aColor.setChans("#aaa", true);
  EXPECT_EQ(aColor.getC0(),  0x0000);
  EXPECT_EQ(aColor.getC1(),  0x0000);
  EXPECT_EQ(aColor.getC2(),  0x0000);
  EXPECT_EQ(aColor.getC3(),  0x0000);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_hex, color4c64F) {

  mjr::color4c64F aColor("0");
  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  EXPECT_NEAR(aColor.getC0(),  0.66666666666, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.73333333333, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.80000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.86666666666, 0.00001);

  // undefined chans left alown
  aColor.setToWhite();
  aColor.setChans("#bbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  EXPECT_NEAR(aColor.getC0(),  0.73333333333, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.80000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.86666666666, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  1.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaa");
  EXPECT_NEAR(aColor.getC0(),  0.66666666666, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  1.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaa");
  EXPECT_NEAR(aColor.getC0(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  1.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  1.00000000000, 0.00001);

  // undefined chans set to min
  aColor.setToWhite();
  aColor.setChans("#bbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd", true);
  EXPECT_NEAR(aColor.getC0(),  0.73333333333, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.80000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.86666666666, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaaaaaaaaaaaaaaa", true);
  EXPECT_NEAR(aColor.getC0(),  0.66666666666, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.00000000000, 0.00001);

  aColor.setToWhite();
  aColor.setChans("#aaa", true);
  EXPECT_NEAR(aColor.getC0(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC1(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC2(),  0.00000000000, 0.00001);
  EXPECT_NEAR(aColor.getC3(),  0.00000000000, 0.00001);

 }

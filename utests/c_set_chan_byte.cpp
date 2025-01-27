// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_chan_byte.cpp
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
TEST(c_set_chan_byte, color4c8b) {

  mjr::color4c8b aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 33);
  aColor.setChan_byte(3, 44);

  EXPECT_EQ(aColor.getChan(0)      , 11);
  EXPECT_EQ(aColor.getChan(1)      , 22);
  EXPECT_EQ(aColor.getChan(2)      , 33);
  EXPECT_EQ(aColor.getChan(3)      , 44);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 11);
  EXPECT_EQ(aColor.getChan_byte(1) , 22);
  EXPECT_EQ(aColor.getChan_byte(2) , 33);
  EXPECT_EQ(aColor.getChan_byte(3) , 44);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(66);
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  EXPECT_EQ(aColor.getChan(0)      , 55);
  EXPECT_EQ(aColor.getChan(1)      , 66);
  EXPECT_EQ(aColor.getChan(2)      , 77);
  EXPECT_EQ(aColor.getChan(3)      , 88);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 55);
  EXPECT_EQ(aColor.getChan_byte(1) , 66);
  EXPECT_EQ(aColor.getChan_byte(2) , 77);
  EXPECT_EQ(aColor.getChan_byte(3) , 88);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setChans_byte(99);

  EXPECT_EQ(aColor.getChan(0)      , 99);
  EXPECT_EQ(aColor.getChan(1)      , 99);
  EXPECT_EQ(aColor.getChan(2)      , 99);
  EXPECT_EQ(aColor.getChan(3)      , 99);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 99);
  EXPECT_EQ(aColor.getChan_byte(1) , 99);
  EXPECT_EQ(aColor.getChan_byte(2) , 99);
  EXPECT_EQ(aColor.getChan_byte(3) , 99);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setChansRGB_byte(33, 44, 55);

  EXPECT_EQ(aColor.getChan(0)      , 33);
  EXPECT_EQ(aColor.getChan(1)      , 44);
  EXPECT_EQ(aColor.getChan(2)      , 55);
  EXPECT_EQ(aColor.getChan(3)      , 99);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 33);
  EXPECT_EQ(aColor.getChan_byte(1) , 44);
  EXPECT_EQ(aColor.getChan_byte(2) , 55);
  EXPECT_EQ(aColor.getChan_byte(3) , 99);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 33, 44);

  EXPECT_EQ(aColor.getChan(0)      , 11);
  EXPECT_EQ(aColor.getChan(1)      , 22);
  EXPECT_EQ(aColor.getChan(2)      , 33);
  EXPECT_EQ(aColor.getChan(3)      , 44);

  EXPECT_EQ(aColor.getChan(0)      , aColor.getC0());
  EXPECT_EQ(aColor.getChan(1)      , aColor.getC1());
  EXPECT_EQ(aColor.getChan(2)      , aColor.getC2());
  EXPECT_EQ(aColor.getChan(3)      , aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0) , 11);
  EXPECT_EQ(aColor.getChan_byte(1) , 22);
  EXPECT_EQ(aColor.getChan_byte(2) , 33);
  EXPECT_EQ(aColor.getChan_byte(3) , 44);

  EXPECT_EQ(aColor.getChan_byte(0) , aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1) , aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2) , aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3) , aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  EXPECT_EQ(aColor.getChan(0)      , mjr::color4c8b::minChanVal);
  EXPECT_EQ(aColor.getChan(1)      , mjr::color4c8b::maxChanVal);
  EXPECT_EQ(aColor.getChan(2)      , mjr::color4c8b::minChanVal);
  EXPECT_EQ(aColor.getChan(3)      , mjr::color4c8b::maxChanVal);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_byte, color4c16b) {

  mjr::color4c16b aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 33);
  aColor.setChan_byte(3, 44);

  EXPECT_EQ(aColor.getChan(0),       0xB0B);
  EXPECT_EQ(aColor.getChan(1),       0x1616);
  EXPECT_EQ(aColor.getChan(2),       0x2121);
  EXPECT_EQ(aColor.getChan(3),       0x2C2C);

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

  aColor.setC0_byte(55);
  aColor.setC1_byte(66);
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  EXPECT_EQ(aColor.getChan(0),       14135);
  EXPECT_EQ(aColor.getChan(1),       16962);
  EXPECT_EQ(aColor.getChan(2),       19789);
  EXPECT_EQ(aColor.getChan(3),       22616);

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

  aColor.setChans_byte(99);

  EXPECT_EQ(aColor.getChan(0),       25443);
  EXPECT_EQ(aColor.getChan(1),       25443);
  EXPECT_EQ(aColor.getChan(2),       25443);
  EXPECT_EQ(aColor.getChan(3),       25443);

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

  aColor.setChansRGB_byte(33, 44, 55);

  EXPECT_EQ(aColor.getChan(0),       8481);
  EXPECT_EQ(aColor.getChan(1),       11308);
  EXPECT_EQ(aColor.getChan(2),       14135);
  EXPECT_EQ(aColor.getChan(3),       25443);

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

  aColor.setChansRGBA_byte(11, 22, 33, 44);

  EXPECT_EQ(aColor.getChan(0),       2827);
  EXPECT_EQ(aColor.getChan(1),       5654);
  EXPECT_EQ(aColor.getChan(2),       8481);
  EXPECT_EQ(aColor.getChan(3),       11308);

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

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  EXPECT_EQ(aColor.getChan(0),       mjr::color4c16b::minChanVal);
  EXPECT_EQ(aColor.getChan(1),       mjr::color4c16b::maxChanVal);
  EXPECT_EQ(aColor.getChan(2),       mjr::color4c16b::minChanVal);
  EXPECT_EQ(aColor.getChan(3),       mjr::color4c16b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_byte, color4c64F) {

  mjr::color4c64F aColor;

  aColor.setToBlack();
  aColor.setChan_byte(0, 11);
  aColor.setChan_byte(1, 22);
  aColor.setChan_byte(2, 34); // 33 has a rounding error :)
  aColor.setChan_byte(3, 44);

  EXPECT_NEAR(aColor.getChan(0),       0.043137254902, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.0862745098039, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.133333333333, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.172549019608, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  34);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setC0_byte(55);
  aColor.setC1_byte(65); // 66 has rounding error :)
  aColor.setC2_byte(77);
  aColor.setC3_byte(88);

  EXPECT_NEAR(aColor.getChan(0),       0.21568627450980393, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.254901960784, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.30196078431372547, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.34509803921568627, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  55);
  EXPECT_EQ(aColor.getChan_byte(1),  65);
  EXPECT_EQ(aColor.getChan_byte(2),  77);
  EXPECT_EQ(aColor.getChan_byte(3),  88);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChans_byte(99);

  EXPECT_NEAR(aColor.getChan(0),       0.38823529411764707, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.38823529411764707, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.38823529411764707, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.38823529411764707, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  99);
  EXPECT_EQ(aColor.getChan_byte(1),  99);
  EXPECT_EQ(aColor.getChan_byte(2),  99);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGB_byte(34, 44, 55);

  EXPECT_NEAR(aColor.getChan(0),       0.133333333333, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.17254901960784313, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.21568627450980393, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.38823529411764707, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  34);
  EXPECT_EQ(aColor.getChan_byte(1),  44);
  EXPECT_EQ(aColor.getChan_byte(2),  55);
  EXPECT_EQ(aColor.getChan_byte(3),  99);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  aColor.setChansRGBA_byte(11, 22, 34, 44);

  EXPECT_NEAR(aColor.getChan(0),       0.043137254902, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       0.08627450980392157, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       0.133333333333, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       0.17254901960784313, 0.0001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.0001);

  EXPECT_EQ(aColor.getChan_byte(0),  11);
  EXPECT_EQ(aColor.getChan_byte(1),  22);
  EXPECT_EQ(aColor.getChan_byte(2),  34);
  EXPECT_EQ(aColor.getChan_byte(3),  44);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  // Test that max & min are hit
  aColor.setChansRGBA_byte(0, 255, 0, 255);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.0001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.0001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.0001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::maxChanVal, 0.0001);
}

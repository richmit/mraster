// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_chan_dbl.cpp
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
TEST(c_set_chan_dbl, color4c8b) {

  mjr::color4c8b aColor;
  decltype(aColor)::channelType mxcv = 255;
  decltype(aColor)::channelType hlcv = 255/2;
  decltype(aColor)::channelType mncv =   0;
  double                        hldb = 127.0/mxcv;

  EXPECT_EQ(decltype(aColor)::maxChanVal,   mxcv);
  EXPECT_EQ(decltype(aColor)::minChanVal,   mncv);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(1, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       hlcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0,  0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChans_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mxcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   1.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       hlcv);
  EXPECT_EQ(aColor.getChan(3),       hlcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  127);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(3),   hldb, 0.005);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_dbl, color4c16b) {
  mjr::color4c16b aColor;

  decltype(aColor)::channelType mxcv = 65535;
  decltype(aColor)::channelType hlcv = 32767; // 
  decltype(aColor)::channelType mncv =   0;
  double                        hldb = 32767.0/mxcv;

  EXPECT_EQ(decltype(aColor)::maxChanVal,   mxcv);
  EXPECT_EQ(decltype(aColor)::minChanVal,   mncv);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(1, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       hlcv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0,  0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0,  0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       mncv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChans_dbl(1.0);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mxcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   1.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  EXPECT_EQ(aColor.getChan(0),       mxcv);
  EXPECT_EQ(aColor.getChan(1),       mncv);
  EXPECT_EQ(aColor.getChan(2),       hlcv);
  EXPECT_EQ(aColor.getChan(3),       hlcv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  127);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0,  0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   hldb, 0.005);
  EXPECT_NEAR(aColor.getChan_dbl(3),   hldb, 0.005);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  EXPECT_EQ(aColor.getChan(0),       mncv);
  EXPECT_EQ(aColor.getChan(1),       mxcv);
  EXPECT_EQ(aColor.getChan(2),       mxcv);
  EXPECT_EQ(aColor.getChan(3),       mncv);

  EXPECT_EQ(aColor.getChan(0),       aColor.getC0());
  EXPECT_EQ(aColor.getChan(1),       aColor.getC1());
  EXPECT_EQ(aColor.getChan(2),       aColor.getC2());
  EXPECT_EQ(aColor.getChan(3),       aColor.getC3());

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.000001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.000001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_dbl, color4c64F) {

  mjr::color4c64F aColor;

  EXPECT_NEAR(mjr::color4c64F::maxChanVal,   1.0, 0.00001);
  EXPECT_NEAR(mjr::color4c64F::minChanVal,   0.0, 0.00001);

  aColor.setToBlack();
  aColor.setChan_dbl(0, 1.0);
  aColor.setChan_dbl(2, 1.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(0, 0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(1.0, 1.0, 0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChan_dbl(1, 0.5);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       0.5,                         0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  127);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.5, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGB_dbl(0.0, 0.0, 0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  0);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChans_dbl(1.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::maxChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  255);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   1.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setChansRGBA_dbl(1.0, 0.0, 0.5, 0.5);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       0.5, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       0.5, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  255);
  EXPECT_EQ(aColor.getChan_byte(1),  0);
  EXPECT_EQ(aColor.getChan_byte(2),  127);
  EXPECT_EQ(aColor.getChan_byte(3),  127);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   0.5, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.5, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);

  aColor.setC0_dbl(0.0);
  aColor.setC1_dbl(1.0);
  aColor.setC2_dbl(1.0);
  aColor.setC3_dbl(0.0);

  EXPECT_NEAR(aColor.getChan(0),       mjr::color4c64F::minChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       mjr::color4c64F::maxChanVal, 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       mjr::color4c64F::minChanVal, 0.00001);

  EXPECT_NEAR(aColor.getChan(0),       aColor.getC0(), 0.00001);
  EXPECT_NEAR(aColor.getChan(1),       aColor.getC1(), 0.00001);
  EXPECT_NEAR(aColor.getChan(2),       aColor.getC2(), 0.00001);
  EXPECT_NEAR(aColor.getChan(3),       aColor.getC3(), 0.00001);

  EXPECT_EQ(aColor.getChan_byte(0),  0);
  EXPECT_EQ(aColor.getChan_byte(1),  255);
  EXPECT_EQ(aColor.getChan_byte(2),  255);
  EXPECT_EQ(aColor.getChan_byte(3),  0);

  EXPECT_EQ(aColor.getChan_byte(0),  aColor.getC0_byte());
  EXPECT_EQ(aColor.getChan_byte(1),  aColor.getC1_byte());
  EXPECT_EQ(aColor.getChan_byte(2),  aColor.getC2_byte());
  EXPECT_EQ(aColor.getChan_byte(3),  aColor.getC3_byte());

  EXPECT_NEAR(aColor.getChan_dbl(0),   0.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   1.0, 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   0.0, 0.00001);

  EXPECT_NEAR(aColor.getChan_dbl(0),   aColor.getC0_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(1),   aColor.getC1_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(2),   aColor.getC2_dbl(), 0.00001);
  EXPECT_NEAR(aColor.getChan_dbl(3),   aColor.getC3_dbl(), 0.00001);
}

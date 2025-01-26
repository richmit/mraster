// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_tfrm_websafe.cpp
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
TEST(tfrm_websafe, unsigned8) {

  mjr::colorRGB8b  aColor;
  mjr::colorRGB8b  bColor;
  mjr::colorRGBA8b dColor;

  aColor.setChansRGB(0x00, 0x33, 0x66);
  bColor.setChansRGB(0x00, 0x33, 0x66);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setChansRGB(0x99, 0xCC, 0xFF);
  bColor.setChansRGB(0x99, 0xCC, 0xFF);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setChansRGB(0x01, 0x34, 0x67);
  bColor.setChansRGB(0x00, 0x33, 0x66);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  aColor.setChansRGB(0x98, 0xCB, 0xFE);
  bColor.setChansRGB(0x99, 0xCC, 0xFF);
  aColor.tfrmWebSafeRGB();
  EXPECT_EQ(aColor.getRed(),    bColor.getRed());
  EXPECT_EQ(aColor.getGreen(),  bColor.getGreen());
  EXPECT_EQ(aColor.getBlue(),   bColor.getBlue());

  dColor.setChans(0xCB);
  dColor.tfrmWebSafeRGB();
  EXPECT_EQ(dColor.getRed(),    0xCC);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xCC);
  EXPECT_EQ(dColor.getAlpha(),  0xCB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(tfrm_websafe, float32) {

  mjr::colorRGB32F cColor;

  cColor.setChansRGB(0.05F, 0.15F, 0.35F);
  cColor.tfrmWebSafeRGB();
  EXPECT_NEAR(cColor.getRed(),    0.0,    0.0001);
  EXPECT_NEAR(cColor.getGreen(),  0.2,    0.0001);
  EXPECT_NEAR(cColor.getBlue(),   0.4,    0.0001);

  cColor.setChansRGB(0.55F, 0.75F, 0.95F);
  cColor.tfrmWebSafeRGB();
  EXPECT_NEAR(cColor.getRed(),    0.6,    0.0001);
  EXPECT_NEAR(cColor.getGreen(),  0.8,    0.0001);
  EXPECT_NEAR(cColor.getBlue(),   1.0,    0.0001);
}

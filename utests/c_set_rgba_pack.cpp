// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_rgba_pack.cpp
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
TEST(c_set_chan_argb_packed, unsigned8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntARGB(0xAABBCCDD);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntARGB(0x00DDCCBB);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_rgba_packed, unsigned8) {
  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntRGBA(0xBBCCDDAA);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntRGBA(0xDDCCBB00);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_abgr_packed, unsigned8) {
  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntABGR(0xAADDCCBB);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntABGR(0x00BBCCDD);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_abrg_packed, unsigned8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorABGR8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntABRG(0xAADDBBCC);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC3(),     0xBB);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xDD);
  EXPECT_EQ(dColor.getC0(),     0xAA);

  dColor.setRGBfromLogPackIntABRG(0x00BBDDCC);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC3(),     0xDD);
  EXPECT_EQ(dColor.getC2(),     0xCC);
  EXPECT_EQ(dColor.getC1(),     0xBB);
  EXPECT_EQ(dColor.getC0(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_bgra_packed, unsigned8) {

  mjr::colorARGB8b aColor;
  mjr::colorRGBA8b bColor;
  mjr::colorBGRA8b cColor;
  mjr::colorBGRA8b dColor;

  mjr::colorRGB8b eColor;
  mjr::colorBGR8b fColor;

  aColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(aColor.getRed(),    0xBB);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xDD);
  EXPECT_EQ(aColor.getAlpha(),  0xAA);

  EXPECT_EQ(aColor.getC1(),     0xBB);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xDD);
  EXPECT_EQ(aColor.getC0(),     0xAA);

  aColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(aColor.getRed(),    0xDD);
  EXPECT_EQ(aColor.getGreen(),  0xCC);
  EXPECT_EQ(aColor.getBlue(),   0xBB);
  EXPECT_EQ(aColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(aColor.getC1(),     0xDD);
  EXPECT_EQ(aColor.getC2(),     0xCC);
  EXPECT_EQ(aColor.getC3(),     0xBB);
  EXPECT_EQ(aColor.getC0(),     0xAA); // From before

  eColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(eColor.getRed(),    0xDD);
  EXPECT_EQ(eColor.getGreen(),  0xCC);
  EXPECT_EQ(eColor.getBlue(),   0xBB);

  EXPECT_EQ(eColor.getC0(),     0xDD);
  EXPECT_EQ(eColor.getC1(),     0xCC);
  EXPECT_EQ(eColor.getC2(),     0xBB);

  bColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(bColor.getRed(),    0xBB);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xDD);
  EXPECT_EQ(bColor.getAlpha(),  0xAA);

  EXPECT_EQ(bColor.getC0(),     0xBB);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xDD);
  EXPECT_EQ(bColor.getC3(),     0xAA);

  bColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(bColor.getRed(),    0xDD);
  EXPECT_EQ(bColor.getGreen(),  0xCC);
  EXPECT_EQ(bColor.getBlue(),   0xBB);
  EXPECT_EQ(bColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(bColor.getC0(),     0xDD);
  EXPECT_EQ(bColor.getC1(),     0xCC);
  EXPECT_EQ(bColor.getC2(),     0xBB);
  EXPECT_EQ(bColor.getC3(),     0xAA); // From before

  fColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(fColor.getRed(),    0xDD);
  EXPECT_EQ(fColor.getGreen(),  0xCC);
  EXPECT_EQ(fColor.getBlue(),   0xBB);

  EXPECT_EQ(fColor.getC2(),     0xDD);
  EXPECT_EQ(fColor.getC1(),     0xCC);
  EXPECT_EQ(fColor.getC0(),     0xBB);

  cColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(cColor.getRed(),    0xBB);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xDD);
  EXPECT_EQ(cColor.getAlpha(),  0xAA);

  EXPECT_EQ(cColor.getC2(),     0xBB);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xDD);
  EXPECT_EQ(cColor.getC3(),     0xAA);

  cColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(cColor.getRed(),    0xDD);
  EXPECT_EQ(cColor.getGreen(),  0xCC);
  EXPECT_EQ(cColor.getBlue(),   0xBB);
  EXPECT_EQ(cColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(cColor.getC2(),     0xDD);
  EXPECT_EQ(cColor.getC1(),     0xCC);
  EXPECT_EQ(cColor.getC0(),     0xBB);
  EXPECT_EQ(cColor.getC3(),     0xAA); // From before

  dColor.setRGBAfromLogPackIntBGRA(0xDDCCBBAA);

  EXPECT_EQ(dColor.getRed(),    0xBB);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xDD);
  EXPECT_EQ(dColor.getAlpha(),  0xAA);

  EXPECT_EQ(dColor.getC2(),     0xBB);
  EXPECT_EQ(dColor.getC1(),     0xCC);
  EXPECT_EQ(dColor.getC0(),     0xDD);
  EXPECT_EQ(dColor.getC3(),     0xAA);

  dColor.setRGBfromLogPackIntBGRA(0xBBCCDD00);

  EXPECT_EQ(dColor.getRed(),    0xDD);
  EXPECT_EQ(dColor.getGreen(),  0xCC);
  EXPECT_EQ(dColor.getBlue(),   0xBB);
  EXPECT_EQ(dColor.getAlpha(),  0xAA); // From before

  EXPECT_EQ(dColor.getC2(),     0xDD);
  EXPECT_EQ(dColor.getC1(),     0xCC);
  EXPECT_EQ(dColor.getC0(),     0xBB);
  EXPECT_EQ(dColor.getC3(),     0xAA); // From before
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_argb_packed, unsigned16) {

  // We really just need to make sure the scale works for 16bit -- i.e. that the bytes of the integer are truely inturprted by set*_byte() members.

  mjr::colorRGBA16b bColor;
  mjr::colorRGB16b  eColor;

  bColor.setRGBAfromLogPackIntARGB(0xFF00FF80);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getBlue(),   0x8080);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA16b::maxChanVal);

  EXPECT_EQ(bColor.getC0(),     mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getC1(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getC2(),     0x8080);
  EXPECT_EQ(bColor.getC3(),     mjr::colorRGBA16b::maxChanVal);

  bColor.setRGBfromLogPackIntARGB(0x00FF00FF);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA16b::maxChanVal); // From before

  EXPECT_EQ(bColor.getC0(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getC1(),     mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(bColor.getC2(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(bColor.getC3(),     mjr::colorRGBA16b::maxChanVal); // From before

  eColor.setRGBfromLogPackIntARGB(0x00FF00FF);

  EXPECT_EQ(eColor.getRed(),    mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(eColor.getGreen(),  mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(eColor.getBlue(),   mjr::colorRGBA16b::maxChanVal);

  EXPECT_EQ(eColor.getC0(),     mjr::colorRGBA16b::maxChanVal);
  EXPECT_EQ(eColor.getC1(),     mjr::colorRGBA16b::minChanVal);
  EXPECT_EQ(eColor.getC2(),     mjr::colorRGBA16b::maxChanVal);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_argb_packed, unsigned8_unset) {

  // Make sure channels that should not be changed are not.

  mjr::colorRGBA8b bColor;
  mjr::color5c8b   cColor;

  bColor.setToWhite();
  bColor.setRGBfromLogPackIntARGB(0x00000000);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal);

  bColor.setToBlack();
  bColor.setRGBfromLogPackIntARGB(0xFFFFFFFF);

  EXPECT_EQ(bColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(bColor.getGreen(),  mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(bColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(bColor.getAlpha(),  mjr::colorRGBA8b::minChanVal);

  cColor.setToWhite();
  cColor.setRGBAfromLogPackIntARGB(0x00000000);

  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getAlpha(),  mjr::colorRGBA8b::minChanVal);
  EXPECT_EQ(cColor.getChan(4),  mjr::colorRGBA8b::maxChanVal);

  cColor.setToBlack();
  cColor.setRGBAfromLogPackIntARGB(0xFFFFFFFF);

  EXPECT_EQ(cColor.getRed(),    mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getGreen(),  mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getBlue(),   mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getAlpha(),  mjr::colorRGBA8b::maxChanVal);
  EXPECT_EQ(cColor.getChan(4),  mjr::colorRGBA8b::minChanVal);
}

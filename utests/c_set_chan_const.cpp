// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_set_chan_const.cpp
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
TEST(c_set_chan_const, color4c8b) {

  mjr::color4c8b aColor(123);
  EXPECT_EQ(aColor.getChan(0),  123);
  EXPECT_EQ(aColor.getChan(1),  123);
  EXPECT_EQ(aColor.getChan(2),  123);
  EXPECT_EQ(aColor.getChan(3),  123);

  mjr::color4c8b cColor(33, 44, 55);
  EXPECT_EQ(cColor.getChan(0),  33);
  EXPECT_EQ(cColor.getChan(1),  44);
  EXPECT_EQ(cColor.getChan(2),  55);
  EXPECT_EQ(cColor.getChan(3),  0);

  mjr::color4c8b dColor(66, 77, 88, 99);
  EXPECT_EQ(dColor.getChan(0),  66);
  EXPECT_EQ(dColor.getChan(1),  77);
  EXPECT_EQ(dColor.getChan(2),  88);
  EXPECT_EQ(dColor.getChan(3),  99);

  mjr::color4c8b eColor(dColor);
  EXPECT_EQ(eColor.getChan(0),  66);
  EXPECT_EQ(eColor.getChan(1),  77);
  EXPECT_EQ(eColor.getChan(2),  88);
  EXPECT_EQ(eColor.getChan(3),  99);

  mjr::color4c8b f0Color(mjr::color4c8b::cornerColorEnum::BLACK);
  mjr::color4c8b fRColor(mjr::color4c8b::cornerColorEnum::RED);
  mjr::color4c8b fGColor(mjr::color4c8b::cornerColorEnum::GREEN);
  mjr::color4c8b fBColor(mjr::color4c8b::cornerColorEnum::BLUE);
  mjr::color4c8b fYColor(mjr::color4c8b::cornerColorEnum::YELLOW);
  mjr::color4c8b fCColor(mjr::color4c8b::cornerColorEnum::CYAN);
  mjr::color4c8b fMColor(mjr::color4c8b::cornerColorEnum::MAGENTA);
  mjr::color4c8b f1Color(mjr::color4c8b::cornerColorEnum::WHITE);

  EXPECT_EQ(f0Color.getC0(),    0);
  EXPECT_EQ(fRColor.getC0(),    255);
  EXPECT_EQ(fGColor.getC0(),    0);
  EXPECT_EQ(fBColor.getC0(),    0);
  EXPECT_EQ(fYColor.getC0(),    255);
  EXPECT_EQ(fCColor.getC0(),    0);
  EXPECT_EQ(fMColor.getC0(),    255);
  EXPECT_EQ(f1Color.getC0(),    255);

  EXPECT_EQ(f0Color.getC1(),    0);
  EXPECT_EQ(fRColor.getC1(),    0);
  EXPECT_EQ(fGColor.getC1(),    255);
  EXPECT_EQ(fBColor.getC1(),    0);
  EXPECT_EQ(fYColor.getC1(),    255);
  EXPECT_EQ(fCColor.getC1(),    255);
  EXPECT_EQ(fMColor.getC1(),    0);
  EXPECT_EQ(f1Color.getC1(),    255);

  EXPECT_EQ(f0Color.getC2(),    0);
  EXPECT_EQ(fRColor.getC2(),    0);
  EXPECT_EQ(fGColor.getC2(),    0);
  EXPECT_EQ(fBColor.getC2(),    255);
  EXPECT_EQ(fYColor.getC2(),    0);
  EXPECT_EQ(fCColor.getC2(),    255);
  EXPECT_EQ(fMColor.getC2(),    255);
  EXPECT_EQ(f1Color.getC2(),    255);

  EXPECT_EQ(f0Color.getC3(),    0);
  EXPECT_EQ(fRColor.getC3(),    0); // primary
  EXPECT_EQ(fGColor.getC3(),    0); // primary
  EXPECT_EQ(fBColor.getC3(),    0); // primary
  EXPECT_EQ(fYColor.getC3(),    255); // secondary
  EXPECT_EQ(fCColor.getC3(),    255); // secondary
  EXPECT_EQ(fMColor.getC3(),    255); // secondary
  EXPECT_EQ(f1Color.getC3(),    255);

  // magic string -- corner with single character.

  mjr::color4c8b g0Color("0");
  mjr::color4c8b gRColor("R");
  mjr::color4c8b gGColor("G");
  mjr::color4c8b gBColor("B");
  mjr::color4c8b gYColor("Y");
  mjr::color4c8b gCColor("C");
  mjr::color4c8b gMColor("M");
  mjr::color4c8b g1Color("W");

  EXPECT_EQ(g0Color.getC0(),    0);
  EXPECT_EQ(gRColor.getC0(),    255);
  EXPECT_EQ(gGColor.getC0(),    0);
  EXPECT_EQ(gBColor.getC0(),    0);
  EXPECT_EQ(gYColor.getC0(),    255);
  EXPECT_EQ(gCColor.getC0(),    0);
  EXPECT_EQ(gMColor.getC0(),    255);
  EXPECT_EQ(g1Color.getC0(),    255);

  EXPECT_EQ(g0Color.getC1(),    0);
  EXPECT_EQ(gRColor.getC1(),    0);
  EXPECT_EQ(gGColor.getC1(),    255);
  EXPECT_EQ(gBColor.getC1(),    0);
  EXPECT_EQ(gYColor.getC1(),    255);
  EXPECT_EQ(gCColor.getC1(),    255);
  EXPECT_EQ(gMColor.getC1(),    0);
  EXPECT_EQ(g1Color.getC1(),    255);

  EXPECT_EQ(g0Color.getC2(),    0);
  EXPECT_EQ(gRColor.getC2(),    0);
  EXPECT_EQ(gGColor.getC2(),    0);
  EXPECT_EQ(gBColor.getC2(),    255);
  EXPECT_EQ(gYColor.getC2(),    0);
  EXPECT_EQ(gCColor.getC2(),    255);
  EXPECT_EQ(gMColor.getC2(),    255);
  EXPECT_EQ(g1Color.getC2(),    255);

  EXPECT_EQ(g0Color.getC3(),    0);
  EXPECT_EQ(gRColor.getC3(),    0); // primary
  EXPECT_EQ(gGColor.getC3(),    0); // primary
  EXPECT_EQ(gBColor.getC3(),    0); // primary
  EXPECT_EQ(gYColor.getC3(),    255); // secondary
  EXPECT_EQ(gCColor.getC3(),    255); // secondary
  EXPECT_EQ(gMColor.getC3(),    255); // secondary
  EXPECT_EQ(g1Color.getC3(),    255);

  // magic string -- corner with full name

  mjr::color4c8b h0Color("black");
  mjr::color4c8b hRColor("Red");
  mjr::color4c8b hGColor("GREEN");
  mjr::color4c8b hBColor("blue");
  mjr::color4c8b hYColor("YeLLoW");
  mjr::color4c8b hCColor("CYAN");
  mjr::color4c8b hMColor("MAGENTA");
  mjr::color4c8b h1Color("White");

  EXPECT_EQ(h0Color.getC0(),    0);
  EXPECT_EQ(hRColor.getC0(),    255);
  EXPECT_EQ(hGColor.getC0(),    0);
  EXPECT_EQ(hBColor.getC0(),    0);
  EXPECT_EQ(hYColor.getC0(),    255);
  EXPECT_EQ(hCColor.getC0(),    0);
  EXPECT_EQ(hMColor.getC0(),    255);
  EXPECT_EQ(h1Color.getC0(),    255);

  EXPECT_EQ(h0Color.getC1(),    0);
  EXPECT_EQ(hRColor.getC1(),    0);
  EXPECT_EQ(hGColor.getC1(),    255);
  EXPECT_EQ(hBColor.getC1(),    0);
  EXPECT_EQ(hYColor.getC1(),    255);
  EXPECT_EQ(hCColor.getC1(),    255);
  EXPECT_EQ(hMColor.getC1(),    0);
  EXPECT_EQ(h1Color.getC1(),    255);

  EXPECT_EQ(h0Color.getC2(),    0);
  EXPECT_EQ(hRColor.getC2(),    0);
  EXPECT_EQ(hGColor.getC2(),    0);
  EXPECT_EQ(hBColor.getC2(),    255);
  EXPECT_EQ(hYColor.getC2(),    0);
  EXPECT_EQ(hCColor.getC2(),    255);
  EXPECT_EQ(hMColor.getC2(),    255);
  EXPECT_EQ(h1Color.getC2(),    255);

  EXPECT_EQ(h0Color.getC3(),    0);
  EXPECT_EQ(hRColor.getC3(),    0); // primary
  EXPECT_EQ(hGColor.getC3(),    0); // primary
  EXPECT_EQ(hBColor.getC3(),    0); // primary
  EXPECT_EQ(hYColor.getC3(),    255); // secondary
  EXPECT_EQ(hCColor.getC3(),    255); // secondary
  EXPECT_EQ(hMColor.getC3(),    255); // secondary
  EXPECT_EQ(h1Color.getC3(),    255);

  mjr::color4c8b iColor("zoogo");   // unknown color => black
  EXPECT_EQ(iColor.getC0(),     0);
  EXPECT_EQ(iColor.getC1(),     0);
  EXPECT_EQ(iColor.getC2(),     0);
  EXPECT_EQ(iColor.getC3(),     0);

  mjr::color4c8b jColor("z");   // unknown color => black
  EXPECT_EQ(jColor.getC0(),     0);
  EXPECT_EQ(jColor.getC1(),     0);
  EXPECT_EQ(jColor.getC2(),     0);
  EXPECT_EQ(jColor.getC3(),     0);

  // magic string -- hex color strings

  mjr::color4c8b kColor("#aabbccdd");
  EXPECT_EQ(kColor.getC0(),     0xAA);
  EXPECT_EQ(kColor.getC1(),     0xBB);
  EXPECT_EQ(kColor.getC2(),     0xCC);
  EXPECT_EQ(kColor.getC3(),     0xDD);

  mjr::color4c8b lColor("#bbccdd");
  EXPECT_EQ(lColor.getC0(),     0xBB);
  EXPECT_EQ(lColor.getC1(),     0xCC);
  EXPECT_EQ(lColor.getC2(),     0xDD);
  EXPECT_EQ(lColor.getC3(),     0x0);

  mjr::color4c8b mColor("#aa");
  EXPECT_EQ(mColor.getC0(),     0xAA);
  EXPECT_EQ(mColor.getC1(),     0x0);
  EXPECT_EQ(mColor.getC2(),     0x0);
  EXPECT_EQ(mColor.getC3(),     0x0);

  mjr::color4c8b nColor("#a");
  EXPECT_EQ(nColor.getC0(),     0x0);
  EXPECT_EQ(nColor.getC1(),     0x0);
  EXPECT_EQ(nColor.getC2(),     0x0);
  EXPECT_EQ(nColor.getC3(),     0x0);

  // Init List

  mjr::color4c8b oColor({1, 2, 3, 4});
  EXPECT_EQ(oColor.getChan(0),  1);
  EXPECT_EQ(oColor.getChan(1),  2);
  EXPECT_EQ(oColor.getChan(2),  3);
  EXPECT_EQ(oColor.getChan(3),  4);

  mjr::color4c8b pColor({1, 2, 3});
  EXPECT_EQ(pColor.getChan(0),  1);
  EXPECT_EQ(pColor.getChan(1),  2);
  EXPECT_EQ(pColor.getChan(2),  3);
  EXPECT_EQ(pColor.getChan(3),  0); // unsp -> zero

  mjr::color4c8b qColor({1});
  EXPECT_EQ(qColor.getChan(0),  1);
  EXPECT_EQ(qColor.getChan(1),  0); // unsp -> zero
  EXPECT_EQ(qColor.getChan(2),  0); // unsp -> zero
  EXPECT_EQ(qColor.getChan(3),  0); // unsp -> zero

  mjr::color4c8b rColor({1, 2, 3, 4, 5, 6});
  EXPECT_EQ(rColor.getChan(0),  1);
  EXPECT_EQ(rColor.getChan(1),  2);
  EXPECT_EQ(rColor.getChan(2),  3);
  EXPECT_EQ(rColor.getChan(3),  4);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_const, color4c16b) {

  mjr::color4c16b aColor(123);
  EXPECT_EQ(aColor.getChan(0),  123);
  EXPECT_EQ(aColor.getChan(1),  123);
  EXPECT_EQ(aColor.getChan(2),  123);
  EXPECT_EQ(aColor.getChan(3),  123);

  mjr::color4c16b cColor(33, 44, 55);
  EXPECT_EQ(cColor.getChan(0),  33);
  EXPECT_EQ(cColor.getChan(1),  44);
  EXPECT_EQ(cColor.getChan(2),  55);
  EXPECT_EQ(cColor.getChan(3),  0);

  mjr::color4c16b dColor(66, 77, 88, 99);
  EXPECT_EQ(dColor.getChan(0),  66);
  EXPECT_EQ(dColor.getChan(1),  77);
  EXPECT_EQ(dColor.getChan(2),  88);
  EXPECT_EQ(dColor.getChan(3),  99);

  mjr::color4c16b eColor(dColor);
  EXPECT_EQ(eColor.getChan(0),  66);
  EXPECT_EQ(eColor.getChan(1),  77);
  EXPECT_EQ(eColor.getChan(2),  88);
  EXPECT_EQ(eColor.getChan(3),  99);

  mjr::color4c16b f0Color(mjr::color4c16b::cornerColorEnum::BLACK);
  mjr::color4c16b fRColor(mjr::color4c16b::cornerColorEnum::RED);
  mjr::color4c16b fGColor(mjr::color4c16b::cornerColorEnum::GREEN);
  mjr::color4c16b fBColor(mjr::color4c16b::cornerColorEnum::BLUE);
  mjr::color4c16b fYColor(mjr::color4c16b::cornerColorEnum::YELLOW);
  mjr::color4c16b fCColor(mjr::color4c16b::cornerColorEnum::CYAN);
  mjr::color4c16b fMColor(mjr::color4c16b::cornerColorEnum::MAGENTA);
  mjr::color4c16b f1Color(mjr::color4c16b::cornerColorEnum::WHITE);

  EXPECT_EQ(f0Color.getC0(),    0);
  EXPECT_EQ(fRColor.getC0(),    65535);
  EXPECT_EQ(fGColor.getC0(),    0);
  EXPECT_EQ(fBColor.getC0(),    0);
  EXPECT_EQ(fYColor.getC0(),    65535);
  EXPECT_EQ(fCColor.getC0(),    0);
  EXPECT_EQ(fMColor.getC0(),    65535);
  EXPECT_EQ(f1Color.getC0(),    65535);

  EXPECT_EQ(f0Color.getC1(),    0);
  EXPECT_EQ(fRColor.getC1(),    0);
  EXPECT_EQ(fGColor.getC1(),    65535);
  EXPECT_EQ(fBColor.getC1(),    0);
  EXPECT_EQ(fYColor.getC1(),    65535);
  EXPECT_EQ(fCColor.getC1(),    65535);
  EXPECT_EQ(fMColor.getC1(),    0);
  EXPECT_EQ(f1Color.getC1(),    65535);

  EXPECT_EQ(f0Color.getC2(),    0);
  EXPECT_EQ(fRColor.getC2(),    0);
  EXPECT_EQ(fGColor.getC2(),    0);
  EXPECT_EQ(fBColor.getC2(),    65535);
  EXPECT_EQ(fYColor.getC2(),    0);
  EXPECT_EQ(fCColor.getC2(),    65535);
  EXPECT_EQ(fMColor.getC2(),    65535);
  EXPECT_EQ(f1Color.getC2(),    65535);

  EXPECT_EQ(f0Color.getC3(),    0);
  EXPECT_EQ(fRColor.getC3(),    0); // primary
  EXPECT_EQ(fGColor.getC3(),    0); // primary
  EXPECT_EQ(fBColor.getC3(),    0); // primary
  EXPECT_EQ(fYColor.getC3(),    65535); // secondary
  EXPECT_EQ(fCColor.getC3(),    65535); // secondary
  EXPECT_EQ(fMColor.getC3(),    65535); // secondary
  EXPECT_EQ(f1Color.getC3(),    65535);

  // magic string -- corner with single character.

  mjr::color4c16b g0Color("0");
  mjr::color4c16b gRColor("R");
  mjr::color4c16b gGColor("G");
  mjr::color4c16b gBColor("B");
  mjr::color4c16b gYColor("Y");
  mjr::color4c16b gCColor("C");
  mjr::color4c16b gMColor("M");
  mjr::color4c16b g1Color("W");

  EXPECT_EQ(g0Color.getC0(),    0);
  EXPECT_EQ(gRColor.getC0(),    65535);
  EXPECT_EQ(gGColor.getC0(),    0);
  EXPECT_EQ(gBColor.getC0(),    0);
  EXPECT_EQ(gYColor.getC0(),    65535);
  EXPECT_EQ(gCColor.getC0(),    0);
  EXPECT_EQ(gMColor.getC0(),    65535);
  EXPECT_EQ(g1Color.getC0(),    65535);

  EXPECT_EQ(g0Color.getC1(),    0);
  EXPECT_EQ(gRColor.getC1(),    0);
  EXPECT_EQ(gGColor.getC1(),    65535);
  EXPECT_EQ(gBColor.getC1(),    0);
  EXPECT_EQ(gYColor.getC1(),    65535);
  EXPECT_EQ(gCColor.getC1(),    65535);
  EXPECT_EQ(gMColor.getC1(),    0);
  EXPECT_EQ(g1Color.getC1(),    65535);

  EXPECT_EQ(g0Color.getC2(),    0);
  EXPECT_EQ(gRColor.getC2(),    0);
  EXPECT_EQ(gGColor.getC2(),    0);
  EXPECT_EQ(gBColor.getC2(),    65535);
  EXPECT_EQ(gYColor.getC2(),    0);
  EXPECT_EQ(gCColor.getC2(),    65535);
  EXPECT_EQ(gMColor.getC2(),    65535);
  EXPECT_EQ(g1Color.getC2(),    65535);

  EXPECT_EQ(g0Color.getC3(),    0);
  EXPECT_EQ(gRColor.getC3(),    0); // primary
  EXPECT_EQ(gGColor.getC3(),    0); // primary
  EXPECT_EQ(gBColor.getC3(),    0); // primary
  EXPECT_EQ(gYColor.getC3(),    65535); // secondary
  EXPECT_EQ(gCColor.getC3(),    65535); // secondary
  EXPECT_EQ(gMColor.getC3(),    65535); // secondary
  EXPECT_EQ(g1Color.getC3(),    65535);

  // magic string -- corner with full name

  mjr::color4c16b h0Color("black");
  mjr::color4c16b hRColor("Red");
  mjr::color4c16b hGColor("GREEN");
  mjr::color4c16b hBColor("blue");
  mjr::color4c16b hYColor("YeLLoW");
  mjr::color4c16b hCColor("CYAN");
  mjr::color4c16b hMColor("MAGENTA");
  mjr::color4c16b h1Color("White");

  EXPECT_EQ(h0Color.getC0(),    0);
  EXPECT_EQ(hRColor.getC0(),    65535);
  EXPECT_EQ(hGColor.getC0(),    0);
  EXPECT_EQ(hBColor.getC0(),    0);
  EXPECT_EQ(hYColor.getC0(),    65535);
  EXPECT_EQ(hCColor.getC0(),    0);
  EXPECT_EQ(hMColor.getC0(),    65535);
  EXPECT_EQ(h1Color.getC0(),    65535);

  EXPECT_EQ(h0Color.getC1(),    0);
  EXPECT_EQ(hRColor.getC1(),    0);
  EXPECT_EQ(hGColor.getC1(),    65535);
  EXPECT_EQ(hBColor.getC1(),    0);
  EXPECT_EQ(hYColor.getC1(),    65535);
  EXPECT_EQ(hCColor.getC1(),    65535);
  EXPECT_EQ(hMColor.getC1(),    0);
  EXPECT_EQ(h1Color.getC1(),    65535);

  EXPECT_EQ(h0Color.getC2(),    0);
  EXPECT_EQ(hRColor.getC2(),    0);
  EXPECT_EQ(hGColor.getC2(),    0);
  EXPECT_EQ(hBColor.getC2(),    65535);
  EXPECT_EQ(hYColor.getC2(),    0);
  EXPECT_EQ(hCColor.getC2(),    65535);
  EXPECT_EQ(hMColor.getC2(),    65535);
  EXPECT_EQ(h1Color.getC2(),    65535);

  EXPECT_EQ(h0Color.getC3(),    0);
  EXPECT_EQ(hRColor.getC3(),    0); // primary
  EXPECT_EQ(hGColor.getC3(),    0); // primary
  EXPECT_EQ(hBColor.getC3(),    0); // primary
  EXPECT_EQ(hYColor.getC3(),    65535); // secondary
  EXPECT_EQ(hCColor.getC3(),    65535); // secondary
  EXPECT_EQ(hMColor.getC3(),    65535); // secondary
  EXPECT_EQ(h1Color.getC3(),    65535);

  mjr::color4c16b iColor("zoogo");   // unknown color => black
  EXPECT_EQ(iColor.getC0(),     0);
  EXPECT_EQ(iColor.getC1(),     0);
  EXPECT_EQ(iColor.getC2(),     0);
  EXPECT_EQ(iColor.getC3(),     0);

  mjr::color4c16b jColor("z");   // unknown color => black
  EXPECT_EQ(jColor.getC0(),     0);
  EXPECT_EQ(jColor.getC1(),     0);
  EXPECT_EQ(jColor.getC2(),     0);
  EXPECT_EQ(jColor.getC3(),     0);

  // magic string -- hex color string

  mjr::color4c16b kColor("#aaaabbbbccccdddd");
  EXPECT_EQ(kColor.getC0(),     0xAAAA);
  EXPECT_EQ(kColor.getC1(),     0xBBBB);
  EXPECT_EQ(kColor.getC2(),     0xCCCC);
  EXPECT_EQ(kColor.getC3(),     0xDDDD);

  mjr::color4c16b lColor("#bbbbccccdddd");
  EXPECT_EQ(lColor.getC0(),     0xBBBB);
  EXPECT_EQ(lColor.getC1(),     0xCCCC);
  EXPECT_EQ(lColor.getC2(),     0xDDDD);
  EXPECT_EQ(lColor.getC3(),     0x0);

  mjr::color4c16b mColor("#aaaa");
  EXPECT_EQ(mColor.getC0(),     0xAAAA);
  EXPECT_EQ(mColor.getC1(),     0x0);
  EXPECT_EQ(mColor.getC2(),     0x0);
  EXPECT_EQ(mColor.getC3(),     0x0);

  mjr::color4c16b nColor("#aaa");
  EXPECT_EQ(nColor.getC0(),     0x0);
  EXPECT_EQ(nColor.getC1(),     0x0);
  EXPECT_EQ(nColor.getC2(),     0x0);
  EXPECT_EQ(nColor.getC3(),     0x0);

  // Init List

  mjr::color4c16b oColor({1, 2, 3, 4});
  EXPECT_EQ(oColor.getChan(0),  1);
  EXPECT_EQ(oColor.getChan(1),  2);
  EXPECT_EQ(oColor.getChan(2),  3);
  EXPECT_EQ(oColor.getChan(3),  4);

  mjr::color4c16b pColor({1, 2, 3});              // size mismatch -> all chans to zero
  EXPECT_EQ(pColor.getChan(0),  1);
  EXPECT_EQ(pColor.getChan(1),  2);
  EXPECT_EQ(pColor.getChan(2),  3);
  EXPECT_EQ(pColor.getChan(3),  0);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(c_set_chan_const, color4c64F) {

  mjr::color4c64F aColor(0.25);
  EXPECT_NEAR(aColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(1),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(2),       0.25, 0.000001);
  EXPECT_NEAR(aColor.getChan(3),       0.25, 0.000001);

  mjr::color4c64F cColor(0.25, 0.50, 0.75);
  EXPECT_NEAR(cColor.getChan(0),       0.25, 0.000001);
  EXPECT_NEAR(cColor.getChan(1),       0.50, 0.000001);
  EXPECT_NEAR(cColor.getChan(2),       0.75, 0.000001);
  EXPECT_NEAR(cColor.getChan(3),       0.00, 0.000001);

  mjr::color4c64F dColor(1.00, 0.75, 0.50, 0.25);
  EXPECT_NEAR(dColor.getChan(0),       1.00, 0.000001);
  EXPECT_NEAR(dColor.getChan(1),       0.75, 0.000001);
  EXPECT_NEAR(dColor.getChan(2),       0.50, 0.000001);
  EXPECT_NEAR(dColor.getChan(3),       0.25, 0.000001);

  mjr::color4c64F eColor(dColor);
  EXPECT_NEAR(eColor.getChan(0),       1.00, 0.000001);
  EXPECT_NEAR(eColor.getChan(1),       0.75, 0.000001);
  EXPECT_NEAR(eColor.getChan(2),       0.50, 0.000001);
  EXPECT_NEAR(eColor.getChan(3),       0.25, 0.000001);

  mjr::color4c64F f0Color(mjr::color4c64F::cornerColorEnum::BLACK);
  mjr::color4c64F fRColor(mjr::color4c64F::cornerColorEnum::RED);
  mjr::color4c64F fGColor(mjr::color4c64F::cornerColorEnum::GREEN);
  mjr::color4c64F fBColor(mjr::color4c64F::cornerColorEnum::BLUE);
  mjr::color4c64F fYColor(mjr::color4c64F::cornerColorEnum::YELLOW);
  mjr::color4c64F fCColor(mjr::color4c64F::cornerColorEnum::CYAN);
  mjr::color4c64F fMColor(mjr::color4c64F::cornerColorEnum::MAGENTA);
  mjr::color4c64F f1Color(mjr::color4c64F::cornerColorEnum::WHITE);

  EXPECT_NEAR(f0Color.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(fGColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fBColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fYColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(fCColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(fMColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(f1Color.getC0(),  1.0, 0.000001);

  EXPECT_NEAR(f0Color.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(fGColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(fBColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(fYColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(fCColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(fMColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(f1Color.getC1(),  1.0, 0.000001);

  EXPECT_NEAR(f0Color.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fGColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fBColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(fYColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(fCColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(fMColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(f1Color.getC2(),  1.0, 0.000001);

  EXPECT_NEAR(f0Color.getC3(),  0.0, 0.000001);
  EXPECT_NEAR(fRColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(fGColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(fBColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(fYColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(fCColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(fMColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(f1Color.getC3(),  1.0, 0.000001);

  // magic string -- corner with single character.

  mjr::color4c64F g0Color("0");
  mjr::color4c64F gRColor("R");
  mjr::color4c64F gGColor("G");
  mjr::color4c64F gBColor("B");
  mjr::color4c64F gYColor("Y");
  mjr::color4c64F gCColor("C");
  mjr::color4c64F gMColor("M");
  mjr::color4c64F g1Color("W");

  EXPECT_NEAR(g0Color.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(gGColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gBColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gYColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(gCColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(gMColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(g1Color.getC0(),  1.0, 0.000001);

  EXPECT_NEAR(g0Color.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(gGColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(gBColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(gYColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(gCColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(gMColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(g1Color.getC1(),  1.0, 0.000001);

  EXPECT_NEAR(g0Color.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gGColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gBColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(gYColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(gCColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(gMColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(g1Color.getC2(),  1.0, 0.000001);

  EXPECT_NEAR(g0Color.getC3(),  0.0, 0.000001);
  EXPECT_NEAR(gRColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(gGColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(gBColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(gYColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(gCColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(gMColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(g1Color.getC3(),  1.0, 0.000001);

  // magic string -- corner with full name

  mjr::color4c64F h0Color("black");
  mjr::color4c64F hRColor("Red");
  mjr::color4c64F hGColor("GREEN");
  mjr::color4c64F hBColor("blue");
  mjr::color4c64F hYColor("YeLLoW");
  mjr::color4c64F hCColor("CYAN");
  mjr::color4c64F hMColor("MAGENTA");
  mjr::color4c64F h1Color("White");

  EXPECT_NEAR(h0Color.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(hGColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hBColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hYColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(hCColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(hMColor.getC0(),  1.0, 0.000001);
  EXPECT_NEAR(h1Color.getC0(),  1.0, 0.000001);

  EXPECT_NEAR(h0Color.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(hGColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(hBColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(hYColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(hCColor.getC1(),  1.0, 0.000001);
  EXPECT_NEAR(hMColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(h1Color.getC1(),  1.0, 0.000001);

  EXPECT_NEAR(h0Color.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hGColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hBColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(hYColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(hCColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(hMColor.getC2(),  1.0, 0.000001);
  EXPECT_NEAR(h1Color.getC2(),  1.0, 0.000001);

  EXPECT_NEAR(h0Color.getC3(),  0.0, 0.000001);
  EXPECT_NEAR(hRColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(hGColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(hBColor.getC3(),  0.0, 0.000001); // primary
  EXPECT_NEAR(hYColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(hCColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(hMColor.getC3(),  1.0, 0.000001); // secondary
  EXPECT_NEAR(h1Color.getC3(),  1.0, 0.000001);

  mjr::color4c64F iColor("zoogo");   // unknown color => black
  EXPECT_NEAR(iColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(iColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(iColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(iColor.getC3(),  0.0, 0.000001);

  mjr::color4c64F jColor("z");   // unknown color => black
  EXPECT_NEAR(jColor.getC0(),  0.0, 0.000001);
  EXPECT_NEAR(jColor.getC1(),  0.0, 0.000001);
  EXPECT_NEAR(jColor.getC2(),  0.0, 0.000001);
  EXPECT_NEAR(jColor.getC3(),  0.0, 0.000001);

  // magic string -- hex color string

  mjr::color4c64F kColor("#aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddddddddd");
  EXPECT_NEAR(kColor.getC0(),  0.66666666666, 0.000001);
  EXPECT_NEAR(kColor.getC1(),  0.73333333333, 0.000001);
  EXPECT_NEAR(kColor.getC2(),  0.80000000000, 0.000001);
  EXPECT_NEAR(kColor.getC3(),  0.86666666666, 0.000001);

  // Init List

  mjr::color4c64F oColor({1, 2, 3, 4});
  EXPECT_NEAR(oColor.getChan(0),  1, 0.000001);
  EXPECT_NEAR(oColor.getChan(1),  2, 0.000001);
  EXPECT_NEAR(oColor.getChan(2),  3, 0.000001);
  EXPECT_NEAR(oColor.getChan(3),  4, 0.000001);

  mjr::color4c64F pColor({1, 2, 3});              // size mismatch -> all chans to zero
  EXPECT_NEAR(pColor.getChan(0),  1, 0.000001);
  EXPECT_NEAR(pColor.getChan(1),  2, 0.000001);
  EXPECT_NEAR(pColor.getChan(2),  3, 0.000001);
  EXPECT_NEAR(pColor.getChan(3),  0, 0.000001);
 }

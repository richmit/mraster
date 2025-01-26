// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_constructor.cpp
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
TEST(c_constructor, Comprehensive) {
  // The simplicity of these functions doesn't warrant complex testing.  If the constructors & set/get work on a simple test case, then they probably work.

  mjr::color8c16b aColor {mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal};
  mjr::color8c16b bColor {mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal};

  EXPECT_TRUE(aColor.getColConRGB_byte().isEqual( mjr::color8c16b::colConRGBbyte {   0, 255,   0                          }));
  EXPECT_TRUE(bColor.getColConRGB_byte().isEqual( mjr::color8c16b::colConRGBbyte { 255,   0, 255                          }));
  EXPECT_TRUE(aColor.getColConRGBA_byte().isEqual(mjr::color8c16b::colConRGBAbyte{   0, 255,   0, 255                     }));
  EXPECT_TRUE(bColor.getColConRGBA_byte().isEqual(mjr::color8c16b::colConRGBAbyte{ 255,   0, 255,   0                     }));
  EXPECT_TRUE(aColor.getColConRGB_dbl().isEqual(  mjr::color8c16b::colConRGBdbl  { 0.0, 1.0, 0.0                          }));
  EXPECT_TRUE(bColor.getColConRGB_dbl().isEqual(  mjr::color8c16b::colConRGBdbl  { 1.0, 0.0, 1.0                          }));
  EXPECT_TRUE(aColor.getColConRGBA_dbl().isEqual( mjr::color8c16b::colConRGBAdbl { 0.0, 1.0, 0.0, 1.0                     }));
  EXPECT_TRUE(bColor.getColConRGBA_dbl().isEqual( mjr::color8c16b::colConRGBAdbl { 1.0, 0.0, 1.0, 0.0                     }));
  EXPECT_TRUE(aColor.getColCon_byte().isEqual(    mjr::color8c16b::colConALLbyte {   0, 255,   0, 255,   0, 255,   0, 255 }));
  EXPECT_TRUE(bColor.getColCon_byte().isEqual(    mjr::color8c16b::colConALLbyte { 255,   0, 255,   0, 255,   0, 255,   0 }));
  EXPECT_TRUE(aColor.getColCon_dbl().isEqual(     mjr::color8c16b::colConALLdbl  { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 }));
  EXPECT_TRUE(bColor.getColCon_dbl().isEqual(     mjr::color8c16b::colConALLdbl  { 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0 }));

  mjr::color8c16b cColor;
  mjr::color8c16b dColor;

  mjr::color8c16b a3nColor {mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal};
  mjr::color8c16b b3xColor {mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal};
  mjr::color8c16b a4nColor {mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::minChanVal};
  mjr::color8c16b b4xColor {mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::minChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal, mjr::colorRGBA16b::maxChanVal};

  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a3nColor.isEqual(cColor.setChansRGB_byte( mjr::color8c16b::colConRGBbyte {   0, 255,   0                          })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b3xColor.isEqual(dColor.setChansRGB_byte( mjr::color8c16b::colConRGBbyte { 255,   0, 255                          })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a4nColor.isEqual(cColor.setChansRGBA_byte(mjr::color8c16b::colConRGBAbyte{   0, 255,   0, 255                     })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b4xColor.isEqual(dColor.setChansRGBA_byte(mjr::color8c16b::colConRGBAbyte{ 255,   0, 255,   0                     })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a3nColor.isEqual(cColor.setChansRGB_dbl(  mjr::color8c16b::colConRGBdbl  { 0.0, 1.0, 0.0                          })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b3xColor.isEqual(dColor.setChansRGB_dbl(  mjr::color8c16b::colConRGBdbl  { 1.0, 0.0, 1.0                          })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(a4nColor.isEqual(cColor.setChansRGBA_dbl( mjr::color8c16b::colConRGBAdbl { 0.0, 1.0, 0.0, 1.0                     })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(b4xColor.isEqual(dColor.setChansRGBA_dbl( mjr::color8c16b::colConRGBAdbl { 1.0, 0.0, 1.0, 0.0                     })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(aColor.isEqual(cColor.setChans_byte(      mjr::color8c16b::colConALLbyte {   0, 255,   0, 255,   0, 255,   0, 255 })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(bColor.isEqual(dColor.setChans_byte(      mjr::color8c16b::colConALLbyte { 255,   0, 255,   0, 255,   0, 255,   0 })));
  cColor.setToCorner(mjr::color8c16b::cornerColorEnum::BLACK);
  EXPECT_TRUE(aColor.isEqual(cColor.setChans_dbl(       mjr::color8c16b::colConALLdbl  { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0 })));
  dColor.setToCorner(mjr::color8c16b::cornerColorEnum::WHITE);
  EXPECT_TRUE(bColor.isEqual(dColor.setChans_dbl(       mjr::color8c16b::colConALLdbl  { 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0 })));
}

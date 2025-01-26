// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      c_comp_bestChan.cpp
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
TEST(c_comp_bestChan, unsigned8) {
  mjr::color1c8b aColor;
  mjr::color2c8b bColor;
  mjr::color3c8b cColor;
  mjr::color4c8b dColor;
  mjr::color8c8b eColor;

  EXPECT_EQ(aColor.bestRedChan(),     0);
  EXPECT_EQ(bColor.bestRedChan(),     0);
  EXPECT_EQ(cColor.bestRedChan(),     0);
  EXPECT_EQ(dColor.bestRedChan(),     0);
  EXPECT_EQ(eColor.bestRedChan(),     0);

  EXPECT_EQ(aColor.bestGreenChan(),   0);
  EXPECT_EQ(bColor.bestGreenChan(),   1);
  EXPECT_EQ(cColor.bestGreenChan(),   1);
  EXPECT_EQ(dColor.bestGreenChan(),   1);
  EXPECT_EQ(eColor.bestGreenChan(),   1);

  EXPECT_EQ(aColor.bestBlueChan(),    0);
  EXPECT_EQ(bColor.bestBlueChan(),   -1);
  EXPECT_EQ(cColor.bestBlueChan(),    2);
  EXPECT_EQ(dColor.bestBlueChan(),    2);
  EXPECT_EQ(eColor.bestBlueChan(),    2);

  EXPECT_EQ(aColor.bestAlphaChan(),  -1);
  EXPECT_EQ(bColor.bestAlphaChan(),  -1);
  EXPECT_EQ(cColor.bestAlphaChan(),  -1);
  EXPECT_EQ(dColor.bestAlphaChan(),   3);
  EXPECT_EQ(eColor.bestAlphaChan(),   3);
}

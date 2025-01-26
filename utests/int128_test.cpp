// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      int128_test.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-26
 @brief     Unit tests for basic color types on ia64 with GCC.@EOL
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

#ifdef MJR_HAVE_128_BIT_TYPES
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color1c8b) {
  EXPECT_EQ(mjr::color1c8b::bitsPerChan,     8                     );
  EXPECT_EQ(mjr::color1c8b::bitsPerPixel,    8                     );
  EXPECT_EQ(mjr::color1c8b::chanIsInt,       true                  );
  EXPECT_EQ(mjr::color1c8b::chanIsUnsigned,  true                  );
  EXPECT_EQ(mjr::color1c8b::chanIsByte,      true                  );
  EXPECT_EQ(mjr::color1c8b::chanIsDouble,    false                 );
  EXPECT_EQ(mjr::color1c8b::goodMask,        true                  );
  EXPECT_EQ(mjr::color1c8b::goodArithD,      true                  );
  EXPECT_EQ(mjr::color1c8b::goodArithSP,     true                  );
  EXPECT_EQ(mjr::color1c8b::goodArithSDP,    true                  );
  EXPECT_EQ(mjr::color1c8b::goodArithFlt,    true                  );
  EXPECT_EQ(mjr::color1c8b::goodArithLog,    true                  );
  EXPECT_EQ(mjr::color1c8b::sizeOfColor,     1                     );
  EXPECT_EQ(mjr::color1c8b::ptrIsSmaller,    false                 );
  EXPECT_EQ(mjr::color1c8b::maxChanVal,      255                   );
  EXPECT_EQ(mjr::color1c8b::minChanVal,      0                     );
  EXPECT_EQ(mjr::color1c8b::meanChanVal,     127                   );
  EXPECT_EQ(mjr::color1c8b::maskAllOne,      0xffu                 );
  EXPECT_EQ(mjr::color1c8b::maskAllZero,     0x00u                 );
  EXPECT_EQ(mjr::color1c8b::channelCount,    1                     );

  EXPECT_TRUE((std::is_same<mjr::color1c8b::colorType,            mjr::color1c8b          >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::colorPtrType,         mjr::color1c8b*         >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color1c8b::colorRefType,         mjr::color1c8b&         >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::colorCRefType,        mjr::color1c8b const&   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::channelType,          uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::maskType,             uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::channelArithDType,    int16_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::channelArithSPType,   uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::channelArithSDPType,  int32_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::channelArithFltType,  float                   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::channelArithLogType,  uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csIntType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::colorArgType,         mjr::color1c8b          >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color2c8b) {
  EXPECT_EQ(mjr::color2c8b::bitsPerChan,     8                     );
  EXPECT_EQ(mjr::color2c8b::bitsPerPixel,    16                    );
  EXPECT_EQ(mjr::color2c8b::chanIsInt,       true                  );
  EXPECT_EQ(mjr::color2c8b::chanIsUnsigned,  true                  );
  EXPECT_EQ(mjr::color2c8b::chanIsByte,      true                  );
  EXPECT_EQ(mjr::color2c8b::chanIsDouble,    false                 );
  EXPECT_EQ(mjr::color2c8b::goodMask,        true                  );
  EXPECT_EQ(mjr::color2c8b::goodArithD,      true                  );
  EXPECT_EQ(mjr::color2c8b::goodArithSP,     true                  );
  EXPECT_EQ(mjr::color2c8b::goodArithSDP,    true                  );
  EXPECT_EQ(mjr::color2c8b::goodArithFlt,    true                  );
  EXPECT_EQ(mjr::color2c8b::goodArithLog,    true                  );
  EXPECT_EQ(mjr::color2c8b::sizeOfColor,     2                     );
  EXPECT_EQ(mjr::color2c8b::ptrIsSmaller,    false                 );
  EXPECT_EQ(mjr::color2c8b::maxChanVal,      255                   );
  EXPECT_EQ(mjr::color2c8b::minChanVal,      0                     );
  EXPECT_EQ(mjr::color2c8b::meanChanVal,     127                   );
  EXPECT_EQ(mjr::color2c8b::maskAllOne,      0xffffu               );
  EXPECT_EQ(mjr::color2c8b::maskAllZero,     0x0000u               );
  EXPECT_EQ(mjr::color2c8b::channelCount,    2                     );

  EXPECT_TRUE((std::is_same<mjr::color2c8b::colorType,            mjr::color2c8b          >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::colorPtrType,         mjr::color2c8b*         >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color2c8b::colorRefType,         mjr::color2c8b&         >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::colorCRefType,        mjr::color2c8b const&   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::channelType,          uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::maskType,             uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::channelArithDType,    int16_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::channelArithSPType,   uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::channelArithSDPType,  int32_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::channelArithFltType,  float                   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::channelArithLogType,  uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::csIntType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c8b::colorArgType,         mjr::color2c8b          >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color3c8b) {
  EXPECT_EQ(mjr::color3c8b::bitsPerChan,     8                     );
  EXPECT_EQ(mjr::color3c8b::bitsPerPixel,    24                    );
  EXPECT_EQ(mjr::color3c8b::chanIsInt,       true                  );
  EXPECT_EQ(mjr::color3c8b::chanIsUnsigned,  true                  );
  EXPECT_EQ(mjr::color3c8b::chanIsByte,      true                  );
  EXPECT_EQ(mjr::color3c8b::chanIsDouble,    false                 );
  EXPECT_EQ(mjr::color3c8b::goodMask,        true                  );
  EXPECT_EQ(mjr::color3c8b::goodArithD,      true                  );
  EXPECT_EQ(mjr::color3c8b::goodArithSP,     true                  );
  EXPECT_EQ(mjr::color3c8b::goodArithSDP,    true                  );
  EXPECT_EQ(mjr::color3c8b::goodArithFlt,    true                  );
  EXPECT_EQ(mjr::color3c8b::goodArithLog,    true                  );
  EXPECT_EQ(mjr::color3c8b::sizeOfColor,     4                     );
  EXPECT_EQ(mjr::color3c8b::ptrIsSmaller,    false                 );
  EXPECT_EQ(mjr::color3c8b::maxChanVal,      255                   );
  EXPECT_EQ(mjr::color3c8b::minChanVal,      0                     );
  EXPECT_EQ(mjr::color3c8b::meanChanVal,     127                   );
  EXPECT_EQ(mjr::color3c8b::maskAllOne,      0xffffffffu           );
  EXPECT_EQ(mjr::color3c8b::maskAllZero,     0x00000000u           );
  EXPECT_EQ(mjr::color3c8b::channelCount,    3                     );

  EXPECT_TRUE((std::is_same<mjr::color3c8b::colorType,            mjr::color3c8b          >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::colorPtrType,         mjr::color3c8b*         >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color3c8b::colorRefType,         mjr::color3c8b&         >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::colorCRefType,        mjr::color3c8b const&   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::channelType,          uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::maskType,             uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::channelArithDType,    int16_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::channelArithSPType,   uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::channelArithSDPType,  int32_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::channelArithFltType,  float                   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::channelArithLogType,  uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::csIntType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c8b::colorArgType,         mjr::color3c8b          >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color4c8b) {
  EXPECT_EQ(mjr::color4c8b::bitsPerChan,     8                     );
  EXPECT_EQ(mjr::color4c8b::bitsPerPixel,    32                    );
  EXPECT_EQ(mjr::color4c8b::chanIsInt,       true                  );
  EXPECT_EQ(mjr::color4c8b::chanIsUnsigned,  true                  );
  EXPECT_EQ(mjr::color4c8b::chanIsByte,      true                  );
  EXPECT_EQ(mjr::color4c8b::chanIsDouble,    false                 );
  EXPECT_EQ(mjr::color4c8b::goodMask,        true                  );
  EXPECT_EQ(mjr::color4c8b::goodArithD,      true                  );
  EXPECT_EQ(mjr::color4c8b::goodArithSP,     true                  );
  EXPECT_EQ(mjr::color4c8b::goodArithSDP,    true                  );
  EXPECT_EQ(mjr::color4c8b::goodArithFlt,    true                  );
  EXPECT_EQ(mjr::color4c8b::goodArithLog,    true                  );
  EXPECT_EQ(mjr::color4c8b::sizeOfColor,     4                     );
  EXPECT_EQ(mjr::color4c8b::ptrIsSmaller,    false                 );
  EXPECT_EQ(mjr::color4c8b::maxChanVal,      255                   );
  EXPECT_EQ(mjr::color4c8b::minChanVal,      0                     );
  EXPECT_EQ(mjr::color4c8b::meanChanVal,     127                   );
  EXPECT_EQ(mjr::color4c8b::maskAllOne,      0xffffffffu           );
  EXPECT_EQ(mjr::color4c8b::maskAllZero,     0x00000000u           );
  EXPECT_EQ(mjr::color4c8b::channelCount,    4                     );

  EXPECT_TRUE((std::is_same<mjr::color4c8b::colorType,            mjr::color4c8b          >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::colorPtrType,         mjr::color4c8b*         >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color4c8b::colorRefType,         mjr::color4c8b&         >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::colorCRefType,        mjr::color4c8b const&   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::channelType,          uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::maskType,             uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::channelArithDType,    int16_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::channelArithSPType,   uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::channelArithSDPType,  int32_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::channelArithFltType,  float                   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::channelArithLogType,  uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::csIntType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color4c8b::colorArgType,         mjr::color4c8b          >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color5c8b) {
  EXPECT_EQ(mjr::color5c8b::bitsPerChan,     8                     );
  EXPECT_EQ(mjr::color5c8b::bitsPerPixel,    40                    );
  EXPECT_EQ(mjr::color5c8b::chanIsInt,       true                  );
  EXPECT_EQ(mjr::color5c8b::chanIsUnsigned,  true                  );
  EXPECT_EQ(mjr::color5c8b::chanIsByte,      true                  );
  EXPECT_EQ(mjr::color5c8b::chanIsDouble,    false                 );
  EXPECT_EQ(mjr::color5c8b::goodMask,        false                 );
  EXPECT_EQ(mjr::color5c8b::goodArithD,      true                  );
  EXPECT_EQ(mjr::color5c8b::goodArithSP,     true                  );
  EXPECT_EQ(mjr::color5c8b::goodArithSDP,    true                  );
  EXPECT_EQ(mjr::color5c8b::goodArithFlt,    true                  );
  EXPECT_EQ(mjr::color5c8b::goodArithLog,    true                  );
  EXPECT_EQ(mjr::color5c8b::sizeOfColor,     5                     );
  EXPECT_EQ(mjr::color5c8b::ptrIsSmaller,    false                 );
  EXPECT_EQ(mjr::color5c8b::maxChanVal,      255                   );
  EXPECT_EQ(mjr::color5c8b::minChanVal,      0                     );
  EXPECT_EQ(mjr::color5c8b::meanChanVal,     127                   );
  EXPECT_EQ(mjr::color5c8b::maskAllOne,      0xffu                 );
  EXPECT_EQ(mjr::color5c8b::maskAllZero,     0x00u                 );
  EXPECT_EQ(mjr::color5c8b::channelCount,    5                     );

  EXPECT_TRUE((std::is_same<mjr::color5c8b::colorType,            mjr::color5c8b          >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::colorPtrType,         mjr::color5c8b*         >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color5c8b::colorRefType,         mjr::color5c8b&         >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::colorCRefType,        mjr::color5c8b const&   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::channelType,          uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::maskType,             uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::channelArithDType,    int16_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::channelArithSPType,   uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::channelArithSDPType,  int32_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::channelArithFltType,  float                   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::channelArithLogType,  uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::csIntType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color5c8b::colorArgType,         mjr::color5c8b          >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color6c8b) {
  EXPECT_EQ(mjr::color6c8b::bitsPerChan,     8                     );
  EXPECT_EQ(mjr::color6c8b::bitsPerPixel,    6*8                   );
  EXPECT_EQ(mjr::color6c8b::chanIsInt,       true                  );
  EXPECT_EQ(mjr::color6c8b::chanIsUnsigned,  true                  );
  EXPECT_EQ(mjr::color6c8b::chanIsByte,      true                  );
  EXPECT_EQ(mjr::color6c8b::chanIsDouble,    false                 );
  EXPECT_EQ(mjr::color6c8b::goodMask,        true                  );
  EXPECT_EQ(mjr::color6c8b::goodArithD,      true                  );
  EXPECT_EQ(mjr::color6c8b::goodArithSP,     true                  );
  EXPECT_EQ(mjr::color6c8b::goodArithSDP,    true                  );
  EXPECT_EQ(mjr::color6c8b::goodArithFlt,    true                  );
  EXPECT_EQ(mjr::color6c8b::goodArithLog,    true                  );
  EXPECT_EQ(mjr::color6c8b::sizeOfColor,     8                     );
  EXPECT_EQ(mjr::color6c8b::ptrIsSmaller,    false                 );
  EXPECT_EQ(mjr::color6c8b::maxChanVal,      255                   );
  EXPECT_EQ(mjr::color6c8b::minChanVal,      0                     );
  EXPECT_EQ(mjr::color6c8b::meanChanVal,     127                   );
  EXPECT_EQ(mjr::color6c8b::maskAllOne,      0xffffffffffffffffu   );
  EXPECT_EQ(mjr::color6c8b::maskAllZero,     0x0000000000000000u   );
  EXPECT_EQ(mjr::color6c8b::channelCount,    6                     );

  EXPECT_TRUE((std::is_same<mjr::color6c8b::colorType,            mjr::color6c8b          >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::colorPtrType,         mjr::color6c8b*         >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color6c8b::colorRefType,         mjr::color6c8b&         >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::colorCRefType,        mjr::color6c8b const&   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::channelType,          uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::maskType,             uint64_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::channelArithDType,    int16_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::channelArithSPType,   uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::channelArithSDPType,  int32_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::channelArithFltType,  float                   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::channelArithLogType,  uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::csIntType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color6c8b::colorArgType,         mjr::color6c8b          >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color8c8b) {
  EXPECT_EQ(mjr::color8c8b::bitsPerChan,     8                     );
  EXPECT_EQ(mjr::color8c8b::bitsPerPixel,    64                    );
  EXPECT_EQ(mjr::color8c8b::chanIsInt,       true                  );
  EXPECT_EQ(mjr::color8c8b::chanIsUnsigned,  true                  );
  EXPECT_EQ(mjr::color8c8b::chanIsByte,      true                  );
  EXPECT_EQ(mjr::color8c8b::chanIsDouble,    false                 );
  EXPECT_EQ(mjr::color8c8b::goodMask,        true                  );
  EXPECT_EQ(mjr::color8c8b::goodArithD,      true                  );
  EXPECT_EQ(mjr::color8c8b::goodArithSP,     true                  );
  EXPECT_EQ(mjr::color8c8b::goodArithSDP,    true                  );
  EXPECT_EQ(mjr::color8c8b::goodArithFlt,    true                  );
  EXPECT_EQ(mjr::color8c8b::goodArithLog,    true                  );
  EXPECT_EQ(mjr::color8c8b::sizeOfColor,     8                     );
  EXPECT_EQ(mjr::color8c8b::ptrIsSmaller,    false                 );
  EXPECT_EQ(mjr::color8c8b::maxChanVal,      255                   );
  EXPECT_EQ(mjr::color8c8b::minChanVal,      0                     );
  EXPECT_EQ(mjr::color8c8b::meanChanVal,     127                   );
  EXPECT_EQ(mjr::color8c8b::maskAllOne,      0xffffffffffffffffu   );
  EXPECT_EQ(mjr::color8c8b::maskAllZero,     0x0000000000000000u   );
  EXPECT_EQ(mjr::color8c8b::channelCount,    8                     );

  EXPECT_TRUE((std::is_same<mjr::color8c8b::colorType,            mjr::color8c8b          >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::colorPtrType,         mjr::color8c8b*         >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color8c8b::colorRefType,         mjr::color8c8b&         >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::colorCRefType,        mjr::color8c8b const&   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::channelType,          uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::maskType,             uint64_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::channelArithDType,    int16_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::channelArithSPType,   uint16_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::channelArithSDPType,  int32_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::channelArithFltType,  float                   >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::channelArithLogType,  uint8_t                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::csIntType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  EXPECT_TRUE((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color8c8b::colorArgType,         mjr::color8c8b          >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color3c16b) {
  EXPECT_EQ(mjr::color3c16b::bitsPerChan,     16                   );
  EXPECT_EQ(mjr::color3c16b::bitsPerPixel,    48                   );
  EXPECT_EQ(mjr::color3c16b::chanIsInt,       true                 );
  EXPECT_EQ(mjr::color3c16b::chanIsUnsigned,  true                 );
  EXPECT_EQ(mjr::color3c16b::chanIsByte,      false                );
  EXPECT_EQ(mjr::color3c16b::chanIsDouble,    false                );
  EXPECT_EQ(mjr::color3c16b::goodMask,        true                 );
  EXPECT_EQ(mjr::color3c16b::goodArithD,      true                 );
  EXPECT_EQ(mjr::color3c16b::goodArithSP,     true                 );
  EXPECT_EQ(mjr::color3c16b::goodArithSDP,    true                 );
  EXPECT_EQ(mjr::color3c16b::goodArithFlt,    true                 );
  EXPECT_EQ(mjr::color3c16b::goodArithLog,    true                 );
  EXPECT_EQ(mjr::color3c16b::sizeOfColor,     8                    );
  EXPECT_EQ(mjr::color3c16b::ptrIsSmaller,    false                );
  EXPECT_EQ(mjr::color3c16b::maxChanVal,      65535                );
  EXPECT_EQ(mjr::color3c16b::minChanVal,      0                    );
  EXPECT_EQ(mjr::color3c16b::meanChanVal,     32767                );
  EXPECT_EQ(mjr::color3c16b::maskAllOne,      0xffffffffffffffffu  );
  EXPECT_EQ(mjr::color3c16b::maskAllZero,     0x0000000000000000u  );
  EXPECT_EQ(mjr::color3c16b::channelCount,    3                    );

  EXPECT_TRUE((std::is_same<mjr::color3c16b::colorType,            mjr::color3c16b        >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::colorPtrType,         mjr::color3c16b*       >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color3c16b::colorRefType,         mjr::color3c16b&       >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::colorCRefType,        mjr::color3c16b const& >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::channelType,          uint16_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::maskType,             uint64_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::channelArithDType,    int32_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::channelArithSPType,   uint32_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::channelArithSDPType,  int64_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::channelArithFltType,  float                  >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::channelArithLogType,  uint16_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::csIntType,            uint32_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::csFltType,            double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::csNatType,            uint32_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c16b::colorArgType,         mjr::color3c16b        >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color2c32b) {
  EXPECT_EQ(mjr::color2c32b::bitsPerChan,     32                   );
  EXPECT_EQ(mjr::color2c32b::bitsPerPixel,    64                   );
  EXPECT_EQ(mjr::color2c32b::chanIsInt,       true                 );
  EXPECT_EQ(mjr::color2c32b::chanIsUnsigned,  true                 );
  EXPECT_EQ(mjr::color2c32b::chanIsByte,      false                );
  EXPECT_EQ(mjr::color2c32b::chanIsDouble,    false                );
  EXPECT_EQ(mjr::color2c32b::goodMask,        true                 );
  EXPECT_EQ(mjr::color2c32b::goodArithD,      true                 );
  EXPECT_EQ(mjr::color2c32b::goodArithSP,     true                 );
  EXPECT_EQ(mjr::color2c32b::goodArithSDP,    true                 );
  EXPECT_EQ(mjr::color2c32b::goodArithFlt,    true                 );
  EXPECT_EQ(mjr::color2c32b::goodArithLog,    true                 );
  EXPECT_EQ(mjr::color2c32b::sizeOfColor,     8                    );
  EXPECT_EQ(mjr::color2c32b::ptrIsSmaller,    false                );
  EXPECT_EQ(mjr::color2c32b::maxChanVal,      4294967295u          );
  EXPECT_EQ(mjr::color2c32b::minChanVal,      0                    );
  EXPECT_EQ(mjr::color2c32b::meanChanVal,     2147483647           );
  EXPECT_EQ(mjr::color2c32b::maskAllOne,      0xffffffffffffffffu  );
  EXPECT_EQ(mjr::color2c32b::maskAllZero,     0x0000000000000000u  );
  EXPECT_EQ(mjr::color2c32b::channelCount,    2                    );

  EXPECT_TRUE((std::is_same<mjr::color2c32b::colorType,            mjr::color2c32b        >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::colorPtrType,         mjr::color2c32b*       >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color2c32b::colorRefType,         mjr::color2c32b&       >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::colorCRefType,        mjr::color2c32b const& >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::channelType,          uint32_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::maskType,             uint64_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::channelArithDType,    int64_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::channelArithSPType,   uint64_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::channelArithSDPType,  mjr_intBiggest_t       >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::channelArithFltType,  double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::channelArithLogType,  uint32_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::csIntType,            uint64_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::csFltType,            double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::csNatType,            uint64_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color2c32b::colorArgType,         mjr::color2c32b        >::value ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(int128_test, color3c64F) {
  EXPECT_EQ(mjr::color3c64F::bitsPerChan,     64                   );
  EXPECT_EQ(mjr::color3c64F::bitsPerPixel,    192                  );
  EXPECT_EQ(mjr::color3c64F::chanIsInt,       false                );
  EXPECT_EQ(mjr::color3c64F::chanIsUnsigned,  false                );
  EXPECT_EQ(mjr::color3c64F::chanIsByte,      false                );
  EXPECT_EQ(mjr::color3c64F::chanIsDouble,    true                 );
  EXPECT_EQ(mjr::color3c64F::goodMask,        false                );
  EXPECT_EQ(mjr::color3c64F::goodArithD,      true                 );
  EXPECT_EQ(mjr::color3c64F::goodArithSP,     true                 );
  EXPECT_EQ(mjr::color3c64F::goodArithSDP,    true                 );
  EXPECT_EQ(mjr::color3c64F::goodArithFlt,    true                 );
  EXPECT_EQ(mjr::color3c64F::goodArithLog,    true                 );
  EXPECT_EQ(mjr::color3c64F::sizeOfColor,     24                   );
  EXPECT_EQ(mjr::color3c64F::ptrIsSmaller,    true                 );
  EXPECT_EQ(mjr::color3c64F::maxChanVal,      1.0                  );
  EXPECT_EQ(mjr::color3c64F::minChanVal,      0                    );
  EXPECT_EQ(mjr::color3c64F::meanChanVal,     0.5                  );
  EXPECT_EQ(mjr::color3c64F::maskAllOne,      0xffu                );
  EXPECT_EQ(mjr::color3c64F::maskAllZero,     0x00u                );
  EXPECT_EQ(mjr::color3c64F::channelCount,    3                    );

  EXPECT_TRUE((std::is_same<mjr::color3c64F::colorType,            mjr::color3c64F        >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::colorPtrType,         mjr::color3c64F*       >::value ));               
  EXPECT_TRUE((std::is_same<mjr::color3c64F::colorRefType,         mjr::color3c64F&       >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::colorCRefType,        mjr::color3c64F const& >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::channelType,          double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::maskType,             uint8_t                >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::channelArithDType,    double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::channelArithSPType,   double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::channelArithSDPType,  double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::channelArithFltType,  double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::channelArithLogType,  uint64_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::csIntType,            uint64_t               >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::csFltType,            double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::csNatType,            double                 >::value ));
  EXPECT_TRUE((std::is_same<mjr::color3c64F::colorArgType,         mjr::color3c64F const& >::value ));
}
#endif
/** @endcond */

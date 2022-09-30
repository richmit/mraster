y// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      utest_colorTpl_ia64nGCC.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-11
 @brief     Unit tests for basic color types on ia64 with GCC.@EOL
 @keywords  boost
 @std       C++20
 @copyright 
  @parblock
  Copyright (c) 2022, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#define BOOST_TEST_DYN_LINK
#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif
#include <boost/test/unit_test.hpp>

#include "ramCanvas.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_CASE(types_ia64ngcc64) {

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color1c8b::bitsPerChan    == 8                     );
  BOOST_TEST_CHECK(mjr::color1c8b::bitsPerPixel   == 8                     );
  BOOST_TEST_CHECK(mjr::color1c8b::chanIsInt      == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::chanIsUnsigned == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::chanIsByte     == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::chanIsDouble   == false                 );
  BOOST_TEST_CHECK(mjr::color1c8b::goodMask       == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::goodArithD     == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::goodArithSP    == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::goodArithSDP   == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::goodArithFlt   == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::goodArithLog   == true                  );
  BOOST_TEST_CHECK(mjr::color1c8b::sizeOfColor    == 1                     );
  BOOST_TEST_CHECK(mjr::color1c8b::ptrIsSmaller   == false                 );
  BOOST_TEST_CHECK(mjr::color1c8b::maxChanVal     == 255                   );
  BOOST_TEST_CHECK(mjr::color1c8b::minChanVal     == 0                     );
  BOOST_TEST_CHECK(mjr::color1c8b::meanChanVal    == 127                   );
  BOOST_TEST_CHECK(mjr::color1c8b::maskAllOne     == 0xffu                 );
  BOOST_TEST_CHECK(mjr::color1c8b::maskAllZero    == 0x00u                 );
  BOOST_TEST_CHECK(mjr::color1c8b::channelCount   == 1                     );

  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::colorType,            mjr::color1c8b          >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::colorPtrType,         mjr::color1c8b*         >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::colorRefType,         mjr::color1c8b&         >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::colorCRefType,        mjr::color1c8b const&   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::channelType,          uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::maskType,             uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::channelArithDType,    int16_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::channelArithSPType,   uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::channelArithSDPType,  int32_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::channelArithFltType,  float                   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::channelArithLogType,  uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csIntType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::colorArgType,         mjr::color1c8b          >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color2c8b::bitsPerChan    == 8                     );
  BOOST_TEST_CHECK(mjr::color2c8b::bitsPerPixel   == 16                    );
  BOOST_TEST_CHECK(mjr::color2c8b::chanIsInt      == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::chanIsUnsigned == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::chanIsByte     == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::chanIsDouble   == false                 );
  BOOST_TEST_CHECK(mjr::color2c8b::goodMask       == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::goodArithD     == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::goodArithSP    == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::goodArithSDP   == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::goodArithFlt   == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::goodArithLog   == true                  );
  BOOST_TEST_CHECK(mjr::color2c8b::sizeOfColor    == 2                     );
  BOOST_TEST_CHECK(mjr::color2c8b::ptrIsSmaller   == false                 );
  BOOST_TEST_CHECK(mjr::color2c8b::maxChanVal     == 255                   );
  BOOST_TEST_CHECK(mjr::color2c8b::minChanVal     == 0                     );
  BOOST_TEST_CHECK(mjr::color2c8b::meanChanVal    == 127                   );
  BOOST_TEST_CHECK(mjr::color2c8b::maskAllOne     == 0xffffu               );
  BOOST_TEST_CHECK(mjr::color2c8b::maskAllZero    == 0x0000u               );
  BOOST_TEST_CHECK(mjr::color2c8b::channelCount   == 2                     );

  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::colorType,            mjr::color2c8b          >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::colorPtrType,         mjr::color2c8b*         >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::colorRefType,         mjr::color2c8b&         >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::colorCRefType,        mjr::color2c8b const&   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::channelType,          uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::maskType,             uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::channelArithDType,    int16_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::channelArithSPType,   uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::channelArithSDPType,  int32_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::channelArithFltType,  float                   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::channelArithLogType,  uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::csIntType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c8b::colorArgType,         mjr::color2c8b          >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color3c8b::bitsPerChan    == 8                     );
  BOOST_TEST_CHECK(mjr::color3c8b::bitsPerPixel   == 24                    );
  BOOST_TEST_CHECK(mjr::color3c8b::chanIsInt      == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::chanIsUnsigned == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::chanIsByte     == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::chanIsDouble   == false                 );
  BOOST_TEST_CHECK(mjr::color3c8b::goodMask       == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::goodArithD     == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::goodArithSP    == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::goodArithSDP   == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::goodArithFlt   == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::goodArithLog   == true                  );
  BOOST_TEST_CHECK(mjr::color3c8b::sizeOfColor    == 4                     );
  BOOST_TEST_CHECK(mjr::color3c8b::ptrIsSmaller   == false                 );
  BOOST_TEST_CHECK(mjr::color3c8b::maxChanVal     == 255                   );
  BOOST_TEST_CHECK(mjr::color3c8b::minChanVal     == 0                     );
  BOOST_TEST_CHECK(mjr::color3c8b::meanChanVal    == 127                   );
  BOOST_TEST_CHECK(mjr::color3c8b::maskAllOne     == 0xffffffffu           );
  BOOST_TEST_CHECK(mjr::color3c8b::maskAllZero    == 0x00000000u           );
  BOOST_TEST_CHECK(mjr::color3c8b::channelCount   == 3                     );

  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::colorType,            mjr::color3c8b          >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::colorPtrType,         mjr::color3c8b*         >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::colorRefType,         mjr::color3c8b&         >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::colorCRefType,        mjr::color3c8b const&   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::channelType,          uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::maskType,             uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::channelArithDType,    int16_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::channelArithSPType,   uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::channelArithSDPType,  int32_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::channelArithFltType,  float                   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::channelArithLogType,  uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::csIntType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c8b::colorArgType,         mjr::color3c8b          >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color4c8b::bitsPerChan    == 8                     );
  BOOST_TEST_CHECK(mjr::color4c8b::bitsPerPixel   == 32                    );
  BOOST_TEST_CHECK(mjr::color4c8b::chanIsInt      == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::chanIsUnsigned == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::chanIsByte     == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::chanIsDouble   == false                 );
  BOOST_TEST_CHECK(mjr::color4c8b::goodMask       == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::goodArithD     == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::goodArithSP    == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::goodArithSDP   == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::goodArithFlt   == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::goodArithLog   == true                  );
  BOOST_TEST_CHECK(mjr::color4c8b::sizeOfColor    == 4                     );
  BOOST_TEST_CHECK(mjr::color4c8b::ptrIsSmaller   == false                 );
  BOOST_TEST_CHECK(mjr::color4c8b::maxChanVal     == 255                   );
  BOOST_TEST_CHECK(mjr::color4c8b::minChanVal     == 0                     );
  BOOST_TEST_CHECK(mjr::color4c8b::meanChanVal    == 127                   );
  BOOST_TEST_CHECK(mjr::color4c8b::maskAllOne     == 0xffffffffu           );
  BOOST_TEST_CHECK(mjr::color4c8b::maskAllZero    == 0x00000000u           );
  BOOST_TEST_CHECK(mjr::color4c8b::channelCount   == 4                     );

  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::colorType,            mjr::color4c8b          >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::colorPtrType,         mjr::color4c8b*         >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::colorRefType,         mjr::color4c8b&         >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::colorCRefType,        mjr::color4c8b const&   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::channelType,          uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::maskType,             uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::channelArithDType,    int16_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::channelArithSPType,   uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::channelArithSDPType,  int32_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::channelArithFltType,  float                   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::channelArithLogType,  uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::csIntType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color4c8b::colorArgType,         mjr::color4c8b          >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color5c8b::bitsPerChan    == 8                     );
  BOOST_TEST_CHECK(mjr::color5c8b::bitsPerPixel   == 40                    );
  BOOST_TEST_CHECK(mjr::color5c8b::chanIsInt      == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::chanIsUnsigned == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::chanIsByte     == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::chanIsDouble   == false                 );
  BOOST_TEST_CHECK(mjr::color5c8b::goodMask       == false                 );
  BOOST_TEST_CHECK(mjr::color5c8b::goodArithD     == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::goodArithSP    == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::goodArithSDP   == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::goodArithFlt   == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::goodArithLog   == true                  );
  BOOST_TEST_CHECK(mjr::color5c8b::sizeOfColor    == 5                     );
  BOOST_TEST_CHECK(mjr::color5c8b::ptrIsSmaller   == false                 );
  BOOST_TEST_CHECK(mjr::color5c8b::maxChanVal     == 255                   );
  BOOST_TEST_CHECK(mjr::color5c8b::minChanVal     == 0                     );
  BOOST_TEST_CHECK(mjr::color5c8b::meanChanVal    == 127                   );
  BOOST_TEST_CHECK(mjr::color5c8b::maskAllOne     == 0xffu                 );
  BOOST_TEST_CHECK(mjr::color5c8b::maskAllZero    == 0x00u                 );
  BOOST_TEST_CHECK(mjr::color5c8b::channelCount   == 5                     );

  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::colorType,            mjr::color5c8b          >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::colorPtrType,         mjr::color5c8b*         >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::colorRefType,         mjr::color5c8b&         >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::colorCRefType,        mjr::color5c8b const&   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::channelType,          uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::maskType,             uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::channelArithDType,    int16_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::channelArithSPType,   uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::channelArithSDPType,  int32_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::channelArithFltType,  float                   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::channelArithLogType,  uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::csIntType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color5c8b::colorArgType,         mjr::color5c8b          >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color6c8b::bitsPerChan    == 8                     );
  BOOST_TEST_CHECK(mjr::color6c8b::bitsPerPixel   == 6*8                   );
  BOOST_TEST_CHECK(mjr::color6c8b::chanIsInt      == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::chanIsUnsigned == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::chanIsByte     == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::chanIsDouble   == false                 );
  BOOST_TEST_CHECK(mjr::color6c8b::goodMask       == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::goodArithD     == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::goodArithSP    == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::goodArithSDP   == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::goodArithFlt   == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::goodArithLog   == true                  );
  BOOST_TEST_CHECK(mjr::color6c8b::sizeOfColor    == 8                     );
  BOOST_TEST_CHECK(mjr::color6c8b::ptrIsSmaller   == false                 );
  BOOST_TEST_CHECK(mjr::color6c8b::maxChanVal     == 255                   );
  BOOST_TEST_CHECK(mjr::color6c8b::minChanVal     == 0                     );
  BOOST_TEST_CHECK(mjr::color6c8b::meanChanVal    == 127                   );
  BOOST_TEST_CHECK(mjr::color6c8b::maskAllOne     == 0xffffffffffffffffu   );
  BOOST_TEST_CHECK(mjr::color6c8b::maskAllZero    == 0x0000000000000000u   );
  BOOST_TEST_CHECK(mjr::color6c8b::channelCount   == 6                     );

  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::colorType,            mjr::color6c8b          >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::colorPtrType,         mjr::color6c8b*         >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::colorRefType,         mjr::color6c8b&         >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::colorCRefType,        mjr::color6c8b const&   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::channelType,          uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::maskType,             uint64_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::channelArithDType,    int16_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::channelArithSPType,   uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::channelArithSDPType,  int32_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::channelArithFltType,  float                   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::channelArithLogType,  uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::csIntType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color6c8b::colorArgType,         mjr::color6c8b          >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color8c8b::bitsPerChan    == 8                     );
  BOOST_TEST_CHECK(mjr::color8c8b::bitsPerPixel   == 64                    );
  BOOST_TEST_CHECK(mjr::color8c8b::chanIsInt      == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::chanIsUnsigned == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::chanIsByte     == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::chanIsDouble   == false                 );
  BOOST_TEST_CHECK(mjr::color8c8b::goodMask       == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::goodArithD     == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::goodArithSP    == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::goodArithSDP   == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::goodArithFlt   == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::goodArithLog   == true                  );
  BOOST_TEST_CHECK(mjr::color8c8b::sizeOfColor    == 8                     );
  BOOST_TEST_CHECK(mjr::color8c8b::ptrIsSmaller   == false                 );
  BOOST_TEST_CHECK(mjr::color8c8b::maxChanVal     == 255                   );
  BOOST_TEST_CHECK(mjr::color8c8b::minChanVal     == 0                     );
  BOOST_TEST_CHECK(mjr::color8c8b::meanChanVal    == 127                   );
  BOOST_TEST_CHECK(mjr::color8c8b::maskAllOne     == 0xffffffffffffffffu   );
  BOOST_TEST_CHECK(mjr::color8c8b::maskAllZero    == 0x0000000000000000u   );
  BOOST_TEST_CHECK(mjr::color8c8b::channelCount   == 8                     );

  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::colorType,            mjr::color8c8b          >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::colorPtrType,         mjr::color8c8b*         >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::colorRefType,         mjr::color8c8b&         >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::colorCRefType,        mjr::color8c8b const&   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::channelType,          uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::maskType,             uint64_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::channelArithDType,    int16_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::channelArithSPType,   uint16_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::channelArithSDPType,  int32_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::channelArithFltType,  float                   >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::channelArithLogType,  uint8_t                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::csIntType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csFltType,            double                  >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color1c8b::csNatType,            uint32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color8c8b::colorArgType,         mjr::color8c8b          >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color3c16b::bitsPerChan    == 16                   );
  BOOST_TEST_CHECK(mjr::color3c16b::bitsPerPixel   == 48                   );
  BOOST_TEST_CHECK(mjr::color3c16b::chanIsInt      == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::chanIsUnsigned == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::chanIsByte     == false                );
  BOOST_TEST_CHECK(mjr::color3c16b::chanIsDouble   == false                );
  BOOST_TEST_CHECK(mjr::color3c16b::goodMask       == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::goodArithD     == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::goodArithSP    == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::goodArithSDP   == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::goodArithFlt   == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::goodArithLog   == true                 );
  BOOST_TEST_CHECK(mjr::color3c16b::sizeOfColor    == 8                    );
  BOOST_TEST_CHECK(mjr::color3c16b::ptrIsSmaller   == false                );
  BOOST_TEST_CHECK(mjr::color3c16b::maxChanVal     == 65535                );
  BOOST_TEST_CHECK(mjr::color3c16b::minChanVal     == 0                    );
  BOOST_TEST_CHECK(mjr::color3c16b::meanChanVal    == 32767                );
  BOOST_TEST_CHECK(mjr::color3c16b::maskAllOne     == 0xffffffffffffffffu  );
  BOOST_TEST_CHECK(mjr::color3c16b::maskAllZero    == 0x0000000000000000u  );
  BOOST_TEST_CHECK(mjr::color3c16b::channelCount   == 3                    );

  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::colorType,            mjr::color3c16b        >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::colorPtrType,         mjr::color3c16b*       >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::colorRefType,         mjr::color3c16b&       >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::colorCRefType,        mjr::color3c16b const& >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::channelType,          uint16_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::maskType,             uint64_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::channelArithDType,    int32_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::channelArithSPType,   uint32_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::channelArithSDPType,  int64_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::channelArithFltType,  float                  >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::channelArithLogType,  uint16_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::csIntType,            uint32_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::csFltType,            double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::csNatType,            uint32_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c16b::colorArgType,         mjr::color3c16b        >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color2c32b::bitsPerChan    == 32                   );
  BOOST_TEST_CHECK(mjr::color2c32b::bitsPerPixel   == 64                   );
  BOOST_TEST_CHECK(mjr::color2c32b::chanIsInt      == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::chanIsUnsigned == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::chanIsByte     == false                );
  BOOST_TEST_CHECK(mjr::color2c32b::chanIsDouble   == false                );
  BOOST_TEST_CHECK(mjr::color2c32b::goodMask       == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::goodArithD     == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::goodArithSP    == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::goodArithSDP   == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::goodArithFlt   == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::goodArithLog   == true                 );
  BOOST_TEST_CHECK(mjr::color2c32b::sizeOfColor    == 8                    );
  BOOST_TEST_CHECK(mjr::color2c32b::ptrIsSmaller   == false                );
  BOOST_TEST_CHECK(mjr::color2c32b::maxChanVal     == 4294967295u          );
  BOOST_TEST_CHECK(mjr::color2c32b::minChanVal     == 0                    );
  BOOST_TEST_CHECK(mjr::color2c32b::meanChanVal    == 2147483647           );
  BOOST_TEST_CHECK(mjr::color2c32b::maskAllOne     == 0xffffffffffffffffu  );
  BOOST_TEST_CHECK(mjr::color2c32b::maskAllZero    == 0x0000000000000000u  );
  BOOST_TEST_CHECK(mjr::color2c32b::channelCount   == 2                    );

  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::colorType,            mjr::color2c32b        >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::colorPtrType,         mjr::color2c32b*       >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::colorRefType,         mjr::color2c32b&       >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::colorCRefType,        mjr::color2c32b const& >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::channelType,          uint32_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::maskType,             uint64_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::channelArithDType,    int64_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::channelArithSPType,   uint64_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::channelArithSDPType,  mjr_intBiggest_t       >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::channelArithFltType,  double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::channelArithLogType,  uint32_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::csIntType,            uint64_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::csFltType,            double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::csNatType,            uint64_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color2c32b::colorArgType,         mjr::color2c32b        >::value ));

////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_TEST_CHECK(mjr::color3c64F::bitsPerChan    == 64                   );
  BOOST_TEST_CHECK(mjr::color3c64F::bitsPerPixel   == 192                  );
  BOOST_TEST_CHECK(mjr::color3c64F::chanIsInt      == false                );
  BOOST_TEST_CHECK(mjr::color3c64F::chanIsUnsigned == false                );
  BOOST_TEST_CHECK(mjr::color3c64F::chanIsByte     == false                );
  BOOST_TEST_CHECK(mjr::color3c64F::chanIsDouble   == true                 );
  BOOST_TEST_CHECK(mjr::color3c64F::goodMask       == false                );
  BOOST_TEST_CHECK(mjr::color3c64F::goodArithD     == true                 );
  BOOST_TEST_CHECK(mjr::color3c64F::goodArithSP    == true                 );
  BOOST_TEST_CHECK(mjr::color3c64F::goodArithSDP   == true                 );
  BOOST_TEST_CHECK(mjr::color3c64F::goodArithFlt   == true                 );
  BOOST_TEST_CHECK(mjr::color3c64F::goodArithLog   == true                 );
  BOOST_TEST_CHECK(mjr::color3c64F::sizeOfColor    == 24                   );
  BOOST_TEST_CHECK(mjr::color3c64F::ptrIsSmaller   == true                 );
  BOOST_TEST_CHECK(mjr::color3c64F::maxChanVal     == 1.0                  );
  BOOST_TEST_CHECK(mjr::color3c64F::minChanVal     == 0                    );
  BOOST_TEST_CHECK(mjr::color3c64F::meanChanVal    == 0.5                  );
  BOOST_TEST_CHECK(mjr::color3c64F::maskAllOne     == 0xffu                );
  BOOST_TEST_CHECK(mjr::color3c64F::maskAllZero    == 0x00u                );
  BOOST_TEST_CHECK(mjr::color3c64F::channelCount   == 3                    );

  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::colorType,            mjr::color3c64F        >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::colorPtrType,         mjr::color3c64F*       >::value ));               
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::colorRefType,         mjr::color3c64F&       >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::colorCRefType,        mjr::color3c64F const& >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::channelType,          double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::maskType,             uint8_t                >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::channelArithDType,    double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::channelArithSPType,   double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::channelArithSDPType,  double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::channelArithFltType,  double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::channelArithLogType,  uint64_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::csIntType,            uint64_t               >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::csFltType,            double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::csNatType,            double                 >::value ));
  BOOST_TEST_CHECK((std::is_same<mjr::color3c64F::colorArgType,         mjr::color3c64F const& >::value ));

}
/** @endcond */

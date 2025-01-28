// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      test_color_con.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2025-01-28
 @brief     Print out various stats for a color type.@EOL
 @std       C++23
 @see       
 @copyright 
  @parblock
  Copyright (c) 2025, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.
  
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "MRcolor.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------

   typedef mjr::colorRGBA8b   ct; //!< colorTpl: RGBA  (8-bit int/channel) (truecolor)
  // typedef mjr::colorRGBA16b  ct; //!< colorTpl: RGBA (16-bit int/channel)
  // typedef mjr::colorRGBA32b  ct; //!< colorTpl: RGBA (32-bit int/channel)
  // typedef mjr::colorRGBA64b  ct; //!< colorTpl: RGBA (64-bit int/channel)
  // typedef mjr::colorRGBA32F  ct; //!< colorTpl: RGBA (32-bit float/channel)
  // typedef mjr::colorRGBA64F  ct; //!< colorTpl: RGBA (64-bit float/channel)
  // typedef mjr::colorRGB8b    ct; //!< colorTpl: RGB   (8-bit int/channel) (truecolor)
  // typedef mjr::colorRGB16b   ct; //!< colorTpl: RGB  (16-bit int/channel)
  // typedef mjr::colorRGB32b   ct; //!< colorTpl: RGB  (32-bit int/channel)
  // typedef mjr::colorRGB64b   ct; //!< colorTpl: RGB  (64-bit int/channel)
  // typedef mjr::colorRGB32F   ct; //!< colorTpl: RGB  (32-bit float/channel)
  // typedef mjr::colorRGB64F   ct; //!< colorTpl: RGB  (64-bit float/channel)
  // typedef mjr::colorGrey8b   ct; //!< colorTpl:   8-bit int Greyscale
  // typedef mjr::colorGrey16b  ct; //!< colorTpl:  16-bit int Greyscale
  // typedef mjr::colorGrey32b  ct; //!< colorTpl:  32-bit int Greyscale
  // typedef mjr::colorGrey64b  ct; //!< colorTpl:  64-bit int Greyscale
  // typedef mjr::colorGrey128b ct; //!< colorTpl: 128-bit int Greyscale
  // typedef mjr::colorGrey32F  ct; //!< colorTpl:  32-bit float Greyscale
  // typedef mjr::colorGrey64F  ct; //!< colorTpl:  64-bit float Greyscale

#define PRTCST(x) (sizeof(x)<=sizeof(char) ? (int)(x) : (x))

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
  std::cout << "ct::bitsPerChan     " << PRTCST(ct::bitsPerChan)    << std::endl;
  std::cout << "ct::bitsPerPixel    " << PRTCST(ct::bitsPerPixel)   << std::endl;
  std::cout << "ct::chanIsInt       " << PRTCST(ct::chanIsInt)      << std::endl;
  std::cout << "ct::chanIsUnsigned  " << PRTCST(ct::chanIsUnsigned) << std::endl;
  std::cout << "ct::chanIsByte      " << PRTCST(ct::chanIsByte)     << std::endl;
  std::cout << "ct::chanIsDouble    " << PRTCST(ct::chanIsDouble)   << std::endl;
  std::cout << "ct::goodMask        " << PRTCST(ct::goodMask)       << std::endl;
  std::cout << "ct::goodArithD      " << PRTCST(ct::goodArithD)     << std::endl;
  std::cout << "ct::goodArithSP     " << PRTCST(ct::goodArithSP)    << std::endl;
  std::cout << "ct::goodArithSDP    " << PRTCST(ct::goodArithSDP)   << std::endl;
  std::cout << "ct::goodArithFlt    " << PRTCST(ct::goodArithFlt)   << std::endl;
  std::cout << "ct::goodArithLog    " << PRTCST(ct::goodArithLog)   << std::endl;
  std::cout << "ct::sizeOfColor     " << PRTCST(ct::sizeOfColor)    << std::endl;
  std::cout << "ct::ptrIsSmaller    " << PRTCST(ct::ptrIsSmaller)   << std::endl;
  std::cout << "ct::maxChanVal      " << PRTCST(ct::maxChanVal)     << std::endl;
  std::cout << "ct::minChanVal      " << PRTCST(ct::minChanVal)     << std::endl;
  std::cout << "ct::meanChanVal     " << PRTCST(ct::meanChanVal)    << std::endl;
  std::cout << "ct::maskAllOne      " << PRTCST(ct::maskAllOne)     << std::endl;
  std::cout << "ct::maskAllZero     " << PRTCST(ct::maskAllZero)    << std::endl;
  std::cout << "ct::channelCount    " << PRTCST(ct::channelCount)   << std::endl;

  std::cout << "sz ct::colorType           " << sizeof(ct::colorType)            << std::endl;
  std::cout << "sz ct::colorPtrType        " << sizeof(ct::colorPtrType)         << std::endl;   
  std::cout << "sz ct::colorRefType        " << sizeof(ct::colorRefType)         << std::endl;
  std::cout << "sz ct::colorCRefType       " << sizeof(ct::colorCRefType)        << std::endl;
  std::cout << "sz ct::channelType         " << sizeof(ct::channelType)          << std::endl;
  std::cout << "sz ct::maskType            " << sizeof(ct::maskType)             << std::endl;
  std::cout << "sz ct::channelArithDType   " << sizeof(ct::channelArithDType)    << std::endl;
  std::cout << "sz ct::channelArithSPType  " << sizeof(ct::channelArithSPType)   << std::endl;
  std::cout << "sz ct::channelArithSDPType " << sizeof(ct::channelArithSDPType)  << std::endl;
  std::cout << "sz ct::channelArithFltType " << sizeof(ct::channelArithFltType)  << std::endl;
  std::cout << "sz ct::channelArithLogType " << sizeof(ct::channelArithLogType)  << std::endl;
  std::cout << "sz ct::csIntType           " << sizeof(ct::csIntType)            << std::endl;
  std::cout << "sz ct::csFltType           " << sizeof(ct::csFltType)            << std::endl;
  std::cout << "sz ct::csNatType           " << sizeof(ct::csNatType)            << std::endl;
  std::cout << "sz ct::colorArgType        " << sizeof(ct::colorArgType)         << std::endl;
}

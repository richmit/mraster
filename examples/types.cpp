// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      types.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-07-09
 @version   VERSION
 @brief     Template types and sizes.@EOL
 @keywords  
 @std       C++20
 @see       
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
********************************************************************************************************************************************************.H.E.**/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <vector>                                                        /* STL vector              C++11    */ 

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {

  std::cout << "mjr::ramCanvas1c8b"                                                                                        << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorType)              " << sizeof(mjr::ramCanvas1c8b::colorType)              << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorChanType)          " << sizeof(mjr::ramCanvas1c8b::colorChanType)          << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorMaskType)          " << sizeof(mjr::ramCanvas1c8b::colorMaskType)          << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorChanArithDType)    " << sizeof(mjr::ramCanvas1c8b::colorChanArithDType)    << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorChanArithSPType)   " << sizeof(mjr::ramCanvas1c8b::colorChanArithSPType)   << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorChanArithSDPType)  " << sizeof(mjr::ramCanvas1c8b::colorChanArithSDPType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorChanArithFltType)  " << sizeof(mjr::ramCanvas1c8b::colorChanArithFltType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorChanArithLogType)  " << sizeof(mjr::ramCanvas1c8b::colorChanArithLogType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas1c8b::colorPtrType)           " << sizeof(mjr::ramCanvas1c8b::colorPtrType)           << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::bitsPerChan         " << (int)mjr::ramCanvas1c8b::colorType::bitsPerChan    << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::bitsPerPixel        " << (int)mjr::ramCanvas1c8b::colorType::bitsPerPixel   << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::chanIsInt           " << (int)mjr::ramCanvas1c8b::colorType::chanIsInt      << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::chanIsFlt           " << (int)mjr::ramCanvas1c8b::colorType::chanIsFlt      << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::chanIsByte          " << (int)mjr::ramCanvas1c8b::colorType::chanIsByte     << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::chanIsDouble        " << (int)mjr::ramCanvas1c8b::colorType::chanIsDouble   << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::sizeOfColor         " << (int)mjr::ramCanvas1c8b::colorType::sizeOfColor    << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::ptrIsSmaller        " << (int)mjr::ramCanvas1c8b::colorType::ptrIsSmaller   << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::goodMask            " << (int)mjr::ramCanvas1c8b::colorType::goodMask       << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::goodArithD          " << (int)mjr::ramCanvas1c8b::colorType::goodArithD     << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::goodArithSP         " << (int)mjr::ramCanvas1c8b::colorType::goodArithSP    << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::goodArithSDP        " << (int)mjr::ramCanvas1c8b::colorType::goodArithSDP   << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::goodArithFlt        " << (int)mjr::ramCanvas1c8b::colorType::goodArithFlt   << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::goodArithLog        " << (int)mjr::ramCanvas1c8b::colorType::goodArithLog   << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::maxChanVal          " << (int)mjr::ramCanvas1c8b::colorType::maxChanVal     << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::minChanVal          " << (int)mjr::ramCanvas1c8b::colorType::minChanVal     << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::meanChanVal         " << (int)mjr::ramCanvas1c8b::colorType::meanChanVal    << std::endl;
  std::cout << "mjr::ramCanvas1c8b::colorType::channelCount        " << (int)mjr::ramCanvas1c8b::colorType::channelCount   << std::endl;

  std::cout << "mjr::ramCanvas3c8b"                                                                                        << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorType)              " << sizeof(mjr::ramCanvas3c8b::colorType)              << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorChanType)          " << sizeof(mjr::ramCanvas3c8b::colorChanType)          << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorMaskType)          " << sizeof(mjr::ramCanvas3c8b::colorMaskType)          << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorChanArithDType)    " << sizeof(mjr::ramCanvas3c8b::colorChanArithDType)    << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorChanArithSPType)   " << sizeof(mjr::ramCanvas3c8b::csIdxType)              << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorChanArithSDPType)  " << sizeof(mjr::ramCanvas3c8b::colorChanArithSDPType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorChanArithFltType)  " << sizeof(mjr::ramCanvas3c8b::colorChanArithFltType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorChanArithLogType)  " << sizeof(mjr::ramCanvas3c8b::colorChanArithLogType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c8b::colorPtrType)           " << sizeof(mjr::ramCanvas3c8b::colorPtrType)           << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::bitsPerChan         " << (int)mjr::ramCanvas3c8b::colorType::bitsPerChan    << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::bitsPerPixel        " << (int)mjr::ramCanvas3c8b::colorType::bitsPerPixel   << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::chanIsInt           " << (int)mjr::ramCanvas3c8b::colorType::chanIsInt      << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::chanIsFlt           " << (int)mjr::ramCanvas3c8b::colorType::chanIsFlt      << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::chanIsByte          " << (int)mjr::ramCanvas3c8b::colorType::chanIsByte     << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::chanIsDouble        " << (int)mjr::ramCanvas3c8b::colorType::chanIsDouble   << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::sizeOfColor         " << (int)mjr::ramCanvas3c8b::colorType::sizeOfColor    << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::ptrIsSmaller        " << (int)mjr::ramCanvas3c8b::colorType::ptrIsSmaller   << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::goodMask            " << (int)mjr::ramCanvas3c8b::colorType::goodMask       << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::goodArithD          " << (int)mjr::ramCanvas3c8b::colorType::goodArithD     << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::goodArithSP         " << (int)mjr::ramCanvas3c8b::colorType::goodArithSP    << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::goodArithSDP        " << (int)mjr::ramCanvas3c8b::colorType::goodArithSDP   << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::goodArithFlt        " << (int)mjr::ramCanvas3c8b::colorType::goodArithFlt   << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::goodArithLog        " << (int)mjr::ramCanvas3c8b::colorType::goodArithLog   << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::maxChanVal          " << (int)mjr::ramCanvas3c8b::colorType::maxChanVal     << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::minChanVal          " << (int)mjr::ramCanvas3c8b::colorType::minChanVal     << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::meanChanVal         " << (int)mjr::ramCanvas3c8b::colorType::meanChanVal    << std::endl;
  std::cout << "mjr::ramCanvas3c8b::colorType::channelCount        " << (int)mjr::ramCanvas3c8b::colorType::channelCount   << std::endl;

  std::cout << "mjr::ramCanvas3c16b"                                                                                       << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorType)             " << sizeof(mjr::ramCanvas3c16b::colorType)             << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorChanType)         " << sizeof(mjr::ramCanvas3c16b::colorChanType)         << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorMaskType)         " << sizeof(mjr::ramCanvas3c16b::colorMaskType)         << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorChanArithDType)   " << sizeof(mjr::ramCanvas3c16b::colorChanArithDType)   << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorChanArithSPType)  " << sizeof(mjr::ramCanvas3c16b::colorChanArithSPType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorChanArithSDPType) " << sizeof(mjr::ramCanvas3c16b::colorChanArithSDPType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorChanArithFltType) " << sizeof(mjr::ramCanvas3c16b::colorChanArithFltType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorChanArithLogType) " << sizeof(mjr::ramCanvas3c16b::colorChanArithLogType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas3c16b::colorPtrType)          " << sizeof(mjr::ramCanvas3c16b::colorPtrType)          << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::bitsPerChan        " << (int)mjr::ramCanvas3c16b::colorType::bitsPerChan   << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::bitsPerPixel       " << (int)mjr::ramCanvas3c16b::colorType::bitsPerPixel  << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::chanIsInt          " << (int)mjr::ramCanvas3c16b::colorType::chanIsInt     << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::chanIsFlt          " << (int)mjr::ramCanvas3c16b::colorType::chanIsFlt     << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::chanIsByte         " << (int)mjr::ramCanvas3c16b::colorType::chanIsByte    << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::chanIsDouble       " << (int)mjr::ramCanvas3c16b::colorType::chanIsDouble  << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::sizeOfColor        " << (int)mjr::ramCanvas3c16b::colorType::sizeOfColor   << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::ptrIsSmaller       " << (int)mjr::ramCanvas3c16b::colorType::ptrIsSmaller  << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::goodMask           " << (int)mjr::ramCanvas3c16b::colorType::goodMask      << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::goodArithD         " << (int)mjr::ramCanvas3c16b::colorType::goodArithD    << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::goodArithSP        " << (int)mjr::ramCanvas3c16b::colorType::goodArithSP   << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::goodArithSDP       " << (int)mjr::ramCanvas3c16b::colorType::goodArithSDP  << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::goodArithFlt       " << (int)mjr::ramCanvas3c16b::colorType::goodArithFlt  << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::goodArithLog       " << (int)mjr::ramCanvas3c16b::colorType::goodArithLog  << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::maxChanVal         " << (int)mjr::ramCanvas3c16b::colorType::maxChanVal    << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::minChanVal         " << (int)mjr::ramCanvas3c16b::colorType::minChanVal    << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::meanChanVal        " << (int)mjr::ramCanvas3c16b::colorType::meanChanVal   << std::endl;
  std::cout << "mjr::ramCanvas3c16b::colorType::channelCount       " << (int)mjr::ramCanvas3c16b::colorType::channelCount  << std::endl;

  std::cout << "mjr::ramCanvas4c32F"                                                                                       << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorType)             " << sizeof(mjr::ramCanvas4c32F::colorType)             << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorChanType)         " << sizeof(mjr::ramCanvas4c32F::colorChanType)         << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorMaskType)         " << sizeof(mjr::ramCanvas4c32F::colorMaskType)         << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorChanArithDType)   " << sizeof(mjr::ramCanvas4c32F::colorChanArithDType)   << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorChanArithSPType)  " << sizeof(mjr::ramCanvas4c32F::colorChanArithSPType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorChanArithSDPType) " << sizeof(mjr::ramCanvas4c32F::colorChanArithSDPType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorChanArithFltType) " << sizeof(mjr::ramCanvas4c32F::colorChanArithFltType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorChanArithLogType) " << sizeof(mjr::ramCanvas4c32F::colorChanArithLogType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c32F::colorPtrType)          " << sizeof(mjr::ramCanvas4c32F::colorPtrType)          << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::bitsPerChan        " << (int)mjr::ramCanvas4c32F::colorType::bitsPerChan   << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::bitsPerPixel       " << (int)mjr::ramCanvas4c32F::colorType::bitsPerPixel  << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::chanIsInt          " << (int)mjr::ramCanvas4c32F::colorType::chanIsInt     << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::chanIsFlt          " << (int)mjr::ramCanvas4c32F::colorType::chanIsFlt     << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::chanIsByte         " << (int)mjr::ramCanvas4c32F::colorType::chanIsByte    << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::chanIsDouble       " << (int)mjr::ramCanvas4c32F::colorType::chanIsDouble  << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::sizeOfColor        " << (int)mjr::ramCanvas4c32F::colorType::sizeOfColor   << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::ptrIsSmaller       " << (int)mjr::ramCanvas4c32F::colorType::ptrIsSmaller  << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::goodMask           " << (int)mjr::ramCanvas4c32F::colorType::goodMask      << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::goodArithD         " << (int)mjr::ramCanvas4c32F::colorType::goodArithD    << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::goodArithSP        " << (int)mjr::ramCanvas4c32F::colorType::goodArithSP   << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::goodArithSDP       " << (int)mjr::ramCanvas4c32F::colorType::goodArithSDP  << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::goodArithFlt       " << (int)mjr::ramCanvas4c32F::colorType::goodArithFlt  << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::goodArithLog       " << (int)mjr::ramCanvas4c32F::colorType::goodArithLog  << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::maxChanVal         " << (int)mjr::ramCanvas4c32F::colorType::maxChanVal    << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::minChanVal         " << (int)mjr::ramCanvas4c32F::colorType::minChanVal    << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::meanChanVal        " << (int)mjr::ramCanvas4c32F::colorType::meanChanVal   << std::endl;
  std::cout << "mjr::ramCanvas4c32F::colorType::channelCount       " << (int)mjr::ramCanvas4c32F::colorType::channelCount  << std::endl;

  std::cout << "mjr::ramCanvas4c64F"                                                                                       << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorType)             " << sizeof(mjr::ramCanvas4c64F::colorType)             << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorChanType)         " << sizeof(mjr::ramCanvas4c64F::colorChanType)         << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorMaskType)         " << sizeof(mjr::ramCanvas4c64F::colorMaskType)         << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorChanArithDType)   " << sizeof(mjr::ramCanvas4c64F::colorChanArithDType)   << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorChanArithSPType)  " << sizeof(mjr::ramCanvas4c64F::colorChanArithSPType)  << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorChanArithSDPType) " << sizeof(mjr::ramCanvas4c64F::colorChanArithSDPType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorChanArithFltType) " << sizeof(mjr::ramCanvas4c64F::colorChanArithFltType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorChanArithLogType) " << sizeof(mjr::ramCanvas4c64F::colorChanArithLogType) << std::endl;
  std::cout << "sizeof(mjr::ramCanvas4c64F::colorPtrType)          " << sizeof(mjr::ramCanvas4c64F::colorPtrType)          << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::bitsPerChan        " << (int)mjr::ramCanvas4c64F::colorType::bitsPerChan   << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::bitsPerPixel       " << (int)mjr::ramCanvas4c64F::colorType::bitsPerPixel  << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::chanIsInt          " << (int)mjr::ramCanvas4c64F::colorType::chanIsInt     << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::chanIsFlt          " << (int)mjr::ramCanvas4c64F::colorType::chanIsFlt     << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::chanIsByte         " << (int)mjr::ramCanvas4c64F::colorType::chanIsByte    << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::chanIsDouble       " << (int)mjr::ramCanvas4c64F::colorType::chanIsDouble  << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::sizeOfColor        " << (int)mjr::ramCanvas4c64F::colorType::sizeOfColor   << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::ptrIsSmaller       " << (int)mjr::ramCanvas4c64F::colorType::ptrIsSmaller  << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::goodMask           " << (int)mjr::ramCanvas4c64F::colorType::goodMask      << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::goodArithD         " << (int)mjr::ramCanvas4c64F::colorType::goodArithD    << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::goodArithSP        " << (int)mjr::ramCanvas4c64F::colorType::goodArithSP   << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::goodArithSDP       " << (int)mjr::ramCanvas4c64F::colorType::goodArithSDP  << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::goodArithFlt       " << (int)mjr::ramCanvas4c64F::colorType::goodArithFlt  << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::goodArithLog       " << (int)mjr::ramCanvas4c64F::colorType::goodArithLog  << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::maxChanVal         " << (int)mjr::ramCanvas4c64F::colorType::maxChanVal    << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::minChanVal         " << (int)mjr::ramCanvas4c64F::colorType::minChanVal    << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::meanChanVal        " << (int)mjr::ramCanvas4c64F::colorType::meanChanVal   << std::endl;
  std::cout << "mjr::ramCanvas4c64F::colorType::channelCount       " << (int)mjr::ramCanvas4c64F::colorType::channelCount  << std::endl;

}

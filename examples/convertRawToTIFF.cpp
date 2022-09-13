// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      convertRawToTIFF.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @brief     Demonstrate how load a floating point RAW file and save it as an integer TIFF.@EOL
 @keywords  MRaster
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
********************************************************************************************************************************************************.H.E.**/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  mjr::ramCanvas3c32F theRamCanvas;
  std::string fileName;

  if (argc < 2)
    fileName = "../data/utest/ut-draw_primatives_flt.mrw";  // This file is used for unit tests -- a handy 32-bit raw image. ;)
  else
    fileName = argv[1];

  int ret;

  ret = theRamCanvas.readRAWfile(fileName);
  if (ret != 0) {
    std::cout << "ERROR(readRAWfile): " << ret << std::endl;
    return ret;
  }

  // We create a converter object for the *two* file write methods below.  This converter will transform the 32-bit floating point channels into 8-bit
  // unsigned integer channels.
  mjr::ramCanvas3c32F::rcConverterRGBbyte<mjr::ramCanvas3c32F> rcConv(theRamCanvas);

  ret = theRamCanvas.writeRAWfile("foo.mrw", rcConv);
  if (ret != 0) {
    std::cout << "ERROR(writeRAWfile): " << ret << std::endl;
    return ret;
  }

  // Note: For the more complex writeTIFFfile() method, the markAlpha argument is not optional.
  ret = theRamCanvas.writeTIFFfile("foo.tiff", rcConv, false);
  if (ret != 0) {
    std::cout << "ERROR(writeTIFFfile): " << ret << std::endl;
    return ret;
  }

  return 0;
}

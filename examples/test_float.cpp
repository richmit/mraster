// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      test_float.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-07-09
 @brief     Make logically identical images, one 8-bit int and one double, and write both to TIFF files.@EOL
 @keywords  mraster
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

  make test_float && { rm test_float*.tiff; ./test_float.exe; tiffdump.exe test_floatF.tiff; tiffdump.exe test_floatI.tiff; }

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <vector>                                                        /* STL vector              C++11    */ 

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

  mjr::ramCanvasRGB64F theFltRamCanvas(1024, 1024);
  for(int x=0;x<theFltRamCanvas.getNumPixX();x++)
    for(int y=0;y<theFltRamCanvas.getNumPixY();y++) 
      theFltRamCanvas.drawPoint(x, y, mjr::ramCanvasRGB64F::colorType(x/1024.0, y/1024.0, 0.0));
  theFltRamCanvas.writeTIFFfile("test_floatF.tiff");

  mjr::ramCanvasRGB8b theIntRamCanvas(1024, 1024);
  for(int x=0;x<theIntRamCanvas.getNumPixX();x++)
    for(int y=0;y<theIntRamCanvas.getNumPixY();y++) 
      theIntRamCanvas.drawPoint(x, y, mjr::ramCanvasRGB8b::colorType((uint8_t)(x/4), (uint8_t)(y/4), (uint8_t)0));
  theIntRamCanvas.writeTIFFfile("test_floatI.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

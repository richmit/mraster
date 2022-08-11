// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color_interp_hsl_vs_rgb.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Illistrate the diffrence in interpolion in HSL vs RGB spaec.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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
 @filedetails

  In some cases, interpolating in HSL spaces can lead to an entirely different result from interpolating in RGB space.  This program illustrates on such
  example.  Note that in many of the most important cases, interpolating leads to the same results in both color spaces.

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <vector>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas(592, 1810, -2.0, 2, -2, 2);
  mjr::ramCanvas3c8b::colorType startColor("red");
  mjr::ramCanvas3c8b::colorType endColor("blue");
  mjr::ramCanvas3c8b::colorType aColor;

  std::vector<mjr::ramCanvas3c8b::colorType::colorSpaceEnum> colorSpaces { mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSL,
                                                                           mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSV,
                                                                           mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LCH,
                                                                           mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LAB,
                                                                           mjr::ramCanvas3c8b::colorType::colorSpaceEnum::XYZ,
                                                                           mjr::ramCanvas3c8b::colorType::colorSpaceEnum::RGB
                                                                         };
  for(int x=0; x<512; x++)
    theRamCanvas.drawLine(x,   0,  x,  250, aColor.interplColors(x/512.0, startColor, endColor));
  theRamCanvas.drawString("RGB", mjr::hershey::font::ROMAN_SL_SANSERIF, 532, (   0+ 250)/2, "red",  1, 20);

for(int j=1; j<1000; j++) {
  int i=0;
  for(auto cs : colorSpaces) {
    for(int x=0; x<512; x++) 
      theRamCanvas.drawLine(x, 260*(i+1), x, 260*(i+1)+250, aColor.interplColorSpace(cs, x/512.0, startColor, endColor));
    theRamCanvas.drawString(aColor.colorSpaceToString(cs), mjr::hershey::font::ROMAN_SL_SANSERIF, 532, 260*(i+1)+125, "red",  1, 20);
    i++;
  }
}
  std::chrono::duration<double> bmTime = std::chrono::system_clock::now() - startTime;
  std::cout << "BM Runtime " << bmTime.count() << " sec" << std::endl;


  std::cout << "Start Color (RGB) : " << startColor << std::endl;
  for(auto cs : colorSpaces) {
    auto tmp = startColor.rgb2colorSpace(cs);
    std::cout << "Start Color (" << startColor.colorSpaceToString(cs) << ") : " << tmp << std::endl;
  }

  std::cout << "End   Color (RGB) : " << endColor << std::endl;
  for(auto cs : colorSpaces) {
  auto tmp = endColor.rgb2colorSpace(cs);
    std::cout << "Start Color (" << endColor.colorSpaceToString(cs) << ") : " << tmp << std::endl;
  }

  theRamCanvas.writeTIFFfile("color_interp_hsl_vs_rgb.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

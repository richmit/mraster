// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      color_interp_hsl_vs_rgb.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Illistrate the diffrence in interpolion in HSL vs RGB spaec.@EOL
 @std       C++98
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

***************************************************************************************************************************************************************/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas(592, 1810, -2.0, 2, -2, 2);
  mjr::ramCanvas3c8b::colorType startColor("red");
  mjr::ramCanvas3c8b::colorType endColor("blue");
  mjr::ramCanvas3c8b::colorType aColor;
  std::tuple<double, double, double> tmp;

  for(int x=0; x<512; x++) {
    theRamCanvas.drawLine(x,   0,  x,  250, aColor.interplColors(                                                        x/512.0, startColor, endColor));
    theRamCanvas.drawLine(x, 260,  x,  510, aColor.interplColorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSL, x/512.0, startColor, endColor));
    theRamCanvas.drawLine(x, 520,  x,  770, aColor.interplColorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LAB, x/512.0, startColor, endColor));
    theRamCanvas.drawLine(x, 780,  x, 1030, aColor.interplColorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSV, x/512.0, startColor, endColor));
    theRamCanvas.drawLine(x, 1040, x, 1290, aColor.interplColorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::XYZ, x/512.0, startColor, endColor));
    theRamCanvas.drawLine(x, 1300, x, 1550, aColor.interplColorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::RGB, x/512.0, startColor, endColor));
    theRamCanvas.drawLine(x, 1560, x, 1810, aColor.interplColorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LCH, x/512.0, startColor, endColor));
  }

  theRamCanvas.drawString("RGB", mjr::hersheyFont::ROMAN_SL_SANSERIF, 532, (   0+ 250)/2, "red",  1, 20);
  theRamCanvas.drawString("HSL", mjr::hersheyFont::ROMAN_SL_SANSERIF, 532, ( 260+ 510)/2, "red",  1, 20);
  theRamCanvas.drawString("Lab", mjr::hersheyFont::ROMAN_SL_SANSERIF, 532, ( 520+ 770)/2, "red",  1, 20);
  theRamCanvas.drawString("HSV", mjr::hersheyFont::ROMAN_SL_SANSERIF, 532, ( 780+1030)/2, "red",  1, 20);
  theRamCanvas.drawString("XYZ", mjr::hersheyFont::ROMAN_SL_SANSERIF, 532, (1040+1290)/2, "red",  1, 20);
  theRamCanvas.drawString("rgb", mjr::hersheyFont::ROMAN_SL_SANSERIF, 532, (1300+1550)/2, "red",  1, 20);
  theRamCanvas.drawString("Lch", mjr::hersheyFont::ROMAN_SL_SANSERIF, 532, (1560+1810)/2, "red",  1, 20);

  std::cout << "Start Color (RGB) : " << startColor << std::endl;
  tmp = startColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::RGB);
  std::cout << "Start Color (rgb) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = startColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSL);
  std::cout << "Start Color (HSL) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = startColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSV);
  std::cout << "Start Color (HSV) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = startColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LAB);
  std::cout << "Start Color (Lab) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = startColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LCH);
  std::cout << "Start Color (Lch) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = startColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::XYZ);
  std::cout << "Start Color (XYZ) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;

  std::cout << "End   Color (RGB) : " << endColor << std::endl;
  tmp = endColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::RGB);
  std::cout << "End   Color (rgb) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = endColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSL);
  std::cout << "End   Color (HSL) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = endColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::HSV);
  std::cout << "End   Color (HSV) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = endColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LAB);
  std::cout << "End   Color (Lab) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = endColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::LCH);
  std::cout << "End   Color (Lch) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;
  tmp = endColor.rgb2colorSpace(mjr::ramCanvas3c8b::colorType::colorSpaceEnum::XYZ);
  std::cout << "End   Color (XYZ) : <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ", " << std::get<2>(tmp) << ">" << std::endl;

  theRamCanvas.writeTIFFfile("color_interp_hsl_vs_rgb.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}

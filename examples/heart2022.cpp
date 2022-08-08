// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      heart2022.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a heart for Valentines Day 2022.@EOL
 @keywords
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
********************************************************************************************************************************************************.H.E.**/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
double f(double x, double y) {
  return std::pow(x, 2) * std::pow(y, 3) - std::pow(std::pow(x, 2) + std::pow(y, 2) - 1, 3);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int x, y;
  double maxH = std::hypot(512, 512);
  mjr::ramCanvas3c8b theRamCanvas(1024, 1024, -2, 2, -2, 2);

  for(y=0;y<theRamCanvas.get_numYpix();y++)  
    for(x=0;x<theRamCanvas.get_numXpix();x++) {
      if(f(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y)) > 0) 
        theRamCanvas.drawPoint(x, y, "red");
      else
        theRamCanvas.drawPoint(x, y, mjr::color3c8b::csPLYquad::c(mjr::genLinMap(std::hypot(x-512, y-512), maxH, 0.0, 0.5, 1.0)));
    }

  theRamCanvas.drawString("MWU. M", mjr::hershey::font::ROMAN_SL_SANSERIF, 900, 90, "red",  1, 20); 
  theRamCanvas.drawString("2022  ", mjr::hershey::font::ROMAN_SL_SANSERIF, 900, 60, "red",  1, 20); 
  theRamCanvas.drawString("    -m", mjr::hershey::font::ROMAN_SL_SANSERIF, 900, 30, "red",  1, 20); 

  theRamCanvas.writeTIFFfile("heart2022.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}

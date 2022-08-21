// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      dlaSeed.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Produces seed images for diffusion limited aggregation (DLA) simulations.@EOL
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
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas(7680/8, 4320/8, -2.2, 2.2, -2.2, 2.2);

  theRamCanvas.clrCanvas(mjr::ramCanvas3c8b::colorType(255, 0, 0));
  theRamCanvas.drawLine(                            2,                            2, theRamCanvas.getNumPixX()-3,                            2, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.drawLine(                            2, theRamCanvas.getNumPixY()-3, theRamCanvas.getNumPixX()-3, theRamCanvas.getNumPixY()-3, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.drawLine(                            2,                            2,                            2, theRamCanvas.getNumPixY()-3, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.drawLine( theRamCanvas.getNumPixX()-3,                            2, theRamCanvas.getNumPixX()-3, theRamCanvas.getNumPixY()-3, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.writeTIFFfile("dlaSeed_border.tiff");

  theRamCanvas.clrCanvas(mjr::ramCanvas3c8b::colorType(255, 0, 0));
  theRamCanvas.drawPoint(theRamCanvas.getNumPixX()/2, theRamCanvas.getNumPixY()/2, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.writeTIFFfile("dlaSeed_center.tiff");

  theRamCanvas.clrCanvas(mjr::ramCanvas3c8b::colorType(255, 0, 0));
  theRamCanvas.drawCircle( theRamCanvas.getNumPixX()/2, theRamCanvas.getNumPixY()/2, theRamCanvas.getNumPixY()/4,   mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.drawCircle( theRamCanvas.getNumPixX()/2, theRamCanvas.getNumPixY()/2, theRamCanvas.getNumPixY()/2-3, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.drawCircle( theRamCanvas.getNumPixX()/2, theRamCanvas.getNumPixY()/2, theRamCanvas.getNumPixX()/2-3, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.drawCircle( theRamCanvas.getNumPixX()/2, theRamCanvas.getNumPixY()/2, (theRamCanvas.getNumPixY()+theRamCanvas.getNumPixX())/4-3, mjr::ramCanvas3c8b::colorType(0, 0, 255));
  theRamCanvas.writeTIFFfile("dlaSeed_circles.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

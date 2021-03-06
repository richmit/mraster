// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      dlaSeed.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Produces seed images for diffusion limited aggregation (DLA) simulations.@EOL
 @std       C++11
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(int argc, char *argv[]) {
  mjr::ramCanvas3c8b theRamCanvas(7680/2, 4320/2, -2.2, 2.2, -2.2, 2.2);

  theRamCanvas.clrCanvas(mjr::color3c8b(255, 0, 0));
  theRamCanvas.drawLine(                            2,                            2, theRamCanvas.get_numXpix()-3,                            2, mjr::color3c8b(0, 0, 255));
  theRamCanvas.drawLine(                            2, theRamCanvas.get_numYpix()-3, theRamCanvas.get_numXpix()-3, theRamCanvas.get_numYpix()-3, mjr::color3c8b(0, 0, 255));
  theRamCanvas.drawLine(                            2,                            2,                            2, theRamCanvas.get_numYpix()-3, mjr::color3c8b(0, 0, 255));
  theRamCanvas.drawLine( theRamCanvas.get_numXpix()-3,                            2, theRamCanvas.get_numXpix()-3, theRamCanvas.get_numYpix()-3, mjr::color3c8b(0, 0, 255));
  theRamCanvas.writeTIFFfile("dlaSeed_border.tiff");
  
  theRamCanvas.clrCanvas(mjr::color3c8b(255, 0, 0));
  theRamCanvas.drawPoint(theRamCanvas.get_numXpix()/2, theRamCanvas.get_numYpix()/2, mjr::color3c8b(0, 0, 255));
  theRamCanvas.writeTIFFfile("dlaSeed_center.tiff");

  theRamCanvas.clrCanvas(mjr::color3c8b(255, 0, 0));
  theRamCanvas.drawCircle( theRamCanvas.get_numXpix()/2, theRamCanvas.get_numYpix()/2, theRamCanvas.get_numYpix()/4,   mjr::color3c8b(0, 0, 255));
  theRamCanvas.drawCircle( theRamCanvas.get_numXpix()/2, theRamCanvas.get_numYpix()/2, theRamCanvas.get_numYpix()/2-3, mjr::color3c8b(0, 0, 255));
  theRamCanvas.drawCircle( theRamCanvas.get_numXpix()/2, theRamCanvas.get_numYpix()/2, theRamCanvas.get_numXpix()/2-3, mjr::color3c8b(0, 0, 255));
  theRamCanvas.drawCircle( theRamCanvas.get_numXpix()/2, theRamCanvas.get_numYpix()/2, (theRamCanvas.get_numYpix()+theRamCanvas.get_numXpix())/4-3, mjr::color3c8b(0, 0, 255));
  theRamCanvas.writeTIFFfile("dlaSeed_circles.tiff");
}

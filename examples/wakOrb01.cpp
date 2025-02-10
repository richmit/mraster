// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      wakOrb01.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Wackey orbit map 01.@EOL
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
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathIVL.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    IMXSIZ = 7680/1;
  const int    IMYSIZ = 7680/1;
  const int    steps  = 5;

  mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -15, 15, -15, 15);
  theRamCanvas.clrCanvasToBlack();

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    if ((y%500)==0)
      std::cout << y << std::endl;
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      double px = theRamCanvas.int2realX(x);
      double py = theRamCanvas.int2realY(y);
      for(int i=0; i<steps; i++) {
        double pxNew = std::sin( 1.50503*py + 1.709360) - std::cos(-1.44118*px + 1.794210);
        double pyNew = std::sin(-1.23281*px + 1.893750) - std::cos( 1.78607*py - 1.38227);
        px = pxNew;
        py = pyNew;
      }
      double r = mjr::math::ivl::wrapCO(px, 1.0);
      double b = mjr::math::ivl::wrapCO(py, 1.0);
      double g = mjr::math::ivl::wrapCO(atan2(px,py)/3.29, 1.0);
      theRamCanvas.getPxColorRefNC(x, y).setChansRGB_dbl(r, g, b);
    }
  }
  theRamCanvas.writeTIFFfile("wakOrb01.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

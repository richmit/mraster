// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      heartFrac.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a grayscale heart fractal.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2015,2018 Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  Notes:

   \[ x_{n+1} = 2 x_n y_n + Re(c) 
      y_{n+1} = \vert y_n\vert - \vert x_n\vert + Im(c) \]

  Notes:
    - Uses a deep, greyscale image.
    - Outputs a TIFF
    - Optimization to avoid the main cardioid boundry and period 2 disk
    - Uses an automatic histogram streach to expand the visual contract.   I leave this step off when using Fiji.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

typedef mjr::ramCanvas3c8b rct;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  int width  = 3440*8;
  int height = 1400*8;
  double ar  = static_cast<double>(width) / static_cast<double>(height);
  rct theRamCanvas(width, height, -1.2*ar, 1.2*ar, -1.2, 1.2);
  const int NUMITR = 50;

# pragma omp parallel for schedule(static,1)
  for(rct::coordIntType y=0; y<theRamCanvas.getNumPixY(); y++) {
    for(rct::coordIntType x=0; x<theRamCanvas.getNumPixX(); x++) {
      rct::coordFltType cr = theRamCanvas.int2realX(x);
      rct::coordFltType ci = theRamCanvas.int2realY(y);
      rct::coordFltType zr = 0;
      rct::coordFltType zi = 0;
      int count = 0;
      while ((std::abs(zr) < 50) && (std::abs(zi) < 50) && (count < NUMITR)) {
        rct::coordFltType tmp = 2 * zr * zi + cr;
        zi = std::abs(zi) - std::abs(zr) + ci;
        zr = tmp;
        count++;
      }
      if(count < NUMITR)
        theRamCanvas.drawPoint(x, y, rct::colorType::csCCsumBRG::c(static_cast<rct::colorType::csIntType>(count*20))); //csCCfractal0RYBCW
    }
  }
  theRamCanvas.scaleDownMean(9);
  theRamCanvas.drawString("MWU. M", mjr::hershey::font::ROMAN_SL_SANSERIF, theRamCanvas.getNumPixX()-130, 200-30, "white",  1, 20); 
  theRamCanvas.drawString("2025  ", mjr::hershey::font::ROMAN_SL_SANSERIF, theRamCanvas.getNumPixX()-130, 200-60, "white",  1, 20); 
  theRamCanvas.drawString("    -m", mjr::hershey::font::ROMAN_SL_SANSERIF, theRamCanvas.getNumPixX()-130, 200-90, "white",  1, 20); 
  theRamCanvas.writeTIFFfile("heartFrac.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

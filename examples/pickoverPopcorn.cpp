// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      pickoverPopcorn.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw Pickover Popcorn Fractals.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/PickoverPopcorn/index.html
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

  Fractals inspired by the book "Computers, Pattern, Chaos and Beauty" by Clifford A. Pickover

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    IMXSIZ = 7680/2;
  const int    IMYSIZ = 4320/2;
  const int    NUMITR = 100;
  mjr::ramCanvas1c16b hstRamCanvas(IMXSIZ, IMYSIZ, -4.0, 4.0, -2.25, 2.25);

  const decltype(hstRamCanvas)::coordIntType spanx  = 1;
  const decltype(hstRamCanvas)::coordIntType spany  = 1;
  const decltype(hstRamCanvas)::coordFltType h      = 0.05;
  const decltype(hstRamCanvas)::coordFltType a      = 3.0;
  const decltype(hstRamCanvas)::coordFltType b      = 3.0;

  for(decltype(hstRamCanvas)::coordIntType y=0;y<hstRamCanvas.getNumPixY();y+=spany) {
    if ((y%100)==0)
      std::cout << y << std::endl;
    for(decltype(hstRamCanvas)::coordIntType x=0;x<hstRamCanvas.getNumPixX();x+=spanx) {
      decltype(hstRamCanvas)::coordFltType zx = hstRamCanvas.int2realX(x);
      decltype(hstRamCanvas)::coordFltType zy = hstRamCanvas.int2realY(y);
      for(int i=0; i<NUMITR; i++) {
        decltype(hstRamCanvas)::coordFltType tmpx = zx - h * std::sin(zy + std::tan(a * zy));
        decltype(hstRamCanvas)::coordFltType tmpy = zy - h * std::sin(zx + std::tan(b * zx));
        zx = tmpx;
        zy = tmpy;
        hstRamCanvas.incPxChan(zx, zy);
      }
    }
  }
  hstRamCanvas.writeTIFFfile("pickoverPopcornCNT.tiff");

  hstRamCanvas.applyHomoPixTfrm(&decltype(hstRamCanvas)::colorType::tfrmMultClamp, 10);
  hstRamCanvas.applyHomoPixTfrm(&decltype(hstRamCanvas)::colorType::tfrmMin, mjr::color3c8b::csCCfractal0RYBCW::numC-1);
  hstRamCanvas.autoHistStrech();

  // This is *identical* to what we did in sic.cpp -- just way shorter.
  hstRamCanvas.writeTIFFfile("pickoverPopcornCOL.tiff", 
                             mjr::ramCanvasPixelFilter::ColorSchemeOnChan<decltype(hstRamCanvas), mjr::color3c8b, mjr::color3c8b::csCCfractal0RYBCW>(hstRamCanvas));

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

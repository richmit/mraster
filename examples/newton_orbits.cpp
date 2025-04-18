// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      newton_orbits.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Newton Fractical -- color by root and max modulus.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/newton/index.html#orbits
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  constexpr int MaxCount = 255;
  constexpr double Tol = .0001;
  constexpr int IMGSIZ = 7680/1;
  std::complex<double> r1( 1.0,                        0.0);
  std::complex<double> r2(-0.5,  sin(2*std::numbers::pi/3));
  std::complex<double> r3(-0.5, -sin(2*std::numbers::pi/3));
  mjr::ramCanvas3c16b theRamCanvas(IMGSIZ, IMGSIZ, -2.15, 1.85, -2.0, 2.0);
  std::complex<double> orbit [MaxCount];

  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      std::complex<double> z = theRamCanvas.int2real(x, y);
      int  count = 0;
      while((count < MaxCount) && (abs(z)>Tol) && (abs(z-r1) >= Tol) && (abs(z-r2) >= Tol) && (abs(z-r3) >= Tol)) {
        z = z-(z*z*z-1.0)/(z*z*3.0);
        orbit[count] = z;
        count++;
      }
      if(abs(z-r1) <= Tol)
        for(int i=0; i<count; i++)
          theRamCanvas.incPxChan<0>(orbit[i]);
      else if(abs(z-r2) <= Tol)
        for(int i=0; i<count; i++)
          theRamCanvas.incPxChan<1>(orbit[i]);
      else if(abs(z-r3) <= Tol)
        for(int i=0; i<count; i++)
          theRamCanvas.incPxChan<2>(orbit[i]);
    }
  }
  theRamCanvas.applyHomoPixTfrm(&decltype(theRamCanvas)::colorType::tfrmLn, 11271.0);
  theRamCanvas.autoMaxHistStrechRGB();
  theRamCanvas.writeTIFFfile("newton_orbits_col.tiff");

  auto tf1 = mjr::ramCanvasPixelFilter::MonoIntensity<decltype(theRamCanvas), mjr::colChanI8>(theRamCanvas);
  auto tf2 = mjr::ramCanvasPixelFilter::Rotate90CW<decltype(tf1)>(tf1);
  theRamCanvas.writeTIFFfile("newton_orbits_mon.tiff", tf2);

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

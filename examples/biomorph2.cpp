// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      biomorph2.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a corner centered biomorph fractal nice for a desktop background image.@EOL
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b::colorType ct;
typedef ct::csIntType cit;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int NUMITR = 100;
  const int CSIZE  = 7680;
  const int LIM    = 4;

  mjr::ramCanvas3c8b theRamCanvasA(CSIZE, CSIZE, -1.0, 1.4, -1.0, 1.4);
  mjr::ramCanvas3c8b theRamCanvasE(CSIZE, CSIZE, -1.0, 1.4, -1.0, 1.4);
  mjr::ramCanvas3c8b theRamCanvasK(CSIZE, CSIZE, -1.0, 1.4, -1.0, 1.4);
  mjr::ramCanvas3c8b theRamCanvasL(CSIZE, CSIZE, -1.0, 1.4, -1.0, 1.4);
  mjr::ramCanvas3c8b theRamCanvasN(CSIZE, CSIZE, -1.0, 1.4, -1.0, 1.4);

  for(int y=0;y<theRamCanvasA.getNumPixY();y++) {
    if((y%(CSIZE/10))==0)
      std::cout << " LINE: " << y << "/" << CSIZE << std::endl;
    for(int x=0;x<theRamCanvasA.getNumPixX();x++) {
      std::complex<double> z(theRamCanvasA.int2realX(x), theRamCanvasA.int2realY(y));
      int count = 0; 
      while( ((std::abs(std::real(z))<LIM) || (std::abs(std::imag(z))<LIM)) && (count<NUMITR) ) {
        z=std::sin(z)+std::complex<double>(1.0, 1.0);
        count++;
      }
      if(count < NUMITR) {
        // A
        theRamCanvasA.drawPoint(x, y, ct::csCColdeRainbow::c(static_cast<cit>(count*500)));
        // E
        if(std::abs(std::real(z))<std::abs(std::imag(z)))
          theRamCanvasE.drawPoint(x, y, ct("red"));
        else
          theRamCanvasE.drawPoint(x, y, ct("blue"));
        // K
        theRamCanvasK.drawPoint(x, y, ct::csCColdeRainbow::c(static_cast<cit>((std::arg(z)+3.14)*255)));
        // L
        if(std::abs(std::real(z))<std::abs(std::imag(z)))
          theRamCanvasL.drawPoint(x, y, ct::csCCu0R::c(mjr::math::ivl::clamp(static_cast<cit>(std::abs(std::real(z))*15), ct::csCCu0R::numC-1)));
        else
          theRamCanvasL.drawPoint(x, y, ct::csCCu0B::c(mjr::math::ivl::clamp(static_cast<cit>(std::abs(std::imag(z))*15), ct::csCCu0B::numC-1)));
      }
    }
  }
  theRamCanvasA.writeTIFFfile("biomorph2A.tiff");
  theRamCanvasE.writeTIFFfile("biomorph2E.tiff");
  theRamCanvasK.writeTIFFfile("biomorph2K.tiff");
  theRamCanvasL.writeTIFFfile("biomorph2L.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

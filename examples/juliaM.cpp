// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_simple.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Create a Julia set movie.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/julia/index.html
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

  Moves $c$ around a circle just a bit larger than the period 2 disk.  A GIF may be rendered from the frames like this:

       time convert -delay 1 -loop 0 -dispose previous juliaM_???.tiff juliaM.gif
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b::colorType ct;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    NUMITR = 1024;
  const double MAXZ   = 4.0;
  const int    NUMFRM = 24*16;
  const int    IMXSIZ = 7680/8;
  const int    IMYSIZ = 7680/8;
  const double ANGMIN = 0.0;
  const double ANGMAX = std::numbers::pi*2;

  for(int frame=0; frame<NUMFRM; frame++) {
    mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -2.2, 2.2, -2.2, 2.2);
    std::cout << "Frame: " << frame << std::endl;
    double angle = frame*(ANGMAX-ANGMIN)/NUMFRM+ANGMIN;
    std::complex<double> c = std::complex<double>(std::cos(angle), std::sin(angle)) * 0.35 - std::complex<double>(0.0, -1.0);
    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> z = theRamCanvas.int2real(x, y);
        int count = 0;
        while((std::norm(z)<MAXZ) && (count<=NUMITR)) {
          z=std::pow(z, 2) + c;
          count++;
        }
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, ct::csCColdeFireRamp::c(static_cast<ct::csIntType>(count*20)));
      }
    }
    theRamCanvas.writeTIFFfile("juliaM_" + mjr::math::str::fmt_int(frame, 3, '0') + ".tiff");
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

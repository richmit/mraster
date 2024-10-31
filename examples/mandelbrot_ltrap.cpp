// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_ltrap.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Mandelbrot set with an Mandelbrot curve as an orbert trap.@EOL
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
double lp(std::complex<double> z, int n) {
  std::complex<double> lpv(0.0, 0.0);
  for(int i=0; i<n; i++)
    lpv = std::pow(lpv, 2) + z;
  return std::abs(lpv) - 2;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    IMGSIZ = 7680;
  const int    MAXITR = 1024;
  const double MAXZSQ = 4.0;
  const int    NUMFRM = 10;

# pragma omp parallel for schedule(static,1)
  for(int frame=1;frame<=NUMFRM;frame++) {
#   pragma omp critical
    std::cout << "Frame " << frame << " of " << NUMFRM << std::endl;
    mjr::ramCanvas3c8b theRamCanvas(IMGSIZ, IMGSIZ, -2.2, 0.8, -1.5, 1.5);
    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> c = theRamCanvas.int2real(x, y);
        std::complex<double> z(0.0, 0.0);
        double minDval = theRamCanvas.getCanvasWidD();
        double minDsgn = 0;
        int count = 0; 
        while((std::norm(z)<MAXZSQ) && (count<=MAXITR)) {
          z=std::pow(z, 2) + c;
          double ld = lp(z, frame);
          if (std::abs(ld) < minDval) {
            minDval = std::abs(ld);
            minDsgn = (ld > 0 ? 1 : -1);
          }
          count++;
        }
        if(count < MAXITR) {
          ct::csIntType csIdx = static_cast<ct::csIntType>(std::log(1+minDval)*100);
          if (minDsgn > 0)
            theRamCanvas.drawPoint(x, y, ct::csCCfractalYB::c(csIdx));
          else
            theRamCanvas.drawPoint(x, y, ct::csCCfractalYR::c(csIdx));
        }
      }
    }
    theRamCanvas.writeTIFFfile("mandelbrot_ltrap_" + mjr::math::str::fmt_int(frame, 2, '0') + ".tiff");
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

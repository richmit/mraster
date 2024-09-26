// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      phoenixM.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Create a phoenix Julia set movie.@EOL
 @std       C++20
 @see       
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
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    WIDTH  = 1920/2;
  const int    HEIGHT = 1920/2;
  const int    NUMITR = 500;
  const double MAXZ   = 4.0;

  const int    NUMFRM = 24*2;
  const double ANGMIN = 0.0;
  const double ANGMAX = std::numbers::pi*2;
  const double RADIUS = 0.0001;

# pragma omp parallel for schedule(static,1)
  for(int frame=0; frame<NUMFRM; frame++) {
#   pragma omp critical
    std::cout << "Frame: " << frame << std::endl;
    double angle = frame*(ANGMAX-ANGMIN)/NUMFRM+ANGMIN;

    const std::complex<double> c(0.566700, 0.00000);
    const std::complex<double> p(-0.50000+RADIUS*std::cos(angle),  0.00000+0*RADIUS*std::sin(angle));
    mjr::ramCanvas3c8b theRamCanvas(WIDTH, HEIGHT, -0.75, -0.5, 0.13, 0.32);

    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> z1(theRamCanvas.int2realY(y), theRamCanvas.int2realX(x));
        std::complex<double> z2(0.0, 0.0);
        int count = 0;
        while((std::norm(z1)<MAXZ) && (count<=NUMITR)) {
          std::complex<double> z = z1*z1+c+p*z2;
          z2 = z1;
          z1 = z;
          count++;
        }
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, ct::csCCfractal0RYBCW::c(static_cast<ct::csIntType>(count*10)));
      }
    }
    theRamCanvas.writeTIFFfile("phoenixM_" + mjr::fmtInt(frame, 2, '0') + ".tiff");
#   pragma omp critical
    std::cout << "FRAME(" << frame <<  "): " << "DONE" << std::endl;
  }

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

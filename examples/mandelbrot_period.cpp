// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_period.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Produce several images related to the period/cycle structure of the Mandelbrot set.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2015,2021 Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  Produce several images related to the period/cycle structure of the Mandelbrot set:
    - mandelbrot_periodCYC.tiff: Period -- i.e. the length of the cycle of the orbit.
    - mandelbrot_periodSTB.tiff: Number of iterations required for the cycle to be apparent.
    - mandelbrot_periodESC.tiff: For divergent points, the number of iterations required for |z|>2.
    - mandelbrot_period.tiff:    A composite, colorized image showing period and divergent points using a nice color scheme.
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

typedef mjr::ramCanvas1c16b rc16;
typedef mjr::ramCanvas3c8b  rc8;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  rc8::colorType aColor;

  const rc16::colorChanType  NUMITR   = 4096;
  const int                  CSIZE    = 7680/2;
  const double               MAXZSQ   = 4.0;
  rc8  theRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);
  rc16 perRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // Period -- 0 => not a periodic point
  rc16 stbRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // Number of iterations period structure was stable
  rc16 escRamCanvas(CSIZE, CSIZE, -2.1, 0.75,  1.4, 1.4);  // Iteration count for cases where |z|>2

#pragma omp parallel for schedule(static,1)
  for(int y=0;y<perRamCanvas.getNumPixY();y++) {
    for(int x=0;x<perRamCanvas.getNumPixX();x++) {
      std::complex<double> c(perRamCanvas.int2realX(x), perRamCanvas.int2realY(y));
      std::complex<double> z(0.0, 0.0);
      std::vector<std::complex<double>> lastZs(NUMITR);
      rc16::colorChanType count = 0;
      while((std::norm(z)<MAXZSQ) && (count<NUMITR)) {
        z=std::pow(z, 2) + c;
        lastZs[count] = z;
        count++;
      }
      if (count == NUMITR) {  // Hit iteration limit
        for(rc16::colorChanType period=1; period<(NUMITR-2); period++) {
          if(std::abs(z-lastZs[NUMITR-1-period])<1e-4) {
            perRamCanvas.drawPoint(x, y, period);
            for(rc16::colorChanType stab=0; stab<(NUMITR-period); stab++) {
              if(std::abs(lastZs[NUMITR-1-stab]-lastZs[NUMITR-1-period-stab])>1e-6) {   
                stbRamCanvas.drawPoint(x, y, NUMITR-stab);
                break;
              }
            }
            break;
          }
        }
      } else {                // Divergence detected because |z|>2
        escRamCanvas.drawPoint(x, y, count);
      }
    }
    std::cout << CSIZE << "/" << y << std::endl;
  }

  perRamCanvas.writeTIFFfile("mandelbrot_periodCYC.tiff");
  stbRamCanvas.writeTIFFfile("mandelbrot_periodSTB.tiff");
  escRamCanvas.writeTIFFfile("mandelbrot_periodOUT.tiff");

  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      if (perRamCanvas.getPxColorNC(x, y).getC0() > 0) {
        if (perRamCanvas.getPxColorNC(x, y).getC0() > (rc8::colorType::csFPcircular24::numC-1)) {
          theRamCanvas.drawPoint(x, y, 255);
        } else {
          theRamCanvas.drawPoint(x, y, rc8::colorType::csFPcircular24::c(perRamCanvas.getPxColorNC(x, y).getC0()));
        }
      } else {
        rc8::csFltType c = static_cast<rc8::csFltType>(escRamCanvas.getPxColorNC(x, y).getC0()) / NUMITR;
        theRamCanvas.drawPoint(x, y, rc8::colorType::csCCdiag01::c(c*30));
      }
    }
  }

  theRamCanvas.writeTIFFfile("mandelbrot_period.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

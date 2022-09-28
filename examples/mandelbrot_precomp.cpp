// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_precomp.cpp
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

   - mandelbrot_precompPER.tiff -- Period of the point.  0 means no period known.
   - mandelbrot_precompSTB.tiff -- Stability of the period.  0 means stability unknown.
   - mandelbrot_precomps.tiff -- Number of iterations required to escape.  0 means it didn't escape.
   - mandelbrot_precompNOE.tiff -- Points that didn't escape -- the mandelbrot set.  255
   - mandelbrot_precomp.tiff    -- A composite of the above with a few notable period regions labeled.

  On my 2022 vintage Intel i7, this takes about 30min to run.  The runtime is directly proportional to the NUMITR, so lower that number if you want it to go
  faster.  Lowering NUMITR will have cause more non-escaping points to not have a known period -- the green points in

********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

typedef mjr::ramCanvas1c16b rcM16;
typedef mjr::ramCanvas1c8b rcM8;
typedef mjr::ramCanvas3c8b  rcC8;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  rcC8::colorType aColor;

  const rcM16::colorChanType NUMITR   = 65530;
  const int                  CSIZE    = 7680;
  const double               MAXZSQ   = 4.1;
  rcC8  theRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);
  rcM16 perRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // Period -- 0 => not a periodic point
  rcM16 stbRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // Number of iterations period structure was stable
  rcM8  noeRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // No escape: Exceeded iteration count
  rcM16 escRamCanvas(CSIZE, CSIZE, -2.1, 0.75,  1.4, 1.4);  // Excaped: Iteration count for cases where |z|>2

#pragma omp parallel for schedule(static,1)
  for(int y=0;y<perRamCanvas.getNumPixY();y++) {
    for(int x=0;x<perRamCanvas.getNumPixX();x++) {
      std::complex<double> c(perRamCanvas.int2realX(x), perRamCanvas.int2realY(y));
      std::complex<double> z(0.0, 0.0);
      std::vector<std::complex<double>> lastZs(NUMITR);
      rcM16::colorChanType count = 1;
      while((std::norm(z)<MAXZSQ) && (count<NUMITR)) {
        z=std::pow(z, 2) + c;
        lastZs[count] = z;
        count++;
      }
      if (count == NUMITR) {  // Hit iteration limit
        noeRamCanvas.drawPoint(x, y, "white");
        for(rcM16::colorChanType period=1; period<(NUMITR-2); period++) {
          if(std::abs(z-lastZs[NUMITR-1-period])<1e-4) { // Found an identical point 'period' away.
            rcM16::colorChanType stab;
            for(stab=0; stab<(NUMITR-period); stab++) {
              if(std::abs(lastZs[NUMITR-1-stab]-lastZs[NUMITR-1-period-stab])>1e-6) {   
                break;
              }
            }
            if (stab > period) { // Definatly found a cycle
              stbRamCanvas.drawPoint(x, y, NUMITR-stab);
              perRamCanvas.drawPoint(x, y, period);
              break;
            }
          }
        }
      } else {                // Divergence detected because |z|>2
        escRamCanvas.drawPoint(x, y, count);
      }
    }
    std::cout << CSIZE << "/" << y << std::endl;
  }

  perRamCanvas.writeTIFFfile("mandelbrot_precompPER.tiff");
  stbRamCanvas.writeTIFFfile("mandelbrot_precompSTB.tiff");
  escRamCanvas.writeTIFFfile("mandelbrot_precompESC.tiff");
  noeRamCanvas.writeTIFFfile("mandelbrot_precompNOE.tiff");

  int numConNoCyc = 0;
  int numCyc      = 0;
  int numEsc      = 0;
  int numPts      = 0;
  int maxPer      = 0;
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      auto period = perRamCanvas.getPxColorNC(x, y).getC0();
      if (period > maxPer)
        maxPer = period;
      if (period > 0) {
        if (period > (rcC8::colorType::csCBDark2::maxNumC-1)) {
          theRamCanvas.drawPoint(x, y, "red");
        } else {
          theRamCanvas.drawPoint(x, y, rcC8::colorType::csCBDark2::c(period));
        }
        numCyc++;
      } else {
        if (noeRamCanvas.getPxColorNC(x, y).getC0() > 0) {
          theRamCanvas.drawPoint(x, y, "green");
          numConNoCyc++;
        } else {
          rcC8::csFltType c = static_cast<rcC8::csFltType>(escRamCanvas.getPxColorNC(x, y).getC0()) / NUMITR;
          theRamCanvas.drawPoint(x, y, rcC8::colorType::csCCdiag01::c(c*30));
          numEsc++;
        }
      }
      numPts++;
    }
  }
  theRamCanvas.drawString("1", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1500,  0.0000, "black", 6.0, 20);
  theRamCanvas.drawString("2", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.0000,  0.0000, "black", 6.0, 20);

  theRamCanvas.drawString("3", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1200,  0.7400, "black", 6.0, 20);
  theRamCanvas.drawString("3", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1200, -0.7400, "black", 6.0, 20);
  theRamCanvas.drawString("3", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.758,   0.0000, "black", 1.0, 20);

  theRamCanvas.drawString("4", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.3100,  0.0000, "black", 6.0, 20);
  theRamCanvas.drawString("4", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.2800,  0.5320, "black", 6.0, 20);
  theRamCanvas.drawString("4", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.2800, -0.5320, "black", 6.0, 20);

  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.5060, -0.5620, "black", 4.0, 20);
  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3780, -0.3370, "black", 4.0, 20);
  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.5060,  0.5620, "black", 4.0, 20);
  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3780,  0.3370, "black", 4.0, 20);

  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3890, -0.2150, "black", 2.0, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1140, -0.8620, "black", 4.0, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.1370, -0.2390, "black", 4.0, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3890,  0.2150, "black", 2.0, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1140,  0.8620, "black", 4.0, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.1370,  0.2390, "black", 4.0, 20);

  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.6220, -0.4240, "black", 2.0, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.1210, -0.6100, "black", 2.0, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3760, -0.1440, "black", 1.0, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.6220,  0.4240, "black", 2.0, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.1210,  0.6100, "black", 2.0, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3760,  0.1440, "black", 1.0, 20);

  theRamCanvas.writeTIFFfile("mandelbrot_precomp.tiff");

  std::cout << "numConNoCyc ... " << numConNoCyc        << std::endl;
  std::cout << "numCyc ........ " << numCyc             << std::endl;
  std::cout << "numInSet ...... " << numConNoCyc+numCyc << std::endl;
  std::cout << "numEsc ........ " << numEsc             << std::endl;
  std::cout << "numPts ........ " << numPts             << std::endl;
  std::cout << "maxPer ........ " << maxPer             << std::endl;

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

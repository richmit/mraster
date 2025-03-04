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

  On my 2022 vintage Intel i7, this takes about 30min to run.  The runtime is directly proportional to the MAXITR, so lower that number if you want it to go
  faster.  Lowering MAXITR will result in more non-escaping points to not have a known period.

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas1c16b rcCNT;  // for counts!
typedef mjr::ramCanvas1c8b  rcM8;
typedef mjr::ramCanvas3c8b  rcC8;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  rcC8::colorType aColor;

  const rcCNT::colorChanType MAXITR   = rcCNT::colorType::maxChanVal/1 - 2;
  const int                  MCSIZE   = 7680;
  const int                  CSIZEF   = 1;
  const int                  CSIZE    = MCSIZE/CSIZEF;
  const double               MAXZSQ   = 4.0;
  const double               MAXZSQU  = MAXZSQ + 0.1;
  rcC8  theRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);
  rcCNT perRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // Period -- 0 => not a periodic point
  rcCNT stbRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // Number of iterations period structure was stable
  rcM8  noeRamCanvas(CSIZE, CSIZE, -2.1, 0.75, -1.4, 1.4);  // No escape: Exceeded iteration count
  rcCNT escRamCanvas(CSIZE, CSIZE, -2.1, 0.75,  1.4, 1.4);  // Excaped: Iteration count for cases where |z|>2

#pragma omp parallel for schedule(static,1)
  for(int y=0;y<perRamCanvas.getNumPixY();y++) {
    rcCNT::colorChanType maxCheckpointITR = 0;
    double meanCheckpointITR = 0;
    std::vector<std::complex<double>> lastZs(MAXITR);
    std::chrono::time_point<std::chrono::system_clock> rowStartTime = std::chrono::system_clock::now();

    for(int x=0;x<perRamCanvas.getNumPixX();x++) {
      std::complex<double> c(perRamCanvas.int2realX(x), perRamCanvas.int2realY(y));
      std::complex<double> z(0.0, 0.0);
      rcCNT::colorChanType count = 1;
      bool seekingUnderstanding = true;
      rcCNT::colorChanType checkpointITR = 1024*8;

      while(seekingUnderstanding) {
        if ((MAXITR - checkpointITR) < checkpointITR)
          checkpointITR = MAXITR;
        else
          checkpointITR *= 2;

        if (maxCheckpointITR < checkpointITR)
          maxCheckpointITR = checkpointITR;

        while((std::norm(z)<MAXZSQU) && (count<checkpointITR)) {
          z=std::pow(z, 2) + c;
          lastZs[count] = z;
          count++;
        }

        if (std::norm(z)>MAXZSQ) { // Escaped
          escRamCanvas.drawPoint(x, y, count);
          seekingUnderstanding = false;
        } else { // no escape.  Perhaps a cycle?
          for(rcCNT::colorChanType period=1; period<(checkpointITR-2); period++) {
            if(std::abs(z-lastZs[checkpointITR-1-period])<1e-7) { // Found an identical point 'period' away.
              rcCNT::colorChanType stab;
              for(stab=0; stab<(checkpointITR-period); stab++) {
                if(std::abs(lastZs[checkpointITR-1-stab]-lastZs[checkpointITR-1-period-stab])>1e-7) {   
                  break;
                }
              }
              if (stab > period) { // Definatly found a cycle
                stbRamCanvas.drawPoint(x, y, checkpointITR-stab);
                perRamCanvas.drawPoint(x, y, period);
                noeRamCanvas.drawPoint(x, y, "white");
                seekingUnderstanding = false;
                break;
              }
            }
          }
          if (seekingUnderstanding && (checkpointITR == MAXITR)) { // Didn't escape.  No cycle.  No more time.
            noeRamCanvas.drawPoint(x, y, "white");
            seekingUnderstanding = false;
            break;
          }
        }
      }
      meanCheckpointITR += checkpointITR / static_cast<double>(CSIZE);

    }
    std::chrono::duration<double> rowRunTime = std::chrono::system_clock::now() - rowStartTime;
    std::cout << "my: " << CSIZE << " y: " << y << " max: " << maxCheckpointITR << " mean: " << meanCheckpointITR << " secs: " << rowRunTime.count() << std::endl;
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
          rcC8::csFltType c = static_cast<rcC8::csFltType>(escRamCanvas.getPxColorNC(x, y).getC0()) / MAXITR;
          theRamCanvas.drawPoint(x, y, rcC8::colorType::csCCdiag01::c(c*30));
          numEsc++;
        }
      }
      numPts++;
    }
  }
  theRamCanvas.drawString("1", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1500,  0.0000, "black", 6.0/CSIZEF, 20);
  theRamCanvas.drawString("2", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.0000,  0.0000, "black", 6.0/CSIZEF, 20);
                                                                                                    
  theRamCanvas.drawString("3", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1200,  0.7400, "black", 6.0/CSIZEF, 20);
  theRamCanvas.drawString("3", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1200, -0.7400, "black", 6.0/CSIZEF, 20);
  theRamCanvas.drawString("3", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.758,   0.0000, "black", 1.0/CSIZEF, 20);
                                                                                                    
  theRamCanvas.drawString("4", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.3100,  0.0000, "black", 6.0/CSIZEF, 20);
  theRamCanvas.drawString("4", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.2800,  0.5320, "black", 6.0/CSIZEF, 20);
  theRamCanvas.drawString("4", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.2800, -0.5320, "black", 6.0/CSIZEF, 20);
                                                                                                    
  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.5060, -0.5620, "black", 4.0/CSIZEF, 20);
  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3780, -0.3370, "black", 4.0/CSIZEF, 20);
  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.5060,  0.5620, "black", 4.0/CSIZEF, 20);
  theRamCanvas.drawString("5", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3780,  0.3370, "black", 4.0/CSIZEF, 20);
                                                                                                    
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3890, -0.2150, "black", 2.0/CSIZEF, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1140, -0.8620, "black", 4.0/CSIZEF, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.1370, -0.2390, "black", 4.0/CSIZEF, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3890,  0.2150, "black", 2.0/CSIZEF, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.1140,  0.8620, "black", 4.0/CSIZEF, 20);
  theRamCanvas.drawString("6", mjr::hershey::font::ROMAN_SL_SANSERIF, -1.1370,  0.2390, "black", 4.0/CSIZEF, 20);
                                                                                                    
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.6220, -0.4240, "black", 2.0/CSIZEF, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.1210, -0.6100, "black", 2.0/CSIZEF, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3760, -0.1440, "black", 1.0/CSIZEF, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF, -0.6220,  0.4240, "black", 2.0/CSIZEF, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.1210,  0.6100, "black", 2.0/CSIZEF, 20);
  theRamCanvas.drawString("7", mjr::hershey::font::ROMAN_SL_SANSERIF,  0.3760,  0.1440, "black", 1.0/CSIZEF, 20);

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

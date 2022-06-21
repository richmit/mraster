// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/

/**
 @file      mandelbrot_orbits.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Mandelbrot orbits.@EOL
 @std       C++11
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

  Explores the orbits of the iteration

    * mandelbrot_orbits_out_h.tiff  Point histogram of exterior point orbits
    * mandelbrot_orbits_in_h.tiff   Point histogram of interior point orbits
    * mandelbrot_orbits_m.tiff      The mandelbrot set
    * mandelbrot_orbits_in_c.tiff   Where interior points converged

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

/** Reasons iteration may stop */
enum class whyStopMO { OUTSET,   //!< Not in set (|z|>2)
                       MAXCOUNT  //!< Maximum iteration reached
                     };

int main(void)
{
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int CSIZE  = 1080*2;
  const int SCALE  = 4;
  const int MAXITR = 2048;
  mjr::ramCanvas1c16b inhRamCanvas (CSIZE*SCALE, CSIZE*SCALE,  -2.0, 1.0, -1.5, 1.5);
  mjr::ramCanvas1c16b incRamCanvas (CSIZE*SCALE, CSIZE*SCALE,  -2.0, 1.0, -1.5, 1.5);
  mjr::ramCanvas1c16b outhRamCanvas(CSIZE*SCALE, CSIZE*SCALE,  -2.0, 1.0, -1.5, 1.5);
  mjr::ramCanvas1c8b  mRamCanvas  (CSIZE*SCALE, CSIZE*SCALE,  -2.0, 1.0, -1.5, 1.5);
  std::complex<double>* theOrbit = new std::complex<double>[MAXITR+1];

  for(int y=0;y<inhRamCanvas.get_numYpix();y++) {
    if((y%((CSIZE*SCALE)/10))==0)
      std::cout << "LINE: " << y << "/" << (CSIZE*SCALE) << std::endl;
    for(int x=0;x<inhRamCanvas.get_numXpix();x++) {
      //std::cout << x << " " << y << std::endl;
      whyStopMO why;
      std::complex<double> z;
      int count;
      double cr = inhRamCanvas.int2realX(x);
      double ci = inhRamCanvas.int2realY(y);
      std::complex<double> c(cr, ci);
      z=c;
      for(count=0; ; count++) {
        z = z * z + c;
        theOrbit[count] = z;
        if(count>=(MAXITR-1)) {
          why = whyStopMO::MAXCOUNT;
          break;
        }
        if(std::abs(z)>2.0) {
          why = whyStopMO::OUTSET;
          break;
        }
      }

      if(why == whyStopMO::MAXCOUNT) {
        mRamCanvas.drawPoint(x, y, "white");
        incRamCanvas.drawPoint(std::real(z), std::imag(z), "white");
      }
      for(int i=0; i<(count-1); i++) {
        int cri = inhRamCanvas.real2intX(std::real(theOrbit[i]));
        int cii = inhRamCanvas.real2intY(std::imag(theOrbit[i]));
        if( !(inhRamCanvas.isCliped(cri, cii))) {
          if(why == whyStopMO::OUTSET) {
            outhRamCanvas.getPxColorRefNC(cri, cii).tfrmAdd(1);
          } else {
            inhRamCanvas.getPxColorRefNC(cri, cii).tfrmAdd(1);
          }
        }
      }
    }
  }
  outhRamCanvas.scaleDownMean(SCALE);
  outhRamCanvas.autoHistStrech();
  outhRamCanvas.writeTIFFfile("mandelbrot_orbits_out_h.tiff");
  inhRamCanvas.scaleDownMean(SCALE);
  inhRamCanvas.autoHistStrech();
  inhRamCanvas.writeTIFFfile("mandelbrot_orbits_in_h.tiff");
  mRamCanvas.scaleDownMax(SCALE);
  mRamCanvas.writeTIFFfile("mandelbrot_orbits_m.tiff");
  incRamCanvas.scaleDownMax(SCALE);
  incRamCanvas.writeTIFFfile("mandelbrot_orbits_in_c.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}

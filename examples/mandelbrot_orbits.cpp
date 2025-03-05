// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_orbits.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Mandelbrot orbits.@EOL
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
 @filedetails

  Explores the orbits of the iteration

    * mandelbrot_orbits_out_h.tiff  Point histogram of exterior point orbits
    * mandelbrot_orbits_in_h.tiff   Point histogram of interior point orbits
    * mandelbrot_orbits_m.tiff      The mandelbrot set
    * mandelbrot_orbits_in_c.tiff   Where interior points converged

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

typedef mjr::ramCanvas1c16b rcct;
typedef mjr::ramCanvas3c8b  rcrt;
//typedef mjr::ramCanvas3c16b rcrt;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int SCALE  = 4;
  const int CSIZE  = 1024*SCALE;
  const int MAXITR = 256*4;
  rcct inhRamCanvas (CSIZE*SCALE, CSIZE*SCALE,  -2.0, 1.0, -1.5, 1.5);
  rcct outhRamCanvas(CSIZE*SCALE, CSIZE*SCALE,  -2.0, 1.0, -1.5, 1.5);
  rcct distRamCanvas(CSIZE*SCALE, CSIZE*SCALE,  -2.0, 1.0, -1.5, 1.5);
  std::complex<double>* theOrbit = new std::complex<rcct::coordFltType>[MAXITR+1];

  for(rcct::coordIntType y=0;y<inhRamCanvas.getNumPixY();y++) {
    if((y%((CSIZE*SCALE)/10))==0)
      std::cout << "LINE: " << y << "/" << (CSIZE*SCALE) << std::endl;
    for(rcct::coordIntType x=0;x<inhRamCanvas.getNumPixX();x++) {
      std::complex<rcct::coordFltType> c(inhRamCanvas.int2realX(x), inhRamCanvas.int2realY(y));
      std::complex<rcct::coordFltType> z(c);
      for(rcct::colorChanType count=0; ; count++) {
        z = z * z + c;
        theOrbit[count] = z;
        if(std::abs(z)>2.0) {
          for(rcct::colorChanType i=0; i<=count; i++) {
            outhRamCanvas.incPxChan(theOrbit[i]);
            distRamCanvas.tformPixel(theOrbit[i], [i](auto& c) { c.tfrmMax(i); });
          }
          break;
        } else if(count>=(MAXITR-1)) {
          for(rcct::colorChanType i=0; i<=count; i++) 
            inhRamCanvas.incPxChan(theOrbit[i]);
          break;
        }
      }
    }
  }

  // Dump out our "data" images
  distRamCanvas.scaleDownMean(SCALE);
  distRamCanvas.autoHistStrech();
  distRamCanvas.rotate90CW();
  distRamCanvas.writeTIFFfile("mandelbrot_orbits_dst_h.tiff");
  outhRamCanvas.scaleDownMean(SCALE);
  outhRamCanvas.autoHistStrech();
  outhRamCanvas.rotate90CW();
  outhRamCanvas.writeTIFFfile("mandelbrot_orbits_out_h.tiff");
  inhRamCanvas.scaleDownMean(SCALE);
  inhRamCanvas.autoHistStrech();
  inhRamCanvas.rotate90CW();
  inhRamCanvas.writeTIFFfile("mandelbrot_orbits_in_h.tiff");

  // Construct an 8-bit RGB image
  rcrt theRamCanvas(distRamCanvas.getNumPixX(), distRamCanvas.getNumPixY());
  theRamCanvas.colorizeIntCanvas([&distRamCanvas, &outhRamCanvas, &inhRamCanvas](auto x, auto y) { return rcrt::colorType(static_cast<rcrt::colorChanType>(distRamCanvas.getPxColor(x, y).tfrmPow(0.8).getChan(0)/256), 
                                                                                                                          static_cast<rcrt::colorChanType>(outhRamCanvas.getPxColor(x, y).tfrmPow(0.6).getChan(0)/256), 
                                                                                                                          static_cast<rcrt::colorChanType>( inhRamCanvas.getPxColor(x, y).tfrmPow(0.8).getChan(0)/256)); });


  theRamCanvas.writeTIFFfile("mandelbrot_orbits_color.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */


// magick \( mandelbrot_orbits_dst_h.tiff -evaluate Pow 0.6 \) \( mandelbrot_orbits_out_h.tiff -evaluate Pow 0.4 \) \( mandelbrot_orbits_in_h.tiff -evaluate Pow 0.7 \)  -combine combined.jpg; nomacs combined.jpg
// magick \( mandelbrot_orbits_dst_h.tiff -evaluate Pow 0.8 \) \( mandelbrot_orbits_out_h.tiff -evaluate Pow 0.6 \) \( mandelbrot_orbits_in_h.tiff -evaluate Pow 0.8 \)  -combine combined.jpg; nomacs combined.jpg

// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_wave.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Animate a mandelbrot-like fractal with a variable coeficient.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/mandelbrotWave/index.html
 @copyright
  @parblock
  Copyright (c) 1988-2022, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  Iterate $f(x)=z^5+a\cdot z+c$ as one would $f(z)=z^2+c$ to render a Mandelbrot set.  Vary the parameter $a$ by moving it around the unit circle, and
  drop out an image for each $a$.  The resulting images may be rendered into movies like this:

  - Make a gif
    convert -delay 1 -loop 0 -dispose previous mandelbrot_wave_???.tiff mandelbrot_wave_mean.gif
  - Make a smaller gif gif
    convert -delay 1 -loop 0 -dispose previous -resize 50% mandelbrot_wave_???.tiff mandelbrot_wave_mean_50.gif
  - For a GIF that runs forward and backward:
    convert -delay 1 -loop 0 -dispose previous $(ls mandelbrot_wave_???.tiff) $(ls -r mandelbrot_wave_???.tiff) mandelbrot_wave_wavy.gif
  - Convert all the TIFF files into PNG so we can use ffmpeg to make a WEBM movie
    ls mandelbrot_wave_???.tiff | xargs -P 0 -I{} sh -c 'echo {}; convert {} $(echo {} | sed "s/\.tiff$/.png/;")'
  - Convert the PNGs into a WEBM
    ffmpeg -r 15 -i mandelbrot_wave_%03d.png mandelbrot_wave_mean.webm
  - Clean up the PNGs
    rm mandelbrot_wave_???..png

  Note the frames are rendered 8x larger than the final images.  I use an 8x, mean scale down to smooth the image out a bit.
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b::colorType ct;
typedef ct::csIntType cit;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    NUMITR = 255;
  const int    NUMFRM = 24*16/24;      // Full circle animation
  //const int    NUMFRM = 24*4;     // Wave animation
  const int    IMXSIZ = 7680/8;
  const int    IMYSIZ = 7680/8;
  const int    MAXZSQ = 10;
  const double ANGMIN = 0.0;                 // Full circle animation
  const double ANGMAX = std::numbers::pi*2;  // Full circle animation
  // const double ANGMIN = 3.04341788317;    // Wave animation
  // const double ANGMAX = 3.23976742401;    // Wave animation

  for(int frame=0; frame<NUMFRM; frame++) {
    mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -1.5, 1.5, -1.5, 1.5);    // Full circle animation
    // mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -0.7, 0.1, -0.7, 0.1); // Wave animation
    theRamCanvas.clrCanvasToBlack();
    std::cout << "Frame: " << frame << std::endl;
    double angle = frame*(ANGMAX-ANGMIN)/NUMFRM+ANGMIN;    
    std::complex<double> a(std::cos(angle), std::sin(angle));
#   pragma omp parallel for schedule(static,1)
    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> c(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
        std::complex<double> z(0.0, 0.0);
        int count = 0; 
        while((std::norm(z)<MAXZSQ) && (count<=NUMITR)) {
          z = std::pow(z, 5) +  a * z + c;
          count++;
        }
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, ct::csCColdeFireRamp::c(static_cast<ct::csIntType>(count*20)));
      }
    }
    theRamCanvas.scaleDownMean(8);   // Another good choice: theRamCanvas.scaleDownMax(8); 
    theRamCanvas.writeTIFFfile("mandelbrot_wave_" + mjr::fmtInt(frame, 3, '0') + ".tiff");
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */



// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_count_movie.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simplified code for for web page examples.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/mandelbrot/index.html
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

  Create a gif like this:
    time convert -delay 1 -loop 0 -dispose previous mandelbrot_count_movie_???.tiff mandelbrot_count_movie.gif
  Convert TIFFs to PNGs:
    ls mandelbrot_count_movie_???.tiff | xargs -P 8 -I{} sh -c 'echo {}; convert {} $(echo {} | sed "s/\.tiff$/.png/;")'
  Convert PNGs into a WEBM
    ffmpeg -r 15 -i mandelbrot_count_movie_%03d.png -crf 20 mandelbrot_count_movie.webm
  Convert TIFFs to PNGs at 45% size:
    ls mandelbrot_count_movie_???.tiff | xargs -P 8 -I{} sh -c 'echo {}; convert {} -resize 45% $(echo {} | sed "s/\.tiff$/_45.png/;")'
  Convert 45% PNGs into a WEBM
    ffmpeg -r 15 -i mandelbrot_count_movie_%03d_45.png -crf 20 mandelbrot_count_movie_45.webm
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
  const int    IMGSIZ = 7680/4;
  const int    MXITRS = 157;
  const int    MXITRE = 461;
  const double MAXZSQ =  4.0;
  const double BALSIZ =  0.00019065;
  const double CNTRX  = -0.745258237857;
  const double CNTRY  =  0.130272017858;

# pragma omp parallel for schedule(static,1)
  for(int frame=0;frame<(MXITRE-MXITRS);frame++) {
    mjr::ramCanvas3c8b theRamCanvas(IMGSIZ, IMGSIZ, CNTRX-BALSIZ, CNTRX+BALSIZ, CNTRY-BALSIZ, CNTRY+BALSIZ);
    int curMaxItr = MXITRS + frame;
    std::chrono::time_point<std::chrono::system_clock> frameStartTime = std::chrono::system_clock::now();
    for(int y=0;y<theRamCanvas.getNumPixY();y++) {
      for(int x=0;x<theRamCanvas.getNumPixX();x++) {
        std::complex<double> c = theRamCanvas.int2real(x, y);
        std::complex<double> z(0.0, 0.0);
        int count = 0; 
        while((std::norm(z)<MAXZSQ) && (count<=curMaxItr)) {
          z=std::pow(z, 2) + c;
          count++;
        }
        if(count < curMaxItr)
          theRamCanvas.drawPoint(x, y, ct::csCColdeFireRamp::c(static_cast<ct::csFltType>(count)/curMaxItr));
      }
    }
    theRamCanvas.writeTIFFfile("mandelbrot_count_movie_" + mjr::fmtInt(frame, 3, '0') + ".tiff");
    std::chrono::duration<double> frameRunTime = std::chrono::system_clock::now() - frameStartTime;
#   pragma omp critical
    std::cout << "Frame " << frame << " Runtime " << frameRunTime.count() << " sec" << std::endl;
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

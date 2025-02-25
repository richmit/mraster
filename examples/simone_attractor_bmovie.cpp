// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      simone_attractor_bmovie.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw fractals inspired by the book Symmetry in Chaos.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/sic/index.html
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

  I came across the Simone Attractor on Paul Bourke's web site (http://www.paulbourke.net/fractals/simone_orbits/).  Apparently it's based on, or inspired by,
  work done by Simone Conradi; however, the web page provides no references.  The governing iteration is as follows:

  @f[ \begin{eqnarray}
       x_{n+1} & = & \sin(x^2_n - y^2_n+a) \\
       y_{n+1} & = & \cos(2 x_n y_n+b)     \\
      \end{eqnarray} @f]

                ffmpeg -y -framerate 15 -i simone_attractor_bmovie_%4d.tiff -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2" -c:v libx264 -crf 10 -b:v 0 -preset veryslow simone_attractor_bmovie_100_crf10.mp4;
                ffmpeg -y -framerate 15 -i simone_attractor_bmovie_%4d.tiff -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2" -c:v libx264 -crf  0 -b:v 0 -preset veryslow simone_attractor_bmovie_100_crf00.mp4;
                magick -delay 1 -loop 0 -dispose previous simone_attractor_bmovie_????.tiff simone_attractor_bmovie_100.gif

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int      BSIZ   = 6400;  
  const int      NUMFRM = 15*6;
  const double   R      = 0.002;
  const double   ANGMIN = 0.0;
  const double   ANGMAX = std::numbers::pi*2;
  const uint64_t MAXITR = 10000000;

# pragma omp parallel for schedule(static,1)
  for(int frame=0; frame<NUMFRM; frame++) {
    mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, -0.6, 0.6, -0.25, 1.0);
    decltype(theRamCanvas)::coordFltType angle = frame*(ANGMAX-ANGMIN)/NUMFRM+ANGMIN;
    decltype(theRamCanvas)::coordFltType a     =  0.382110 + R * std::cos(angle);
    decltype(theRamCanvas)::coordFltType b     = -1.012590 + R * std::sin(angle);
    decltype(theRamCanvas)::coordFltType xn    = 0;
    decltype(theRamCanvas)::coordFltType yn    = 0;
    for(uint64_t i=0;i<MAXITR;i++) {
      decltype(theRamCanvas)::coordFltType tmp = std::sin(xn*xn-yn*yn+a);
      yn = std::cos(2*xn*yn+b);
      xn = tmp;
      if(i>1000) {
        decltype(theRamCanvas)::coordIntType ix = theRamCanvas.real2intX(xn);
        decltype(theRamCanvas)::coordIntType iy = theRamCanvas.real2intY(yn);
        if (theRamCanvas.isOnCanvas(ix, iy))
          theRamCanvas.getPxColorRefNC(ix, iy).tfrmAdd(1);
      }
    }
    theRamCanvas.autoHistStrech();
    theRamCanvas.applyHomoPixTfrm(&decltype(theRamCanvas)::colorType::tfrmPow, 1/4.0);
    theRamCanvas.rotate90CW();
    theRamCanvas.scaleDownMean(8);
    theRamCanvas.autoHistStrech();
#   pragma omp critical
    std::cout << "FRAME(" << frame <<  "): DONE" << std::endl;
    theRamCanvas.writeTIFFfile("simone_attractor_bmovie_" + mjr::math::str::fmt_int(frame, 4, '0') + ".tiff", 
                               mjr::ramCanvasPixelFilter::ColorSchemeOnChan<decltype(theRamCanvas), 
                                                                            mjr::color3c8b, 
                                                                            mjr::color3c8b::csCColdeFireRamp>(theRamCanvas));

  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

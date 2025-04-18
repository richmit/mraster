// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      sprott2d.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a sprott Attractor.@EOL
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

  Inspired by http://paulbourke.net/fractals/starjulia/
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int BSIZ = 7680/8;
  mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, -1, 1, -1, 1);
  double x=0.0, y=0.0, xNew, yNew;

  double a[12] = {-0.6599, -0.2, 1.1, 0.2, -0.81, 0.61, -0.7, 0.71, 0.7, 0.28, 0.19, 0.89};
  double p = 1.7;

    /* Draw the atractor on a 16-bit, greyscale canvas -- the grey level will be an integer represeting the hit count for that pixel.  This is a good example
       of how an image can have pixel values that are generic "data" as well as color information. */
    uint64_t maxII = 0;
    for(uint64_t i=0;i<1000000000ul;i++) {

      xNew = a[0] + a[1]*x + a[2]*x*x + a[3]*x*y + a[4]*y  + a[5]*y*y;
      yNew = a[6] + a[7]*x + a[8]*x*x + a[9]*x*y + a[10]*y + a[11]*y*y;
      theRamCanvas.incPxChan(xNew, yNew);
      if(theRamCanvas.getPxColor(xNew, yNew).getC0() > maxII) {
        maxII = theRamCanvas.getPxColor(xNew, yNew).getC0();
        if(maxII > 16384) { // 1/4 of max possible intensity
          std::cout << "ITER(): " << i << " MAXS: " << maxII << " EXIT: Maximum image intensity reached" << std::endl;
          break;
        }
      }
      if((i % 10000000) == 0)
        std::cout << "ITER: " << i << " MAXS: " << maxII << std::endl;
      x=xNew;
      y=yNew;
    }

    theRamCanvas.writeRAWfile("sprott2d.mrw");

    // Root image transform
    theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmStdPow, 1/p);
    maxII = static_cast<uint64_t>(65535.0 * std::pow(static_cast<double>(maxII)/65535.0, 1/p));

    // Log image transform
    // theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmLn);
    // maxII = log(maxII);

    /* Create a new image based on an integer color scale -- this one is 24-bit RGB color.  This isn't the most efficient technique from a RAM perspective in
       that we could pass a conversion routine to writeTIFFfile (see sic.cpp for an example of how to do just that). */
    mjr::ramCanvas3c8b anotherRamCanvas(BSIZ, BSIZ);
    mjr::ramCanvas3c8b::colorType bColor;
    for(int yi=0;yi<theRamCanvas.getNumPixY();yi++)
      for(int xi=0;xi<theRamCanvas.getNumPixX();xi++)
        anotherRamCanvas.drawPoint(xi, yi, bColor.cmpRGBcornerDGradiant(static_cast<mjr::ramCanvas3c8b::csIntType>(theRamCanvas.getPxColor(xi, yi).getC0() * 1275 / maxII), "0RYBCW"));

    anotherRamCanvas.writeTIFFfile("sprott2d.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      peterdejongM.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Peter de Jong Attractor Movie.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/swirl/index.html
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

  Moves the parameters around a simple closed curve in @f$\mathbb{R}^8@f$.  Make a GIF like this:

       time convert -delay 1 -loop 0 -dispose previous peterdejongM_???.tiff peterdejongM.gif
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();

  const int               imageSize =  540; // 4320 2160 1080 540 270
  const unsigned long int maxIters  =  300000000ul;
  const unsigned long int itersTick =  10000000ul;
  const int               numFrames =  24*8; // 512 128 32 16
  const double            a         =  1.50503;
  const double            b         = -1.44118;
  const double            c         = -1.23281;
  const double            d         =  1.78607;
  const double            e         =  1.709360;
  const double            f         =  1.794210;
  const double            g         =  1.893750;
  const double            h         = -1.38227;
  const double            p         =  2.10;

  mjr::ramCanvas1c16b::colorType aColor;
  aColor.setChans(1);

# pragma omp parallel for schedule(static,1)
  for(int frame=0; frame<numFrames; frame++) {
    mjr::ramCanvas1c16b theRamCanvas(imageSize, imageSize, -2, 2, -2, 2);
    /* Draw the atractor on a 16-bit, greyscale canvas -- the grey level will be an integer represeting the hit count for that pixel. */
    double x = 1.0;
    double y = 1.0;
    mjr::ramCanvas1c16b::colorChanArithSPType maxII = 0;
    for(mjr::ramCanvas1c16b::colorChanArithSPType i=0;i<maxIters;i++) {
      double da = 0.07 * cos(frame * 2 * std::numbers::pi / numFrames);
      double dc = 0.04 * sin(frame * 2 * std::numbers::pi / numFrames);
      double db = 0.05 * cos(frame * 2 * std::numbers::pi / numFrames);
      double dd = 0.13 * sin(frame * 2 * std::numbers::pi / numFrames);
      double de = 0.18 * sin(frame * 2 * std::numbers::pi / numFrames);
      double dg = 0.05 * cos(frame * 2 * std::numbers::pi / numFrames);
      double df = 0.09 * sin(frame * 2 * std::numbers::pi / numFrames);
      double dh = 0.12 * cos(frame * 2 * std::numbers::pi / numFrames);
      double xNew = sin((a + da)*y + e + de) - cos((b+db)*x + f + df);
      double yNew = sin((c + dc)*x + g + dg) - cos((d+dd)*y + h + dh);
      theRamCanvas.drawPoint(x, y, theRamCanvas.getPxColor(x, y).tfrmAdd(aColor));
      if(theRamCanvas.getPxColor(x, y).getC0() > maxII) {
        maxII = theRamCanvas.getPxColor(x, y).getC0();
        if(maxII > 16384) { // 1/4 of max possible intensity
          std::cout << "FRAME(" << frame <<  "): " << i << " MAXS: " << maxII << " EXIT: Maximum image intensity reached" << std::endl;
          break;
        }
      }
      if((i % itersTick) == 0)
        std::cout << "FRAME(" << frame <<  "): " << i << " MAXS: " << maxII << std::endl;
      x=xNew;
      y=yNew;
    }

    // Dump a raw image
    theRamCanvas.writeTIFFfile("peterdejongM_" + mjr::math::str::fmt_int(frame, 3, '0') + ".mrw");

    // Root image transform
    theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmStdPow, 1.0/p);
    maxII = static_cast<mjr::ramCanvas1c16b::colorChanArithSPType>(65535.0 * pow(static_cast<double>(maxII)/65535.0, 1.0/p));

    /* Create a new image based on an integer color scale -- this one is 24-bit RGB color.  This isn't the most efficient technique from a RAM perspective in
       that we could pass a conversion routine to writeTIFFfile (see sic.cpp for an example of how to do just that). */
    mjr::ramCanvas3c8b anotherRamCanvas(imageSize, imageSize);
    mjr::ramCanvas3c8b::colorType bColor;
    for(int yi=0;yi<theRamCanvas.getNumPixY();yi++)
      for(int xi=0;xi<theRamCanvas.getNumPixX();xi++)
        anotherRamCanvas.drawPoint(xi, yi, bColor.cmpRGBcornerDGradiant(static_cast<mjr::ramCanvas3c8b::csIntType>(theRamCanvas.getPxColor(xi, yi).getC0() * 1275 / maxII), "0RYBCW"));
    anotherRamCanvas.writeTIFFfile("peterdejongM_" + mjr::math::str::fmt_int(frame, 3, '0') + ".tiff");

  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}


// mkdir rawpng
// mkdir mrw
// mv peter*.mrw mrw
// for f in mrw/*.mrw(:r:t); do echo $f; if [ ! -e rawpng/$f.png ] ; then convert -depth 16 -size 540x540+100 gray:mrw/$f.mrw -quality 90 rawpng/$f.png; fi; done
/** @endcond */

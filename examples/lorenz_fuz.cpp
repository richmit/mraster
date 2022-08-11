// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      lorenz_fuz.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a Lorenz Attractor histogram.@EOL
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
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  double p = 1.75;
  const int XSIZ = 7680/1;
  const int YSIZ = 4320/1;
  uint64_t maxII = 0;
  mjr::ramCanvas1c16b::colorType aColor;
  aColor.setChans(1);
  mjr::ramCanvas1c16b theRamCanvas(XSIZ, YSIZ, -19, 19, 3, 47);

  double distToGo = 80000.0;             /* How long should the curve be? */

  double idealJumpDist = 0.12;               /* Size of the spheres to use */

  double maxMovDelta = idealJumpDist / 2.0; /* The maximum delta for the function. */
  double minMovDelta = idealJumpDist / 6.0; /* The minimum delta for the function. */


  double minTdelta        = 0.000001;   /* Minimum value for tDelta */
  double maxTdelta        = 0.01;       /* Maximum value for tDelta */
  double tDeltaZeroThresh = 0.00000001; /* Episolon ball for zero. */
  double maxNumBisect     = 10;         /* Max bisections on tDelta. */

  /* Initial conditions, and constants. */
  double a = 10;
  double b = 28;
  double c = 8.0 / 3;

  double curMaxTdelta, curMinTdelta, tDelta, dist, Xdelta, Ydelta, Zdelta, movDelta;
  int    numBisect, doneBisecting, numBalls;

  for(int i=0; i<10; i++) {
    double x = 0.0;
    double y = i - 5.2;
    double z = 25;

    std::cout << "y: " << y << std::endl;

    /*  Solve the equations..... */
    numBalls = 0;
    tDelta = maxTdelta;
    dist = 0.0;
    while (dist < distToGo) {
      numBalls++;
      /*  Take a big step up to minimize the number of balls. */
      tDelta = (maxTdelta + tDelta) / 2;
      if (tDelta > maxTdelta) {
        tDelta = maxTdelta;
      }
      curMaxTdelta = maxTdelta;
      curMinTdelta = minTdelta;
      /*  Bisect t delta until we have done it too much or until we have a good value for t delta. */
      numBisect = 0;
      doneBisecting = 0;
      while (!(doneBisecting)) {
        numBisect++;
        Xdelta = a * (y - x) * tDelta;
        Ydelta = (x * (b - z) - y) * tDelta;
        Zdelta = (x * y - c * z) * tDelta;
        movDelta = sqrt (fabs (Xdelta * Xdelta + Ydelta * Ydelta + Zdelta * Zdelta));
        if (numBisect > maxNumBisect) {
          doneBisecting = 1;
        } else {
          if (movDelta > maxMovDelta) {
            if (fabs (tDelta - curMinTdelta) < tDeltaZeroThresh) {
              doneBisecting = 1;
            } else {
              curMaxTdelta = tDelta;
              tDelta = (tDelta + curMinTdelta) / 2;
              if (tDelta < minTdelta) {
                tDelta = minTdelta;
              }
            }
          } else if (movDelta < minMovDelta) {
            if (fabs (tDelta - curMaxTdelta) < tDeltaZeroThresh) {
              doneBisecting = 1;
            } else {
              curMinTdelta = tDelta;
              tDelta = (curMaxTdelta + tDelta) / 2;
              if (tDelta > maxTdelta) {
                tDelta = maxTdelta;
              }
            }
          } else {
            doneBisecting = 1;
          }
        }
      }
      dist += movDelta;
      x = x + Xdelta;
      y = y + Ydelta;
      z = z + Zdelta;
      theRamCanvas.drawPoint(x, z, theRamCanvas.getPxColor(x, z).tfrmAdd(aColor));

      if(theRamCanvas.getPxColor(x, z).getC0() > maxII)
        maxII = theRamCanvas.getPxColor(x, z).getC0();
    }
  }

  theRamCanvas.writeRAWfile("lorenz_fuz.mrw");

  // Root image transform
  theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmStdPow, 1.0 / p);
  maxII = static_cast<uint64_t>(65535.0 * std::pow(static_cast<double>(maxII) / 65535.0, 1.0 / p));

  // Log image transform
  // theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmLn);
  // maxII = log(maxII);

  /* Create a new image based on an integer color scale -- this one is 24-bit RGB color.  This isn't the most efficient technique from a RAM perspective in
     that we could pass a conversion routine to writeTIFFfile (see sic.cpp for an example of how to do just that). */
  mjr::ramCanvas3c8b anotherRamCanvas(XSIZ, YSIZ);
  mjr::ramCanvas3c8b::colorType bColor;
  for(int yi=0;yi<theRamCanvas.get_numYpix();yi++)
    for(int xi=0;xi<theRamCanvas.get_numXpix();xi++) {
      anotherRamCanvas.drawPoint(xi, yi, bColor.cmpRGBcornerDGradiant(static_cast<mjr::ramCanvas3c8b::csIntType>(theRamCanvas.getPxColor(xi, yi).getC0() * 1275 / maxII), "0RYBCW"));
      if( (anotherRamCanvas.getPxColor(xi, yi).getC0() > 0) && (anotherRamCanvas.getPxColor(xi, yi).getC0() < 255) )
        anotherRamCanvas.getPxColorRefNC(xi, yi).setC0(255);
    }

  anotherRamCanvas.writeTIFFfile("lorenz_fuz.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
/** @endcond */

// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      lorenz_multi.cpp
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
  const int XSIZ = 7680/2;
  const int YSIZ = 4320/2;
  mjr::ramCanvas1c16b::colorType aColor;
  aColor.setChans(1);
  mjr::ramCanvas1c16b theRamCanvas(XSIZ, YSIZ, -19, 19, 3, 47);
  double x=5.10, y=3.1, z=10.1, xNew, yNew, zNew;

  std::random_device rd;
  std::mt19937 rEng(rd());
  std::uniform_real_distribution<double> uniform_dist_double(-15.0, 15.0);

  int numCurves          = 100;
  int numPtsPerCurve     = 105000;
  int numPtsPerCurveToss = 700;
  double tDelta           = 0.00001;

  double a = 10.0;
  double b = 28.0;
  double c = 8.0 / 3;

  double p = 1.7;

  /* Draw the atractor on a 16-bit, greyscale canvas -- the grey level will be an integer represeting the hit count for that pixel.  This is a good example
     of how an image can have pixel values that are generic "data" as well as color information. */
  uint64_t maxII = 0;
  for(int j=0; j<numCurves; j++) {
    x=0*uniform_dist_double(rEng);
    //y=uniform_dist_double(rEng);
    y=30.0*j/(numCurves-1)-15.0;
    z=30+0*uniform_dist_double(rEng);

    std::cout << "y: " << y << std::endl;

    for(int i=0;i<numPtsPerCurve;i++) {
      xNew = x + a * (y - x) * tDelta;
      yNew = y + (x * (b - z) - y) * tDelta;
      zNew = z + (x * y - c * z) * tDelta;
      if(i>numPtsPerCurveToss) {
        theRamCanvas.drawPoint(xNew, zNew, theRamCanvas.getPxColor(xNew, zNew).tfrmAdd(aColor));
        if(theRamCanvas.getPxColor(xNew, zNew).getC0() > maxII) {
          maxII = theRamCanvas.getPxColor(xNew, zNew).getC0();
        }
      }
      x=xNew;
      y=yNew;
      z=zNew;
    }
  }
  theRamCanvas.writeRAWfile("lorenz_multi.mrw");

  // Root image transform
  theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmStdPow, 1/p);
  maxII = static_cast<uint64_t>(65535.0 * std::pow(static_cast<double>(maxII) / 65535.0, 1.0 / p));

  // Log image transform
  // theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmLn);
  // maxII = log(maxII);

  /* Create a new image based on an integer color scale -- this one is 24-bit RGB color.  This isn't the most efficient technique from a RAM perspective in
     that we could pass a conversion routine to writeTIFFfile (see sic.cpp for an example of how to do just that). */
  mjr::ramCanvas3c8b anotherRamCanvas(XSIZ, YSIZ);
  mjr::ramCanvas3c8b::colorType bColor;
  for(int yi=0;yi<theRamCanvas.getNumPixY();yi++)
    for(int xi=0;xi<theRamCanvas.getNumPixX();xi++) {
      anotherRamCanvas.drawPoint(xi, yi, bColor.cmpRGBcornerDGradiant(static_cast<mjr::ramCanvas3c8b::csIntType>(theRamCanvas.getPxColor(xi, yi).getC0() * 1275 / maxII), "0RYBCW"));
       if( (anotherRamCanvas.getPxColor(xi, yi).getC0() > 0) && (anotherRamCanvas.getPxColor(xi, yi).getC0() < 255/2) )
         anotherRamCanvas.getPxColorRefNC(xi, yi).setC0(255/2);
    }

  anotherRamCanvas.writeTIFFfile("lorenz_multi.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
/** @endcond */

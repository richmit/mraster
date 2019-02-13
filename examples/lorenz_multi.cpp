// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      chua.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a sprott Attractor.@EOL
 @std       C++98
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <cmath>                                                         /* std:: C math.h          C++11    */
#include <complex>                                                       /* STL algorithm           C++11    */
#include <random>                                                        /* C++ random numbers      C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

int main(void) {
  const int XSIZ = 7680/2;
  const int YSIZ = 4320/2;
  mjr::color1c16b aColor;
  aColor.setAll(1);
  mjr::ramCanvas1c16b theRamCanvas(XSIZ, YSIZ, -19, 19, 3, 47);
  double x=5.10, y=3.1, z=10.1, xNew, yNew, zNew;

  std::random_device rd;
  std::mt19937 rEng(rd());
  std::uniform_real_distribution<double> uniform_dist_float(-15.0, 15.0);

  int numCurves          = 100;
  int numPtsPerCurve     = 105000;
  int numPtsPerCurveToss = 700;
  float tDelta           = 0.00001;

  float a = 10;
  float b = 28;
  float c = 8.0 / 3;
    
  float p = 1.7;

  /* Draw the atractor on a 16-bit, greyscale canvas -- the grey level will be an integer represeting the hit count for that pixel.  This is a good example
     of how an image can have pixel values that are generic "data" as well as color information. */
  uint64_t maxII = 0;
  for(int j=0; j<numCurves; j++) {
    x=0*uniform_dist_float(rEng);
    //y=uniform_dist_float(rEng);
    y=30.0*j/(numCurves-1)-15.0;
    z=30+0*uniform_dist_float(rEng);

    std::cout << "y: " << y << std::endl;
    
    for(int i=0;i<numPtsPerCurve;i++) {
      xNew = x + a * (y - x) * tDelta;
      yNew = y + (x * (b - z) - y) * tDelta;
      zNew = z + (x * y - c * z) * tDelta;
      if(i>numPtsPerCurveToss) {
        theRamCanvas.drawPoint(xNew, zNew, theRamCanvas.getPxColor(xNew, zNew).tfrmAdd(aColor));
        if(theRamCanvas.getPxColor(xNew, zNew).getRed() > maxII) {
          maxII = theRamCanvas.getPxColor(xNew, zNew).getRed();
        }
      }
      x=xNew;
      y=yNew;
      z=zNew;
    }
  }
  theRamCanvas.writeRAWfile("lorenz_multi.mrw");

  // Root image transform
  theRamCanvas.applyHomoPixTfrm(&mjr::color1c16b::tfrmStdPow, 1/p);
  maxII = 65535.0 * pow(maxII/65535.0, 1/p);

  // Log image transform
  // theRamCanvas.applyHomoPixTfrm(&mjr::color1c16b::tfrmLn);
  // maxII = log(maxII);

  /* Create a new image based on an integer color scale -- this one is 24-bit RGB color.  This isn't the most efficient technique from a RAM perspective in
     that we could pass a conversion routine to writeTIFFfile (see sic.cpp for an example of how to do just that). */
  mjr::ramCanvas3c8b anotherRamCanvas(XSIZ, YSIZ);
  mjr::color3c8b bColor;
  for(int yi=0;yi<theRamCanvas.get_numYpix();yi++)
    for(int xi=0;xi<theRamCanvas.get_numXpix();xi++) {
      anotherRamCanvas.drawPoint(xi, yi, bColor.cmpColorRamp(theRamCanvas.getPxColor(xi, yi).getRed() * 1275 / maxII, "0RYBCW"));
       if( (anotherRamCanvas.getPxColor(xi, yi).getRed() > 0) && (anotherRamCanvas.getPxColor(xi, yi).getRed() < 255/2) )
         anotherRamCanvas.getPxColorRefNC(xi, yi).setRed(255/2);
    }

  anotherRamCanvas.writeTIFFfile("lorenz_multi.tiff");
  return 0;
}

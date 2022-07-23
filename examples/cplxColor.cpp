// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      cplxColor.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     draw complex function plots@EOL
 @keywords
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
using cplx = std::complex<double>;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
cplx f(cplx z);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const double ar       = 16/9.0; // Aspect ratio
  const int    hdLevel  = 4;      // 1=FHD/2 2=FHD, 4=4k, 8=8k
  mjr::ramCanvas3c8b theRamCanvas(960*hdLevel, 540*hdLevel, -2.2*ar, 2.2*ar, -2.2, 2.2);
  mjr::ramCanvas3c8b::colorType aColor;

  const double tau      = std::numbers::pi * 2;   // 2*Pi
  const double cutDepth = 10.0;          // Range: $[1, ~30]$ Smaller means more contrast on cuts.
  const double argCuts  = 16.0;          // Number of grey cuts for arg
  const int    argWrap  = 3;             // Number of times to wrap around the color ramp for arg
  const double absCuts  = 2.0;           // Number of grey cuts for abs
  const int    numColor = 6*255;         // Number of colors in setRGBcmpClrCubeRainbow -1

  for(int y=0;y<theRamCanvas.get_numYpix();y++)  {
    //std::cout << "LINE: " << y << " of " << (1080*hdLevel) << std::endl;
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      cplx z { theRamCanvas.int2realX(x), theRamCanvas.int2realY(y) };
      cplx fz      = f(z);

      double zArg  = std::arg(fz);                           // Arg
      double pzArg = (zArg < 0.0 ? tau + zArg : zArg) / tau; // Arg mapped to [0, 1]
      double zAbs  = std::abs(fz);                           // Abs
      double lzAbs = std::log(zAbs);                         // log(Abs
      // double xAbs  = std::abs(x);                            // abs(re
      // double yAbs  = std::abs(y);                            // abs(img
      // double xPz   = 1.0/(xAbs + 1.0);                       // Map real z to [0,1]  0->1, \inf->0
      // double yPz   = 1.0/(yAbs + 1.0);                       // Map real z to [0,1]  0->1, \inf->0
      // double zPz   = 1.0/(zAbs + 1.0);                       // Map abs(z) to [0,1]  0->1, \inf->0
      // double atm   = 2*atan(zAbs)/pi;                        // Map Abs to [0,1]
      // double a     = 2;                                      // param for sgpm
      // double tmp   = std::pow(zAbs, a);                      // tmp for sgpm
      // double sgpm  = tmp / (tmp + 1);                        // Map Abs to [0, 1] e stereographic projection onto the Riemann sphere.
      // double patm  = 1 - std::pow(0.5, zAbs);                // Map Abs to [0,1] -- much like atm, but no trig

      // Primary color for fz
      aColor.setRGBcmpClrCubeRainbow(static_cast<mjr::ramCanvas3c8b::csIdxType>(mjr::numberWrap(mjr::unitTooIntLinMap(mjr::unitClamp(pzArg), numColor*argWrap), numColor))); // Make color

      // Modify the color with "cuts" along argument & magnitede scales.
      aColor.tfrmLinearGreyLevelScale(1.0 - std::fabs(int(pzArg*argCuts) - pzArg*argCuts)/cutDepth, 0);
      aColor.tfrmLinearGreyLevelScale(1.0 - std::fabs(int(lzAbs*absCuts) - lzAbs*absCuts)/cutDepth, 0);

      theRamCanvas.drawPoint(x, y, aColor);
    }
  }
  theRamCanvas.writeTIFFfile("cplxColor.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
cplx f(cplx z) {
  try {
    z=z*cplx(1.5);
    return ((z-2.0)*(z-2.0)*(z+cplx(1,-2))*(z+cplx(2,2))/(z*z*z));

    // z=z/cplx(5.5);
    // return (std::sin(cplx(1)/z));

    // z=z/cplx(2.3);
    // for(int i=0; i<20; i++)
    //   z = z*z-cplx(0.75, 0.2);
    // return z;

    // z=(z*cplx(0, 1)+cplx(1.8, 0))*cplx(0.6, 0);
    // for(int i=0; i<3; i++)
    //   z = (std::sin(std::exp(z)) - cplx(1))/(std::cos(z*z) - cplx(2.0)*z*z + z + cplx(1));
    // return z;

    //return (std::sin(z) - cplx(1))/(z*z*z - cplx(0.5)*z*z + z + cplx(1));

    //return (std::sin(std::exp(z)) - cplx(1))/(std::cos(z*z) - cplx(2.0)*z*z + z + cplx(1));

    //return (z - cplx(1))/(z*z*z - cplx(0.5)*z*z + z + cplx(1));

    // return z;

    //// Eisenstein series E4
    // cplx f = 0.0;
    // cplx zp = z;
    // for(int n=1; n<20; n++) {
    //   f += static_cast<double>(n*n*n)*zp/(1.0-zp);
    //   zp *= z;
    // }
    // f *= 240;
    // f += 1;
    // return f;

    //// Eisenstein series E6
    // cplx f = 0.0;
    // cplx zp = z;
    // for(int n=1; n<20; n++) {
    //   f += static_cast<double>(n*n*n*n*n)*zp/(1.0-zp);
    //   zp *= z;
    // }
    // f *= 504.0;
    // f = 1.0 - f;
    // return f;

    // //// Eisenstein series G6
    // cplx f = 0.0;
    // for(int n=1; n<10; n++) 
    //   for(int m=1; m<10; m++) {
    //     cplx d = 1.0/std::pow(static_cast<double>(m) + static_cast<double>(n) * z, 6.0);
    //     f += d;
    //     if (std::abs(d) < 0.00001) break;
    //   }
    // return f;

  } catch(...) {
    std::cout << "Something went wrong!!" << std::endl;
    return 0;
  }
}




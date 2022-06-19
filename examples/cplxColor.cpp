// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      cplxColor.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     draw complex function plots@EOL
 @keywords
 @std       C++11
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <iostream>                                                      /* C++ iostream            C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */

using cplx = std::complex<mjr::ramCanvas3c8b::coordFltType>;

cplx f(cplx z);

cplx f(cplx z) {
  try {
    // z=z*cplx(1.5);
    // return ((z-cplx(2))*(z-cplx(2))*(z+cplx(1,-2))*(z+cplx(2,2))/(z*z*z));

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

    return (std::sin(z) - cplx(1))/(z*z*z - cplx(0.5)*z*z + z + cplx(1));

    //return (std::sin(std::exp(z)) - cplx(1))/(std::cos(z*z) - cplx(2.0)*z*z + z + cplx(1));

    //return (z - cplx(1))/(z*z*z - cplx(0.5)*z*z + z + cplx(1));

    //return z;
  } catch(...) {
    std::cout << "Something went wrong!!" << std::endl;
    return 0;
  }
}

int main(void) {
  const double cutDepth = 10.0;   // Range: $[1, ~30]$ Smaller means more contrast on cuts.
  const double argCuts  = 16.0;   // Number of grey cuts for arg
  const int   argWrap  = 3;       // Number of times to wrap around the color ramp for arg
  const double absCuts  = 2.0;    // Number of grey cuts for abs
  const double ar       = 16/9.0; // Aspect ratio
  const int   hdLevel  = 2;       // 1=FHD, 2=4k, 4=8k
  const int   numColor = 1530;
  //const int   numColor = 765;
  mjr::ramCanvas3c8b theRamCanvas(1920*hdLevel, 1080*hdLevel, -2.0*ar, 2.0*ar, -2.0, 2.0);
  for(int y=0;y<theRamCanvas.get_numYpix();y++)  {
    for(int x=0;x<theRamCanvas.get_numXpix();x++) {
      cplx z { theRamCanvas.int2realX(x), theRamCanvas.int2realY(y) };
      cplx fz      = f(z);
      double fzArg  = std::arg(fz);
      double pfzArg = (fzArg < 0.0 ? 2.0 *3.141592653589793 + fzArg : fzArg) / (2.0 * 3.141592653589793);
      double fzAbs  = std::abs(fz);
      double lfzAbs = std::log(fzAbs);
      mjr::ramCanvas3c8b::colorType aColor;
      aColor.cmpClrCubeRainbow(mjr::intWrap(mjr::unitTooIntLinMap(mjr::unitClamp(pfzArg), numColor*argWrap), numColor));
      //aColor.cmpSumRampRGB(mjr::intWrap(mjr::unitTooIntLinMap(mjr::unitClamp(pfzArg), numColor*argWrap), numColor));
      aColor.tfrmLinearGreyLevelScale(1.0 - std::fabs(int(pfzArg*argCuts) - pfzArg*argCuts)/cutDepth, 0);
      aColor.tfrmLinearGreyLevelScale(1.0 - std::fabs(int(lfzAbs*absCuts) - lfzAbs*absCuts)/cutDepth, 0);
      theRamCanvas.drawPoint(x, y, aColor);
    }
  }
  theRamCanvas.writeTIFFfile("cplxColor.tiff");
}

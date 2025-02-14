// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_meanOrbit.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Color Mandelbrot set using the mean orbit.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 2025, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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


cmake --build . -t mandelbrot_meanOrbit && ./mandelbrot_meanOrbit.exe && magick mandelbrot_meanOrbit.tiff -pointsize 40 -draw "gravity northwest fill white text 3,11 'Color: Im'"  mandelbrot_meanOrbit_im.png
cmake --build . -t mandelbrot_meanOrbit && ./mandelbrot_meanOrbit.exe && magick mandelbrot_meanOrbit.tiff -pointsize 40 -draw "gravity northwest fill white text 3,11 'Color: abs'" mandelbrot_meanOrbit_abs.png
cmake --build . -t mandelbrot_meanOrbit && ./mandelbrot_meanOrbit.exe && magick mandelbrot_meanOrbit.tiff -pointsize 40 -draw "gravity northwest fill white text 3,11 'Color: Re'"  mandelbrot_meanOrbit_re.png
cmake --build . -t mandelbrot_meanOrbit && ./mandelbrot_meanOrbit.exe && magick mandelbrot_meanOrbit.tiff -pointsize 40 -draw "gravity northwest fill white text 3,11 'Color: arg'" mandelbrot_meanOrbit_arg.png

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b rcT;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int DSCALE = 8;
  const int USCALE = 8;
  const int MAXITR = 256;
  const int width  = 1024*USCALE;  
  const int height = 1024*USCALE;
  rcT theRamCanvas(width, height, -2.2, 0.8, -1.5, 1.5);

# pragma omp parallel for schedule(static,1)
  for(rcT::coordIntType y=0;y<theRamCanvas.getNumPixY();y++) {
    for(rcT::coordIntType x=0;x<theRamCanvas.getNumPixX();x++) {
      int count;
      std::complex<mjr::ramCanvas1c64F::coordFltType> z(0.0, 0.0);
      std::complex<mjr::ramCanvas1c64F::coordFltType> c(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
      std::complex<mjr::ramCanvas1c64F::coordFltType> orbit_sum(0.0, 0.0);
      for(count=0; count<MAXITR ; count++) {
        orbit_sum += z;
        z = z * z + c;
        if (std::abs(z) > 2)
          break;
      }
      if (count == MAXITR) {
        double clr = (std::arg(orbit_sum / static_cast<double>(MAXITR)-c) + std::numbers::pi) / (2.0*std::numbers::pi);        
        // double clr = std::abs(orbit_sum / static_cast<double>(MAXITR)-c);
        // double clr = std::real(orbit_sum / static_cast<double>(MAXITR)-c);
        // double clr = std::imag(orbit_sum / static_cast<double>(MAXITR)-c);
        theRamCanvas.drawPoint(x, y, rcT::colorType::csCColdeColdToHot::c(mjr::math::ivl::wrapCC(clr, 1.0)));
      }
    }
  }

  if (DSCALE > 1)
    theRamCanvas.scaleDownMax(DSCALE);
  theRamCanvas.writeTIFFfile("mandelbrot_meanOrbit.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

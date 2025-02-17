// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      feather.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     The feather fractal.@EOL
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
 @filedetails

  I learned about the "duck" or "feather" fractal from an old blog post: https://algorithmic-worlds.net/blog/blog.php?Post=20110227

  The idea is to iterate a function a fixed number of times for each point in the complex plane, and then color that point according to the magnitude of the
  mean of the orbit points.  In this case we iterate the log of the "iabs" function:

  @f[ \log\left(\Re(z)+\vert\Im(z)\vert+c\right) @f]

  Coloring by the magnitude of the final iterate is interesting; however, I think it's even more interesting to color by the final iterate *relative* to the
  initial condition.  Another interesting choice is to color by the relative argument.
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
  const int DSCALE = 1;
  const int USCALE = 1;
  const int MAXITR = 100;
  const int width  = 1024*USCALE;  
  const int height = 1024*USCALE;
  rcT theRamCanvas(width, height, -1.0, 1.0, -2.6, 0.0);   // Whole feather
  //rcT theRamCanvas(width, height, 0.5, 1.0, -0.25, 0.0); // Just the upper tip

# pragma omp parallel for schedule(static,1)
  for(rcT::coordIntType y=0;y<theRamCanvas.getNumPixY();y++) {
    for(rcT::coordIntType x=0;x<theRamCanvas.getNumPixX();x++) {
      int count;
      std::complex<rcT::coordFltType> z(0.0, 0.0);
      std::complex<rcT::coordFltType> c(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));
      std::complex<rcT::coordFltType> orbit_sum(0.0, 0.0);
      for(count=0; count<MAXITR ; count++) {
        orbit_sum += z;
        z = std::log(std::complex<rcT::coordFltType>(std::real(z), std::abs(std::imag(z))) + c);
      }
      if (count == MAXITR) {
        //double clr = (std::arg(orbit_sum / static_cast<double>(MAXITR)-c) + std::numbers::pi) / (2.0*std::numbers::pi); // Relative argument
        double clr = std::abs(orbit_sum  / static_cast<double>(MAXITR)-c);                                                // Distance from initial point
        //double clr = std::abs(orbit_sum  / static_cast<double>(MAXITR));                                                // Distance from center
        theRamCanvas.drawPoint(x, y, rcT::colorType::csCColdeColdToHot::c(mjr::math::ivl::wrapCC(clr, 1.0)));
      }
    }
  }

  if (DSCALE > 1)
    theRamCanvas.scaleDownMax(DSCALE);
  theRamCanvas.writeTIFFfile("feather.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

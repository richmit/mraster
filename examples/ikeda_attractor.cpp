// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      ikeda_attractor.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw an Ikeda map fractal.@EOL
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

  The one parameter Ikeda map is given by the following iteration:

  @f[ \begin{eqnarray}
       t_n     & = & \frac{2}{5} - \frac{6}{1+x_n^2 + y_n^2} \\
       x_{n+1} & = & 1 + u (x_n\cos(t_n) - y_n\sin(t_n)); \\
       y_{n+1} & = & u (x_n\sin(t_n) + y_n\cos(t_n));     \\
  \end{eqnarray} @f]

  Where @f$ u \ge \frac{3}{5} @f$ is a parameter.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    BSIZ = 7680/2;
  const int    SGSIZ = 400;
  const double SGWID = 1.0;
  const int    MXITR = 1000;
  const int    DRTHS = 100;
  const double U     = .995;

  mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, -6.0, 7.0, -2.0, 10.0);
  for(int xsi=0; xsi<SGSIZ; xsi++) {
    decltype(theRamCanvas)::coordFltType xn = -SGWID/2 + xsi*SGWID/(SGSIZ-1);
    for(int ysi=0; ysi<SGSIZ; ysi++) {
      decltype(theRamCanvas)::coordFltType yn = -SGWID/2 + ysi*SGWID/(SGSIZ-1);
      for(uint64_t i=0;i<MXITR;i++) {
        decltype(theRamCanvas)::coordFltType tmp1 = 0.4 - 6.0 / (1.0+xn*xn+yn*yn);
        decltype(theRamCanvas)::coordFltType tmp2 = 1.0 + U * (xn * std::cos(tmp1) - yn*std::sin(tmp1));
        yn = U * (xn * std::sin(tmp1) + yn*std::cos(tmp1));
        xn = tmp2;
        if(i>DRTHS)
          theRamCanvas.incPxChan(xn, yn);
      }
    }
  }
  theRamCanvas.autoHistStrech();
  theRamCanvas.applyHomoPixTfrm(&decltype(theRamCanvas)::colorType::tfrmPow, 1/5.0);
  theRamCanvas.writeTIFFfile("ikeda_attractor.tiff", 
                             mjr::ramCanvasPixelFilter::ColorSchemeOnChan<decltype(theRamCanvas), 
                             mjr::color3c8b, 
                             mjr::color3c8b::csCColdeFireRamp>(theRamCanvas));
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

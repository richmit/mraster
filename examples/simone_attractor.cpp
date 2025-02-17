// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      simone_attractor.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw fractals inspired by the book Symmetry in Chaos.@EOL
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

  I came acros the Simone Attractor on Paul Bourke's web site: http://www.paulbourke.net/fractals/simone_orbits/
  The iteration is:

  @f[ \begin{eqnarray}
       x_{n+1} & = & \sin(x^2_n - y^2_n+a) \\
       y_{n+1} & = & \cos(2x_ny_n+b)       \\
  \end{eqnarray} @f]

  Note: This example is experimental, and still in work...
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// typedef mjr::ramCanvas3c8b rct;
// typedef rct::colorType ct;

typedef mjr::ramCanvas1c16b::rcConverterColorScheme<mjr::ramCanvas1c16b, mjr::color3c8b, mjr::color3c8b::csCCfractal0RYBCW, true, 100, 0> g2rgb8;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<std::array<mjr::ramCanvas1c16b::coordFltType, 5>> params {
  /* a      b      x0         y0   maxitr */
  {  3.69,  4.511, 0.0,       0.0, 100000000}, // 0
  {  3.64,  1.710, 0.0,       0.0, 100000000}, // 1
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int BSIZ = 7680/4;

  for(decltype(params.size()) j=0; j<params.size(); ++j) {
    mjr::ramCanvas1c16b theRamCanvas(BSIZ, BSIZ, -1.0, 1.0, -1.0, 1.0);
    typename mjr::ramCanvas1c16b::coordFltType a  = params[j][0];
    typename mjr::ramCanvas1c16b::coordFltType b  = params[j][1];
    typename mjr::ramCanvas1c16b::coordFltType x0 = params[j][2];
    typename mjr::ramCanvas1c16b::coordFltType y0 = params[j][3];
    uint64_t maxitr = static_cast<uint64_t>(params[j][4]);

    typename mjr::ramCanvas1c16b::coordFltType xn = x0;
    typename mjr::ramCanvas1c16b::coordFltType yn = y0;
    for(uint64_t i=0;i<maxitr;i++) {
      typename mjr::ramCanvas1c16b::coordFltType tmp = std::sin(xn*xn-yn*yn+a);
      yn = std::cos(2*xn*yn+b);
      xn = tmp;
      if(i>1000) {
        int ix = theRamCanvas.real2intX(xn);
        int iy = theRamCanvas.real2intY(yn);
        theRamCanvas.getPxColorRefNC(ix, iy).tfrmAdd(1);
      }
      if((i % 10000000) == 0)
        std::cout << "ITER(" << j <<  "): " << i << std::endl;
    }

    theRamCanvas.autoHistStrech();
    theRamCanvas.applyHomoPixTfrm(&mjr::ramCanvas1c16b::colorType::tfrmLn1);
    g2rgb8 rcFilt(theRamCanvas);
    std::cout << "ITER(" << j <<  "): " << "TIFF" << std::endl;
    theRamCanvas.writeTIFFfile("simone_attractor_" + mjr::math::str::fmt_int(j, 2, '0') + ".tiff", rcFilt, true);
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

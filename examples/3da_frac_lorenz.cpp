// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      3da_frac_lorenz.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw lorenz attractors with different initial conditions.@EOL
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

  This code generates a fractal-like image from the Lorenz system.  The image represents a rectangle in @f$\mathbb{R}^3@f$ parallel to the @f$x@f$-@f$z@f$
  plane, and hitting the @f$y@f$ axis at @f$1.51@f$. We start the IVP problem with initial conditions in this rectangle.  The color represents the time
  required for the @f$x@f$ value to change sign.

  For reference the Lorenz system is defined by:
  @f[ \begin{array}{lcl}
        \frac{dx}{dt} & = & a(y-x)   \\
        \frac{dy}{dt} & = & x(b-z)-y \\
        \frac{dz}{dt} & = & xy-cz
  \end{array} @f]

  Traditional parameter values are:

  @f[ \begin{array}{lcc}
        a & = & 10   \\
        b & = & 28 \\
        c & = & \frac{8}{3}
  \end{array} @f]

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <functional>                                                    /* STL funcs               C++98    */

#include "ramCanvas.hpp"
#include "MRMathSFUN.hpp"
#include "MRMathODE.hpp"

typedef mjr::ramCanvas1c16b drc_t;
typedef mjr::color3c8b oc_t;
typedef mjr::ramCanvasPixelFilter::FuncHomoTransform<drc_t, oc_t> hpf_t;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
std::array<drc_t::coordFltType, 3> eq(std::array<drc_t::coordFltType, 3> const& p) {
  const drc_t::coordFltType a = 10.0;
  const drc_t::coordFltType b = 28.0;
  const drc_t::coordFltType c = 8.0 / 3;
  return {a * (p[1] - p[0]),
          p[0] * (b - p[2]) - p[1],
          p[0] * p[1] - c * p[2]};
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int XSIZ = 7680/1;
  const int YSIZ = 4320/1;

  drc_t theRamCanvas(XSIZ, YSIZ, -200, 200, 10, 40);

  const drc_t::colorChanType maxPtsPerCurve = drc_t::colorType::maxChanVal;
  const drc_t::coordFltType tDelta          = 0.01;

# pragma omp parallel for schedule(static,1)
  for(drc_t::coordIntType yi=0;yi<theRamCanvas.getNumPixY();yi++) {
    std::cout << "Line: " << yi << std::endl;
    for(drc_t::coordIntType xi=0;xi<theRamCanvas.getNumPixX();xi++) {
    std::array<drc_t::coordFltType, 3> p {theRamCanvas.int2realX(xi), 1.51, theRamCanvas.int2realY(yi) };
      int s = mjr::math::sfun::sgn(p[0]);
      for(drc_t::colorChanType i=0;i<maxPtsPerCurve;i++) {
        std::array<drc_t::coordFltType, 3> p_new = mjr::math::vec::sum(p, mjr::math::ode::rk4<drc_t::coordFltType, 3>(p, eq, tDelta));
        if (mjr::math::sfun::sgn(p[0]) != s) {
          theRamCanvas.drawPoint(xi, yi, i*10);
          break;
        }
      p = p_new;
      }
    }
  }
  theRamCanvas.writeRAWfile("3da_frac_lorenz.mrw");

  /* Write with color map */
  theRamCanvas.writeTIFFfile("3da_frac_lorenz.tiff", hpf_t(theRamCanvas,[](auto inColor) { return oc_t::csCCfractal0RYBCW::c(inColor.getC0()); }));

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */


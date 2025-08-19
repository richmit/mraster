// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      3da_frac_langford.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw langford attractors with different initial conditions.@EOL
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

  This code generates a fractal-like image from the Langford attractor.  The image represents a rectangle inthe @f$x@f$-@f$z@f$ axis plane of
  @f$\mathbb{R}^3@f$. We start the IVP problem with initial conditions in this rectangle.  The color represents the time required for the solution point to
  enter a sphere of radius @f$\frac{1}{2}@f$ centered at @f$(0, 0, \frac{3}{4})@f$.  This sphere intersects the central "stalk" in the Langford attractor, and
  the time to hit this sphere is a proxy for the time required for the solution to be "captured by" or "on" the attractor.

  For reference the Langford system is defined by:
  @f[ \begin{array}{lcl}
        \frac{dx}{dt} & = & (z - \beta)  x - \omega  y \\
        \frac{dy}{dt} & = & \omega  x + (z - \beta)  y \\
        \frac{dz}{dt} & = & \lambda + \alpha  z - \frac{1}{3}z^3 - (x^2 + y^2)  (1 + \rho  z) + \epsilon  z  x^3
  \end{array} @f]

  Traditional parameter values are:

  @f[ \begin{array}{lcc}
        \alpha    & = & \frac{19}{20} \\
        \beta     & = & \frac{7}{10} \\
        \lambda   & = & \frac{3}{5} \\
        \omega    & = & \frac{7}{2} \\
        \rho      & = & \frac{1}{4} \\
        \epsilon  & = & \frac{1}{10} 
  \end{array} @f]

  We use Euler's method to solve the equations with a @f$\Delta{t}@f$ of 0.001 and a maximum of @f$65536 = 2^{16}@f$ iterations.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <valarray>
#include "ramCanvas.hpp"
#include "MRMathSFUN.hpp"

typedef mjr::ramCanvas1c16b drc_t;
typedef mjr::color3c8b oc_t;
typedef mjr::ramCanvasPixelFilter::FuncHomoTransform<drc_t, oc_t> hpf_t;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int XSIZ = 7680/1;
  const int YSIZ = 7680/1;

  drc_t theRamCanvas(XSIZ, YSIZ, -1.6, 1.6, -0.5, 3);

  const drc_t::colorChanType maxPtsPerCurve = drc_t::colorType::maxChanVal;
  const drc_t::coordFltType tDelta          = 0.001;
  const drc_t::coordFltType alpha           =  0.95;
  const drc_t::coordFltType beta            =  0.7;
  const drc_t::coordFltType lambda          =  0.6;
  const drc_t::coordFltType omega           =  3.5;
  const drc_t::coordFltType rho             =  0.25;
  const drc_t::coordFltType epsilon         =  0.1;
  const drc_t::coordFltType zOff            =  0.75;
  const drc_t::coordFltType inRad           =  0.50;

# pragma omp parallel for schedule(static,1)
  for(drc_t::coordIntType yi=0;yi<theRamCanvas.getNumPixY();yi++) {
    std::cout << "Line: " << yi << std::endl;
    for(drc_t::coordIntType xi=0;xi<theRamCanvas.getNumPixX();xi++) {
      drc_t::coordFltType xNew, yNew, zNew;
      drc_t::coordFltType x, y, z;
      x = theRamCanvas.int2realX(xi);
      y = 0;
      z = theRamCanvas.int2realY(yi);
      for(drc_t::colorChanType i=0;i<maxPtsPerCurve;i++) {
        xNew = x + tDelta * ((z - beta) * x - omega * y);
        yNew = y + tDelta * (omega * x + (z - beta) * y);
        zNew = z + tDelta * (lambda + alpha * z - (z*z*z / 3) - (x*x + y*y) * (1 + rho * z) + epsilon * z * x*x*x);
        if (xNew*xNew + yNew*yNew + (zNew-zOff)*(zNew-zOff) < inRad*inRad) {
          theRamCanvas.drawPoint(xi, yi, i);
          break;
        }
        x=xNew;
        y=yNew;
        z=zNew;
      }
    }
  }
  theRamCanvas.writeRAWfile("3da_frac_langford.mrw");

  /* Transform image and write result with color map */
  theRamCanvas.autoHistStrech();
  theRamCanvas.writeTIFFfile("3da_frac_langford.tiff", hpf_t(theRamCanvas,[](auto inColor) { return oc_t::csCCfractal0RYBCW::c(inColor.getC0()); }));

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */


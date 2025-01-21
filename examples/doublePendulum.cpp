// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      doublePendulum.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     For each pixel, simulate a double pendulum system over 2sec and color the pixel according to the pendulum end state.@EOL
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

  Inspired by a reddit post: 
      https://www.reddit.com/r/FractalPorn/comments/1i4gdy8/visualization_of_a_double_pendulum_pixel_x_and_y/

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathCPP.hpp"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    IMXSIZ = 7680/4;
  const int    IMYSIZ = 7680/4;
  const double m1     = 1.0;
  const double m2     = 1.0;
  const double L1     = 1.0;
  const double L2     = 1.0;
  const int    steps  = 200;
  const double h      = 0.01;
  const double g      = 9.80665;
  const double p      = std::numbers::pi;

  mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -0, 2*p, -0, 2*p);
  theRamCanvas.clrCanvasToBlack();

# pragma omp parallel for schedule(static,1)
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    if ((y%100)==0)
      std::cout << y << std::endl;
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      double theta1 = theRamCanvas.int2realX(x);
      double omega1 = 0.0;
      double theta2 = theRamCanvas.int2realY(y);
      double omega2 = 0.0;
      for(int i=0; i<steps; i++) {
        double cd         = cos(theta1-theta2);
        double sd         = sin(theta1-theta2);
        double o12        = omega1*omega1;
        double o22        = omega2*omega2;
        double denom      = 2*m1+m2-m2*cos(2*theta1-2*theta2);
        double new_omega1 = (-g*(2*m1+m2)*sin(theta1)-m2*g*sin(theta1-2*theta2)-2*sd*m2*(o22*L2+o12*L1*cd))/(L1*denom);
        double new_omega2 = (2*sd*(o12*L1*(m1+m2)+g*(m1+m2)*cos(theta1)+o22*L2*m2*cd))/(L2*denom);
        theta1 += h*omega1;
        omega1 += h*new_omega1;
        theta2 += h*omega2;
        omega2 += h*new_omega2;
      }
      double r = mjr::math::ivl::wrapCO(theta2, 2*p)/(2*p);
      double b = mjr::math::ivl::wrapCO(theta1, 2*p)/(2*p);
      double g = mjr::math::ivl::wrapCC((omega1+omega2)/(4*p), 1.0);
      theRamCanvas.getPxColorRefNC(x, y).setChansRGB_dbl(r, g, b);
    }
  }
  theRamCanvas.writeTIFFfile("doublePendulum.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

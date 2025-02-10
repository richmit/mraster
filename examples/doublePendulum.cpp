// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      doublePendulum.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     For each pixel, simulate a double pendulum system over 2sec and color the pixel according to the pendulum end state.@EOL
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

  The equations of motion for the double pendulum may be written as a system of first degree differential equations:
  
  @f[\begin{eqnarray}
    \frac{\mathrm{d}\theta_1}{\mathrm{d}t} & = & \omega_1                                                                                                                                                                                                   \\
    \frac{\mathrm{d}\theta_2}{\mathrm{d}t} & = & \omega_2                                                                                                                                                                                                   \\
    \frac{\mathrm{d}\omega_1}{\mathrm{d}t} & = & \frac{-g (2 m_1+m_2) \sin(\theta_1)-m_2 g \sin(\theta_1-2 \theta_2)-2 m_2 (\omega_2^2 L_2+\omega_1^2 L_1 \cos(\theta_1-\theta_2))\sin(\theta_1-\theta_2)}{L_1 (2 m_1+m_2-m_2 \cos(2 \theta_1-2 \theta_2))} \\
    \frac{\mathrm{d}\omega_2}{\mathrm{d}t} & = & \frac{2 \sin(\theta_1-\theta_2) (\omega_1^2 L_1 (m_1+m_2)+g (m_1+m_2) \cos(\theta_1)+\omega_2^2 L_2 m_2 \cos(\theta_1-\theta_2))}{L_2 (2 m_1+m_2-m_2 \cos(2 \theta_1-2 \theta_2))}
  \end{eqnarray}@f]
  
  Where
  
  @f[\begin{array}{lll}
    L_1      & = & \text{ Length of top bar}              \\
    L_2      & = & \text{ Length of bottom bar}           \\
    m_1      & = & \text{ Mass of top weight}             \\
    m_2      & = & \text{ Mass of bottom weight}          \\
    g        & = & \text{ Acceleration of gravity}        \\
    \theta_1 & = & \text{ Vertical angle of top bar}      \\
    \theta_2 & = & \text{ Vertical angle of bottom bar}   \\
    \omega_1 & = & \text{ Angular velocity of top bar}    \\
    \omega_2 & = & \text{ Angular velocity of bottom bar} 
  \end{array}@f]

  The idea is to run a double pendulum simulation for each pixel.  Each pixel is mapped to a pair of angles -- the x coordinate is mapped to @f$ \theta_1 @f$,
  and the y coordinate is mapped to @f$ \theta_2 @f$.  These angles are used for the initial conditions for the double pendulum equations.  We then solve
  these equations over a time span of 2 seconds using 200 steps of Euler's method.  We dump an image of the final state of the simulation at the end.

  Two ways are provided to map pixels to angles controlled by the boolean `CENTER`.  If it's `true`, then the angles are mapped left to right & top to bottom
  from @f$0@f$ to @f$2\pi@f$.  If it's `false`, we map from @f$-\pi@f$ to @f$\pi@f$.  The effect is that when `CENTER` is true the larger angles are at the
  center of the image, and they are at the corners otherwise.

  Inspired by a reddit post: 
      https://www.reddit.com/r/FractalPorn/comments/1i4gdy8/visualization_of_a_double_pendulum_pixel_x_and_y/

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathIVL.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const bool   CENTER = true;
  const int    IMXSIZ = 7680/2;
  const int    IMYSIZ = 7680/2;
  const double m1     = 1.0;
  const double m2     = 1.0;
  const double L1     = 1.0;
  const double L2     = 1.0;
  const int    steps  = 200;
  const double h      = 0.01;
  const double g      = 9.80665;
  const double p      = std::numbers::pi;

  mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ);
  if (CENTER) 
    theRamCanvas.newRealCoords(0, 2*p, 0, 2*p);
  else
    theRamCanvas.newRealCoords(-p, p, -p, p);
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
  theRamCanvas.writeTIFFfile((CENTER ? "doublePendulum_center.tiff" : "doublePendulum_corner.tiff"));
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */


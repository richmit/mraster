// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      doublePendulumM.cpp
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

  This code makes a movie of time steps of the solution the double pendulum equations.  For the equations, see doublePendulum.cpp.

  In this program we solve solve the equations over a time span of 10 seconds using 1000 steps of Euler's method.  We dump out an image for each step.

  Make Movies:

             ffmpeg -y -framerate 15 -i doublePendulumM_center_%4d.tiff -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2" -c:v libx264 -crf 30 -b:v 0 -pix_fmt yuv420p doublePendulumM_center_100_crf30.mp4;
             ffmpeg -y -framerate 15 -i doublePendulumM_center_%4d.tiff -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2" -c:v libx264 -crf  3 -b:v 0 -pix_fmt yuv420p doublePendulumM_center_100_crf01.mp4;
             ffmpeg -y -framerate 15 -i doublePendulumM_corner_%4d.tiff -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2" -c:v libx264 -crf 30 -b:v 0 -pix_fmt yuv420p doublePendulumM_corner_100_crf30.mp4;
             ffmpeg -y -framerate 15 -i doublePendulumM_corner_%4d.tiff -vf "scale=trunc(iw/2)*2:trunc(ih/2)*2" -c:v libx264 -crf  3 -b:v 0 -pix_fmt yuv420p doublePendulumM_corner_100_crf01.mp4;

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathCPP.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const bool   CENTER = false;
  const int    NUMFRM = 1080;
  const int    IMXSIZ = 7680/8;
  const int    IMYSIZ = 7680/8;
  const double m1     = 1.0;
  const double m2     = 1.0;
  const double L1     = 1.0;
  const double L2     = 1.0;
  const double h      = 0.01;
  const double g      = 9.80665;
  const double p      = std::numbers::pi;

  mjr::ramCanvas1c64F theta1canvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas1c64F omega1canvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas1c64F theta2canvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas1c64F omega2canvas(IMXSIZ, IMYSIZ);

  mjr::ramCanvas3c8b pcolorCanvas(IMXSIZ, IMYSIZ);
  if (CENTER) 
    pcolorCanvas.newRealCoords(0, 2*p, 0, 2*p);
  else
    pcolorCanvas.newRealCoords(-p, p, -p, p);
  pcolorCanvas.clrCanvasToBlack();

  for(int frame=0; frame<NUMFRM; frame++) {
#   pragma omp parallel for schedule(static,1)
    for(int y=0;y<pcolorCanvas.getNumPixY();y++) {
      for(int x=0;x<pcolorCanvas.getNumPixX();x++) {
        double theta1, omega1, theta2, omega2;
        if (frame == 0) {
          theta1 = pcolorCanvas.int2realX(x);
          omega1 = 0.0;
          theta2 = pcolorCanvas.int2realY(y);
          omega2 = 0.0;
        } else {
          theta1 = theta1canvas.getPxColorRefNC(x, y).getC0();
          omega1 = omega1canvas.getPxColorRefNC(x, y).getC0();
          theta2 = theta2canvas.getPxColorRefNC(x, y).getC0();
          omega2 = omega2canvas.getPxColorRefNC(x, y).getC0();
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
        theta1canvas.drawPoint(x, y, theta1);
        omega1canvas.drawPoint(x, y, omega1);
        theta2canvas.drawPoint(x, y, theta2);
        omega2canvas.drawPoint(x, y, omega2);
        double r = mjr::math::ivl::wrapCO(theta2, 2*p)/(2*p);
        double b = mjr::math::ivl::wrapCO(theta1, 2*p)/(2*p);
        double g = mjr::math::ivl::wrapCC((omega1+omega2)/(4*p), 1.0);
        pcolorCanvas.getPxColorRefNC(x, y).setChansRGB_dbl(r, g, b);
      }
    }
    pcolorCanvas.writeTIFFfile((CENTER ? "doublePendulumM_center_" : "doublePendulumM_corner_") + mjr::math::str::fmt_int(frame, 4, '0') + ".tiff");
#   pragma omp critical
    std::cout << "FRAME(" << frame <<  "): " << "DONE" << std::endl;
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */


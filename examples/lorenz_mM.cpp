// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      lorenz_mM.cpp
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

  This code makes a movie of time steps of the solution the Lorenz system.  Each pixel is a complete simulation of the Lorenz system with the pixel's color
  encoding the system state (red for x, green for y, and blue for z).  The initial values for x range from -20 to 20, for z they range from 20 to 50, and y is
  always zero.

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

  And the traditional initial conditions are:
  @f[ \begin{array}{lcc}
        x & = & \frac{1}{10}   \\
        y & = & 0 \\
        z & = & 0
  \end{array} @f]

  This program produces an image sequence which may be rendered into a movie with ffmpeg.  

             ffmpeg -y -framerate 15 -i lorenz_mM_%4d.tiff -vf "scale=trunc(iw/4)*2:trunc(ih/4)*2" -c:v libx264 -crf 30 -b:v 0 -preset veryslow lorenz_mM_100_crf30.mp4;
             ffmpeg -y -framerate 15 -i lorenz_mM_%4d.tiff -vf "scale=trunc(iw/4)*2:trunc(ih/4)*2" -c:v libx264 -crf 20 -b:v 0 -preset veryslow lorenz_mM_100_crf20.mp4;
             ffmpeg -y -framerate 15 -i lorenz_mM_%4d.tiff -vf "scale=trunc(iw/4)*2:trunc(ih/4)*2" -c:v libx264 -crf 10 -b:v 0 -preset veryslow lorenz_mM_100_crf10.mp4;
             ffmpeg -y -framerate 15 -i lorenz_mM_%4d.tiff -vf "scale=trunc(iw/4)*2:trunc(ih/4)*2" -c:v libx264 -crf  3 -b:v 0 -preset veryslow lorenz_mM_100_crf03.mp4;
             ffmpeg -y -framerate 15 -i lorenz_mM_%4d.tiff -vf "scale=trunc(iw/4)*2:trunc(ih/4)*2" -c:v libx264 -crf  0 -b:v 0 -preset veryslow lorenz_mM_100_crf00.mp4;
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"
#include "MRMathIVL.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    NUMFRM = 1000;
  const int    STPPF  = 1000/1000;
  const int    IMXSIZ = 7680/4;
  const int    IMYSIZ = 7680/4;
  const double tDelta = 0.00001*1000;
  const double a      = 10.0;
  const double b      = 28.0;
  const double c      = 8.0 / 3;

  mjr::ramCanvas1c64F xcanvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas1c64F ycanvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas1c64F zcanvas(IMXSIZ, IMYSIZ);

  mjr::ramCanvas3c8b pcolorCanvas(IMXSIZ, IMYSIZ, -20, 20, 20, 50);
  pcolorCanvas.clrCanvasToBlack();

  for(int frame=0; frame<NUMFRM; frame++) {
#   pragma omp parallel for schedule(static,1)
    for(int yi=0;yi<pcolorCanvas.getNumPixY();yi++) {
      for(int xi=0;xi<pcolorCanvas.getNumPixX();xi++) {
        double x, y, z;
        for(int step=0; step<STPPF; step++) {
          if (frame == 0) {
            x = pcolorCanvas.int2realX(xi);
            y = 0.0;
            z = pcolorCanvas.int2realY(yi);
          } else {
            x = xcanvas.getPxColorRefNC(xi, yi).getC0();
            y = ycanvas.getPxColorRefNC(xi, yi).getC0();
            z = zcanvas.getPxColorRefNC(xi, yi).getC0();
            double xNew = x + a * (y - x) * tDelta;
            double yNew = y + (x * (b - z) - y) * tDelta;
            double zNew = z + (x * y - c * z) * tDelta;
            x = xNew;
            y = yNew;
            z = zNew;
          }
          xcanvas.drawPoint(xi, yi, x);
          ycanvas.drawPoint(xi, yi, y);
          zcanvas.drawPoint(xi, yi, z);
        }
        double r = mjr::math::ivl::wrapCO((x+20)/40, 1.0);
        double g = mjr::math::ivl::wrapCO((y+20)/40, 1.0);
        double b = mjr::math::ivl::wrapCO((z-20)/30, 1.0);
        pcolorCanvas.getPxColorRefNC(xi, yi).setChansRGB_dbl(r, g, b);
      }
    }
    pcolorCanvas.writeTIFFfile("lorenz_mM_" + mjr::math::str::fmt_int(frame, 4, '0') + ".tiff");
#   pragma omp critical
    std::cout << "FRAME(" << frame <<  "): " << "DONE" << std::endl;
  }
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */


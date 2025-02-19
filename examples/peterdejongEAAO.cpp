// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      peterdejongEAAO.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Peter de Jong Everywhere All At Once.@EOL
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

  Normally when working with the Peter de Jong map we pick a set of parameters (a-h), pick a seed point, and iterate the map a few million times recording all
  the points the map visits in the plane.  We then use this information to color an image -- for example by counting the number of times the map hit each
  pixel. Not much thought is generally given to the choice of the initial seed point, but it impacts the reaulting image.  This approach is used in the
  example peterdejong.cpp.  A write up of this example may be found here:

     https://www.mitchr.me/SS/swirl/index.html

  I called this example "Peter de Jong Everywhere All At Once" because we are using a grid of seed points and simultaneously doing the above process for each
  pixel in an image.  We don't iterate millions of times -- just 8 in this case.  Then we colorize the result not by hit count, but by the value of the map at
  each pixel.

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
  const int    IMXSIZ = 7680/1;
  const int    IMYSIZ = 7680/1;

  const int    n =  8;
  const double a =  1.4;
  const double b =  2.3;
  const double c =  2.2;
  const double d =  1.9;
  const double e =  1.1;
  const double f =  2.1;
  const double g =  1.1;
  const double h = -2.3;

  mjr::ramCanvas1c64F xcanvas(IMXSIZ, IMYSIZ, -2, 2, -2, 2);
  mjr::ramCanvas1c64F ycanvas(IMXSIZ, IMYSIZ, -2, 2, -2, 2);
  for(int itr=0; itr<n; itr++) {
#   pragma omp parallel for schedule(static,1)
    for(int yi=0;yi<xcanvas.getNumPixY();yi++) {
      for(int xi=0;xi<xcanvas.getNumPixX();xi++) {
        double x, y;
        if (itr == 0) {
          x = xcanvas.int2realX(xi);
          y = xcanvas.int2realY(yi);
        } else {
          x = xcanvas.getPxColorRefNC(xi, yi).getC0();
          y = ycanvas.getPxColorRefNC(xi, yi).getC0();
          double xNew = std::sin(a*y + e) - std::cos(b*x + f);
          double yNew = std::sin(c*x + g) - std::cos(d*y + h);
          x = xNew;
          y = yNew;
        }
        xcanvas.drawPoint(xi, yi, x);
        ycanvas.drawPoint(xi, yi, y);
      }
    }
    std::cout << "ITR(" << itr <<  "): " << "DONE" << std::endl;
  }

  mjr::ramCanvas3c8b p1canvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas3c8b p2canvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas3c8b p3canvas(IMXSIZ, IMYSIZ);
  mjr::ramCanvas3c8b p4canvas(IMXSIZ, IMYSIZ);
# pragma omp parallel for schedule(static,1)
  for(int yi=0;yi<p1canvas.getNumPixY();yi++) {
    for(int xi=0;xi<p1canvas.getNumPixX();xi++) {
      double x = xcanvas.getPxColorRefNC(xi, yi).getC0();
      double y = ycanvas.getPxColorRefNC(xi, yi).getC0();

      double r = mjr::math::ivl::wrapCO((x+2)/4, 1.0);
      double g = 0.0;
      double b = mjr::math::ivl::wrapCO((y+2)/4, 1.0);
      p1canvas.getPxColorRefNC(xi, yi).setChansRGB_dbl(r, g, b);

      g = mjr::math::ivl::wrapCO((x+y+4)/8, 1.0);
      p2canvas.getPxColorRefNC(xi, yi).setChansRGB_dbl(r, g, b);

      p3canvas.drawPoint(xi, yi, decltype(p1canvas)::colorType::csPLYgrey::c(g));

      p4canvas.drawPoint(xi, yi, decltype(p1canvas)::colorType::csCColdeFireRamp::c(r*r));
    }
  }
  p1canvas.scaleDownMean(4);
  p2canvas.scaleDownMean(4);
  p3canvas.scaleDownMean(4);
  p4canvas.scaleDownMean(4);
  p1canvas.writeTIFFfile("peterdejongEAAO_00_c1.tiff");
  p2canvas.writeTIFFfile("peterdejongEAAO_00_c2.tiff");
  p3canvas.writeTIFFfile("peterdejongEAAO_00_c3.tiff");
  p4canvas.writeTIFFfile("peterdejongEAAO_00_c4.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */


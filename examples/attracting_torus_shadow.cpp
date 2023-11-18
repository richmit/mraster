// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      attracting_torus_shadow.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw the intersection of the Attracting Torus Attractor with coordinate plains.@EOL
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

  I first came across this strange attractor in Sprott's book "Elegant Automation" where it is the topic of chapter 43 starting on page 311.  In that chapter,
  on page 315, he has an image of the intersection of the attractor with the z=0 plain.  This program reproduces that image along with the intersections of
  the x=0 & y=0 plain.  As a bonus we produce projections of the curve as well.

  Reference: 
    Sprott, Julien C. Elegant Automation: Robotic Analysis of Chaotic Systems. New Jersey: World Scientific, 2023.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int XSIZ = 7680/1;
  const int YSIZ = 4320/1;
  mjr::ramCanvas3c8b theRamCanvasX0(XSIZ, YSIZ, -10, 10, -10, 10);
  mjr::ramCanvas3c8b theRamCanvasY0(XSIZ, YSIZ, -10, 10, -10, 10);
  mjr::ramCanvas3c8b theRamCanvasZ0(XSIZ, YSIZ, -10, 10, -10, 10);
  mjr::ramCanvas3c8b theRamCanvasXY(XSIZ, YSIZ, -10, 10, -10, 10);
  mjr::ramCanvas3c8b theRamCanvasXZ(XSIZ, YSIZ, -10, 10, -10, 10);
  mjr::ramCanvas3c8b theRamCanvasYZ(XSIZ, YSIZ, -10, 10, -10, 10);

  double isectDistToGo = 1e8; /* How long should the curve be for Z0 ? */
  double curveDistToGo = 1e4; /* How long should the curve be for XY, XZ, & YZ? */

  double a = 4.0; /* Equation paramaters */
  double b = 0.1; /* Equation paramaters */
  double x = 0.0; /* Initial  conditions */
  double y = 2.0; /* Initial  conditions */
  double z = 1.0; /* Initial  conditions */

  double targetDist    = 0.025; /* Size of each step on curve */
  int maxNumUpBisect   = 5;     /* Max times we double tDelta to get > targetDist. */
  int maxNumDownBisect = 10;    /* Max times we half tDelta to get < targetDist. */

  /*  Solve the equations..... */
  double tDelta = 1.0;
  double dist = 0.0;
  double xOld = x;
  double yOld = y;
  double zOld = z;
  double Xdelta, Ydelta, Zdelta, movDist;
  while (dist < isectDistToGo) {
    /*  Find tDelta that gets us bigger than targetDist */
    int numUpBisect = 0;
    do {
      tDelta += (2 * tDelta);
      Xdelta = (y) * tDelta;
      Ydelta = (-x-z*y) * tDelta;
      Zdelta = (y*y-a+b*z) * tDelta;
      movDist = sqrt (fabs (Xdelta * Xdelta + Ydelta * Ydelta + Zdelta * Zdelta));
      numUpBisect++;
    } while ((numUpBisect < maxNumUpBisect) && (movDist < targetDist));
    
    /* Find tDelta that gets us a jump of <targetDist. */
    int numDownBisect = 0;
    do {
      tDelta = tDelta / 2;
      Xdelta = (y) * tDelta;
      Ydelta = (-x-z*y) * tDelta;
      Zdelta = (y*y-a+b*z) * tDelta;
      movDist = sqrt (fabs (Xdelta * Xdelta + Ydelta * Ydelta + Zdelta * Zdelta));
      numDownBisect++;
    } while ((numDownBisect < maxNumDownBisect) && (movDist > targetDist));

    /* Update and draw */
    dist += movDist;
    x = x + Xdelta;
    y = y + Ydelta;
    z = z + Zdelta;
    if (dist < curveDistToGo) {
      theRamCanvasXY.drawPoint(x, y, mjr::ramCanvas3c8b::colorType::cornerColorEnum::WHITE);
      theRamCanvasXZ.drawPoint(x, z, mjr::ramCanvas3c8b::colorType::cornerColorEnum::WHITE);
      theRamCanvasYZ.drawPoint(y, z, mjr::ramCanvas3c8b::colorType::cornerColorEnum::WHITE);
    }
    if(z*zOld<=0.0) {
      if (z < 0) {
        theRamCanvasZ0.drawPoint((x+xOld)/2.0, (y+yOld)/2.0, theRamCanvasZ0.getPxColor((x+xOld)/2.0, (y+yOld)/2.0).setC0(255));
      } else {
        theRamCanvasZ0.drawPoint((x+xOld)/2.0, (y+yOld)/2.0, theRamCanvasZ0.getPxColor((x+xOld)/2.0, (y+yOld)/2.0).setC2(255));        
      }
      theRamCanvasZ0.drawPoint((x+xOld)/2.0, (y+yOld)/2.0, theRamCanvasZ0.getPxColor((x+xOld)/2.0, (y+yOld)/2.0).setC1(255));
    }
    if(x*xOld<=0.0) {
      if (x < 0) {
        theRamCanvasX0.drawPoint((y+yOld)/2.0, (z+zOld)/2.0, theRamCanvasX0.getPxColor((y+yOld)/2.0, (z+zOld)/2.0).setC0(255));
      } else {
        theRamCanvasX0.drawPoint((x+xOld)/2.0, (y+yOld)/2.0, theRamCanvasX0.getPxColor((y+yOld)/2.0, (z+zOld)/2.0).setC2(255));        
      }
      theRamCanvasX0.drawPoint((y+yOld)/2.0, (z+zOld)/2.0, theRamCanvasX0.getPxColor((y+yOld)/2.0, (z+zOld)/2.0).setC1(255));
    }
    if(y*yOld<=0.0) {
      if (y < 0) {
        theRamCanvasY0.drawPoint((x+xOld)/2.0, (z+zOld)/2.0, theRamCanvasY0.getPxColor((x+xOld)/2.0, (z+zOld)/2.0).setC0(255));
      } else {
        theRamCanvasY0.drawPoint((x+xOld)/2.0, (y+yOld)/2.0, theRamCanvasY0.getPxColor((x+xOld)/2.0, (z+zOld)/2.0).setC2(255));        
      }
      theRamCanvasY0.drawPoint((x+xOld)/2.0, (z+zOld)/2.0, theRamCanvasY0.getPxColor((x+xOld)/2.0, (z+zOld)/2.0).setC1(255));
    }
    xOld = x;
    yOld = y;
    zOld = z;
  }

  theRamCanvasXY.writeTIFFfile("attracting_torus_shadowXY.tiff");
  theRamCanvasXZ.writeTIFFfile("attracting_torus_shadowXZ.tiff");
  theRamCanvasYZ.writeTIFFfile("attracting_torus_shadowYZ.tiff");
  theRamCanvasZ0.writeTIFFfile("attracting_torus_shadowZ0.tiff");
  theRamCanvasX0.writeTIFFfile("attracting_torus_shadowX0.tiff");
  theRamCanvasY0.writeTIFFfile("attracting_torus_shadowY0.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
/** @endcond */

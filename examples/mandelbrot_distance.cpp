// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_distance.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     This program draws a mandelbrot set using the "distance".@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2022, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  The normal Mandelbrot raster scan iteration fails to illustrate the thin filaments projecting off the Mandelbrot set -- because the complex number at the
  center of the pixel misses the set, and thus the entire rectangular region of the complex plane covered by the pixel is marked as "escaped".  In order to
  provide some graphical representation of these filaments, we can use a the Milnor and Thurston distance estimator as presented in 'The Science of Fractal
  Images' to draw pixels that have a center "close" to the Mandelbrot set.  This program uses a simple color scheme to label points as described in the
  comment for the pixelStateEnum enumeration.  All of the drawing code is confined to a switch statement at the end of the x loop to make it easy to play
  around with various color schemes.

  Reference: Peitgen, Heinz-Otto and Saupe, Dietmar; 1988; The Science of Fractal Images; ISBN: 0-387-96608-0; pp 192-196
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

enum class pixelStateEnum {UNKNOWN,             // Intermediate state -> ESCAPED || MAXITR1
                           P1BULB,              // In the period 1 bulb ....................................................................... COL: RED
                           P2BULB,              // In the period 2 bulb ....................................................................... COL: MAGENTA
                           MAXITR1,             // Final state: Assumed in the set because it didn't escape aftter MAXITR1 iterations ......... COL: CYAN
                           ESCAPED,             // Intermediate state -> ESCAPED_BUT_CLOSE || ESCAPED_BUT_FAR || ESCAPED_UNKNOWN || MAXITR2
                           ESCAPED_BUT_CLOSE,   // Final state: escaped (>2), but the point is close to the set ............................... COL: BLUE
                           ESCAPED_BUT_FAR,     // Final state: escaped (>2), and the point is NOT close to the set ........................... COL: YELLOW
                           ESCAPED_UNKNOWN,     // Final state: escaped (>2), but we could not compute distance (can't happen) ................ COL: WHITE
                           MAXITR2};            // Final state: escaped (>2), but we never got to MAXZSQ2 (shouldn't happen) .................. COL: GREEN

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  constexpr int      IMXSIZ  = 7680;
  constexpr int      IMYSIZ  = 7680;
  constexpr double   DISTTH  = 0.0002;
  constexpr int      MAXITR2 = 2048;
  constexpr double   MAXZSQ2 = 10000.0;
  constexpr int      MAXITR1 = 2048;
  constexpr double   MAXZSQ1 = 4.0;
  constexpr double   ZROEPS  = 1.0e-5;
  mjr::ramCanvas3c8b theRamCanvas(IMXSIZ, IMYSIZ, -1.9, 0.5, -1.2, 1.2);

# pragma omp parallel for schedule(static,1)
  for(int y=0; y<theRamCanvas.getNumPixY(); y++) {
    for(int x=0; x<theRamCanvas.getNumPixX(); x++) {
      pixelStateEnum pixelState = pixelStateEnum::UNKNOWN;
      std::complex<double> c = theRamCanvas.int2real(x, y);
      double p = std::abs(c-0.25);
      if(std::abs(c+1.0) < 0.25) {
        pixelState = pixelStateEnum::P2BULB;
      } else if(std::real(c) < p-2.0*p*p+0.25) {
        pixelState = pixelStateEnum::P1BULB;
      } else {
        std::complex<double> der(0, 0), z(0, 0);
        int count = 0;
        // First we do at most MAXITR1 standard iterations to see if the point seems to be in the set.
        while(pixelState == pixelStateEnum::UNKNOWN) {
          der = 2.0 * z * der + 1.0;
          z   = z * z + c;
          if (std::norm(z) > MAXZSQ1) {
            pixelState = pixelStateEnum::ESCAPED;
          } else if (count > MAXITR1) {
            pixelState = pixelStateEnum::MAXITR1;
          }
          count++;
        }
        // If it escaped, we see if it was close.
        while(pixelState == pixelStateEnum::ESCAPED) {
          der = 2.0 * z * der + 1.0;
          z   = z * z + c;
          double absz = std::abs(z);
          if (absz > MAXZSQ2) {
            double der_mag = std::abs(der);
            if(der_mag > ZROEPS) {
              double dist = 2.0*std::log(absz)*absz/der_mag;
              if(dist < DISTTH) {
                pixelState = pixelStateEnum::ESCAPED_BUT_CLOSE;
              } else {
                pixelState = pixelStateEnum::ESCAPED_BUT_FAR;
              }
            } else {
              pixelState = pixelStateEnum::ESCAPED_UNKNOWN;
            }
          } else if (count > MAXITR2) {
            pixelState = pixelStateEnum::MAXITR2;
          }
          count++;
        }
      }
      // Now we should have a good pixelState, so we color the pixel.
      switch(pixelState) {
        case pixelStateEnum::P2BULB:             theRamCanvas.drawPoint(x, y, "magenta"); break;
        case pixelStateEnum::P1BULB:             theRamCanvas.drawPoint(x, y, "red");     break;
        case pixelStateEnum::MAXITR1:            theRamCanvas.drawPoint(x, y, "cyan");    break;
        case pixelStateEnum::ESCAPED_BUT_CLOSE:  theRamCanvas.drawPoint(x, y, "blue");    break;
        case pixelStateEnum::ESCAPED_BUT_FAR:    theRamCanvas.drawPoint(x, y, "yellow");  break;
        case pixelStateEnum::ESCAPED_UNKNOWN:    theRamCanvas.drawPoint(x, y, "white");   break;
        case pixelStateEnum::MAXITR2:            theRamCanvas.drawPoint(x, y, "green");   break;
        default:                                 theRamCanvas.drawPoint(x, y, "black");   break;
      }
    }
  }
  theRamCanvas.writeTIFFfile("mandelbrot_distance.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

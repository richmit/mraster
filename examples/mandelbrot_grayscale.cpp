// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mandelbrot_grayscale.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw a grayscale Mandelbrot Set.@EOL
 @std       C++20
 @copyright
  @parblock
  Copyright (c) 1988-2015,2018 Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

  The escape time Mandelbrot rendering algorithm delivers us a single data point, the iteration count, per pixel.  Niavely this maps directly to a monochrome
  image; however, the iteration counts used are frequently beyond 256 -- the limit for most display technology.  Additionally the spatial distribution of
  these counts is quite compressed near the edige of the Mandelbrot set leading to visually unsatsifying results.  In responce a great many schemes have been
  developed to colorize the results, and the vast majoritiy of these schemes can be broken down into standard image processing steps used in scientific image
  analyssis.  This program takes a very directrect approach and produces a deep (16-bit) greyscale TIFF image.  This image may then be loaded up in your
  favroith scietific image analysis pacakger (Mine is Fiji an ImageJ derivative), where one may then quickly play with various coloring schemes.  Most of thje
  classic ones can be reporduced in one or two steps -- a LUT and perhaps a homogenious mathematical filter.  This is a great way to expore known coloring
  schemes, and to develop new ones.

  Notes:
    - Uses a deep, greyscale image.
    - Outputs a TIFF
    - Optimization to avoid the main cardioid boundry and period 2 disk
    - Uses an automatic histogram streach to expand the visual contract.   I leave this step off when using Fiji.
********************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <chrono>                                                        /* time                    C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas1c16b theRamCanvas(7680, 7680, -2.2, 0.8, -1.5, 1.5);
  int count;
  const int NUMITR = mjr::ramCanvas1c16b::colorType::maxChanVal;

  mjr::ramCanvas1c16b::coordFltType cr, ci;
  std::complex<mjr::ramCanvas1c16b::coordFltType> c, z, zero(0.0, 0.0);
  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      cr = theRamCanvas.int2realX(x);
      ci = theRamCanvas.int2realY(y);
      c  = std::complex<mjr::ramCanvas1c16b::coordFltType>(cr, ci);
      mjr::ramCanvas1c16b::coordFltType p = abs(c-0.25);
      if((cr >= p-2.0*p*p+0.25) && abs(c+1.0) >= 0.25) {
        for(z=zero,count=0; (std::norm(z)<4)&&(count<NUMITR); count++,z=z*z+c)
          ;
        if(count < NUMITR)
          theRamCanvas.drawPoint(x, y, static_cast<mjr::ramCanvas1c16b::colorChanType>(count));
      }
    }
  }
  theRamCanvas.autoHistStrech();
  theRamCanvas.writeTIFFfile("mandelbrot_grayscale.tiff");
  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

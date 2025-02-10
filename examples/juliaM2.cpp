// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      juliaM2.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw julia sets on a Mandelbrot Curve.@EOL
 @std       C++20
 @see       https://www.mitchr.me/SS/julia/index.html
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

  Moves $c$ around the Mandelbrot set along the 10th Mandelbrot Curve.  A GIF may be rendered from the frames like this:

       time convert -delay 1 -loop 0 -dispose previous juliaM2_???.tiff juliaM2.gif
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathSTR.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef mjr::ramCanvas3c8b::colorType ct;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  const int    JULIA_MAXITR = 1024;
  const double JULIA_MAXZSQ = 4.0;
  const int    IMGSIZ = 7680/8;
  const int    MANDL_MAXITR = 1024;
  const double MANDL_MAXZSQ = 4.0;
  mjr::ramCanvas3c8b manRamCanvas(IMGSIZ, IMGSIZ, -2.2, 0.8, -1.5, 1.5);

  // Read in our curve -- not much error checking here...
  std::vector<double> mcX;
  std::vector<double> mcY;
  char strBuf[256];
  std::ifstream iStream("../data/mandelbrot_curve_10.txt", std::ios_base::binary);
  if (!(iStream.good()))
    return 1;
  while(iStream.good()) {
    iStream.getline(strBuf, 100, '\n');
    std::string strBufS(strBuf);
    if (strBufS.length() > 0) {
      std::string::size_type pos;
      std::string::size_type tagIdx = strBufS.find_first_of("\t ,");
      mcX.push_back(std::stod(strBufS.substr(0, tagIdx), &pos));
      mcY.push_back(std::stod(strBufS.substr(tagIdx+1), &pos));
    }
  }
  int numPts = static_cast<int>(mcX.size());

  // Draw a refrence mandelbrot set
  for(int y=0;y<manRamCanvas.getNumPixY();y++) {
    for(int x=0;x<manRamCanvas.getNumPixX();x++) {
      std::complex<double> c = manRamCanvas.int2real(x, y);
      std::complex<double> z(0.0, 0.0);
      int count = 0;
      while((std::norm(z)<MANDL_MAXZSQ) && (count<=MANDL_MAXITR)) {
        z=std::pow(z, 2) + c;
        count++;
      }
      if(count < MANDL_MAXITR)
        manRamCanvas.drawPoint(x, y, ct::csCColdeFireRamp::c(static_cast<ct::csIntType>(count*20)));
    }
  }
  // Draw our curve on the refrence mandelbrot set image
  for(int frame=0; frame<numPts; frame++)
    manRamCanvas.drawLine(mcX[frame], mcY[frame], mcX[(frame+1)%numPts], mcY[(frame+1)%numPts], "white");

  // Draw frames
  for(int frame=0; frame<numPts; frame++) {
    // Draw julia curve frames
    mjr::ramCanvas3c8b julRamCanvas(IMGSIZ, IMGSIZ, -2.2, 2.2, -2.2, 2.2);
    std::cout << "Frame: " << frame << " of " << numPts << std::endl;
    std::complex<double> c = std::complex<double>(mcX[frame], mcY[frame]);
    for(int y=0;y<julRamCanvas.getNumPixY();y++) {
      for(int x=0;x<julRamCanvas.getNumPixX();x++) {
        std::complex<double> z(julRamCanvas.int2realX(x), julRamCanvas.int2realY(y));
        int count = 0;
        while((std::norm(z)<JULIA_MAXZSQ) && (count<=JULIA_MAXITR)) {
          z=std::pow(z, 2) + c;
          count++;
        }
        if(count < JULIA_MAXITR)
          julRamCanvas.drawPoint(x, y, ct::csCColdeFireRamp::c(static_cast<ct::csIntType>(count*20)));
      }
    }
    // Draw inset image
    mjr::ramCanvas3c8b setRamCanvas(manRamCanvas);
    setRamCanvas.drawFillCircle(c, 0.04, "white");
    setRamCanvas.scaleDownMean(4);
    julRamCanvas.insertCanvas(setRamCanvas, 0, 0);
    julRamCanvas.drawRectangle(0, 0, IMGSIZ/4, IMGSIZ/4, "white");
    // Label the frame
    julRamCanvas.drawString("MJR 2022", mjr::hershey::font::ROMAN_SL_SANSERIF,  IMGSIZ-IMGSIZ/6, 20, "white", 1, 20);
    // Dump out frame
    julRamCanvas.writeTIFFfile("juliaM2_" + mjr::math::str::fmt_int(frame, 3, '0') + ".tiff");
  }

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

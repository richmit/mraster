// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      circles.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Mathematical art with circles.@EOL
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

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

int main(void) {
  const int    n       = 200000;
  const double pi      = 3.141592653589793238462643383279502884;
  const int    width   = 1920*2;
  const int    height  = 1080*2;
  const double aspect  = 1.0*width/height;
  mjr::ramCanvas3c8b theRamCanvas(width*1, height*1, -1.2*aspect, 1.2*aspect, -1.2, 1.2);

  theRamCanvas.set_drawMode(mjr::ramCanvasRGB8b::drawModeType::ADDCLIP);

  for(int k=0; k<n; k++) {
    // v=017 n=120000
    double x =  (cos(11.0*pi*k/n))*(1.0-3.0/4.0*std::pow(cos(10.0*pi*k/n), 2));
    double y =  -((sin(17.0*pi*k/n))*(1.0-3.0/4.0*pow(cos(12.0*pi*k/n), 2)));
    double s =  1.0/80.0+1.0/10.0*pow(sin(56.0*pi*k/n), 2);
    double r =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/100.0;
    double g =  255.0*(0.5+pow(cos(42.0*pi*k/n), 2))/80.0;
    double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/125.0;

    // // v=002 n=20000
    // double x =  (sin(33.0*pi*k/n) * (cos(19.0*pi*k/n)))*2;
    // double y =  (sin(20.0*pi*k/n) * (cos(33.0*pi*k/n)))*2;
    // double s =  std::pow(sin(43.0*pi*k/n), 3)*0.75+0.5;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/10.0;
    // double g =  255.0*(0.5+pow(cos(46.0*pi*k/n), 2))/17.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;

    // // v=003 n=40000
    // double x =  (sin(33.0*pi*k/n) * (cos(19.0*pi*k/n)))*1;
    // double y =  (sin(20.0*pi*k/n) * (cos(33.0*pi*k/n)))*1;
    // double s =  std::pow(sin(143.0*pi*k/n), 3)*.05+0.0;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/10.0;
    // double g =  255.0*(0.5+pow(cos(46.0*pi*k/n), 2))/17.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;

    // // v=004 n=40000
    // double x =  (sin(33.0*pi*k/n) * (cos(19.0*pi*k/n)))*2;
    // double y =  (sin(20.0*pi*k/n) * (cos(33.0*pi*k/n)))*1.2;
    // double s =  std::pow(sin(33.0*pi*k/n), 3)*.15+0.0;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/10.0;
    // double g =  255.0*(0.5+pow(cos(46.0*pi*k/n), 2))/17.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;

    // // v=005 n=40000
    // double x =  (sin(33.0*pi*k/n) * (cos(19.0*pi*k/n)))*2.3;
    // double y =  (sin(20.0*pi*k/n) * (cos(33.0*pi*k/n)))*2;
    // double s =  std::pow(sin(33.0*pi*k/n), 3)*.55+0.4;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/10.0;
    // double g =  255.0*(0.5+pow(cos(46.0*pi*k/n), 2))/17.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;

    // // v=006 n=10000
    // double x =  (sin(133.0*pi*k/n) * (cos(19.0*pi*k/n)))*1;
    // double y =  (sin(20.0*pi*k/n) * (cos(133.0*pi*k/n)))*1;
    // double s =  std::pow(sin(33.0*pi*k/n), 3)*1.25+0.5;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/10.0;
    // double g =  255.0*(0.5+pow(cos(46.0*pi*k/n), 2))/17.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;

    // // v=007 n=10000
    // double x =  (sin(133.0*pi*k/n) * (cos(19.0*pi*k/n)))*1.2;
    // double y =  (sin(20.0*pi*k/n) * (cos(133.0*pi*k/n)))*.51;
    // double s =  std::pow(sin(133.0*pi*k/n), 3)*1.25+0.5;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/10.0;
    // double g =  255.0*(0.5+pow(cos(46.0*pi*k/n), 2))/17.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;

    // // v=008 n=30000
    // double x =  (sin(53.0*pi*k/n) * (1-cos(33.0*pi*k/n)))*1;
    // double y =  (sin(33.0*pi*k/n) * (1+cos(33.0*pi*k/n)))*0.8;
    // double s =  std::pow(sin(122.0*pi*k/n), 3)*0.0 + 0.1;
    // double r =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;
    // double g =  255.0*(0.5+pow(cos(46.0*pi*k/n), 2))/17.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/17.0;

    // // v=010 n=100000
    // double x =  (cos(1.0*pi*k/n) * (sin(9.0*pi*k/n)))*1.;
    // double y =  (sin(8.0*pi*k/n) * (cos(1.0*pi*k/n)))*1.;
    // double s =  std::abs(sin(1.0*pi*k/n) * (cos(69.0*pi*k/n)))*1.22 + 1.1;
    // double r =  255.0*(0.5+pow(sin(6.0*pi*k/n), 4))/90.0;
    // double g =  255.0*(0.5+pow(cos(6.0*pi*k/n), 2))/87.0;
    // double b =  255.0*(0.5+pow(sin(6.0*pi*k/n), 2))/87.0;

    // // v=011 n=100000
    // double x =  (cos(1.0*pi*k/n) * (sin(9.0*pi*k/n)))*1.;
    // double y =  (sin(8.0*pi*k/n) * (cos(1.0*pi*k/n)))*1.;
    // double s =  std::abs(sin(1.0*pi*k/n) * (cos(29.0*pi*k/n)))*.22 + .1;
    // double r =  255.0*(0.5+pow(sin(6.0*pi*k/n), 4))/90.0;
    // double g =  255.0*(0.5+pow(cos(6.0*pi*k/n), 2))/87.0;
    // double b =  255.0*(0.5+pow(sin(6.0*pi*k/n), 2))/87.0;

    // // v=012 n=120000
    // double x =  (cos(1.0*pi*k*k/n) * (sin(9.0*pi*k/n)))*1.;
    // double y =  (sin(8.0*pi*k/n) * (cos(1.0*pi*k*k/n)))*1.;
    // double s =  std::abs(sin(1.0*pi*k/n) * (cos(29.0*pi*k/n)))*.92 + 1.1;
    // double r =  255.0*(0.5+pow(sin(6.0*pi*k/n), 4))/90.0;
    // double g =  255.0*(0.5+pow(cos(6.0*pi*k/n), 2))/97.0;
    // double b =  255.0*(0.5+pow(sin(6.0*pi*k/n), 2))/97.0;

    // // v=013 n=120000
    // double x =  (cos(1.0*pi*k*k/n) * (sin(9.0*pi*k/n)))*2.0;
    // double y =  (sin(8.0*pi*k/n) * (cos(1.0*pi*k*k/n)))*1.;
    // double s =  std::abs(sin(1.0*pi*k*k/n) * (cos(2.0*pi*k/n)))*.92 + .1;
    // double r =  255.0*(0.5+pow(sin(16.0*pi*k/n), 4))/90.0;
    // double g =  255.0*(0.5+pow(cos(6.0*pi*k/n), 2))/100.0;
    // double b =  255.0*(0.5+pow(sin(6.0*pi*k/n), 2))/100.0;

    // // v=014 n=120000
    // double x =  (cos(11.0*pi*k/n) * (sin(9.0*pi*k/n)))*2.0;
    // double y =  (sin(8.0*pi*k/n) * (cos(11.0*pi*k/n)))*1.;
    // double s =  std::abs(sin(9.0*pi*k/n) * (cos(11.0*pi*k/n)))*.4 + .51;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/200.0;
    // double g =  255.0*(0.5+pow(cos(6.0*pi*k/n), 2))/220.0;
    // double b =  255.0*(0.5+pow(sin(6.0*pi*k/n), 2))/220.0;

    // // v=015 n=120000
    // double x =  (cos(11.0*pi*k/n) * (sin(9.0*pi*k/n)))*2.5;
    // double y =  (sin(8.0*pi*k/n) * (cos(11.0*pi*k/n)))*1.5;
    // double s =  std::abs(sin(9.0*pi*k/n) * (cos(11.0*pi*k*k/n)))*.4 + .51;
    // double r =  255.0*(0.5+pow(sin(26.0*pi*k/n), 4))/200.0;
    // double g =  255.0*(0.5+pow(cos(6.0*pi*k/n), 2))/220.0;
    // double b =  255.0*(0.5+pow(sin(6.0*pi*k/n), 2))/220.0;

    // // v=016 n=120000
    // double x =  (cos(11.0*pi*k/n))*(1.0-3.0/4.0*std::pow(cos(10.0*pi*k/n), 2));
    // double y =  -((sin(17.0*pi*k/n))*(1.0-3.0/4.0*pow(cos(12.0*pi*k/n), 2)));
    // double s =  1.0/80.0+1.0/10.0*pow(sin(56.0*pi*k/n), 2) + .5;
    // double r =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0/54.0;
    // double g =  255.0*(0.5+pow(cos(42.0*pi*k/n), 2))/7.0/38.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0/48.0;

    // // v=017 n=120000
    // double x =  (cos(11.0*pi*k/n))*(1.0-3.0/4.0*std::pow(cos(10.0*pi*k/n), 2))*2.6;
    // double y =  -((sin(17.0*pi*k/n))*(1.0-3.0/4.0*pow(cos(12.0*pi*k/n), 2)))*2.5+.3;
    // double s =  1.0/80.0+1.0/10.0*pow(sin(56.0*pi*k/n), 2) + .5;
    // double r =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0/54.0;
    // double g =  255.0*(0.5+pow(cos(42.0*pi*k/n), 2))/7.0/38.0;
    // double b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0/48.0;

    mjr::ramCanvasRGB8b::rcColor::channelType ri = static_cast<mjr::ramCanvasRGB8b::rcColor::channelType>(r);
    mjr::ramCanvasRGB8b::rcColor::channelType gi = static_cast<mjr::ramCanvasRGB8b::rcColor::channelType>(g);
    mjr::ramCanvasRGB8b::rcColor::channelType bi = static_cast<mjr::ramCanvasRGB8b::rcColor::channelType>(b);

    theRamCanvas.drawCircle(x, y, s, mjr::ramCanvasRGB8b::rcColor(ri, gi, bi));
  }

  // double kernel[51*51];
  // int kSize = 9;
  // theRamCanvas.computeConvolutionMatrixGausian(kernel, kSize, 10);
  // theRamCanvas.convolution(kernel, kSize);
  theRamCanvas.writeTIFFfile("circles.tiff");
}

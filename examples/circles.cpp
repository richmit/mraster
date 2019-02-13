// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      test_draw_primatives.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Benchmark program for pixel draw rates with ramCanvas.@EOL
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

   We instantiate every drawing function in ramCanvas so that we can check for compile time errors and do some basic functionality testing.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <cmath>                                                         /* std:: C math.h          C++11    */


int main(void) {
  const int    n       = 10000;
  const double pi      = 3.141592653589793238462643383279502884;
  const int    width   = 2736; // 1920;
  const int    height  = 1824; // 1080;
  const double aspect  = 1.0*width/height;
  mjr::ramCanvas3c8b theRamCanvas(width*1, height*1, -1.2*aspect, 1.2*aspect, -1.2, 1.2);
  // mjr::ramCanvas3c8b theRamCanvas(width*1, height*1, -0.6*aspect, 0.6*aspect, -0.6, 0.6);

  theRamCanvas.set_drawMode(mjr::ramCanvasRGB8b::drawModeType::ADDCLIP);
  
  // (let* ((n       12000)
  //      (svgf    (mjr_svg_create "exp-svgCircles-OUT-frog.svg" :width 1000 :height 1000 :background "white" :xmin -1.2 :xmax 1.2 :ymin -1.2 :ymax 1.2)))
  // (loop for k from 0 upto n
  //       for x = (* (cos (/ (* 11 pi k) n)) (- 1 (* 3/4 (expt (cos (/ (* 10 pi k) n)) 2))))
  //       for y = (- (* (sin (/ (* 17 pi k) n)) (- 1 (* 3/4 (expt (cos (/ (* 12 pi k) n)) 2)))))
  //       for s = (+ 1/80 (* 1/10 (expt (sin (/ (* (* 56 ) pi k) n)) 2)))
  //       for r = (* 255 (/ (+ 0.5 (expt (sin (/ (* (* 56 ) pi k) n)) 4)) 2))
  //       for g = (* 255 (/ (+ 0.5 (expt (cos (/ (* (* 42 ) pi k) n)) 2)) 2))
  //       for b = (* 255 (/ (+ 0.5 (expt (sin (/ (* (* 56 ) pi k) n)) 4)) 2))
  //       do (mjr_svg_circle svgf x y s :stroke-opacity 0.6 :stroke (list r g b) :stroke-width 0.3))
  // (mjr_svg_finish svgf))

  for(int k=0; k<n; k++) {
    double x =  (cos(11.0*pi*k/n))*(1.0-3.0/4.0*std::pow(cos(10.0*pi*k/n), 2));
    double y =  -((sin(17.0*pi*k/n))*(1.0-3.0/4.0*pow(cos(12.0*pi*k/n), 2)));
    double s =  1.0/80.0+1.0/10.0*pow(sin(56.0*pi*k/n), 2);
    int r =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0;
    int g =  255.0*(0.5+pow(cos(42.0*pi*k/n), 2))/7.0;
    int b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0;

    // double x =  (cos(11.0*pi*k/n))*(1.0-3.0/4.0*std::pow(cos(10.0*pi*k/n), 2));
    // double y =  -((sin(17.0*pi*k/n))*(1.0-3.0/4.0*pow(cos(12.0*pi*k/n), 2)));
    // double s =  1.0/80.0+1.0/10.0*pow(sin(56.0*pi*k/n), 2) + .5;
    // int r =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0/4.0;
    // int g =  255.0*(0.5+pow(cos(42.0*pi*k/n), 2))/7.0/8.0;
    // int b =  255.0*(0.5+pow(sin(56.0*pi*k/n), 4))/7.0/8.0;

    theRamCanvas.drawCircle(x, y, s, mjr::ramCanvasRGB8b::rcColor(r, g, b));
  } 

  // double kernel[51*51];
  // int kSize = 3;
  // theRamCanvas.computeConvolutionMatrixGausian(kernel, kSize, 10);
  // theRamCanvas.convolution(kernel, kSize);
  theRamCanvas.writeTIFFfile("circles.tiff");
}




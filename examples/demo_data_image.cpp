// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      demo_data_image.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Demonstrate "data images" and mjr::ramCanvasPixelFilter.@EOL
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

  One of the most powerful abstractions in modern image processing is to think of an image as a sample drawn from a real function of two variables taken on a
  regular grid.  This simple change of perspective opens up an entire world of mathematical techniques which may now be applied to image processing problems.
  In science and engineering visualization we are presented with the situation in reverse.  That is to say we have one or more two dimensional grids of data
  (frequently thought of as values sampled from some underlying function), and we wish to visualize this data by *synthesizing* a pseudo-color image.  

  For example, consider the visualizing temperature variation across Kansas -- which, in the grand tradition of Physics, we will assume to be a 2D rectangle.
  In this case the data consists of temperatures measured on a regular grid across the state.  In these contexts we frequently store the "data" in something
  like HDF5, and then synthesize the visualization into a "image" manged by something like libPNG.  Because MRaster supports such a broad array of data types
  for colors and color components, we can use MRaster images both for visual images and to house data instead.  People doing multi-spectral imaging are one
  of MRaster's largest user communities.

  Another large MRaster community are people visualizing fractals, ODEs, and chaotic systems.  For this community the underlying function is known, and can be
  computed (sometimes at great cost).  For this group, the data image serves as samples of this underlying function.  Many of the MRaster example programs
  follow this paradigm:

    - demo_data_image.cpp: We use an integer image to hold values of the Mandelbrot escape time function.
    - doublePendulumM.cpp: We use four floating point images to store the state of a differential equation solution
    - sic.cpp & peterdejong.cpp: We use integer images to store a 2D histogram
    - 3da_frac_langford.cpp & 3da_frac_lorenz.cpp: Use integer images to store the time required for an IV to be captured by an attractor.
    - 16bit_data_image_filter.cpp: Read a 16bit greyscale image, and colorizes it several diffrent ways.
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"
#include "MRMathIVL.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas1c16b escDatRC(1024, 1024, -2.2, 0.8, -1.5, 1.5);

  // Fill escDatRC with values for the Mandelbrot escape function.

  escDatRC.colorizeFltCanvas([](decltype(escDatRC)::coordFltType x, decltype(escDatRC)::coordFltType y) {
    std::complex<decltype(escDatRC)::coordFltType> z(0.0, 0.0), c(x, y);
    decltype(escDatRC)::colorChanType count = 0;
    while ((std::abs(z)<2) && (count<256)) { z = z * z + c; count++; }
    return decltype(escDatRC)::colorType((count >= 255 ? 0 : count));
  });

  // escDatRC contains Mandelbrot escape function data, but visually it appears as nothing but a black image -- the maximum grey value at 255 and a total
  // dynamic range of 65536.  See: 16bit_data_image_filter.cpp!

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
}
/** @endcond */

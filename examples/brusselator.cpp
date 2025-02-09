// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      brusselator.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Simulate the brusselator on a random initial set.@EOL
 @keywords  brusselator reaction diffusion models
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

  The Brusselator is a reaction-diffusion model for an autocatalytic chemical reaction in space and time. This system was was proposed by Ilya Romanovich
  Prigogine and Rene Lefever from Universite libre de Bruxelles -- hence the name.  The model is given by the following equations:

  @f[ \begin{eqnarray}
       \frac{\partial u_1}{\partial t} & = & 1-(b+1)u_1+au_1^2u_2+d_1 \left(\frac{\partial^2 u_1}{\partial x_1^2}+\frac{\partial^2 u_1}{\partial x_2^2}\right) \\
       \frac{\partial u_2}{\partial t} & = & bu_1-au_1^2u_2+d_2 \left(\frac{\partial^2 u_2}{\partial x_1^2}+\frac{\partial^2 u_2}{\partial x_2^2}\right)
  \end{eqnarray} @f]

  The functions @f$ u_1 @f$ and @f$ u_2 @f$ represent dimensionless concentrations of two of the reactants -- an activator and an inhibitor.  The values
  @f$ a @f$ and @f$ b @f$ represent normalized reaction rates.  The values @f$ d_1 @f$ and @f$ d_2 @f$ are "diffusion coefficients", and may be
  combined into a single value @f$ d=\frac{d_2}{d_1} @f$ like this:

  @f[ \begin{eqnarray}
       \frac{\partial u_1}{\partial t} & = & 1-(b+1)u_1+au_1^2u_2 \left(\frac{\partial^2 u_1}{\partial x_1^2}+\frac{\partial^2 u_1}{\partial x_2^2}\right) \\
       \frac{\partial u_2}{\partial t} & = & bu_1-au_1^2u_2+d \left(\frac{\partial^2 u_2}{\partial x_1^2}+\frac{\partial^2 u_2}{\partial x_2^2}\right)
  \end{eqnarray} @f]

  In the code below, we use the following values for the parameters:

  @f[ \begin{array}{lcc}
       a & = & 9 \\
       b & = & \frac{98}{10} \\
       d & = & 3
  \end{array} @f]

  We use a simple finite differences method to solve the equations with a step size of @f$ \Delta t=0.007 @f$ over 3000 steps.  The spatial grid has a grid
  size of @f$ h=0.3 @f$.  The spatial second derivatives at a point @f$ (x,y) @f$ are approximated with the five point stencil":

  @f[ \frac{\partial^2 u_j}{\partial x_1^2}+\frac{\partial^2 u_j}{\partial x_2^2} \approx \frac{u_j(x+h, y)+u_j(x-h, y)+u_j(x, y+h)+u_j(x, y-h)-4u_j(x,y)}{h^2} @f]

  The code uses four images to store the state of the system at two steps.  At each time step it uses two of the images to update the other two.  This doubles
  the RAM required, but simplifies the code and eliminates the need for swapping data.  At the end of the run the last updated state images are combined into
  a floating point RGB image.  This image is then histogram stretched, and written to disk as a 24-bit RGB TIFF.

*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void) {
  std::random_device rd;
  std::minstd_rand0 rEng(rd());
  std::uniform_real_distribution<double> uniform_dist_double(1.0e-5, 1.0);
  int width  = 7680/8;
  int height = 4320/8;

  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c64F theRamCanvas(width, height);

  std::vector<mjr::ramCanvas1c64F> imgu1{mjr::ramCanvas1c64F(width, height), mjr::ramCanvas1c64F(width, height)};
  std::vector<mjr::ramCanvas1c64F> imgu2{mjr::ramCanvas1c64F(width, height), mjr::ramCanvas1c64F(width, height)};

  mjr::ramCanvas1c64F::pointIntVecType st { {0,-1}, {0,1}, {-1,0}, {1,0}};

  int    N = 3000;
  double h = 0.3;
  double t = 0.007;
  double a = 9.0;
  double b = 9.8;
  double d = 3.0;

  for(int y=0;y<theRamCanvas.getNumPixY();y++) {
    for(int x=0;x<theRamCanvas.getNumPixX();x++) {
      imgu1[0].drawPoint(x, y, uniform_dist_double(rEng));
      imgu2[0].drawPoint(x, y, uniform_dist_double(rEng));
    }
  }

  int i_in, i_ou;
  double maxv = 0;
  for(int step=0; step<N; step++) {
    i_in = (step%2);
    i_ou = ((step+1)%2);
    if (0==(step%100))
      std::cout << "STEP: " << step << std::endl;
# pragma omp parallel for schedule(static,1)
    for(mjr::ramCanvas3c64F::coordIntType y=0;y<theRamCanvas.getNumPixY();y++) {
      for(mjr::ramCanvas3c64F::coordIntType x=0;x<theRamCanvas.getNumPixX();x++) {

        double u1_sum = 0;
        double u2_sum = 0;
        for(mjr::ramCanvas1c64F::pointIntType const &p: st) {
          u1_sum += imgu1[i_in].getPxColorChanWrap<0>(x+p.x, y+p.y);
          u2_sum += imgu2[i_in].getPxColorChanWrap<0>(x+p.x, y+p.y);
        }

        double u1_c = imgu1[i_in].getPxColor(x, y).getC0();
        double u2_c = imgu2[i_in].getPxColor(x, y).getC0();

        double du1_c = t*(1.0-(b+1)*u1_c+a*u1_c*u1_c*u2_c+(u1_sum-4*u1_c)/(h*h));
        double du2_c = t*(b*u1_c-a*u1_c*u1_c*u2_c+d*(u2_sum-4*u2_c)/(h*h));

        double u1 = u1_c + du1_c;
        double u2 = u2_c + du2_c;

        maxv = std::max(maxv, std::max(u1, u2));

        imgu1[i_ou].drawPoint(x, y, u1);
        imgu2[i_ou].drawPoint(x, y, u2);
      }
    }
    if (maxv > 1e10) {
      std::cout << "Solution Failure at step " << step << std::endl;
      return 1;
    } else if (maxv < 0.0001) {
      std::cout << "Zero Solution at step " << step << std::endl;
      return 1;
    }
  }

  imgu1[i_ou].autoHistStrech();
  imgu2[i_ou].autoHistStrech();
  for(int y=0;y<theRamCanvas.getNumPixY();y++)
    for(int x=0;x<theRamCanvas.getNumPixX();x++)
      theRamCanvas.drawPoint(x, y, mjr::color3c64F(std::abs(imgu1[i_ou].getPxColorNC(x, y).getC0()), 
                                                   0.0, 
                                                   std::abs(imgu2[i_ou].getPxColorNC(x, y).getC0())));
  mjr::ramCanvas1c64F::rcConverterRGBbyte<mjr::ramCanvas3c64F> rcConv(theRamCanvas);
  theRamCanvas.writeTIFFfile("brusselator.tiff", rcConv, true);

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;
  return 0;
}
/** @endcond */

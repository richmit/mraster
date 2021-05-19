// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      newton_vs.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw Fractals via Newton-like methods.@EOL
 @std       C++11
 @copyright 
  @parblock
  Copyright (c) 1988-2015, 2017, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

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

     Maxima: f:sin(z); z-f/diff(f, z);

 Laguerre's method:
 \f[x_k\f]
 \f[G=\frac{f'(x_n)}{f(x_n)}\f]
 \f[H=G^2-\frac{f''(x_n)}{f(x_n)}\f]
 \f[a=\frac{n}{G+-\sqrt{(n-1)(nH-G^2)}}\f]
 \f[x_{n+1}=x_n-a\f]

        f0v=f0(x)
        if(abs(f0v)<eps) ERROR
        f1v=f1(x)
        f2v=f2(x)
        G=f1v/f0v
        G2=G*G
        H=G2-f2v/f0v
        sqr=(n-1)*(n*H-G2)
        if(sqr<0) ERROR
        sq=sqrt(sqr)
        b1=G+sq
        b2=G-sq
        if(abs(b1)>abs(b2))
          b=b1
        else
          b=b2
        fi
        if(abs(b)<eps) ERROR
        a=n/b
        x=x-a

 Newton's
 \f[x=x-\frac{f(x_n)}{f'(x_n)}\f]

        f0v=f0(x)
        f1v=f1(x)
        if(abs(f1v)<eps) ERROR
        x=x-f0v/f1v

 Halley's
 \f[x_n-\frac{f(x_n)}{f'(x_n)}\left[1-\frac{f(x_n)}{f'(x_n)}\cdot\frac{f''(x_n)}{2f'(x_n)}\right]^{-1}\f]

        f0v=f0(x)
        f1v=f1(x)
        if(abs(f1v)<eps) ERROR
        f2v=f2(x)
        G=f0v/f1v
        b=1-G*f2v/f1v
        if(abs(b)<eps) ERROR
        a=G/b
         xnext=x-a

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <complex>                                                       /* Complex Numbers         C++11    */
#include <vector>                                                        /* STL vector              C++11    */ 
#include <iostream>                                                      /* C++ iostream            C++11    */

enum class whyStopNV { DIVZERO,   //!< Divide by zero (zeroTol)
                       TOOBIG,    //!< Iterate got too big (> escapeMod)
                       CONVERGEU, //!< Converged in the upper half plane
                       CONVERGEL, //!< Converged in the lower half plane
                       TOOLONG    //!< Too many iterations (> MaxCount)
                     };


enum class solMethNV { NEWTON,    //!< Use Newton's method
                       HALLEY,    //!< Use Halley's method
                       LAGUERRE   //!< Use laguerre's method
                     };

int main(void) {
  const double escapeMod = -32.0;
  const int    MaxCount  = 64;
  const float  Tol       = 0.0001;
  const int    numToKeep = 1;
  whyStopNV why;           
  mjr::ramCanvas3c8b theRamCanvas(3840, 2160, -1.5, 1.5, -1.5, 1.5);
  std::vector<solMethNV> methodsToDo({solMethNV::NEWTON, solMethNV::HALLEY, solMethNV::LAGUERRE});

  for(auto method : methodsToDo) {
    mjr::color3c8b aColor(255, 255, 255);

    for(int y=0;y<theRamCanvas.get_numYpix();y++) {
      if(y%512==0)
        std::cout << "Case: " << (int)method << " Line: " << y << std::endl;
      for(int x=0;x<theRamCanvas.get_numXpix();x++) {
        std::complex<double> z(theRamCanvas.int2realX(x), theRamCanvas.int2realY(y));

        std::vector<std::complex<double>> lastZs(numToKeep);
        int  count = 0;
        double maxMod = 0.0;
        while(1) {
          if (count >= MaxCount) {
            why = whyStopNV::TOOLONG;
            break;
          }

          std::complex<double> f0v=sin(cos(z));
          std::complex<double> f1v=-sin(z)*cos(cos(z));
          std::complex<double> f2v=(-sin(z)*sin(z)*sin(cos(z)))-cos(z)*cos(cos(z));

          switch(method) {
            case solMethNV::NEWTON : {
              if(abs(f1v) < Tol) {
                why = whyStopNV::DIVZERO;
                break;
              }
              z=z-f0v/f1v; 
              break;
            }
            case solMethNV::HALLEY : {
              if(abs(f1v) < Tol) {
                why = whyStopNV::DIVZERO;
                break;
              }                   
              std::complex<double> G=f0v/f1v;
              std::complex<double> b=1.0-G*f2v/f1v;
              if(abs(b) < Tol) {
                why = whyStopNV::DIVZERO;
                break;
              }
              std::complex<double> a=G/b;
              z = z-a;
              break;
            }
            case solMethNV::LAGUERRE : {
              std::complex<double> pdeg = 4.0;
              if(abs(f0v) < Tol) {
                break;
              }                   
              std::complex<double> G=f1v/f0v;
              std::complex<double> G2=G*G;
              std::complex<double> H=G2-f2v/f0v;
              std::complex<double> sqr=(pdeg-1.0)*(pdeg*H-G2);
              std::complex<double> sq=sqrt(sqr);
              std::complex<double> b1=G+sq;
              std::complex<double> b2=G-sq;
              std::complex<double> b=b2;
              if(abs(b1)>abs(b2))
                b=b1;
              if(abs(b) < Tol) {
                why = whyStopNV::DIVZERO;
                break;
              }
              std::complex<double> a=pdeg/b;
              z = z-a;
              break;
            }
          }
      
          double modz = abs(z);
          lastZs[count%numToKeep] = z;
          if(modz>maxMod) {
            maxMod = modz;
          }
          if(count >= numToKeep) {  // Criteria for convergeance:  Last numToKeep z values must be within Tol of each other.
            bool allEqual = true;
            for(int i=1; i<numToKeep; i++)
              if(abs(lastZs[0]-lastZs[i])>Tol) {
                allEqual = false;
                break;
              }
            if(allEqual) {
              if(z.real() > 0) {
                why = whyStopNV::CONVERGEU;
              } else {
                why = whyStopNV::CONVERGEL;
              }
              break;
            }
          }
          if((escapeMod>0) && (modz>escapeMod)) {
            why = whyStopNV::TOOBIG;
            break;
          }
          count++;
        }

        int ccol = (2*4*count);
        int mcol = ((int)(2*8*maxMod));
        switch(why) {
          case whyStopNV::TOOLONG   : theRamCanvas.drawPoint(x, y, aColor.cmpColorRamp((mcol)%(2*256),      "MWM")); break;
          case whyStopNV::CONVERGEU : theRamCanvas.drawPoint(x, y, aColor.cmpColorRamp((mcol+ccol)%(2*256), "BWB")); break;
          case whyStopNV::CONVERGEL : theRamCanvas.drawPoint(x, y, aColor.cmpColorRamp((mcol+ccol)%(2*256), "RWR")); break;
          case whyStopNV::TOOBIG    : theRamCanvas.drawPoint(x, y, mjr::color3c8b(0,        0,        0));           break;
          case whyStopNV::DIVZERO   : theRamCanvas.drawPoint(x, y, aColor.cmpColorRamp((mcol+ccol)%(2*256), "CWC")); break;
        }
      }
    }
  
    switch(method) {
      case solMethNV::NEWTON   : theRamCanvas.writeTIFFfile("newton_vs_newton.tiff"  ); break;
      case solMethNV::HALLEY   : theRamCanvas.writeTIFFfile("newton_vs_halley.tiff"  ); break;
      case solMethNV::LAGUERRE : theRamCanvas.writeTIFFfile("newton_vs_laguerre.tiff"); break;
    }
  }
}

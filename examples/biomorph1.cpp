// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      biomorph1.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Draw some classical versions of Clifford Pickover's biomorph fractals.@EOL
 @std       C++14
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
***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

#include <complex>                                                       /* Complex Numbers         C++11    */

int main(void) {
  const int NUMITR = 2000;
  const int CSIZE  = 7680;
  const int LIM    = 4;
  int count;
  std::complex<float> oneone(1,1), z;
    
  mjr::ramCanvas3c8b theRamCanvasA(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasB(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasC(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasD(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasE(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasF(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasG(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasH(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasI(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasJ(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasK(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);
  mjr::ramCanvas3c8b theRamCanvasL(CSIZE, CSIZE, 0.2, 1.2, 0.2, 1.2);

  for(int y=0;y<theRamCanvasA.get_numYpix();y++) {
    if((y%(CSIZE/10))==0)
      std::cout << " LINE: " << y << "/" << CSIZE << std::endl;
    for(int x=0;x<theRamCanvasA.get_numXpix();x++) {
      for(z=std::complex<double>(theRamCanvasA.int2realX(x),theRamCanvasA.int2realY(y)),count=0;
          ((std::abs(std::real(z))<LIM)||(std::abs(std::imag(z))<LIM))&&(count<=NUMITR);
          count++,z=static_cast<std::complex<float>>(std::pow(z, 5))+oneone) ;
      if(count < NUMITR) {
        // A
        theRamCanvasA.drawPoint(x, y, mjr::color3c8b().cmpClrCubeRainbow(mjr::intWrap(count*500, 255*6+1)));
        // B
        theRamCanvasB.drawPoint(x, y, mjr::color3c8b().cmpClrCubeRainbow(mjr::intWrap(static_cast<int>(std::norm(z)/1000), 255*6+1)));
        // C
        theRamCanvasC.drawPoint(x, y, mjr::color3c8b().cmpClrCubeRainbow(mjr::intWrap(static_cast<int>(std::abs(std::imag(z))), 255*6+1)));
        // D
        theRamCanvasD.drawPoint(x, y, mjr::color3c8b().cmpClrCubeRainbow(mjr::intWrap(static_cast<int>(std::abs(std::real(z))), 255*6+1)));
        // E
        if(std::abs(std::real(z))<std::abs(std::imag(z)))
          theRamCanvasE.drawPoint(x, y, mjr::color3c8b("red"));
        else
          theRamCanvasE.drawPoint(x, y, mjr::color3c8b("blue"));
        // F
        if(std::abs(std::real(z))<std::abs(std::imag(z)))
          theRamCanvasF.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(std::abs(static_cast<int>(std::real(z))), 255*1-1), "0R"));
        else
          theRamCanvasF.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(std::abs(static_cast<int>(std::imag(z))), 255*1-1), "0B"));
        // G
        if(std::abs(std::real(z))<std::abs(std::imag(z)))
          theRamCanvasG.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::norm(z)/1000), 255*1-1), "0R"));
        else
          theRamCanvasG.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::norm(z)/1000), 255*1-1), "0B"));
        // H
        if(std::real(z) < 0) {
          if(std::imag(z) < 0) {
            theRamCanvasH.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(std::abs(static_cast<int>(std::real(z))), 255*1-1), "0R"));
          } else {
            theRamCanvasH.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(std::abs(static_cast<int>(std::real(z))), 255*1-1), "0B"));
          }
        } else {
          if(std::imag(z) < 0) {
            theRamCanvasH.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(std::abs(static_cast<int>(std::real(z))), 255*1-1), "0M"));
          } else {
            theRamCanvasH.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(std::abs(static_cast<int>(std::real(z))), 255*1-1), "0C"));
          }
        }
        // I
        if(std::real(z) < 0) {
          if(std::imag(z) < 0) {
            if(std::imag(z) < std::real(z) ) {
              theRamCanvasI.drawPoint(x, y, mjr::color3c8b("red"));
            } else {
              theRamCanvasI.drawPoint(x, y, mjr::color3c8b("yellow"));
            }
          } else {
            theRamCanvasI.drawPoint(x, y, mjr::color3c8b("blue"));
          }
        } else {
          if(std::imag(z) < 0) {
            theRamCanvasI.drawPoint(x, y, mjr::color3c8b("magenta"));
          } else {
            if(std::imag(z) < std::real(z) ) {
              theRamCanvasI.drawPoint(x, y, mjr::color3c8b("cyan"));
            } else {
              theRamCanvasI.drawPoint(x, y, mjr::color3c8b("green"));
            }
          }
        }
        // J
        if(std::real(z) < 0) {
          if(std::imag(z) < 0) {
            if(std::imag(z) < std::real(z) ) {
              theRamCanvasJ.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::abs(std::real(z))), 255*1-1), "0R")); 
            } else {
              theRamCanvasJ.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::abs(std::real(z))), 255*1-1), "0Y")); 
            }
          } else {
            theRamCanvasJ.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::abs(std::real(z))), 255*1-1), "0B"));   
          }
        } else {
          if(std::imag(z) < 0) {
            theRamCanvasJ.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::abs(std::real(z))), 255*1-1), "0M"));   
          } else {
            if(std::imag(z) < std::real(z) ) {
              theRamCanvasJ.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::abs(std::real(z))), 255*1-1), "0C")); 
            } else {
              theRamCanvasJ.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intWrap(static_cast<int>(std::abs(std::real(z))), 255*1-1), "0G")); 
            }
          }
        }
        // K
        theRamCanvasK.drawPoint(x, y, mjr::color3c8b().cmpClrCubeRainbow(mjr::intWrap(static_cast<int>((std::arg(z)+3.14)*255), 255*6+1)));
        // L
        if(std::abs(std::real(z))<std::abs(std::imag(z)))
          theRamCanvasL.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intClamp(static_cast<int>(std::abs(std::real(z))/100), 255*1-1), "0R"));
        else
          theRamCanvasL.drawPoint(x, y, mjr::color3c8b().cmpColorRamp(mjr::intClamp(static_cast<int>(std::abs(std::imag(z))/100), 255*1-1), "0B"));
      }
    }
  }
  theRamCanvasA.writeTIFFfile("biomorph1A.tiff");
  theRamCanvasB.writeTIFFfile("biomorph1B.tiff");
  theRamCanvasC.writeTIFFfile("biomorph1C.tiff");
  theRamCanvasD.writeTIFFfile("biomorph1D.tiff");
  theRamCanvasE.writeTIFFfile("biomorph1E.tiff");
  theRamCanvasF.writeTIFFfile("biomorph1F.tiff");
  theRamCanvasG.writeTIFFfile("biomorph1G.tiff");
  theRamCanvasH.writeTIFFfile("biomorph1H.tiff");
  theRamCanvasI.writeTIFFfile("biomorph1I.tiff");
  theRamCanvasJ.writeTIFFfile("biomorph1J.tiff");
  theRamCanvasK.writeTIFFfile("biomorph1K.tiff");
  theRamCanvasL.writeTIFFfile("biomorph1L.tiff");
}

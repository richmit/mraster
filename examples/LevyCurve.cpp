// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      LevyCurve.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @brief     Draws Levy Curve with the Chaos Game algorithm.@EOL
 @std       C++23
 @see       https://www.mitchr.me/SS/LevyCurveChaosGame/index.html
 @copyright 
  @parblock
  Copyright (c) 2024, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.
  
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

  A chaos game that generates a Levy Curve:

  Start at a random point.  Randomly select one of two transformations, and transform the point.  Repeat this process with the new point.  The two
  transformations are given by:

  @f[ \begin{array}{ll}
        T_1(\vec{x}) & =  \left[ {\begin{array}{rr}
                                  \frac{1}{2} & \frac{1}{2} \\
                                 -\frac{1}{2} & \frac{1}{2} \\
                                \end{array} } 
                          \right]
                          \cdot\vec{x} \\
        T_2(\vec{x}) & =  \left[ {\begin{array}{rr}
                                  \frac{1}{2} & -\frac{1}{2} \\
                                  \frac{1}{2} &  \frac{1}{2} \\
                                \end{array} } 
                          \right]
                          \cdot\vec{x}-
                          \left[ {\begin{array}{rr}
                                    \frac{1}{2} \\
                                    \frac{1}{2} \\
                                  \end{array} } 
                          \right]
      \end{array} 
  @f] 

  We can easily expand these transforms into C code with maxima:

  #+BEGIN_SRC maxima

                  A : matrix([.5,  .5], [-.5, .5]);
                  B : matrix([.5, -.5], [ .5, .5]);
                  C : matrix([-.5], [-.5]);
                  X : matrix([x], [y]);
                  display2d:false;
                  A.X;
                      matrix([0.5*y+0.5*x],[0.5*y-0.5*x])
                  B.X+C;
                      matrix([(-0.5*y)+0.5*x-0.5],[0.5*y+0.5*x-0.5])

  #+END_SRC      
*/
/*******************************************************************************************************************************************************.H.E.**/
/** @cond exj */

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main() {
  std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
  mjr::ramCanvas3c8b theRamCanvas(2048, 2048, -1.5, 0.7, -1.6, .6);

  mjr::ramCanvas3c8b::colorType        acl;
  mjr::point2d<double>                 cpt = {0.0, 0.0};
    for(int n=0;n<100000;n++) {
      if (rand()%2) {
        cpt = { 0.5*cpt.y+0.5*cpt.x,        0.5*cpt.y-0.5*cpt.x };
        acl = mjr::ramCanvas3c8b::colorType::cornerColorEnum::RED;
      } else {
        cpt = { (-0.5*cpt.y)+0.5*cpt.x-0.5, 0.5*cpt.y+0.5*cpt.x-0.5  };
        acl = mjr::ramCanvas3c8b::colorType::cornerColorEnum::GREEN;
      }
      if(n > 100) 
        theRamCanvas.drawPoint(cpt, acl);
    }

  theRamCanvas.writeTIFFfile("LevyCurve.tiff");

  std::chrono::duration<double> runTime = std::chrono::system_clock::now() - startTime;
  std::cout << "Total Runtime " << runTime.count() << " sec" << std::endl;

  return 0;
}
/** @endcond */

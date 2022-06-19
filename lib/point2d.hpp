// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      point2d.hpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Internal include file for ramCanvas types.@EOL
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

#ifndef MJR_INCLUDE_point2d

#include <iomanip>                                                       /* C++ stream formatting   C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */

#include <type_traits>                                                   /* C++ metaprogramming     C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <vector>                                                        /* STL vector              C++11    */
#include <tuple>                                                         /* STL tuples              C++11    */

// Put everything in the mjr namespace
namespace mjr {
  /** Handy class to hold a point in 2D (integer or real) */
  template <class coordT>
  class point2d {

      static_assert(std::is_arithmetic<coordT>::value,
                    "ERROR: coordT parameter of point2d template must be a numeric type.");

    public:
      coordT x; //!< X coordinate
      coordT y; //!< Y coordinate

      /** @name Constructors */
      //@{
      point2d() = default;
      point2d(std::initializer_list<coordT> iList) { auto p=iList.begin();  x=*p; y=*(++p);         }
      point2d(const point2d &aPoint)               { x=aPoint.x;            y=aPoint.y;             }
      point2d(coordT newX, coordT newY)            { x=newX;                y=newY;                 }
      point2d(std::complex<coordT> aComplex)       { x=aComplex.real();     y=aComplex.imag();      }
      point2d(std::tuple<coordT, coordT> aTuple)   { x=std::get<0>(aTuple); y=std::get<1>(aTuple);  }
      point2d(std::vector<coordT> aVector)         { x=aVector[0];          y=aVector[1];           }
      point2d(coordT* aPtr)                        { x=aPtr[0];             y=aPtr[1];              }
//      point2d(coordT[2] aArray)                      { x=aArray[0];           y=aArray[1];            }
      //@}

      ~point2d() = default;
  }; // end point2d
} // end namespace mjr

#define MJR_INCLUDE_point2d
#endif

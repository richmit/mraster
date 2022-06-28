// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      mjrmath.hpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Include file defining several mapping and clamping functions.@EOL @EOL
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
  This file contains several definitions for inline functions useful for mapping and clamping integers and floats.
***************************************************************************************************************************************************************/

/* Some simple linear mapping and clamping functions. */

#ifndef MJR_INCLUDE_mjrmath

#include <type_traits>                                                   /* C++ metaprogramming     C++11    */
#include <cmath> 
#include <ctgmath>

// Put everything in the mjr namespace
namespace mjr {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Yep.  Pi */
  const static double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Wrap an integer to the range [0,maxValue] via a modulus like function that wraps the value onto the range (i.e. maxOutValue+1 will map to 0).
   @param anInt The value to be wrapped
   @param maxOutValue The maximum output value
   @return The wrapped value. */
  inline int intWrap(int anInt, int maxOutValue) {
//  MJR TODO NOTE <2022-06-28T09:54:40-0500> intWrap: Consider an right open interval like we do for realWrap...
    if ((anInt < 0) || (anInt > maxOutValue)) {
      int tmp = anInt % (maxOutValue + 1);
      if(tmp < 0)
        return maxOutValue + tmp;
      else
        return tmp;
    } else {
      return anInt;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Wrap a floating point value to the range [0, maxValue) via a modulus like function that wraps the value onto the range (i.e. maxOutValue will map to 0).
    Handy way to wrap angles in degrees to [0, 360).
   @param aReal The value to be wrapped
   @param maxOutValue The maximum output value
   @return The wrapped value. */
  template <typename realType>
  inline realType realWrap(realType aReal, realType maxOutValue) {
    if ((aReal < static_cast<realType>(0)) || (aReal >= maxOutValue)) { // yes, I mean >= here... It's an == compare on floats, but it works in this case.
      realType tmp = std::fmod(aReal, maxOutValue);
      if(tmp < static_cast<realType>(0))
        return maxOutValue+tmp;
      else
        return tmp;
    } else {
      return aReal;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Clamp an integer to the range [0,maxOutValue] via a true clamping function (i.e. values below the range map to 0, and values above the range map to
    maxOutValue.).
    @param anInt The value to be clamped
    @param maxOutValue The maximum output value
    @return The wrapped value. */
  inline int intClamp(int anInt, int maxOutValue) {
    if(anInt < 0)
      return 0;
    if(anInt > maxOutValue)
      return maxOutValue;
    return anInt;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Clamp a floating point number to the range [0,1] via a true clamping function (i.e. values less than 0 map to 0, and values above 1 map to 1.).
    @param aReal The value to be clamped
    @return The wrapped value. */
  template <typename realType>
  inline realType unitClamp(realType aReal) {
    static_assert(std::is_floating_point<realType>::value, "ERROR(unitClamp template): realType must be a floating point type.");
    if(aReal < static_cast<realType>(0))
      return static_cast<realType>(0);
    if(aReal > static_cast<realType>(1))
      return static_cast<realType>(1);
    return aReal;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Linear interpolation between two double valus
   @param v1 First value
   @param v2 Second value
   @param w  weight
   @return (v2-v1)*w+v1. */
  inline double interpolateLinear(double v1, double v2, double w) {
    return (v2 - v1) * w + v1;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Linear interpolation between two double valus interperted as angles in degrees
   @param v1 First angle (in degrees)
   @param v2 Second angle (in degrees)
   @param w  weight
   @return (v2-v1)*w+v1. */
  inline double interpolateLinearAnglesDeg(double v1, double v2, double w) {
    v1 = realWrap(v1, 360.0);
    v2 = realWrap(v2, 360.0);

    if (std::abs(v2 - v1) > 180) {
      if (v1 < v2)
        v1 += 360;
      else
        v2 += 360;
    } 
    return realWrap((v2 - v1) * w + v1,  360.0);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Map an integer in the range [0,maxInValue] onto the range [0,maxOutValue] via a linear mapping function.  That is to say, 0 maps to zero, and maxInValue
    maps to maxOutValue. Input values outside the allowed input range will be linearly mapped outside of the given output range.  To guarantee an output
    within [0,maxInValue], then clamp the input values.
    @param anInt The value to be mapped
    @param maxInValue The maximum input value (used to compute slope for linear map, not to clamp)
    @param maxOutValue The maximum output value (used to compute slope for linear map, not to clamp)
    @return The mapped value. */
  inline int intLinMap(int anInt, int maxOutValue, int maxInValue) {
    return int(double(anInt)*double(maxOutValue)/double(maxInValue));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Map an double in the unit interval, the range [0,1], onto the integers in the range [0,maxOutValue] via a linear mapping function.  That is to say, 0.0
    maps to 0, and 1.0 maps to maxOutValue. Input values outside the allowed input range may be linearly mapped outside of the given output range.  To
    guarantee an output within [0,maxInValue], then clamp the input values to the unit interval.
    @param aDouble The value to be mapped
    @param maxOutValue The maximum output value (used to compute slope for linear map, not to clamp)
    @return The mapped value. */
  inline int unitTooIntLinMap(double aDouble, int maxOutValue) {
    return int(aDouble*double(maxOutValue));
  }

} // end namespace mjr

#define MJR_INCLUDE_mjrmath
#endif

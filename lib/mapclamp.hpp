// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      mapclamp.hpp
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

#ifndef MJR_INCLUDE_mapclamp

// Put everything in the mjr namespace
namespace mjr {

/** Clamp an integer to the range [0,maxValue] via a modulus like function that wraps the value onto the range (i.e. maxOutValue+1 will map to 0).
   @param anInt The value to be wrapped
   @param maxOutValue The maximum output value
   @return The wrapped value. */
inline int intWrap(int anInt, int maxOutValue) {
  int tmp = anInt % (maxOutValue + 1);
  if(tmp < 0)
    return -tmp;
  else
    return tmp;
}

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

#define MJR_INCLUDE_mapclamp
#endif

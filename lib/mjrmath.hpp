// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
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
*/
/*******************************************************************************************************************************************************.H.E.**/

/* Some simple linear mapping and clamping functions. */

#ifndef MJR_INCLUDE_mjrmath

#include <type_traits>                                                   /* C++ metaprogramming     C++11    */
#include <cmath>                                                         /* std:: C math.h          C++11    */
#include <cmath>                                                         /* std:: C math.h          C++11    */
#include <string>                                                        /* C++ strings             C++11    */
#include <numbers>                                                       /* C++ math constants      C++20    */
#include <algorithm>                                                     /* STL algorithm           C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <iomanip>                                                       /* C++ stream formatting   C++11    */
#include <vector>

// Put everything in the mjr namespace
namespace mjr {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Wrap a numbers outside [0, maxOutValue] onto  [0, maxOutValue] for integers and [0, maxOutValue) for floating point.
   @param inNum       The value to be wrapped
   @param maxOutValue The maximum output value
   @return The wrapped value. */
  template <typename inT, typename maxT>
  requires (std::convertible_to<maxT, inT> && std::integral<inT> && std::integral<maxT>)
  inline inT numberWrap(inT inNum, maxT maxOutValue) {
    if ((inNum >= static_cast<inT>(0)) && (inNum <= static_cast<inT>(maxOutValue))) { [[likely]]
      return inNum;
    } else {
      inT tmp = inNum % (static_cast<inT>((static_cast<inT>(maxOutValue) + static_cast<inT>(1))));
      if(tmp >= static_cast<inT>(0)) [[likely]]
        return tmp;
      else
        return static_cast<inT>(maxOutValue) + tmp;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Teplate specialization. */
  template <typename inT, typename maxT>
  requires (std::convertible_to<maxT, inT> && ( std::floating_point<inT> || std::floating_point<maxT> ))
  inline inT numberWrap(inT inNum, maxT maxOutValue) {
    if ((inNum >= static_cast<inT>(0)) && (inNum <= static_cast<inT>(maxOutValue))) { [[likely]]
      return inNum;
    } else {
      inT tmp = std::fmod(inNum, maxOutValue);
      if(tmp < static_cast<inT>(0))
        return maxOutValue+tmp;
      else
        return tmp;
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
    @param inInt The value to be clamped
    @param maxOutValue The maximum output value
    @return The wrapped value. */
  template <typename inT, typename maxT>
  requires (std::convertible_to<maxT, inT>)
  inline inT intClamp(inT inInt, maxT maxOutValue) {
    if(inInt < static_cast<inT>(0))
      return static_cast<inT>(0);
    if(inInt > static_cast<inT>(maxOutValue))
      return static_cast<inT>(maxOutValue);
    return inInt;
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
    return int(static_cast<double>(anInt) * static_cast<double>(maxOutValue) / static_cast<double>(maxInValue));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Compute equatoin of a line hitting (x1, y1) and (x2, y2), and return equation evaluated at x.
    @param x           Value at which to evaluate linear equation
    @param x1          X coordinate of first point
    @param y1          Y coordinate of first point
    @param x2          X coordinate of second point
    @param y2          Y coordinate of second point
    @return The mapped value. */
  template <typename numTx, typename numTy>
  inline numTy genLinMap(numTx x, numTx x1, numTx x2, numTy y1, numTy y2) {
    double m = (static_cast<double>(y1) - static_cast<double>(y2)) / (static_cast<double>(x1) - static_cast<double>(x2));
    double b = static_cast<double>(y1) - m * static_cast<double>(x1);
    return static_cast<numTy>(m * x + b);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Map a non-negative double into the unit interval, the range [0,1] such that 0 mapps to 1 and @f$\infty@f$ maps to 0
    @param aDouble The value to be mapped
    @return The mapped value. */
  inline double rightRayToInterval(double aDouble) {
    return 1.0/(aDouble + 1.0);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Map an double in the unit interval, the range [0,1], onto the integers in the range [0,maxOutValue] via a linear mapping function.  That is to say, 0.0
    maps to 0, and 1.0 maps to maxOutValue. Input values outside the allowed input range may be linearly mapped outside of the given output range.  To
    guarantee an output within [0,maxInValue], then clamp the input values to the unit interval.
    @param aDouble The value to be mapped
    @param maxOutValue The maximum output value (used to compute slope for linear map, not to clamp)
    @return The mapped value. */
  template <typename intT>
  inline intT unitTooIntLinMap(double aDouble, intT maxOutValue) {
    return intT(aDouble*double(maxOutValue));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Maximum of three numbers
    @param x1 First number
    @param x2 Second number
    @param x3 Third number
    @return Maximum of input values. */
  template <typename numType>
  inline numType max3(numType x1, numType x2, numType x3) {
    return std::max(x1, std::max(x2, x3));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Minimum of three numbers
    @param x1 First number
    @param x2 Second number
    @param x3 Third number
    @return Minimum of input values. */
  template <typename numType>
  inline numType min3(numType x1, numType x2, numType x3) {
    return std::min(x1, std::min(x2, x3));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Maximum of three numbers
    @param x1 First number
    @param x2 Second number
    @param x3 Third number
    @param x4 Fourth number
    @return Maximum of input values. */
  template <typename numType>
  inline numType max4(numType x1, numType x2, numType x3, numType x4) {
    return std::max(std::max(x1, x2), std::max(x3, x4));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Minimum of three numbers
    @param x1 First number
    @param x2 Second number
    @param x3 Third number
    @param x4 Fourth number
    @return Minimum of input values. */
  template <typename numType>
  inline numType min4(numType x1, numType x2, numType x3, numType x4) {
    return std::min(std::min(x1, x2), std::min(x3, x4));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Format an integer as a string
    @param inInt         The integer to format
    @param width         The width of the string
    @param fill          Fill character
    @param base          An integer (valid values: 16, 10, 8)
    @param rightJustify  If true, then right justify.  Otherwise, left.
    @return A formatted string. */
  std::string fmtInt(int inInt, int width = 0, char fill = ' ', int base = 10, bool rightJustify = true) {
    std::ostringstream stringStream;
    if (width > 0)
      stringStream << std::setfill(fill) << std::setw(width);
    else
      stringStream << std::setfill(fill) << std::setw(0);
    if(rightJustify)
      stringStream << std::right;
    else
      stringStream << std::left;
    if (base == 16)
      stringStream << std::hex << std::noshowbase;
    if (base == 8)
      stringStream << std::oct << std::noshowbase;
    // TODO: Should throw if base is not 8, 10, or 16...
    stringStream << inInt;
    return stringStream.str();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Return the maximum exponent possible for a bi-variate polynomial stored in a vector of n terms, or a negative value on error.
    @param n Number of terms.
    @return Maximum exponent, or a negative value on error.
      @retval -1 n was too big (>10201)
      @retval -2 n was too small (==0)
      @retval -3 n was not the correct size for a dense bi-variate polynomial */
  int maxExpBiPoly(std::vector<double>::size_type n) {
    if (n>10201)
      return -1;
    if (n == 0)
      return -2;
    double nsqrt  = std::sqrt(n);
    double nsqrtr = std::round(nsqrt);
    if (std::abs(nsqrtr-nsqrt) > 0.00001)
      return -3;
    return static_cast<int>(nsqrtr)-1;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Evaluate a bi-variate polynomial with double coefficients.

    A polynomial is defined by it's coefficients.  In this function those coefficients are provided in a vector, and are in lexicographic order:
     - 2nd: 00 01 02 10 11 12 20 21 22 -> a00*x^2*y^2 + a01*x^2*y^1 + ... + a21*x^0*y^1 + a22*x^0*y^0
     - 3rd: 00 01 02 03 10 11 12 13 20 21 22 23 30 31 32 33
    @param biPoly The polynomial
    @param x      x value at which to evaluate the polynomial
    @param y      x value at which to evaluate the polynomial
    @return Value of polynomial evaluated at (x, y). */
  double evalBiPoly(std::vector<double> const& biPoly, double x, double y) {
    int maxPower = maxExpBiPoly(biPoly.size());
    if (maxPower < 0)
      return -1;  // This is an error.  Probably should throw.
    std::vector<double> xpowers(maxPower+1);
    xpowers[0] = 1;
    std::vector<double> ypowers(maxPower+1);
    ypowers[0] = 1;
    for(int i=1; i<=maxPower; i++) {
      xpowers[i] = x * xpowers[i-1];
      ypowers[i] = y * ypowers[i-1];
    }
    double pvalue = 0;
    std::vector<double>::size_type k=biPoly.size()-1;
    for(int i=0; i<=maxPower; i++) {
      for(int j=0; j<=maxPower; j++) {
        pvalue += biPoly[k] * xpowers[i] * ypowers[j];
        k--;
      }
    }
    return pvalue;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Evaluate a uni-variate polynomial with double coefficients.

    A polynomial is defined by it's coefficients.  In this function those coefficients are provided in a vector, and are in lexicographic order:
      $$a_0+a_1x+a_2x^2+...+a_nx^n$$
    @param uniPoly The polynomial
    @param x       x value at which to evaluate the polynomial
    @return Value of polynomial evaluated at x. */
  inline double evalUniPoly(std::vector<double> const& uniPoly, double x) {
    double pvalue = uniPoly[0];
    for (std::vector<double>::size_type i=1; i<uniPoly.size(); i++)
      pvalue = pvalue * x + uniPoly[i];
    return pvalue;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Signum (sgn, sign) function -- -1 if input is negative, +1 if it is positive, and 0 if it is zero.

    @param x Value to test
    @return The sign */
  template <typename T> 
  requires (std::integral<T> || std::floating_point<T>)
  inline int 
  sgn(T x) {
    if (x > T(0)) return  1;
    if (x < T(0)) return -1;
    return 0;
  }

} // end namespace mjr

#define MJR_INCLUDE_mjrmath
#endif

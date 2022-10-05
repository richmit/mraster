// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      colorTpl.hpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Header for the ramColor class@EOL
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
*/
/*******************************************************************************************************************************************************.H.E.**/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MJR_INCLUDE_colorTpl

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "mjrmath.hpp"

#include <algorithm>                                                     /* STL algorithm           C++11    */
#include <array>                                                         /* array template          C++11    */
#include <bit>                                                           /* STL bit manipulation    C++20    */
#include <climits>                                                       /* std:: C limits.h        C++11    */
#include <cmath>                                                         /* std:: C math.h          C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <concepts>                                                      /* Concepts library        C++20    */
#include <cstring>                                                       /* std:: C string.h        C++11    */
#include <iomanip>                                                       /* C++ stream formatting   C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <limits>                                                        /* C++ Numeric limits      C++11    */
#include <span>                                                          /* STL spans               C++20    */
#include <sstream>                                                       /* C++ string stream       C++      */
#include <string>                                                        /* C++ strings             C++11    */
#include <tuple>                                                         /* STL tuples              C++11    */
#include <type_traits>                                                   /* C++ metaprogramming     C++11    */
#include <utility>                                                       /* STL Misc Utilities      C++11    */
#include <vector>                                                        /* STL vector              C++11    */ 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Set to 1 to look for 128-bit integer types, and 0 to not look for them.
    Right now this only works on GCC & Clang! */
#ifndef MJR_LOOK_FOR_128_BIT_TYPES
#define MJR_LOOK_FOR_128_BIT_TYPES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if MJR_LOOK_FOR_128_BIT_TYPES
#ifdef __GNUC__
#ifdef __SIZEOF_INT128__
#if __SIZEOF_INT128__ == 16
typedef unsigned __int128 mjr_uint128_t;
typedef          __int128 mjr_int128_t;
#define MJR_HAVE_128_BIT_TYPES
#endif
#endif
#endif
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef MJR_HAVE_128_BIT_TYPES
typedef mjr_uint128_t mjr_uintBiggest_t;  //!< The largest unsigned integer supported on the platform
typedef mjr_int128_t  mjr_intBiggest_t;   //!< The largest signed integer supported on the platform
#else
typedef uint64_t      mjr_uintBiggest_t;   //!< The largest unsigned integer supported on the platform
typedef int64_t       mjr_intBiggest_t;    //!< The largest signed integer supported on the platform
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Put everything in the mjr namespace
namespace mjr {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @brief Template Class used to house colors for ramCanvas objects.@EOL

    This template provides a rich API for color management, and may be used to store colors with a wide range of channel depth and count.  This class is
    intended to be a "small concrete" class (as defined by Bjarne Stroustrup in "The C++ Programming Language").  That is to say, it is intended for use as a
    "fundamental" type for tools requiring a space efficient and high performance set of concrete objects representing colors.  The canonical example is
    representing an image as a very large, rectangular array of colors.

    @par Size efficiency

    While this class supports large channel counts and very deep channels, it is best optimized for colors that take less than 64-bits of RAM.  This is
    because the library uses an integer to cover color channel array in RAM to make memory operations faster.  With a compiler supporting ISO C++, this object
    should take no more than the maximum of sizeof(clrChanT)*numChan or the mask used to cover the data. See the next paragraph for details on the "mask".

    The most common use cases are 24-bit RGB/RGBA and greyscale up to 64-bits deep.  All of these types are smaller than a 64-bit pointer, so it is
    almost always better to pass these values around by reference.  That said, some types are quite large -- an RGBA image with 64-bit floating point channels
    requires 256 bits of RAM.  For these larger color objects, it is more efficient to pass them by reference.  Within the library, some care is taken to
    adapt to the size of the color object, and pass objects to functions by the most efficient means (value or const reference).  The class provides a type
    the end user can employ to use this same strategy: colorArgType.

    @par Memory Layout and Performance

    Within this object an integer mask and an array of numChan clrCompT are placed into a union -- and thus are stacked upon each other in memory.  When an
    integer type exists that can cover the entire channel array without wasting too much space, we can achieve serious performance gains.  The trick is
    finding an integer big enough, but not so big it wastes space.  Big enough means it is at least sizeof(clrChanT)*numChan chars long.  The "not too big"
    constraint is more flexible, and I have elected to make a covering mask only if we waste no more than 1/4 of the RAM for the mask value.  Examples:

     - An 8-bit RGBA color is covered by a uint32_t, and so is an 8-bit RGB color -- we waste 1 byte per pixel, or 1/4 of the space.
     - An 8-bit, 5 channel color is NOT covered by an integer, but a 6 channel one would be covered by a uint64_t.

    When we can't cover the channel array, the mask type will be set to an uint8_t to avoid any alignment issues with the union.

    Some common diagrams of common cases might help:

          2222222222222222  Cover: 16-bits
          11111111          1x8   Waste 1/2 => No Cover
          1111111122222222  2x8   Waste 0/2 => Cover with 16-bits

          44444444444444444444444444444444  Cover: 32-bits
          111111112222222233333333          3x8   Waste 1/4 => Cover with 32-bits
          11111111222222223333333344444444  4x8   Waste 0/4 => Cover with 32-bits

          8888888888888888888888888888888888888888888888888888888888888888
          1111111122222222333333334444444455555555                          5x8   Waste 3/8 => No cover
          111111112222222233333333444444445555555566666666                  6x8   Waste 2/8 => Cover with 64-bits
          111111111111111122222222222222223333333333333333                  3x16  Waste 2/8 => Cover with 64-bits

          FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
          1111111122222222333333334444444455555555666666667777777788888888999999990000000011111111               11x8 Waste 5/16 => No Cover
          111111112222222233333333444444445555555566666666777777778888888899999999000000001111111122222222       12x8 Waste 4/16 => Cover with uint128_t
          11111111111111112222222222222222333333333333333344444444444444445555555555555555                       5x16 Waste 6/16 == No Cover
          111111111111111122222222222222223333333333333333444444444444444455555555555555556666666666666666       6x16 Waste 4/16 => Cover with uint128_t
          111111111111111111111111111111112222222222222222222222222222222233333333333333333333333333333333       3x32 Waste 4/16 => Cover with uint128_t

    @par Usage

    Several methods are provided that access and modify the internal color represented by a color object.  In most cases, methods that modify the color object
    state return a reference to the object after the change.  This provides, at a performance impact, the ability to use the value returned by such a function
    in the expression in which it appears.  So, for example, it is not necessary to use two statements to change a color object's value and then use it in a
    drawing function.  As another example, this provides the ability to do "method chaining" like so: aColor.setToRed().setToBlack() -- which will lead to
    aColor being black.  That said, it means we must use compiler optimization features to throw away this refrence if it is not used!!

    Several methods are provided that transform the color object as a whole.  For example, methods are provided to compute component-wise linear histogram
    transformations.  Note that transformation methods are not provided to transform just one component of an object or a range of components.  The philosophy
    is that the class provides methods that treat the color object as a whole and not methods that operate on single components.  Just as we don't have a
    function to add the second half of two integers together -- integers are one "thingy" and so are colors. :)

    @par Construction

    Several constructors are provided.  All in all, the goal is to make it easy to construct color objects with a specified color.

                            |--------------------------------+---------------------+----------------------------------------|
                            | Type                           | Member Helper       | Cast Application                       |
                            |--------------------------------+---------------------+----------------------------------------|
                            | colorT                         | copy                |                                        |
                            | four clrChanT                  | setChans            |                                        |
                            | three clrChanT                 | setChans            |                                        |
                            | two clrChanT                   | setChans            |                                        |
                            | one clrChanT                   | setChans            | drawPoint(x, y, 128);                  |
                            | Named Corner Colors via string | setColorFromString  | drawPoint(x, y, "Red");                |
                            | Web hex string                 | setColorFromString  | drawPoint(x, y, "#FF0000");            |
                            | Extended web hex string        | setColorFromString  | drawPoint(x, y, "##FFFF00000000");     |
                            | Single character string        | setColorFromString  | drawPoint(x, y, "R");                  |
                            | Named Corner Colors via ENUM   | setToCorner         | drawPoint(x, y, cornerColorEnum::RED); |
                            |--------------------------------+---------------------+----------------------------------------|

    @tparam clrChanT Type to contain the channel information.  This type should be a unsigned integral type, a float, or double.
    @tparam numChan The number of channels this color will have.  Common choices are 1 for greyscale, 3 for RGB, and 4 for RGBA.
    @tparam redChanIdx Index for the Red channel. -1 indicates no Red chan.
    @tparam blueChanIdx Index for the Blue channel. -1 indicates no Red channel.
    @tparam greenChanIdx Index for the Green channel. -1 indicates no Red channel.
    @tparam alphaChanIdx Index for the Alpha channel. -1 indicates no Red channel.
    If redChanIdx, blueChanIdx, greenChanIdx, & alphaChanIdx are *all* -1, then they will be assigned to channels 0, 1, 2, & 3 when numChan is >= 4.  If they
    are all negative and numChan == 3, then alphaChanIdx won't be assigned, but red, blue, and green will be. */
  template <class clrChanT, int numChan, int redChanIdx = -1, int greenChanIdx = -1, int blueChanIdx = -1, int alphaChanIdx = -1>
  requires ((numChan>0)                                                                    && // Must have at least 1 chan
            (std::is_unsigned<clrChanT>::value || std::is_floating_point<clrChanT>::value) && // unsigned integral or floating point
            (std::is_floating_point<clrChanT>::value || (sizeof(clrChanT) >= 1))           && // If clrChanT int, then must be >= 1 char size
            (redChanIdx < numChan)                                                         &&
            (blueChanIdx < numChan)                                                        &&
            (greenChanIdx < numChan)                                                       &&
            (alphaChanIdx < numChan)                                                       &&
            (((blueChanIdx <  0) && (redChanIdx <  0) && (greenChanIdx <  0)) ||
             ((blueChanIdx >= 0) && (redChanIdx >= 0) && (greenChanIdx >= 0)))             && // R, G, & B all non-negative or all negative
            ((alphaChanIdx < 0) || (redChanIdx >= 0))                                      && // If A is non-negative, then all non-negative
            ((redChanIdx < 0) || ((redChanIdx   != greenChanIdx) &&
                                  (redChanIdx   != blueChanIdx)  &&
                                  (redChanIdx   != alphaChanIdx) &&
                                  (greenChanIdx != blueChanIdx)  &&
                                  (greenChanIdx != alphaChanIdx) &&
                                  (blueChanIdx  != alphaChanIdx))))                           // Chans can't be teh same if non-negative
  class colorTpl {

    public:

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public type related types -- meta-types? ;) */
      //@{
      /** This object type */
      typedef colorTpl                     colorType;
      /** Pointer to colorTpl */
      typedef colorType*                   colorPtrType;
      /** Reference to colorTpl) */
      typedef colorType&                   colorRefType;
      /** Reference to const colorTpl */
      typedef colorType const&             colorCRefType;
      /** Type for the channels (clrChanT) */
      typedef clrChanT                     channelType;
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public types for std::tuple & std::vector containing clrChanT values */
      //@{
      typedef std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> clrChanTup6;
      typedef std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> clrChanTup5;
      typedef std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> clrChanTup4;
      typedef std::tuple<clrChanT, clrChanT, clrChanT>           clrChanTup3;
      typedef std::tuple<clrChanT, clrChanT>                     clrChanTup2;
      typedef std::tuple<clrChanT>                               clrChanTup1;

      typedef std::vector<clrChanT>                              clrChanVec;
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public types for for packed integers. */
      //@{
      typedef uint32_t            packed4Cint;          //!< Used for passing & returning integers with packed 8-bit channels
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public color types related to colorT.
       These types are used for things like color space computations and sources for setting channels, etc...*/
      //@{
      typedef colorTpl<double,  3>       colConDbl3;     //!< Used for color space computations.  Type identical to colConRGBdbl, but might not be RGB.
      typedef colorTpl<double,  3>       colConRGBdbl;   //!< RGB with double channels.  
      typedef colorTpl<double,  4>       colConRGBAdbl;  //!< RGBA with double channels.
      typedef colorTpl<uint8_t, 3>       colConRGBbyte;  //!< RGB with uint8_t channels.
      typedef colorTpl<uint8_t, 4>       colConRGBAbyte; //!< RGBA with uint8_t channels.
      typedef colorTpl<double,  numChan> colConALLdbl;   //!< Color with the same number of challens as colorT, but with double channels
      typedef colorTpl<uint8_t, numChan> colConALLbyte;  //!< Color with the same number of challens as colorT, but with uint8_t channels
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @cond pat */
      /** @name Public arithmetic types  */
      //@{
      /** @typedef maskType
          Unsigned integer mask to cover the channel array without wasting too much space.
          This type is the the smallest unsigned integer that can cover clrChanT[numChan] such that it is no larger than 1/4 the total size of
          clrChanT[numChan].  Ex: 3*uint8_t is covered by uint32_t, but 5*uint8_t would not be covered by uint64_t because it would waste almost half the
          64 bits.  When a cover can't be found, this type is set to uint8_t -- to avoid any alignment issues in RAM.

          The constant goodMask can be used to tell if maskType is large enough to cover.
          Note we use cmp_greater_equal and cmp_less_equal because the operators confuse Doxygen. */
      typedef typename std::conditional<std::cmp_greater_equal(sizeof(uint8_t),           sizeof(clrChanT)*numChan),           uint8_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(uint16_t),          sizeof(clrChanT)*numChan),           uint16_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(uint32_t),          sizeof(clrChanT)*numChan),           uint32_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(uint64_t),          sizeof(clrChanT)*numChan),
                       typename std::conditional<std::cmp_less_equal(3*sizeof(uint64_t),          sizeof(clrChanT)*numChan*4), uint64_t,
                                                                                                                               uint8_t
                                                 >::type,
              typename std::conditional<std::cmp_greater_equal(sizeof(mjr_uintBiggest_t), sizeof(clrChanT)*numChan),
                       typename std::conditional<std::cmp_less_equal(3*sizeof(mjr_uintBiggest_t), sizeof(clrChanT)*numChan*4), mjr_uintBiggest_t,
                                                                                                                               uint8_t
                                                 >::type,
                                                                                                                               uint8_t
                                        >::type>::type>::type>::type>::type maskType;

      /** @typedef channelArithDType
          Arithmetic type for differences of clrChanT values.
          When clrChanT is a float, this type will be clrChanT.  When it's an integer, we attempt to find a signed integer 2x the size.

          The constant goodArithD can be used to tell if channelArithDType is large enough.
          Note we use cmp_greater_equal and cmp_less_equal because the operators confuse Doxygen. */
      typedef typename std::conditional<std::is_floating_point<clrChanT>::value, clrChanT,
              typename std::conditional<std::cmp_greater_equal(sizeof(int8_t),  sizeof(clrChanT)*2), int8_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int16_t), sizeof(clrChanT)*2), int16_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int32_t), sizeof(clrChanT)*2), int32_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int64_t), sizeof(clrChanT)*2), int64_t,
                                                                                                     mjr_intBiggest_t
                                        >::type>::type>::type>::type>::type channelArithDType;

      /** @typedef channelArithSPType
          Arithmetic type for sums and products of clrChanT values.
          When clrChanT is a float, this type will be clrChanT.  When it's an integer, we attempt to find an unsigned integer 2x the size.

          The constant goodArithSP can be used to tell if channelArithSPType is large enough.
          Note we use cmp_greater_equal and cmp_less_equal because the operators confuse Doxygen. */
      typedef typename std::conditional<std::is_floating_point<clrChanT>::value, clrChanT,
              typename std::conditional<std::cmp_greater_equal(sizeof(int8_t),  sizeof(clrChanT)*2),  uint8_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int16_t), sizeof(clrChanT)*2),  uint16_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int32_t), sizeof(clrChanT)*2),  uint32_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int64_t), sizeof(clrChanT)*2),  uint64_t,
                                                                                                      mjr_uintBiggest_t
                                        >::type>::type>::type>::type>::type channelArithSPType;

      /** @typedef channelArithSDPType
          Arithmetic type for sums, differences, and products of clrChanT values.
          When clrChanT is a float, this type will be clrChanT.  When it's an integer, we attempt to find an signed integer 4x the size.

          The constant goodArithSDP can be used to tell if channelArithSDPType is large enough.
          Note we use cmp_greater_equal and cmp_less_equal because the operators confuse Doxygen. */
      typedef typename std::conditional<std::is_floating_point<clrChanT>::value, clrChanT,
              typename std::conditional<std::cmp_greater_equal(sizeof(int8_t),  sizeof(clrChanT)*4), int8_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int16_t), sizeof(clrChanT)*4), int16_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int32_t), sizeof(clrChanT)*4), int32_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int64_t), sizeof(clrChanT)*4), int64_t,
                                                                                                     mjr_intBiggest_t
                                        >::type>::type>::type>::type>::type channelArithSDPType;

      /** @typedef channelArithFltType
          Floating point type suitable for arithmetic of clrChanT values.
          When clrChanT is a float, this type will be clrChanT.  When it's an integer, we attempt to find a float at least as big as clrChanT.

          The constant goodArithFlt can be used to tell if channelArithFltType is large enough.
          Note we use cmp_greater_equal and cmp_less_equal because the operators confuse Doxygen. */
      typedef typename std::conditional<std::is_floating_point<clrChanT>::value,                    clrChanT,
              typename std::conditional<std::cmp_greater_equal(sizeof(int8_t),  sizeof(clrChanT)),  float,
              typename std::conditional<std::cmp_greater_equal(sizeof(int16_t), sizeof(clrChanT)),  float,
              typename std::conditional<std::cmp_greater_equal(sizeof(int32_t), sizeof(clrChanT)),  double,
              typename std::conditional<std::cmp_greater_equal(sizeof(int64_t), sizeof(clrChanT)),  long double,
                                                                                                    long double
                                        >::type>::type>::type>::type>::type channelArithFltType;

      /** @typedef channelArithLogType
          Arithmetic type suitable for for logical operations of clrChanT values.

          When clrChanT is an integer, this type will be clrChanT.  When it's a floating point type, we attempt to find an unsigned integer exactly the same
          size as clrChanT.  Note that on x86 hardware, a quad float (long double or extended double) is 80-bits in the processor but 128-bits in RAM.  In
          general the size of quad floats can vary a bit across hardware platforms, so I suggest not using them for channel types.

          The constant goodArithLog can be used to tell if channelArithLogType the same size as clrChanT.
          Note we use cmp_greater_equal and cmp_less_equal because the operators confuse Doxygen. */
      typedef typename std::conditional<std::is_integral<clrChanT>::value,                                     clrChanT,
              typename std::conditional<std::cmp_greater_equal(sizeof(int32_t),            sizeof(clrChanT)),  uint32_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(int64_t),            sizeof(clrChanT)),  uint64_t,
              typename std::conditional<std::cmp_greater_equal(sizeof(mjr_uintBiggest_t),  sizeof(clrChanT)),  mjr_uintBiggest_t,
                                                                                                               uint64_t
                                        >::type>::type>::type>::type channelArithLogType;
      //@}
      /** @endcond */

    private:

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Private Object Data */
      //@{
      /** Holds the color channel data.
          The union is used to overlay a mask integer leading to dramatic performance improvements for common color types.

          Technically we are not allowed to use a union the way we do in colorTpl with modern C++; however, every compiler I use allows us to access
          "non-active" union members the same way we did with good old C.  At some point C++ compilers will have bit_cast, and I can try doing this the
          "correct" way with modern C++; however, I'll need to do quite a bit of performance testing first... */
      union {
          maskType theInt;
          clrChanT thePartsA[numChan];
      } theColor;
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Private utility functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This is a helper function for setRGBfromColorSpace. */
      inline double hslHelperVal(double n1, double n2, double hue) {
        hue = realWrap(hue, 360.0);
        if(hue<60)
          return n1+(n2-n1)*hue/60.0;
        else if(hue<180)
          return n2;
        else if (hue < 240)
          return n1+(n2-n1)*(240-hue)/60.0;
        else
          return n1;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set all channels to meanChanVal. */
      inline void setChansToMean() { std::fill_n(theColor.thePartsA, numChan, meanChanVal); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set all channels to minChanVal. */
      inline void setChansToMin() {
        if(goodMask)
          setMaskNC(maskAllZero);
        else
          std::fill_n(theColor.thePartsA, numChan, minChanVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set all channels to maxChanVal. */
      inline void setChansToMax() {
        if(chanIsInt && goodMask)
          setMaskNC(~static_cast<maskType>(0));
        else
          std::fill_n(theColor.thePartsA, numChan, maxChanVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the current color based upon the contents of the given std::string.
          This is the guts of the magic constructor taking a string.  If colorString starts with a "#", then setChans() will be used.
          Otherwise setToCorner() will be used */
      inline colorTpl& setColorFromString(std::string colorString) {
        if ( !(colorString.empty())) {
          if(colorString[0] == '#') {
            setChans(colorString, true);
          } else {
            if(((colorString[0] == 'b') || (colorString[0] == 'B')) && (colorString.size() > 1)) {
              if( (colorString[2]=='u') || (colorString[2]=='U') )
                setToBlue();
              else
                setToBlack();
            } else {
              setToCorner(colorString[0]);
            }
          }
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a uint8_t to a clrChanT (for integral clrChanT) */
      inline clrChanT convertByteToChan(uint8_t cVal) const requires (std::integral<clrChanT>) {
        if(chanIsByte)
          return cVal;
        else
          return static_cast<clrChanT>(static_cast<channelArithSPType>(cVal) * static_cast<channelArithSPType>(maxChanVal) / static_cast<channelArithSPType>(255));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a uint8_t to a clrChanT (for floating point clrChanT)*/
      inline clrChanT convertByteToChan(uint8_t cVal) const requires (std::floating_point<clrChanT>) {
        return (static_cast<clrChanT>(cVal) / static_cast<clrChanT>(255));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert hex CString to clrChanT (for integral clrChanT) */
      inline clrChanT convertHexStringToChan(std::string hexString) const requires (std::integral<clrChanT>) {
        if (sizeof(unsigned long) >= sizeof(clrChanT))
          return static_cast<clrChanT>( std::stoul(hexString, nullptr, 16));
        else
          return static_cast<clrChanT>(std::stoull(hexString, nullptr, 16));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert hex CString to clrChanT  (for floating point clrChanT)*/
      inline clrChanT convertHexStringToChan(std::string hexString) const requires (std::floating_point<clrChanT>) {
        if (sizeof(unsigned long) >= sizeof(clrChanT))
          return static_cast<clrChanT>( std::stoul(hexString, nullptr, 16)) / static_cast<clrChanT>((chanIsInt ? 1 : std::pow(2, bitsPerChan)));
        else
          return static_cast<clrChanT>(std::stoull(hexString, nullptr, 16)) / static_cast<clrChanT>((chanIsInt ? 1 : std::pow(2, bitsPerChan)));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a clrChanT to a uint8_t (for floating point clrChanT) */
      inline uint8_t convertChanToByte(clrChanT cVal) const requires (std::floating_point<clrChanT>) {
        return static_cast<uint8_t>(cVal * static_cast<clrChanT>(255) / maxChanVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a clrChanT to a uint8_t (for integral clrChanT) */
      inline uint8_t convertChanToByte(clrChanT cVal) const requires (std::integral<clrChanT>) {
        /* Performance: A good compiler *should* recgonize the case when bitsPerChan-8==0, and render this function an NOOP.  Some don't.  Hence the if-then
           below. */
        if(chanIsByte)
          return static_cast<uint8_t>(cVal);  // Cast is unnessary because we only get uint8_t cVal in this branch, but some compilers issue a warning.
        else
          return static_cast<uint8_t>(static_cast<channelArithSPType>(cVal) * static_cast<channelArithSPType>(255) / static_cast<channelArithSPType>(maxChanVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a double to a clrChanT */
      inline clrChanT convertDoubleToChan(double cVal) const {
        /* Performance: Not all compilers recognize multiplication by 1.0 as a NOOP.  Hence the if-then below. */
        if(chanIsInt)
          return static_cast<clrChanT>(cVal * maxChanVal);
        else
          return static_cast<clrChanT>(cVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a clrChanT to a double */
      inline double convertChanToDouble(clrChanT cVal) const {
        if(chanIsInt)
          return static_cast<double>(cVal) / static_cast<double>(maxChanVal);
        else
          return static_cast<double>(cVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Return the mask value */
      inline maskType getMaskNC() const {
#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
        return theColor.theInt;
#if __GNUC__
#pragma GCC diagnostic pop
#endif
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the mask value */
      inline void setMaskNC(maskType aMask) { theColor.theInt = aMask; }
      //@}

      public:

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public Constants Related to RGBA channels */
      //@{
      constexpr static int noRGBchanIdx = (redChanIdx < 0) && (greenChanIdx < 0) && (blueChanIdx < 0) && (alphaChanIdx < 0);
      constexpr static int redChan      = (noRGBchanIdx && numChan > 0 ? 0 : redChanIdx);
      constexpr static int greenChan    = (noRGBchanIdx && numChan > 1 ? 1 : greenChanIdx);
      constexpr static int blueChan     = (noRGBchanIdx && numChan > 2 ? 2 : blueChanIdx);
      constexpr static int alphaChan    = (noRGBchanIdx && numChan > 3 ? 3 : alphaChanIdx);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public Constants Related to template paramaters */
      //@{
      constexpr static int         bitsPerChan    = (int)(sizeof(clrChanT)*CHAR_BIT);                                     //!< Number of bits in clrChanT
      constexpr static int         bitsPerPixel   = numChan*bitsPerChan;                                                  //!< Number of color data bits
      constexpr static bool        chanIsInt      = std::is_integral<clrChanT>::value;                                    //!< clrChanT is an integral type
      constexpr static bool        chanIsFloat    = std::is_floating_point<clrChanT>::value;                              //!< clrChanT is a floating pint type
      constexpr static bool        chanIsUnsigned = std::is_unsigned<clrChanT>::value;                                    //!< clrChanT is an unsigned integral type
      constexpr static bool        chanIsByte     = std::is_same<clrChanT, uint8_t>::value;                               //!< is clrChanT an 8-bit unsigned int?
      constexpr static bool        chanIsDouble   = std::is_same<clrChanT, double>::value;                                //!< is clrChanT a double?
      constexpr static bool        goodMask       = (sizeof(maskType) >= sizeof(clrChanT)*numChan);                       //!< maskType is big enough
      constexpr static bool        perfectMask    = (sizeof(maskType) == sizeof(clrChanT)*numChan);                       //!< maskType is perfectly sized
      constexpr static bool        goodArithD     = (chanIsFloat || (sizeof(channelArithDType)   >= sizeof(clrChanT)*2)); //!< channelArithDType is big enough
      constexpr static bool        goodArithSP    = (chanIsFloat || (sizeof(channelArithSPType)  >= sizeof(clrChanT)*2)); //!< channelArithSPType is big enough
      constexpr static bool        goodArithSDP   = (chanIsFloat || (sizeof(channelArithSDPType) >= sizeof(clrChanT)*4)); //!< channelArithSDPType is big enough
      constexpr static bool        goodArithFlt   = (chanIsFloat || (sizeof(channelArithFltType) >  sizeof(clrChanT)));   //!< channelArithFltType is big enough
      constexpr static bool        goodArithLog   = (sizeof(channelArithLogType) == sizeof(clrChanT));                    //!< channelArithLogType is the right size
      constexpr static int         sizeOfColor    = (int)(goodMask ? sizeof(maskType) : sizeof(clrChanT)*numChan);        //!< Size of this object
      constexpr static bool        ptrIsSmaller   = sizeOfColor > (int)sizeof(colorPtrType);                              //!< This object smaller than a pointer
      constexpr static clrChanT    maxChanVal     = (chanIsInt ? std::numeric_limits<clrChanT>::max() : 1);               //!< maximum value for a channel
      constexpr static clrChanT    minChanVal     = (chanIsInt ? std::numeric_limits<clrChanT>::min() : 0);               //!< maximum value for a channel
      constexpr static clrChanT    meanChanVal    = (maxChanVal-minChanVal)/2;                                            //!< middle value for a channel
      constexpr static maskType    maskAllOne     = ~(static_cast<maskType>(0));                                          //!< mask value all ones
      constexpr static maskType    maskAllZero    = static_cast<maskType>(0);                                             //!< mask value all zeros
      constexpr static int         channelCount   = numChan;                                                              //!< Number of channels
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public type for argument passing */
      //@{
      /** A type for passing colorTpl objects to functions.

          WHen the size of a colorTpl object is smaller than a pointer, this type is colorTpl -- resulting in pass by value.  Otherwise, this type is
          colorType const& -- resulting in pass by refrence. */
      typedef typename std::conditional<ptrIsSmaller, colorCRefType, colorType>::type colorArgType;
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @cond cst */
      /** @name Color Scheme Related Types */
      //@{
      /** A type used for discreet color scheme indexes.
          This will be uint64_t for floating point clrChanT, and the larger of uint32_t and colorChanArithSPType for integral clrChanT.
          We use cmp_less because < confuses Doxygen.*/
      typedef typename std::conditional<std::cmp_less(sizeof(channelArithSPType), sizeof(uint32_t)), uint32_t,
              typename std::conditional<std::is_floating_point<clrChanT>::value,                     uint64_t,
                                                                                                     channelArithSPType
                                        >::type>::type csIntType;

      /** A type used for continous color scheme indexes. */
      typedef double csFltType;
      /** A clrChanT-similar type color scheme indexes. */
      typedef typename std::conditional<std::is_floating_point<clrChanT>::value, csFltType, csIntType>::type csNatType;
      //@}
      /** @endcond */

      /** @name Color Scheme Constants */
      //@{
      /* The cast to csIntType is required to prevent std::numeric_limits<uint32_t>::max from being cast to a float when maxChanVal is a float. */
      constexpr static csIntType chanStepMax   = (chanIsInt ? static_cast<csIntType>(maxChanVal) : std::numeric_limits<uint32_t>::max());  //!< Finite "steps" for a color scheme: [0, chanStepMax]
      constexpr static int       minWavelength = 360;                                                                                      //!< Minimum wavelength for wavelength conversion
      constexpr static int       maxWavelength = 830;                                                                                      //!< Maximum wavelength for wavelength conversion
      //@}

      /** @name Default RGB Luminescence Weights */
      //@{
      constexpr static double RGBluminanceWeightR = 0.2126;
      constexpr static double RGBluminanceWeightG = 0.7152;
      constexpr static double RGBluminanceWeightB = 0.0722;
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Public Enums Constants */
      //@{
      /** Colors at the corners of the RGB color cube. */
      enum class cornerColorEnum { BLACK,   //!< Color cube corner color with RGB=000
                                   RED,     //!< Color cube corner color with RGB=100
                                   GREEN,   //!< Color cube corner color with RGB=010
                                   BLUE,    //!< Color cube corner color with RGB=001
                                   YELLOW,  //!< Color cube corner color with RGB=110
                                   CYAN,    //!< Color cube corner color with RGB=011
                                   MAGENTA, //!< Color cube corner color with RGB=101
                                   WHITE    //!< Color cube corner color with RGB=111
                                 };
      /** Color spaces.
          This ENUM is used by setRGBfromColorSpace(), interplColorSpace(), and rgb2colorSpace().  In this context these color spaces use double values for each
          channel.  Angles (the H of HSV, HSL, & LCH) are in degrees, and will always be normalized to [0, 360).  */
      enum class colorSpaceEnum { RGB, //!< RGB color space.       R in [0, 1].   G in [0, 1].   B in [0, 1].
                                  HSL, //!< HSL color space.       H in [0, 360]. S in [0, 1].   L in [0, 1].
                                  HSV, //!< HSV color space.       H in [0, 360]. S in [0, 1].   V in [0, 1].
                                  LAB, //!< CIE-L*ab color space.  L in [0, 100]. A in REALS.    B in REALS.
                                  XYZ, //!< XYZ color space.       X in [0, 1].   Y in [0, 1].   Z in [0, 1].
                                  LCH, //!< CIE-L*ch color space.  L in [0, 100]. C in [0, 100]. H in [0, 360]
                                  NONE //!< Used when the color channels don't have an assocaited color space
                                };
      /** Interpolation methods for emperical color matching functions. */
      enum class cmfInterpolationEnum { FLOOR,   //!< closest lower
                                        CEILING, //!< closest upper
                                        NEAREST, //!< closest
                                        LINEAR,  //!< linear interpolation
                                        BUMP     //!< exponential bump map interpolation
                                      //  MJR TODO NOTE cmfInterpolationEnum: Add Chebychev and cubic spline options.
                                      };
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Constructors: C++ Utility */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The no arg constructor is a noop so we don't needlessly initialize millions of pixels -- compiler warnings are expected. */
      colorTpl() { }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Copy constructor (heavily used for assignment in the ramCanvas library). */
      colorTpl(const colorType& aColor) {
        /* Saftey: Yep.  Sometimes the compiler might not be able to tell if we have initalized the color object -- some of the color set code is too complex.
           Sometimes we might even want to copy an unitilzied color -- sometimes it makes the code easier to write.*/
        if(goodMask)
          setMaskNC(aColor.getMaskNC());
        else
          std::copy_n(aColor.theColor.thePartsA, numChan, theColor.thePartsA);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Initializer list.  Unspecified channels are set ot minChanVal, and extra channel values are ignored. */
      colorTpl(std::initializer_list<clrChanT> cVals) { 
        int numChanGiven = static_cast<int>(cVals.size());
        auto p = cVals.begin();
        for(int i=0; i<std::min(numChanGiven, numChan); i++) {
          setChanNC(i, *p);
          ++p;
        }
        if (numChanGiven < numChan)
          for(int i=numChanGiven; i<numChan; i++)
            setChanToMin(i);
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Constructors: RGB
          These all use setChansRGB or setChansRGBA internally; however, these constructors will set any unspecified channels to min. */
      //@{
      colorTpl(clrChanT r, clrChanT g, clrChanT b, clrChanT a) {
        if (numChan > 4)
          setChansToMin();
        setChansRGBA(r, g, b, a);
      }
      colorTpl(clrChanT r, clrChanT g, clrChanT b) {
        if (numChan > 3)
          setChansToMin();
        setChansRGB(r, g, b);
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Constructors: Conversions
          These are all guarnteed to set all channels of the object. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses setChans() to set all channels to the given value
          @param cVal The value to set the channels to */
      colorTpl(clrChanT cVal) { setChans(cVal); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses the setToCorner() method to set the initialize the object.
       Note that no constructor exists taking a character to provide to setToCorner().  Why?  Because character literals are integers in C++, and they might
       be the same as clrChanT -- rendering ambiguous overload cases.*/
      colorTpl(cornerColorEnum cornerColor) { setToCorner(cornerColor); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses the setColorFromString() method to set the initialize the object. */
      colorTpl(std::string colorString) { setColorFromString(colorString); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses the setColorFromString() method to set the initialize the object. */
      colorTpl(const char* colorCString) { setColorFromString(std::string(colorCString)); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Destructor */
      //@{
      /** The destructor for this class is a no-op. */
      ~colorTpl() { }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Utility Methods */
      //@{
      /** Copy the contents of the given color object into the current object.
          When sizeof(colorTpl)<=sizeof(maskType), this function consists of a single assignment statement.  Otherwise it is O(numChan).
          @return Returns a reference to the current color object.*/
      inline colorTpl& copy(colorArgType aCol) {
        if(goodMask)
          setMaskNC(aCol.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, aCol.getChanNC(i));
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Named Channel Access
       Provides access to the specified color channel value with compile time index check.
         - _dbl versions work with double values scaled to [0, 1].
         - _byte versions work with uint8_t values scaled to [0, 255]
         - Numbered channel names are 0 indexed. */
      //@{
      inline clrChanT getRed()   const requires ((redChan>=0)   && (numChan>redChan))   { return getChanNC(redChan);   }
      inline clrChanT getBlue()  const requires ((blueChan>=0)  && (numChan>blueChan))  { return getChanNC(blueChan);  }
      inline clrChanT getGreen() const requires ((greenChan>=0) && (numChan>greenChan)) { return getChanNC(greenChan); }
      inline clrChanT getAlpha() const requires ((alphaChan>=0) && (numChan>alphaChan)) { return getChanNC(alphaChan); }

      inline double getRed_dbl()   const { return convertChanToDouble(getRed());   }
      inline double getGreen_dbl() const { return convertChanToDouble(getGreen()); }
      inline double getBlue_dbl()  const { return convertChanToDouble(getBlue());  }
      inline double getAlpha_dbl() const { return convertChanToDouble(getAlpha()); }

      inline uint8_t getRed_byte()   const { return convertChanToByte(getRed());   }
      inline uint8_t getGreen_byte() const { return convertChanToByte(getGreen()); }
      inline uint8_t getBlue_byte()  const { return convertChanToByte(getBlue());  }
      inline uint8_t getAlpha_byte() const { return convertChanToByte(getAlpha()); }

      inline clrChanT getC0() const                      { return getChanNC(0); }
      inline clrChanT getC1() const requires (numChan>1) { return getChanNC(1); }
      inline clrChanT getC2() const requires (numChan>2) { return getChanNC(2); }
      inline clrChanT getC3() const requires (numChan>3) { return getChanNC(3); }

      inline double getC0_dbl() const { return convertChanToDouble(getC0()); }
      inline double getC1_dbl() const { return convertChanToDouble(getC1()); }
      inline double getC2_dbl() const { return convertChanToDouble(getC2()); }
      inline double getC3_dbl() const { return convertChanToDouble(getC3()); }

      inline uint8_t getC0_byte() const { return convertChanToByte(getC0()); }
      inline uint8_t getC1_byte() const { return convertChanToByte(getC1()); }
      inline uint8_t getC2_byte() const { return convertChanToByte(getC2()); }
      inline uint8_t getC3_byte() const { return convertChanToByte(getC3()); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Indexed Channel Access
          Provides access to an indexed color channel value with run time index check.
          The channels are 0 indexed.
         - _dbl versions work with double values scaled to [0, 1].
         - _byte versions work with uint8_t values scaled to [0, 255] */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline clrChanT getChan(int chan) const {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          return getChanNC(chan);
        else
          return minChanVal;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline double getChan_dbl(int chan) const {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          return convertChanToDouble(getChanNC(chan));
        else
          return 0.0;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline uint8_t getChan_byte(int chan) const {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          return convertChanToByte(getChanNC(chan));
        else
          return 0;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set Named Channel Value
       Provides access to the specified color channel value with compile time index check.
         - _dbl versions work with double values scaled to [0, 1].
         - _byte versions work with uint8_t values scaled to [0, 255]
         - Numbered channel names are 0 indexed. */
      //@{
      /* Performance: numChan is known at compile time, so the optimizer will produce an assignment or no code at all -- i.e. the test for numChan is done at
           compile time only, and imposes zero overhead at runtime.  */
      /* Performance: The array assignment here gets optimized because the index is known at compile time.  It's just as fast as accessing a member of a union
           for example.  */
      /* Useablity: We could do this with a template, but that means we need ".template set" syntax in some cases.  That's just too uguly. */

      inline colorTpl& setC0(clrChanT cVal)                      { return setChanNC(0, cVal); }
      inline colorTpl& setC1(clrChanT cVal) requires (numChan>1) { return setChanNC(1, cVal); }
      inline colorTpl& setC2(clrChanT cVal) requires (numChan>2) { return setChanNC(2, cVal); }
      inline colorTpl& setC3(clrChanT cVal) requires (numChan>3) { return setChanNC(3, cVal); }

      inline colorTpl& setC0_dbl(double cVal) { return setC0(convertDoubleToChan(cVal));  }
      inline colorTpl& setC1_dbl(double cVal) { return setC1(convertDoubleToChan(cVal));  }
      inline colorTpl& setC2_dbl(double cVal) { return setC2(convertDoubleToChan(cVal));  }
      inline colorTpl& setC3_dbl(double cVal) { return setC3(convertDoubleToChan(cVal));  }

      inline colorTpl& setC0_byte(uint8_t cVal) { return setC0(convertByteToChan(cVal));  }
      inline colorTpl& setC1_byte(uint8_t cVal) { return setC1(convertByteToChan(cVal));  }
      inline colorTpl& setC2_byte(uint8_t cVal) { return setC2(convertByteToChan(cVal));  }
      inline colorTpl& setC3_byte(uint8_t cVal) { return setC3(convertByteToChan(cVal));  }

      inline colorTpl& setRed(clrChanT cVal)   requires ((redChan>=0)   && (numChan>redChan))   { return setChanNC(redChan,   cVal); }
      inline colorTpl& setBlue(clrChanT cVal)  requires ((blueChan>=0)  && (numChan>blueChan))  { return setChanNC(blueChan,  cVal); }
      inline colorTpl& setGreen(clrChanT cVal) requires ((greenChan>=0) && (numChan>greenChan)) { return setChanNC(greenChan, cVal); }
      inline colorTpl& setAlpha(clrChanT cVal) requires ((alphaChan>=0) && (numChan>alphaChan)) { return setChanNC(alphaChan, cVal); }

      inline colorTpl& setRed_dbl(double cVal)   { return setRed(convertDoubleToChan(cVal));   }
      inline colorTpl& setGreen_dbl(double cVal) { return setGreen(convertDoubleToChan(cVal)); }
      inline colorTpl& setBlue_dbl(double cVal)  { return setBlue(convertDoubleToChan(cVal));  }
      inline colorTpl& setAlpha_dbl(double cVal) { return setAlpha(convertDoubleToChan(cVal)); }

      inline colorTpl& setRed_byte(uint8_t cVal)   { return setRed(convertByteToChan(cVal));   }
      inline colorTpl& setGreen_byte(uint8_t cVal) { return setGreen(convertByteToChan(cVal)); }
      inline colorTpl& setBlue_byte(uint8_t cVal)  { return setBlue(convertByteToChan(cVal));  }
      inline colorTpl& setAlpha_byte(uint8_t cVal) { return setAlpha(convertByteToChan(cVal)); }

      inline colorTpl& setChansRGBA(clrChanT r, clrChanT g, clrChanT b, clrChanT a) { setRed(r); setGreen(g); setBlue(b); setAlpha(a); return *this; }
      inline colorTpl& setChansRGB(clrChanT r, clrChanT g, clrChanT b)              { setRed(r); setGreen(g); setBlue(b);              return *this; }

      inline colorTpl& setChansRGBA_dbl(double r, double g, double b, double a)     { return setChansRGBA(convertDoubleToChan(r), convertDoubleToChan(g), convertDoubleToChan(b), convertDoubleToChan(a)); }
      inline colorTpl& setChansRGB_dbl(double r, double g, double b)                { return setChansRGB(convertDoubleToChan(r), convertDoubleToChan(g), convertDoubleToChan(b));                         }

      inline colorTpl& setChansRGBA_byte(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return setChansRGBA(convertByteToChan(r), convertByteToChan(g), convertByteToChan(b), convertByteToChan(a)); }
      inline colorTpl& setChansRGB_byte(uint8_t r, uint8_t g, uint8_t b)             { return setChansRGB(convertByteToChan(r), convertByteToChan(g), convertByteToChan(b));                       }

      inline colorTpl& setChansRGBA(clrChanTup4 chanValues) { setRed(std::get<0>(chanValues)); setGreen(std::get<1>(chanValues)); setBlue(std::get<2>(chanValues)); setAlpha(std::get<3>(chanValues)); return *this; }
      inline colorTpl& setChansRGB(clrChanTup3 chanValues)  { setRed(std::get<0>(chanValues)); setGreen(std::get<1>(chanValues)); setBlue(std::get<2>(chanValues));                                    return *this; }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canonical Color Types.
       Provide conversions to/from canonical color types. */
      //@{
      inline colorTpl& setChans_dbl(colConALLdbl dblColor)         { for(int i=0; i<numChan; i++) setChanNC(i, convertDoubleToChan(dblColor.getChanNC(i))); return *this; }
      inline colorTpl& setChans_byte(colConALLbyte byteColor)      { for(int i=0; i<numChan; i++) setChanNC(i, convertByteToChan(byteColor.getChanNC(i)));  return *this; }
      inline colorTpl& setChansRGBA_dbl(colConRGBAdbl dblColor)    { return setChansRGBA(convertDoubleToChan(dblColor.getRed()), convertDoubleToChan(dblColor.getGreen()), convertDoubleToChan(dblColor.getBlue()), convertDoubleToChan(dblColor.getAlpha())); }
      inline colorTpl& setChansRGB_dbl(colConRGBdbl dblColor)      { return setChansRGB( convertDoubleToChan(dblColor.getRed()), convertDoubleToChan(dblColor.getGreen()), convertDoubleToChan(dblColor.getBlue()));                                           }
      inline colorTpl& setChansRGBA_byte(colConRGBAbyte byteColor) { return setChansRGBA(convertByteToChan(byteColor.getRed()), convertByteToChan(byteColor.getGreen()), convertByteToChan(byteColor.getBlue()), convertByteToChan(byteColor.getAlpha())); }
      inline colorTpl& setChansRGB_byte(colConRGBbyte byteColor)   { return setChansRGB( convertByteToChan(byteColor.getRed()), convertByteToChan(byteColor.getGreen()), convertByteToChan(byteColor.getBlue()));                                          }

      inline colConALLdbl   getColCon_dbl()      { colConALLdbl   rCol; for(int i=0; i<numChan; i++) rCol.setChanNC(i, convertChanToDouble(getChanNC(i))); return rCol; }
      inline colConALLbyte  getColCon_byte()     { colConALLbyte  rCol; for(int i=0; i<numChan; i++) rCol.setChanNC(i, convertChanToByte(  getChanNC(i))); return rCol; }
      inline colConRGBAdbl  getColConRGBA_dbl()  { return colConRGBAdbl( getChan_dbl(bestRedChan()), getChan_dbl(bestGreenChan()), getChan_dbl(bestBlueChan()), getChan_dbl(bestAlphaChan()));     }
      inline colConRGBdbl   getColConRGB_dbl()   { return colConRGBdbl(  getChan_dbl(bestRedChan()), getChan_dbl(bestGreenChan()), getChan_dbl(bestBlueChan()));                                   }
      inline colConRGBAbyte getColConRGBA_byte() { return colConRGBAbyte(getChan_byte(bestRedChan()), getChan_byte(bestGreenChan()), getChan_byte(bestBlueChan()), getChan_byte(bestAlphaChan())); }
      inline colConRGBbyte  getColConRGB_byte()  { return colConRGBbyte( getChan_byte(bestRedChan()), getChan_byte(bestGreenChan()), getChan_byte(bestBlueChan()));                                }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Best guess for named channel index.
          These are used when we wish to get the named channel index, but the current color might not have specified an approprate value. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /* Returns redChan if non-negative and 0 otherwise */
      inline int bestRedChan() {                       
        if (redChan >= 0)
          return redChan;      // If we have an identical red, then return it.
        else
          return 0;            // Otherwise return 0 -- we are guarnteed at least one channel.
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /* Returns blueChan if it is non-negative.  If we only have one channel, then returns 0. If we have more than one channel, then returns 1. */
      inline int bestGreenChan() {                       
        if (greenChan >= 0)
          return greenChan;    // If we have an identified green, then return it.
        else if (numChan == 1) 
          return 0;            // for greyscale, return chan 0
        else
          return 1;            // If we have more than 1 channel, then return 1
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /* Returns blueChan if it is non-negative.  If we only have one channel, then returns 0.  If we have two channels, then returns -1.  Otherwise returns 2. */
      inline int bestBlueChan() {                       
        if (blueChan >= 0)
          return blueChan;     // If we have an identified blue, then return it.
        else if (numChan == 1) 
          return 0;            // for greyscale, return chan 0
        else if (numChan == 2) 
          return -1;           // No sensible value for blue channel with 2 channel images
        else
          return 2;            // If we have at least three channels, then return chan 2
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /* Returns alphaChan if it is non-negative.  If we only have four or more channels, then returns 3.  Otherwise returns -1. */
      inline int bestAlphaChan() {                       
        if (alphaChan >= 0)
          return alphaChan;    // If we have an identified alpha, then return it.
        else if (numChan >= 4) 
          return 3;            // If we have at least four channels, then return chan 3
        else
          return -1;           // No sensible value for alpha channel 
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Setting a single Channel by Index
          Provides access to an indexed color channel value with run time index check.
          The channels are 0 indexed.
         - _dbl versions work with double values scaled to [0, 1].
         - _byte versions work with uint8_t values scaled to [0, 255] */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChanToMax(int chan) {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          setChanNC(chan, maxChanVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChanToMin(int chan) {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          setChanNC(chan, minChanVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChan(int chan, clrChanT cVal) {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          setChanNC(chan, cVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChan_dbl(int chan, double cVal) {
        /* Performance: We expect chan to be in range most of the time.  If it is not, we waste time here computing the channel value.. */
        return setChan(chan, convertDoubleToChan(cVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChan_byte(int chan, uint8_t cVal) {
        /* Performance: We expect chan to be in range most of the time.  If it is not, we waste time here computing the channel value.. */
        /* Performance: When chanIsByte, convertByteToChan is a NOOP.  As it's inline, this leads to zero overhead for the chanIsByte case. */
        return setChan(chan, convertByteToChan(cVal));
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set/Get Single Channel values with no index checks.
          @warning These functions are fast, but have no error checking.  Use them wrong, and get a segfault! */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the specified color channel value with no index check. */
      inline colorTpl& setChanNC(int chan, clrChanT cVal) { theColor.thePartsA[chan] = cVal; return *this; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value with no index check. */
      inline clrChanT getChanNC(int chan) const {
#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
        return theColor.thePartsA[chan];
#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#pragma GCC diagnostic pop
#endif
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set All Channel Values To One Value
       Sets all components of the current object from to \a cVal.
        - _dbl versions work with double values scaled to [0, 1].
        - _byte versions work with uint8_t values scaled to [0, 255] */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChans(clrChanT cVal) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, cVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChans_dbl(double cVal)   { return setChans(convertDoubleToChan(cVal)); }
      inline colorTpl& setChans_byte(uint8_t cVal) { return setChans(convertByteToChan(cVal));   }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set Channel Value(s) with clrChanT values */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first four channels current object.
          @param chanValues The values for the components
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(clrChanTup4 chanValues) { /* Requires: Inherits numChan>3 from getC3. */
        setC0(std::get<0>(chanValues));
        setC1(std::get<1>(chanValues));
        setC2(std::get<2>(chanValues));
        return setC3(std::get<3>(chanValues));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first three channels current object.
          @param chanValues The values for the components
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(clrChanTup3 chanValues) {   /* Requires: Inherits numChan>2 from getC2. */
        setC0(std::get<0>(chanValues));
        setC1(std::get<1>(chanValues));
        return setC2(std::get<2>(chanValues));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This function sets color channels from the data in a std::vector.
          @warning input vector must have at least #channelCount elements!  This is *not* checked!

          @param chanValues A std::vector containing the color channels.  
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(clrChanVec& chanValues) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, chanValues[i]);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the current color based upon the contents of the given color hex string.
          A color hex string is similar to the hash hex strings used in HTML, but extended to larger depths and higher channel counts.

                    #FF0000       -- Red for an RGB color with 8-bit per channels
                    #FFFF00000000 -- Red for an RGB color with 16-bit per channels
                    #FF0000EE     -- Red for an RGBA color with 8-bit per channels  (with alpha set to EE)
                    #FFFFFFFFFF   -- White for a 5 channel color with 8-bit per channels
          Fewer channel specifiers may be provided than channels in the current color, then the value of clearUndefinedChannels defines the behavior: NOOP or
          set them to #minChanVal.  If the colorHexString is somehow invalid, then all channels are considered undefined, and the action is defined by the
          value of clearUndefinedChannels.
          @param colorHexString         Hex string specifying a color.
          @param clearUndefinedChannels Specify error action and what to do with unspecified channels.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(std::string colorHexString, bool clearUndefinedChannels = false) {
        std::string::size_type sizeOfString = colorHexString.size();
        std::string::size_type digitsPerChan = bitsPerChan / 4;
        if (sizeOfString > 0) {  // Not empty
          if (colorHexString[0] == '#') { // Starts with hash
            if (0 == ((sizeOfString-1) % digitsPerChan)) { // Has correct number of digits
              if (std::string::npos == colorHexString.find_first_not_of("0123456789abcdefABCDEF", 1)) { // All hex digits after the pound
                std::string::size_type numChanGiven = (sizeOfString-1) / digitsPerChan;
                if (numChan < numChanGiven)
                  numChanGiven = numChan;
                std::string curHexStr(digitsPerChan, 1);
                for(std::string::size_type i=0; i<numChanGiven; i++) {
                  for(std::string::size_type j=0; j<digitsPerChan; j++)
                    curHexStr[j] = colorHexString[1+j+digitsPerChan*i];
                  setChan(static_cast<int>(i), convertHexStringToChan(curHexStr));
                }
                if (clearUndefinedChannels && (numChanGiven < numChan))
                  for(std::string::size_type i=numChanGiven; i<numChan; i++)
                    setChanToMin(static_cast<int>(i));
                return *this;
              }
            }
          }
        }
        if (clearUndefinedChannels)
          return setToBlack();
        else
          return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set To Special Colors (RGB Corners)
          While the assumed color model is RGB, these functions are generalized beyond RGB in that non-RGB channels are uniformly, and usefully, manipulated.
          For example, setToBlack and setToWhite functions set all channels to minimum and maximum respectively -- both reasonable definitions for "black" and
          "white" in many situations.  The "primary" colors (red, blue, and green) set all non-RGB channels to minimum, and the "secondary" colors (cyan,
          yellow, and magenta) set all non-RGB channels to max.  The reason for this difference in behavior on non-RGB channels between primary and secondary
          colors is two fold: 1) It allows the setTo*() functions to complete their work using no more than two assignment statements for channel objects with
          integer channels and good masks.  2) It makes each secondary an inverse (a logical NOT for integer colors) color from a primary across all
          channels. Note that the other functions in this group end with a call to one of the setTo*() functions. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setToBlack()   { setChansToMin();                  return *this; }
      inline colorTpl& setToWhite()   { setChansToMax();                  return *this; }
      inline colorTpl& setToRed()     { setChansToMin(); setChanToMax(0); return *this; }
      inline colorTpl& setToBlue()    { setChansToMin(); setChanToMax(2); return *this; }
      inline colorTpl& setToGreen()   { setChansToMin(); setChanToMax(1); return *this; }
      inline colorTpl& setToCyan()    { setChansToMax(); setChanToMin(0); return *this; }
      inline colorTpl& setToYellow()  { setChansToMax(); setChanToMin(2); return *this; }
      inline colorTpl& setToMagenta() { setChansToMax(); setChanToMin(1); return *this; }
      inline colorTpl& setToHalf()    { setChansToMean();                 return *this; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the current color based upon the single character given -- 0==black, R, G, B, M, C, Y, W/1==white).
          The color is acutally set using one of the setTo*() functions.  If \a cornerColor is invalid, then setToBlack().
          @param cornerColor Character specifying the color
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToCorner(char cornerColor) {
        /* This case is ordered by the frequency in which colors are generally encountered.  This will vary for different applications. */
        switch(cornerColor) {
          case '0': return setToBlack();   break;
          case '1':                        [[fallthrough]];
          case 'w':                        [[fallthrough]];
          case 'W': return setToWhite();   break;
          case 'r':                        [[fallthrough]];
          case 'R': return setToRed();     break;
          case 'g':                        [[fallthrough]];
          case 'G': return setToGreen();   break;
          case 'b':                        [[fallthrough]];
          case 'B': return setToBlue();    break;
          case 'y':                        [[fallthrough]];
          case 'Y': return setToYellow();  break;
          case 'c':                        [[fallthrough]];
          case 'C': return setToCyan();    break;
          case 'm':                        [[fallthrough]];
          case 'M': return setToMagenta(); break;
          default:  return setToBlack();   break;
        }
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color to the given  corner color.
          The color is acutally set using one of the setTo*() functions.  If \a cornerColor is invalid, then setToBlack().
          @param cornerColor Enum value specifying the color
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToCorner(cornerColorEnum cornerColor) {
        /* This case is ordered by the frequency in which colors are generally encountered.  This will vary for different applications. */
        switch(cornerColor) {
          case cornerColorEnum::BLACK:    return setToBlack();   break;
          case cornerColorEnum::WHITE:    return setToWhite();   break;
          case cornerColorEnum::RED:      return setToRed();     break;
          case cornerColorEnum::GREEN:    return setToGreen();   break;
          case cornerColorEnum::BLUE:     return setToBlue();    break;
          case cornerColorEnum::YELLOW:   return setToYellow();  break;
          case cornerColorEnum::CYAN:     return setToCyan();    break;
          case cornerColorEnum::MAGENTA:  return setToMagenta(); break;
          default:                        return setToBlack();   break; // Some compilers don't realize all cases are covered above...
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color to the named corner color.
          If cornerColor is one character long, then the call is equivalent to setToCorner(cornerColor[0]).  Otherwise a valid corner color name string is
          expected: red, blue, green, cyan, yellow, magenta, black, or white.  If \a cornerColor is invalid, then setToBlack().  The color is actually set
          using one of the setTo*() functions.
          @param cornerColor String value specifying the color
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToCorner(std::string cornerColor) {
        std::string::size_type sizeOfString = cornerColor.size();
        if (sizeOfString > 0) {
          if(((cornerColor[0] == 'b') || (cornerColor[0] == 'B')) && (sizeOfString > 0)) {
            if( (cornerColor[2]=='u') || (cornerColor[2]=='U') )
              return setToBlue();
            else
              return setToBlack();
          } else {
            return setToCorner(cornerColor[0]);
          }
        }
        return setToBlack();
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Color Setting Methods via Logically Packed Integers.
       By "logically" we mean as if the integers were written on paper left to right with MSB on the left -- the same way they are "written" in C++ source code.
       ex: 0x11223344u has 11 as the most significant byte, but it might be placed in memory differently.  These functions are very usefully for unpacking integers
       derived from integer literals in C++ code.  setRGBfromLogPackIntARGB() is heavily used for color schemes. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color based upon the bytes of the given integer ordered from LSB to MSB.
          The *Idx arguments select which byte of the int is used for each channel -- with LSB equal to index 0 and MSB equal to index 3. The extracted bytes
          are interpreted as by setChans_byte.  Any channels beyond four are left untouched.
          @param anInt The integer from which to extract bytes to set color
          @param rIdx Location of red byte in \a anInt
          @param gIdx Location of green byte in \a anInt
          @param bIdx Location of blue byte in \a anInt
          @param aIdx Location of alpha byte in \a anInt
          @return Returns a reference to the current color object.*/
      inline colorTpl& setRGBAfromLogPackIntGen(packed4Cint anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx) {
        /* Requires: Inherits numChan>3 from setAlpha. */
        uint8_t bytes[4];
        bytes[0] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[1] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[2] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[3] = (0xFF & anInt);
        setRed_byte(  bytes[rIdx]);
        setGreen_byte(bytes[gIdx]);
        setBlue_byte( bytes[bIdx]);
        setAlpha_byte(bytes[aIdx]);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Just like setRGBAfromLogPackIntGen, but no A */
      inline colorTpl& setRGBfromLogPackIntGen(packed4Cint anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx) {
        uint8_t bytes[4];
        /* Requires: Inherits numChan>2 from setBlue. */
        bytes[0] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[1] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[2] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[3] = (0xFF & anInt);
        setRed_byte(  bytes[rIdx]);
        setGreen_byte(bytes[gIdx]);
        setBlue_byte( bytes[bIdx]);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /* These four pixel formats (ARGB, RGBA, ABGR, & BGRA) are commonly used (SDL, OpenGL, ImageJ, etc...).  Note we have two methods per pixel format --
         one for RGB & one for RGBA */
      inline colorTpl& setRGBAfromLogPackIntARGB(packed4Cint anInt) { return setRGBAfromLogPackIntGen(anInt, 2, 1, 0, 3); } /* Requires: Inherits numChan>3 from setAlpha. */
      inline colorTpl& setRGBfromLogPackIntARGB( packed4Cint anInt) { return setRGBfromLogPackIntGen( anInt, 2, 1, 0);    } /* Requires: Inherits numChan>2 from setBlue.  */
      inline colorTpl& setRGBAfromLogPackIntRGBA(packed4Cint anInt) { return setRGBAfromLogPackIntGen(anInt, 3, 2, 1, 0); } /* Requires: Inherits numChan>3 from setAlpha. */
      inline colorTpl& setRGBfromLogPackIntRGBA( packed4Cint anInt) { return setRGBfromLogPackIntGen( anInt, 3, 2, 1);    } /* Requires: Inherits numChan>2 from setBlue.  */
      inline colorTpl& setRGBAfromLogPackIntABGR(packed4Cint anInt) { return setRGBAfromLogPackIntGen(anInt, 0, 1, 2, 3); } /* Requires: Inherits numChan>3 from setAlpha. */
      inline colorTpl& setRGBfromLogPackIntABGR( packed4Cint anInt) { return setRGBfromLogPackIntGen( anInt, 0, 1, 2);    } /* Requires: Inherits numChan>2 from setBlue.  */
      inline colorTpl& setRGBAfromLogPackIntBGRA(packed4Cint anInt) { return setRGBAfromLogPackIntGen(anInt, 1, 2, 3, 0); } /* Requires: Inherits numChan>3 from setAlpha. */
      inline colorTpl& setRGBfromLogPackIntBGRA( packed4Cint anInt) { return setRGBfromLogPackIntGen( anInt, 1, 2, 3);    } /* Requires: Inherits numChan>2 from setBlue.  */
      /* This pixel format (ABRG) is used by POV-Ray for height fields */
      inline colorTpl& setRGBAfromLogPackIntABRG(packed4Cint anInt) { return setRGBAfromLogPackIntGen(anInt, 1, 0, 2, 3); } /* Requires: Inherits numChan>3 from setAlpha. */
      inline colorTpl& setRGBfromLogPackIntABRG( packed4Cint anInt) { return setRGBfromLogPackIntGen( anInt, 1, 0, 2);    } /* Requires: Inherits numChan>2 from setBlue.  */
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name TGA Height Maps for POVray */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes a 24-bit truecolor value intended for use in producing 16-bit greyscale TGA.
          This is the color scheme that should be used for POVray 16-bit height files
          @param tga16val An integer
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBcmpGreyTGA16bit(uint32_t tga16val) requires(chanIsByte) {
        /* Requires: Inherits numChan>1 from setGreen. */
        tga16val = numberWrap(tga16val, 0x0000FFFFu);
        return setRGBfromLogPackIntABRG(tga16val);
        // setChansToMin();
        // setGreen_byte(static_cast<clrChanT>( tga16val        & 0xff));  // 0
        // setRed_byte(  static_cast<clrChanT>((tga16val >> 8)  & 0xff));  // 1
        // return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes a 24-bit truecolor value intended for use in producing 24-bit greyscale TGA.
          @param tga24val An integer
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBcmpGreyTGA24bit(uint32_t tga24val) requires(chanIsByte) {
        /* Requires: Inherits numChan>2 from setBlue. */
        tga24val = numberWrap(tga24val, 0x00FFFFFFu);
        return setRGBfromLogPackIntABRG(tga24val);
        // setGreen_byte( tga24val        & 0xff); // 0
        // setRed_byte(  (tga24val >> 8)  & 0xff); // 1
        // setBlue_byte( (tga24val >> 16) & 0xff); // 2
        // return *this;
      }   //BRG
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Color Setting Methods via Physically Packed Integers.
       By "physically" we mean as the bytes are physically ordered in RAM -- which may differ from how we write them on paper or in C++ code. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color based upon the bytes of the given integer ordered as in RAM.
          The *Idx arguments select which byte of the int is used for each channel -- with byte[0] being the first in RAM. The extracted bytes are interpreted
          as by setChans_byte.  Any channels beyond four are left untouched.
          @param anInt The integer from which to extract bytes to set color
          @param rIdx Location of red byte in \a anInt
          @param gIdx Location of green byte in \a anInt
          @param bIdx Location of blue byte in \a anInt
          @param aIdx Location of alpha byte in \a anInt
          @return Returns a reference to the current color object.*/
      inline colorTpl& setRGBAfromPackIntGen(packed4Cint anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx) {
        /* Requires: Inherits numChan>3 from setAlpha. */
        uint8_t *curByte = (uint8_t *)(&anInt);
        setRed_byte(  curByte[rIdx]);
        setGreen_byte(curByte[gIdx]);
        setBlue_byte( curByte[bIdx]);
        setAlpha_byte(curByte[aIdx]);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Just like setRGBAfromPackIntGen, but no A */
      inline colorTpl& setRGBfromPackIntGen(packed4Cint anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx) {
        /* Requires: Inherits numChan>2 from setBlue. */
        uint8_t *curByte = (uint8_t *)(&anInt);
        setRed_byte(  curByte[rIdx]);
        setGreen_byte(curByte[gIdx]);
        setBlue_byte( curByte[bIdx]);
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Setting Colors Based Upon Other Color Spaces
          Other Colorspaces.
          The most common use case is to think of the image as holding RGB color data, and these functions are designed with that idea in mind.  Note that
          alternate colorspaces computations all take place with double floating point values.  Various other tools are also available for manipulating colors
          in other colorspaces (see: interplColorSpace() and rgb2colorSpace() for example)..  See the #colorSpaceEnum for details regarding supported colorspaces. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the given HSV values.
          The 'unit' in the name indicates that the values for h, s, and v are the unit interval, [0,1].
          @param H The Hue.
          @param S The Saturation.
          @param V The Value
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromUnitHSV(double H, double S, double V) { return setRGBfromColorSpace(colorSpaceEnum::HSV, H*360.0, S, V); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the given HSL values.
          The 'unit' in the name indicates that The ranges for h, s, and v are the the unit interval -- i.e. [0,1].
          @param H The Hue.
          @param S The Saturation.
          @param L The Lightness or Luminescence
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromUnitHSL(double H, double S, double L) { return setRGBfromColorSpace(colorSpaceEnum::HSL, H*360.0, S, L); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the color space and values.
          @param space The colorspace
          @param inCh1 Channel one value for given colorspace
          @param inCh2 Channel two value for given colorspace
          @param inCh3 Channel three value for given colorspace
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromColorSpace(colorSpaceEnum space, double inCh1, double inCh2, double inCh3) {
        // Note: If space==RGB => C0==R, C1=G, C2=B regardless of redChan, blueChan, & greenChan.
        double outR = 0.0, outG = 0.0, outB = 0.0;
        if (space == colorSpaceEnum::HSL) {
          if( (inCh3 >= 0.0) && (inCh3 <= 1.0) && (inCh2 >= 0.0) && (inCh2 <= 1.0) ) {
            double H = realWrap(inCh1, 360.0);
            const double epsilon = 0.000001;
            double m1, m2;
            if(inCh3 <= 0.5)
              m2 = inCh3 * (1.0 + inCh2);
            else
              m2 = inCh3 + inCh2 - inCh3 * inCh2;
            m1 = 2.0 * inCh3 - m2;
            if(inCh2 < epsilon) {
              outR = inCh3;
              outG = inCh3;
              outB = inCh3;
            } else {
              outR = unitClamp(hslHelperVal(m1, m2, H+120));
              outG = unitClamp(hslHelperVal(m1, m2, H));
              outB = unitClamp(hslHelperVal(m1, m2, H-120));
            }
          }
        } else if ((space == colorSpaceEnum::LAB) || (space == colorSpaceEnum::XYZ) || (space == colorSpaceEnum::LCH)) {
          double X, Y, Z;
          if (space == colorSpaceEnum::XYZ) {
            X = inCh1 / 100.0;
            Y = inCh2 / 100.0;
            Z = inCh3 / 100.0;
          } else {
            Y = ( inCh1 + 16.0 ) / 116.0;
            if (space == colorSpaceEnum::LCH) {
              X = std::cos(inCh3 * std::numbers::pi / 180.0) * inCh2 / 500.0 + Y;
              Z = Y - std::sin(inCh3 * std::numbers::pi / 180.0) * inCh2 / 200.0;
            } else {
              X = inCh2 / 500.0 + Y;
              Z = Y - inCh3 / 200.0;
            }
            X = (X > 0.206893034423 ? std::pow(X, 3) : ( X - 16.0 / 116.0 ) / 7.787)  * 95.047  / 100.0;
            Y = (Y > 0.206893034423 ? std::pow(Y, 3) : ( Y - 16.0 / 116.0 ) / 7.787)  * 100.000 / 100.0;
            Z = (Z > 0.206893034423 ? std::pow(Z, 3) : ( Z - 16.0 / 116.0 ) / 7.787)  * 108.883 / 100.0;
          }
          outR = X *  3.2406 + Y * -1.5372 + Z * -0.4986;
          outG = X * -0.9689 + Y *  1.8758 + Z *  0.0415;
          outB = X *  0.0557 + Y * -0.2040 + Z *  1.0570;
          outR = unitClamp((outR > 0.0031308 ? 1.055 * std::pow(outR, 1.0 / 2.4) - 0.055 : 12.92 * outR));
          outG = unitClamp((outG > 0.0031308 ? 1.055 * std::pow(outG, 1.0 / 2.4) - 0.055 : 12.92 * outG));
          outB = unitClamp((outB > 0.0031308 ? 1.055 * std::pow(outB, 1.0 / 2.4) - 0.055 : 12.92 * outB));
        } else if (space == colorSpaceEnum::RGB) {
          outR = unitClamp(inCh1);
          outG = unitClamp(inCh2);
          outB = unitClamp(inCh3);
        } else if (space == colorSpaceEnum::HSV) {
          double t;
          double f = static_cast<double>(std::modf(inCh1 * 6.0 / 360.0, &t));
          int    i = static_cast<int>(t) % 6;
          double p = inCh3 * (1 - inCh2);
          double q = inCh3 * (1 - inCh2 * f);
          double u = inCh3 * (1 - (inCh2 * (1 - f)));
          double w = inCh3;
          switch (i) {
            case 0:   outR = unitClamp(w); outG = unitClamp(u); outB = unitClamp(p); break;
            case 1:   outR = unitClamp(q); outG = unitClamp(w); outB = unitClamp(p); break;
            case 2:   outR = unitClamp(p); outG = unitClamp(w); outB = unitClamp(u); break;
            case 3:   outR = unitClamp(p); outG = unitClamp(q); outB = unitClamp(w); break;
            case 4:   outR = unitClamp(u); outG = unitClamp(p); outB = unitClamp(w); break;
            case 5:   outR = unitClamp(w); outG = unitClamp(p); outB = unitClamp(q); break;
            default:  outR =         0.0 ; outG =         0.0 ; outB =         0.0 ; break;
          }
        } else {
          std::cerr << "ERROR: Unsupported color space used in setRGBfromColorSpace!" << std::endl;
        }
        setChansRGB(static_cast<clrChanT>(maxChanVal * outR),
                    static_cast<clrChanT>(maxChanVal * outG),
                    static_cast<clrChanT>(maxChanVal * outB));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @overload */
      inline colorTpl& setRGBfromColorSpace(colorSpaceEnum space, colConDbl3 inColor) {
        /* Requires: Inherits numChan>2 from getC2. */
        /* This use of getC0/getC1/getC2 for RGB is OK -- that is how colConDbl3 objects work */
        return setRGBfromColorSpace(space, inColor.getC0(), inColor.getC1(), inColor.getC2());
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Setting Colors Based Upon Spectral Color */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the given wavelength.
          This function uses an algorithm based upon the color matching functions as tabulated in table 3 from Stockman and Sharpe (2000) -- I believe they
          are taken from Stiles and Burch 10-degree (1959).  Four of the algorithms are based upon simple linear interpolation, while one is based upon
          exponential bump functions closely matching the color matching functions.  The method of interpolation may be specified via the final argument.

          @warning If you are looking for a wavelength color scheme, then see the csRainbowCM class: http://richmit.github.io/mraster/ColorSchemes.html

          @param wavelength   The wavelength to convert into RGB
          @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum)
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromWavelengthCM(double wavelength, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR) {
        // Color matching function table & metadata.
        // Tabulated in table 3 from Stockman and Sharpe (2000).  I beleive they are taken from Stiles and Burch 10-degree (1959)
        const double minWL         = 390.0;   // Min wavelength in table
        const double maxWL         = 830.0;   // Max wavelength in table
        const int    numPT         = 89;      // Number fo points in the table
        const double rScl          = 3.1673;  // Scale factors for color function
        const double gScl          = 1.0517;
        const double bScl          = 1.0019;
        const static int cmfW[]    = {         390,         395,         400,         405,         410,         415,         420,         425,         430,
                                               435,         440,         445,         450,         455,         460,         465,         470,         475,
                                               480,         485,         490,         495,         500,         505,         510,         515,         520,
                                               525,         530,         535,         540,         545,         550,         555,         560,         565,
                                               570,         575,         580,         585,         590,         595,         600,         605,         610,
                                               615,         620,         625,         630,         635,         640,         645,         650,         655,
                                               660,         665,         670,         675,         680,         685,         690,         695,         700,
                                               705,         710,         715,         720,         725,         730,         735,         740,         745,
                                               750,         755,         760,         765,         770,         775,         780,         785,         790,
                                               795,         800,         805,         810,         815,         820,         825,         830 };
        const static double cmfR[] = {  1.5000E-03,  3.8000E-03,  8.9000E-03,  1.8800E-02,  3.5000E-02,  5.3100E-02,  7.0200E-02,  7.6300E-02,  7.4500E-02,
                                        5.6100E-02,  3.2300E-02, -4.4000E-03, -4.7800E-02, -9.7000E-02, -1.5860E-01, -2.2350E-01, -2.8480E-01, -3.3460E-01,
                                       -3.7760E-01, -4.1360E-01, -4.3170E-01, -4.4520E-01, -4.3500E-01, -4.1400E-01, -3.6730E-01, -2.8450E-01, -1.8550E-01,
                                       -4.3500E-02,  1.2700E-01,  3.1290E-01,  5.3620E-01,  7.7220E-01,  1.0059E+00,  1.2710E+00,  1.5574E+00,  1.8465E+00,
                                        2.1511E+00,  2.4250E+00,  2.6574E+00,  2.9151E+00,  3.0779E+00,  3.1613E+00,  3.1673E+00,  3.1048E+00,  2.9462E+00,
                                        2.7194E+00,  2.4526E+00,  2.1700E+00,  1.8358E+00,  1.5179E+00,  1.2428E+00,  1.0070E+00,  7.8270E-01,  5.9340E-01,
                                        4.4420E-01,  3.2830E-01,  2.3940E-01,  1.7220E-01,  1.2210E-01,  8.5300E-02,  5.8600E-02,  4.0800E-02,  2.8400E-02,
                                        1.9700E-02,  1.3500E-02,  9.2400E-03,  6.3800E-03,  4.4100E-03,  3.0700E-03,  2.1400E-03,  1.4900E-03,  1.0500E-03,
                                        7.3900E-04,  5.2300E-04,  3.7200E-04,  2.6500E-04,  1.9000E-04,  1.3600E-04,  9.8400E-05,  7.1300E-05,  5.1800E-05,
                                        3.7700E-05,  2.7600E-05,  2.0300E-05,  1.4900E-05,  1.1000E-05,  8.1800E-06,  6.0900E-06,  4.5500E-06};
        const static double cmfG[] = { -4.0000E-04, -1.0000E-03, -2.5000E-03, -5.9000E-03, -1.1900E-02, -2.0100E-02, -2.8900E-02, -3.3800E-02, -3.4900E-02,
                                       -2.7600E-02, -1.6900E-02,  2.4000E-03,  2.8300E-02,  6.3600E-02,  1.0820E-01,  1.6170E-01,  2.2010E-01,  2.7960E-01,
                                        3.4280E-01,  4.0860E-01,  4.7160E-01,  5.4910E-01,  6.2600E-01,  7.0970E-01,  7.9350E-01,  8.7150E-01,  9.4770E-01,
                                        9.9450E-01,  1.0203E+00,  1.0375E+00,  1.0517E+00,  1.0390E+00,  1.0029E+00,  9.6980E-01,  9.1620E-01,  8.5710E-01,
                                        7.8230E-01,  6.9530E-01,  5.9660E-01,  5.0630E-01,  4.2030E-01,  3.3600E-01,  2.5910E-01,  1.9170E-01,  1.3670E-01,
                                        9.3800E-02,  6.1100E-02,  3.7100E-02,  2.1500E-02,  1.1200E-02,  4.4000E-03,  7.8000E-05, -1.3680E-03, -1.9880E-03,
                                       -2.1680E-03, -2.0060E-03, -1.6420E-03, -1.2720E-03, -9.4700E-04, -6.8300E-04, -4.7800E-04, -3.3700E-04, -2.3500E-04,
                                       -1.6300E-04, -1.1100E-04, -7.4800E-05, -5.0800E-05, -3.4400E-05, -2.3400E-05, -1.5900E-05, -1.0700E-05, -7.2300E-06,
                                       -4.8700E-06, -3.2900E-06, -2.2200E-06, -1.5000E-06, -1.0200E-06, -6.8800E-07, -4.6500E-07, -3.1200E-07, -2.0800E-07,
                                       -1.3700E-07, -8.8000E-08, -5.5300E-08, -3.3600E-08, -1.9600E-08, -1.0900E-08, -5.7000E-09, -2.7700E-09 };
        const static double cmfB[] = {  6.2000E-03,  1.6100E-02,  4.0000E-02,  9.0600E-02,  1.8020E-01,  3.0880E-01,  4.6700E-01,  6.1520E-01,  7.6380E-01,
                                        8.7780E-01,  9.7550E-01,  1.0019E+00,  9.9960E-01,  9.1390E-01,  8.2970E-01,  7.4170E-01,  6.1340E-01,  4.7200E-01,
                                        3.4950E-01,  2.5640E-01,  1.8190E-01,  1.3070E-01,  9.1000E-02,  5.8000E-02,  3.5700E-02,  2.0000E-02,  9.5000E-03,
                                        7.0000E-04, -4.3000E-03, -6.4000E-03, -8.2000E-03, -9.4000E-03, -9.7000E-03, -9.7000E-03, -9.3000E-03, -8.7000E-03,
                                        8.0000E-03, -7.3000E-03, -6.3000E-03, -5.3700E-03, -4.4500E-03, -3.5700E-03, -2.7700E-03, -2.0800E-03,  1.5000E-03,
                                        1.0300E-03, -6.8000E-04, -4.4200E-04, -2.7200E-04, -1.4100E-04, -5.4900E-05, -2.2000E-06,  2.3700E-05,  2.8600E-05,
                                        2.6100E-05,  2.2500E-05,  1.8200E-05,  1.3900E-05,  1.0300E-05,  7.3800E-06, -5.2200E-06,  3.6700E-06,  2.5600E-06,
                                        1.7600E-06,  1.2000E-06,  8.1700E-07,  5.5500E-07,  3.7500E-07,  2.5400E-07, -1.7100E-07,  1.1600E-07,  7.8500E-08,
                                        5.3100E-08,  3.6000E-08,  2.4400E-08,  1.6500E-08,  1.1200E-08,  7.5300E-09, -5.0700E-09,  3.4000E-09,  2.2700E-09,
                                        1.5000E-09,  9.8600E-10,  6.3900E-10,  4.0700E-10,  2.5300E-10,  1.5200E-10, -8.6400E-11,  4.4200E-11 };

        // Clip the wavelength to be in range
        wavelength = std::clamp(wavelength, minWL, maxWL);

        // Figure out where we are in our color function table
        double fIdx  = (wavelength-minWL)/(maxWL-minWL)*(numPT-1.0);
        int   iIdx1 = static_cast<int>(fIdx);
        int   iIdx2 = iIdx1+1;

        // If we fell off the edge, then we set our indexes to the appropriate edge
        if(iIdx2>(numPT-1)) { iIdx1 = numPT-2; iIdx2 = numPT-1; fIdx = static_cast<double>(iIdx1); }
        if(iIdx1<0)         { iIdx1 = 0;       iIdx2 = 1;       fIdx = static_cast<double>(iIdx1); }

        // Interpolate using our tabulated color matching function
        double rf, gf, bf;
        switch(interpMethod) {
          case cmfInterpolationEnum::FLOOR : // Closest with wavelength lower than given value
            rf=cmfR[iIdx1];
            gf=cmfG[iIdx1];
            bf=cmfB[iIdx1];
            break;
          case cmfInterpolationEnum::CEILING : // Closest with wavelength greater than given value
            rf=cmfR[iIdx2];
            gf=cmfG[iIdx2];
            bf=cmfB[iIdx2];
            break;
          case cmfInterpolationEnum::NEAREST : // Closest with wavelength to given value
            if( std::abs(wavelength-cmfW[iIdx2]) < std::abs(wavelength-cmfW[iIdx1])) {
              rf=cmfR[iIdx2];
              gf=cmfG[iIdx2];
              bf=cmfB[iIdx2];
            } else {
              rf=cmfR[iIdx1];
              gf=cmfG[iIdx1];
              bf=cmfB[iIdx1];
            }
            break;
          case cmfInterpolationEnum::LINEAR : // Linear interpolation between data points
            rf = (fIdx-static_cast<double>(iIdx1)) * (cmfR[iIdx2] - cmfR[iIdx1]) + cmfR[iIdx1];
            gf = (fIdx-static_cast<double>(iIdx1)) * (cmfG[iIdx2] - cmfG[iIdx1]) + cmfG[iIdx1];
            bf = (fIdx-static_cast<double>(iIdx1)) * (cmfB[iIdx2] - cmfB[iIdx1]) + cmfB[iIdx1];
            break;
          case cmfInterpolationEnum::BUMP : // Use exponential hump functions -- MJR developed algorithm 2007
            rf = 3.07 / std::exp(0.0005 * (wavelength-600.0)*(wavelength-600.0)) + 0.09 / std::exp(0.005 * (wavelength-425.0)*(wavelength-425.0));
            gf = 1.05 / std::exp(0.0004 * (wavelength-540.0)*(wavelength-540.0));
            bf = 1.00 / std::exp(0.0010 * (wavelength-450.0)*(wavelength-450.0));
            break;
          default:
            rf = gf = bf = 0.0;
            break;
        }

        // Make them positive and scale to a [0,1] range
        rf=(rf>0.0 ? rf : 0.0)/rScl;
        gf=(gf>0.0 ? gf : 0.0)/gScl;
        bf=(bf>0.0 ? bf : 0.0)/bScl;

        // We are done.  Set the color and exit.
        setChansRGB_dbl(rf, gf, bf);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the given wavelength.
          This function uses an algorithm based upon linear approximations to the color match functions.  I believe the original algorithm is due to Dan
          Bruton, and his FORTRAN version is available (at least as of 1997) at http://www.physics.sfasu.edu/astro/color.html

          @warning If you are looking for a wavelength color scheme, then see the csRainbowLA class: http://richmit.github.io/mraster/ColorSchemes.html

          @param wavelength to convert
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromWavelengthLA(double wavelength) {
        double rf, gf, bf;

        const double minWL = 380.0;     // Min wavelength in table
        const double maxWL = 780.0;     // Max wavelength in table

        // Clip the wavelength to be in range
        if(wavelength < minWL)
          wavelength = minWL;
        if(wavelength > maxWL)
          wavelength = maxWL;

        // Compute color match functions.
        rf = gf = bf = 0;
        if       ( (wavelength >= 380) && (wavelength < 440)) {
          rf = (440-wavelength)/(440-380);
          gf = 0.0;
          bf = 1.0;
        } else if( (wavelength >= 440) && (wavelength < 490)) {
          rf = 0.0;
          gf = (wavelength-440)/(490-440);
          bf = 1.0;
        } else if( (wavelength >= 490) && (wavelength < 510)) {
          rf = 0.0;
          gf = 1.0;
          bf = (510-wavelength)/(510-490);
        } else if( (wavelength >= 510) && (wavelength < 580)) {
          rf = (wavelength-510)/(580-510);
          gf = 1.0;
          bf = 0.0;
        } else if( (wavelength >= 580) && (wavelength < 645)) {
          rf = 1.0;
          gf = (645-wavelength)/(645-580);
          bf = 0.0;
        } else if( (wavelength >= 645) && (wavelength <= 780)) {
          rf = 1.0;
          gf = 0.0;
          bf = 0.0;
        }

        /* Lower the intensity near edges of vision. */
        double edgeIntensityAdj;
        if(wavelength > 700.0) {
          edgeIntensityAdj=0.3 + 0.7 * (780-wavelength)/(780-700);
        } else if(wavelength < 420.0) {
          edgeIntensityAdj=0.3 + 0.7 * (wavelength - 380)/(420-380);
        } else {
          edgeIntensityAdj=1.0;
        }

        return setChansRGB_dbl(edgeIntensityAdj*rf, edgeIntensityAdj*gf, edgeIntensityAdj*bf);
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Color Ramps, Gradients, Interpolation, Binary Thresholds.
          Members in this section form the computational foundation for many of the named color schemes found in this class. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a double to a color value based upon a color ramp passing through the given sequence of corner colors at the given anchor points.
          The value of this function at \a aDouble equal to \a anchor[i] will be \a colors[i].  This is an extremely general function that is capable of
          replicating many of the more precise color ramp sequence functions in this library.  The only defects are the lack of bit level precision and the
          poor performance -- both due to the use of floating point arithmetic.  Note this function operates correctly with any channel type and with an
          arbitrary number of channels -- it is NOT limited to RGB colors or RGB color corners for anchors.

          @warning In many cases it is better to use csFP_tpl, csCC_tpl, or csHSLh_tpl to define a continuous gradient color scheme than to use this function
          directly.  In fact, the first step might be to see if a suitable gradient color scheme is already are predefined:
          http://richmit.github.io/mraster/ColorSchemes.html

          @param csX The value to convert
          @param anchors Doubles for which color equals the corresponding corner.
          @param colors  A vector  of colors to use
          @return A reference to this object */
      inline colorTpl& cmpGradiant(csFltType csX, std::vector<csFltType > const& anchors, std::vector<colorType> const& colors) {
        typename std::vector<colorType>::size_type numColors = colors.size();
        if((numColors >= 2) && (anchors.size() == numColors)) {
          for(typename std::vector<colorType>::size_type i=0; i<(numColors-1); i++) {
            csFltType lowAnchor  = anchors[i];
            csFltType highAnchor = anchors[i+1];
            if( (csX >= lowAnchor) && (csX <= highAnchor) ) {
              return linearInterpolate(std::abs((csX-lowAnchor)/(highAnchor-lowAnchor)), colors[i], colors[i+1]);
            }
          }
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Identical to the other cmpGradiant() function except that equidistant anchors are automatically generated on [0, 1] for the given colors array. */
      inline colorTpl& cmpGradiant(csFltType csX, std::vector<colorType> const& colors) {
        typename std::vector<colorType>::size_type numColors = colors.size();
        if(numColors >= 2) {
          for(typename std::vector<colorType>::size_type i=0; i<(numColors-1); i++) {
            csFltType lowAnchor  = static_cast<csFltType>(i)  / static_cast<csFltType>(numColors-1);
            csFltType highAnchor = static_cast<csFltType>(i+1)/ static_cast<csFltType>(numColors-1);
            if( (csX >= lowAnchor) && (csX <= highAnchor) ) {
              return linearInterpolate(std::abs((csX-lowAnchor)/(highAnchor-lowAnchor)), colors[i], colors[i+1]);
            }
          }
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Identical to the other equidistant cmpGradiant() function except that this one works on just the RGB channels and takes an array of packed integers. */
      inline colorTpl& cmpGradiant(csFltType csX, csIntType numColors, const packed4Cint* colors) {
        if(numColors >= 2) {
          for(csIntType i=0; i<(numColors-1); i++) {
            csFltType lowAnchor  = static_cast<csFltType>(i)  / static_cast<csFltType>(numColors-1);
            csFltType highAnchor = static_cast<csFltType>(i+1)/ static_cast<csFltType>(numColors-1);
            if( (csX >= lowAnchor) && (csX <= highAnchor) ) {
              colorTpl c1;
              colorTpl c2;
              c1.setRGBfromLogPackIntARGB(colors[i]);
              c2.setRGBfromLogPackIntARGB(colors[i+1]);
              return linearInterpolateRGB(std::abs((csX-lowAnchor)/(highAnchor-lowAnchor)), c1, c2);
            }
          }
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This is simply a version of cmpRGBcornerCGradiant() that computes the length of the final argument as a C-string.
          Unlike the version of cmpRGBcornerDGradiant() specifying numColors, this one requires the final argument to be a real C-string -- i.e. it must have a
          terminating NULL.  Note this function uses RGB corner colors as anchors, and is thus designed to work with RGB colors.

          @warning Many gradient color schemes are predefined: http://richmit.github.io/mraster/ColorSchemes.html

          @param csX The value to convert
          @param cornerColors Characters specifying color (as used by setColor)
          @return A reference to this object */
      inline colorTpl& cmpRGBcornerCGradiant(csFltType csX, const char *cornerColors) {
        return cmpRGBcornerCGradiant(csX, static_cast<csIntType>(std::strlen(cornerColors)), cornerColors);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This is simply a version of cmpRGBcornerDGradiant() that computes the length of the final argument as a C-string.
          Unlike the version of cmpRGBcornerDGradiant() specifying numColors, this one requires the final argument to be a real C-string -- i.e. it must have a
          terminating NULL.  Note this function uses RGB corner colors as anchors, and is thus designed to work with RGB colors.

          @warning Many gradient color schemes are predefined: http://richmit.github.io/mraster/ColorSchemes.html

          @param csIdx The value to convert
          @param cornerColors Characters specifying color (as used by setColor)
          @return A reference to this object */
      inline colorTpl& cmpRGBcornerDGradiant(csIntType csIdx, const char *cornerColors) {
        return cmpRGBcornerDGradiant(csIdx, static_cast<csIntType>(std::strlen(cornerColors)), cornerColors);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Color value based upon a color ramp passing through the given sequence of corner colors at equal intervals along [0, (mjr::colorTpl::chanStepMax *
          (numColors - 1) + 1)].  At 0, the color will be the first specified color.  At (mjr::colorTpl::chanStepMax * ( numColors - 1) + 1) it will be the
          last color specified color.  This function uses precise integer arithmetic.  cornerColors need not be a real C-string -- i.e. no need for an
          terminating NULL.  Note this function uses RGB corner colors as anchors, and is thus designed to work with RGB colors.

          @warning Many gradient color schemes are predefined: http://richmit.github.io/mraster/ColorSchemes.html

          @param csIdx The value to convert
          @param numColors The number of colors
          @param cornerColors An array of things that can be passed to setToCorner() -- usually char or cornerColorEnum
          @return A reference to this object */
      template <typename ccT>
      inline colorTpl& cmpRGBcornerDGradiant(csIntType csIdx, csIntType numColors, const ccT* cornerColors) {
        csIdx = numberWrap(csIdx, static_cast<csIntType>(chanStepMax * numColors - chanStepMax)); // First wrap to the total color count
        csIntType edgeNum = csIdx / chanStepMax;
        if (edgeNum == (numColors-1)) {
          edgeNum = edgeNum - 1;
          csIdx = chanStepMax;
        } else {
          csIdx = csIdx % chanStepMax;
        }
        colorTpl c1;
        colorTpl c2;
        c1.setToCorner(cornerColors[edgeNum]);
        c2.setToCorner(cornerColors[edgeNum+1]);
        for (int j : {redChan, greenChan, blueChan}) {
          csIntType cVal;
          if(c1.getChan(j) > c2.getChan(j)) {
            cVal = chanStepMax - csIdx;
          } else if(c1.getChan(j) < c2.getChan(j)) {
            cVal = csIdx;
          } else {
            cVal = ( c1.getChan(j) > 0 ? chanStepMax : 0);
          }
          if (chanIsFloat)
            setChan(j, static_cast<clrChanT>(cVal) / static_cast<clrChanT>(chanStepMax));
          else
            setChan(j, static_cast<clrChanT>(cVal));
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Color value based upon a color ramp passing through the given sequence of corner colors at equal intervals along [0.0, 1.0].  At 0, the color will
          be the first specified color.  At 1.0 it will be the last color specified color. CornerColors need not be a real C-string -- i.e. no need for an
          terminating NULL.  Note this function uses RGB corner colors as anchors, and is thus designed to work with RGB colors.

          @warning Many gradient color schemes are predefined: http://richmit.github.io/mraster/ColorSchemes.html

          @param csX The value to convert
          @param numColors The number of colors
          @param cornerColors An array of things that can be passed to setToCorner() -- usually char or cornerColorEnum
          @return A reference to this object */
      template <typename ccT>
      inline colorTpl& cmpRGBcornerCGradiant(csFltType csX, csIntType numColors, const ccT* cornerColors) {
        /* performance: I have no idea why this is slower than the linear search loop used in cmpGradiant().  Still, the code is cleaner this way.  Perhaps
           the optimizer will figure it out someday... The optimizer works in strange ways. */
        if(numColors >= 2) {
            csX = numberWrap(csX, static_cast<csFltType>(1));
            csFltType mF = csX * static_cast<csFltType>(numColors - 1);
            csIntType mI = static_cast<csIntType>(mF);
            if (mI >= (numColors-2)) mI=numColors-2;
            colorTpl c1;
            colorTpl c2;
            c1.setToCorner(cornerColors[mI]);
            c2.setToCorner(cornerColors[mI+1]);
            return linearInterpolate(mF-static_cast<csFltType>(mI), c1, c2);
        } else {
          return *this;
        }
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the current color to a value linearly interpolated between the two given colors.
          When \a aDouble is 0, the color is col1.  When \a aDouble is 1 the new value is col2.  The interpolation is done in HSL space -- i.e. the given colors are
          converted to HSL, the interpolation is done, and the result is converted back to RGB and the current color is set.  Unlike linearInterpolate, this
          function will NOT interpolate every channel.  Rather, as this function deals specifically with RGB and HSL space, only the RGB channels will be
          interpolated.
          @param space The color space to use
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      inline colorTpl& interplColorSpace(colorSpaceEnum space, double aDouble, colorArgType col1, colorArgType col2) {
        /* Requires: Inherits numChan>2 from getC2. */
        /* This use of getC0/getC1/getC2 for RGB is OK -- that is how colConDbl3 objects work */
        if( (aDouble >= 0.0) && (aDouble <= 1.0) ) {
          // Convert our given colors into HSL
          colConDbl3 acol1 = col1.rgb2colorSpace(space);
          colConDbl3 acol2 = col2.rgb2colorSpace(space);

          // Interpolate values
          double out1, out2, out3;
          if ((space == colorSpaceEnum::HSL) || (space == colorSpaceEnum::HSV))
            out1 = mjr::interpolateLinearAnglesDeg(acol1.getC0(), acol2.getC0(), aDouble);
          else
            out1 = mjr::interpolateLinear(acol1.getC0(), acol2.getC0(), aDouble);
          out2 = mjr::interpolateLinear(acol1.getC1(), acol2.getC1(), aDouble);
          if (space == colorSpaceEnum::LCH)
            out3 = mjr::interpolateLinearAnglesDeg(acol1.getC2(), acol2.getC2(), aDouble);
          else
            out3 = mjr::interpolateLinear(acol1.getC2(), acol2.getC2(), aDouble);

          // Set color
          setRGBfromColorSpace(space, out1, out2, out3);
        }
        // Return
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the weighted mean of the given colors.

          @warning In order to keep the result in range, w1,w2,w3,s4 must be in [0,1] and w1+w2+w3_w5=1. See uMean() for a way to do that automatically.

          @param w1   The first weight
          @param w2   The second weight
          @param w3   The third weight
          @param w4   The fourth weight
          @param col1 The first color
          @param col2 The second color
          @param col3 The third color
          @param col4 The fourth color
          @return Returns a reference to the current color object. */
      inline colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, channelArithFltType w4,
                             colorArgType      col1, colorArgType      col2, colorArgType      col3, colorArgType      col4) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>((static_cast<channelArithFltType>(col1.getChanNC(i)) * w1) +
                                             (static_cast<channelArithFltType>(col2.getChanNC(i)) * w2) +
                                             (static_cast<channelArithFltType>(col3.getChanNC(i)) * w3) +
                                             (static_cast<channelArithFltType>(col4.getChanNC(i)) * w4)));

        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @overload */
      inline colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3,
                             colorArgType      col1, colorArgType      col2, colorArgType      col3) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>((static_cast<channelArithFltType>(col1.getChanNC(i)) * w1) +
                                             (static_cast<channelArithFltType>(col2.getChanNC(i)) * w2) +
                                             (static_cast<channelArithFltType>(col3.getChanNC(i)) * w3)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @overload */
      inline colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>((static_cast<channelArithFltType>(col1.getChanNC(i)) * w1) +
                                             (static_cast<channelArithFltType>(col2.getChanNC(i)) * w2)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the unit weighted mean of the given colors -- like wMean(), but last weight is computed such that weights sum to 1.0.
          @param w1   The first weight in the range [0, 1) -- the range not checked!
          @param w2   The second weight in the range [0, 1) -- the range not checked!
          @param w3   The third weight in the range [0, 1) -- the range not checked!
          @param col1 The first color
          @param col2 The second color
          @param col3 The third color
          @param col4 The fourth color
          @return Returns a reference to the current color object. */
      inline colorTpl& uMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3,
                             colorArgType      col1, colorArgType      col2, colorArgType      col3, colorArgType col4) {
        return wMean(w1, w2, w3, 1-w1-w2-w3, col1, col2, col3, col4);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @overload */
      inline colorTpl& uMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2, colorArgType col3) {
        return wMean(w1, w2, 1-w1-w2, col1, col2, col3);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @overload */
      inline colorTpl& uMean(channelArithFltType w1, colorArgType col1, colorArgType col2) {
        return wMean(w1, 1-w1, col1, col2);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the current color to a value linearly interpolated between the two given colors.
          When \a aDouble is 0, the color is col1.  When \a aDouble is 1 the new value is col2.  This method interpolates all channels without any color space
          conversions and as few type conversions as possible.
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      inline colorTpl& linearInterpolate(double aDouble, colorArgType col1, colorArgType col2) {
        if( (aDouble >= 0.0) && (aDouble <= 1.0) )
          for(int i=0; i<numChan; i++)
            setChanNC(i, static_cast<clrChanT>(mjr::interpolateLinear(static_cast<double>(col1.getChanNC(i)), static_cast<double>(col2.getChanNC(i)), aDouble)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the RGB channels of the current color to a value linearly interpolated between the two given colors.
          When \a aDouble is 0, the color is col1.  When \a aDouble is 1 the new value is col2.  This method interpolates all channels without any color space
          conversions and as few type conversions as possible.
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      inline colorTpl& linearInterpolateRGB(double aDouble, colorArgType col1, colorArgType col2) {
        if( (aDouble >= 0.0) && (aDouble <= 1.0) )
          for (int i : {redChan, blueChan, greenChan})
            setChanNC(i, static_cast<clrChanT>(mjr::interpolateLinear(static_cast<double>(col1.getChanNC(i)), static_cast<double>(col2.getChanNC(i)), aDouble)));
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Logical Operators */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Performs a logical OR with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmOr(colorArgType aCol) requires (std::integral<clrChanT>) {
        if(goodMask)
          setMaskNC(getMaskNC() | aCol.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, getChanNC(i) | aCol.getChanNC(i));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmOr(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        /* Performance: Yep.  Sometimes floating point colors get a goodMask. */
        if(goodMask)
          setMaskNC(getMaskNC() | aCol.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) | std::bit_cast<channelArithLogType>(aCol.getChanNC(i))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Performs a logical NOR with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmNor(colorArgType aCol) requires (std::integral<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC() | aCol.getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, ~(getChanNC(i) | aCol.getChanNC(i)));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmNor(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC() | aCol.getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i)) | std::bit_cast<channelArithLogType>(aCol.getChanNC(i)))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Performs a logical AND with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmAnd(colorArgType aCol) requires (std::integral<clrChanT>) {
        if(goodMask)
          setMaskNC(getMaskNC() & aCol.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, getChanNC(i) & aCol.getChanNC(i));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmAnd(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        if(goodMask)
          setMaskNC(getMaskNC() & aCol.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) & std::bit_cast<channelArithLogType>(aCol.getChanNC(i))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Performs a logical NAND with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmNand(colorArgType aCol) requires (std::integral<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC() & aCol.getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, ~(getChanNC(i) & aCol.getChanNC(i)));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmNand(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC() & aCol.getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i)) & std::bit_cast<channelArithLogType>(aCol.getChanNC(i)))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Performs a logical EXCLUSIVE OR (XOR) with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmXor(colorArgType aCol) requires (std::integral<clrChanT>) {
        if(goodMask)
          setMaskNC(getMaskNC() ^ aCol.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, getChanNC(i) ^ aCol.getChanNC(i));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmXor(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        if(goodMask)
          setMaskNC(getMaskNC() ^ aCol.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) ^ std::bit_cast<channelArithLogType>(aCol.getChanNC(i))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Performs a logical NOT EXCLUSIVE OR (NXOR) with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmNxor(colorArgType aCol) requires (std::integral<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC() ^ aCol.getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, ~(getChanNC(i) ^ aCol.getChanNC(i)));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmNxor(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC() ^ aCol.getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i)) ^ std::bit_cast<channelArithLogType>(aCol.getChanNC(i)))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Performs logical (bit-wise) negation of current object.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmNot(void) requires (std::integral<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, ~(getChanNC(i)));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmNot(void) requires (std::floating_point<clrChanT>) {
        if(goodMask)
          setMaskNC(~(getMaskNC()));
        else
          for(int i=0; i<numChan; i++)
            setChanNC(i, std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i)))));
        return *this;
      }
#endif
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Arithmetic Operators */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the square of the difference for each channel between the given color and the current color object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmSqDiff(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>((static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aCol.getChanNC(i))) *
                                             (static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aCol.getChanNC(i)))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the absolute value of the difference for each channel between the given color and the current color object.
          @param aCol The color to use in the computation.
          @return Returns the absolute value of the difference for each channel.*/
      inline colorTpl& tfrmAbsDiff(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(std::abs(static_cast<channelArithDType>(getChanNC(i))   - static_cast<channelArithDType>(aCol.getChanNC(i)))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic sum of the given color and the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmAdd(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic division of the current color by the given color.
          If a channel of aCol is zero, then the corresponding channel of the current color object will be left untouched.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDiv(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          if (aCol.getChanNC(i) != 0)
            setChanNC(i, static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) / static_cast<channelArithSPType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic product of the given color and the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMult(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the product of the given color and the current one.
          If the result of a multiplication is too large, it will be set to the maximum component value.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMultClamp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clampTop(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the component wise scaled sign of the difference between the current color and the given one.
          As an example of the computation, the red component of the current color is computed like this:
          - R=#minChanVal  iff(R<color.R)
          - R=#meanChanVal iff(R==color.R)
          - R=#maxChanVal  iff(R>color.R)
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmSignDiff(colorArgType aCol) {
        for(int i=0; i<numChan; i++) {
          if(getChanNC(i) < aCol.getChanNC(i)) {
            setChanNC(i, minChanVal);
          } else if(getChanNC(i) > aCol.getChanNC(i)) {
            setChanNC(i, maxChanVal);
          } else {
            setChanNC(i, meanChanVal);
          }
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic difference of the given color from the current one.
          If the result a differences is negative, then that component will be set to zero.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDiffClamp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clampBot(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the negative of the arithmetic difference of the given color from the current one.
          This is the same as the arithmetic difference of the current color from the given color.  If the result a differences is negative, then that
          component will be set to zero.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmNegDiffClamp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clampBot(static_cast<channelArithDType>(aCol.getChanNC(i)) - static_cast<channelArithDType>(getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic sum of the given color from the current one.
          If the result of a sum is greater than the maximum value, then that component will be set to the maximum value.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmAddClamp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clampTop(static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic sum of the current color and aCol, then divids by dCol.
          If the result is greater than the maximum value, then that component will be set to the maximum value.
          If a channel of dCol is zero, then the corresponding channel of the current color object will be left untouched.
          @param aCol The color to use for initial add.
          @param dCol The color to use for final division.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmAddDivClamp(colorArgType aCol, colorArgType dCol) {
        for(int i=0; i<numChan; i++)
          if (dCol.getChanNC(i) != 0)
            setChanNC(i, clampTop((static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))) /
                                 static_cast<channelArithSPType>(dCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic difference of the given color from the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDiff(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic modulus of the current by the given one.
          If a channel of aCol is zero, then the corresponding channel of the current object is left untouched.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMod(colorArgType aCol) requires (std::integral<clrChanT>) {
        for(int i=0; i<numChan; i++)
          if (aCol.getChanNC(i) != 0) //  MJR TODO NOTE tfrmMod: What about floats?
            setChanNC(i, getChanNC(i) % aCol.getChanNC(i));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmMod(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(std::fmod(static_cast<double>(getChanNC(i)), static_cast<double>(aCol.getChanNC(i)))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Transforms the color: r=#maxChanVal-r, g=#maxChanVal-r, and b=#maxChanVal-b
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmInvert() {
        //  MJR TODO NOTE tfrmInvert: This is just as fast as array refs...
        //  MJR TODO NOTE tfrmInvert: We should use this universally across the library -- to isolate the code from the array specifics...
        for(int i=0; i<numChan; i++)
          setChanNC(i, maxChanVal - getChanNC(i));
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Named Operators */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Adds 1.0 and takes the natural logarithm of each channel.
          Floating point Numbers are used for intermediate values and the result cast to a colorChanType at the end.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmLn() {
        /* Performance: Even if the compiler fails to unroll this loop, the runtime is dominated by the double computations. */
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(std::log(1.0 + static_cast<double>(getChanNC(i)))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Linearly interpolate between the current color and the given color (at a point scaled the unit interval).
          If \a aDouble is 0, then the current color will not change.  If \a aDouble is 1, then the current color will be tooCol.
          @param aDouble Distance from the current color (on a unit interval)
          @param tooCol  The color we are interpolating with.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMix(double aDouble, colorArgType tooCol) {
        if( (aDouble >= 0.0) && (aDouble <= 1.0) )
          for(int i=0; i<numChan; i++)
            setChanNC(i, static_cast<clrChanT>(mjr::interpolateLinear(static_cast<double>(getChanNC(i)), static_cast<double>(tooCol.getChanNC(i)), aDouble)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Copies the given argument into the current color object.
          Scan as copy() -- just with a name more suited to transformation code.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmCopy(colorArgType aCol) { return copy(aCol); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Makes the current color the maximum of the current color or the given color.
          Colors are ordered by intensity (thus the 'I' in the name)
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMaxI(colorArgType aCol) {
        channelArithSPType thisSum = 0;
        channelArithSPType thatSum = 0;
        for(int i=0; i<numChan; i++) {
          thisSum += static_cast<channelArithSPType>(getChanNC(i));
          thatSum += static_cast<channelArithSPType>(aCol.getChanNC(i));
        }
        if(thisSum < thatSum)
          tfrmCopy(aCol);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Makes the current color the minimum of the current color or the given color.
          Colors are ordered by intensity (thus the 'I' in the name)
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMinI(colorArgType aCol) {
        /* Performance: Finding the max of two arrays in parallel with one loop is faster than calling max twice, once for each array. */
        channelArithSPType thisSum = 0;
        channelArithSPType thatSum = 0;
        for(int i=0; i<numChan; i++) {
          thisSum += static_cast<channelArithSPType>(getChanNC(i));
          thatSum += static_cast<channelArithSPType>(aCol.getChanNC(i));
        }
        if(thisSum > thatSum)
          tfrmCopy(aCol);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Makes each component of the current color the maximum of that component and the corresponding component of the given color.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMax(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          if(getChanNC(i) < aCol.getChanNC(i))
            setChanNC(i, aCol.getChanNC(i));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Makes each component of the current color the minimum of that component and the corresponding component of the given color.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMin(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          if(getChanNC(i) > aCol.getChanNC(i))
            setChanNC(i, aCol.getChanNC(i));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Shift Left Transform modifies the current color.
          @param aCol Number of bits to shift left
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmShiftL(colorArgType aCol) requires (std::integral<clrChanT>) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, getChanNC(i) << aCol.getChanNC(i));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmShiftL(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        for(int i=0; i<numChan; i++)
          /* tricky: We are casting the color component being shifted bitwise to a big int; however, we are casting the shifting quantity via a static_cast. */
          setChanNC(i, std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) << static_cast<uint64_t>(aCol.getChanNC(i))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Shift Right Transform modifies the current color.
          @param aCol How many bits to shift.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmShiftR(colorArgType aCol) requires (std::integral<clrChanT>) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, getChanNC(i) >> aCol.getChanNC(i));
        return *this;
      }
#if !(MISSING_P0476R2)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmShiftR(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) >> static_cast<uint64_t>(aCol.getChanNC(i))));
        return *this;
      }
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Saw Transform modifies the current color: C_i = ifelse(ra<=C_i<=rb, C_i, 0)
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmSaw(colorArgType lowCol, colorArgType highCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, ((lowCol.getChanNC(i) <= getChanNC(i)) && (highCol.getChanNC(i) >= getChanNC(i)) ? getChanNC(i) : 0));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Saw Transform modifies the current color: C_i = ifelse(ra<=C_i<=rb, maxChanVal, 0)
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmStep(colorArgType lowCol, colorArgType highCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, ((lowCol.getChanNC(i) <= getChanNC(i)) && (highCol.getChanNC(i) >= getChanNC(i)) ? maxChanVal : 0));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The DiracTot (total) Transform modifies the current color: Set current color to white if it equals aCol, and black otherwise.
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDiracTot(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          if(aCol.getChanNC(i) != getChanNC(i))
            return setToBlack();
        return setToWhite();
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Dirac Transform modifies the current color: C_i = ifelse(C_i==aCol.C_i, maxChanVal, 0)
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDirac(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, ((aCol.getChanNC(i) == getChanNC(i)) ? maxChanVal : 0));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Fuzzy Dirac Transform modifies the current color: C_i=ifelse(|R-ctrCol.R|<=radCol.R), maxChanVal, 0)
          @param ctrCol Center Color
          @param radCol Radius Color
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmFuzzyDirac(colorArgType ctrCol, colorArgType radCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, ((std::abs(ctrCol.getChanNC(i) - getChanNC(i)) <= radCol.getChanNC(i)) ? maxChanVal : 0));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic mean of the given color and the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMean(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>((static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))) / 2));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the geometric mean of the given color and the current one.
          Floating point Numbers re used for intermediate values and the result cast to a colorChanType at the end.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmGmean(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(std::sqrt(static_cast<channelArithFltType>(getChanNC(i)) * static_cast<channelArithFltType>(aCol.getChanNC(i)))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Transform the current color by rendering it into a true grey via the same method used by the luminanceRGB() function.
          This function only sets the red, blue, and green channels -- all other channels are left untouched.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmGreyScaleRGB(void) {
        /* Requires: Inherits numChan>2 from getC2. */
        double lumU = static_cast<double>(luminanceRGB());
        setRed_dbl( lumU);
        setGreen_dbl(lumU);
        setBlue_dbl( lumU);
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Color Reduction Transformations */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The 216 Palate Web Safe Transform modifies the current color into the closest web safe color from the 216 color web safe pallet.
          This function only sets the red, blue, and green channels -- all other channels are left untouched.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmWebSafeRGB() requires (redChan>=0) {
        for (int c : {redChan, blueChan, greenChan}) {
          int charCompVal = convertChanToByte(getChanNC(c));
          int minDist     = 256;
          int minCol;
          for(int pv : { 0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF }) {
            int curDist = std::abs(charCompVal - pv);
            if( curDist < minDist ) {
              minDist = curDist;
              minCol  = pv;
            }
          }
          setChanNC(c, convertByteToChan(static_cast<uint8_t>(minCol)));
        }
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Alternate Color Space Stuff */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute channels for given color space coordinates for the current color.
          Note RGB returns float RGB normalized to 1.0.
          @param space The color space to convert to
          @return An RGB color with double channels. */
      inline colConDbl3 rgb2colorSpace(colorSpaceEnum space) const {
        /* Requires: Inherits numChan>2 from getBlue. */

        double redF   = getRed_dbl();
        double greenF = getGreen_dbl();
        double blueF  = getBlue_dbl();

        if (space == colorSpaceEnum::RGB)
          return colConDbl3(redF, greenF, blueF);

        if ((space == colorSpaceEnum::HSL) || (space == colorSpaceEnum::HSV)) {
          clrChanT rgbMaxI = getMaxRGB();
          clrChanT rgbMinI = getMinRGB();

          channelArithSDPType rangeI = rgbMaxI - rgbMinI;

          double rgbMaxF = static_cast<double>(rgbMaxI) / static_cast<double>(maxChanVal);
          double rgbMinF = static_cast<double>(rgbMinI) / static_cast<double>(maxChanVal);

          double rangeF = rgbMaxF - rgbMinF;
          double sumF   = rgbMaxF + rgbMinF;

          // Compute L
          double L = sumF / 2.0;
          double V = rgbMaxF;

          // Compute H & S
          double S, H;
          if((rgbMaxI == 0) || (rangeI == 0)) {
            S = 0.0;
            H = 0.0;
          } else {

            if (space == colorSpaceEnum::HSL) {
              if(L <= 0.5)
                S = rangeF / sumF;
              else
                S = rangeF / ( 2.0 - sumF);
            } else {
              S = rangeF / rgbMaxF;
            }

            H = 0.0;
            if(getRed() == rgbMaxI)
              H = 0.0 + (greenF - blueF) / rangeF;
            else if(getGreen() == rgbMaxI)
              H = 2.0 + (blueF - redF) / rangeF;
            else if(getBlue() == rgbMaxI)
              H = 4.0 + (redF - greenF) / rangeF;
            H = realWrap(H * 60.0, 360.0);
          }
          if (space == colorSpaceEnum::HSL)
            return colConDbl3(H, S, L);
          else
            return colConDbl3(H, S, V);
        } else {
          redF   = 100.0 * ((redF   > 0.04045) ? std::pow((redF   + 0.055) / 1.055, 2.4) : redF   / 12.92);
          greenF = 100.0 * ((greenF > 0.04045) ? std::pow((greenF + 0.055) / 1.055, 2.4) : greenF / 12.92);
          blueF  = 100.0 * ((blueF  > 0.04045) ? std::pow((blueF  + 0.055) / 1.055, 2.4) : blueF  / 12.92);

          double X = (0.4124 * redF + 0.3576 * greenF + 0.1805 * blueF);
          double Y = (0.2126 * redF + 0.7152 * greenF + 0.0722 * blueF); // luminance with weights RGBluminanceWeightR, RGBluminanceWeightG, RGBluminanceWeightB
          double Z = (0.0193 * redF + 0.1192 * greenF + 0.9505 * blueF);

          if (space == colorSpaceEnum::XYZ)
            return colConDbl3(X, Y, Z);

          X /= 95.0429;
          Y /= 100.0;
          Z /= 108.89;

          X = (X > 0.008856 ? std::pow(X, 1.0 / 3.0) : (7.787 * X) + (16.0 / 116.0));
          Y = (Y > 0.008856 ? std::pow(Y, 1.0 / 3.0) : (7.787 * Y) + (16.0 / 116.0));
          Z = (Z > 0.008856 ? std::pow(Z, 1.0 / 3.0) : (7.787 * Z) + (16.0 / 116.0));

          double L = (116.0 * Y) - 16.0;
          double A = 500.0 * (X - Y);
          double B = 200.0 * (Y - Z);

          if (space == colorSpaceEnum::LAB)
            return colConDbl3(L, A, B);

          double C = std::hypot(A, B);

          double H = 0.0;
          if ( std::abs(A) > 1.0e-5)  // Not Grey
            H = realWrap(atan2(B,A) * 180.0 / std::numbers::pi, 360.0);

          if (space == colorSpaceEnum::LCH)
            return colConDbl3(L, C, H);
        }

        return colConDbl3(0.0, 0.0, 0.0);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute channels for given color space coordinates for the current color.
          Note RGB returns float RGB normalized to 1.0.
          @param space The color space to stringify
          @return A string representing the color space. */
      inline std::string colorSpaceToString(colorSpaceEnum space) {
        switch (space) {
          case colorSpaceEnum::RGB : return std::string("rgb");
          case colorSpaceEnum::HSL : return std::string("HSL");
          case colorSpaceEnum::HSV : return std::string("HSV");
          case colorSpaceEnum::LAB : return std::string("Lab");
          case colorSpaceEnum::XYZ : return std::string("XYZ");
          case colorSpaceEnum::LCH : return std::string("Lch");
          default:                   return std::string("ERROR");
        }
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Color Transformation Functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Linear Grey Level Scale transform modifies the current color such that: C_n=c*C_n+b.
          This function transforms all channels --- not just RGBA.
          @param c The "contrast" value
          @param b The "brightness" value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmLinearGreyLevelScale(double c, double b) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(c * static_cast<double>(getChanNC(i)) + b));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Linear Grey Level Scale transform modifies the current color such that: R=rc*R+rb, G=gc*G+gb, B=bc*B+bb.
          This function ONLY transforms the red, green, and blue channels.
          @param rc The "contrast" value for red
          @param rb The "brightness" value for red
          @param gc The "contrast" value for green
          @param gb The "brightness" value for green
          @param bc The "contrast" value for blue
          @param bb The "brightness" value for blue
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmLinearGreyLevelScaleRGB(double rc, double rb, double gc, double gb, double bc, double bb) {
        /* Requires: Inherits numChan>3 from setAlpha & getC3. */
        setRed(  static_cast<clrChanT>(rc * static_cast<double>(getRed()) + rb));
        setGreen(static_cast<clrChanT>(gc * static_cast<double>(getGreen()) + gb));
        setBlue( static_cast<clrChanT>(bc * static_cast<double>(getBlue()) + bb));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Standard Power Transform modifies the current color such that: C_i = maxChanVal*(C_i / maxChanVal)**p.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmStdPow(double p) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(std::pow(static_cast<double>(getChanNC(i)) / static_cast<double>(maxChanVal), p) * static_cast<double>(maxChanVal)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Standard Power Transform modifies the current color such that:
          R=#maxChanVal*(R/#maxChanVal)**rp, B=#maxChanVal*(B/#maxChanVal)**gp, B=#maxChanVal*(B/#maxChanVal)**bp
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmStdPowRGB(double rp, double gp, double bp) {
        /* Requires: Inherits numChan>2 from setBlue & getC2. */
        setRed(  static_cast<clrChanT>(std::pow(static_cast<double>(getRed())    / static_cast<double>(maxChanVal), rp) * static_cast<double>(maxChanVal)));
        setGreen(static_cast<clrChanT>(std::pow(static_cast<double>(getGreen()) / static_cast<double>(maxChanVal), gp) * static_cast<double>(maxChanVal)));
        setBlue( static_cast<clrChanT>(std::pow(static_cast<double>(getBlue())  / static_cast<double>(maxChanVal), bp) * static_cast<double>(maxChanVal)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Standard Power Transform with p=2. The new color will be: C_i = C_i * C_i / maxChanVal == (C_i/maxChanVal)^2*maxChanVal
          This computation is done with integer math if clrChanT is integral.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmStdPowSqr(void) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(getChanNC(i)) /
                                             static_cast<channelArithSPType>(maxChanVal)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Standard Power Transform with p=1/2. The new color will be: C_i = sqrt(C_i / maxChanVal) * maxChanVal
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmStdPowSqrt(void) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(std::sqrt(static_cast<double>(getChanNC(i)) / static_cast<double>(maxChanVal)) * static_cast<double>(maxChanVal)));
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Mathematical Operations On Color(s)
          Members in this section produce non-color results. i.e. They consume the current, and possibly other colors and arguments, to produce a non-color
          result. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Use the  R, G, & B channels to compute a floating point value representing a grey scale.
          What is returned is the dot product of the given color and the three scalars: R*redWt+G*greenWt+B*blueWt.  
          @param redWt The red weight
          @param greenWt The green weight
          @param blueWt The blue weight
          @return The integer representing grey value for the given color. */
      inline channelArithFltType rgb2GreyDotProd(channelArithFltType redWt   = RGBluminanceWeightR,
                                                 channelArithFltType greenWt = RGBluminanceWeightG, 
                                                 channelArithFltType blueWt  = RGBluminanceWeightB) const {
        /* Requires: Inherits numChan>2 from getC2. */
        return (static_cast<channelArithFltType>(getRed())   * static_cast<channelArithFltType>(redWt)   +
                static_cast<channelArithFltType>(getGreen()) * static_cast<channelArithFltType>(greenWt) +
                static_cast<channelArithFltType>(getBlue())  * static_cast<channelArithFltType>(blueWt));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the luminance of the current color via the definition given in the ITU-R Recommendation BT.709.
          The output value will be between 0 and 1, and is given by: (RGBluminanceWeightR*R+RGBluminanceWeightG*G+RGBluminanceWeightB*B)/#maxChanVal.
          @return The luminance for the current object. */
      inline channelArithFltType luminanceRGB(void) const {
        /* Requires: Inherits numChan>2 from getC2. */
        return ((static_cast<channelArithFltType>(getRed())   * static_cast<channelArithFltType>(RGBluminanceWeightR) +
                 static_cast<channelArithFltType>(getGreen()) * static_cast<channelArithFltType>(RGBluminanceWeightG) +
                 static_cast<channelArithFltType>(getBlue())  * static_cast<channelArithFltType>(RGBluminanceWeightB)) / static_cast<channelArithFltType>(maxChanVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the unscaled intensity (sum of the R, G, & B components) of the current color
          @return The unscaled intensity for the current object. */
      inline channelArithSPType intensityRGB(void) const {
        /* Requires: Inherits numChan>2 from getC2. */
        return static_cast<channelArithSPType>(static_cast<channelArithSPType>(getRed()) +
                                               static_cast<channelArithSPType>(getGreen()) +
                                               static_cast<channelArithSPType>(getC2()));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the sum of the components.
          @return Sum of components. */
      inline channelArithSPType intensity() const {
        channelArithSPType sum = 0;
        for(int i=0; i<numChan; i++)
          sum += getChan(i);
        return (sum);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the scaled intensity (sum of the first three components divided by the maximum intensity possible) of the current color
          @return The scaled intensity for the current object. */
      inline channelArithFltType intensityScaledRGB() const {
        return (static_cast<channelArithFltType>(intensityRGB()) / static_cast<channelArithFltType>(3) / static_cast<channelArithFltType>(maxChanVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the scaled intensity (sum of the components divided by the maximum intensity possible) of the current color
          @return Sum of components. */
      inline channelArithFltType intensityScaled() const {
        return (static_cast<channelArithFltType>(intensity()) / static_cast<channelArithFltType>(numChan) / static_cast<channelArithFltType>(maxChanVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the value of the largest component.
          @return The value of the largest color component currently stored.*/
      inline clrChanT getMaxC() const {
        /* Performance: I'm manually unrolling the loop and using direct calls to max functions because some compilers can't figure out how to optimize this code.
           At some point I expect the C++ reduce or max algorithms to be able to handle this case in an optimal way.  Till then, we get this weird bit of
           code. */
        if(numChan == 1) {                                         // 1 channel
          return getChanNC(0);
        } else if(numChan == 2) {                                  // 2 channels
          return std::max(getChanNC(0),  getChanNC(1));
        } else if(numChan == 3) {                                  // 3 channels
          return mjr::max3(getChanNC(0), getChanNC(1), getChanNC(2));
        } else if(numChan == 4) {                                  // 4 channels
          return mjr::max4(getChanNC(0), getChanNC(1), getChanNC(2), getChanNC(3));
        } else {                                                   // More than 3 channels
          clrChanT theMax = minChanVal;
          for(int i=0; i<numChan; i++)
            if(theMax < getChanNC(i))
              theMax = getChanNC(i);
          return theMax;
        }
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the value of the smallest component.
          @return The value of the smallest color component currently stored.*/
      inline clrChanT getMinC() const {
        if(numChan == 1) {                                         // 1 channel
          return getChanNC(0);
        } else if(numChan == 2) {                                  // 2 channels
          return std::min(getChanNC(0), getChanNC(1));
        } else if(numChan == 3) {                                  // 3 channels
          return mjr::min3(getChanNC(0), getChanNC(1), getChanNC(2));
        } else if(numChan == 4) {                                  // 4 channels
          return mjr::min4(getChanNC(0), getChanNC(1), getChanNC(2), getChanNC(3));
        } else {
          clrChanT theMin = maxChanVal;
          for(int i=0; i<numChan; i++)
            if(theMin > getChanNC(i))
              theMin = getChanNC(i);
          return theMin;
        }
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the value of the largest component from R, G, and B. This function is highly optimized.
          @return The value of the largest color component.*/
      inline clrChanT getMaxRGB() const { return mjr::max3(getRed(), getGreen(), getBlue()); } /* Requires: Inherits numChan>2 from getC2. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the value of the smallest component from R, G, and B. This function is highly optimized.
          @return The value of the smallest color component.*/
      inline clrChanT getMinRGB() const { return mjr::min3(getRed(), getGreen(), getBlue()); } /* Requires: Inherits numChan>2 from getC2. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the dot product between the current color and the given color. i.e. c1.r*c2.r+c1.g*c2.g+...
          @param aColor the given color
          @return Returns dot product.*/
      inline channelArithFltType dotProd(colorArgType aColor) const {
        channelArithFltType daProd = 0;
        for(int i=0; i<numChan; i++)
          daProd += static_cast<channelArithFltType>(static_cast<channelArithFltType>(getChanNC(i)) * static_cast<channelArithFltType>(aColor.getChanNC(i)));
        return daProd;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Distance between current color and given one (sum squares of channel differences -- Euclidean distance squared).
          @param aColor The given color
          @return Returns Distance */
      inline channelArithFltType distHypot(colorArgType aColor) const {
        channelArithFltType daDist = 0;
        for(int i=0; i<numChan; i++)
          daDist += (static_cast<channelArithFltType>((static_cast<channelArithFltType>(getChanNC(i)) - static_cast<channelArithFltType>(aColor.getChanNC(i))) *
                                                      (static_cast<channelArithFltType>(getChanNC(i)) - static_cast<channelArithFltType>(aColor.getChanNC(i)))));
        return static_cast<channelArithFltType>(std::sqrt(daDist));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Distance between current color and given one (sum of absolute channel differences).
          @param aColor the given color
          @return Returns Distance */
      inline channelArithSPType distSumAbs(colorArgType aColor) const {
        channelArithSPType daDist = 0;
        for(int i=0; i<numChan; i++)
          daDist += static_cast<channelArithSPType>(std::abs(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aColor.getChanNC(i))));
        return daDist;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Distance between current color and given one (maximum of absolute value of channel differences).
          @param aColor the given color
          @return Returns Distance */
      inline channelArithSPType distMaxAbs(colorArgType aColor) const {
        channelArithSPType daDist = 0;
        for(int i=0; i<numChan; i++) {
          channelArithSPType tmp = static_cast<channelArithSPType>(std::abs(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aColor.getChanNC(i))));
          if (daDist < tmp)
            daDist = tmp;
        }
        return daDist;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** LAB Delta E* distance between current color and given one.
          Note: The Delta E* 1976 distance measurement is inherently an RGB measurement in that the colors are converted to LAB* as part of the computation.
          @param aColor the given color
          @return Returns Distance -- note return is a double not a channelArithFltType. */
      inline double distDeltaE1976(colorArgType aColor) const {
        colConDbl3 acol1 = rgb2colorSpace(colorSpaceEnum::LAB);
        colConDbl3 acol2 = aColor.rgb2colorSpace(colorSpaceEnum::LAB);
        double daDist = 0;
        for (int c=0; c<3; c++)
          daDist += std::pow(acol1.getChanNC(c) - acol2.getChanNC(c), 2);
        daDist = std::sqrt(daDist);
        return daDist;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** LAB Delta E* 1994 (graphic arts) distance between current color and given one.
          Note: The Delta E* 1994 distance measurement is inherently an RGB measurement in that the colors are converted to LAB* as part of the computation.
          Note: The Delta E* 1994 distance measurement is NOT symetric -- the 1976 one is!
          @param aColor the given color
          @return Returns Distance -- note return is a double not a channelArithFltType. */
      inline double distDeltaE1994(colorArgType aColor) const {
        colConDbl3 acol1 = rgb2colorSpace(colorSpaceEnum::LAB);
        colConDbl3 acol2 = aColor.rgb2colorSpace(colorSpaceEnum::LAB);
        double k1 = 0.045;
        double k2 = 0.015;
        double kL = 1.000;
        double kC = 1.000;
        double kH = 1.000;
        double sL = 1.000;
        double dL = acol1.getC0() - acol2.getC0();
        double da = acol1.getC1() - acol2.getC1();
        double db = acol1.getC2() - acol2.getC2();
        double c1 = std::sqrt(std::pow(acol1.getC1(), 2) + std::pow(acol1.getC2(), 2));
        double c2 = std::sqrt(std::pow(acol2.getC1(), 2) + std::pow(acol2.getC2(), 2));
        double sH = 1.000 + k2 * c1;
        double sC = 1.000 + k1 * c1;
        double dC = c2 - c2;
        double dH2 = std::pow(da, 2) + std::pow(db, 2) - std::pow(dC, 2);
        if (dH2 < 0.0)
          dH2 = 0.000;
        double dE = std::sqrt(std::pow(dL/kL/sL, 2) + std::pow(dC/kC/sC, 2) + dH2/std::pow(kH*sH, 2));
        return dE;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns non-zero if the current color is close to aColor (the maximum delta between any two channels is less than or equal to epsilon).
          Note the implications for floating point clrChanT.
          @return non-zero if the given color is logically the same as the current color*/
      inline bool isClose(colorArgType aColor, clrChanT epsilon) const {
        for(int i=0; i<numChan; i++)
          if (std::abs(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aColor.getChanNC(i))) > epsilon)
            return false;
        return true;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Like isClose(), but only checks the R, G, & B channels.
          @return non-zero if the given RGB color is the same as the current color*/
      inline bool isCloseRGB(colorArgType aColor, clrChanT epsilon) const requires(blueChan >= 0) {
        for (int i : {redChan, blueChan, greenChan})
          if (std::abs(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aColor.getChanNC(i))) > epsilon)
            return false;
        return true;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns non-zero if the current color is precicely equal to aColor.
          Note the implications for floating point clrChanT.
          @return non-zero if the given color is logically the same as the current color*/
      inline bool isEqual(colorArgType aColor) const {
        if(perfectMask)
          return (getMaskNC() == aColor.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            if(getChanNC(i) != aColor.getChanNC(i))
              return false;
        return true;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Like isEqual(), but only checks the R, G, & B channels.
          @return non-zero if the given RGB color is the same as the current color*/
      inline bool isEqualRGB(colorArgType aColor) const {
        /* Requires: Inherits RGB channel requirements from getRed/getGreen/getBlue. */
        return ((getRed()   == aColor.getRed()  ) &&
                (getGreen() == aColor.getGreen()) &&
                (getBlue()  == aColor.getBlue()));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns non-zero if the given color is logically NOT the same as the current color.
          Note the implications for floating point clrChanT.
          @return non-zero if the given color is logically the same as the current color*/
      inline bool isNotEqual(colorArgType aColor) const { return !(isEqual(aColor)); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns non-zero if the given color is black (all componnets are zero)
          @return non-zero if the given color is black (all componnets are zero) */
      inline bool isBlack() {
        if(perfectMask)
          return (getMaskNC() == maskAllZero);
        else
          for(int i=0; i<numChan; i++)
            if(getChanNC(i) != 0)
              return false;
        return true;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** LIke isBlack(), but only checks the R, G, & B channels
          @return non-zero if the given color is black (R, G, & B are  are zero) */
      inline bool isBlackRGB() const { return ((getRed() == 0) && (getGreen() == 0) && (getBlue() == 0)); } /* Requires: Inherits RGB channel requirements from getRed/getGreen/getBlue. */
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Channel Clipping Functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clamp a value to (infinity, maxChanVal].
          Input values larger than maxChanVal are mapped to maxChanVal.  Values less than minChanVal are not changed.
          @param arithValue The value to clamp */
      template <typename iT>
      inline clrChanT clampTop(iT arithValue) {
        if(arithValue > maxChanVal)
          return static_cast<clrChanT>(maxChanVal);
        else
          return static_cast<clrChanT>(arithValue);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clamp a value to [minChanVal, infinity).
          @param arithValue The value to clamp */
      template <typename iT>
      inline clrChanT clampBot(iT arithValue) {
        if(arithValue < minChanVal)
          return static_cast<clrChanT>(minChanVal);
        else
          return static_cast<clrChanT>(arithValue);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clamp a value to [minChanVal, maxChanVal].
          @param arithValue The value to clamp */
      template <typename iT>
      inline clrChanT clampAll(iT arithValue) {
        if     (arithValue > maxChanVal)
          return static_cast<clrChanT>(maxChanVal);
        else if(arithValue < minChanVal)
          return static_cast<clrChanT>(minChanVal);
        else
        return static_cast<clrChanT>(arithValue);
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Meta Color Schemes */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
#if !(MISSING_P1907R1)
      /** Compute a color from a polynomial space curve in the RGB color space. This is a continuous color scheme!
          @tparam coefs Polynomial coefficients*/
      template<double...coefs>
      class csPLY_tpl {
        public:
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csX A value in [0, 1] that identifies the color in the scheme.
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csFltType csX) {
            double pR = pcoff[0 * psize];
            double pG = pcoff[1 * psize];
            double pB = pcoff[2 * psize];
            for (unsigned int i=1; i<psize; i++) {
              pR = pR * csX + pcoff[i + 0 * psize];
              pG = pG * csX + pcoff[i + 1 * psize];
              pB = pB * csX + pcoff[i + 2 * psize];
            }
            return aColor.setChansRGB_dbl(std::clamp(pR, 0.0, 1.0), std::clamp(pG, 0.0, 1.0), std::clamp(pB, 0.0, 1.0));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csX A value in [0, 1] that identifies the color in the scheme.
              @return Returns a colorTpl value */
          static inline colorTpl c(csFltType csX) { colorTpl tmp; return c(tmp, csX); }
        private:
          constexpr static int    psize   = (sizeof...(coefs)) / 3;
          constexpr static double pcoff[] = { coefs... };
      };
#endif
#if !(MISSING_P1907R1)
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute a color from Dave Green's cubehelix scheme.  See: Green, D. A., 2011, Bulletin of the Astronomical Society of India, Vol.39, p.289.
          This is a continous color scheme!
          @tparam start colour (1=red, 2=green, 3=blue; ex: 0.5=purple;
          @tparam rots  Rotations in colour in [-1.5, 1.5]. ex: -1.0 is one blue->green->red cycle;
          @tparam hue   Hue intensity scaling in [0, 1] (0 == greyscale).
          @tparam gamma Gamma correction for intensity. */
      template<double start, double rots, double hue, double gamma>
      class csCubeHelix_tpl {
        public:
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csX A value in [0, 1] that identifies the color in the scheme.
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csFltType csX) {
            //csX=mjr::numberWrap(csX, 0.0, 1.0);
            double angle=2*std::numbers::pi*(start/3.0+1.0+rots*csX);
            csX=std::pow(csX, gamma);
            double ampl=hue*csX*(1-csX)/2.0;
            return aColor.setChansRGB_dbl(std::clamp(csX+ampl*(-0.14861*std::cos(angle)+1.78277*std::sin(angle)), 0.0, 1.0),
                                          std::clamp(csX+ampl*(-0.29227*std::cos(angle)-0.90649*std::sin(angle)), 0.0, 1.0),
                                          std::clamp(csX+ampl*(+1.97294*std::cos(angle)),                         0.0, 1.0));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csX A value in [0, 1] that identifies the color in the scheme.
              @return Returns a colorTpl value */
          static inline colorTpl c(csFltType csX) { colorTpl tmp; return c(tmp, csX); }
      };
#endif
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template for HSL color schemes.
          If clrChanT is integral, this is a discrete color scheme, otherwise it is continuous.. */
      template<cornerColorEnum corner>
      class csHSLh_tpl {
        public:
          constexpr static csIntType numC = (chanIsInt ? meanChanVal : 0);
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csVal Index of color in pallet.  Wrapped to [0, meanChanVal].
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csNatType csVal) {
            clrChanT cVal = static_cast<clrChanT>(numberWrap(csVal, meanChanVal));
            colorTpl cc(corner);
            return aColor.setChansRGB(static_cast<clrChanT>(meanChanVal + (meanChanVal < cc.getRed()   ? cVal : -cVal)),
                                      static_cast<clrChanT>(meanChanVal + (meanChanVal < cc.getGreen() ? cVal : -cVal)),
                                      static_cast<clrChanT>(meanChanVal + (meanChanVal < cc.getBlue()  ? cVal : -cVal)));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csVal Index of color in pallet.  Wrapped to [0, meanChanVal].
              @return Returns a colorTpl value */
          static inline colorTpl c(csNatType csVal) { colorTpl tmp; return c(tmp, csVal); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template providing RGB color cube gradiant color schemes */
      template<cornerColorEnum...corners>
      class csCC_tpl {
        public:
          constexpr static csIntType numC = ((sizeof...(corners)) - 1) * chanStepMax + 1;
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csG Integer used to select a color from the discrete gradiaant.
              @return Returns a reference to \a aColor. */
          template<typename saT> static inline colorTpl& c(colorRefType aColor, saT csG) requires (std::floating_point<saT>) {
            csFltType csX = static_cast<csFltType>(csG);
            return aColor.cmpRGBcornerCGradiant(csX, numA, cols);
          }
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csG    Floating point value in [0, 1] used to select a color from the continuous color gradiant.
              @return Returns a reference to \a aColor. */
          template<typename saT> static inline colorTpl& c(colorRefType aColor, saT csG) requires (std::integral<saT>) {
            csIntType csIdx = static_cast<csIntType>(csG);
            return aColor.cmpRGBcornerDGradiant(csIdx % numC, numA, cols);
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csG color scheme selector
              @return Returns a colorTpl value */
          template<typename saT> static inline colorTpl c(saT csG) requires (std::integral<saT> || std::floating_point<saT>) {
            colorTpl tmp;
            return c(tmp, csG);
          }
        private:
          constexpr static int numA = (sizeof...(corners));
          constexpr static cornerColorEnum cols[] = { corners... };
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Binary color scheme. First color for even inputs and second color for odd. */
      template<cornerColorEnum a, cornerColorEnum b>
      class csBin_tpl {
        public:
          constexpr static csIntType numC = 2;
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Not wrapped or clipped.  Even values get color \a a, while odd values get color \a b.
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csIntType csIdx) { if (csIdx % 2) return aColor.setToCorner(b); else return aColor.setToCorner(a); }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Not wrapped or clipped.  Even values get color \a a, while odd values get color \a b.
              @return Returns a colorTpl value */
          static inline colorTpl c(csIntType csIdx) { colorTpl tmp; return c(tmp, csIdx); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template for fixed size pallets. */
      template<uint32_t...colors>
      class csFP_tpl {
        public:
          constexpr static csIntType numC = (sizeof...(colors));
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csG Integer used to select a color from the discrete gradiaant.
              @return Returns a reference to \a aColor. */
          template<typename saT> static inline colorTpl& c(colorRefType aColor, saT csG) requires (std::floating_point<saT>) {
            csFltType csX = static_cast<csFltType>(csG);
            return aColor.cmpGradiant(numberWrap(csX, 1.0), numC, d);
          }
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csG    Floating point value in [0, 1] used to select a color from the continuous color gradiant.
              @return Returns a reference to \a aColor. */
          template<typename saT> static inline colorTpl& c(colorRefType aColor, saT csG) requires (std::integral<saT>) {
            csIntType csIdx = static_cast<csIntType>(csG);
            return aColor.setRGBfromLogPackIntARGB(d[csIdx % numC]);
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csG color scheme color selector
              @return Returns a colorTpl value */
          template<typename saT> static inline colorTpl c(saT csG) requires (std::integral<saT> || std::floating_point<saT>) {
            colorTpl tmp;
            return c(tmp, csG);
          }
        private:
          constexpr static uint32_t d[] = { colors... };
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template for Color Brewer 2 variable sized pallets. */
      template<csIntType mx, uint32_t...colors>
      class csCB_tpl {
        public:
          constexpr static csIntType minNumC = 3;
          constexpr static csIntType maxNumC = mx;
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csG Integer used to select a color from the discrete gradiaant.
              @param numC Number of colors for the given scheme.  Will be clamped to [minNumC, maxNumC].
              @return Returns a reference to \a aColor. */
          template<typename saT> static inline colorTpl& c(colorRefType aColor, saT csG, csIntType numC=maxNumC) requires (std::floating_point<saT>) {
            csFltType csX = static_cast<csFltType>(csG);
            csIntType b = std::clamp(numC, minNumC, maxNumC);
            return aColor.cmpGradiant(numberWrap(csX, 1.0), b, &d[b*(b-1)/2-3+0]);
          }
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csG    Floating point value in [0, 1] used to select a color from the continuous color gradiant.
              @param numC Number of colors for the given scheme.  Will be clamped to [minNumC, maxNumC].
              @return Returns a reference to \a aColor. */
          template<typename saT> static inline colorTpl& c(colorRefType aColor, saT csG, csIntType numC=maxNumC) requires (std::integral<saT>) {
            csIntType csIdx = static_cast<csIntType>(csG);
            csIntType b = std::clamp(numC, minNumC, maxNumC);
            csIntType i = csIdx % b;
            return aColor.setRGBfromLogPackIntARGB(d[b*(b-1)/2-3+i]);
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csG color scheme color selector
              @param numC Number of colors for the given scheme.  Will be clamped to [minNumC, maxNumC].
              @return Returns a colorTpl value */
          template<typename saT> static inline colorTpl c(saT csG, csIntType numC=maxNumC) requires (std::integral<saT> || std::floating_point<saT>) {
            colorTpl tmp;
            return c(tmp, csG, numC);
          }
        private:
          constexpr static uint32_t d[] = { colors... };
      };


      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template for web safe 216 pallets. */
      template<uint32_t...colors>
      class csWS_tpl {
        public:
          constexpr static csIntType numC = (sizeof...(colors));
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a reference to \a aColor. */
          static inline colorTpl&  c(colorRefType aColor, csIntType csIdx) { return aColor.setRGBfromLogPackIntARGB(d[csIdx % numC]);  }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a reference a colorTpl value. */
          static inline colorTpl c(csIntType csIdx) { colorTpl tmp; return c(tmp, csIdx); }
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csCol input color to convert to a web safe color.
              @return Returns a reference to \a aColor. */
          static colorTpl&  c(colorRefType aColor, colorRefType csCol) {
            aColor.copy(csCol);
            aColor.tfrmWebSafeRGB();
            int colIdx = 36 * (aColor.getRed_byte() / 0x33) + 6 * (aColor.getGreen_byte() / 0x33) + 1 * (aColor.getBlue_byte() / 0x33) + 1;
            return aColor.setRGBfromLogPackIntARGB(d[colIdx]);
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csCol input color to convert to a web safe color.
              @return Returns a reference a colorTpl value. */
          static colorTpl c(colorRefType csCol) { colorTpl tmp; return c(tmp, csCol); }
        private:
          constexpr static uint32_t d[] = { colors... };
      };

      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      /** @cond color-schemes */
      /* Doxygen is pretty bad at formatting these bits... */

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @defgroup cs Color Schemes */

#if !(MISSING_P1907R1)
      //========================================================================================================================================================
      /** @name Color Schemes: Polynomial */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /*- @class csPLYgrey
          @ingroup cs
          @extends csPLY_tpl
          Greyscale */
      typedef csPLY_tpl<1.0, 0.0,
                        1.0, 0.0,
                        1.0, 0.0> csPLYgrey;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYquad
          @ingroup cs
          @extends csPLY_tpl
          Quadratic */
      typedef csPLY_tpl<1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0,
                        1.0, 0.0, 0.0> csPLYquad;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYturbo
          @ingroup cs
          @extends csPLY_tpl
          Similar to the Google turbo colormap.
          Note this colormap is not identical to turbo, and lacks some of it's more sophisticated characteristics; however, it looks nice.
          See: https://ai.googleblog.com/2019/08/turbo-improved-rainbow-colormap-for.html */
      typedef csPLY_tpl< 40703.92740, -218720.2701,   492368.2177, -590441.1804,   384271.9078, -101352.6555,  -30425.81099,
                         32619.05953, -10529.162296, 1625.5688083, -124.13217495,  4.867108400, 0.15787894011,
                         20766.64723, -122258.4886,   315808.0723, -470687.9792,   447662.9929, -283594.9850,  121141.42864,
                        -34482.96363,  6288.268231, -682.8118257,   37.74849512,  2.025549368, 0.06643490255,
                        -94331.85477,  587011.8043, -1597312.2220, 2495306.9899, -2470958.0510, 1616523.3372, -706621.97816,
                        204052.57726, -37536.525321, 4109.7062335, -257.68681737, 13.750387410, 0.16179522842>                          csPLYturbo;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYparula
          @ingroup cs
          @extends csPLY_tpl
          Similar to the Matlab parula colormap.
          Note this colormap is not identical to parula, and lacks some of it's more sophisticated characteristics; however, it looks nice.
          See: https://www.mathworks.com/help/matlab/ref/parula.html */
      typedef csPLY_tpl< 62043.87545, -399037.6523, 1122946.9120, -1812238.5254, 1846100.4184, -1230398.5816,  537273.93047,
                       -149254.730651, 24535.019552, -2015.3894764, 44.825447931, 0.6772663755, 0.2018889435,
                        -17121.77553,  108751.1007, -300422.7570,   473217.4661, -468061.6834,   301522.8593, -126770.41694,
                         33776.781210, -5288.933402,   404.6316583, -7.800267203, 1.3431462881, 0.1677335602,
                        -17004.66127,  100139.7442, -255248.5285,   366029.9549, -319570.5392,   169195.6211,  -48015.67328,
                          2478.369459,  2717.762128,  -795.8032035, 72.119793045, 1.1497391882, 0.5347179324>                           csPLYparula;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYmagma
          @ingroup cs
          @extends csPLY_tpl
          Similar, but not identical, to the matplotlib magma colormap.
          See: https://bids.github.io/colormap/ and https://matplotlib.org/stable/tutorials/colors/colormaps.html */
      typedef csPLY_tpl<746.7387907, -3433.588054,   6464.361262,  -6369.328232,   3470.981211, -1010.528460,   141.7946515,
                        -15.78575778,   6.066078845,  0.2765580349, 0.000406276347,
                        885.3555317, -5488.721941,  14347.739660, -20613.711506,  17758.797775, -9380.063372,  2976.8215781,
                       -529.56166374,  45.254936301, -0.9276250448, 0.006923020887,
                      -3360.6362774, 17553.826465, -38851.355442,  47349.901018, -34548.072322, 15336.155184, -3997.3017542,
                        548.12480687, -32.540585926,  2.6406562133, 0.006263758764>                                                     csPLYmagma;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYinferno
          @ingroup cs
          @extends csPLY_tpl
          Similar, but not identical, to the matplotlib inferno colormap.
          See: https://bids.github.io/colormap/ and https://matplotlib.org/stable/tutorials/colors/colormaps.html */
      typedef csPLY_tpl<-19.63292067,    452.2107953, -1685.008066,   2775.510486, -2442.279827,   1181.312494, -280.5809421,
                         10.74924866,  8.60430465,  0.1030211659, 0.002048171596,
                       1970.76446015, -10379.8617699, 23277.924908, -28925.873437, 21688.815122, -10002.539645, 2763.0755166,
                       -419.99828889, 28.92908793, -0.2365793129, 0.001175881895,
                       2525.53763382, -12168.1567723, 24862.266312, -28273.600973, 19817.598983,  -8983.810158, 2683.7805375,
                       -515.72960422, 52.67809976,  0.0641022894, 0.024051180021>                                                       csPLYinferno;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYplasma
          @ingroup cs
          @extends csPLY_tpl
          Similar, but not identical, to the matplotlib plasma colormap.
          See: https://bids.github.io/colormap/ and https://matplotlib.org/stable/tutorials/colors/colormaps.html */
      typedef csPLY_tpl<-43.8322257,   285.8375115,  -806.7514473,   1301.765273, -1325.274751,   878.0715655,  -374.7228293,
                         98.20716947, -15.31425214,  2.899584724, 0.05309687850,
                       1014.1378090, -5599.3136737, 13256.9879694, -17529.001879, 14102.556299, -7032.4501033,  2110.7323912,
                       -350.31653834,  28.69509557, -1.086029536, 0.03452846048,
                       -829.5844973,  4029.2020771, -8461.6295286,  10078.322085, -7471.246818,  3531.4365043, -1036.2596994,
                        175.24253651, -17.51426724,  1.646647586, 0.52562476199>                                                        csPLYplasma;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYviridis
          @ingroup cs
          @extends csPLY_tpl
          Similar, but not identical, to the matplotlib viridis colormap.
          See: https://bids.github.io/colormap/ and https://matplotlib.org/stable/tutorials/colors/colormaps.html */
      typedef csPLY_tpl<-5.432077171,   4.751786889,  6.203735901,  -4.599931518, -0.32724109679, 0.1077083262, 0.274455424454,
                         4.641571316, -13.749439404, 14.153964947,  -5.758238189,  0.21481356454, 1.3964696839, 0.005767962397,
                        26.272107604, -65.320967828, 56.656299565, -19.291808950,  0.09197688076, 1.3867705979, 0.332663881113>         csPLYviridis;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYcividis
          @ingroup cs
          @extends csPLY_tpl
          Similar, but not identical, to the cividis colormap.
          Note this map dosen't have the flat red and sharp increase in blue at the start of the map.
          See: https://github.com/marcosci/cividis and https://matplotlib.org/stable/tutorials/colors/colormaps.html */
      typedef csPLY_tpl<-10.6296994279,  27.5479183452, -25.1086313881,  9.3401209056, -0.1385953043, -0.0177903167,
                         -0.2641767638,   0.6924831686,  -0.5155427716,  0.2071305342,  0.6695454456,  0.1273928107,
                          9.7085048454, -25.9409393982,  24.1852720215, -9.7350011883,  1.7347333905,  0.3185822998>                    csPLYcividis;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYhsvRB
          @ingroup cs
          @extends csPLY_tpl
          Similar to csCColdeRainbow, but a little softer. */
      typedef csPLY_tpl<8.746561257e-11,   4.285714286, -4.285714286,  1.166666667e+00,
                        1.200000000e+01, -21.000000000,  9.023809524, -2.161907281e-13,
                       -1.200000000e+01,  15.000000000, -3.023809524,  2.380952381e-02>                                                 csPLYhsvRB;
      //@}
#endif

#if !(MISSING_P1907R1)
      //========================================================================================================================================================
      /** @name Color Schemes: CubeHelix */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCHstd
          @ingroup cs
          @extends csCubeHelix_tpl
          The "standard" cubehelix color scheme with start=0.5, rots=-1.5, hue=1, and gamma=1. */
      typedef csCubeHelix_tpl<0.5, -1.5, 1.0, 1.0> csCHstd;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCHblu
          @ingroup cs
          @extends csCubeHelix_tpl
          The "blues" cubehelix color scheme with start=0.5, rots=-0.5, hue=1, and gamma=1. */
      typedef csCubeHelix_tpl<0.5, -0.5, 1.0, 1.0> csCHblu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCHvio
          @ingroup cs
          @extends csCubeHelix_tpl
          The "violets" cubehelix color scheme with start=0.5, rots=0.0, hue=1, and gamma=1. */
      typedef csCubeHelix_tpl<0.5,  0.0, 1.0, 1.0> csCHvio;
      //@}
#endif

      //========================================================================================================================================================
      /** @name Color Schemes: RGB Constant Brightness Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCconsTwo
          @ingroup cs
          @extends csCC_tpl
          Color cycle around the cube with constant brightness of two. Provides (mjr::colorTpl::chanStepMax*3+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::CYAN, cornerColorEnum::MAGENTA, cornerColorEnum::YELLOW, cornerColorEnum::CYAN>  csCCconsTwo;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCconsOne
          @ingroup cs
          @extends csCC_tpl
          Color cycle around the cube with constant brightness of one. Provides (mjr::colorTpl::chanStepMax*3+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::BLUE, cornerColorEnum::RED, cornerColorEnum::GREEN, cornerColorEnum::BLUE>       csCCconsOne;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: Start and end with a primary with the secondary mixed from the primaries in the middle.   */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCmixRYG
          @ingroup cs
          @extends csCC_tpl
          Provides (mjr::colorTpl::chanStepMax*2+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::RED, cornerColorEnum::YELLOW, cornerColorEnum::GREEN>  csCCmixRYG;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCmixRMB
          @ingroup cs
          @extends csCC_tpl
          Provides (mjr::colorTpl::chanStepMax*2+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::RED, cornerColorEnum::MAGENTA, cornerColorEnum::BLUE>  csCCmixRMB;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCmixGCB
          @ingroup cs
          @extends csCC_tpl
          Provides (mjr::colorTpl::chanStepMax*2+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::GREEN, cornerColorEnum::CYAN, cornerColorEnum::BLUE>  csCCmixGCB;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: RGB Divergent Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCdivBWR
          @ingroup cs
          @extends csCC_tpl
          Divergent color scheme with blue on one end and red on the other -- white in the middle. Provides (mjr::colorTpl::chanStepMax*2+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::BLUE, cornerColorEnum::WHITE, cornerColorEnum::RED>     csCCdivBWR;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCdivCWM
          @ingroup cs
          @extends csCC_tpl
          Divergent color scheme with cyan on one end and magenta on the other -- white in the middle. Provides (mjr::colorTpl::chanStepMax*2+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::CYAN, cornerColorEnum::WHITE, cornerColorEnum::MAGENTA> csCCdivCWM;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: RGB Cube Diagional Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCdiag01
          @ingroup cs
          @extends csCC_tpl
          Gradient across the diagonal of the RGB color cube from black to white.  Provides about (mjr::colorTpl::chanStepMax + 1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK,   cornerColorEnum::WHITE> csCCdiag01;
      /** @class csCCdiag10
          @ingroup cs
          @extends csCC_tpl
          Gradient across the diagonal of the RGB color cube from white to black.  Provides about (mjr::colorTpl::chanStepMax + 1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::WHITE,  cornerColorEnum::BLACK> csCCdiag10;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCdiagCR
          @ingroup cs
          @extends csCC_tpl
          Gradient across the diagonal of the RGB color cube from cyan to red.  Provides about (mjr::colorTpl::chanStepMax + 1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::CYAN,    cornerColorEnum::RED>   csCCdiagCR;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCdiagMG
          @ingroup cs
          @extends csCC_tpl
          Gradient across the diagonal of the RGB color cube from magenta to green.  Provides about (mjr::colorTpl::chanStepMax + 1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::MAGENTA, cornerColorEnum::GREEN> csCCdiagMG;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCdiagYB
          @ingroup cs
          @extends csCC_tpl
          Gradient across the diagonal of the RGB color cube from yellow to blue.  Provides about (mjr::colorTpl::chanStepMax + 1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::YELLOW,  cornerColorEnum::BLUE>  csCCdiagYB;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: Classic RGB Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCColdeFireRamp
          @ingroup cs
          @extends csCC_tpl
          Classic color cube "Fire Ramp". */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::RED, cornerColorEnum::YELLOW, cornerColorEnum::WHITE>                csCColdeFireRamp;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCColdeColdToHot
          @ingroup cs
          @extends csCC_tpl
          Classical cold to hot color cube ramp.  Provides (mjr::colorTpl::chanStepMax*4+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::BLUE, cornerColorEnum::CYAN, cornerColorEnum::GREEN,
                       cornerColorEnum::YELLOW, cornerColorEnum::RED>                                                                csCColdeColdToHot;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCColdeIceToWaterToHot
          @ingroup cs
          @extends csCC_tpl
          Modified version of the classical cold to hot color cube ramp.ramp. It starts at white (ice), moves up to blue (cold),
          then yellow through red (hot).  Provides (mjr::colorTpl::chanStepMax*4+1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::WHITE, cornerColorEnum::CYAN, cornerColorEnum::BLUE,
                       cornerColorEnum::YELLOW, cornerColorEnum::RED>                                                                csCColdeIceToWaterToHot;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCColdeRainbow
          @ingroup cs
          @extends csCC_tpl
          The classic HSV rainbow color scheme based upon an edge traversal of the RGB color cube.  Provides (6 * mjr::colorTpl::chanStepMax + 1) colors. */
      typedef csCC_tpl<cornerColorEnum::RED, cornerColorEnum::YELLOW, cornerColorEnum::GREEN, cornerColorEnum::CYAN,
                       cornerColorEnum::BLUE, cornerColorEnum::MAGENTA, cornerColorEnum::RED>                                        csCColdeRainbow;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: Classic Fractal RGB Gradients.
          Gradients frequently used to color fractal images.  */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCfractal0RYBCW
          @ingroup cs
          @extends csCC_tpl
             Provides (5 * mjr::colorTpl::chanStepMax + 1) colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::RED, cornerColorEnum::YELLOW, 
                       cornerColorEnum::BLUE, cornerColorEnum::CYAN, cornerColorEnum::WHITE>            csCCfractal0RYBCW;
      /** @class csCCfractalYR
          @ingroup cs
          @extends csCC_tpl
             Provides (mjr::colorTpl::chanStepMax + 1) colors. */
      typedef csCC_tpl<cornerColorEnum::YELLOW,  cornerColorEnum::RED>                                  csCCfractalYR;
      /** @class csCCfractalYB
          @ingroup cs
          @extends csCC_tpl
             Provides (mjr::colorTpl::chanStepMax + 1) colors. */
      typedef csCC_tpl<cornerColorEnum::YELLOW,  cornerColorEnum::BLUE>                                 csCCfractalYB;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: RGB Sum Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCsumRGB
          @ingroup cs
          @extends csCC_tpl
          RGB cube sum-ramp: RGB == Black -> Red -> Yellow -> White. Provides (3 * mjr::colorTpl::chanStepMax + 1) different colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::RED,   cornerColorEnum::YELLOW,  cornerColorEnum::WHITE> csCCsumRGB;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCsumBGR
          @ingroup cs
          @extends csCC_tpl
          RGB cube sum-ramp: BGR == Black -> Blue -> cyan -> White.  Provides (3 * mjr::colorTpl::chanStepMax + 1) different colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::BLUE,  cornerColorEnum::CYAN,    cornerColorEnum::WHITE> csCCsumBGR;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCsumGRB
          @ingroup cs
          @extends csCC_tpl
          RGB cube sum-ramp: GRB == Black -> Green -> yellow -> White.  Provides (3 * mjr::colorTpl::chanStepMax + 1) different colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::GREEN, cornerColorEnum::YELLOW,  cornerColorEnum::WHITE> csCCsumGRB;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCsumGBR
          @ingroup cs
          @extends csCC_tpl
          RGB cube sum-ramp: GBR == Black -> Green -> cyan -> White.  Provides (3 * mjr::colorTpl::chanStepMax + 1) different colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::GREEN, cornerColorEnum::CYAN,    cornerColorEnum::WHITE> csCCsumGBR;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCsumBRG
          @ingroup cs
          @extends csCC_tpl
          RGB cube sum-ramp: BRG == Black -> Blue -> magenta -> White. Provides (3 * mjr::colorTpl::chanStepMax + 1) different colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::BLUE,  cornerColorEnum::MAGENTA, cornerColorEnum::WHITE> csCCsumBRG;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCsumRBG
          @ingroup cs
          @extends csCC_tpl
          RGB cube sum-ramp: RBG Black -> Red -> Magenta -> White.  Provides (3 * mjr::colorTpl::chanStepMax + 1) different colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::RED,   cornerColorEnum::MAGENTA, cornerColorEnum::WHITE> csCCsumRBG;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: RGB Up-Down Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCudRg
          @ingroup cs
          @extends csCC_tpl
          RGB Up-Down Ramp: Rg == Red Up and Green Down == cyan -> magenta. Provides chanStepMax different colors.*/
      typedef csCC_tpl<cornerColorEnum::CYAN,    cornerColorEnum::MAGENTA> csCCudRg;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCudRb
          @ingroup cs
          @extends csCC_tpl
          RGB Up-Down Ramp: Rb == Red Up and Blue Down == cyan -> yellow. Provides chanStepMax different colors.*/
      typedef csCC_tpl<cornerColorEnum::CYAN,    cornerColorEnum::YELLOW>  csCCudRb;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCudGr
          @ingroup cs
          @extends csCC_tpl
          RGB Up-Down Ramp: Gr == Green Up and Red Down == magenta -> cyan. Provides chanStepMax different colors. */
      typedef csCC_tpl<cornerColorEnum::MAGENTA, cornerColorEnum::CYAN>    csCCudGr;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCudGb
          @ingroup cs
          @extends csCC_tpl
          RGB Up-Down Ramp: Gb == Green Up and Blue Down == magenta -> yellow. Provides chanStepMax different colors. */
      typedef csCC_tpl<cornerColorEnum::MAGENTA, cornerColorEnum::YELLOW>  csCCudGb;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCudBr
          @ingroup cs
          @extends csCC_tpl
          RGB Up-Down Ramp: Br == Blue Up and Red Down == yellow -> cyan. Provides chanStepMax different colors. */
      typedef csCC_tpl<cornerColorEnum::YELLOW,  cornerColorEnum::CYAN>    csCCudBr;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCudBg
          @ingroup cs
          @extends csCC_tpl
          RGB Up-Down Ramp: Bg == Blue Up and Green Down == yellow -> magenta. Provides chanStepMax different colors. */
      typedef csCC_tpl<cornerColorEnum::YELLOW,  cornerColorEnum::MAGENTA> csCCudBg;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: Ramp from black to corner */
      //@{
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::WHITE>   csCCu0W; //!< Ramp from black to white
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::RED>     csCCu0R; //!< Ramp from black to red
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::BLUE>    csCCu0B; //!< Ramp from black to blue
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::GREEN>   csCCu0G; //!< Ramp from black to green
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::CYAN>    csCCu0C; //!< Ramp from black to cyan
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::MAGENTA> csCCu0M; //!< Ramp from black to magenta
      typedef csCC_tpl<cornerColorEnum::BLACK, cornerColorEnum::YELLOW>  csCCu0Y; //!< Ramp from black to yellow
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: Binary */
      //@{
      typedef csBin_tpl<cornerColorEnum::BLACK,   cornerColorEnum::WHITE>  csBin01; //!< Binary Black-White color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::GREEN,   cornerColorEnum::BLUE>   csBinGB; //!< Binary Green-Blue color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::RED,     cornerColorEnum::BLUE>   csBinRB; //!< Binary Red-Blue color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::MAGENTA, cornerColorEnum::CYAN>   csBinMC; //!< Binary Magenta-Cyan color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::YELLOW,  cornerColorEnum::CYAN>   csBinYC; //!< Binary Yellow-Cyan color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::RED,     cornerColorEnum::GREEN>  csBinRG; //!< Binary Red-Green color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::MAGENTA, cornerColorEnum::YELLOW> csBinMY; //!< Binary Magenta-Yellow color scheme. First color for even inputs and second color for odd.
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: Pseudo-Grey
       These color schemes start with black and move toward white trying to increase perceptional brightness, they don't stay precisely on the diagonal. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPGrey3x
          @ingroup cs
          A Pseudo-Grey color scheme with 3 * mjr::colorTpl::chanStepMax colors. */
      class csPGrey3x {
        public:
          constexpr static csIntType numC = 3*chanStepMax;
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a reference to \a aColor. */
          static inline colorTpl&  c(colorRefType aColor, csIntType csIdx) {
            csIdx = csIdx % numC;
            return aColor.setChansRGB(static_cast<clrChanT>(csIdx / 3 + (csIdx%3==0?1:0)),
                                      static_cast<clrChanT>(csIdx / 3 + (csIdx%3==1?1:0)),
                                      static_cast<clrChanT>(csIdx / 3 + (csIdx%3==2?1:0)));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a colorTpl value */
          static inline colorTpl c(csIntType csIdx) { colorTpl tmp; return c(tmp, csIdx); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPGrey4x
          @ingroup cs
          A Pseudo-Grey color scheme with 4 * mjr::colorTpl::chanStepMax colors. */
      class csPGrey4x {
        public:
          constexpr static csIntType numC = 4*chanStepMax;
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csIntType csIdx) {
            csIdx = csIdx % numC;
            return aColor.setChansRGB(static_cast<clrChanT>(csIdx / 4 + ((csIdx+1)%4==0?1:0)),
                                      static_cast<clrChanT>(csIdx / 4 + ((csIdx+2)%4==0?1:0)),
                                      static_cast<clrChanT>(csIdx / 4 + ((csIdx+3)%4==0?1:0)));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a colorTpl value */
          static inline colorTpl c(csIntType csIdx) { colorTpl tmp; return c(tmp, csIdx); }
      };
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: HSL Saturation Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csHSLhR
          @ingroup cs
          @extends csHSLh_tpl
          HSL color scheme extending from the center of the HSL color space to the red vertex.
          Provides mjr::colorTpl::meanChanVal unique colors for integral clrChanT.  For floating point clrChanT, csIdx may be any value in [0, mjr::colorTpl::meanChanVal]. */
      typedef csHSLh_tpl<cornerColorEnum::RED> csHSLhR;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csHSLhG
          @ingroup cs
          @extends csHSLh_tpl
          HSL color scheme extending from the center of the HSL color space to the green vertex.
          Provides mjr::colorTpl::meanChanVal unique colors for integral clrChanT.  For floating point clrChanT, csIdx may be any value in [0, mjr::colorTpl::meanChanVal]. */
      typedef csHSLh_tpl<cornerColorEnum::GREEN> csHSLhG;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csHSLhB
          @ingroup cs
          @extends csHSLh_tpl
          HSL color scheme extending from the center of the HSL color space to the blue vertex.
          Provides mjr::colorTpl::meanChanVal unique colors for integral clrChanT.  For floating point clrChanT, csIdx may be any value in [0, mjr::colorTpl::meanChanVal]. */
      typedef csHSLh_tpl<cornerColorEnum::BLUE> csHSLhB;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csHSLhC
          @ingroup cs
          @extends csHSLh_tpl
          HSL color scheme extending from the center of the HSL color space to the cyan vertex.
          Provides mjr::colorTpl::meanChanVal unique colors for integral clrChanT.  For floating point clrChanT, csIdx may be any value in [0, mjr::colorTpl::meanChanVal]. */
      typedef csHSLh_tpl<cornerColorEnum::CYAN> csHSLhC;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csHSLhM
          @ingroup cs
          @extends csHSLh_tpl
          HSL color scheme extending from the center of the HSL color space to the magenta vertex.
          Provides mjr::colorTpl::meanChanVal unique colors for integral clrChanT.  For floating point clrChanT, csIdx may be any value in [0, mjr::colorTpl::meanChanVal]. */
      typedef csHSLh_tpl<cornerColorEnum::MAGENTA> csHSLhM;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csHSLhY
          @ingroup cs
          @extends csHSLh_tpl
          HSL color scheme extending from the center of the HSL color space to the yellow vertex.
          Provides mjr::colorTpl::meanChanVal unique colors for integral clrChanT.  For floating point clrChanT, csIdx may be any value in [0, mjr::colorTpl::meanChanVal]. */
      typedef csHSLh_tpl<cornerColorEnum::YELLOW> csHSLhY;
      //@}

      //========================================================================================================================================================
      /** @name Color Schemes: Rainbows */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csRainbowLA
          @ingroup cs
          Computes a color value based upon a linear approximation of the color match functions used to approximate wavelength to RGB conversion.
          The linear color function approximation is not very accurate, but it is quite attractive. */
      class csRainbowLA {
        public:
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @param numC Number of colors to provide
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csIntType csIdx, csIntType numC) {
            csIdx = numberWrap(csIdx, numC);
            return aColor.setRGBfromWavelengthLA(mjr::genLinMap(static_cast<double>(csIdx),
                                                                static_cast<double>(0),
                                                                static_cast<double>(numC),
                                                                static_cast<double>(minWavelength),
                                                                static_cast<double>(maxWavelength)));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @param numC Number of colors to provide
              @return Returns a reference a colorTpl value. */
          static inline colorTpl c(csIntType csIdx, csIntType numC) {
            colorTpl tmp;
            return c(tmp, numC, csIdx);
          }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csRainbowCM
          @ingroup cs
          Computes a color value based upon an algorithm to convert wavelength to RGB that uses the Color Matching functions.
          @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum) */
      class csRainbowCM {
        public:
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param numC Number of colors to provide.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum)
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csIntType csIdx, csIntType numC, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR) {
            csIdx = numberWrap(csIdx, numC);
            return aColor.setRGBfromWavelengthCM(mjr::genLinMap(static_cast<double>(csIdx),
                                                                static_cast<double>(0),
                                                                static_cast<double>(numC),
                                                                static_cast<double>(minWavelength),
                                                                static_cast<double>(maxWavelength)),
                                                 interpMethod);
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @param numC Number of colors to provide.
              @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum)
              @return Returns a reference a colorTpl value. */
          static inline colorTpl c(csIntType csIdx, csIntType numC, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR) {
            colorTpl tmp;
            return c(tmp, numC, csIdx, interpMethod);
          }
      };
      //@}

      //========================================================================================================================================================
      /** @name "Web Safe" Color Schemes */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csWSnormalVision
          @ingroup cs
          @extends csWS_tpl
          The "web safe" color pallet of 216 colors as seen by someone with normal color vision.
          These colors were originally designed for low color web browsers in the early days of the internet.  Today they provide a simple (easy to compute)
          pallet for color reduction.  The colors are ordered in lexicographical ordering based upon the hexadecimal web-based color name scheme "#RRGGBB" --
          0 maps to "#000000", and 215 maps to "#ffffff".  Note that one can transform an rgb color into the nearest web safe color via tfrmWebSafeRGB(). */
      typedef csWS_tpl<0x000000, 0x000033, 0x000066, 0x000099, 0x0000CC, 0x0000FF, 0x003300, 0x003333, 0x003366, 0x003399, 0x0033CC,
                       0x0033FF, 0x006600, 0x006633, 0x006666, 0x006699, 0x0066CC, 0x0066FF, 0x009900, 0x009933, 0x009966, 0x009999,
                       0x0099CC, 0x0099FF, 0x00CC00, 0x00CC33, 0x00CC66, 0x00CC99, 0x00CCCC, 0x00CCFF, 0x00FF00, 0x00FF33, 0x00FF66,
                       0x00FF99, 0x00FFCC, 0x00FFFF, 0x330000, 0x330033, 0x330066, 0x330099, 0x3300CC, 0x3300FF, 0x333300, 0x333333,
                       0x333366, 0x333399, 0x3333CC, 0x3333FF, 0x336600, 0x336633, 0x336666, 0x336699, 0x3366CC, 0x3366FF, 0x339900,
                       0x339933, 0x339966, 0x339999, 0x3399CC, 0x3399FF, 0x33CC00, 0x33CC33, 0x33CC66, 0x33CC99, 0x33CCCC, 0x33CCFF,
                       0x33FF00, 0x33FF33, 0x33FF66, 0x33FF99, 0x33FFCC, 0x33FFFF, 0x660000, 0x660033, 0x660066, 0x660099, 0x6600CC,
                       0x6600FF, 0x663300, 0x663333, 0x663366, 0x663399, 0x6633CC, 0x6633FF, 0x666600, 0x666633, 0x666666, 0x666699,
                       0x6666CC, 0x6666FF, 0x669900, 0x669933, 0x669966, 0x669999, 0x6699CC, 0x6699FF, 0x66CC00, 0x66CC33, 0x66CC66,
                       0x66CC99, 0x66CCCC, 0x66CCFF, 0x66FF00, 0x66FF33, 0x66FF66, 0x66FF99, 0x66FFCC, 0x66FFFF, 0x990000, 0x990033,
                       0x990066, 0x990099, 0x9900CC, 0x9900FF, 0x993300, 0x993333, 0x993366, 0x993399, 0x9933CC, 0x9933FF, 0x996600,
                       0x996633, 0x996666, 0x996699, 0x9966CC, 0x9966FF, 0x999900, 0x999933, 0x999966, 0x999999, 0x9999CC, 0x9999FF,
                       0x99CC00, 0x99CC33, 0x99CC66, 0x99CC99, 0x99CCCC, 0x99CCFF, 0x99FF00, 0x99FF33, 0x99FF66, 0x99FF99, 0x99FFCC,
                       0x99FFFF, 0xCC0000, 0xCC0033, 0xCC0066, 0xCC0099, 0xCC00CC, 0xCC00FF, 0xCC3300, 0xCC3333, 0xCC3366, 0xCC3399,
                       0xCC33CC, 0xCC33FF, 0xCC6600, 0xCC6633, 0xCC6666, 0xCC6699, 0xCC66CC, 0xCC66FF, 0xCC9900, 0xCC9933, 0xCC9966,
                       0xCC9999, 0xCC99CC, 0xCC99FF, 0xCCCC00, 0xCCCC33, 0xCCCC66, 0xCCCC99, 0xCCCCCC, 0xCCCCFF, 0xCCFF00, 0xCCFF33,
                       0xCCFF66, 0xCCFF99, 0xCCFFCC, 0xCCFFFF, 0xFF0000, 0xFF0033, 0xFF0066, 0xFF0099, 0xFF00CC, 0xFF00FF, 0xFF3300,
                       0xFF3333, 0xFF3366, 0xFF3399, 0xFF33CC, 0xFF33FF, 0xFF6600, 0xFF6633, 0xFF6666, 0xFF6699, 0xFF66CC, 0xFF66FF,
                       0xFF9900, 0xFF9933, 0xFF9966, 0xFF9999, 0xFF99CC, 0xFF99FF, 0xFFCC00, 0xFFCC33, 0xFFCC66, 0xFFCC99, 0xFFCCCC,
                       0xFFCCFF, 0xFFFF00, 0xFFFF33, 0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF>                                          csWSnormalVision;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csWSprotanopia
          @ingroup cs
          @extends csWS_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Protanopia.
          For more about web safe colors, see mjr::colorTpl::csWSnormalVision. Also seemjr::colorTpl::csWSprotanopiaAlt. */
      typedef csWS_tpl<0x000000, 0x002346, 0x004487, 0x0060C1, 0x0078F0, 0x719CFF, 0x312C00, 0x2E2E30, 0x0D3366, 0x0053A6,
                       0x006FDE, 0x5B91FF, 0x635800, 0x61592E, 0x5C5B5F, 0x4E5F93, 0x1A66CC, 0x007EFE, 0x948500, 0x93852D, 0x90865E,
                       0x8A898F, 0x7E8DC2, 0x6792F8, 0xC5B000, 0xC5B12B, 0xC3B25D, 0xBFB38D, 0xB8B6BF, 0xADBAF2, 0xF6DC00, 0xF6DD29,
                       0xF5DD5C, 0xF2DF8C, 0xEDE1BD, 0xE6E4EE, 0x1E1B08, 0x002448, 0x00468B, 0x0062C4, 0x0079F2, 0x739DFF, 0x373200,
                       0x343333, 0x19376A, 0x0054AA, 0x0070E1, 0x6094FF, 0x655B00, 0x645B2F, 0x5E5D61, 0x506195, 0x2067CD, 0x2581FF,
                       0x958600, 0x95862E, 0x92875E, 0x8C8A90, 0x7F8EC3, 0x6993FA, 0xC6B100, 0xC6B22C, 0xC4B25D, 0xC0B48E, 0xB9B7BF,
                       0xAEBBF2, 0xF7DD00, 0xF7DD29, 0xF5DE5C, 0xF3DF8C, 0xEEE2BD, 0xE7E5EF, 0x3C360F, 0x323748, 0x00478E, 0x0065CA,
                       0x007CF8, 0x7AA1FF, 0x4A420B, 0x46433A, 0x324676, 0x0059B4, 0x0074EA, 0x6E9AFF, 0x6F6300, 0x6D6432, 0x686666,
                       0x59699C, 0x326ED5, 0x518DFF, 0x9B8B00, 0x9B8B2F, 0x988C61, 0x918F93, 0x8593C7, 0x6E98FE, 0xCAB500, 0xCAB52D,
                       0xC8B65E, 0xC4B88F, 0xBDBBC1, 0xB2BEF5, 0xFAE000, 0xFAE02A, 0xF8E15D, 0xF6E28D, 0xF1E4BF, 0xEAE7F0, 0x5A5117,
                       0x55514A, 0x39538F, 0x0067D0, 0x2782FF, 0x83A6FF, 0x635913, 0x5F5941, 0x505B80, 0x005EBF, 0x007AF6, 0x7DA2FF,
                       0x7F720D, 0x7E7237, 0x78746D, 0x6A77A5, 0x497BDF, 0x709BFF, 0xA69500, 0xA59532, 0xA29665, 0x9B9899, 0x8F9CCE,
                       0x83A4FF, 0xD2BC00, 0xD1BC2F, 0xCFBD61, 0xCBBF93, 0xC4C1C6, 0xB9C5FA, 0xFFE41C, 0xFFE532, 0xFEE65E, 0xFBE790,
                       0xF7E9C1, 0xEFECF4, 0x786C1E, 0x746C4C, 0x646D90, 0x356FD5, 0x5D91FF, 0x8CABFF, 0x7E711B, 0x7B7146, 0x707387,
                       0x5275C8, 0x4387FF, 0x8AAAFF, 0x948415, 0x92853C, 0x8C8675, 0x7F88AF, 0x648CEB, 0x87A7FF, 0xB5A20E, 0xB5A336,
                       0xB1A46A, 0xAAA5A0, 0x9EA8D7, 0x98B1FF, 0xDDC600, 0xDDC631, 0xDBC764, 0xD7C997, 0xCFCBCB, 0xC4CEFF, 0xFFE655,
                       0xFFE75C, 0xFFE873, 0xFFEB97, 0xFFF1C5, 0xF8F4F8, 0x968726, 0x93874E, 0x888892, 0x6E89D7, 0x7BA0FF, 0x96B1FF,
                       0x9A8B23, 0x988B4A, 0x8F8C8B, 0x7A8ECE, 0x779DFF, 0x96B1FF, 0xAC9A1E, 0xAA9A42, 0xA59B7C, 0x999DB9, 0x82A0F6,
                       0x98B2FF, 0xC8B317, 0xC7B43A, 0xC4B470, 0xBDB6A8, 0xB1B8E0, 0xAABDFF, 0xECD30F, 0xECD435, 0xE9D469, 0xE5D69D,
                       0xDED8D2, 0xCFD7FF, 0xFFE871, 0xFFE975, 0xFFEA86, 0xFFEDA2, 0xFFF2C8, 0xFFFAFA>                                csWSprotanopia;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csWSdeutanopia
          @ingroup cs
          @extends csWS_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Deutanopia.
          For more about web safe colors, see mjr::colorTpl::csWSnormalVision. Also seemjr::colorTpl::csWSdeutanopiaAlt. */
      typedef csWS_tpl<0x000000, 0x002135, 0x004168, 0x005E97, 0x0076BE, 0x008BDF, 0x362A0C, 0x2F2D34, 0x003E68, 0x005E9A, 0x0078C2,
                       0x008CE2, 0x6D5418, 0x6A5538, 0x5E5A69, 0x3D629A, 0x0078C9, 0x0090EC, 0xA37E25, 0xA27E3D, 0x9B816C, 0x8D869D,
                       0x728ECF, 0x3398FF, 0xDAA831, 0xD9A844, 0xD4AA6F, 0xCBAEA0, 0xBBB3D1, 0xA5BBFF, 0xFFCD72, 0xFFCD77, 0xFFCF87,
                       0xFFD3A6, 0xFBDAD4, 0xE6DCFF, 0x221A00, 0x131E30, 0x003F67, 0x005D96, 0x0076BF, 0x008BDF, 0x3D2F09, 0x373133,
                       0x003B65, 0x005D99, 0x0078C2, 0x008CE2, 0x705617, 0x6D5737, 0x615B68, 0x43639A, 0x0078C9, 0x0090EC, 0xA58600,
                       0xA4803C, 0x9D826B, 0x8F879D, 0x758FCE, 0x3999FF, 0xDBA830, 0xDAA943, 0xD6AB6F, 0xCCAEA0, 0xBDB4D1, 0xA7BBFF,
                       0xFFCD74, 0xFFCD78, 0xFFCF88, 0xFFD4A6, 0xFCDBD4, 0xE7DDFF, 0x453500, 0x3F352F, 0x253D60, 0x005A94, 0x0076BF,
                       0x008BE1, 0x534000, 0x4F4031, 0x3D4763, 0x005995, 0x0076C2, 0x008CE4, 0x7B5E11, 0x795F35, 0x6F6367, 0x586A98,
                       0x0076C9, 0x0090EE, 0xAC8421, 0xAA853B, 0xA4876A, 0x978C9C, 0x8093CD, 0x519CFE, 0xE0AC2E, 0xDFAC42, 0xDAAE6E,
                       0xD2B29F, 0xC3B7D1, 0xADBEFF, 0xFFCE79, 0xFFCF7C, 0xFFD08B, 0xFFD5A7, 0xFFDDD3, 0xEBDFFF, 0x674F00, 0x634E2C,
                       0x57535F, 0x385B90, 0x0073C0, 0x008CE5, 0x705600, 0x6C552D, 0x625961, 0x496192, 0x0073C2, 0x008DE8, 0x8E6C00,
                       0x8C6D31, 0x847064, 0x737696, 0x507FC7, 0x0090F3, 0xA69500, 0xB78E37, 0xB29068, 0xA6949A, 0x929BCC, 0x6FA4FD,
                       0xE9B22A, 0xE8B33F, 0xE4B56C, 0xDBB89D, 0xCEBDCF, 0xB9C4FF, 0xFFD080, 0xFFD184, 0xFFD291, 0xFFD6A9, 0xFFDDD0,
                       0xF4E4FF, 0x886900, 0x856726, 0x7E6A5E, 0x6E7190, 0x4B7AC0, 0x008CEC, 0x8F6D00, 0x8C6C27, 0x856F5F, 0x767591,
                       0x577EC2, 0x008DEF, 0xA67F00, 0xA47E2B, 0x9E8161, 0x918694, 0x7B8DC5, 0x4C97F6, 0xCA9A00, 0xC99B32, 0xC49D65,
                       0xBAA198, 0xAAA7C9, 0x8FAEFB, 0xF6C600, 0xF5BC3B, 0xF1BE6A, 0xEAC19B, 0xDEC6CD, 0xCBCCFF, 0xFFD389, 0xFFD38C,
                       0xFFD497, 0xFFD8AB, 0xFFDECC, 0xFFEAFD, 0xA98200, 0xA8801A, 0xA2835B, 0x97888E, 0x838FC0, 0x5E98F1, 0xAE8600,
                       0xAD841C, 0xA7875C, 0x9D8B8F, 0x8A92C1, 0x679BF2, 0xC09300, 0xBF9322, 0xBB955E, 0xB19992, 0xA09FC3, 0x85A7F5,
                       0xDFAA00, 0xDEAB2A, 0xDAAC62, 0xD2B095, 0xC5B5C7, 0xB0BCF9, 0xFFC750, 0xFFC857, 0xFFCA6F, 0xFCCD99, 0xF1D2CB,
                       0xE1D8FD, 0xFFD592, 0xFFD594, 0xFFD79D, 0xFFDAAD, 0xFFDFC8, 0xFFE8EF>                                          csWSdeutanopia;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csWStritanoptia
          @ingroup cs
          @extends csWS_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Tritanoptia.
          For more about web safe colors, see mjr::colorTpl::csWSnormalVision. Also seemjr::colorTpl::csWStritanoptiaAlt. */
      typedef csWS_tpl<0x000000, 0x001C1D, 0x003739, 0x005155, 0x006A6E, 0x007F85, 0x173033, 0x0A3236, 0x004347, 0x00595E, 0x006F74,
                       0x008389, 0x2D5F66, 0x2A6068, 0x15656D, 0x00727A, 0x00828A, 0x00929A, 0x448F9A, 0x42909A, 0x39929D, 0x1F97A3,
                       0x00A1AC, 0x00ACB7, 0x5ABFCD, 0x59BFCD, 0x54C1CF, 0x47C4D3, 0x29CAD9, 0x00D0DF, 0x73EDFF, 0x73EDFF, 0x73EEFF,
                       0x72EEFF, 0x70EFFF, 0x6EEFFF, 0x330600, 0x301517, 0x212A2D, 0x00474B, 0x006469, 0x007C82, 0x363033, 0x333236,
                       0x263C41, 0x005056, 0x006A70, 0x008187, 0x415F66, 0x3F6068, 0x35656D, 0x146D76, 0x007F87, 0x009099, 0x518F9A,
                       0x4F909A, 0x49929D, 0x3997A3, 0x00A0AC, 0x00ABB7, 0x64BFD7, 0x63BFCD, 0x5EC1CF, 0x54C4D3, 0x3ECAD9, 0x00D1E0,
                       0x7AEDFF, 0x7AEDFF, 0x79EEFF, 0x78EEFF, 0x76EFFF, 0x74EFFF, 0x660B00, 0x651615, 0x602B2D, 0x563F44, 0x42545B,
                       0x006B73, 0x673033, 0x663336, 0x623D41, 0x584C51, 0x445D64, 0x007179, 0x6C5F66, 0x6B6067, 0x67656C, 0x5E6D75,
                       0x4D7982, 0x228791, 0x758F9A, 0x74909A, 0x71929D, 0x6997A3, 0x5A9FAB, 0x3EA9B6, 0x82BECD, 0x81BFCD, 0x7EC1CF,
                       0x77C4D3, 0x6BCAD9, 0x57D1E1, 0x92EDFF, 0x92EDFF, 0x90EEFF, 0x8EEEFF, 0x8BEFFF, 0x88EFFF, 0x991100, 0x981612,
                       0x962B2C, 0x904044, 0x87555B, 0x796A71, 0x9A3032, 0x993335, 0x963D40, 0x914C51, 0x885D64, 0x7A7078, 0x9D5F66,
                       0x9C6067, 0x9A656C, 0x946D75, 0x8C7982, 0x7E8791, 0xA28F99, 0xA2909A, 0x9F929D, 0x9A97A3, 0x929FAB, 0x86A9B6,
                       0xABBECD, 0xAABFCD, 0xA8C1CF, 0xA3C4D3, 0x9CCAD9, 0x91D1E1, 0xB6EDFF, 0xB5EDFF, 0xB4EEFF, 0xB0EEFF, 0xACEFFF,
                       0xA6EFFF, 0xCC1600, 0xCB170B, 0xCA2B2B, 0xC64043, 0xC0555A, 0xB76A71, 0xCC3030, 0xCC3334, 0xCA3D3F, 0xC64C50,
                       0xC15E64, 0xB87178, 0xCF5F65, 0xCE6067, 0xCC656C, 0xC96E75, 0xC37982, 0xBB8791, 0xD38F99, 0xD2909A, 0xD0929D,
                       0xCD98A2, 0xC79FAB, 0xBFA9B6, 0xD9BECC, 0xD8BFCD, 0xD7C1CF, 0xD3C4D3, 0xCECAD9, 0xC6D1E1, 0xE0EEFF, 0xE0EEFF,
                       0xDDEEFF, 0xD9EEFF, 0xD3EFFF, 0xCBEFFF, 0xFE1C00, 0xFE1A00, 0xFD2B28, 0xFA4042, 0xF6555A, 0xF06A71, 0xFF3331,
                       0xFF3332, 0xFE3D3E, 0xFB4C4F, 0xF75E63, 0xF07178, 0xFF6569, 0xFF656A, 0xFF666C, 0xFD6E74, 0xF87981, 0xF28791,
                       0xFF949C, 0xFF949D, 0xFF959E, 0xFF99A2, 0xFC9FAA, 0xF6A9B5, 0xFFBECA, 0xFFBFCA, 0xFFC0CD, 0xFFC4D1, 0xFFCAD8,
                       0xFBD1E1, 0xFFE4F2, 0xFFE5F3, 0xFFE6F5, 0xFFEAF9, 0xFDEFFF, 0xF4F0FF>                                          csWStritanoptia;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csWSprotanopiaAlt
          @ingroup cs
          @extends csWS_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Protanopia.
          For more about web safe colors, see mjr::colorTpl::csWSnormalVision. Also seemjr::colorTpl::csWSprotanopia. */
      typedef csWS_tpl<0x000000, 0x000E33, 0x001D66, 0x002B99, 0x003ACC, 0x0048FF, 0x422F00, 0x303133, 0x003566, 0x003D99, 0x0047CC,
                       0x0053FF, 0x845D00, 0x7E5E33, 0x606266, 0x266699, 0x006BCC, 0x0072FF, 0xC68C00, 0xC38D33, 0xB38F66, 0x909399,
                       0x6896CC, 0x009BFF, 0xFFBB00, 0xFFBB32, 0xFCBD66, 0xE6C099, 0xC0C4CC, 0x9DC7FF, 0xFFE900, 0xFFEA31, 0xFFEB65,
                       0xFFED99, 0xFFF1CC, 0xF0F5FF, 0x1A1202, 0x001633, 0x002166, 0x002E99, 0x003BCC, 0x0049FF, 0x453100, 0x333333,
                       0x003766, 0x003F99, 0x0048CC, 0x0053FF, 0x855E00, 0x7F5F33, 0x616366, 0x2A6699, 0x006CCC, 0x0072FF, 0xC78C00,
                       0xC38D33, 0xB48F66, 0x919499, 0x6997CC, 0x009BFF, 0xFFBB00, 0xFFBB32, 0xFCBD66, 0xE6C099, 0xC0C5CC, 0x9DC8FF,
                       0xFFEA00, 0xFFEA31, 0xFFEB65, 0xFFED99, 0xFFF1CC, 0xF0F6FF, 0x332405, 0x1D2733, 0x002D66, 0x003699, 0x0042CC,
                       0x004EFF, 0x4F3804, 0x413A33, 0x003E66, 0x004499, 0x004DCC, 0x0057FF, 0x8A6100, 0x846233, 0x666666, 0x376999,
                       0x006ECC, 0x0075FF, 0xC98E00, 0xC68F33, 0xB79166, 0x939599, 0x6E99CC, 0x009DFF, 0xFFBC00, 0xFFBD32, 0xFEBE66,
                       0xE8C199, 0xC2C6CC, 0xA0C9FF, 0xFFEA00, 0xFFEB32, 0xFFEC65, 0xFFEE99, 0xFFF2CC, 0xF2F6FF, 0x4D3607, 0x3E3833,
                       0x003C66, 0x004399, 0x004CCC, 0x0057FF, 0x604407, 0x564533, 0x2E4966, 0x004E99, 0x0056CC, 0x005FFF, 0x926703,
                       0x8D6833, 0x726C66, 0x496F99, 0x0074CC, 0x007AFF, 0xCE9200, 0xCB9233, 0xBD9566, 0x999999, 0x769CCC, 0x00A0FF,
                       0xFFBF00, 0xFFBF32, 0xFFC166, 0xEDC499, 0xC6C8CC, 0xA5CBFF, 0xFFEC00, 0xFFED32, 0xFFEE66, 0xFFF099, 0xFFF4CC,
                       0xF4F8FF, 0x66490A, 0x5E4A33, 0x3A4E66, 0x005299, 0x0059CC, 0x0062FF, 0x745209, 0x6D5333, 0x4D5766, 0x005B99,
                       0x0061CC, 0x0069FF, 0x9E7008, 0x9A7133, 0x837466, 0x5E7899, 0x007CCC, 0x0081FF, 0xD69700, 0xD39833, 0xC59A66,
                       0xA59E99, 0x82A1CC, 0x16A5FF, 0xFFC300, 0xFFC333, 0xFFC466, 0xF3C799, 0xCCCCCC, 0xACCFFF, 0xFFEF00, 0xFFEF32,
                       0xFFF166, 0xFFF399, 0xFFF6CC, 0xF9FBFF, 0x805B0C, 0x7A5C34, 0x5C6066, 0x006399, 0x0069CC, 0x0070FF, 0x8A620C,
                       0x856334, 0x676766, 0x396A99, 0x006FCC, 0x0076FF, 0xAE7B0B, 0xAA7C34, 0x967E66, 0x738299, 0x2786CC, 0x008BFF,
                       0xE19F08, 0xDE9F33, 0xD1A166, 0xB3A599, 0x90A9CC, 0x4FACFF, 0xFFC800, 0xFFC833, 0xFFCA66, 0xFCCC99, 0xD7D1CC,
                       0xB7D4FF, 0xFFF300, 0xFFF332, 0xFFF466, 0xFFF799, 0xFFFACC, 0xFFFFFF>                                          csWSprotanopiaAlt;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csWSdeutanopiaAlt
          @ingroup cs
          @extends csWS_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Deutanopia.
          For more about web safe colors, see mjr::colorTpl::csWSnormalVision. Also seemjr::colorTpl::csWSdeutanopia. */
      typedef csWS_tpl<0x000000, 0x001433, 0x002866, 0x003C99, 0x0050CB, 0x0064FE, 0x3A2A0B, 0x2C2F33, 0x003866, 0x004699, 0x0057CB,
                       0x0069FE, 0x755316, 0x6F5635, 0x585D67, 0x226599, 0x0070CC, 0x007EFF, 0xAF7D20, 0xAC7E39, 0x9E8468, 0x848C9A,
                       0x5F93CC, 0x009DFF, 0xEAA72B, 0xE8A83F, 0xDFAB6B, 0xCBB29B, 0xAFBBCD, 0x8FC2FF, 0xFFD036, 0xFFD146, 0xFFD46E,
                       0xFFD99D, 0xF7E1CE, 0xDBE9FF, 0x231800, 0x001F33, 0x002D66, 0x003F99, 0x0052CB, 0x0065FE, 0x412E09, 0x333333,
                       0x003C66, 0x004999, 0x0059CB, 0x006BFE, 0x775515, 0x725735, 0x5B5F66, 0x2C6799, 0x0072CC, 0x007FFE, 0xB17E20,
                       0xAE7F39, 0xA08568, 0x858D9A, 0x6294CC, 0x009EFF, 0xEBA72B, 0xE9A83F, 0xE0AC6B, 0xCCB39B, 0xB0BBCD, 0x91C2FF,
                       0xFFD136, 0xFFD246, 0xFFD46E, 0xFFDA9D, 0xF8E2CE, 0xDCEAFF, 0x453000, 0x393532, 0x003E65, 0x004B98, 0x005ACB,
                       0x006CFE, 0x563C00, 0x4D4032, 0x2C4865, 0x005398, 0x0061CB, 0x0071FE, 0x825C11, 0x7D5E34, 0x666666, 0x446D99,
                       0x0077CC, 0x0084FE, 0xB7821E, 0xB48338, 0xA78968, 0x8C9199, 0x6C98CC, 0x00A1FF, 0xEFAA2A, 0xEDAB3E, 0xE4AF6A,
                       0xD2B69B, 0xB5BECD, 0x97C5FF, 0xFFD335, 0xFFD445, 0xFFD66E, 0xFFDC9D, 0xFCE4CE, 0xE0ECFF, 0x684900, 0x624B2F,
                       0x485364, 0x005C98, 0x0069CB, 0x0077FE, 0x725000, 0x6D5230, 0x545A64, 0x106398, 0x006ECB, 0x007CFE, 0x946800,
                       0x906A32, 0x7E7165, 0x617898, 0x0081CB, 0x008DFE, 0xC38A1A, 0xC08B37, 0xB49067, 0x999999, 0x7E9FCC, 0x38A8FF,
                       0xF7B027, 0xF5B13D, 0xEDB46A, 0xDBBB9B, 0xBEC4CD, 0xA3CAFF, 0xFFD733, 0xFFD844, 0xFFDA6D, 0xFFE09D, 0xFFE7CE,
                       0xE7F0FF, 0x8B6100, 0x87632C, 0x736A63, 0x537297, 0x007BCA, 0x0087FE, 0x926600, 0x8E682C, 0x7B6F63, 0x5E7697,
                       0x007FCA, 0x008BFE, 0xAC7900, 0xA97A2F, 0x9A8064, 0x7F8897, 0x5790CB, 0x009AFE, 0xD4960E, 0xD19734, 0xC79B66,
                       0xB0A398, 0x94ABCB, 0x68B2FE, 0xFFB822, 0xFFB93A, 0xFABC68, 0xEAC39A, 0xCCCCCC, 0xB3D2FF, 0xFFDE30, 0xFFDE42,
                       0xFFE16C, 0xFFE69C, 0xFFEDCD, 0xF1F6FF, 0xAE7900, 0xAB7A26, 0x9D8061, 0x818996, 0x5B90CA, 0x009AFD, 0xB37D00,
                       0xB07E27, 0xA38461, 0x878C96, 0x6494CA, 0x009DFD, 0xC78C00, 0xC58D2A, 0xB99162, 0x9F9A96, 0x83A1CA, 0x47AAFD,
                       0xE9A400, 0xE7A52F, 0xDEA964, 0xCAB097, 0xAEB9CA, 0x8DC0FE, 0xFFC319, 0xFFC436, 0xFFC767, 0xFDCD99, 0xE2D6CB,
                       0xC8DDFE, 0xFFE62B, 0xFFE73F, 0xFFE96B, 0xFFEE9B, 0xFFF5CD, 0xFFFFFF>                                          csWSdeutanopiaAlt;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csWStritanoptiaAlt
          @ingroup cs
          @extends csWS_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Tritanoptia.
          For more about web safe colors, see mjr::colorTpl::csWSnormalVision. Also seemjr::colorTpl::csWStritanoptia. */
      typedef csWS_tpl<0x000000, 0x00191E, 0x00323D, 0x004B5B, 0x00647A, 0x007C98, 0x202E31, 0x113237, 0x00404A, 0x005463, 0x006A7F,
                       0x00819C, 0x415C61, 0x3C5D63, 0x21646D, 0x00707E, 0x008093, 0x0093AC, 0x618A92, 0x5F8B93, 0x548F99, 0x3296A4,
                       0x00A1B4, 0x00AFC7, 0x82B8C2, 0x80B8C3, 0x79BBC7, 0x69C0CF, 0x42C8DA, 0x00D3EA, 0xA2E6F3, 0xA1E6F3, 0x9CE8F6,
                       0x91ECFC, 0x7DF2FF, 0x53FAFF, 0x340010, 0x2C1A1C, 0x00333A, 0x004B5A, 0x006479, 0x007D98, 0x392E2F, 0x333333,
                       0x004147, 0x005462, 0x006A7E, 0x00819C, 0x4D5C5F, 0x4A5E62, 0x39646C, 0x00707D, 0x008093, 0x0093AB, 0x698A91,
                       0x678B92, 0x5D8F98, 0x4296A3, 0x00A1B3, 0x00AFC6, 0x87B8C1, 0x85B8C2, 0x7FBBC6, 0x70C0CE, 0x4FC8DA, 0x00D3E9,
                       0xA6E6F2, 0xA5E6F3, 0xA0E8F6, 0x95ECFC, 0x82F2FF, 0x5CFAFF, 0x670021, 0x651527, 0x583338, 0x364E52, 0x006674,
                       0x007E94, 0x692C35, 0x673139, 0x5B4244, 0x3C565B, 0x006C7A, 0x008298, 0x725C5E, 0x705E60, 0x666666, 0x507278,
                       0x00818F, 0x0094A8, 0x838B8D, 0x818C8E, 0x7B9094, 0x6B97A0, 0x46A2B0, 0x00B0C4, 0x9AB8BF, 0x99B9C0, 0x94BCC4,
                       0x88C1CC, 0x71C9D8, 0x3CD4E7, 0xB5E6F0, 0xB4E7F1, 0xB0E9F4, 0xA7ECFA, 0x97F3FF, 0x7AFBFF, 0x9B0031, 0x990035,
                       0x933041, 0x854D54, 0x686969, 0x1C808C, 0x9C293F, 0x9A2E42, 0x943F4C, 0x86565B, 0x6B6E6F, 0x288591, 0xA15B63,
                       0xA05D65, 0x9A656A, 0x8D7275, 0x758387, 0x4496A2, 0xAC8B8E, 0xAA8C8F, 0xA59092, 0x999999, 0x86A4AA, 0x63B2BF,
                       0xBABABA, 0xB9BABB, 0xB5BDBF, 0xADC2C7, 0x9DCAD3, 0x83D5E3, 0xD0E7EC, 0xCFE8ED, 0xCBEAF0, 0xC4EDF6, 0xB7F3FF,
                       0xA3FCFF, 0xCE0042, 0xCD0044, 0xC92A4E, 0xC04A5D, 0xB1676F, 0x978284, 0xCF214C, 0xCE284E, 0xCA3C56, 0xC15463,
                       0xB26D75, 0x988788, 0xD3596B, 0xD25B6C, 0xCE6371, 0xC5717B, 0xB68388, 0x9E9899, 0xDA8A92, 0xD98B93, 0xD58F97,
                       0xCD989D, 0xBFA5A7, 0xAAB4B6, 0xE5B9BD, 0xE4BABE, 0xE0BDC0, 0xD9C3C5, 0xCCCCCC, 0xBBD6DD, 0xF3E8E9, 0xF2E9E9,
                       0xEFEBEB, 0xE9EFF0, 0xDFF5FA, 0xD0FDFF, 0xFF0052, 0xFF0054, 0xFE205B, 0xF84668, 0xED6478, 0xDD818B, 0xFF095A,
                       0xFF1B5C, 0xFF3662, 0xF8506E, 0xEE6B7D, 0xDE858F, 0xFF5674, 0xFF5875, 0xFF607A, 0xFB6F83, 0xF1818F, 0xE1979E,
                       0xFF8898, 0xFF8999, 0xFF8E9C, 0xFF96A3, 0xF7A3AC, 0xE8B3B8, 0xFFB8C1, 0xFFB9C2, 0xFFBCC4, 0xFFC2C9, 0xFFCBD0,
                       0xF2D7D9, 0xFFE7EC, 0xFFE8ED, 0xFFEAEE, 0xFFEFF2, 0xFFF6F7, 0xFFFFFF>                                          csWStritanoptiaAlt;
      //@}
      //========================================================================================================================================================
      /** @name Interesting Pallets */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcircular12
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xFF0000, 0xFF7D00, 0xFFFF00, 0x7DFF00, 0x66CC00, 0x66FFB2, 0x00FFFF,
                       0x007DFF, 0x0000FF, 0x7D00FF, 0xFF00FF, 0xFF007D>                                                              csFPcircular12;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcircular24
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xFF0000, 0xFF3F00, 0xFF7D00, 0xFFBE00, 0xFFE100, 0xFFFF00, 0x7DFF00, 0x7DCC00, 0x009600, 0x00BE00, 0x00FF5A,
                       0x00FFBE, 0x00FFFF, 0x00BEFF, 0x007DFF, 0x003FFF, 0x0000FF, 0x3F00FF, 0x7D00FF, 0xBE00FF, 0xFF00FF, 0xFF00BE,
                       0xFF007D, 0xFF003F>                                                                                            csFPcircular24;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPblAqGrYeOrReVi200
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x0000FF, 0x0008FF, 0x000FFF, 0x0017FF, 0x001FFF, 0x0027FF, 0x002EFF, 0x0036FF, 0x003EFF, 0x0046FF, 0x004DFF,
                       0x0055FF, 0x005DFF, 0x0064FF, 0x006CFF, 0x0074FF, 0x007CFF, 0x0083FF, 0x008BFF, 0x0093FF, 0x009BFF, 0x00A2FF,
                       0x00AAFF, 0x00B2FF, 0x00B9FF, 0x00C1FF, 0x00C9FF, 0x00D1FF, 0x00D8FF, 0x00E0FF, 0x00E8FF, 0x00F0FF, 0x00F7FF,
                       0x00FFFF, 0x00FDF8, 0x00FAF0, 0x01F8E9, 0x01F6E2, 0x01F3DB, 0x01F1D3, 0x02EFCC, 0x02EDC5, 0x02EABE, 0x02E8B6,
                       0x03E6AF, 0x03E3A8, 0x03E1A0, 0x03DF99, 0x04DC92, 0x04DA8B, 0x04D883, 0x04D67C, 0x05D375, 0x05D16E, 0x05CF66,
                       0x05CC5F, 0x06CA58, 0x06C850, 0x06C549, 0x06C342, 0x07C13B, 0x07BF33, 0x07BC2C, 0x07BA25, 0x08B81E, 0x08B516,
                       0x08B30F, 0x0FB50F, 0x17B70E, 0x1EBA0E, 0x25BC0D, 0x2CBE0D, 0x34C00C, 0x3BC30C, 0x42C50B, 0x49C70B, 0x51C90B,
                       0x58CC0A, 0x5FCE0A, 0x66D009, 0x6ED209, 0x75D508, 0x7CD708, 0x84D908, 0x8BDB07, 0x92DD07, 0x99E006, 0xA1E206,
                       0xA8E405, 0xAFE605, 0xB6E904, 0xBEEB04, 0xC5ED04, 0xCCEF03, 0xD3F203, 0xDBF402, 0xE2F602, 0xE9F801, 0xF0FB01,
                       0xF8FD00, 0xFFFF00, 0xFFFC00, 0xFFFA00, 0xFFF700, 0xFFF400, 0xFFF100, 0xFFEF00, 0xFFEC00, 0xFFE900, 0xFFE600,
                       0xFFE400, 0xFFE100, 0xFFDE00, 0xFFDC00, 0xFFD900, 0xFFD600, 0xFFD300, 0xFFD100, 0xFFCE00, 0xFFCB00, 0xFFC800,
                       0xFFC600, 0xFFC300, 0xFFC000, 0xFFBE00, 0xFFBB00, 0xFFB800, 0xFFB500, 0xFFB300, 0xFFB000, 0xFFAD00, 0xFFAA00,
                       0xFFA800, 0xFFA500, 0xFFA000, 0xFF9B00, 0xFF9600, 0xFF9100, 0xFF8C00, 0xFF8700, 0xFF8200, 0xFF7D00, 0xFF7800,
                       0xFF7300, 0xFF6E00, 0xFF6900, 0xFF6400, 0xFF5F00, 0xFF5A00, 0xFF5500, 0xFF5000, 0xFF4B00, 0xFF4600, 0xFF4100,
                       0xFF3C00, 0xFF3700, 0xFF3200, 0xFF2D00, 0xFF2800, 0xFF2300, 0xFF1E00, 0xFF1900, 0xFF1400, 0xFF0F00, 0xFF0A00,
                       0xFF0500, 0xFF0000, 0xFA0004, 0xF50008, 0xF0000C, 0xEB0010, 0xE60015, 0xE00019, 0xDB001D, 0xD60021, 0xD10025,
                       0xCC0029, 0xC7002D, 0xC20031, 0xBD0036, 0xB8003A, 0xB3003E, 0xAE0042, 0xA80046, 0xA3004A, 0x9E004E, 0x990052,
                       0x940057, 0x8F005B, 0x8A005F, 0x850063, 0x800067, 0x7B006B, 0x76006F, 0x700073, 0x6B0078, 0x66007C, 0x610080,
                       0x5C0084, 0x570088>                                                                                            csFPblAqGrYeOrReVi200;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanAlgae
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xD7F9D0, 0xD6F8CE, 0xD4F7CD, 0xD3F6CB, 0xD2F5CA, 0xD1F4C8, 0xCFF4C7, 0xCEF3C5, 0xCDF2C4, 0xCCF1C3, 0xCAF0C1,
                       0xC9EFC0, 0xC8EEBE, 0xC7EDBD, 0xC5ECBB, 0xC4EBBA, 0xC3EBB9, 0xC2EAB7, 0xC0E9B6, 0xBFE8B4, 0xBEE7B3, 0xBDE6B1,
                       0xBBE5B0, 0xBAE4AF, 0xB9E4AD, 0xB8E3AC, 0xB6E2AB, 0xB5E1A9, 0xB4E0A8, 0xB2DFA6, 0xB1DEA5, 0xB0DEA4, 0xAFDDA2,
                       0xADDCA1, 0xACDBA0, 0xABDA9E, 0xAADA9D, 0xA8D99C, 0xA7D89A, 0xA6D799, 0xA4D698, 0xA3D596, 0xA2D595, 0xA0D494,
                       0x9FD392, 0x9ED291, 0x9DD190, 0x9BD18F, 0x9AD08D, 0x99CF8C, 0x97CE8B, 0x96CD8A, 0x95CD88, 0x93CC87, 0x92CB86,
                       0x91CA85, 0x8FCA83, 0x8EC982, 0x8CC881, 0x8BC780, 0x8AC77E, 0x88C67D, 0x87C57C, 0x85C47B, 0x84C47A, 0x83C379,
                       0x81C277, 0x80C176, 0x7EC175, 0x7DC074, 0x7BBF73, 0x7ABE72, 0x78BE71, 0x77BD6F, 0x75BC6E, 0x74BB6D, 0x72BB6C,
                       0x71BA6B, 0x6FB96A, 0x6EB969, 0x6CB868, 0x6BB767, 0x69B666, 0x67B665, 0x66B564, 0x64B463, 0x62B462, 0x61B361,
                       0x5FB260, 0x5DB25F, 0x5BB15E, 0x5AB05D, 0x58AF5D, 0x56AF5C, 0x54AE5B, 0x52AD5A, 0x50AD59, 0x4EAC59, 0x4CAB58,
                       0x4AAB57, 0x48AA57, 0x46A956, 0x44A855, 0x42A855, 0x3FA754, 0x3DA654, 0x3BA654, 0x39A553, 0x37A453, 0x34A353,
                       0x32A352, 0x30A252, 0x2EA152, 0x2CA052, 0x2AA052, 0x289F51, 0x269E51, 0x249D51, 0x229C51, 0x209C51, 0x1E9B51,
                       0x1C9A51, 0x1B9951, 0x199851, 0x189750, 0x169650, 0x159650, 0x139550, 0x129450, 0x109350, 0x0F9250, 0x0E9150,
                       0x0D904F, 0x0C8F4F, 0x0B8F4F, 0x0A8E4F, 0x098D4F, 0x098C4F, 0x088B4E, 0x088A4E, 0x07894E, 0x07884E, 0x07874D,
                       0x07864D, 0x07864D, 0x07854D, 0x07844D, 0x07834C, 0x07824C, 0x08814C, 0x08804B, 0x087F4B, 0x097E4B, 0x097D4B,
                       0x0A7C4A, 0x0A7C4A, 0x0B7B4A, 0x0B7A49, 0x0C7949, 0x0C7849, 0x0D7748, 0x0D7648, 0x0E7548, 0x0E7447, 0x0F7347,
                       0x0F7347, 0x107246, 0x107146, 0x117045, 0x116F45, 0x126E45, 0x126D44, 0x126C44, 0x136B43, 0x136A43, 0x146A43,
                       0x146942, 0x146842, 0x156741, 0x156641, 0x156540, 0x166440, 0x166340, 0x16623F, 0x17623F, 0x17613E, 0x17603E,
                       0x175F3D, 0x185E3D, 0x185D3C, 0x185C3C, 0x185B3B, 0x185B3B, 0x195A3A, 0x19593A, 0x195839, 0x195739, 0x195638,
                       0x195538, 0x195437, 0x195437, 0x1A5336, 0x1A5235, 0x1A5135, 0x1A5034, 0x1A4F34, 0x1A4E33, 0x1A4D33, 0x1A4D32,
                       0x1A4C32, 0x1A4B31, 0x1A4A30, 0x1A4930, 0x1A482F, 0x1A472F, 0x1A472E, 0x1A462E, 0x1A452D, 0x1A442C, 0x1A432C,
                       0x19422B, 0x19412B, 0x19402A, 0x194029, 0x193F29, 0x193E28, 0x193D27, 0x193C27, 0x183B26, 0x183B26, 0x183A25,
                       0x183924, 0x183824, 0x183723, 0x173622, 0x173522, 0x173521, 0x173420, 0x173320, 0x16321F, 0x16311E, 0x16301E,
                       0x162F1D, 0x152F1C, 0x152E1C, 0x152D1B, 0x142C1A, 0x142B1A, 0x142A19, 0x142918, 0x132918, 0x132817, 0x132716,
                       0x122616, 0x122515, 0x122414>                                                                                  csFPcmoceanAlgae;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanAmp
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xF1EDEC, 0xF1ECEB, 0xF0EBE9, 0xEFE9E8, 0xEFE8E7, 0xEEE7E5, 0xEEE6E4, 0xEDE5E3, 0xEDE3E1, 0xECE2E0, 0xECE1DE,
                       0xEBE0DD, 0xEBDFDC, 0xEADDDA, 0xEADCD9, 0xE9DBD7, 0xE9DAD6, 0xE9D9D4, 0xE8D8D3, 0xE8D6D2, 0xE7D5D0, 0xE7D4CF,
                       0xE6D3CD, 0xE6D2CC, 0xE6D1CA, 0xE5CFC9, 0xE5CEC8, 0xE4CDC6, 0xE4CCC5, 0xE4CBC3, 0xE3C9C2, 0xE3C8C0, 0xE2C7BF,
                       0xE2C6BD, 0xE2C5BC, 0xE1C4BB, 0xE1C3B9, 0xE1C1B8, 0xE0C0B6, 0xE0BFB5, 0xDFBEB3, 0xDFBDB2, 0xDFBCB0, 0xDEBAAF,
                       0xDEB9AE, 0xDEB8AC, 0xDDB7AB, 0xDDB6A9, 0xDDB5A8, 0xDCB4A6, 0xDCB2A5, 0xDCB1A3, 0xDBB0A2, 0xDBAFA1, 0xDBAE9F,
                       0xDAAD9E, 0xDAAC9C, 0xD9AA9B, 0xD9A999, 0xD9A898, 0xD8A796, 0xD8A695, 0xD8A594, 0xD7A492, 0xD7A291, 0xD7A18F,
                       0xD6A08E, 0xD69F8C, 0xD69E8B, 0xD59D89, 0xD59C88, 0xD59A87, 0xD49985, 0xD49884, 0xD49782, 0xD39681, 0xD3957F,
                       0xD3947E, 0xD2927D, 0xD2917B, 0xD2907A, 0xD18F78, 0xD18E77, 0xD18D76, 0xD08C74, 0xD08B73, 0xD08971, 0xCF8870,
                       0xCF876F, 0xCF866D, 0xCE856C, 0xCE846A, 0xCD8369, 0xCD8168, 0xCD8066, 0xCC7F65, 0xCC7E64, 0xCC7D62, 0xCB7C61,
                       0xCB7A60, 0xCB795E, 0xCA785D, 0xCA775B, 0xC9765A, 0xC97559, 0xC97457, 0xC87256, 0xC87155, 0xC87054, 0xC76F52,
                       0xC76E51, 0xC66D50, 0xC66B4E, 0xC66A4D, 0xC5694C, 0xC5684A, 0xC56749, 0xC46548, 0xC46447, 0xC36346, 0xC36244,
                       0xC36143, 0xC25F42, 0xC25E41, 0xC15D3F, 0xC15C3E, 0xC05B3D, 0xC0593C, 0xC0583B, 0xBF573A, 0xBF5639, 0xBE5438,
                       0xBE5336, 0xBD5235, 0xBD5134, 0xBD4F33, 0xBC4E32, 0xBC4D31, 0xBB4C30, 0xBB4A30, 0xBA492F, 0xBA482E, 0xB9462D,
                       0xB9452C, 0xB8442B, 0xB8422B, 0xB7412A, 0xB74029, 0xB63F29, 0xB53D28, 0xB53C27, 0xB43B27, 0xB43926, 0xB33826,
                       0xB23726, 0xB23525, 0xB13425, 0xB03325, 0xB03125, 0xAF3024, 0xAE2F24, 0xAE2D24, 0xAD2C24, 0xAC2B24, 0xAB2A24,
                       0xAA2824, 0xAA2724, 0xA92624, 0xA82524, 0xA72424, 0xA62225, 0xA52125, 0xA42025, 0xA31F25, 0xA21E25, 0xA11D25,
                       0xA01C26, 0x9F1B26, 0x9E1A26, 0x9D1926, 0x9C1827, 0x9B1727, 0x9A1627, 0x991527, 0x981527, 0x971428, 0x951328,
                       0x941328, 0x931228, 0x921128, 0x911129, 0x901029, 0x8E1029, 0x8D1029, 0x8C0F29, 0x8B0F29, 0x890F29, 0x880F29,
                       0x870E29, 0x850E29, 0x840E29, 0x830E29, 0x810E29, 0x800E29, 0x7F0E29, 0x7D0E29, 0x7C0E29, 0x7B0E29, 0x790E29,
                       0x780E28, 0x770E28, 0x750E28, 0x740E28, 0x730E27, 0x710E27, 0x700E27, 0x6F0E26, 0x6D0E26, 0x6C0F26, 0x6B0F25,
                       0x690F25, 0x680F25, 0x670F24, 0x650F24, 0x640E23, 0x630E23, 0x610E22, 0x600E22, 0x5F0E21, 0x5D0E21, 0x5C0E21,
                       0x5B0E20, 0x5A0E1F, 0x580E1F, 0x570E1E, 0x560E1E, 0x540D1D, 0x530D1D, 0x520D1C, 0x510D1C, 0x4F0D1B, 0x4E0D1A,
                       0x4D0C1A, 0x4B0C19, 0x4A0C19, 0x490C18, 0x480B17, 0x460B17, 0x450B16, 0x440B16, 0x430A15, 0x410A14, 0x400A14,
                       0x3F0A13, 0x3D0912, 0x3C0912>                                                                                  csFPcmoceanAmp;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanBalance
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x181C43, 0x191E46, 0x1A1F49, 0x1B214C, 0x1C224F, 0x1D2352, 0x1E2555, 0x1F2658, 0x20275B, 0x21295F, 0x212A62,
                       0x222B65, 0x232D69, 0x242E6C, 0x252F6F, 0x253073, 0x263276, 0x27337A, 0x27347D, 0x283681, 0x283784, 0x293888,
                       0x293A8C, 0x293B8F, 0x293C93, 0x293E97, 0x293F9A, 0x29409E, 0x2942A2, 0x2843A5, 0x2745A9, 0x2647AC, 0x2548B0,
                       0x234AB3, 0x214CB6, 0x1F4EB8, 0x1C50BA, 0x1952BC, 0x1655BD, 0x1357BE, 0x1059BE, 0x0D5BBE, 0x0C5EBE, 0x0A60BE,
                       0x0A62BE, 0x0A64BE, 0x0B66BD, 0x0D68BD, 0x0F6ABD, 0x116CBC, 0x136EBC, 0x1670BC, 0x1972BB, 0x1B74BB, 0x1E76BB,
                       0x2178BB, 0x237ABA, 0x267BBA, 0x297DBA, 0x2B7FBA, 0x2E81BA, 0x3083BA, 0x3384BA, 0x3686BA, 0x3888BA, 0x3B89BA,
                       0x3E8BBA, 0x408DBA, 0x438FBA, 0x4690BA, 0x4892BA, 0x4B94BA, 0x4E95BA, 0x5197BA, 0x5399BA, 0x569ABB, 0x599CBB,
                       0x5C9DBB, 0x5F9FBB, 0x62A0BB, 0x65A2BC, 0x68A4BC, 0x6BA5BC, 0x6EA7BD, 0x71A8BD, 0x75AABE, 0x78ABBE, 0x7BACBF,
                       0x7EAEBF, 0x81AFC0, 0x85B1C0, 0x88B2C1, 0x8BB4C2, 0x8EB5C3, 0x91B7C3, 0x94B8C4, 0x98BAC5, 0x9BBBC6, 0x9EBCC7,
                       0xA1BEC8, 0xA4BFC9, 0xA7C1CA, 0xAAC2CB, 0xADC4CC, 0xB0C5CD, 0xB3C7CE, 0xB6C9CF, 0xB9CAD0, 0xBCCCD2, 0xBFCDD3,
                       0xC1CFD4, 0xC4D0D5, 0xC7D2D7, 0xCAD4D8, 0xCDD5D9, 0xD0D7DA, 0xD3D9DC, 0xD5DADD, 0xD8DCDE, 0xDBDEE0, 0xDEE0E1,
                       0xE1E1E3, 0xE3E3E4, 0xE6E5E6, 0xE9E7E7, 0xEBE9E9, 0xEEEAEA, 0xF1ECEC, 0xF1ECEB, 0xF0EAE9, 0xEFE8E6, 0xEEE5E3,
                       0xEDE3E0, 0xECE0DE, 0xEBDEDB, 0xEADCD8, 0xE9D9D5, 0xE8D7D2, 0xE7D5CF, 0xE6D2CD, 0xE5D0CA, 0xE5CEC7, 0xE4CBC4,
                       0xE3C9C1, 0xE2C7BE, 0xE1C4BB, 0xE1C2B8, 0xE0C0B5, 0xDFBDB2, 0xDFBBB0, 0xDEB9AD, 0xDDB6AA, 0xDCB4A7, 0xDCB2A4,
                       0xDBAFA1, 0xDAAD9E, 0xDAAB9B, 0xD9A998, 0xD8A696, 0xD8A493, 0xD7A290, 0xD69F8D, 0xD69D8A, 0xD59B87, 0xD49984,
                       0xD39681, 0xD3947F, 0xD2927C, 0xD18F79, 0xD18D76, 0xD08B73, 0xCF8970, 0xCF866E, 0xCE846B, 0xCD8268, 0xCD7F65,
                       0xCC7D63, 0xCB7B60, 0xCA795D, 0xCA765B, 0xC97458, 0xC87255, 0xC76F53, 0xC76D50, 0xC66B4D, 0xC5684B, 0xC46648,
                       0xC36346, 0xC36143, 0xC25F41, 0xC15C3F, 0xC05A3C, 0xBF573A, 0xBE5538, 0xBE5236, 0xBD5034, 0xBC4D32, 0xBB4B30,
                       0xBA482E, 0xB9452C, 0xB8432B, 0xB74029, 0xB63D28, 0xB43B27, 0xB33826, 0xB23525, 0xB13325, 0xAF3024, 0xAE2E24,
                       0xAC2B24, 0xAB2924, 0xA92624, 0xA72424, 0xA52125, 0xA31F25, 0xA11D25, 0x9F1B26, 0x9D1926, 0x9B1727, 0x991627,
                       0x971428, 0x941328, 0x921228, 0x901029, 0x8D1029, 0x8B0F29, 0x880F29, 0x860E29, 0x830E29, 0x800E29, 0x7E0E29,
                       0x7B0E29, 0x780E28, 0x760E28, 0x730E27, 0x700E27, 0x6D0E26, 0x6B0F25, 0x680F25, 0x650F24, 0x630E23, 0x600E22,
                       0x5E0E21, 0x5B0E20, 0x580E1F, 0x560E1E, 0x530D1D, 0x510D1C, 0x4E0D1B, 0x4B0C19, 0x490C18, 0x460B17, 0x440B16,
                       0x410A14, 0x3F0A13, 0x3C0912>                                                                                  csFPcmoceanBalance;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanCurl
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x151D44, 0x151F45, 0x162146, 0x162347, 0x172548, 0x172749, 0x18294A, 0x182B4B, 0x182D4C, 0x192F4D, 0x19314F,
                       0x1A3350, 0x1A3551, 0x1A3652, 0x1B3853, 0x1B3A54, 0x1B3C56, 0x1B3E57, 0x1C4058, 0x1C4259, 0x1C435A, 0x1C455B,
                       0x1C475D, 0x1C495E, 0x1C4B5F, 0x1C4C60, 0x1C4E61, 0x1C5062, 0x1C5263, 0x1C5465, 0x1B5666, 0x1B5867, 0x1B5968,
                       0x1A5B69, 0x1A5D6A, 0x1A5F6B, 0x19616C, 0x19636D, 0x18656E, 0x17666F, 0x176870, 0x166A71, 0x156C72, 0x146E73,
                       0x147074, 0x137275, 0x127476, 0x127676, 0x117777, 0x117978, 0x117B79, 0x117D79, 0x117F7A, 0x12817B, 0x13837B,
                       0x14847C, 0x16867C, 0x17887D, 0x1A8A7D, 0x1C8C7E, 0x1F8D7E, 0x228F7E, 0x25917F, 0x29937F, 0x2C947F, 0x309680,
                       0x349880, 0x389981, 0x3B9B81, 0x3F9C81, 0x439E82, 0x479F82, 0x4BA183, 0x50A284, 0x54A484, 0x57A585, 0x5BA686,
                       0x5FA887, 0x63A988, 0x67AB89, 0x6BAC8A, 0x6FAD8B, 0x72AF8C, 0x76B08D, 0x7AB18E, 0x7DB390, 0x81B491, 0x85B593,
                       0x88B794, 0x8BB896, 0x8FBA97, 0x92BB99, 0x96BC9B, 0x99BE9D, 0x9CBF9F, 0xA0C0A0, 0xA3C2A2, 0xA6C3A4, 0xA9C5A6,
                       0xACC6A9, 0xB0C8AB, 0xB3C9AD, 0xB6CBAF, 0xB9CCB2, 0xBCCEB4, 0xBFCFB6, 0xC2D1B9, 0xC5D2BB, 0xC8D4BE, 0xCBD5C0,
                       0xCED7C3, 0xD1D8C5, 0xD3DAC8, 0xD6DCCB, 0xD9DDCD, 0xDCDFD0, 0xDFE1D3, 0xE2E2D6, 0xE4E4D8, 0xE7E6DB, 0xEAE8DE,
                       0xEDEAE1, 0xF0EBE4, 0xF2EDE7, 0xF5EFEA, 0xF8F1ED, 0xFBF3F0, 0xFDF5F3, 0xFEF6F5, 0xFCF4F1, 0xFBF1EE, 0xFAEFEB,
                       0xF9ECE7, 0xF8EAE4, 0xF6E7E1, 0xF5E5DD, 0xF4E2DA, 0xF3E0D6, 0xF2DDD3, 0xF2DBD0, 0xF1D8CC, 0xF0D6C9, 0xEFD3C6,
                       0xEED1C3, 0xEDCFBF, 0xECCCBC, 0xECCAB9, 0xEBC7B6, 0xEAC5B3, 0xE9C2AF, 0xE9C0AC, 0xE8BDA9, 0xE7BBA6, 0xE7B8A3,
                       0xE6B6A0, 0xE5B39D, 0xE5B19A, 0xE4AE98, 0xE3AC95, 0xE3A992, 0xE2A78F, 0xE1A48D, 0xE1A28A, 0xE09F88, 0xE09D85,
                       0xDF9A83, 0xDE9880, 0xDE957E, 0xDD937C, 0xDC907A, 0xDB8E78, 0xDB8B76, 0xDA8974, 0xD98672, 0xD88471, 0xD7816F,
                       0xD67F6E, 0xD67C6C, 0xD57A6B, 0xD4776A, 0xD37569, 0xD27268, 0xD07067, 0xCF6E66, 0xCE6B65, 0xCD6964, 0xCC6764,
                       0xCA6463, 0xC96263, 0xC86062, 0xC65D62, 0xC55B61, 0xC35961, 0xC25761, 0xC05561, 0xBF5360, 0xBD5160, 0xBB4E60,
                       0xBA4C60, 0xB84A60, 0xB64860, 0xB44660, 0xB34460, 0xB14260, 0xAF4160, 0xAD3F60, 0xAB3D60, 0xA93B60, 0xA73960,
                       0xA53760, 0xA33660, 0xA13460, 0x9F3260, 0x9D3060, 0x9B2F60, 0x992D61, 0x972B61, 0x952A61, 0x922861, 0x902760,
                       0x8E2560, 0x8C2460, 0x892260, 0x872160, 0x852060, 0x821F60, 0x801D5F, 0x7D1C5F, 0x7B1B5E, 0x781A5E, 0x76195D,
                       0x73195D, 0x71185C, 0x6E175B, 0x6C175A, 0x691659, 0x661658, 0x641557, 0x611556, 0x5E1455, 0x5C1453, 0x591452,
                       0x571350, 0x54134E, 0x51134D, 0x4F124B, 0x4C1249, 0x491247, 0x471145, 0x441143, 0x421041, 0x3F103F, 0x3D0F3D,
                       0x3A0F3B, 0x380E39, 0x350D36>                                                                                  csFPcmoceanCurl;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanDeep
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xFDFECC, 0xFBFDCB, 0xF9FCCA, 0xF7FBC8, 0xF5FAC7, 0xF3FAC6, 0xF1F9C5, 0xEFF8C4, 0xEDF7C3, 0xEBF7C1, 0xE9F6C0,
                       0xE7F5BF, 0xE5F4BE, 0xE3F4BD, 0xE1F3BC, 0xDFF2BB, 0xDDF2BA, 0xDBF1B9, 0xD9F0B8, 0xD7EFB7, 0xD4EFB6, 0xD2EEB5,
                       0xD0EDB4, 0xCEECB3, 0xCCECB3, 0xCAEBB2, 0xC8EAB1, 0xC6EAB0, 0xC4E9AF, 0xC1E8AF, 0xBFE7AE, 0xBDE7AD, 0xBBE6AC,
                       0xB9E5AC, 0xB7E5AB, 0xB5E4AA, 0xB2E3AA, 0xB0E2A9, 0xAEE2A9, 0xACE1A8, 0xAAE0A8, 0xA7E0A7, 0xA5DFA7, 0xA3DEA6,
                       0xA1DDA6, 0x9FDDA5, 0x9CDCA5, 0x9ADBA5, 0x98DAA4, 0x96DAA4, 0x94D9A4, 0x92D8A4, 0x90D7A4, 0x8DD7A3, 0x8BD6A3,
                       0x89D5A3, 0x87D4A3, 0x85D3A3, 0x83D3A3, 0x81D2A3, 0x7FD1A3, 0x7DD0A3, 0x7CCFA3, 0x7ACEA3, 0x78CEA3, 0x76CDA3,
                       0x75CCA3, 0x73CBA3, 0x71CAA3, 0x70C9A3, 0x6EC8A3, 0x6DC7A3, 0x6BC6A3, 0x6AC5A4, 0x69C4A4, 0x67C3A4, 0x66C2A4,
                       0x65C2A4, 0x64C1A4, 0x63C0A4, 0x62BFA4, 0x61BEA4, 0x60BDA4, 0x5FBCA4, 0x5EBBA4, 0x5DBAA4, 0x5CB9A4, 0x5BB8A4,
                       0x5AB7A4, 0x5AB6A4, 0x59B4A4, 0x58B3A4, 0x58B2A4, 0x57B1A4, 0x56B0A4, 0x56AFA4, 0x55AEA3, 0x55ADA3, 0x54ACA3,
                       0x53ABA3, 0x53AAA3, 0x52A9A3, 0x52A8A3, 0x51A7A3, 0x51A6A2, 0x51A5A2, 0x50A4A2, 0x50A3A2, 0x4FA2A2, 0x4FA1A2,
                       0x4FA0A2, 0x4E9FA1, 0x4E9EA1, 0x4D9DA1, 0x4D9CA1, 0x4D9BA1, 0x4C9AA0, 0x4C99A0, 0x4B98A0, 0x4B97A0, 0x4B96A0,
                       0x4A959F, 0x4A949F, 0x4A939F, 0x49929F, 0x49919E, 0x49909E, 0x488F9E, 0x488E9E, 0x488D9D, 0x478C9D, 0x478B9D,
                       0x478A9D, 0x46899D, 0x46889C, 0x46879C, 0x45869C, 0x45859C, 0x45849B, 0x44839B, 0x44829B, 0x44819B, 0x44809B,
                       0x437F9A, 0x437E9A, 0x437D9A, 0x427C9A, 0x427B99, 0x427A99, 0x427999, 0x417899, 0x417799, 0x417698, 0x407598,
                       0x407498, 0x407398, 0x407298, 0x407197, 0x3F7097, 0x3F6F97, 0x3F6E97, 0x3F6D97, 0x3F6C96, 0x3E6B96, 0x3E6A96,
                       0x3E6996, 0x3E6896, 0x3E6795, 0x3E6695, 0x3E6595, 0x3E6495, 0x3E6394, 0x3E6294, 0x3E6194, 0x3E6094, 0x3E5F93,
                       0x3E5E93, 0x3E5C93, 0x3E5B93, 0x3E5A92, 0x3E5992, 0x3E5892, 0x3E5791, 0x3E5691, 0x3F5590, 0x3F5490, 0x3F538F,
                       0x3F528F, 0x3F508E, 0x404F8D, 0x404E8D, 0x404D8C, 0x404C8B, 0x414B8A, 0x414A89, 0x414988, 0x414887, 0x414785,
                       0x414684, 0x414583, 0x414481, 0x424380, 0x41427E, 0x41417D, 0x41407B, 0x41407A, 0x413F78, 0x413E76, 0x413D75,
                       0x403C73, 0x403C71, 0x403B70, 0x403A6E, 0x3F396C, 0x3F386B, 0x3F3869, 0x3E3767, 0x3E3666, 0x3D3564, 0x3D3562,
                       0x3D3461, 0x3C335F, 0x3C325D, 0x3B325C, 0x3B315A, 0x3A3058, 0x3A3057, 0x392F55, 0x392E54, 0x382D52, 0x382D51,
                       0x372C4F, 0x362B4D, 0x362A4C, 0x352A4A, 0x352949, 0x342847, 0x342846, 0x332744, 0x322643, 0x322541, 0x312540,
                       0x30243E, 0x30233D, 0x2F223B, 0x2F223A, 0x2E2139, 0x2D2037, 0x2D1F36, 0x2C1F34, 0x2B1E33, 0x2B1D32, 0x2A1C30,
                       0x291C2F, 0x281B2D, 0x281A2C>                                                                                  csFPcmoceanDeep;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanDense
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xE6F1F1, 0xE4F0F0, 0xE3EFEF, 0xE1EEEF, 0xDFEDEE, 0xDDEDED, 0xDCECED, 0xDAEBEC, 0xD8EAEC, 0xD7E9EB, 0xD5E9EB,
                       0xD3E8EA, 0xD1E7EA, 0xD0E6E9, 0xCEE5E9, 0xCCE4E8, 0xCBE4E8, 0xC9E3E8, 0xC7E2E7, 0xC6E1E7, 0xC4E0E6, 0xC2DFE6,
                       0xC1DFE6, 0xBFDEE6, 0xBEDDE5, 0xBCDCE5, 0xBADBE5, 0xB9DAE4, 0xB7DAE4, 0xB6D9E4, 0xB4D8E4, 0xB2D7E4, 0xB1D6E3,
                       0xAFD5E3, 0xAED4E3, 0xACD4E3, 0xABD3E3, 0xA9D2E3, 0xA8D1E3, 0xA6D0E3, 0xA5CFE2, 0xA3CEE2, 0xA2CEE2, 0xA0CDE2,
                       0x9FCCE2, 0x9ECBE2, 0x9CCAE2, 0x9BC9E2, 0x9AC8E2, 0x98C7E2, 0x97C6E2, 0x96C5E2, 0x94C5E2, 0x93C4E2, 0x92C3E2,
                       0x90C2E2, 0x8FC1E2, 0x8EC0E2, 0x8DBFE2, 0x8CBEE2, 0x8ABDE3, 0x89BCE3, 0x88BBE3, 0x87BAE3, 0x86B9E3, 0x85B8E3,
                       0x84B7E3, 0x83B6E3, 0x82B5E3, 0x81B4E3, 0x80B3E3, 0x7FB2E3, 0x7FB1E4, 0x7EB0E4, 0x7DAFE4, 0x7CAEE4, 0x7BADE4,
                       0x7BACE4, 0x7AABE4, 0x79AAE4, 0x79A9E4, 0x78A8E4, 0x78A7E4, 0x77A6E4, 0x77A5E4, 0x76A4E5, 0x76A3E5, 0x75A1E5,
                       0x75A0E5, 0x759FE5, 0x759EE5, 0x749DE5, 0x749CE4, 0x749BE4, 0x749AE4, 0x7498E4, 0x7397E4, 0x7396E4, 0x7395E4,
                       0x7394E4, 0x7393E3, 0x7391E3, 0x7390E3, 0x738FE3, 0x738EE2, 0x748DE2, 0x748BE2, 0x748AE2, 0x7489E1, 0x7488E1,
                       0x7487E0, 0x7485E0, 0x7584DF, 0x7583DF, 0x7582DE, 0x7581DE, 0x757FDD, 0x757EDD, 0x767DDC, 0x767CDC, 0x767BDB,
                       0x7679DA, 0x7678DA, 0x7777D9, 0x7776D8, 0x7775D7, 0x7773D7, 0x7772D6, 0x7871D5, 0x7870D4, 0x786FD3, 0x786ED2,
                       0x786CD2, 0x786BD1, 0x786AD0, 0x7969CF, 0x7968CE, 0x7966CD, 0x7965CC, 0x7964CB, 0x7963CA, 0x7962C9, 0x7961C8,
                       0x7960C7, 0x795EC5, 0x795DC4, 0x795CC3, 0x795BC2, 0x795AC1, 0x7959C0, 0x7958BF, 0x7957BD, 0x7956BC, 0x7954BB,
                       0x7953BA, 0x7952B8, 0x7951B7, 0x7950B6, 0x794FB5, 0x784EB3, 0x784DB2, 0x784CB1, 0x784BAF, 0x784AAE, 0x7849AD,
                       0x7748AB, 0x7747AA, 0x7746A9, 0x7745A7, 0x7743A6, 0x7642A5, 0x7641A3, 0x7640A2, 0x763FA0, 0x753E9F, 0x753D9D,
                       0x753C9C, 0x743B9B, 0x743B99, 0x743A98, 0x733996, 0x733895, 0x733793, 0x723692, 0x723590, 0x72348F, 0x71338D,
                       0x71328C, 0x70318A, 0x703088, 0x6F2F87, 0x6F2E85, 0x6E2D84, 0x6E2D82, 0x6D2C81, 0x6D2B7F, 0x6C2A7E, 0x6C297C,
                       0x6B287A, 0x6B2879, 0x6A2777, 0x6A2675, 0x692574, 0x682472, 0x682471, 0x67236F, 0x67226D, 0x66216C, 0x65216A,
                       0x652068, 0x641F67, 0x631F65, 0x621E63, 0x621D62, 0x611D60, 0x601C5E, 0x5F1B5D, 0x5F1B5B, 0x5E1A59, 0x5D1A58,
                       0x5C1956, 0x5B1954, 0x5A1853, 0x5A1851, 0x591750, 0x58174E, 0x57164C, 0x56164B, 0x551649, 0x541548, 0x531546,
                       0x521544, 0x511443, 0x501441, 0x4F1440, 0x4E133E, 0x4D133D, 0x4B133B, 0x4A133A, 0x491238, 0x481237, 0x471236,
                       0x461234, 0x451133, 0x441132, 0x421130, 0x41112F, 0x40102E, 0x3F102D, 0x3E102B, 0x3C102A, 0x3B0F29, 0x3A0F28,
                       0x390F27, 0x380F25, 0x360E24>                                                                                  csFPcmoceanDense;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanHaline
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x2A186C, 0x2A196E, 0x2A1971, 0x2B1973, 0x2B1975, 0x2C1A78, 0x2C1A7A, 0x2D1A7D, 0x2D1A7F, 0x2D1B82, 0x2E1B84,
                       0x2E1B87, 0x2E1C89, 0x2E1C8C, 0x2E1C8E, 0x2E1D91, 0x2E1D93, 0x2E1E95, 0x2E1E98, 0x2E1F9A, 0x2D209C, 0x2D219D,
                       0x2C229F, 0x2B24A0, 0x2A25A1, 0x2927A2, 0x2829A3, 0x262BA3, 0x252DA3, 0x242EA3, 0x2230A3, 0x2132A2, 0x2034A2,
                       0x1E35A1, 0x1D37A1, 0x1C39A0, 0x1B3AA0, 0x193C9F, 0x183D9E, 0x173F9E, 0x16409D, 0x15419C, 0x14439C, 0x13449B,
                       0x12459B, 0x11479A, 0x104899, 0x0F4999, 0x0F4A98, 0x0E4C97, 0x0D4D97, 0x0D4E96, 0x0D4F96, 0x0C5095, 0x0C5195,
                       0x0C5294, 0x0C5394, 0x0C5493, 0x0D5593, 0x0D5692, 0x0D5792, 0x0E5891, 0x0E5991, 0x0F5A91, 0x0F5B90, 0x105C90,
                       0x115D8F, 0x115E8F, 0x125F8F, 0x13608E, 0x14618E, 0x14628E, 0x15638E, 0x16638D, 0x17648D, 0x18658D, 0x18668C,
                       0x19678C, 0x1A688C, 0x1B698C, 0x1C6A8C, 0x1D6B8B, 0x1D6B8B, 0x1E6C8B, 0x1F6D8B, 0x206E8B, 0x216F8B, 0x22708A,
                       0x22718A, 0x23718A, 0x24728A, 0x25738A, 0x26748A, 0x26758A, 0x27768A, 0x287689, 0x297789, 0x297889, 0x2A7989,
                       0x2B7A89, 0x2B7B89, 0x2C7C89, 0x2D7C89, 0x2D7D89, 0x2E7E89, 0x2F7F89, 0x2F8089, 0x308189, 0x318289, 0x318288,
                       0x328388, 0x338488, 0x338588, 0x348688, 0x348788, 0x358888, 0x358988, 0x368988, 0x378A88, 0x378B88, 0x388C88,
                       0x388D88, 0x398E88, 0x398F88, 0x3A9087, 0x3A9087, 0x3B9187, 0x3B9287, 0x3C9387, 0x3C9487, 0x3D9587, 0x3D9687,
                       0x3E9787, 0x3E9886, 0x3F9986, 0x3F9986, 0x409A86, 0x419B86, 0x419C85, 0x429D85, 0x429E85, 0x439F85, 0x43A084,
                       0x44A184, 0x44A284, 0x45A384, 0x46A483, 0x46A483, 0x47A583, 0x48A682, 0x48A782, 0x49A882, 0x4AA981, 0x4AAA81,
                       0x4BAB81, 0x4CAC80, 0x4CAD80, 0x4DAE7F, 0x4EAE7F, 0x4FAF7E, 0x50B07E, 0x51B17D, 0x51B27D, 0x52B37C, 0x53B47C,
                       0x54B57B, 0x55B67B, 0x56B77A, 0x57B879, 0x58B879, 0x5AB978, 0x5BBA77, 0x5CBB77, 0x5DBC76, 0x5EBD75, 0x5FBE75,
                       0x61BF74, 0x62BF73, 0x63C072, 0x65C172, 0x66C271, 0x68C370, 0x69C46F, 0x6BC46E, 0x6CC56E, 0x6EC66D, 0x70C76C,
                       0x71C86B, 0x73C86A, 0x75C969, 0x77CA68, 0x78CB68, 0x7ACB67, 0x7CCC66, 0x7ECD65, 0x80CE64, 0x82CE63, 0x84CF62,
                       0x86D062, 0x89D061, 0x8BD160, 0x8DD25F, 0x8FD25F, 0x92D35E, 0x94D35D, 0x97D45D, 0x99D45D, 0x9BD55C, 0x9ED65C,
                       0xA0D65C, 0xA3D75C, 0xA5D75C, 0xA8D85C, 0xAAD85C, 0xADD85C, 0xAFD95D, 0xB1D95D, 0xB4DA5E, 0xB6DA5F, 0xB8DB60,
                       0xBBDB61, 0xBDDC62, 0xBFDC63, 0xC1DD64, 0xC4DD65, 0xC6DE66, 0xC8DE67, 0xCADF69, 0xCCDF6A, 0xCEE06C, 0xD0E06D,
                       0xD2E16F, 0xD4E170, 0xD6E272, 0xD8E273, 0xDAE375, 0xDCE377, 0xDEE479, 0xE0E57A, 0xE1E57C, 0xE3E67E, 0xE5E680,
                       0xE7E781, 0xE9E783, 0xEBE885, 0xECE987, 0xEEE989, 0xF0EA8A, 0xF2EA8C, 0xF3EB8E, 0xF5EC90, 0xF7EC92, 0xF8ED94,
                       0xFAEE96, 0xFCEE98, 0xFDEF9A>                                                                                  csFPcmoceanHaline;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanIce
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x040613, 0x050614, 0x050715, 0x060817, 0x070918, 0x080A1A, 0x090B1B, 0x0A0C1D, 0x0B0D1E, 0x0C0D1F, 0x0D0E21,
                       0x0E0F22, 0x0F1024, 0x101125, 0x111227, 0x121328, 0x13132A, 0x14142B, 0x15152C, 0x16162E, 0x17172F, 0x171831,
                       0x181832, 0x191934, 0x1A1A35, 0x1B1B37, 0x1C1C38, 0x1D1C3A, 0x1E1D3B, 0x1F1E3D, 0x1F1F3E, 0x201F40, 0x212041,
                       0x222143, 0x232244, 0x242246, 0x252347, 0x252449, 0x26254A, 0x27254C, 0x28264E, 0x29274F, 0x292851, 0x2A2852,
                       0x2B2954, 0x2C2A55, 0x2C2B57, 0x2D2B59, 0x2E2C5A, 0x2F2D5C, 0x2F2E5E, 0x302F5F, 0x312F61, 0x313062, 0x323164,
                       0x333266, 0x333267, 0x343369, 0x35346B, 0x35356C, 0x36356E, 0x363670, 0x373771, 0x383873, 0x383975, 0x393976,
                       0x393A78, 0x3A3B7A, 0x3A3C7B, 0x3A3D7D, 0x3B3E7F, 0x3B3E80, 0x3C3F82, 0x3C4084, 0x3C4185, 0x3D4287, 0x3D4389,
                       0x3D448A, 0x3E458C, 0x3E468D, 0x3E478F, 0x3E4890, 0x3E4992, 0x3E4993, 0x3F4A95, 0x3F4B96, 0x3F4C97, 0x3F4E99,
                       0x3F4F9A, 0x3F509B, 0x3F519D, 0x3F529E, 0x3F539F, 0x3F54A0, 0x3F55A1, 0x3F56A2, 0x3F57A3, 0x3F58A4, 0x3F59A5,
                       0x3E5AA6, 0x3E5CA7, 0x3E5DA8, 0x3E5EA9, 0x3E5FAA, 0x3E60AB, 0x3E61AB, 0x3E62AC, 0x3E63AD, 0x3E65AD, 0x3E66AE,
                       0x3E67AF, 0x3E68AF, 0x3E69B0, 0x3E6AB0, 0x3F6BB1, 0x3F6CB2, 0x3F6EB2, 0x3F6FB3, 0x3F70B3, 0x3F71B4, 0x4072B4,
                       0x4073B4, 0x4074B5, 0x4075B5, 0x4176B6, 0x4178B6, 0x4279B7, 0x427AB7, 0x427BB7, 0x437CB8, 0x437DB8, 0x447EB9,
                       0x447FB9, 0x4580B9, 0x4581BA, 0x4682BA, 0x4684BB, 0x4785BB, 0x4786BB, 0x4887BC, 0x4988BC, 0x4989BC, 0x4A8ABD,
                       0x4B8BBD, 0x4B8CBD, 0x4C8DBE, 0x4D8EBE, 0x4E8FBF, 0x4E90BF, 0x4F91BF, 0x5092C0, 0x5194C0, 0x5195C0, 0x5296C1,
                       0x5397C1, 0x5498C2, 0x5599C2, 0x559AC2, 0x569BC3, 0x579CC3, 0x589DC3, 0x599EC4, 0x5A9FC4, 0x5BA0C5, 0x5CA1C5,
                       0x5DA2C5, 0x5EA3C6, 0x5FA4C6, 0x5FA6C7, 0x60A7C7, 0x61A8C7, 0x62A9C8, 0x63AAC8, 0x64ABC9, 0x65ACC9, 0x67ADC9,
                       0x68AECA, 0x69AFCA, 0x6AB0CB, 0x6BB1CB, 0x6CB2CB, 0x6DB3CC, 0x6EB4CC, 0x6FB5CD, 0x71B6CD, 0x72B8CE, 0x73B9CE,
                       0x74BACE, 0x75BBCF, 0x77BCCF, 0x78BDD0, 0x79BED0, 0x7BBFD0, 0x7CC0D1, 0x7DC1D1, 0x7FC2D2, 0x80C3D2, 0x82C4D3,
                       0x83C5D3, 0x85C6D3, 0x86C7D4, 0x88C8D4, 0x89C9D5, 0x8BCAD5, 0x8CCBD6, 0x8ECCD6, 0x90CDD7, 0x92CED7, 0x93CFD8,
                       0x95D0D8, 0x97D1D9, 0x99D2D9, 0x9AD3DA, 0x9CD4DA, 0x9ED5DB, 0xA0D6DC, 0xA2D6DC, 0xA4D7DD, 0xA6D8DE, 0xA8D9DE,
                       0xA9DADF, 0xABDBE0, 0xADDCE0, 0xAFDDE1, 0xB1DEE2, 0xB3DFE3, 0xB5E0E3, 0xB7E1E4, 0xB9E2E5, 0xBAE3E6, 0xBCE4E7,
                       0xBEE5E7, 0xC0E6E8, 0xC2E6E9, 0xC4E7EA, 0xC6E8EB, 0xC8E9EC, 0xC9EAED, 0xCBEBEE, 0xCDECEF, 0xCFEDEF, 0xD1EEF0,
                       0xD3EFF1, 0xD5F0F2, 0xD6F1F3, 0xD8F2F4, 0xDAF3F5, 0xDCF4F6, 0xDEF5F7, 0xE0F6F8, 0xE1F7F9, 0xE3F9FA, 0xE5FAFB,
                       0xE7FBFB, 0xE8FCFC, 0xEAFDFD>                                                                                  csFPcmoceanIce;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPcmoceanTempo
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xFFF6F4, 0xFDF5F3, 0xFCF4F1, 0xFBF3F0, 0xF9F2EE, 0xF8F1ED, 0xF7F0EB, 0xF5EFEA, 0xF4EEE8, 0xF2EDE7, 0xF1ECE5,
                       0xF0EBE4, 0xEEEAE2, 0xEDEAE1, 0xEBE9DF, 0xEAE8DE, 0xE9E7DD, 0xE7E6DB, 0xE6E5DA, 0xE4E4D8, 0xE3E3D7, 0xE2E2D6,
                       0xE0E2D4, 0xDFE1D3, 0xDDE0D1, 0xDCDFD0, 0xDBDECF, 0xD9DDCD, 0xD8DDCC, 0xD6DCCB, 0xD5DBC9, 0xD3DAC8, 0xD2D9C7,
                       0xD1D8C5, 0xCFD8C4, 0xCED7C3, 0xCCD6C1, 0xCBD5C0, 0xC9D4BF, 0xC8D4BE, 0xC6D3BC, 0xC5D2BB, 0xC3D1BA, 0xC2D1B9,
                       0xC0D0B7, 0xBFCFB6, 0xBDCEB5, 0xBCCEB4, 0xBACDB3, 0xB9CCB2, 0xB7CBB0, 0xB6CBAF, 0xB4CAAE, 0xB3C9AD, 0xB1C8AC,
                       0xB0C8AB, 0xAEC7AA, 0xACC6A9, 0xABC5A8, 0xA9C5A6, 0xA8C4A5, 0xA6C3A4, 0xA4C3A3, 0xA3C2A2, 0xA1C1A1, 0xA0C0A0,
                       0x9EC09F, 0x9CBF9F, 0x9BBE9E, 0x99BE9D, 0x97BD9C, 0x96BC9B, 0x94BC9A, 0x92BB99, 0x91BA98, 0x8FBA97, 0x8DB997,
                       0x8BB896, 0x8AB795, 0x88B794, 0x86B693, 0x85B593, 0x83B592, 0x81B491, 0x7FB390, 0x7DB390, 0x7CB28F, 0x7AB18E,
                       0x78B18E, 0x76B08D, 0x74AF8D, 0x72AF8C, 0x71AE8B, 0x6FAD8B, 0x6DAD8A, 0x6BAC8A, 0x69AB89, 0x67AB89, 0x65AA88,
                       0x63A988, 0x61A987, 0x5FA887, 0x5DA786, 0x5BA686, 0x59A685, 0x57A585, 0x56A485, 0x54A484, 0x52A384, 0x50A284,
                       0x4EA183, 0x4BA183, 0x49A083, 0x479F82, 0x459F82, 0x439E82, 0x419D82, 0x3F9C81, 0x3D9C81, 0x3B9B81, 0x3A9A81,
                       0x389981, 0x369880, 0x349880, 0x329780, 0x309680, 0x2E9580, 0x2C947F, 0x2A937F, 0x29937F, 0x27927F, 0x25917F,
                       0x24907F, 0x228F7E, 0x218E7E, 0x1F8D7E, 0x1E8D7E, 0x1C8C7E, 0x1B8B7D, 0x1A8A7D, 0x19897D, 0x17887D, 0x16877C,
                       0x16867C, 0x15857C, 0x14847C, 0x13847B, 0x13837B, 0x12827B, 0x12817B, 0x11807A, 0x117F7A, 0x117E7A, 0x117D79,
                       0x117C79, 0x117B79, 0x117A78, 0x117978, 0x117878, 0x117777, 0x117677, 0x127676, 0x127576, 0x127476, 0x137375,
                       0x137275, 0x137174, 0x147074, 0x146F73, 0x146E73, 0x156D73, 0x156C72, 0x166B72, 0x166A71, 0x166971, 0x176870,
                       0x176770, 0x17666F, 0x18656F, 0x18656E, 0x18646E, 0x19636D, 0x19626D, 0x19616C, 0x19606C, 0x1A5F6B, 0x1A5E6B,
                       0x1A5D6A, 0x1A5C6A, 0x1A5B69, 0x1B5A68, 0x1B5968, 0x1B5867, 0x1B5867, 0x1B5766, 0x1B5666, 0x1C5565, 0x1C5465,
                       0x1C5364, 0x1C5263, 0x1C5163, 0x1C5062, 0x1C4F62, 0x1C4E61, 0x1C4D61, 0x1C4C60, 0x1C4C5F, 0x1C4B5F, 0x1C4A5E,
                       0x1C495E, 0x1C485D, 0x1C475D, 0x1C465C, 0x1C455B, 0x1C445B, 0x1C435A, 0x1C425A, 0x1C4259, 0x1C4158, 0x1C4058,
                       0x1B3F57, 0x1B3E57, 0x1B3D56, 0x1B3C56, 0x1B3B55, 0x1B3A54, 0x1B3954, 0x1B3853, 0x1A3753, 0x1A3652, 0x1A3651,
                       0x1A3551, 0x1A3450, 0x1A3350, 0x19324F, 0x19314F, 0x19304E, 0x192F4D, 0x192E4D, 0x182D4C, 0x182C4C, 0x182B4B,
                       0x182A4B, 0x18294A, 0x17284A, 0x172749, 0x172648, 0x172548, 0x172447, 0x162347, 0x162246, 0x162146, 0x162045,
                       0x151F45, 0x151E44, 0x151D44>                                                                                  csFPcmoceanTempo;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPmplBrBG
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x563105, 0x5A3305, 0x5E3605, 0x633906, 0x673B06, 0x6C3E07, 0x704007, 0x744307, 0x794608, 0x7B4708, 0x824B09,
                       0x844C09, 0x8A5009, 0x8C510A, 0x93570E, 0x955910, 0x9A5F14, 0x9E6217, 0xA16418, 0xA76A1C, 0xAA6E1F, 0xAF7122,
                       0xB17323, 0xB67927, 0xBA7D2A, 0xBF802D, 0xC08330, 0xC48B39, 0xC6903F, 0xC99546, 0xCA9749, 0xCE9F52, 0xD0A458,
                       0xD3A95F, 0xD5AE65, 0xD8B36B, 0xDAB972, 0xDBBB75, 0xDFC27E, 0xE1C583, 0xE3C889, 0xE4CB8E, 0xE6CE94, 0xE8D199,
                       0xEAD49F, 0xEBD6A2, 0xEDDAAA, 0xEFDDAF, 0xF1E0B5, 0xF3E3BA, 0xF5E6C0, 0xF5E8C4, 0xF5E9C8, 0xF5EACA, 0xF5EBD0,
                       0xF5ECD4, 0xF5EDD8, 0xF5EEDC, 0xF5EFE0, 0xF5F0E4, 0xF5F1E8, 0xF5F2EA, 0xF5F3F0, 0xF5F4F4, 0xF2F4F4, 0xEEF3F2,
                       0xEBF2F1, 0xE7F1F0, 0xE3F0EF, 0xE0F0ED, 0xDCEFEC, 0xD9EEEB, 0xD5EDEA, 0xD1ECE8, 0xCEEBE7, 0xCCEBE6, 0xC6E9E4,
                       0xC1E7E2, 0xBBE5DF, 0xB6E3DC, 0xB0E0D9, 0xABDED6, 0xA5DCD4, 0xA0DAD1, 0x9AD7CE, 0x94D5CB, 0x8FD3C8, 0x89D0C5,
                       0x84CEC3, 0x7ECBC0, 0x78C7BC, 0x75C5BA, 0x6CBFB4, 0x67BAB0, 0x61B6AC, 0x5BB2A8, 0x55AEA4, 0x4FAAA0, 0x49A59C,
                       0x43A198, 0x3D9D94, 0x379990, 0x32958D, 0x2E9189, 0x2A8D85, 0x268981, 0x22857D, 0x20837B, 0x1A7E76, 0x167A72,
                       0x12766E, 0x0E726A, 0x0A6E66, 0x066A62, 0x02665E, 0x00635B, 0x006057, 0x005C54, 0x005950, 0x00564C, 0x005349,
                       0x004F45, 0x004C42, 0x004A40, 0x00453A, 0x004237, 0x003F33, 0x003B2F>                                          csFPmplBrBG;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPmplOcean
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x007E01, 0x007B03, 0x007705, 0x007507, 0x007208, 0x006E0A, 0x006B0C, 0x00690F, 0x006611, 0x006411, 0x006015,
                       0x005E16, 0x005918, 0x00581A, 0x00541C, 0x00521D, 0x004D21, 0x004B23, 0x004923, 0x004426, 0x004228, 0x003F2A,
                       0x003D2B, 0x00382F, 0x003631, 0x003333, 0x003134, 0x002D36, 0x002A38, 0x00263B, 0x00253B, 0x00213F, 0x001D41,
                       0x001A42, 0x001844, 0x001546, 0x001149, 0x001049, 0x000C4D, 0x00084F, 0x000550, 0x000352, 0x000054, 0x000356,
                       0x000559, 0x000759, 0x000C5D, 0x000F5E, 0x001160, 0x001562, 0x001864, 0x001A67, 0x001D69, 0x001F69, 0x00236D,
                       0x00266E, 0x002A70, 0x002D72, 0x002F75, 0x003377, 0x003679, 0x003779, 0x003B7C, 0x003F7E, 0x004280, 0x004482,
                       0x004885, 0x004B87, 0x004D89, 0x00508A, 0x00548C, 0x00568E, 0x005990, 0x005D93, 0x006095, 0x006195, 0x006699,
                       0x00699A, 0x006B9C, 0x006E9E, 0x0072A1, 0x0075A3, 0x0077A5, 0x007BA7, 0x007EA8, 0x0380AA, 0x0883AC, 0x0F87AF,
                       0x1589B1, 0x1A8CB3, 0x2190B5, 0x2391B5, 0x2D95B8, 0x3399BA, 0x389CBC, 0x3F9EBF, 0x44A1C1, 0x4BA5C3, 0x50A8C4,
                       0x56AAC6, 0x5DAEC8, 0x62B1CA, 0x69B3CD, 0x6EB6CF, 0x75BAD1, 0x7BBCD3, 0x80BFD4, 0x83C1D6, 0x8CC6D8, 0x93C8DB,
                       0x99CCDD, 0x9ECFDF, 0xA5D1E1, 0xAAD4E2, 0xB1D8E4, 0xB6DBE6, 0xBCDDE8, 0xC3E1EB, 0xC8E4ED, 0xCFE6EF, 0xD4E9F0,
                       0xDBEDF2, 0xE1EFF4, 0xE4F1F6, 0xEDF6F9, 0xF2F9FB, 0xF9FBFD, 0xFFFFFF>                                          csFPmplOcean;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPmplOranges
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xFEF4EA, 0xFEF3E8, 0xFEF2E6, 0xFEF1E4, 0xFEF0E2, 0xFEEFE0, 0xFEEEDF, 0xFEEDDD, 0xFEEDDB, 0xFEECDA, 0xFEEBD7,
                       0xFEEAD6, 0xFEE9D4, 0xFEE8D3, 0xFEE7D0, 0xFEE6CF, 0xFDE5CC, 0xFDE3C9, 0xFDE3C8, 0xFDE1C4, 0xFDDFC1, 0xFDDEBE,
                       0xFDDDBD, 0xFDDBB9, 0xFDDAB6, 0xFDD8B3, 0xFDD8B2, 0xFDD6AE, 0xFDD4AB, 0xFDD3A8, 0xFDD2A7, 0xFDD0A3, 0xFDCE9F,
                       0xFDCC9C, 0xFDCA98, 0xFDC895, 0xFDC692, 0xFDC590, 0xFDC18B, 0xFDBF87, 0xFDBD84, 0xFDBB80, 0xFDB97D, 0xFDB779,
                       0xFDB576, 0xFDB374, 0xFDB06F, 0xFDAE6C, 0xFDAC68, 0xFDAA66, 0xFDA863, 0xFDA660, 0xFDA45D, 0xFDA35B, 0xFDA057,
                       0xFD9E54, 0xFD9C51, 0xFD994E, 0xFD974B, 0xFD9548, 0xFD9345, 0xFD9244, 0xFD8F3F, 0xFD8D3C, 0xFC8B3A, 0xFB8937,
                       0xFA8634, 0xFA8432, 0xF9822F, 0xF8802D, 0xF77D2A, 0xF77B28, 0xF67925, 0xF57622, 0xF47420, 0xF4731F, 0xF3701B,
                       0xF26D18, 0xF16B16, 0xF16913, 0xEF6712, 0xEE6510, 0xEC630F, 0xEB610E, 0xE95F0D, 0xE85C0C, 0xE65A0B, 0xE5580A,
                       0xE35609, 0xE25407, 0xE05206, 0xDF5106, 0xDD4E04, 0xDC4C03, 0xDA4A02, 0xD94801, 0xD64701, 0xD34501, 0xCF4401,
                       0xCC4301, 0xC94201, 0xC64101, 0xC34001, 0xBF3F01, 0xBC3D02, 0xB93C02, 0xB63B02, 0xB43B02, 0xAF3902, 0xAC3802,
                       0xA93702, 0xA63602, 0xA33503, 0xA13403, 0x9E3303, 0x9C3203, 0x993103, 0x973003, 0x952F03, 0x922E03, 0x902D03,
                       0x8D2C03, 0x8B2B03, 0x8A2B03, 0x862903, 0x832803, 0x812703, 0x7E2603>                                          csFPmplOranges;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPneoDdivVegetationA
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x530000, 0x540000, 0x540000, 0x550000, 0x560000, 0x560000, 0x570000, 0x580000, 0x5A0000, 0x5A0000, 0x5B0000,
                       0x5B0000, 0x5D0000, 0x5E0000, 0x5F0000, 0x600000, 0x610000, 0x610000, 0x620000, 0x630000, 0x640000, 0x650000,
                       0x670000, 0x670000, 0x690000, 0x6A0000, 0x6B0000, 0x6C0000, 0x6D0000, 0x6E0000, 0x700000, 0x710000, 0x720000,
                       0x740000, 0x740000, 0x760000, 0x770000, 0x790000, 0x790000, 0x7B0000, 0x7C0000, 0x7D0000, 0x7F0000, 0x800000,
                       0x830401, 0x830702, 0x860B04, 0x870D05, 0x8A1106, 0x8C1507, 0x8E1908, 0x901D0A, 0x921F0B, 0x93220C, 0x96270D,
                       0x972A0E, 0x992E0F, 0x9C3211, 0x9E3512, 0x9F3913, 0xA13C14, 0xA23F15, 0xA54417, 0xA74818, 0xA94B19, 0xAB501A,
                       0xAD531B, 0xB0571D, 0xB25B1E, 0xB35D1F, 0xB66321, 0xB86722, 0xBB6C24, 0xBD6F25, 0xBF7326, 0xC0762A, 0xC1782D,
                       0xC2792F, 0xC37C33, 0xC57F37, 0xC6813A, 0xC7843E, 0xC88641, 0xC98945, 0xCB8C49, 0xCC8E4C, 0xCC904F, 0xCE9252,
                       0xCF9656, 0xD09859, 0xD19B5D, 0xD29D60, 0xD49F64, 0xD5A368, 0xD6A56B, 0xD7A86F, 0xD9AA73, 0xD9AC75, 0xDBB07A,
                       0xDCB27D, 0xDDB581, 0xDFB885, 0xE0BA88, 0xE1BD8D, 0xE2C090, 0xE3C293, 0xE5C597, 0xE6C79A, 0xE7CA9E, 0xE9CDA3,
                       0xEAD0A6, 0xEBD2A9, 0xECD5AC, 0xEDD7B0, 0xEFDAB4, 0xF0DDB8, 0xF1E1BD, 0xF2E3C0, 0xF3E5C3, 0xF5E8C7, 0xF6EBCB,
                       0xF7EDCE, 0xF8EFD1, 0xFAF4D6, 0xFBF5D9, 0xFCF8DD, 0xFDFBE1, 0xFFFFE5, 0xFEFFE5, 0xFAFDE0, 0xF8FBDD, 0xF6FBDB,
                       0xF4F9D7, 0xF1F8D4, 0xEFF7D1, 0xECF6CD, 0xEAF4CA, 0xE7F3C6, 0xE5F2C3, 0xE2F1BF, 0xE0EFBB, 0xDDEEB9, 0xDAEDB5,
                       0xD8ECB1, 0xD6EAAF, 0xD2E9AB, 0xD0E8A8, 0xCDE7A5, 0xCBE5A1, 0xC8E49F, 0xC6E39B, 0xC3E297, 0xC1E194, 0xBFDF91,
                       0xBCDE8D, 0xBADD8B, 0xB7DB86, 0xB5DA83, 0xB3D981, 0xB0D87D, 0xAED77A, 0xABD576, 0xA9D574, 0xA6D371, 0xA3D26D,
                       0xA1D16A, 0x9ED066, 0x9CCE64, 0x9ACD60, 0x97CC5D, 0x96CB5B, 0x93CA57, 0x90C954, 0x8EC750, 0x8CC74E, 0x89C54A,
                       0x87C448, 0x85C344, 0x83C242, 0x80C03D, 0x7FC03C, 0x7BBE39, 0x77BC37, 0x72B935, 0x6EB733, 0x6BB532, 0x67B331,
                       0x63B02F, 0x5FAE2D, 0x5BAC2C, 0x58AB2B, 0x54A829, 0x51A628, 0x4DA426, 0x4AA325, 0x46A124, 0x429F22, 0x409D20,
                       0x3B9A1E, 0x38991D, 0x34971C, 0x31951A, 0x2D9319, 0x299118, 0x278F17, 0x238D15, 0x1F8B13, 0x1B8913, 0x198711,
                       0x168510, 0x13840F, 0x0F810D, 0x0C800C, 0x0C7E0C, 0x0C7D0C, 0x0B7B0B, 0x0B790B, 0x0B780B, 0x0B770B, 0x0B750B,
                       0x0B750B, 0x0A730A, 0x0A710A, 0x0A700A, 0x0A6E0A, 0x0A6D0A, 0x0A6C0A, 0x0A6B0A, 0x096909, 0x096709, 0x096609,
                       0x096609, 0x096409, 0x096309, 0x086108, 0x086108, 0x085F08, 0x085F08, 0x085D08, 0x085C08, 0x085A08, 0x085A08,
                       0x075907, 0x075807, 0x075607, 0x075507, 0x075507, 0x075407, 0x075207, 0x075107, 0x065106, 0x065006, 0x064F06,
                       0x064E06, 0x064D06, 0x064C06>                                                                                  csFPneoDdivVegetationA;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPneoDivVegetationC
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0x795B13, 0x865614, 0x8A5513, 0x8A5513, 0x875715, 0x875715, 0x895A0A, 0x8C590A, 0x935711, 0x945812, 0x945812,
                       0x955913, 0x965A14, 0x975B15, 0x985C16, 0x985C16, 0x9B5F19, 0x9B5F19, 0x9C601A, 0x9C601A, 0x9D611B, 0x9E621C,
                       0x9F631D, 0x9F631D, 0xAA681A, 0xAA681A, 0xAA681A, 0xAB691B, 0xAC6A1C, 0xAD6B1D, 0xAE6C1E, 0xAE6C1E, 0xB47224,
                       0xB57325, 0xB67426, 0xB87628, 0xBA782A, 0xBB792B, 0xBD7B2D, 0xBD7B2D, 0xBB8231, 0xBB8231, 0xBD8433, 0xBF8635,
                       0xC28737, 0xC38838, 0xC58A3A, 0xC58A3A, 0xC38A3B, 0xC48B3C, 0xC48D3D, 0xC68F3F, 0xC49140, 0xC69342, 0xC59543,
                       0xC69548, 0xC89E52, 0xC99F53, 0xC9A255, 0xCAA356, 0xCDA65B, 0xCFA85D, 0xCFA95E, 0xD0AA5F, 0xD5AF66, 0xD6B067,
                       0xD7B26B, 0xD8B36C, 0xD9B76F, 0xDBB971, 0xDCBA72, 0xDDBB73, 0xDCBE78, 0xDDBF79, 0xDEC07A, 0xE0C27C, 0xE1C47E,
                       0xE3C684, 0xE4C785, 0xE5C789, 0xE6CA89, 0xE7CA8E, 0xE6CC8F, 0xE7CC94, 0xE9CE96, 0xEACF97, 0xEBD098, 0xECD199,
                       0xEAD9A5, 0xEBD9A9, 0xEBDBAA, 0xEDDDAC, 0xEEDDAF, 0xF0DFB1, 0xEFE1B2, 0xF0E1B6, 0xECDFB3, 0xECDEB7, 0xEEE0B9,
                       0xEFE1BA, 0xF0E4BE, 0xF2E6C0, 0xF3E7C1, 0xF4E8C2, 0xF0EAD0, 0xF0EAD4, 0xF1EBD5, 0xF1EBD5, 0xF1EBD5, 0xF2ECD6,
                       0xF1ECD6, 0xF1ECD9, 0xF0EDDA, 0xF1EEDF, 0xF0EEDF, 0xF0EEDF, 0xF1EFE0, 0xF1EFE0, 0xF1EFE0, 0xF1EFE3, 0xF1F1E9,
                       0xF1F0EC, 0xF2F1ED, 0xF2F1ED, 0xF2F3EE, 0xF2F3EE, 0xF2F4F1, 0xF2F4F1, 0xF1F3F2, 0xF1F3F2, 0xEEF2F1, 0xEEF2F1,
                       0xEDF1F2, 0xECF0F1, 0xEBF1F1, 0xEBF1F1, 0xE5EEED, 0xE5EEED, 0xE4EDEC, 0xE4EDEC, 0xE2ECED, 0xE2ECED, 0xE0ECEC,
                       0xE0ECEC, 0xD9E7E7, 0xD9E7E7, 0xD7E7E7, 0xD7E7E7, 0xD4E6E6, 0xD3E5E5, 0xD3E5E5, 0xD3E5E5, 0xC3EEE5, 0xC3EEE5,
                       0xC2EDE4, 0xC0EBE2, 0xBDEBE1, 0xBBE9DF, 0xB7E9DE, 0xB7E9DE, 0xB0E4D8, 0xAFE3D7, 0xADE3D6, 0xABE1D4, 0xA8E0D3,
                       0xA6DED1, 0xA4DED0, 0xA3DDCF, 0x9BDDCF, 0x9ADCCE, 0x97DBCC, 0x94D8C9, 0x92D6C7, 0x8FD3C4, 0x8BD2C2, 0x8AD1C1,
                       0x8BD4C3, 0x8AD3C2, 0x89D2C1, 0x87D0BF, 0x84CEBD, 0x82CCBB, 0x81CBBA, 0x80CAB9, 0x74C7B5, 0x74C7B5, 0x71C6B3,
                       0x6FC4B1, 0x6DC2AF, 0x6BC0AD, 0x68BFAC, 0x67BEAB, 0x60B7A6, 0x5FB6A5, 0x5CB5A3, 0x5BB4A2, 0x57B2A0, 0x55B09E,
                       0x53AE9C, 0x53AE9C, 0x52A9A0, 0x51A89F, 0x4FA69D, 0x4EA59C, 0x4AA49A, 0x48A298, 0x47A197, 0x46A096, 0x3E9A8F,
                       0x3D998E, 0x3B988D, 0x39968B, 0x379489, 0x369388, 0x359287, 0x349186, 0x2C9183, 0x2C9183, 0x2A8F81, 0x298E80,
                       0x278C7E, 0x258A7C, 0x24897B, 0x23887A, 0x1F8476, 0x1F8476, 0x1E8375, 0x1D8274, 0x1C8173, 0x1C8173, 0x1B8072,
                       0x1B8072, 0x197D71, 0x187C70, 0x177B6F, 0x167A6E, 0x14786C, 0x13776B, 0x12766A, 0x117569, 0x0F7367, 0x0F7367,
                       0x0F7367, 0x0E7266, 0x0D7165, 0x0D7165, 0x0C7064, 0x0C7064, 0x066B5B, 0x066B5B, 0x066B59, 0x086958, 0x0B6655,
                       0x0B6655, 0x056951, 0x056951>                                                                                  csFPneoDivVegetationC;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPneoModisNdvi
          @ingroup cs
          @extends csFP_tpl */
      typedef csFP_tpl<0xECE0D7, 0xEBDFD6, 0xEADED4, 0xEADDD3, 0xE9DDD1, 0xE8DCD0, 0xE7DBCE, 0xE7DACD, 0xE6D9CC, 0xE5D8CA, 0xE4D7C9,
                       0xE3D6C7, 0xE3D6C6, 0xE2D5C5, 0xE1D4C3, 0xE0D3C2, 0xE0D2C0, 0xDFD1BF, 0xDED0BD, 0xDDCFBC, 0xDDCFBB, 0xDCCEB9,
                       0xDBCDB8, 0xDACCB6, 0xD9CBB5, 0xD9CAB4, 0xD8C9B2, 0xD7C8B1, 0xD6C8AF, 0xD6C7AE, 0xD5C6AC, 0xD4C5AB, 0xD3C4AA,
                       0xD2C3A8, 0xD1C3A7, 0xD1C2A5, 0xD0C1A4, 0xCFC0A2, 0xCEC0A1, 0xCDBF9F, 0xCCBE9E, 0xCCBD9C, 0xCBBC9B, 0xCABC99,
                       0xC9BB98, 0xC8BA96, 0xC7B995, 0xC7B994, 0xC6B892, 0xC5B791, 0xC4B68F, 0xC3B58E, 0xC2B58C, 0xC1B48B, 0xC1B389,
                       0xC0B288, 0xBFB186, 0xBEB185, 0xBDB083, 0xBCAF82, 0xBCAE80, 0xBBAE7F, 0xBAAD7D, 0xB9AC7C, 0xB8AB7A, 0xB7AB79,
                       0xB6AA77, 0xB5A975, 0xB4A974, 0xB3A872, 0xB2A770, 0xB1A76F, 0xB0A66D, 0xAFA56B, 0xAEA469, 0xADA468, 0xACA366,
                       0xABA264, 0xAAA263, 0xAAA161, 0xA9A05F, 0xA8A05E, 0xA79F5C, 0xA69E5A, 0xA59E59, 0xA49D57, 0xA39C55, 0xA29C54,
                       0xA19B52, 0xA09A50, 0x9F994E, 0x9E994D, 0x9D984B, 0x9C9749, 0x9B9748, 0x9A9646, 0x999545, 0x989544, 0x979442,
                       0x969341, 0x959340, 0x93923F, 0x92913D, 0x91913C, 0x90903B, 0x8F8F3A, 0x8E8E38, 0x8D8E37, 0x8C8D36, 0x8B8C35,
                       0x8A8C33, 0x898B32, 0x878A31, 0x868A30, 0x85892E, 0x84882D, 0x83882C, 0x82872B, 0x818629, 0x808628, 0x7F8527,
                       0x7E8426, 0x7C8324, 0x7B8323, 0x7A8222, 0x798121, 0x78811F, 0x77801E, 0x767F1E, 0x757F1E, 0x747E1E, 0x737D1E,
                       0x727C1E, 0x717C1F, 0x707B1F, 0x6F7A1F, 0x6E791F, 0x6D791F, 0x6C781F, 0x6B771F, 0x6A761F, 0x69761F, 0x68751F,
                       0x677420, 0x667320, 0x657320, 0x647220, 0x637120, 0x627020, 0x617020, 0x606F20, 0x5F6E20, 0x5E6D20, 0x5D6D20,
                       0x5C6C21, 0x5B6B21, 0x5A6A21, 0x596A21, 0x586921, 0x576821, 0x566721, 0x556621, 0x556621, 0x546521, 0x536421,
                       0x526321, 0x516321, 0x516221, 0x506121, 0x4F6021, 0x4E5F21, 0x4D5F21, 0x4C5E21, 0x4C5D21, 0x4B5C21, 0x4A5C21,
                       0x495B21, 0x485A21, 0x485921, 0x475821, 0x465821, 0x455721, 0x445621, 0x445521, 0x435421, 0x425421, 0x415321,
                       0x405221, 0x3F5121, 0x3F5121, 0x3E5021, 0x3D4F21, 0x3C4E20, 0x3B4E1F, 0x3A4D1E, 0x394C1D, 0x384C1C, 0x374B1B,
                       0x364A1A, 0x354A19, 0x344918, 0x334817, 0x324816, 0x314715, 0x304614, 0x2F4613, 0x2E4512, 0x2E4511, 0x2D440F,
                       0x2C430E, 0x2B430D, 0x2A420C, 0x29410B, 0x28410A, 0x274009, 0x263F08, 0x253F07, 0x243E06, 0x233D05, 0x223D04,
                       0x213C03, 0x203B02, 0x1F3B01, 0x1E3A00, 0x1D3900, 0x1D3900, 0x1C3800, 0x1C3700, 0x1B3600, 0x1A3601, 0x1A3501,
                       0x193401, 0x183401, 0x183301, 0x173201, 0x173101, 0x163101, 0x153001, 0x152F01, 0x142F02, 0x132E02, 0x132D02,
                       0x122C02, 0x122C02, 0x112B02, 0x102A02, 0x102902, 0x0F2902, 0x0E2802, 0x0E2702, 0x0D2703, 0x0D2603, 0x0C2503,
                       0x0B2403, 0x0B2403, 0x000000>                                                                                  csFPneoModisNdvi;
      //@}


      //========================================================================================================================================================
      /** @name ColorBrewer2 Color Schemes */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBSpectral
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Spectral" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xFC8D59, 0xFFFFBF, 0x99D594,
                           0xD7191C, 0xFDAE61, 0xABDDA4, 0x2B83BA,
                           0xD7191C, 0xFDAE61, 0xFFFFBF, 0xABDDA4, 0x2B83BA,
                           0xD53E4F, 0xFC8D59, 0xFEE08B, 0xE6F598, 0x99D594, 0x3288BD,
                           0xD53E4F, 0xFC8D59, 0xFEE08B, 0xFFFFBF, 0xE6F598, 0x99D594, 0x3288BD,
                           0xD53E4F, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xE6F598, 0xABDDA4, 0x66C2A5, 0x3288BD,
                           0xD53E4F, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xFFFFBF, 0xE6F598, 0xABDDA4, 0x66C2A5, 0x3288BD,
                           0x9E0142, 0xD53E4F, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xE6F598, 0xABDDA4, 0x66C2A5, 0x3288BD, 0x5E4FA2,
                           0x9E0142, 0xD53E4F, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xFFFFBF, 0xE6F598, 0xABDDA4, 0x66C2A5, 0x3288BD, 0x5E4FA2> csCBSpectral;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBRdYlGn
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "RdYlGn" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xFC8D59, 0xFFFFBF, 0x91CF60,
                           0xD7191C, 0xFDAE61, 0xA6D96A, 0x1A9641,
                           0xD7191C, 0xFDAE61, 0xFFFFBF, 0xA6D96A, 0x1A9641,
                           0xD73027, 0xFC8D59, 0xFEE08B, 0xD9EF8B, 0x91CF60, 0x1A9850,
                           0xD73027, 0xFC8D59, 0xFEE08B, 0xFFFFBF, 0xD9EF8B, 0x91CF60, 0x1A9850,
                           0xD73027, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xD9EF8B, 0xA6D96A, 0x66BD63, 0x1A9850,
                           0xD73027, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xFFFFBF, 0xD9EF8B, 0xA6D96A, 0x66BD63, 0x1A9850,
                           0xA50026, 0xD73027, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xD9EF8B, 0xA6D96A, 0x66BD63, 0x1A9850, 0x006837,
                           0xA50026, 0xD73027, 0xF46D43, 0xFDAE61, 0xFEE08B, 0xFFFFBF, 0xD9EF8B, 0xA6D96A, 0x66BD63, 0x1A9850, 0x006837> csCBRdYlGn;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBRdBu
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "RdBu" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xEF8A62, 0xF7F7F7, 0x67A9CF,
                           0xCA0020, 0xF4A582, 0x92C5DE, 0x0571B0,
                           0xCA0020, 0xF4A582, 0xF7F7F7, 0x92C5DE, 0x0571B0,
                           0xB2182B, 0xEF8A62, 0xFDDBC7, 0xD1E5F0, 0x67A9CF, 0x2166AC,
                           0xB2182B, 0xEF8A62, 0xFDDBC7, 0xF7F7F7, 0xD1E5F0, 0x67A9CF, 0x2166AC,
                           0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xD1E5F0, 0x92C5DE, 0x4393C3, 0x2166AC,
                           0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xF7F7F7, 0xD1E5F0, 0x92C5DE, 0x4393C3, 0x2166AC,
                           0x67001F, 0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xD1E5F0, 0x92C5DE, 0x4393C3, 0x2166AC, 0x053061,
                           0x67001F, 0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xF7F7F7, 0xD1E5F0, 0x92C5DE, 0x4393C3, 0x2166AC, 0x053061> csCBRdBu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPiYG
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "PiYG" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xE9A3C9, 0xF7F7F7, 0xA1D76A,
                           0xD01C8B, 0xF1B6DA, 0xB8E186, 0x4DAC26,
                           0xD01C8B, 0xF1B6DA, 0xF7F7F7, 0xB8E186, 0x4DAC26,
                           0xC51B7D, 0xE9A3C9, 0xFDE0EF, 0xE6F5D0, 0xA1D76A, 0x4D9221,
                           0xC51B7D, 0xE9A3C9, 0xFDE0EF, 0xF7F7F7, 0xE6F5D0, 0xA1D76A, 0x4D9221,
                           0xC51B7D, 0xDE77AE, 0xF1B6DA, 0xFDE0EF, 0xE6F5D0, 0xB8E186, 0x7FBC41, 0x4D9221,
                           0xC51B7D, 0xDE77AE, 0xF1B6DA, 0xFDE0EF, 0xF7F7F7, 0xE6F5D0, 0xB8E186, 0x7FBC41, 0x4D9221,
                           0x8E0152, 0xC51B7D, 0xDE77AE, 0xF1B6DA, 0xFDE0EF, 0xE6F5D0, 0xB8E186, 0x7FBC41, 0x4D9221, 0x276419,
                           0x8E0152, 0xC51B7D, 0xDE77AE, 0xF1B6DA, 0xFDE0EF, 0xF7F7F7, 0xE6F5D0, 0xB8E186, 0x7FBC41, 0x4D9221, 0x276419> csCBPiYG;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPRGn
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "PRGn" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xAF8DC3, 0xF7F7F7, 0x7FBF7B,
                           0x7B3294, 0xC2A5CF, 0xA6DBA0, 0x008837,
                           0x7B3294, 0xC2A5CF, 0xF7F7F7, 0xA6DBA0, 0x008837,
                           0x762A83, 0xAF8DC3, 0xE7D4E8, 0xD9F0D3, 0x7FBF7B, 0x1B7837,
                           0x762A83, 0xAF8DC3, 0xE7D4E8, 0xF7F7F7, 0xD9F0D3, 0x7FBF7B, 0x1B7837,
                           0x762A83, 0x9970AB, 0xC2A5CF, 0xE7D4E8, 0xD9F0D3, 0xA6DBA0, 0x5AAE61, 0x1B7837,
                           0x762A83, 0x9970AB, 0xC2A5CF, 0xE7D4E8, 0xF7F7F7, 0xD9F0D3, 0xA6DBA0, 0x5AAE61, 0x1B7837,
                           0x40004B, 0x762A83, 0x9970AB, 0xC2A5CF, 0xE7D4E8, 0xD9F0D3, 0xA6DBA0, 0x5AAE61, 0x1B7837, 0x00441B,
                           0x40004B, 0x762A83, 0x9970AB, 0xC2A5CF, 0xE7D4E8, 0xF7F7F7, 0xD9F0D3, 0xA6DBA0, 0x5AAE61, 0x1B7837, 0x00441B> csCBPRGn;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBRdYlBu
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "RdYlBu" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xFC8D59, 0xFFFFBF, 0x91BFDB,
                           0xD7191C, 0xFDAE61, 0xABD9E9, 0x2C7BB6,
                           0xD7191C, 0xFDAE61, 0xFFFFBF, 0xABD9E9, 0x2C7BB6,
                           0xD73027, 0xFC8D59, 0xFEE090, 0xE0F3F8, 0x91BFDB, 0x4575B4,
                           0xD73027, 0xFC8D59, 0xFEE090, 0xFFFFBF, 0xE0F3F8, 0x91BFDB, 0x4575B4,
                           0xD73027, 0xF46D43, 0xFDAE61, 0xFEE090, 0xE0F3F8, 0xABD9E9, 0x74ADD1, 0x4575B4,
                           0xD73027, 0xF46D43, 0xFDAE61, 0xFEE090, 0xFFFFBF, 0xE0F3F8, 0xABD9E9, 0x74ADD1, 0x4575B4,
                           0xA50026, 0xD73027, 0xF46D43, 0xFDAE61, 0xFEE090, 0xE0F3F8, 0xABD9E9, 0x74ADD1, 0x4575B4, 0x313695,
                           0xA50026, 0xD73027, 0xF46D43, 0xFDAE61, 0xFEE090, 0xFFFFBF, 0xE0F3F8, 0xABD9E9, 0x74ADD1, 0x4575B4, 0x313695> csCBRdYlBu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBBrBG
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "BrBG" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xD8B365, 0xF5F5F5, 0x5AB4AC,
                           0xA6611A, 0xDFC27D, 0x80CDC1, 0x018571,
                           0xA6611A, 0xDFC27D, 0xF5F5F5, 0x80CDC1, 0x018571,
                           0x8C510A, 0xD8B365, 0xF6E8C3, 0xC7EAE5, 0x5AB4AC, 0x01665E,
                           0x8C510A, 0xD8B365, 0xF6E8C3, 0xF5F5F5, 0xC7EAE5, 0x5AB4AC, 0x01665E,
                           0x8C510A, 0xBF812D, 0xDFC27D, 0xF6E8C3, 0xC7EAE5, 0x80CDC1, 0x35978F, 0x01665E,
                           0x8C510A, 0xBF812D, 0xDFC27D, 0xF6E8C3, 0xF5F5F5, 0xC7EAE5, 0x80CDC1, 0x35978F, 0x01665E,
                           0x543005, 0x8C510A, 0xBF812D, 0xDFC27D, 0xF6E8C3, 0xC7EAE5, 0x80CDC1, 0x35978F, 0x01665E, 0x003C30,
                           0x543005, 0x8C510A, 0xBF812D, 0xDFC27D, 0xF6E8C3, 0xF5F5F5, 0xC7EAE5, 0x80CDC1, 0x35978F, 0x01665E, 0x003C30> csCBBrBG;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBRdGy
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "RdGy" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xEF8A62, 0xFFFFFF, 0x999999,
                           0xCA0020, 0xF4A582, 0xBABABA, 0x404040,
                           0xCA0020, 0xF4A582, 0xFFFFFF, 0xBABABA, 0x404040,
                           0xB2182B, 0xEF8A62, 0xFDDBC7, 0xE0E0E0, 0x999999, 0x4D4D4D,
                           0xB2182B, 0xEF8A62, 0xFDDBC7, 0xFFFFFF, 0xE0E0E0, 0x999999, 0x4D4D4D,
                           0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xE0E0E0, 0xBABABA, 0x878787, 0x4D4D4D,
                           0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xFFFFFF, 0xE0E0E0, 0xBABABA, 0x878787, 0x4D4D4D,
                           0x67001F, 0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xE0E0E0, 0xBABABA, 0x878787, 0x4D4D4D, 0x1A1A1A,
                           0x67001F, 0xB2182B, 0xD6604D, 0xF4A582, 0xFDDBC7, 0xFFFFFF, 0xE0E0E0, 0xBABABA, 0x878787, 0x4D4D4D, 0x1A1A1A> csCBRdGy;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPuOr
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "PuOr" color scheme of 3 to 11 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<11,
                           0xF1A340, 0xF7F7F7, 0x998EC3,
                           0xE66101, 0xFDB863, 0xB2ABD2, 0x5E3C99,
                           0xE66101, 0xFDB863, 0xF7F7F7, 0xB2ABD2, 0x5E3C99,
                           0xB35806, 0xF1A340, 0xFEE0B6, 0xD8DAEB, 0x998EC3, 0x542788,
                           0xB35806, 0xF1A340, 0xFEE0B6, 0xF7F7F7, 0xD8DAEB, 0x998EC3, 0x542788,
                           0xB35806, 0xE08214, 0xFDB863, 0xFEE0B6, 0xD8DAEB, 0xB2ABD2, 0x8073AC, 0x542788,
                           0xB35806, 0xE08214, 0xFDB863, 0xFEE0B6, 0xF7F7F7, 0xD8DAEB, 0xB2ABD2, 0x8073AC, 0x542788,
                           0x7F3B08, 0xB35806, 0xE08214, 0xFDB863, 0xFEE0B6, 0xD8DAEB, 0xB2ABD2, 0x8073AC, 0x542788, 0x2D004B,
                           0x7F3B08, 0xB35806, 0xE08214, 0xFDB863, 0xFEE0B6, 0xF7F7F7, 0xD8DAEB, 0xB2ABD2, 0x8073AC, 0x542788, 0x2D004B> csCBPuOr;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBSet2
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Set2" color scheme of 3 to 8 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<8,
                           0x66C2A5, 0xFC8D62, 0x8DA0CB,
                           0x66C2A5, 0xFC8D62, 0x8DA0CB, 0xE78AC3,
                           0x66C2A5, 0xFC8D62, 0x8DA0CB, 0xE78AC3, 0xA6D854,
                           0x66C2A5, 0xFC8D62, 0x8DA0CB, 0xE78AC3, 0xA6D854, 0xFFD92F,
                           0x66C2A5, 0xFC8D62, 0x8DA0CB, 0xE78AC3, 0xA6D854, 0xFFD92F, 0xE5C494,
                           0x66C2A5, 0xFC8D62, 0x8DA0CB, 0xE78AC3, 0xA6D854, 0xFFD92F, 0xE5C494, 0xB3B3B3> csCBSet2;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBAccent
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Accent" color scheme of 3 to 8 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<8,
                           0x7FC97F, 0xBEAED4, 0xFDC086,
                           0x7FC97F, 0xBEAED4, 0xFDC086, 0xFFFF99,
                           0x7FC97F, 0xBEAED4, 0xFDC086, 0xFFFF99, 0x386CB0,
                           0x7FC97F, 0xBEAED4, 0xFDC086, 0xFFFF99, 0x386CB0, 0xF0027F,
                           0x7FC97F, 0xBEAED4, 0xFDC086, 0xFFFF99, 0x386CB0, 0xF0027F, 0xBF5B17,
                           0x7FC97F, 0xBEAED4, 0xFDC086, 0xFFFF99, 0x386CB0, 0xF0027F, 0xBF5B17, 0x666666> csCBAccent;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBSet1
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Set1" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xE41A1C, 0x377EB8, 0x4DAF4A,
                           0xE41A1C, 0x377EB8, 0x4DAF4A, 0x984EA3,
                           0xE41A1C, 0x377EB8, 0x4DAF4A, 0x984EA3, 0xFF7F00,
                           0xE41A1C, 0x377EB8, 0x4DAF4A, 0x984EA3, 0xFF7F00, 0xFFFF33,
                           0xE41A1C, 0x377EB8, 0x4DAF4A, 0x984EA3, 0xFF7F00, 0xFFFF33, 0xA65628,
                           0xE41A1C, 0x377EB8, 0x4DAF4A, 0x984EA3, 0xFF7F00, 0xFFFF33, 0xA65628, 0xF781BF,
                           0xE41A1C, 0x377EB8, 0x4DAF4A, 0x984EA3, 0xFF7F00, 0xFFFF33, 0xA65628, 0xF781BF, 0x999999> csCBSet1;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBSet3
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Set3" color scheme of 3 to 12 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<12,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3, 0xFDB462,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3, 0xFDB462, 0xB3DE69,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3, 0xFDB462, 0xB3DE69, 0xFCCDE5,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3, 0xFDB462, 0xB3DE69, 0xFCCDE5, 0xD9D9D9,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3, 0xFDB462, 0xB3DE69, 0xFCCDE5, 0xD9D9D9, 0xBC80BD,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3, 0xFDB462, 0xB3DE69, 0xFCCDE5, 0xD9D9D9, 0xBC80BD, 0xCCEBC5,
                           0x8DD3C7, 0xFFFFB3, 0xBEBADA, 0xFB8072, 0x80B1D3, 0xFDB462, 0xB3DE69, 0xFCCDE5, 0xD9D9D9, 0xBC80BD, 0xCCEBC5, 0xFFED6F> csCBSet3;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBDark2
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Dark2" color scheme of 3 to 8 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<8,
                           0x1B9E77, 0xD95F02, 0x7570B3,
                           0x1B9E77, 0xD95F02, 0x7570B3, 0xE7298A,
                           0x1B9E77, 0xD95F02, 0x7570B3, 0xE7298A, 0x66A61E,
                           0x1B9E77, 0xD95F02, 0x7570B3, 0xE7298A, 0x66A61E, 0xE6AB02,
                           0x1B9E77, 0xD95F02, 0x7570B3, 0xE7298A, 0x66A61E, 0xE6AB02, 0xA6761D,
                           0x1B9E77, 0xD95F02, 0x7570B3, 0xE7298A, 0x66A61E, 0xE6AB02, 0xA6761D, 0x666666> csCBDark2;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPaired
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Paired" color scheme of 3 to 12 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<12,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99, 0xE31A1C,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99, 0xE31A1C, 0xFDBF6F,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99, 0xE31A1C, 0xFDBF6F, 0xFF7F00,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99, 0xE31A1C, 0xFDBF6F, 0xFF7F00, 0xCAB2D6,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99, 0xE31A1C, 0xFDBF6F, 0xFF7F00, 0xCAB2D6, 0x6A3D9A,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99, 0xE31A1C, 0xFDBF6F, 0xFF7F00, 0xCAB2D6, 0x6A3D9A, 0xFFFF99,
                           0xA6CEE3, 0x1F78B4, 0xB2DF8A, 0x33A02C, 0xFB9A99, 0xE31A1C, 0xFDBF6F, 0xFF7F00, 0xCAB2D6, 0x6A3D9A, 0xFFFF99, 0xB15928> csCBPaired;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPastel2
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Pastel2" color scheme of 3 to 8 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<8,
                           0xB3E2CD, 0xFDCDAC, 0xCBD5E8,
                           0xB3E2CD, 0xFDCDAC, 0xCBD5E8, 0xF4CAE4,
                           0xB3E2CD, 0xFDCDAC, 0xCBD5E8, 0xF4CAE4, 0xE6F5C9,
                           0xB3E2CD, 0xFDCDAC, 0xCBD5E8, 0xF4CAE4, 0xE6F5C9, 0xFFF2AE,
                           0xB3E2CD, 0xFDCDAC, 0xCBD5E8, 0xF4CAE4, 0xE6F5C9, 0xFFF2AE, 0xF1E2CC,
                           0xB3E2CD, 0xFDCDAC, 0xCBD5E8, 0xF4CAE4, 0xE6F5C9, 0xFFF2AE, 0xF1E2CC, 0xCCCCCC> csCBPastel2;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPastel1
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Pastel1" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xFBB4AE, 0xB3CDE3, 0xCCEBC5,
                           0xFBB4AE, 0xB3CDE3, 0xCCEBC5, 0xDECBE4,
                           0xFBB4AE, 0xB3CDE3, 0xCCEBC5, 0xDECBE4, 0xFED9A6,
                           0xFBB4AE, 0xB3CDE3, 0xCCEBC5, 0xDECBE4, 0xFED9A6, 0xFFFFCC,
                           0xFBB4AE, 0xB3CDE3, 0xCCEBC5, 0xDECBE4, 0xFED9A6, 0xFFFFCC, 0xE5D8BD,
                           0xFBB4AE, 0xB3CDE3, 0xCCEBC5, 0xDECBE4, 0xFED9A6, 0xFFFFCC, 0xE5D8BD, 0xFDDAEC,
                           0xFBB4AE, 0xB3CDE3, 0xCCEBC5, 0xDECBE4, 0xFED9A6, 0xFFFFCC, 0xE5D8BD, 0xFDDAEC, 0xF2F2F2> csCBPastel1;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBOrRd
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "RdYlGn" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xFEE8C8, 0xFDBB84, 0xE34A33,
                           0xFEF0D9, 0xFDCC8A, 0xFC8D59, 0xD7301F,
                           0xFEF0D9, 0xFDCC8A, 0xFC8D59, 0xE34A33, 0xB30000,
                           0xFEF0D9, 0xFDD49E, 0xFDBB84, 0xFC8D59, 0xE34A33, 0xB30000,
                           0xFEF0D9, 0xFDD49E, 0xFDBB84, 0xFC8D59, 0xEF6548, 0xD7301F, 0x990000,
                           0xFFF7EC, 0xFEE8C8, 0xFDD49E, 0xFDBB84, 0xFC8D59, 0xEF6548, 0xD7301F, 0x990000,
                           0xFFF7EC, 0xFEE8C8, 0xFDD49E, 0xFDBB84, 0xFC8D59, 0xEF6548, 0xD7301F, 0xB30000, 0x7F0000> csCBOrRd;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPuBu
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "PuBu" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xECE7F2, 0xA6BDDB, 0x2B8CBE,
                           0xF1EEF6, 0xBDC9E1, 0x74A9CF, 0x0570B0,
                           0xF1EEF6, 0xBDC9E1, 0x74A9CF, 0x2B8CBE, 0x045A8D,
                           0xF1EEF6, 0xD0D1E6, 0xA6BDDB, 0x74A9CF, 0x2B8CBE, 0x045A8D,
                           0xF1EEF6, 0xD0D1E6, 0xA6BDDB, 0x74A9CF, 0x3690C0, 0x0570B0, 0x034E7B,
                           0xFFF7FB, 0xECE7F2, 0xD0D1E6, 0xA6BDDB, 0x74A9CF, 0x3690C0, 0x0570B0, 0x034E7B,
                           0xFFF7FB, 0xECE7F2, 0xD0D1E6, 0xA6BDDB, 0x74A9CF, 0x3690C0, 0x0570B0, 0x045A8D, 0x023858> csCBPuBu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBBuPu
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "CbBuPu" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xE0ECF4, 0x9EBCDA, 0x8856A7,
                           0xEDF8FB, 0xB3CDE3, 0x8C96C6, 0x88419D,
                           0xEDF8FB, 0xB3CDE3, 0x8C96C6, 0x8856A7, 0x810F7C,
                           0xEDF8FB, 0xBFD3E6, 0x9EBCDA, 0x8C96C6, 0x8856A7, 0x810F7C,
                           0xEDF8FB, 0xBFD3E6, 0x9EBCDA, 0x8C96C6, 0x8C6BB1, 0x88419D, 0x6E016B,
                           0xF7FCFD, 0xE0ECF4, 0xBFD3E6, 0x9EBCDA, 0x8C96C6, 0x8C6BB1, 0x88419D, 0x6E016B,
                           0xF7FCFD, 0xE0ECF4, 0xBFD3E6, 0x9EBCDA, 0x8C96C6, 0x8C6BB1, 0x88419D, 0x810F7C, 0x4D004B> csCBBuPu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBOranges
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Oranges" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xFEE6CE, 0xFDAE6B, 0xE6550D,
                           0xFEEDDE, 0xFDBE85, 0xFD8D3C, 0xD94701,
                           0xFEEDDE, 0xFDBE85, 0xFD8D3C, 0xE6550D, 0xA63603,
                           0xFEEDDE, 0xFDD0A2, 0xFDAE6B, 0xFD8D3C, 0xE6550D, 0xA63603,
                           0xFEEDDE, 0xFDD0A2, 0xFDAE6B, 0xFD8D3C, 0xF16913, 0xD94801, 0x8C2D04,
                           0xFFF5EB, 0xFEE6CE, 0xFDD0A2, 0xFDAE6B, 0xFD8D3C, 0xF16913, 0xD94801, 0x8C2D04,
                           0xFFF5EB, 0xFEE6CE, 0xFDD0A2, 0xFDAE6B, 0xFD8D3C, 0xF16913, 0xD94801, 0xA63603, 0x7F2704> csCBOranges;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBBuGn
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "BuGn" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xE5F5F9, 0x99D8C9, 0x2CA25F,
                           0xEDF8FB, 0xB2E2E2, 0x66C2A4, 0x238B45,
                           0xEDF8FB, 0xB2E2E2, 0x66C2A4, 0x2CA25F, 0x006D2C,
                           0xEDF8FB, 0xCCECE6, 0x99D8C9, 0x66C2A4, 0x2CA25F, 0x006D2C,
                           0xEDF8FB, 0xCCECE6, 0x99D8C9, 0x66C2A4, 0x41AE76, 0x238B45, 0x005824,
                           0xF7FCFD, 0xE5F5F9, 0xCCECE6, 0x99D8C9, 0x66C2A4, 0x41AE76, 0x238B45, 0x005824,
                           0xF7FCFD, 0xE5F5F9, 0xCCECE6, 0x99D8C9, 0x66C2A4, 0x41AE76, 0x238B45, 0x006D2C, 0x00441B> csCBBuGn;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBYlOrBr
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "YlOrBr" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xFFF7BC, 0xFEC44F, 0xD95F0E,
                           0xFFFFD4, 0xFED98E, 0xFE9929, 0xCC4C02,
                           0xFFFFD4, 0xFED98E, 0xFE9929, 0xD95F0E, 0x993404,
                           0xFFFFD4, 0xFEE391, 0xFEC44F, 0xFE9929, 0xD95F0E, 0x993404,
                           0xFFFFD4, 0xFEE391, 0xFEC44F, 0xFE9929, 0xEC7014, 0xCC4C02, 0x8C2D04,
                           0xFFFFE5, 0xFFF7BC, 0xFEE391, 0xFEC44F, 0xFE9929, 0xEC7014, 0xCC4C02, 0x8C2D04,
                           0xFFFFE5, 0xFFF7BC, 0xFEE391, 0xFEC44F, 0xFE9929, 0xEC7014, 0xCC4C02, 0x993404, 0x662506> csCBYlOrBr;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBYlGn
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "csCBYlGn" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xF7FCB9, 0xADDD8E, 0x31A354,
                           0xFFFFCC, 0xC2E699, 0x78C679, 0x238443,
                           0xFFFFCC, 0xC2E699, 0x78C679, 0x31A354, 0x006837,
                           0xFFFFCC, 0xD9F0A3, 0xADDD8E, 0x78C679, 0x31A354, 0x006837,
                           0xFFFFCC, 0xD9F0A3, 0xADDD8E, 0x78C679, 0x41AB5D, 0x238443, 0x005A32,
                           0xFFFFE5, 0xF7FCB9, 0xD9F0A3, 0xADDD8E, 0x78C679, 0x41AB5D, 0x238443, 0x005A32,
                           0xFFFFE5, 0xF7FCB9, 0xD9F0A3, 0xADDD8E, 0x78C679, 0x41AB5D, 0x238443, 0x006837, 0x004529> csCBYlGn;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBReds
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Reds" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xFEE0D2, 0xFC9272, 0xDE2D26,
                           0xFEE5D9, 0xFCAE91, 0xFB6A4A, 0xCB181D,
                           0xFEE5D9, 0xFCAE91, 0xFB6A4A, 0xDE2D26, 0xA50F15,
                           0xFEE5D9, 0xFCBBA1, 0xFC9272, 0xFB6A4A, 0xDE2D26, 0xA50F15,
                           0xFEE5D9, 0xFCBBA1, 0xFC9272, 0xFB6A4A, 0xEF3B2C, 0xCB181D, 0x99000D,
                           0xFFF5F0, 0xFEE0D2, 0xFCBBA1, 0xFC9272, 0xFB6A4A, 0xEF3B2C, 0xCB181D, 0x99000D,
                           0xFFF5F0, 0xFEE0D2, 0xFCBBA1, 0xFC9272, 0xFB6A4A, 0xEF3B2C, 0xCB181D, 0xA50F15, 0x67000D> csCBReds;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBRdPu
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "RdPu" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xFDE0DD, 0xFA9FB5, 0xC51B8A,
                           0xFEEBE2, 0xFBB4B9, 0xF768A1, 0xAE017E,
                           0xFEEBE2, 0xFBB4B9, 0xF768A1, 0xC51B8A, 0x7A0177,
                           0xFEEBE2, 0xFCC5C0, 0xFA9FB5, 0xF768A1, 0xC51B8A, 0x7A0177,
                           0xFEEBE2, 0xFCC5C0, 0xFA9FB5, 0xF768A1, 0xDD3497, 0xAE017E, 0x7A0177,
                           0xFFF7F3, 0xFDE0DD, 0xFCC5C0, 0xFA9FB5, 0xF768A1, 0xDD3497, 0xAE017E, 0x7A0177,
                           0xFFF7F3, 0xFDE0DD, 0xFCC5C0, 0xFA9FB5, 0xF768A1, 0xDD3497, 0xAE017E, 0x7A0177, 0x49006A> csCBRdPu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBGreens
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Greens" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xE5F5E0, 0xA1D99B, 0x31A354,
                           0xEDF8E9, 0xBAE4B3, 0x74C476, 0x238B45,
                           0xEDF8E9, 0xBAE4B3, 0x74C476, 0x31A354, 0x006D2C,
                           0xEDF8E9, 0xC7E9C0, 0xA1D99B, 0x74C476, 0x31A354, 0x006D2C,
                           0xEDF8E9, 0xC7E9C0, 0xA1D99B, 0x74C476, 0x41AB5D, 0x238B45, 0x005A32,
                           0xF7FCF5, 0xE5F5E0, 0xC7E9C0, 0xA1D99B, 0x74C476, 0x41AB5D, 0x238B45, 0x005A32,
                           0xF7FCF5, 0xE5F5E0, 0xC7E9C0, 0xA1D99B, 0x74C476, 0x41AB5D, 0x238B45, 0x006D2C, 0x00441B> csCBGreens;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBYlGnBu
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "YlGnBu" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xEDF8B1, 0x7FCDBB, 0x2C7FB8,
                           0xFFFFCC, 0xA1DAB4, 0x41B6C4, 0x225EA8,
                           0xFFFFCC, 0xA1DAB4, 0x41B6C4, 0x2C7FB8, 0x253494,
                           0xFFFFCC, 0xC7E9B4, 0x7FCDBB, 0x41B6C4, 0x2C7FB8, 0x253494,
                           0xFFFFCC, 0xC7E9B4, 0x7FCDBB, 0x41B6C4, 0x1D91C0, 0x225EA8, 0x0C2C84,
                           0xFFFFD9, 0xEDF8B1, 0xC7E9B4, 0x7FCDBB, 0x41B6C4, 0x1D91C0, 0x225EA8, 0x0C2C84,
                           0xFFFFD9, 0xEDF8B1, 0xC7E9B4, 0x7FCDBB, 0x41B6C4, 0x1D91C0, 0x225EA8, 0x253494, 0x081D58> csCBYlGnBu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPurples
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Purples" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xEFEDF5, 0xBCBDDC, 0x756BB1,
                           0xF2F0F7, 0xCBC9E2, 0x9E9AC8, 0x6A51A3,
                           0xF2F0F7, 0xCBC9E2, 0x9E9AC8, 0x756BB1, 0x54278F,
                           0xF2F0F7, 0xDADAEB, 0xBCBDDC, 0x9E9AC8, 0x756BB1, 0x54278F,
                           0xF2F0F7, 0xDADAEB, 0xBCBDDC, 0x9E9AC8, 0x807DBA, 0x6A51A3, 0x4A1486,
                           0xFCFBFD, 0xEFEDF5, 0xDADAEB, 0xBCBDDC, 0x9E9AC8, 0x807DBA, 0x6A51A3, 0x4A1486,
                           0xFCFBFD, 0xEFEDF5, 0xDADAEB, 0xBCBDDC, 0x9E9AC8, 0x807DBA, 0x6A51A3, 0x54278F, 0x3F007D> csCBPurples;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBGnBu
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "GnBu" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xE0F3DB, 0xA8DDB5, 0x43A2CA,
                           0xF0F9E8, 0xBAE4BC, 0x7BCCC4, 0x2B8CBE,
                           0xF0F9E8, 0xBAE4BC, 0x7BCCC4, 0x43A2CA, 0x0868AC,
                           0xF0F9E8, 0xCCEBC5, 0xA8DDB5, 0x7BCCC4, 0x43A2CA, 0x0868AC,
                           0xF0F9E8, 0xCCEBC5, 0xA8DDB5, 0x7BCCC4, 0x4EB3D3, 0x2B8CBE, 0x08589E,
                           0xF7FCF0, 0xE0F3DB, 0xCCEBC5, 0xA8DDB5, 0x7BCCC4, 0x4EB3D3, 0x2B8CBE, 0x08589E,
                           0xF7FCF0, 0xE0F3DB, 0xCCEBC5, 0xA8DDB5, 0x7BCCC4, 0x4EB3D3, 0x2B8CBE, 0x0868AC, 0x084081> csCBGnBu;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBGreys
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Greys" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xF0F0F0, 0xBDBDBD, 0x636363,
                           0xF7F7F7, 0xCCCCCC, 0x969696, 0x525252,
                           0xF7F7F7, 0xCCCCCC, 0x969696, 0x636363, 0x252525,
                           0xF7F7F7, 0xD9D9D9, 0xBDBDBD, 0x969696, 0x636363, 0x252525,
                           0xF7F7F7, 0xD9D9D9, 0xBDBDBD, 0x969696, 0x737373, 0x525252, 0x252525,
                           0xFFFFFF, 0xF0F0F0, 0xD9D9D9, 0xBDBDBD, 0x969696, 0x737373, 0x525252, 0x252525,
                           0xFFFFFF, 0xF0F0F0, 0xD9D9D9, 0xBDBDBD, 0x969696, 0x737373, 0x525252, 0x252525, 0x000000> csCBGreys;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBYlOrRd
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "YlOrRd" color scheme of 3 to 8 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<8,
                           0xFFEDA0, 0xFEB24C, 0xF03B20,
                           0xFFFFB2, 0xFECC5C, 0xFD8D3C, 0xE31A1C,
                           0xFFFFB2, 0xFECC5C, 0xFD8D3C, 0xF03B20, 0xBD0026,
                           0xFFFFB2, 0xFED976, 0xFEB24C, 0xFD8D3C, 0xF03B20, 0xBD0026,
                           0xFFFFB2, 0xFED976, 0xFEB24C, 0xFD8D3C, 0xFC4E2A, 0xE31A1C, 0xB10026,
                           0xFFFFCC, 0xFFEDA0, 0xFED976, 0xFEB24C, 0xFD8D3C, 0xFC4E2A, 0xE31A1C, 0xB10026> csCBYlOrRd;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPuRd
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "PuRd" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xE7E1EF, 0xC994C7, 0xDD1C77,
                           0xF1EEF6, 0xD7B5D8, 0xDF65B0, 0xCE1256,
                           0xF1EEF6, 0xD7B5D8, 0xDF65B0, 0xDD1C77, 0x980043,
                           0xF1EEF6, 0xD4B9DA, 0xC994C7, 0xDF65B0, 0xDD1C77, 0x980043,
                           0xF1EEF6, 0xD4B9DA, 0xC994C7, 0xDF65B0, 0xE7298A, 0xCE1256, 0x91003F,
                           0xF7F4F9, 0xE7E1EF, 0xD4B9DA, 0xC994C7, 0xDF65B0, 0xE7298A, 0xCE1256, 0x91003F,
                           0xF7F4F9, 0xE7E1EF, 0xD4B9DA, 0xC994C7, 0xDF65B0, 0xE7298A, 0xCE1256, 0x980043, 0x67001F> csCBPuRd;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBBlues
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "Blues" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xDEEBF7, 0x9ECAE1, 0x3182BD,
                           0xEFF3FF, 0xBDD7E7, 0x6BAED6, 0x2171B5,
                           0xEFF3FF, 0xBDD7E7, 0x6BAED6, 0x3182BD, 0x08519C,
                           0xEFF3FF, 0xC6DBEF, 0x9ECAE1, 0x6BAED6, 0x3182BD, 0x08519C,
                           0xEFF3FF, 0xC6DBEF, 0x9ECAE1, 0x6BAED6, 0x4292C6, 0x2171B5, 0x084594,
                           0xF7FBFF, 0xDEEBF7, 0xC6DBEF, 0x9ECAE1, 0x6BAED6, 0x4292C6, 0x2171B5, 0x084594,
                           0xF7FBFF, 0xDEEBF7, 0xC6DBEF, 0x9ECAE1, 0x6BAED6, 0x4292C6, 0x2171B5, 0x08519C, 0x08306B> csCBBlues;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCBPuBuGn
          @ingroup cs
          @extends csCB_tpl
          ColorBrewer2 "PuBuGn" color scheme of 3 to 9 colors. Credit: Brewer, Cynthia A., 2022. http://www.ColorBrewer.org2, 2022-07-30. */
      typedef csCB_tpl<9,
                           0xECE2F0, 0xA6BDDB, 0x1C9099,
                           0xF6EFF7, 0xBDC9E1, 0x67A9CF, 0x02818A,
                           0xF6EFF7, 0xBDC9E1, 0x67A9CF, 0x1C9099, 0x016C59,
                           0xF6EFF7, 0xD0D1E6, 0xA6BDDB, 0x67A9CF, 0x1C9099, 0x016C59,
                           0xF6EFF7, 0xD0D1E6, 0xA6BDDB, 0x67A9CF, 0x3690C0, 0x02818A, 0x016450,
                           0xFFF7FB, 0xECE2F0, 0xD0D1E6, 0xA6BDDB, 0x67A9CF, 0x3690C0, 0x02818A, 0x016450,
                           0xFFF7FB, 0xECE2F0, 0xD0D1E6, 0xA6BDDB, 0x67A9CF, 0x3690C0, 0x02818A, 0x016C59, 0x014636> csCBPuBuGn;
      //@}

      /** @endcond  */

      template <class csT, class csAT> colorTpl& csSet(csAT csArg) { return csT::c(*this, csArg); }

  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** i/O stream output operator for colorTpl types. */
  template <class clrChanT, int numChan, int redChanIdx = -1, int blueChanIdx = -1, int greenChanIdx = -1, int alphaChanIdx = -1>
  requires ((numChan>0)                                                                    && // Must have at least 1 chan
            (std::is_unsigned<clrChanT>::value || std::is_floating_point<clrChanT>::value) && // unsigned integral or floating point
            (std::is_floating_point<clrChanT>::value || (sizeof(clrChanT) >= 1))           && // If clrChanT int, then must be >= 1 char size
            (redChanIdx < numChan)                                                         &&
            (blueChanIdx < numChan)                                                        &&
            (greenChanIdx < numChan)                                                       &&
            (alphaChanIdx < numChan)                                                       &&
            (((blueChanIdx <  0) && (redChanIdx <  0) && (greenChanIdx <  0)) ||
             ((blueChanIdx >= 0) && (redChanIdx >= 0) && (greenChanIdx >= 0)))             && // R, G, & B all non-negative or all negative
            ((alphaChanIdx < 0) || (redChanIdx >= 0))                                      && // If A is non-negative, then all non-negative
            ((redChanIdx < 0) || ((redChanIdx   != greenChanIdx) &&
                                  (redChanIdx   != blueChanIdx)  &&
                                  (redChanIdx   != alphaChanIdx) &&
                                  (greenChanIdx != blueChanIdx)  &&
                                  (greenChanIdx != alphaChanIdx) &&
                                  (blueChanIdx  != alphaChanIdx))))                           // Chans can't be teh same if non-negative
  inline std::ostream&
  operator<< (std::ostream &out, colorTpl<clrChanT, numChan> const& color) {
    //  MJR BUG NOTE operator<<: Will fail if 'char' is bigger than uint64_t -- I shudder to imagine a future that might bring such a condition..
    out << "<";
    if (std::is_floating_point<clrChanT>::value || (sizeof(clrChanT) > sizeof(uint64_t))) {
      for(int i=0; i<(numChan-1); i++)
        out << color.getChan(i) << ", ";
      out << color.getChan(numChan-1) << ">";
    } else {
      for(int i=0; i<(numChan-1); i++)
        out << static_cast<uint64_t>(color.getChan(i)) << ", ";
      out << static_cast<uint64_t>(color.getChan(numChan-1)) << ">";
    }
    return out;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** i/O stream output operator for colorTpl types. */
  template <class clrChanT, int numChan, int redChanIdx = -1, int blueChanIdx = -1, int greenChanIdx = -1, int alphaChanIdx = -1>
  requires ((numChan>0)                                                                    && // Must have at least 1 chan
            (std::is_unsigned<clrChanT>::value || std::is_floating_point<clrChanT>::value) && // unsigned integral or floating point
            (std::is_floating_point<clrChanT>::value || (sizeof(clrChanT) >= 1))           && // If clrChanT int, then must be >= 1 char size
            (redChanIdx < numChan)                                                         &&
            (blueChanIdx < numChan)                                                        &&
            (greenChanIdx < numChan)                                                       &&
            (alphaChanIdx < numChan)                                                       &&
            (((blueChanIdx <  0) && (redChanIdx <  0) && (greenChanIdx <  0)) ||
             ((blueChanIdx >= 0) && (redChanIdx >= 0) && (greenChanIdx >= 0)))             && // R, G, & B all non-negative or all negative
            ((alphaChanIdx < 0) || (redChanIdx >= 0))                                      && // If A is non-negative, then all non-negative
            ((redChanIdx < 0) || ((redChanIdx   != greenChanIdx) &&
                                  (redChanIdx   != blueChanIdx)  &&
                                  (redChanIdx   != alphaChanIdx) &&
                                  (greenChanIdx != blueChanIdx)  &&
                                  (greenChanIdx != alphaChanIdx) &&
                                  (blueChanIdx  != alphaChanIdx))))                           // Chans can't be teh same if non-negative
  inline bool
  operator!= (colorTpl<clrChanT, numChan> const& color1, colorTpl<clrChanT, numChan> const& color2) {
    return color1.isNotEqual(color2);
  }

} // end namespace mjr

#define MJR_INCLUDE_colorTpl
#endif

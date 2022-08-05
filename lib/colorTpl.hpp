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
********************************************************************************************************************************************************.H.E.**/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MJR_INCLUDE_colorTpl

#include "ramConfig.hpp"
#include "mjrmath.hpp"

#include <algorithm>                                                     /* STL algorithm           C++11    */
#include <array>                                                         /* array template          C++11    */
#include <climits>                                                       /* std:: C limits.h        C++11    */
#include <cmath>                                                         /* std:: C math.h          C++11    */
#include <cstring>                                                       /* std:: C string.h        C++11    */
#include <ctgmath>                                                       /* C++ math                C++11    */
#include <iomanip>                                                       /* C++ stream formatting   C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <limits>                                                        /* C++ Numeric limits      C++11    */
#include <sstream>                                                       /* C++ string stream       C++      */
#include <string>                                                        /* C++ strings             C++11    */
#include <tuple>                                                         /* STL tuples              C++11    */
#include <type_traits>                                                   /* C++ metaprogramming     C++11    */
#include <vector>                                                        /* STL vector              C++11    */
#include <concepts>                                                      /* Concepts library        C++20    */
#include <utility>                                                       /* STL Misc Utilities      C++11    */
#include <bit>                                                           /* STL bit manipulation    C++20    */
#include <span>

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
    adapt to the size of the color object, and pass by objects to functions by the most efficient means (value or const reference).  The class provides a type
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
    @tparam numChan The number of channels this color will have.  Common choices are 1 for greyscale, 3 for RGB, and 4 for RGBA. */
  template <class clrChanT, int numChan>
  requires (numChan>0) && ((std::is_unsigned<clrChanT>::value && std::is_integral<clrChanT>::value) || std::is_floating_point<clrChanT>::value)
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

    private:

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Private Object Data */
      //@{
      /** Holds the color channel data.
          The union is used to overlay a mask integer leading to dramatic performance improvements for common color types. */
      union {
          maskType theInt;
          clrChanT thePartsA[numChan];
      } theColor;
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Private utility functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Helper function for converting to web safe colors.  This function is highly optimized. */
      inline clrChanT colorComp2WebSafeColorComp(clrChanT aColorComp) {
        clrChanT minCol;
        int minDist;
        uint8_t charCompVal = convertChanToByte(aColorComp);
        // Find the closest component
        uint8_t posValue[6] = { 0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF };
        minDist = charCompVal;
        minCol = 0;
        for(int i=1;i<6;i++)
          if( std::abs(charCompVal - posValue[i]) < minDist ) {
            minDist = std::abs(charCompVal - posValue[i]);
            minCol = posValue[i];
          }
        return(minCol);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Find the element in the discreet value list that is closest to the given component value.
          The intended use is to reduce colors down to a smaller set of values -- ex: convert a color to the nearest web safe value. */
      inline clrChanT colorComp2CloseColorComp(clrChanT aColorComp, clrChanT *discreetVals, int numVals) {
        clrChanT minCol = -1;
        int minDist = maxChanVal;
        // Find the closest of the discreetVals
        for(int i=0;i<numVals;i++)
          if( std::abs(aColorComp - discreetVals[i]) < minDist ) {
            minDist = std::abs(aColorComp - discreetVals[i]);
            minCol = discreetVals[i];
          }
        return(minCol);
      }
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
          return (static_cast<clrChanT>(cVal) << (bitsPerChan-8));
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
      /** Convert a clrChanT to a uint8_t (for integral clrChanT) */
      inline uint8_t convertChanToByte(clrChanT cVal) const requires (std::floating_point<clrChanT>) {
        return static_cast<uint8_t>(cVal * static_cast<clrChanT>(255) / maxChanVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a clrChanT to a uint8_t (for floating point clrChanT) */
      inline uint8_t convertChanToByte(clrChanT cVal) const requires (std::integral<clrChanT>) {
        /* Performance: A good compiler *should* recgonize the case when bitsPerChan-8==0, and render this function an NOOP.  Some don't.  Hence the if-then
           below. */
        if(chanIsByte)
          return cVal;
        else
          return static_cast<uint8_t>(cVal >> (bitsPerChan-8));
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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
        return theColor.theInt; 
#pragma GCC diagnostic pop
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the mask value */
      inline void setMaskNC(maskType aMask) { theColor.theInt = aMask; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the specified color channel value with no index check. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      inline colorTpl& setChanNC(int chan, clrChanT cVal) { theColor.thePartsA[chan] = cVal; return *this; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value with no index check. */
      inline clrChanT getChanNC(int chan) const { 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
        return theColor.thePartsA[chan]; 
#pragma GCC diagnostic pop
      }
      //@}

      public:

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

      /** @name Color Scheme Constants */
      //@{
      constexpr static csIntType chanStepMax   = (chanIsInt ? maxChanVal : std::numeric_limits<uint32_t>::max());  //!< Number of discreet "steps" for channel value
      constexpr static int       minWavelength = 360;                                                              //!< Minimum wavelength for wavelength conversion
      constexpr static int       maxWavelength = 830;                                                              //!< Maximum wavelength for wavelength conversion
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
          channel.  Angles (the H of HSV, HSL, & LAB) are in degrees, and will always be normalized to [0, 360).  */
      enum class colorSpaceEnum { RGB, //!< RGB color space.  Note: R, G, & B are in [0, 1] not [0, 255]
                                  HSL, //!< HSL color space.  Note: S & L are in [0, 1] not [0, 100]
                                  HSV, //!< HSV color space.
                                  LAB, //!< CIE-L*ab color space.
                                  XYZ, //!< XYZ color space.
                                  LCH, //!< CIE-L*ch color space.
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
      /** Copy constructor (heavily used for assignment in the ramCanvas library). */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      colorTpl(const colorType& aColor) {
        /* Saftey: Yep.  Sometimes the compiler might not be able to tell if we have initalized the color object -- some of the color set code is too complex.
           Sometimes we might even want to copy an unitilzied color -- sometimes it makes the code easier to write.*/
        if(goodMask)
          setMaskNC(aColor.getMaskNC());
        else
          std::copy_n(aColor.theColor.thePartsA, numChan, theColor.thePartsA);
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Constructors: Set channels
          These all use setChans internally; however, these constructors will set any unspecified channels to min. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses setChans() to set the first four channels of the color object
          @param c1 The value to set the first channel to
          @param c2 The value to set the second channel to
          @param c3 The value to set the third channel to
          @param c4 The value to set the fourth channel to  */
      colorTpl(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4) {
        if (numChan > 4)
          setChansToMin();
        setChans(c1, c2, c3, c4);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses setChans() to set the first three channels of the color object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the second channel to
          @param c3 The value to set the third channel to */
      colorTpl(clrChanT c1, clrChanT c2, clrChanT c3) {
        if (numChan > 3)
          setChansToMin();
        setChans(c1, c2, c3);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses setChans() to set the first two channels of the color object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the second channel to */
      colorTpl(clrChanT c1, clrChanT c2) {
        if (numChan > 2)
          setChansToMin();
        setChans(c1, c2);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Uses setChans() to set all channels to the given value
          @param cVal The value to set the channels to */
      colorTpl(clrChanT cVal) { setChans(cVal); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Constructors: Corner Colors */
      //@{
      /** Uses the setToCorner() method to set the initialize the object.
       Note that no constructor exists taking a character to provide to setToCorner().  Why?  Because character literals are integers in C++, and they might
       be the same as clrChanT -- rendering ambiguous overload cases.*/
      colorTpl(cornerColorEnum cornerColor) { setToCorner(cornerColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Constructors: Magic String Constructor
          These constructors work hard to interpret the given string, and set the color. */
      //@{
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
      /** @name Component Access */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value with compile time index check.
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline clrChanT getC0() const { return getChanNC(0); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value with compile time index check.
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline clrChanT getC1() const requires (numChan>1) { return getChanNC(1); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value with compile time index check.
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline clrChanT getC2() const requires (numChan>2) { return getChanNC(2); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value with compile time index check.
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline clrChanT getC3() const requires (numChan>3) { return getChanNC(3); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value with run time time index check.
          The channels are 0 indexed.  Returns #minChanVal if \a chan id out of range.
          @return The the value of the indexed channel. */
      inline clrChanT getChan(int chan) const {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          return getChanNC(chan);
        else
          return minChanVal;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Component Access and Conversion to Double Float */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline double getC0_dbl() const { return convertChanToDouble(getC0()); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline double getC1_dbl() const { return convertChanToDouble(getC1()); } /* Requires: Inherits numChan>1 from getC1. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline double getC2_dbl() const { return convertChanToDouble(getC2()); } /* Requires: Inherits numChan>2 from getC2. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline double getC3_dbl() const { return convertChanToDouble(getC3()); } /* Requires: Inherits numChan>3 from getC3. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a double with run time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          Returns 0.0d if \a chan is out of range.
          @param chan The channel index
          @return The the value of the indexed channel. */
      inline double getChan_dbl(int chan) const {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          return convertChanToDouble(getChanNC(chan));
        else
          return 0.0;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Component Access and Conversion to Unsigned 8-Bit Integer */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline uint8_t getC0_byte() const { return convertChanToByte(getC0()); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline uint8_t getC1_byte() const { return convertChanToByte(getC1()); } /* Requires: Inherits numChan>1 from getC1. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline uint8_t getC2_byte() const { return convertChanToByte(getC2()); } /* Requires: Inherits numChan>2 from getC2. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      inline uint8_t getC3_byte() const { return convertChanToByte(getC3()); } /* Requires: Inherits numChan>3 from getC3. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Provides access to an specified color channel value as a uint8_t with run time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          Returns 0.0d if \a chan is out of range.
          @param chan The channel index
          @return The the value of the indexed channel. */
      inline uint8_t getChan_byte(int chan) const {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          return convertChanToByte(getChanNC(chan));
        else
          return 0;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set Channel Value(s) with clrChanT values */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC0(clrChanT cVal) {
        /* Performance: numChan is known at compile time, so the optimizer will produce an assignment or no code at all -- i.e. the test for numChan is done at
           compile time only, and imposes zero overhead at runtime.  */
        /* Performance: The array assignment here gets optimized because the index is known at compile time.  It's just as fast as accessing a member of a union
           for example.  */
        /* Useablity: We could do this with a template, but that means we need ".template set" syntax in some cases.  That's just too uguly. */
        return setChanNC(0, cVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC1(clrChanT cVal) requires (numChan>1) { return setChanNC(1, cVal); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC2(clrChanT cVal) requires (numChan>2) { return setChanNC(2, cVal); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC3(clrChanT cVal) requires (numChan>3) { return setChanNC(3, cVal); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the specified color channel value with run time index check.
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChan(int chan, clrChanT cVal) {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          setChanNC(chan, cVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the given channel of the current object to mjr::colorTpl::maxChanVal.
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @return Returns a reference to the current color object. */
      inline colorTpl& setChanToMax(int chan) {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          setChanNC(chan, maxChanVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the given channel of the current object to #minChanVal.
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @return Returns a reference to the current color object. */
      inline colorTpl& setChanToMin(int chan) {
        if((chan >= 0) && (chan < numChan)) [[likely]]
          setChanNC(chan, minChanVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first four channels current object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the thrid channel to
          @param c3 The value to set the second channel to
          @param c4 The value to set the alpha channel to
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4) {  /* Requires: Inherits numChan>3 from getC3. */
        setC0(c1); setC1(c2); setC2(c3); return setC3(c4); 
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first three channels current object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the thrid channel to
          @param c3 The value to set the second channel to
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(clrChanT c1, clrChanT c2, clrChanT c3) { /* Requires: Inherits numChan>2 from getC2. */
        setC0(c1); setC1(c2); return setC2(c3); 
      }  
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first two channels current object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the thrid channel to
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(clrChanT c1, clrChanT c2) { setC0(c1); return setC1(c2); }  /* Requires: Inherits numChan>1 from getC1. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets all components of the current object from to \a cVal
          @param cVal The value to set each channel to
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(clrChanT cVal) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, cVal);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first four channels current object.
          @param chanValues The values for the components
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> chanValues) { /* Requires: Inherits numChan>3 from getC3. */
        setC0(std::get<0>(chanValues));
        setC1(std::get<1>(chanValues));
        setC2(std::get<2>(chanValues));
        return setC3(std::get<3>(chanValues));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first three channels current object.
          @param chanValues The values for the components
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(std::tuple<clrChanT, clrChanT, clrChanT> chanValues) {   /* Requires: Inherits numChan>2 from getC2. */
        setC0(std::get<0>(chanValues)); 
        setC1(std::get<1>(chanValues)); 
        return setC2(std::get<2>(chanValues)); 
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This function sets color channels from the data in a std::vector.
          @param chanValues A std::vector containing the color channels.  It must have at least #channelCount elements!  This is *not* checked!
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans(std::vector<clrChanT>& chanValues) {
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
      /** @name Set Channel Value(s) with Floating Point Doubles */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the given channel of the current object from a floating point value in the unit interval, [0,1].
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object. */
      inline colorTpl& setChan_dbl(int chan, double cVal) {
        /* Performance: We expect chan to be in range most of the time.  If it is not, we waste time here computing the channel value.. */
        return setChan(chan, convertDoubleToChan(cVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC0_dbl(double cVal) { return setC0(convertDoubleToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the second channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC1_dbl(double cVal) { return setC1(convertDoubleToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the thrid channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC2_dbl(double cVal) { return setC2(convertDoubleToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the fourth channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC3_dbl(double cVal) { return setC3(convertDoubleToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This function sets the first four channels of the current color objects using floats in the unit interval, [0,1].
          @param c1 The value to set the first channel to -- 1 is fully saturated.
          @param c2 The value to set the thrid channel to -- 1 is fully saturated.
          @param c3 The value to set the second channel to -- 1 is fully saturated.
          @param c4 The value to set the alpha channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_dbl(double c1, double c2, double c3, double c4) {
        return setChans(convertDoubleToChan(c1), convertDoubleToChan(c2), convertDoubleToChan(c3), convertDoubleToChan(c4));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This function sets the first three channels of the current color objects using floats in the unit interval, [0,1].
          @param c1 The value to set the first channel to -- 1 is fully saturated.
          @param c2 The value to set the thrid channel to -- 1 is fully saturated.
          @param c3 The value to set the second channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_dbl(double c1, double c2, double c3) {
        return setChans(convertDoubleToChan(c1), convertDoubleToChan(c2), convertDoubleToChan(c3));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This function sets the first two channels of the current color objects using floats in the unit interval, [0,1].
          @param c1 The value to set the first channel to -- 1 is fully saturated.
          @param c2 The value to set the thrid channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_dbl(double c1, double c2) {
        return setChans(convertDoubleToChan(c1), convertDoubleToChan(c2));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets all components of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set each channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_dbl(double cVal) { return setChans(convertDoubleToChan(cVal)); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set Channel Value(s) with 8-Bit, Unsigned Integers */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the given channel of the current object from an uint8_t value in the interval [0,255].
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @param cVal The value to set the channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object. */
      inline colorTpl& setChan_byte(int chan, uint8_t cVal) {
        /* Performance: We expect chan to be in range most of the time.  If it is not, we waste time here computing the channel value.. */
        /* Performance: When chanIsByte, convertByteToChan is a NOOP.  As it's inline, this leads to zero overhead for the chanIsByte case. */
        return setChan(chan, convertByteToChan(cVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the first channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC0_byte(uint8_t cVal) { return setC0(convertByteToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the second channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the thrid channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC1_byte(uint8_t cVal) { return setC1(convertByteToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the thrid channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the second channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC2_byte(uint8_t cVal) { return setC2(convertByteToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the fourth channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the alpha channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setC3_byte(uint8_t cVal) { return setC3(convertByteToChan(cVal));  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first four channels current object. Values are uint8_t the range [0,255].
          @param c1 The value to set the first channel to  -- 255 is fully saturated.
          @param c2 The value to set the thrid channel to  -- 255 is fully saturated.
          @param c3 The value to set the second channel to  -- 255 is fully saturated.
          @param c4 The value to set the alpha channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4) {
        setChans(convertByteToChan(c1), convertByteToChan(c2), convertByteToChan(c3), convertByteToChan(c4));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first three channels current object. Values are uint8_t the range [0,255].
          @param c1 The value to set the first channel to  -- 255 is fully saturated.
          @param c2 The value to set the thrid channel to  -- 255 is fully saturated.
          @param c3 The value to set the second channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3) {
        setChans(convertByteToChan(c1), convertByteToChan(c2), convertByteToChan(c3));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets the first three channels current object. Values are uint8_t the range [0,255].
          @param c1 The value to set the first channel to  -- 255 is fully saturated.
          @param c2 The value to set the thrid channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_byte(uint8_t c1, uint8_t c2) {
        setChans(convertByteToChan(c1), convertByteToChan(c2));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Sets all components of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set each channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setChans_byte(uint8_t cVal) { return setChans(convertByteToChan(cVal)); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Set To Special Colors (RGB Corners)
          While the assumed color model is RGB, these functions are generalized beyond RGB in that non-RGB channels are uniformly, and usefully, manipulated.
          For example, setToBlack and setToWhite functions set all channels to minimum and maximum respectively -- both reasonable definitions for "black" and
          "white" in many situations.  The "primary" colors (red, blue, and green) set all non-RGB channels to minimum, and the "secondary" colors (cyan,
          yellow, and magenta) set all non-RGB channels to max.  This odd difference in behavior on non-RGB channels between primary and secondary colors is
          due to an optimization choice.  This choice allows the setTo*() functions to complete their work using no more than two assignment statements for
          channel objects with integer channels and good masks.  Note that the other functions in this group end with a call to one of the setTo*()
          functions. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set all channels to #minChanVal -- black in RGB
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToBlack()   { setChansToMin(); return *this;  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set all channels to mjr::colorTpl::maxChanVal -- white in RGB
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToWhite()   { setChansToMax(); return *this;  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set channel 1 is set to mjr::colorTpl::maxChanVal, and all others to #minChanVal -- red in RGB
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToRed()     { setChansToMin(); setChanToMax(0); return *this;  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Channel 3 to mjr::colorTpl::maxChanVal, and all others to #minChanVal -- blue in RGB
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToBlue()    { setChansToMin(); setChanToMax(2); return *this;  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color to green. (RGB=010).
          Channel 2 to mjr::colorTpl::maxChanVal, and all others to #minChanVal -- green in RGB
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToGreen()   { setChansToMin(); setChanToMax(1); return *this;  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color to cyan (RGB=011).
          Channel 1 is set to #minChanVal, all others are set to mjr::colorTpl::maxChanVal.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToCyan()    { setChansToMax(); setChanToMin(0); return *this;  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color to yellow (RGB=110).
          Channel 3 is set to #minChanVal, all others are set to mjr::colorTpl::maxChanVal.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToYellow()  { setChansToMax(); setChanToMin(2); return *this;  }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color to magenta (RGB=101).
          Channel 2 is set to #minChanVal, all others are set to mjr::colorTpl::maxChanVal.
          @return Returns a reference to the current color object.*/
      inline colorTpl& setToMagenta() { setChansToMax(); setChanToMin(1); return *this;  }
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
      /** @name Color Setting Methods via Packed Integers
          We use R, G, B, and A in the method names to indicate the first, second, third, and fourth channels respectively of the current color object. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color based upon the bytes of the given integer ordered from LSB to MSB.
           - LSB (lest significant byte) -> Channel1
           - next byte                   -> Channel2
           - next byte                   -> Channel3
           - MSB (most significant byte) -> Channel4
          The extracted bytes are interpreted as by setChans_byte.  Any channels beyond four are left untouched.
          @param anInt The integer from which to extract bytes to set color
          @return Returns a reference to the current color object.*/
      inline colorTpl& setRGBAfromLogPackIntABGR(uint32_t anInt) {
        /* Requires: Inherits numChan>3 from setC3. */
        setC0_byte(0xFF & anInt); anInt = anInt >> 8;
        setC1_byte(0xFF & anInt); anInt = anInt >> 8;
        setC2_byte(0xFF & anInt); anInt = anInt >> 8;
        setC3_byte(0xFF & anInt);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Just like setRGBAfromLogPackIntABGR, but no A */
      inline colorTpl& setRGBfromLogPackIntABGR(uint32_t anInt) {
        /* Requires: Inherits numChan>2 from setC2. */
        setC0_byte(0xFF & anInt); anInt = anInt >> 8;
        setC1_byte(0xFF & anInt); anInt = anInt >> 8;
        setC2_byte(0xFF & anInt); anInt = anInt >> 8;
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color based upon the bytes of the given integer ordered from LSB to MSB.
           - LSB (lest significant byte) -> Channel3
           - next byte                   -> Channel2
           - next byte                   -> Channel1
           - MSB (most significant byte) -> Channel4
           The extracted bytes are interpreted as by setChans_byte.  Any channels beyond four are left untouched.
           @param anInt The integer from which to extract bytes to set color
           @return Returns a reference to the current color object.*/
      inline colorTpl& setRGBAfromLogPackIntARGB(uint32_t anInt) {
        /* Requires: Inherits numChan>3 from setC3. */
        setC2_byte(0xFF & anInt); anInt = anInt >> 8;
        setC1_byte(0xFF & anInt); anInt = anInt >> 8;
        setC0_byte(0xFF & anInt); anInt = anInt >> 8;
        setC3_byte(0xFF & anInt);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Just like setRGBAfromLogPackIntARGB, but no A */
      inline colorTpl & setRGBfromLogPackIntARGB(uint32_t anInt) {
        /* Requires: Inherits numChan>2 from setC2. */
        setC2_byte(0xFF & anInt); anInt = anInt >> 8;
        setC1_byte(0xFF & anInt); anInt = anInt >> 8;
        setC0_byte(0xFF & anInt); anInt = anInt >> 8;
        return *this;
      }
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
      inline colorTpl& setRGBAfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx) {
        /* Requires: Inherits numChan>3 from setC3. */
        uint8_t bytes[4];
        bytes[0] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[1] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[2] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[3] = (0xFF & anInt);
        setC0_byte(bytes[rIdx]);
        setC1_byte(bytes[gIdx]);
        setC2_byte(bytes[bIdx]);
        setC3_byte(bytes[aIdx]);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Just like setRGBAfromLogPackIntGen, but no A */
      inline colorTpl& setRGBfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx) {
        uint8_t bytes[4];
        /* Requires: Inherits numChan>2 from setC2. */
        bytes[0] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[1] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[2] = (0xFF & anInt); anInt = anInt >> 8;
        bytes[3] = (0xFF & anInt);
        setC0_byte(bytes[rIdx]);
        setC1_byte(bytes[gIdx]);
        setC2_byte(bytes[bIdx]);
        return *this;
      }
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
      inline colorTpl& setRGBAfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx) {
        /* Requires: Inherits numChan>3 from setC3. */
        uint8_t *curByte = (uint8_t *)(&anInt);
        setC0_byte(curByte[rIdx]);
        setC1_byte(curByte[gIdx]);
        setC2_byte(curByte[bIdx]);
        setC3_byte(curByte[aIdx]);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Just like setRGBAfromPackIntGen, but no A */
      inline colorTpl& setRGBfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx) {
        /* Requires: Inherits numChan>2 from setC2. */
        uint8_t *curByte = (uint8_t *)(&anInt);
        setC0_byte(curByte[rIdx]);
        setC1_byte(curByte[gIdx]);
        setC2_byte(curByte[bIdx]);
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
          The 'unit' in the name indicates that the values for h, s, and v are the unit interval, [0,1].  This function is based upon the HSV_TO_RGB found in
          Foley and Van Dam.
          @param H The Hue.
          @param S The Saturation.
          @param V The Value
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromUnitHSV(double H, double S, double V) { return setRGBfromColorSpace(colorSpaceEnum::HSV, H*360.0, S, V); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the given HSL values.
          The 'unit' in the name indicates that The ranges for h, s, and v are the the unit interval -- i.e. [0,1].  The algorithm is that presented in
          Computer Graphics by Foley, Van Dam, Feiner, and Hughes -- 2nd edition page 596.  I have corrected a typeo in the text algorithm.
          @param H The Hue.
          @param S The Saturation.
          @param L The Lightness or Luminescence
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromUnitHSL(double H, double S, double L) { return setRGBfromColorSpace(colorSpaceEnum::HSL, H*360.0, L, S); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the color space and values.
          @param space The colorspace
          @param inCh1 Channel one value for given colorspace
          @param inCh2 Channel two value for given colorspace
          @param inCh3 Channel three value for given colorspace
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBfromColorSpace(colorSpaceEnum space, double inCh1, double inCh2, double inCh3) {
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
        setChans(static_cast<clrChanT>(maxChanVal * outR), static_cast<clrChanT>(maxChanVal * outG), static_cast<clrChanT>(maxChanVal * outB));
        return *this;
      }

      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @overload */
      inline colorTpl& setRGBfromColorSpace(colorSpaceEnum space, colorTpl<double, 3> inColor) {
        /* Requires: Inherits numChan>2 from getC2. */
        return setRGBfromColorSpace(space, inColor.getC0(), inColor.getC1(), inColor.getC2());
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name TGA Height Maps for POVray */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes a 24-bit truecolor value intended for use in producing 16-bit greyscale TGA.
          This is the color scheme that should be used for POVray 16-bit height files
          @param tga16val An integer
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBcmpGreyTGA16bit(uint16_t tga16val) {
        /* Requires: Inherits numChan>1 from setC1. */
        tga16val = numberWrap(tga16val, 65536u);
        setChansToMin();
        setC1_byte(static_cast<clrChanT>( tga16val        & 0xff));
        setC0_byte(static_cast<clrChanT>((tga16val >> 8)  & 0xff));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes a 24-bit truecolor value intended for use in producing 24-bit greyscale TGA.
          @param tga24val An integer
          @return Returns a reference to the current color object. */
      inline colorTpl& setRGBcmpGreyTGA24bit(uint32_t tga24val) {
        /* Requires: Inherits numChan>2 from setC2. */
        tga24val = numberWrap(tga24val, 16777216u);
        setC1_byte(tga24val         & 0xff);
        setC0_byte((tga24val >> 8)  & 0xff);
        setC2_byte((tga24val >> 16) & 0xff);
        return *this;
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
        setChans_dbl(rf, gf, bf);
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the color indicated by the given wavelength.
          This function uses an algorithm based upon linear approximations to the color match functions.  I believe the original algorithm is due to Dan
          Bruton, and his FORTRAN version is available (at least as of 1997) at http://www.physics.sfasu.edu/astro/color.html
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

        return setChans_dbl(edgeIntensityAdj*rf, edgeIntensityAdj*gf, edgeIntensityAdj*bf);
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
          @param aDouble The value to convert
          @param anchors Doubles for which color equals the corresponding corner.
          @param colors  A vector  of colors to use
          @return A reference to this object */
      inline colorTpl& cmpGradiant(double aDouble, std::vector<double> const& anchors, std::vector<colorType> const& colors) {
        typename std::vector<colorType>::size_type numColors = colors.size();
        if((numColors >= 2) && (anchors.size() == numColors)) {
          for(typename std::vector<colorType>::size_type i=0; i<(numColors-1); i++) {
            double lowAnchor  = anchors[i];
            double highAnchor = anchors[i+1];
            if( (aDouble >= lowAnchor) && (aDouble < highAnchor) ) {
              return interplColors(std::abs((aDouble-lowAnchor)/(highAnchor-lowAnchor)), colors[i], colors[i+1]);
            }
          }
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Identical to the other cmpGradiant() function except that equidistant anchors are automatically generated on [0, 1] for the given colors array. */
      inline colorTpl& cmpGradiant(double aDouble, std::vector<colorType> const& colors) {
        typename std::vector<colorType>::size_type numColors = colors.size();
        if(numColors >= 2) {
          for(typename std::vector<colorType>::size_type i=0; i<(numColors-1); i++) {
            double lowAnchor  = static_cast<double>(i)  / (numColors-1);
            double highAnchor = static_cast<double>(i+1)/ (numColors-1);
            if( (aDouble >= lowAnchor) && (aDouble < highAnchor) ) {
              return interplColors(std::abs((aDouble-lowAnchor)/(highAnchor-lowAnchor)), colors[i], colors[i+1]);
            }
          }
        }
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This is simply a version of cmpRGBcornerGradiant() that computes the length of the final argument as a C-string.
          Unlike the version of cmpRGBcornerGradiant() specifying numColors, this one requires the final argument to be a real C-string -- i.e. it must have a
          terminating NULL.  Note this function uses RGB corner colors as anchors, and is thus designed to work with RGB colors.  This function is the primary
          workhorse behind many of the "cmp" color schemes in this library.
          @param csIdx The value to convert
          @param cornerColors Characters specifying color (as used by setColor)
          @return A reference to this object */
      inline colorTpl& cmpRGBcornerGradiant(csIntType csIdx, const char *cornerColors) {
        return cmpRGBcornerGradiant(csIdx, static_cast<csIntType>(std::strlen(cornerColors)), cornerColors);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Color value based upon a color ramp passing through the given sequence of corner colors at equal intervals along [0, (mjr::colorTpl::chanStepMax * (numColors - 1)
          + 1)].  At 0, the color will be the first specified color.  At (mjr::colorTpl::chanStepMax * ( numColors - 1) + 1) it will be the last color specified color.  This
          function is similar to the one taking doubles. This version doesn't allow for the specification of anchor points, but uses precise integer
          arithmetic.  With this function it is possible to precisely duplicate many of the integer ramp color scheme functions.  This function supports input
          conditioning.  cornerColors need not be a real C-string -- i.e. no need for an terminating NULL.  Note this function uses RGB corner colors as
          anchors, and is thus designed to work with RGB colors.  This function is the primary workhorse behind many of the "cmp" color schemes in this
          library.
          @param csIdx The value to convert
          @param numColors The number of colors
          @param cornerColors An array of things that can be passed to setToCorner() -- usually char or cornerColorEnum
          @return A reference to this object */
      template <typename ccT> 
      inline colorTpl& cmpRGBcornerGradiant(csIntType csIdx, csIntType numColors, const ccT* cornerColors) {
        /* Requires: Inherits numChan>2 from getC2. */
        csIdx = numberWrap(csIdx, static_cast<csIntType>(chanStepMax * numColors - chanStepMax));
        if(csIdx != 0) { [[likely]]
          for(csIntType i=0; i<(numColors-1); i++) {
            if(csIdx <= chanStepMax) {
              clrChanT csIdxNoMore = static_cast<clrChanT>(csIdx);
              // Note: This could be MUCH better optimized!
              colorTpl<clrChanT, numChan> c1;
              colorTpl<clrChanT, numChan> c2;
              c1.setToCorner(cornerColors[i]);
              c2.setToCorner(cornerColors[i+1]);
              clrChanT r, g, b;
              if(c1.getC0() > c2.getC0()) {
                r = chanStepMax - csIdxNoMore;
              } else if(c1.getC0() < c2.getC0()) {
                r = csIdxNoMore;
              } else {
                r = c1.getC0();
              }
              if(c1.getC1() > c2.getC1()) {
                g = chanStepMax - csIdxNoMore;
              } else if(c1.getC1() < c2.getC1()) {
                g = csIdxNoMore;
              } else {
                g = c1.getC1();
              }
              if(c1.getC2() > c2.getC2()) {
                b = chanStepMax - csIdxNoMore;
              } else if(c1.getC2() < c2.getC2()) {
                b = csIdxNoMore;
              } else {
                b = c1.getC2();
              }
              return setChans(r, g, b);
            } else {
              csIdx = csIdx - chanStepMax;
            }
          }
        } else {
          return setToCorner(cornerColors[0]);
        }
        // If we got here, we had a problem.  But not much we can do about it...
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the current color to a value linearly interpolated between the two given colors.  When \a aDouble is 0, the color is col1.
          When \a aDouble is 1 the new value is col2.  This method interpolates all channels without any color space conversions and as few type conversions as
          possible.
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      inline colorTpl& interplColors(double aDouble, colorArgType col1, colorArgType col2) {
        if( (aDouble >= 0.0) && (aDouble <= 1.0) )
          for(int i=0; i<numChan; i++)
            setChanNC(i, static_cast<clrChanT>(mjr::interpolateLinear(static_cast<double>(col1.getChanNC(i)), static_cast<double>(col2.getChanNC(i)), aDouble)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the current color to a value linearly interpolated between the two given colors.
          When \a aDouble is 0, the color is col1.  When \a aDouble is 1 the new value is col2.  The interpolation is done in HSL space -- i.e. the given colors are
          converted to HSL, the interpolation is done, and the result is converted back to RGB and the current color is set.  Unlike interplColors, this
          function will NOT interpolate every channel.  Rather, as this function deals specifically with RGB and HSL space, only the RGB channels will be
          interpolated.
          @param space The color space to use
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      inline colorTpl& interplColorSpace(colorSpaceEnum space, double aDouble, colorArgType col1, colorArgType col2) {
        /* Requires: Inherits numChan>2 from getC2. */
        if( (aDouble >= 0.0) && (aDouble <= 1.0) ) {
          // Convert our given colors into HSL
          colorTpl<double, 3> acol1 = col1.rgb2colorSpace(space);
          colorTpl<double, 3> acol2 = col2.rgb2colorSpace(space);

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
          In order to keep the result in range, w1,w2 must be in [0,1] and w1+w2=1. See uMean().
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
          In order to keep the result in range, w1,w2 must be in [0,1] and w1+w2=1.  This constraint is *not* checked -- see uMean for an alterantive!
          @param w1   The first weight in the range [0, 1)
          @param w2   The second weight in the range [0, 1)
          @param w3   The third weight in the range [0, 1)
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
          No check is made for division by zero.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDiv(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
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
      inline colorTpl& tfrmMultClp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clipTop(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(aCol.getChanNC(i))));
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
      inline colorTpl& ScaleSignDiff(colorArgType aCol) {
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
      inline colorTpl& tfrmDiffClp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clipBot(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the negative of the arithmetic difference of the given color from the current one.
          This is the same as the arithmetic difference of the current color from the given color.  If the result a differences is negative, then that
          component will be set to zero.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmNegDiffClp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clipBot(static_cast<channelArithDType>(aCol.getChanNC(i)) - static_cast<channelArithDType>(getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic sum of the given color from the current one.
          If the result of a sum is greater than the maximum value, then that component will be set to the maximum value.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmAddClp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clipTop(static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the arithmetic sum of the given color from the current one, then divids by dcolor.
          If the result of a sum is greater than the maximum value, then that component will be set to the maximum value.
          No check is made for division by zero.
          @param aCol The color to use for initial add.
          @param dCol The color to use for final division.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmAddDivClp(colorArgType aCol, colorArgType dCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clipTop((static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))) /
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
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmMod(colorArgType aCol) requires (std::integral<clrChanT>) {
        for(int i=0; i<numChan; i++)
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
          Floating point Numbers re used for intermediate values and the result cast to a colorChanType at the end.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmLn() {
        /* Performance: Even if the compiler fails to unroll this loop, the runtime is dominated by the double computations. */
        for(int i=0; i<numChan; i++)
          setChanNC(i, std::log(1.0 + static_cast<double>(getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Linearly interpolate between the current color and the given color (at a point scaled the unit interval).
          If \a aDouble is 0, then the current color will not change.  If \a aDouble is 1, then the current color will be tooCol.
          @param aDouble Distance from the current color (on a unit interval)
          @param tooCol  The color we are interpolating with.
          @return Returns a reference to the current color object.*/
      inline colorTpl & interplColors(double aDouble, colorArgType tooCol) {
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
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmShiftL(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        for(int i=0; i<numChan; i++)
          /* tricky: We are casting the color component being shifted bitwise to a big int; however, we are casting the shifting quantity via a static_cast. */
          setChanNC(i, std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) << static_cast<uint64_t>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Shift Right Transform modifies the current color.
          @param aCol How many bits to shift.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmShiftR(colorArgType aCol) requires (std::integral<clrChanT>) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, getChanNC(i) >> aCol.getChanNC(i));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Template specialization member function differing from the above function only in supported template conditions. */
      inline colorTpl& tfrmShiftR(colorArgType aCol) requires (std::floating_point<clrChanT>) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) >> static_cast<uint64_t>(aCol.getChanNC(i))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Saw Transform modifies the current color: R=R iff(ra<=R<=rb), G=G iff(ga<=G<=gb), B=B iff(ba<=B<=bb).
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmSaw(colorArgType lowCol, colorArgType highCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, ((lowCol.getChanNC(i) <= getChanNC(i)) && (highCol.getChanNC(i) >= getChanNC(i)) ? getChanNC(1) : 0));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Saw Transform modifies the current color: R=#maxChanVal iff(ra<=R<=rb), G=#maxChanVal iff(ga<=G<=gb), B=#maxChanVal iff(ba<=B<=bb)
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmStep(colorArgType lowCol, colorArgType highCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, ((lowCol.getChanNC(i) <= getChanNC(i)) && (highCol.getChanNC(i) >= getChanNC(i)) ? maxChanVal : 0));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The DiracTot (total) Transform modifies the current color: R=MAX,G=MAX, B=MAX iff ((R==aCol.R)&&(G==aCol.G)&&(B==aCol.B)).
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDiracTot(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          if(aCol.getChanNC(i) != getChanNC(i)) {
            return setToBlack();
            break;
          }
        return setToBlack();
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Dirac Transform modifies the current color: R=MAX iff(R==aCol.R), G=MAX iff(G==aCol.G), B=MAX iff(B==aCol.B).
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmDirac(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, ((aCol.getChanNC(i) == getChanNC(i)) ? maxChanVal : 0));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Fuzzy Dirac Transform modifies the current color: R=MAX iff(|R-ctrCol.R|<=radCol.R), G=MAX iff(|G-ctrCol.G|<=radCol.G), B=MAX iff(|B-ctrCol.B|<=radCol.B).
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
          setChanNC(i, static_cast<clrChanT>(std::sqrt(static_cast<double>(getChanNC(i)) * static_cast<double>(aCol.getChanNC(i)))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes the clipped  geometric mean of the given color and the current one.
          Floating point Numbers re used for intermediate values and the result cast to a colorChanType at the end.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmGmeanClp(colorArgType aCol) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, clipTop(static_cast<channelArithSPType>(std::sqrt(static_cast<double>(getChanNC(i))   * static_cast<double>(aCol.getChanNC(i))))));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Transform the current color by rendering it into a true grey via the same method used by the rgbLuminance() function.
          Note, the rgbLuminance() function is NOT used internally within this function for performance reasons.  This function will do the best job it can
          within the current color depth.
          @return Returns a reference to the current color object.*/
      inline colorTpl & tfrmGreyScaleRGB(void) {
        /* Requires: Inherits numChan>2 from getC2. */
        setChanNC(0, static_cast<clrChanT>(static_cast<channelArithFltType>(getC0()) * static_cast<channelArithFltType>(RGBluminanceWeightR) +
                                           static_cast<channelArithFltType>(getC1()) * static_cast<channelArithFltType>(RGBluminanceWeightG) +
                                           static_cast<channelArithFltType>(getC2()) * static_cast<channelArithFltType>(RGBluminanceWeightB)));
        for(int i=1; i<numChan; i++)
          setChanNC(i, getChanNC(0));
        return *this;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Color Reduction Transformations */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The 216 Palate Web Safe Transform modifies the current color into the closest web safe color from the 216 color web safe pallet.
          @return Returns a reference to the current color object.*/
      inline colorTpl<clrChanT, numChan>& tfrmWebSafe216() {
        for(int i=0; i<numChan; i++)
          setChanNC(i, colorComp2WebSafeColorComp(getChanNC(i)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Protanopia might see.
          @return Returns a reference to the current color object.*/
      inline colorTpl<clrChanT, numChan>& tfrmWebSafePro216() {
        /* Requires: Inherits numChan>2 from getC2. */
        tfrmWebSafe216();
        int colIdx = 36 * (getC0_byte() / 0x33) + 6 * (getC1_byte() / 0x33) + 1 * (getC2_byte() / 0x33) + 1;
        return csSet<colorTpl::csFPwebSafeNormalVision>(colIdx);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Deutanopia might see.
          @return Returns a reference to the current color object.*/
      inline colorTpl<clrChanT, numChan>& tfrmWebSafeDeu216() {
        /* Requires: Inherits numChan>2 from getC2. */
        tfrmWebSafe216();
        int colIdx = 36 * (getC0_byte() / 0x33) + 6 * (getC1_byte() / 0x33) + 1 * (getC2_byte() / 0x33) + 1;
        return csSet<colorTpl::csFPwebSafeDeutanopia>(colIdx);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Tritanoptia might see.
          @return Returns a reference to the current color object.*/
      inline colorTpl<clrChanT, numChan>& tfrmWebSafeTri216() {
        /* Requires: Inherits numChan>2 from getC2. */
        tfrmWebSafe216();
        int colIdx = 36 * (getC0_byte() / 0x33) + 6 * (getC1_byte() / 0x33) + 1 * (getC2_byte() / 0x33) + 1;
        return csSet<colorTpl::csFPwebSafeTritanoptia>(colIdx);
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
      inline colorTpl<double, 3> rgb2colorSpace(colorSpaceEnum space) {
        /* Requires: Inherits numChan>2 from getC2. */

        double redF   = getC0_dbl();
        double greenF = getC1_dbl();
        double blueF  = getC2_dbl();

        if (space == colorSpaceEnum::RGB)
          return colorTpl<double, 3>(redF, greenF, blueF);

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
            if(getC0() == rgbMaxI)
              H = 0.0 + (greenF - blueF) / rangeF;
            else if(getC1() == rgbMaxI)
              H = 2.0 + (blueF - redF) / rangeF;
            else if(getC2() == rgbMaxI)
              H = 4.0 + (redF - greenF) / rangeF;
            H = realWrap(H * 60.0, 360.0);
          }
          if (space == colorSpaceEnum::HSL)
            return colorTpl<double, 3>(H, S, L);
          else
            return colorTpl<double, 3>(H, S, V);
        } else {
          redF   = 100.0 * ((redF   > 0.04045) ? std::pow((redF   + 0.055) / 1.055, 2.4) : redF   / 12.92);
          greenF = 100.0 * ((greenF > 0.04045) ? std::pow((greenF + 0.055) / 1.055, 2.4) : greenF / 12.92);
          blueF  = 100.0 * ((blueF  > 0.04045) ? std::pow((blueF  + 0.055) / 1.055, 2.4) : blueF  / 12.92);

          double X = (0.4124 * redF + 0.3576 * greenF + 0.1805 * blueF);
          double Y = (0.2126 * redF + 0.7152 * greenF + 0.0722 * blueF); // luminance with weights RGBluminanceWeightR, RGBluminanceWeightG, RGBluminanceWeightB
          double Z = (0.0193 * redF + 0.1192 * greenF + 0.9505 * blueF);

          if (space == colorSpaceEnum::XYZ)
            return colorTpl<double, 3>(X, Y, Z);

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
            return colorTpl<double, 3>(L, A, B);

          double C = std::hypot(A, B);

          double H = 0.0;
          if ( std::abs(A) > 1.0e-5)  // Not Grey
            H = realWrap(atan2(B,A) * 180.0 / std::numbers::pi, 360.0);

          if (space == colorSpaceEnum::LCH)
            return colorTpl<double, 3>(L, C, H);
        }

        return colorTpl<double, 3>(0.0, 0.0, 0.0);
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
      inline colorTpl & tfrmLinearGreyLevelScale(double c, double b) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(c * static_cast<double>(getChanNC(i)) + b));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Linear Grey Level Scale transform defined by two control points for each channel of the current color.
          The linear Grey Level Scale transform is defined by the control points, such that the "from" points are mapped into the "to" points.  For example,
          from1.red will map onto to1.red and from2.red will .  Two points define a line for each channel, and thus define a linear grey level scale transform
          for each channel.  Note, this function transforms all channels.  This function is quite slow because of all of the floating point operations
          required.
          @param from1 Control point mapped to argument to1
          @param from2 Control point mapped to argument to2
          @param to1 Control point mapped from argument from1
          @param to2 Control point mapped from argument from2
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmLinearGreyLevelScale(colorArgType from1, colorArgType from2, colorArgType to1, colorArgType to2) {
        for(int i=0; i<numChan; i++) {
          double c = ( (static_cast<double>(to1.getChanNC(i))   - static_cast<double>(to2.getChanNC(i))) /
                       (static_cast<double>(from1.getChanNC(i)) - static_cast<double>(from2.getChanNC(i))) );
          double b = static_cast<double>(to1.getChanNC(i)) - c * static_cast<double>(from1.getChanNC(i));
          setChanNC(i, static_cast<clrChanT>(c * getChanNC(i) + b));
        }
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
        /* Requires: Inherits numChan>3 from setC3 & getC3. */
        setC0(static_cast<clrChanT>(rc * static_cast<double>(theColor.getC0()) + rb));
        setC1(static_cast<clrChanT>(gc * static_cast<double>(theColor.getC1()) + gb));
        setC2(static_cast<clrChanT>(bc * static_cast<double>(theColor.getC2()) + bb));
        setC3(static_cast<clrChanT>(bc * static_cast<double>(theColor.getC3()) + bb));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Standard Power Transform modifies the current color such that:
          R=#maxChanVal*(R/#maxChanVal)**p, G=#maxChanVal*(G/#maxChanVal)**p, B=#maxChanVal*(B/#maxChanVal)**p
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
        /* Requires: Inherits numChan>2 from setC2 & getC2. */
        setC0(static_cast<clrChanT>(std::pow(static_cast<double>(getC0) / static_cast<double>(maxChanVal), rp) * static_cast<double>(maxChanVal)));
        setC1(static_cast<clrChanT>(std::pow(static_cast<double>(getC1) / static_cast<double>(maxChanVal), gp) * static_cast<double>(maxChanVal)));
        setC2(static_cast<clrChanT>(std::pow(static_cast<double>(getC2) / static_cast<double>(maxChanVal), bp) * static_cast<double>(maxChanVal)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Standard Power Transform with p=2. The new color will be:
          R=#maxChanVal*(R/#maxChanVal)**2, G=#maxChanVal*(G/#maxChanVal)**2, B=#maxChanVal*(B/#maxChanVal)**2
          @return Returns a reference to the current color object.*/
      inline colorTpl& tfrmStdPowSqr(void) {
        for(int i=0; i<numChan; i++)
          setChanNC(i, static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(getChanNC(i)) /
                                             static_cast<channelArithSPType>(maxChanVal)));
        return *this;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** The Standard Power Transform with p=1/2. The new color will be:
          R=#maxChanVal*(R/#maxChanVal)**(1/2), G=#maxChanVal*(G/#maxChanVal)**(1/2), B=#maxChanVal*(B/#maxChanVal)**(1/2)
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
      /** Use the first three channels to compute an integer representing a grey scale.
          What is returned is the dot product of the given color and the three scalars: R*redWt+G*greenWt+B*blueWt.  This dot product is not scaled.  Common
          values for (redWt, greenWt, blueWt) are:
          - (     1,      1,     1)  b=3
          - (     3,      4,     2)  b=9
          - (   299,    587,   114)  b=1e3
          - (  2125,   7154,   721)  b=1e4
          - (212671, 715160, 72169)  b=1e6
          - (223002, 749900, 75676)  b=2^20
          - (  2^17,   2^19,  2^16)  b=2^19
          @param redWt The red weight
          @param greenWt The green weight
          @param blueWt The blue weight
          @return The integer representing grey value for the given color. */
      inline channelArithSDPType rgb2GreyDotProd(channelArithSDPType redWt, channelArithSDPType greenWt, channelArithSDPType blueWt) {
        /* Requires: Inherits numChan>2 from getC2. */
        return static_cast<int>(static_cast<channelArithSDPType>(getC0()) * static_cast<channelArithSDPType>(redWt)   +
                                static_cast<channelArithSDPType>(getC1()) * static_cast<channelArithSDPType>(greenWt) +
                                static_cast<channelArithSDPType>(getC2()) * static_cast<channelArithSDPType>(blueWt));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the luminance of the current color via the definition given in the ITU-R Recommendation BT.709.
          The output value will be between 0 and 1, and is given by: (RGBluminanceWeightR*R+RGBluminanceWeightG*G+RGBluminanceWeightB*B)/#maxChanVal.
          @return The luminance for the current object. */
      inline channelArithFltType rgbLuminance(void) {
        /* Requires: Inherits numChan>2 from getC2. */
        return (static_cast<channelArithFltType>(getC0()) * static_cast<channelArithFltType>(RGBluminanceWeightR) +
                static_cast<channelArithFltType>(getC1()) * static_cast<channelArithFltType>(RGBluminanceWeightG) +
                static_cast<channelArithFltType>(getC2()) * static_cast<channelArithFltType>(RGBluminanceWeightB)) / static_cast<channelArithFltType>(maxChanVal);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the unscaled intensity (sum of the first three components) of the current color
          @return The unscaled intensity for the current object. */
      inline channelArithSPType rgbSumIntensity(void) {
        /* Requires: Inherits numChan>2 from getC2. */
        return (static_cast<channelArithSPType>(getC0()) +
                static_cast<channelArithSPType>(getC1()) +
                static_cast<channelArithSPType>(getC2()));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the sum of the components.
          @return Sum of components. */
      inline channelArithSPType sumIntensity(void) {
        channelArithSPType sum = 0;
        for(int i=0; i<numChan; i++)
          sum += getChan(i);
        return (sum);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the scaled intensity (sum of the first three components divided by the maximum intensity possible) of the current color
          @return The scaled intensity for the current object. */
      inline channelArithFltType rgbScaledIntensity(void) {
        return (static_cast<channelArithFltType>(rgbSumIntensity()) / static_cast<channelArithFltType>(numChan) / static_cast<channelArithFltType>(maxChanVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the scaled intensity (sum of the components divided by the maximum intensity possible) of the current color
          @return Sum of components. */
      inline channelArithFltType sumScaledIntensity(void) {
        return (static_cast<channelArithFltType>(sumIntensity()) / static_cast<channelArithFltType>(numChan) / static_cast<channelArithFltType>(maxChanVal));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the value of the largest component.
          @return The value of the largest color component currently stored.*/
      inline clrChanT getMaxC() {
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
      inline clrChanT getMinC() {
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
      inline clrChanT getMaxRGB() { return mjr::max3(getC0(), getC1(), getC2()); } /* Requires: Inherits numChan>2 from getC2. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the value of the smallest component from R, G, and B. This function is highly optimized.
          @return The value of the smallest color component.*/
      inline clrChanT getMinRGB() { return mjr::min3(getC0(), getC1(), getC2()); } /* Requires: Inherits numChan>2 from getC2. */
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute the dot product between the current color and the given color. i.e. c1.r*c2.r+c1.g*c2.g+...
          @param aColor the given color
          @return Returns dot product.*/
      inline channelArithSPType dotProd(colorArgType aColor) {
        channelArithSPType daProd = 0;
        for(int i=0; i<numChan; i++)
          daProd += (static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(aColor.getChanNC(i)));
        return daProd;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Distance between current color and given one (sum squares) Returns the sum of the squares of the differences of the components.  Returns |c1-c2|^2
          @param aColor The given color
          @return Returns distance squared.*/
      inline channelArithSPType distP2sq(colorArgType aColor) {
        channelArithSPType daDist = 0;
        for(int i=0; i<numChan; i++)
          daDist += (static_cast<channelArithSPType>((static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aColor.getChanNC(i))) *
                                                     (static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aColor.getChanNC(i)))));
        return daDist;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Distance between current color and given one (absolute difference) Returns sum of the absolute value of the differences of the components
          @param aColor the given color
          @return Returns absolute distance squared.*/
      inline channelArithSPType distAbs(colorArgType aColor) {
        channelArithSPType daDist = 0;
        for(int i=0; i<numChan; i++)
          daDist += static_cast<channelArithSPType>(std::abs(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aColor.getChanNC(i))));
        return daDist;
      }
//  MJR TODO NOTE: Add distMaxAbs -- max(|C_i - aC_i|)
//  MJR TODO NOTE: Add fuzzy isEqual/isNotEqual/isBlack/... for floating point channels.  isBlack vs isBlackEPS? Or overloaded versions with extra arg?
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns non-zero if the current color is precicely equal to aColor.
          Note the implications for floating point clrChanT.
          @return non-zero if the given color is logically the same as the current color*/
      inline bool isEqual(colorArgType aColor) {
        if(perfectMask)
          return (getMaskNC() == aColor.getMaskNC());
        else
          for(int i=0; i<numChan; i++)
            if(getChanNC(i) != aColor.getChanNC(i))
              return 0;
        return 1;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Like isEual(), but only checks the R, G, & B channels.
          @return non-zero if the given RGB color is the same as the current color*/
      inline bool isEqualRGB(colorArgType aColor) {
        /* Requires: Inherits numChan>2 from getC2. */
        return ((getC0() == aColor.getC0()) &&
                (getC1() == aColor.getC1()) &&
                (getC2() == aColor.getC2()));
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns non-zero if the given color is logically NOT the same as the current color.
          Note the implications for floating point clrChanT.
          @return non-zero if the given color is logically the same as the current color*/
      inline bool isNotEqual(colorArgType aColor) { return !(isEqual(aColor)); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns non-zero if the given color is black (all componnets are zero)
          @return non-zero if the given color is black (all componnets are zero) */
      inline bool isBlack() {
        if(goodMask)
          return (getMaskNC() == maskAllZero);
        else
          for(int i=4; i<numChan; i++)
            if(getChanNC(i) != 0)
              return 0;
        return 1;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** LIke isBlack(), but only checks the R, G, & B channels
          @return non-zero if the given color is black (R, G, & B are  are zero) */
      inline bool isBlackRGB() { return ((getC0() == 0) && (getC1() == 0) && (getC2() == 0)); } /* Requires: Inherits numChan>2 from getC2. */
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Channel Clipping Functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clamp a value on the top end such that it will fit into a clrChanT type. Input values larger than the maximum channel value are mapped to the maximum
          channel value.  Values less than the minimum (0) are not clamped.
          @param arithValue The value to clamp */
      template <typename iT>
      inline clrChanT clipTop(iT arithValue) {
        if(arithValue > maxChanVal)
          return maxChanVal;
        else
          return static_cast<clrChanT>(arithValue);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clamp a value on the bottom end such that it will fit into a clrChanT type. Input values less than the minimum (0), are mapped to 0.  Note values
          greater than the maximum channel value are NOT clamped.
          @param arithValue The value to clam    p */
      template <typename iT>
      inline clrChanT clipBot(iT arithValue) {
        if(arithValue < minChanVal)
          return minChanVal;
        else
          return static_cast<clrChanT>(arithValue);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clamp a value such that it will fit into a clrChanT type. Input values less than zero are mapped to zero, and input values larger than the maximum
          channel value are mapped to the maximum q channel value.
          @param arithValue The value to clamp */
      template <typename iT>
      inline clrChanT clipAll(iT arithValue) {
        if(arithValue > maxChanVal)
          return maxChanVal;
        if(arithValue < minChanVal)
          return minChanVal;
        return static_cast<clrChanT>(arithValue);
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @defgroup cs Color Schemes */

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            return aColor.setChans_dbl(std::clamp(pR, 0.0, 1.0), std::clamp(pG, 0.0, 1.0), std::clamp(pB, 0.0, 1.0));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csX A value in [0, 1] that identifies the color in the scheme.
              @return Returns a colorTpl value */
          static inline colorTpl c(csFltType csX) { colorTpl tmp; return c(tmp, csX); }
        private:
          constexpr static int    psize   = (sizeof...(coefs)) / 3;
          constexpr static double pcoff[] = { coefs... };
      };

      //========================================================================================================================================================
      /** @name Color Schemes: Polynomial */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYgrey
          @ingroup cs
          @extends csPLY_tpl
          Greyscale */
      typedef csPLY_tpl<1.0, 0.0,
                        1.0, 0.0,
                        1.0, 0.0> csPLYgrey;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csPLYgrey
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
          @image html color_lut_docs_csPLYgrey.tiff
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

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            return aColor.setChans_dbl(std::clamp(csX+ampl*(-0.14861*std::cos(angle)+1.78277*std::sin(angle)), 0.0, 1.0),
                                       std::clamp(csX+ampl*(-0.29227*std::cos(angle)-0.90649*std::sin(angle)), 0.0, 1.0),
                                       std::clamp(csX+ampl*(+1.97294*std::cos(angle)),                         0.0, 1.0));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csX A value in [0, 1] that identifies the color in the scheme.
              @return Returns a colorTpl value */
          static inline colorTpl c(csFltType csX) { colorTpl tmp; return c(tmp, csX); }
      };

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

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** Template providing RGB color cube gradiant color schemes */
      template<cornerColorEnum...corners>
      class csCC_tpl {
        public:
          constexpr static csIntType numC = ((sizeof...(corners)) - 1) * chanStepMax + 1;
          static inline colorTpl&  c(colorRefType aColor, csIntType csIdx) { return aColor.cmpRGBcornerGradiant(csIdx % numC, numC, cols); }
          static inline colorTpl   c(                     csIntType csIdx) { colorTpl tmp; return c(tmp, csIdx);                      }
        private:
          constexpr static cornerColorEnum cols[] = { corners... };
      };

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
      /** @name Color Schemes: RGB Cube Diagional Ramps */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csCCdiag01
          @ingroup cs
          @extends csCC_tpl
          Gradient across the diagonal of the RGB color cube from black to white.  Provides about (mjr::colorTpl::chanStepMax + 1) unique colors. */
      typedef csCC_tpl<cornerColorEnum::BLACK,   cornerColorEnum::WHITE> csCCdiag01;
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

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

      //========================================================================================================================================================
      /** @name Color Schemes: Binary */
      //@{
      typedef csBin_tpl<cornerColorEnum::BLACK,   cornerColorEnum::WHITE>  ccBin01; //!< Binary Black-White color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::GREEN,   cornerColorEnum::BLUE>   ccBinGB; //!< Binary Green-Blue color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::RED,     cornerColorEnum::BLUE>   ccBinRB; //!< Binary Red-Blue color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::MAGENTA, cornerColorEnum::CYAN>   ccBinMC; //!< Binary Magenta-Cyan color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::YELLOW,  cornerColorEnum::CYAN>   ccBinYC; //!< Binary Yellow-Cyan color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::RED,     cornerColorEnum::GREEN>  ccBinRG; //!< Binary Red-Green color scheme. First color for even inputs and second color for odd.
      typedef csBin_tpl<cornerColorEnum::MAGENTA, cornerColorEnum::YELLOW> ccBinMY; //!< Binary Magenta-Yellow color scheme. First color for even inputs and second color for odd.
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
            return aColor.setChans(static_cast<clrChanT>(csIdx / 3 + (csIdx%3==0?1:0)),
                                   static_cast<clrChanT>(csIdx / 3 + (csIdx%3==1?1:0)),
                                   static_cast<clrChanT>(csIdx / 3 + (csIdx%3==2?1:0)));            }
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
            return aColor.setChans(static_cast<clrChanT>(csIdx / 4 + ((csIdx+1)%4==0?1:0)),
                                   static_cast<clrChanT>(csIdx / 4 + ((csIdx+2)%4==0?1:0)),
                                   static_cast<clrChanT>(csIdx / 4 + ((csIdx+3)%4==0?1:0)));        
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a colorTpl value */
          static inline colorTpl c(csIntType csIdx) { colorTpl tmp; return c(tmp, csIdx); }
      };
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** Template for HSL color schemes. 
          If clrChanT is integral, this is a discrete color scheme, otherwise it is continuous.. */
      template<cornerColorEnum corner>
      class csHSLh_tpl {
        public:
          constexpr static csIntType numC = (chanIsInt ? meanChanVal : 0);
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Wrapped to [0, meanChanVal].
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csNatType csIdx) { 
            clrChanT cVal = static_cast<clrChanT>(numberWrap(csIdx, meanChanVal));
            colorTpl cc(corner);
            return aColor.setChans(static_cast<clrChanT>(meanChanVal + (meanChanVal < cc.getC0() ? cVal : -cVal)),
                                   static_cast<clrChanT>(meanChanVal + (meanChanVal < cc.getC1() ? cVal : -cVal)),
                                   static_cast<clrChanT>(meanChanVal + (meanChanVal < cc.getC2() ? cVal : -cVal)));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, meanChanVal].
              @return Returns a colorTpl value */
          static inline colorTpl c(csNatType csIdx) { colorTpl tmp; return c(tmp, csIdx); }
      };

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

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Color Schemes: Rainbows */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csRainbowLA
          @ingroup cs
          Computes a color value based upon a linear approximation of the color match functions used to approximate wavelength to RGB conversion.
          The linear color function approximation is not very accurate, but it is quite attractive. */
      class csRainbowLA {
        public:
          static inline colorTpl& c(colorRefType aColor, csIntType numC, csIntType csIdx) {
            csIdx = numberWrap(csIdx, numC);
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a reference to \a aColor. */
            return aColor.setRGBfromWavelengthLA(mjr::genLinMap(static_cast<double>(csIdx),
                                                                static_cast<double>(0),
                                                                static_cast<double>(numC),
                                                                static_cast<double>(minWavelength),
                                                                static_cast<double>(maxWavelength)));
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @return Returns a reference a colorTpl value. */
          static inline colorTpl c(csIntType numC, csIntType csIdx) {
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
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum)
              @return Returns a reference to \a aColor. */
          static inline colorTpl& c(colorRefType aColor, csIntType numC, csIntType csIdx, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR) {
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
              @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum)
              @return Returns a reference a colorTpl value. */
          static inline colorTpl c(csIntType numC, csIntType csIdx, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR) {
            colorTpl tmp;
            return c(tmp, numC, csIdx, interpMethod);
          }
      };
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** Template for fixed size pallets. */
      template<uint32_t...colors>
      class csFP_tpl {
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
          static inline colorTpl c(csIntType csIdx) { return c(colorTpl(), csIdx); }
        private:
          constexpr static uint32_t d[] = { colors... };
      };

      //========================================================================================================================================================
      /** @name "Web Safe" Color Schemes */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPwebSafeNormalVision
          @ingroup cs
          @extends csFP_tpl
          The "web safe" color pallet of 216 colors as seen by someone with normal color vision.
          These colors were originally designed for low color web browsers in the early days of the internet.  Today they provide a simple (easy to compute)
          pallet for color reduction.  The colors are ordered in lexicographical ordering based upon the hexadecimal web-based color name scheme "#RRGGBB" --
          0 maps to "#000000", and 215 maps to "#ffffff".  Note that one can transform an rgb color into the nearest web safe color via tfrmWebSafe216(). */
      typedef csFP_tpl<0x000000, 0x000033, 0x000066, 0x000099, 0x0000CC, 0x0000FF, 0x003300, 0x003333, 0x003366, 0x003399, 0x0033CC,
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
                       0xFFCCFF, 0xFFFF00, 0xFFFF33, 0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF>                                          csFPwebSafeNormalVision;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPwebSafeProtanopia
          @ingroup cs
          @extends csFP_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Protanopia.
          For more about web safe colors, see mjr::colorTpl::csFPwebSafeNormalVision. Also seemjr::colorTpl::csFPwebSafeProtanopiaAlt. */
      typedef csFP_tpl<0x000000, 0x002346, 0x004487, 0x0060C1, 0x0078F0, 0x719CFF, 0x312C00, 0x2E2E30, 0x0D3366, 0x0053A6,
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
                       0xDED8D2, 0xCFD7FF, 0xFFE871, 0xFFE975, 0xFFEA86, 0xFFEDA2, 0xFFF2C8, 0xFFFAFA>                                csFPwebSafeProtanopia;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPwebSafeDeutanopia
          @ingroup cs
          @extends csFP_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Deutanopia.
          For more about web safe colors, see mjr::colorTpl::csFPwebSafeNormalVision. Also seemjr::colorTpl::csFPwebSafeDeutanopiaAlt. */
      typedef csFP_tpl<0x000000, 0x002135, 0x004168, 0x005E97, 0x0076BE, 0x008BDF, 0x362A0C, 0x2F2D34, 0x003E68, 0x005E9A, 0x0078C2,
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
                       0xE1D8FD, 0xFFD592, 0xFFD594, 0xFFD79D, 0xFFDAAD, 0xFFDFC8, 0xFFE8EF>                                          csFPwebSafeDeutanopia;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPwebSafeTritanoptia
          @ingroup cs
          @extends csFP_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Tritanoptia.
          For more about web safe colors, see mjr::colorTpl::csFPwebSafeNormalVision. Also seemjr::colorTpl::csFPwebSafeTritanoptiaAlt. */
      typedef csFP_tpl<0x000000, 0x001C1D, 0x003739, 0x005155, 0x006A6E, 0x007F85, 0x173033, 0x0A3236, 0x004347, 0x00595E, 0x006F74,
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
                       0xFBD1E1, 0xFFE4F2, 0xFFE5F3, 0xFFE6F5, 0xFFEAF9, 0xFDEFFF, 0xF4F0FF>                                          csFPwebSafeTritanoptia;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPwebSafeProtanopiaAlt
          @ingroup cs
          @extends csFP_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Protanopia.
          For more about web safe colors, see mjr::colorTpl::csFPwebSafeNormalVision. Also seemjr::colorTpl::csFPwebSafeProtanopia. */
      typedef csFP_tpl<0x000000, 0x000E33, 0x001D66, 0x002B99, 0x003ACC, 0x0048FF, 0x422F00, 0x303133, 0x003566, 0x003D99, 0x0047CC,
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
                       0xB7D4FF, 0xFFF300, 0xFFF332, 0xFFF466, 0xFFF799, 0xFFFACC, 0xFFFFFF>                                          csFPwebSafeProtanopiaAlt;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPwebSafeDeutanopiaAlt
          @ingroup cs
          @extends csFP_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Deutanopia.
          For more about web safe colors, see mjr::colorTpl::csFPwebSafeNormalVision. Also seemjr::colorTpl::csFPwebSafeDeutanopia. */
      typedef csFP_tpl<0x000000, 0x001433, 0x002866, 0x003C99, 0x0050CB, 0x0064FE, 0x3A2A0B, 0x2C2F33, 0x003866, 0x004699, 0x0057CB,
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
                       0xC8DDFE, 0xFFE62B, 0xFFE73F, 0xFFE96B, 0xFFEE9B, 0xFFF5CD, 0xFFFFFF>                                          csFPwebSafeDeutanopiaAlt;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @class csFPwebSafeTritanoptiaAlt
          @ingroup cs
          @extends csFP_tpl
          The "web safe" color pallet of 216 colors as seen by someone with Tritanoptia.
          For more about web safe colors, see mjr::colorTpl::csFPwebSafeNormalVision. Also seemjr::colorTpl::csFPwebSafeTritanoptia. */
      typedef csFP_tpl<0x000000, 0x00191E, 0x00323D, 0x004B5B, 0x00647A, 0x007C98, 0x202E31, 0x113237, 0x00404A, 0x005463, 0x006A7F,
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
                       0xF2D7D9, 0xFFE7EC, 0xFFE8ED, 0xFFEAEE, 0xFFEFF2, 0xFFF6F7, 0xFFFFFF>                                          csFPwebSafeTritanoptiaAlt;
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** Template for Color Brewer 2 variable sized pallets. */
      template<csIntType mx, uint32_t...colors>
      class csCB_tpl {
        public:
          constexpr static csIntType minNumC = 3;
          constexpr static csIntType maxNumC = mx;
          /** Set given colorTpl instance to the selected color in the color scheme.
              @param aColor color object to set.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @param numC Number of colors for the given scheme.  Will be clamped to [minNumC, maxNumC].
              @return Returns a reference to \a aColor. */
          static colorTpl&  c(colorRefType aColor, csIntType csIdx, csIntType numC=maxNumC) { 
            csIntType b = std::clamp(numC, minNumC, maxNumC);
            csIntType i = csIdx % b; 
            return aColor.setRGBfromLogPackIntARGB(d[b*(b-1)/2-3+i]); 
          }
          /** Create a new colorTpl object and set it's color to the selected color in the color scheme.
              @param csIdx Index of color in pallet.  Wrapped to [0, numC-1].
              @param numC Number of colors for the given scheme.  Will be clamped to [minNumC, maxNumC].
              @return Returns a reference a colorTpl value. */
          static colorTpl c(csIntType csIdx, csIntType numC=maxNumC) { 
            colorTpl tmp; 
            return c(tmp, csIdx, numC);
          }
        private:
          constexpr static uint32_t d[] = { colors... };
      };

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

      template <class csT> colorTpl& csSet(csIntType csIdx) { return csT::c(*this, csIdx); }

  };
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** i/O stream output operator for colorTpl types. */
  template <class clrChanT, int numChan>
  requires (numChan>0) && ((std::is_unsigned<clrChanT>::value && std::is_integral<clrChanT>::value) || std::is_floating_point<clrChanT>::value)
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

} // end namespace mjr

#define MJR_INCLUDE_colorTpl
#endif

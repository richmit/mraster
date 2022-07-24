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
#include "colorData.hpp"

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

      /** @name Private Object Data */
      //@{
      /** Holds the color channel data.
          The union is used to overlay a mask integer leading to dramatic performance improvements for common color types. */
      union {
          maskType theInt;
          clrChanT thePartsA[numChan];
      } theColor;
      //@}

      /** @name Private Constants */
      //@{
      const static int minWavelength = 360; //!< Minimum wavelength for wavelength conversion
      const static int maxWavelength = 830; //!< Maximum wavelength for wavelength conversion
      //@}

      /** @name Private utility functions */
      //@{
      /** Helper function for converting to web safe colors.  This function is highly optimized. */
      clrChanT colorComp2WebSafeColorComp(clrChanT aColorComp);
      /** Find the element in the discreet value list that is closest to the given component value.
          The intended use is to reduce colors down to a smaller set of values -- ex: convert a color to the nearest web safe value. */
      clrChanT colorComp2CloseColorComp(clrChanT aColorComp, clrChanT *discreetVals, int numVals);
      /** This is a helper function for setRGBfromColorSpace. */
      double hslHelperVal(double n1, double n2, double hue);
      /** Set all channels to minChanVal. */
      void setChansToMin();
      /** Set all channels to maxChanVal. */
      void setChansToMax();
      /** Sets the current color based upon the contents of the given std::string.
          This is the guts of the magic constructor taking a string.  First all channels are set to minChanVal.  The next step depends on the contents of the
          colorString argument.  If colorString starts with a "#", then setChans() will be used.  Otherwise setToCorner() will be used
          @param colorString string specifying a color.
          @return Returns a reference to the current color object.*/
      colorTpl& setColorFromString(std::string colorString);
      /** Convert a uint8_t to a clrChanT (for integral clrChanT) */
      clrChanT convertByteToChan(uint8_t cVal) const requires (std::integral<clrChanT>);
      /** Convert a uint8_t to a clrChanT (for floating point clrChanT)*/
      clrChanT convertByteToChan(uint8_t cVal) const requires (std::floating_point<clrChanT>);
      /** Convert a clrChanT to a uint8_t (for integral clrChanT) */
      uint8_t convertChanToByte(clrChanT cVal) const requires (std::floating_point<clrChanT>);
      /** Convert a clrChanT to a uint8_t (for floating point clrChanT) */
      uint8_t convertChanToByte(clrChanT cVal) const requires (std::integral<clrChanT>);
      /** Convert a double to a clrChanT */
      clrChanT convertDoubleToChan(double cVal) const;
      /** Convert a clrChanT to a double */
      double convertChanToDouble(clrChanT cVal) const;
      /** Return the mask value */
      maskType getMask() const;
      bool setMask(maskType aMask);
      //@}

      public:

      /** @name Public Constants Related to Types */
      //@{
      constexpr static int      bitsPerChan    = (int)(sizeof(clrChanT)*CHAR_BIT);                                       //!< Number of bits in clrChanT
      constexpr static int      bitsPerPixel   = numChan*bitsPerChan;                                                    //!< Number of color data bits
      constexpr static bool     chanIsInt      = std::is_integral<clrChanT>::value;                                      //!< clrChanT is an integral type
      constexpr static bool     chanIsFlt      = !(chanIsInt);                                                           //!< clrChanT is a floating point type
      constexpr static bool     chanIsByte     = std::is_same<clrChanT, uint8_t>::value;                                 //!< is clrChanT an 8-bit unsigned int?
      constexpr static bool     chanIsDouble   = std::is_same<clrChanT, double>::value;                                  //!< is clrChanT a double?
      constexpr static bool     goodMask       = chanIsInt && (sizeof(maskType)            >= sizeof(clrChanT)*numChan); //!< maskType is big enough
      constexpr static bool     goodArithD     = chanIsFlt || (sizeof(channelArithDType)   >= sizeof(clrChanT)*2);       //!< channelArithDType is big enough
      constexpr static bool     goodArithSP    = chanIsFlt || (sizeof(channelArithSPType)  >= sizeof(clrChanT)*2);       //!< channelArithSPType is big enough
      constexpr static bool     goodArithSDP   = chanIsFlt || (sizeof(channelArithSDPType) >= sizeof(clrChanT)*4);       //!< channelArithSDPType is big enough
      constexpr static bool     goodArithFlt   = chanIsFlt || (sizeof(channelArithFltType) >  sizeof(clrChanT));         //!< channelArithFltType is big enough
      constexpr static bool     goodArithLog   = (sizeof(channelArithLogType) == sizeof(clrChanT));                      //!< channelArithLogType is the right size
      constexpr static int      sizeOfColor    = (int)(goodMask ? sizeof(maskType) : sizeof(clrChanT)*numChan);          //!< Size of this object
      constexpr static bool     ptrIsSmaller   = sizeOfColor > (int)sizeof(colorPtrType);                                //!< This object smaller than a pointer
      constexpr static clrChanT maxChanVal     = (chanIsInt ? std::numeric_limits<clrChanT>::max() : 1);                 //!< maximum value for a channel
      constexpr static clrChanT minChanVal     = (chanIsInt ? std::numeric_limits<clrChanT>::min() : 0);                 //!< maximum value for a channel
      constexpr static clrChanT meanChanVal    = (maxChanVal-minChanVal)/2;                                              //!< middle value for a channel
      constexpr static int      channelCount   = numChan;                                                                //!< Number of channels
      //@}

      /** @name Public type for argument passing */
      //@{
      /** A type for passing colorTpl objects to functions.

          WHen the size of a colorTpl object is smaller than a pointer, this type is colorTpl -- resulting in pass by value.  Otherwise, this type is
          colorType const& -- resulting in pass by refrence. */
      typedef typename std::conditional<ptrIsSmaller, colorCRefType, colorType>::type colorArgType;

      /** A type used to pass color scheme indexes.
          This will be the larger of uint32_t and colorChanArithSPType. We use cmp_less because < confuses Doxygen.*/
      typedef typename std::conditional<std::cmp_less(sizeof(channelArithSPType), sizeof(uint32_t)), uint32_t, channelArithSPType>::type csIdxType;

      // typedef uint32 csIdxType;

      /** A type used to pass indexed color pallet (ICP) indexes. */
      typedef uint16_t icpIdxType;
      //@}

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

      /** @name Constructors: C++ Utility */
      //@{
      /** The no arg constructor is a noop so we don't needlessly initialize millions of pixels -- compiler warnings are expected. */
      colorTpl();
      /** Copy constructor (heavily used for assignment in the ramCanvas library). */
      colorTpl(const colorType& aColor);
      //@}

      /** @name Constructors: Set channels
          These all use setChans internally; however, these constructors will set any unspecified channels to min. */
      //@{
      /** Uses setChans() to set the first four channels of the color object
          @param c1 The value to set the first channel to
          @param c2 The value to set the second channel to
          @param c3 The value to set the third channel to
          @param c4 The value to set the fourth channel to  */
      colorTpl(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4);
      /** Uses setChans() to set the first three channels of the color object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the second channel to
          @param c3 The value to set the third channel to */
      colorTpl(clrChanT c1, clrChanT c2, clrChanT c3);
      /** Uses setChans() to set the first two channels of the color object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the second channel to */
      colorTpl(clrChanT c1, clrChanT c2);
      /** Uses setChans() to set all channels to the given value
          @param cVal The value to set the channels to */
      colorTpl(clrChanT cVal);
      //@}

      /** @name Constructors: Corner Colors */
      //@{
      /** Uses the setToCorner() method to set the initialize the object.
       Note that no constructor exists taking a character to provide to setToCorner().  Why?  Because character literals are integers in C++, and they might
       be the same as clrChanT -- rendering ambiguous overload cases.*/
      colorTpl(cornerColorEnum cornerColor);
      //@}

      /** @name Constructors: Magic String Constructor
          These constructors work hard to interpret the given string, and set the color. */
      //@{
      /** Uses the setColorFromString() method to set the initialize the object. */
      colorTpl(std::string colorString);
      /** Uses the setColorFromString() method to set the initialize the object. */
      colorTpl(const char* colorCString);
      //@}

      /** @name Destructor */
      //@{
      /** The destructor for this class is a no-op. */
      ~colorTpl();
      //@}

      /** @name Utility Methods */
      //@{
      /** Copy the contents of the given color object into the current object.
          When sizeof(colorTpl)<=sizeof(maskType), this function consists of a single assignment statement.  Otherwise it is O(numChan).
          @return Returns a reference to the current color object.*/
      colorTpl& copy(colorArgType aCol);
      //@}

      /** @name Component Access */
      //@{
      /** Provides access to an specified color channel value with compile time index check.  
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      clrChanT getC0() const;
      /** Provides access to an specified color channel value with compile time index check.  
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      clrChanT getC1() const requires (numChan>1);
      /** Provides access to an specified color channel value with compile time index check.  
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      clrChanT getC2() const requires (numChan>2);
      /** Provides access to an specified color channel value with compile time index check.  
          The channels are 0 indexed.
          @return The the value of the indexed channel. */
      clrChanT getC3() const requires (numChan>3);
      /** Provides access to an specified color channel value with run time time index check.  
          The channels are 0 indexed.  Returns #minChanVal if \a chan id out of range.
          @return The the value of the indexed channel. */
      clrChanT getChan(int chan) const;
      /** Provides access to an specified color channel value with no index check.  
          The channels are 0 indexed.
          @param chan The channel index
          @return The the value of the indexed channel. */
      clrChanT getChanNC(int chan) const;
      //@}


      /** @name Component Access and Conversion to Double Float */
      //@{
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      double getC0_dbl() const;
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      double getC1_dbl() const;
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      double getC2_dbl() const;
      /** Provides access to an specified color channel value as a double with compile time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      double getC3_dbl() const;
      /** Provides access to an specified color channel value as a double with run time index check.
          Value is scaled from source clrChanT range to [0, 1]. The channels are 0 indexed.
          Returns 0.0d if \a chan is out of range.
          @param chan The channel index
          @return The the value of the indexed channel. */
      double getChan_dbl(int chan) const;
      //@}

      /** @name Component Access and Conversion to Unsigned 8-Bit Integer */
      //@{
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      uint8_t getC0_byte() const;
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      uint8_t getC1_byte() const;
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      uint8_t getC2_byte() const;
      /** Provides access to an specified color channel value as a uint8_t with compile time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          @return The the value of the indexed channel. */
      uint8_t getC3_byte() const;
      /** Provides access to an specified color channel value as a uint8_t with run time index check.
          Value is scaled from source clrChanT range to 8-bit range. The channels are 0 indexed.
          Returns 0.0d if \a chan is out of range.
          @param chan The channel index
          @return The the value of the indexed channel. */
      uint8_t getChan_byte(int chan) const;
      //@}

      /** @name Set Channel Value(s) with clrChanT values */
      //@{
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      colorTpl& setC0(clrChanT cVal);
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      colorTpl& setC1(clrChanT cVal) requires (numChan>1);;
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      colorTpl& setC2(clrChanT cVal) requires (numChan>2);;
      /** Sets the specified color channel value with compile time index check.  The channels are 0 indexed.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      colorTpl& setC3(clrChanT cVal) requires (numChan>3);;
      /** Sets the specified color channel value with run time index check.           
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @param cVal The channel value
          @return Returns a reference to the current color object.*/
      colorTpl& setChan(int chan, clrChanT cVal);
      /** Sets the specified color channel value with no index check.  
          The channels are 0 indexed.
          @param chan The channel index
          @param cVal The channel value
          @return The the value of the indexed channel. */
      colorTpl& setChanNC(int chan, clrChanT cVal);
      /** Sets the given channel of the current object to #maxChanVal.
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP. 
          @return Returns a reference to the current color object. */
      colorTpl& setChanToMax(int chan);
      /** Sets the given channel of the current object to #minChanVal.
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP. 
          @return Returns a reference to the current color object. */
      colorTpl& setChanToMin(int chan);
      /** Sets the first four channels current object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the thrid channel to
          @param c3 The value to set the second channel to
          @param c4 The value to set the alpha channel to
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4);
      /** Sets the first three channels current object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the thrid channel to
          @param c3 The value to set the second channel to
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(clrChanT c1, clrChanT c2, clrChanT c3);
      /** Sets the first two channels current object.
          @param c1 The value to set the first channel to
          @param c2 The value to set the thrid channel to
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(clrChanT c1, clrChanT c2);
      /** Sets all components of the current object from to \a cVal
          @param cVal The value to set each channel to
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(clrChanT cVal);
      /** Sets the first four channels current object.
          @param chanValues The values for the components
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> chanValues);
      /** Sets the first three channels current object.
          @param chanValues The values for the components
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(std::tuple<clrChanT, clrChanT, clrChanT> chanValues);
      /** This function sets color channels from the data in a std::vector.
          @param chanValues A std::vector containing the color channels.  It must have at least #channelCount elements!  This is *not* checked!
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(std::vector<clrChanT>& chanValues);
      /** Sets the current color based upon the contents of the given color hex string.
          A color hex string is similar to the hash hex strings used in HTML, but extended to larger depths and higher channel counts.

                    #FF0000       -- Red for an RGB color with 8-bit per channels
                    #FFFF00000000 -- Red for an RGB color with 16-bit per channels
                    #FF0000EE     -- Red for an RGBA color with 8-bit per channels  (with alpha set to EE)
                    #FFFFFFFFFF   -- White for a 5 channel color with 8-bit per channels

          Fewer channel specifiers may be provided than channels in the current color.  In this case the unspecified channels are left untouched.
          For most error cases this function silently fails leaving the current color object unchanged.
          @param colorHexString hex string specifying a color.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans(std::string colorHexString);
      //@}

      /** @name Set Channel Value(s) with Floating Point Doubles */
      //@{
      /** Sets the given channel of the current object from a floating point value in the unit interval, [0,1].
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object. */
      colorTpl& setChan_dbl(int chan, double cVal);
      /** Sets the first channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC0_dbl(double cVal);
      /** Sets the second channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC1_dbl(double cVal);
      /** Sets the thrid channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC2_dbl(double cVal);
      /** Sets the fourth channel of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set the channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC3_dbl(double cVal);
      /** This function sets the first four channels of the current color objects using floats in the unit interval, [0,1].
          @param c1 The value to set the first channel to -- 1 is fully saturated.
          @param c2 The value to set the thrid channel to -- 1 is fully saturated.
          @param c3 The value to set the second channel to -- 1 is fully saturated.
          @param c4 The value to set the alpha channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_dbl(double c1, double c2, double c3, double c4);
      /** This function sets the first three channels of the current color objects using floats in the unit interval, [0,1].
          @param c1 The value to set the first channel to -- 1 is fully saturated.
          @param c2 The value to set the thrid channel to -- 1 is fully saturated.
          @param c3 The value to set the second channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_dbl(double c1, double c2, double c3);
      /** This function sets the first two channels of the current color objects using floats in the unit interval, [0,1].
          @param c1 The value to set the first channel to -- 1 is fully saturated.
          @param c2 The value to set the thrid channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_dbl(double c1, double c2);
      /** Sets all components of the current object from a floating point value in the unit interval, [0,1].
          @param cVal The value to set each channel to -- 1 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_dbl(double cVal);
      //@}

      /** @name Set Channel Value(s) with 8-Bit, Unsigned Integers */
      //@{
      /** Sets the given channel of the current object from an uint8_t value in the interval [0,255].
          @param chan The channel to set.  The channels are 0 indexed.  Out of range is a NOOP.
          @param cVal The value to set the channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object. */
      colorTpl& setChan_byte(int chan, uint8_t cVal);
      /** Sets the first channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the first channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC0_byte(uint8_t cVal);
      /** Sets the second channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the thrid channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC1_byte(uint8_t cVal);
      /** Sets the thrid channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the second channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC2_byte(uint8_t cVal);
      /** Sets the fourth channel of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set the alpha channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setC3_byte(uint8_t cVal);
      /** Sets the first four channels current object. Values are uint8_t the range [0,255].
          @param c1 The value to set the first channel to  -- 255 is fully saturated.
          @param c2 The value to set the thrid channel to  -- 255 is fully saturated.
          @param c3 The value to set the second channel to  -- 255 is fully saturated.
          @param c4 The value to set the alpha channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4);
      /** Sets the first three channels current object. Values are uint8_t the range [0,255].
          @param c1 The value to set the first channel to  -- 255 is fully saturated.
          @param c2 The value to set the thrid channel to  -- 255 is fully saturated.
          @param c3 The value to set the second channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3);
      /** Sets the first three channels current object. Values are uint8_t the range [0,255].
          @param c1 The value to set the first channel to  -- 255 is fully saturated.
          @param c2 The value to set the thrid channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_byte(uint8_t c1, uint8_t c2);
      /** Sets all components of the current object from an uint8_t value in the interval [0,255].
          @param cVal The value to set each channel to  -- 255 is fully saturated.
          @return Returns a reference to the current color object.*/
      colorTpl& setChans_byte(uint8_t cVal);
      //@}

      /** @name Set To Special Colors (RGB Corners)
          While the assumed color model is RGB, these functions are generalized beyond RGB in that non-RGB channels are uniformly, and usefully, manipulated.
          For example, setToBlack and setToWhite functions set all channels to minimum and maximum respectively -- both reasonable definitions for "black" and
          "white" in many situations.  The "primary" colors (red, blue, and green) set all non-RGB channels to minimum, and the "secondary" colors (cyan,
          yellow, and magenta) set all non-RGB channels to max.  This odd difference in behavior on non-RGB channels between primary and secondary colors is
          due to an optimization choice.  This choice allows the setTo*() functions to complete their work using no more than two assignment statements for
          channel objects with integer channels and good masks.  Note that the other functions in this group end with a call to one of the setTo*()
          functions. */
      //@{
      /** Set all channels to #minChanVal -- black in RGB
          @return Returns a reference to the current color object.*/
      colorTpl& setToBlack();
      /** Set all channels to #maxChanVal -- white in RGB
          @return Returns a reference to the current color object.*/
      colorTpl& setToWhite();
      /** Set channel 1 is set to #maxChanVal, and all others to #minChanVal -- red in RGB
          @return Returns a reference to the current color object.*/
      colorTpl& setToRed();
      /** Channel 3 to #maxChanVal, and all others to #minChanVal -- blue in RGB
          @return Returns a reference to the current color object.*/
      colorTpl& setToBlue();
      /** Set the color to green. (RGB=010).
          Channel 2 to #maxChanVal, and all others to #minChanVal -- green in RGB
          @return Returns a reference to the current color object.*/
      colorTpl& setToGreen();
      /** Set the color to cyan (RGB=011).
          Channel 1 is set to #minChanVal, all others are set to #maxChanVal.
          @return Returns a reference to the current color object.*/
      colorTpl& setToCyan();
      /** Set the color to yellow (RGB=110).
          Channel 3 is set to #minChanVal, all others are set to #maxChanVal.
          @return Returns a reference to the current color object.*/
      colorTpl& setToYellow();
      /** Set the color to magenta (RGB=101).
          Channel 2 is set to #minChanVal, all others are set to #maxChanVal.
          @return Returns a reference to the current color object.*/
      colorTpl& setToMagenta();
      /** Set the current color based upon the single character given -- 0==black, R, G, B, M, C, Y, W/1==white).
          The color is acutally set using one of the setTo*() functions.
          If the value of cornerColor is not valid, then setToBlack() is used
          @param cornerColor Character specifying the color
          @return Returns a reference to the current color object.*/
      colorTpl& setToCorner(char cornerColor);
      /** Set the color to the given  corner color.
          The color is acutally set using one of the setTo*() functions.
          @param cornerColor Enum value specifying the color
          @return Returns a reference to the current color object.*/
      colorTpl& setToCorner(cornerColorEnum cornerColor);
      /** Set the color to the named corner color.
          If cornerColor is one character long, then the call is equivalent to setToCorner(cornerColor[0]).  Otherwise a valid
          corner color name string is expected: red, blue, green, cyan, yellow, magenta, black, or white.  If no valid color
          name is provided, then setToBlack() is used. The color is actually set using one of the setTo*() functions.
          @param cornerColor String value specifying the color
          @return Returns a reference to the current color object.*/
      colorTpl& setToCorner(std::string cornerColor);
      //@}

      /** @name Color Setting Methods via Packed Integers
          We use R, G, B, and A in the method names to indicate the first, second, third, and fourth channels respectively of the current color object. */
      //@{
      /** Set the color based upon the bytes of the given integer ordered from LSB to MSB.
           - LSB (lest significant byte) -> Channel1
           - next byte                   -> Channel2
           - next byte                   -> Channel3
           - MSB (most significant byte) -> Channel4
          The extracted bytes are interpreted as by setChans_byte.  Any channels beyond four are left untouched.
          @param anInt The integer from which to extract bytes to set color
          @return Returns a reference to the current color object.*/
      colorTpl& setRGBAfromLogPackIntABGR(uint32_t anInt);
      /** Just like setRGBAfromLogPackIntABGR, but no A */
      colorTpl& setRGBfromLogPackIntABGR(uint32_t anInt);
      /** Set the color based upon the bytes of the given integer ordered from LSB to MSB.
           - LSB (lest significant byte) -> Channel3
           - next byte                   -> Channel2
           - next byte                   -> Channel1
           - MSB (most significant byte) -> Channel4
          The extracted bytes are interpreted as by setChans_byte.  Any channels beyond four are left untouched.
          @param anInt The integer from which to extract bytes to set color
          @return Returns a reference to the current color object.*/
      colorTpl& setRGBAfromLogPackIntARGB(uint32_t anInt);
      /** Just like setRGBAfromLogPackIntARGB, but no A */
      colorTpl& setRGBfromLogPackIntARGB(uint32_t anInt);
      /** Set the color based upon the bytes of the given integer ordered from LSB to MSB.
          The *Idx arguments select which byte of the int is used for each channel -- with LSB equal to index 0 and MSB equal to index 3. The extracted bytes
          are interpreted as by setChans_byte.  Any channels beyond four are left untouched.
          @param anInt The integer from which to extract bytes to set color
          @param rIdx Location of red byte in \a anInt
          @param gIdx Location of green byte in \a anInt
          @param bIdx Location of blue byte in \a anInt
          @param aIdx Location of alpha byte in \a anInt
          @return Returns a reference to the current color object.*/
      colorTpl& setRGBAfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx);
      /** Just like setRGBAfromLogPackIntGen, but no A */
      colorTpl& setRGBfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx);
      /** Set the color based upon the bytes of the given integer ordered as in RAM.
          The *Idx arguments select which byte of the int is used for each channel -- with byte[0] being the first in RAM. The extracted bytes are interpreted
          as by setChans_byte.  Any channels beyond four are left untouched.
          @param anInt The integer from which to extract bytes to set color
          @param rIdx Location of red byte in \a anInt
          @param gIdx Location of green byte in \a anInt
          @param bIdx Location of blue byte in \a anInt
          @param aIdx Location of alpha byte in \a anInt
          @return Returns a reference to the current color object.*/
      colorTpl& setRGBAfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx);
      /** Just like setRGBAfromPackIntGen, but no A */
      colorTpl& setRGBfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx);
      //@}

      /** @name Setting Colors Based Upon Other Color Spaces
          Other Colorspaces.
          The most common use case is to think of the image as holding RGB color data, and these functions are designed with that idea in mind.  Note that
          alternate colorspaces computations all take place with double floating point values.  Various other tools are also available for manipulating colors
          in other colorspaces (see: interplColorSpace() and rgb2colorSpace() for example)..  See the #colorSpaceEnum for details regarding supported colorspaces. */
      //@{
      /** Set the color indicated by the given HSV values.
          The 'unit' in the name indicates that the values for h, s, and v are the unit interval, [0,1].  This function is based upon the HSV_TO_RGB found in
          Foley and Van Dam.
          @param H The Hue.
          @param S The Saturation.
          @param V The Value 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBfromUnitHSV(double H, double S, double V);
      /** Set the color indicated by the given HSL values.
          The 'unit' in the name indicates that The ranges for h, s, and v are the the unit interval -- i.e. [0,1].  The algorithm is that presented in
          Computer Graphics by Foley, Van Dam, Feiner, and Hughes -- 2nd edition page 596.  I have corrected a typeo in the text algorithm.
          @param H The Hue.
          @param S The Saturation.
          @param L The Lightness or Luminescence
          @return Returns a reference to the current color object. */
      colorTpl& setRGBfromUnitHSL(double H, double S, double L);
      /** Set the color indicated by the color space and values.
          @param space The colorspace
          @param inCh1 Channel one value for given colorspace
          @param inCh2 Channel two value for given colorspace
          @param inCh3 Channel three value for given colorspace
          @return Returns a reference to the current color object. */
      colorTpl& setRGBfromColorSpace(colorSpaceEnum space, double inCh1, double inCh2, double inCh3);
      /** @overload */
      colorTpl& setRGBfromColorSpace(colorSpaceEnum space, colorTpl<double, 3> inColor);
      //@}

      /** @name Color Schemes: Indexed Color Schemes.
       Indexed color schemes use an array of colors (defined as hex color strings or uint32_t integers.  The hex color strings are interpreted via setChans()
       and the integers are interpreted by setRGBAfromLogPackIntARGB().  The first element of the array holds the number of colors, and the rest of the
       elements describe the colors.  Several schemes I particularly like may be found in colorData.cpp. */
      //@{
      /** Sets the color based upon the web safe 216 indexed color pallet.
          The colors are ordered in lexicographical ordering based upon the hexadecimal web-based color name scheme "#RRGGBB" -- i.e. 1 maps to "#000000", and
          216 maps to "#ffffff".  Note that one can transform an rgb color into the nearest web safe color via tfrmWebSafe216().  As with all icp functions, 0
          is black and the last color, at 217, is white.
          @param icpIdx An integer
          @return A reference to the current object */
      colorTpl& setRGBtoWebSafe216(int icpIdx);
      /** Sets the color based upon an indexed color pallet.
          As with all icp functions, 0 is black and the last color, at 217, is white.  Out of range \a icpIdx resutls in black.
          @param icpIdx An integer
          @param icpArray The pallet data
          @return A reference to the current object */
      colorTpl& setRGBfromICP(int icpIdx, const char **icpArray);
      /** @overload */
      colorTpl& setRGBfromICP(int icpIdx, const uint32_t* icpArray);
      //@}

      /** @name Color Schemes: TGA Height Maps for POVray */
      //@{
      /** Computes a 24-bit truecolor value intended for use in producing 16-bit greyscale TGA.
          This is the color scheme that should be used for POVray 16-bit height files
          @param tga16val An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpGreyTGA16bit(uint16_t tga16val);
      /** Computes a 24-bit truecolor value intended for use in producing 24-bit greyscale TGA.
          @param tga24val An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpGreyTGA24bit(uint32_t tga24val);
      //@}

      /** @name Setting Colors Based Upon Spectral Color */
      //@{
      /** Set the color indicated by the given wavelength.
          This function uses an algorithm based upon the color matching functions as tabulated in table 3 from Stockman and Sharpe (2000) -- I believe they
          are taken from Stiles and Burch 10-degree (1959).  Four of the algorithms are based upon simple linear interpolation, while one is based upon
          exponential bump functions closely matching the color matching functions.  The method of interpolation may be specified via the final argument.
          @param wavelength   The wavelength to convert into RGB
          @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum) 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBfromWavelengthCM(double wavelength, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR);
      /** Set the color indicated by the given wavelength.
          This function uses an algorithm based upon linear approximations to the color match functions.  I believe the original algorithm is due to Dan
          Bruton, and his FORTRAN version is available (at least as of 1997) at http://www.physics.sfasu.edu/astro/color.html
          @param wavelength to convert 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBfromWavelengthLA(double wavelength);
      //@}

      /** @name Color Schemes: Rainbows */
      //@{
      /** Computes a color value based upon a linear approximation of the color match functions used to approximate wavelength to RGB conversion.
          The linear color function approximation is not very accurate, but it is quite attractive.
          @param base The maximum number of colors
          @param csIdx The index of the desired color */
      colorTpl& setRGBcmpRainbowLA(csIdxType base, csIdxType csIdx);
      /** Computes a color value based upon an algorithm to convert wavelength to RGB that uses the Color Matching functions.
          @param base The maximum number of colors
          @param csIdx        The index of the desired color
          @param interpMethod Specify the interpolation method (see: cmfInterpolationEnum) 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpRainbowCM(csIdxType base, csIdxType csIdx, cmfInterpolationEnum interpMethod = cmfInterpolationEnum::LINEAR);
      /** Computes a color value based upon a common rainbow-like color scheme based upon the HSV or HSL color space.
          This rainbow is not natural in that the colors on the ends match each other, and the colors move in the wrong direction (red to violet).  This
          function uses floating point arithmetic and is thus prone to round off errors.  For a precise rainbow with integer arithmetic, see the function
          setRGBcmpClrCubeRainbow().
          @param base The maximum number of colors
          @param csIdx The index of the desired color 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpRainbowHSV(csIdxType base, csIdxType csIdx);
      /** This computes a color value based upon a common rainbow-like color scheme based upon an edge traversal of the RGB color cube.
          It is thus the same as using cmpRGBcolorRamp() with a corner sequence of "RYGCBMR".  At least one color component is always maximal in RGB space, and one
          is minimum.  This sequence of colors corresponds to an HSV sequence from h=0 to h=360, with s=100 and v=100.  This is simply a more precise version
          of setRGBcmpRainbowHSV that is immune to round off errors as it doesn't require any floating point conversions.  This function will generate
          6*#maxChanVal+1 different colors.
          @param csIdx The index of the desired color 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpClrCubeRainbow(csIdxType csIdx);
      //@}

      /** @name Color Schemes: Grey and Pseudo-Grey */
      //@{
      /** Computes a true grey color given an index.
          Provides #maxChanVal different colors.  This function is NOT always the same as cmpRGBcolorRamp() with a string of "0W" because cmpRGBcolorRamp() is based
          upon a three channel space, while this function is based upon the number of channels in the current color.  For example, this function sets the
          alpha value of an RGBA color.  For an RGB based grey ramp, use setRGBcmpGreyRGB -- which is the same as cmpRGBcolorRamp() with a corner string of "0W".
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpGrey(csIdxType csIdx);
      /** Returns an RGB based true grey color given an index.
          Provides #maxChanVal different colors.  This This function is is always the same as cmpRGBcolorRamp() with a string of "0W".  Supports input
          conditioning.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpGreyRGB(csIdxType csIdx);
      /** A grey-like color scheme with 3*#maxChanVal colors, [0,3*#maxChanVal-1].
          It is not a true grey, but most people can't tell when used with reasonable channel depths.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpGrey3x(csIdxType csIdx);
      /** A grey-like color scheme with 4*#maxChanVal colors, [0,4*#maxChanVal-1].
          It is not a true grey, but most people can't tell when used with reasonable channel depths.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpGrey4x(csIdxType csIdx);
      //@}

      /** @name Color Schemes: RGB Cube Diagional Ramps */
      //@{
      /** Color based upon a traversal of the diagonal of the color cube from cyan to red.
          This is the same as the saturation based HSL ramp joining the same two colors.  The result is just as if cmpRGBcolorRamp() had been called with string of
          "CR".  Provides about (#maxChanVal*1+1) unique colors.
          @param csIdx     An integer
          @return A reference to the current object. */
      colorTpl& setRGBcmpDiagRampCR(csIdxType csIdx);
      /** Color based upon a traversal of the diagonal of the color cube from magenta to green.
          This is the same as the saturation based HSL ramp joining the same two colors.  The result is just as if cmpRGBcolorRamp() had been called with string of
          "MG".  Provides about (#maxChanVal*1+1) unique colors.
          @param csIdx     An integer
          @return A reference to the current object. */
      colorTpl& setRGBcmpDiagRampMG(csIdxType csIdx);
      /** Color based upon a traversal of the diagonal of the color cube from yellow to blue.
          This is the same as the saturation based HSL ramp joining the same two colors.  The result is just as if cmpRGBcolorRamp() had been called with string of
          "YB".  Provides about (#maxChanVal*1+1) unique colors.
          @param csIdx     An integer
          @return A reference to the current object. */
      colorTpl& setRGBcmpDiagRampYB(csIdxType csIdx);
      //@}

      /** @name Color Schemes: RGB Constant Brightness Ramps */
      //@{
      /** Color based upon a color cycle around the cube with constant constant brightness of two.
          The result is just as if cmpRGBcolorRamp() had been called with string of "CMYC".  Provides about (#maxChanVal*3+1) unique colors.  Supports input
          conditioning.
          @param csIdx     An integer
          @return A reference to the current object. */
      colorTpl& setRGBcmpConstTwoRamp(csIdxType csIdx);
      /** Color based upon a color cycle around the cube with constant constant brightness of two.
          The result is just as if cmpRGBcolorRamp() had been called with string of "BRGB".  Provides about (#maxChanVal*3+1) unique colors.  Supports input
          conditioning.
          @param csIdx     An integer
          @return A reference to the current object. */
      colorTpl& setRGBcmpConstOneRamp(csIdxType csIdx);
      //@}

      /** @name Color Schemes: Classic RGB Ramps */
      //@{
      /** Same as setRGBcmpSumRampRGB
          @param csIdx An integer to convert to a color. 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpFireRamp(csIdxType csIdx);
      /** Color based upon the classical cold to hot ramp.
          This is the same as cmpRGBcolorRamp() with a corner list of "BCGYR" Provides (#maxChanVal*4+1) unique colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpColdToHot(csIdxType csIdx);
      /** Color based upon a modified version of the classical cold to hot ramp.
          This modified version corresponds to using cmpRGBcolorRamp() with a corner list of "WCBYR" -- i.e. it starts at white (ice), moves up to blue (cold),
          then yellow through red (hot).  Provides (#maxChanVal*4+1) unique colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpIceToWaterToHot(csIdxType csIdx);
      //@}

      /** @name Color Schemes: HSL Saturation Ramps */
      //@{
      /** Popular saturation based HSL color scheme extending from the center of the HSL color space to the red vertex.
          The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides #meanChanVal unique
          colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpRampGrey2R(csIdxType csIdx);
      /** Popular saturation HSL color scheme extending from the center of the HSL color space to the green vertex.
          The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides #meanChanVal unique
          colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpRampGrey2G(csIdxType csIdx);
      /** Popular saturation HSL color scheme extending from the center of the HSL color space to the blue vertex.
          The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides #meanChanVal unique
          colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpRampGrey2B(csIdxType csIdx);
      /** Popular saturation based HSL color scheme extending from the center of the HSL color space to the cyan vertex.
          The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides #meanChanVal unique
          colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpRampGrey2C(csIdxType csIdx);
      /** Popular saturation based HSL color scheme extending from the center of the HSL color space to the magenta vertex.
          The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides #meanChanVal unique
          colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpRampGrey2M(csIdxType csIdx);
      /** Popular saturation based HSL color scheme extending from the center of the HSL color space to the yellow vertex.
          The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides #meanChanVal unique
          colors.
          @param csIdx The integer to convert
          @return A reference to the current object.*/
      colorTpl& setRGBcmpRampGrey2Y(csIdxType csIdx);
      //@}

      /** @name Color Schemes: RGB Up-Down Ramps */
      //@{
      /** Converts an integer into a color based upon a color up-down ramp: Gg == Green Up and Green Down == cyan -> magenta.
          Provides #maxChanVal different colors.
          @param csIdx An integer
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpUpDownRampRg(csIdxType csIdx);
      /** Converts an integer into a color based upon a color up-down ramp: Rb == Red Up and Blue Down == cyan -> yellow.
          Provides #maxChanVal different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpUpDownRampRb(csIdxType csIdx);
      /** Converts an integer into a color based upon a color up-down ramp: Gr == Green Up and Red Down == magenta -> cyan.
          Provides #maxChanVal different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpUpDownRampGr(csIdxType csIdx);
      /** Converts an integer into a color based upon a color up-down ramp: Gb == Green Up and Blue Down == magenta -> yellow.
          Provides #maxChanVal different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpUpDownRampGb(csIdxType csIdx);
      /** Converts an integer into a color based upon a color up-down ramp: Br == Blue Up and Red Down == yellow -> cyan.
          Provides #maxChanVal different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpUpDownRampBr(csIdxType csIdx);
      /** Converts an integer into a color based upon a color up-down ramp: Bg == Blue Up and Green Down == yellow -> magenta.
          Provides #maxChanVal different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpUpDownRampBg(csIdxType csIdx);
      //@}

      /** @name Color Schemes: RGB Sum Ramps */
      //@{
      /** Converts an integer into a color based upon a color sum-ramp: RGB == Black -> Red -> Yellow -> White.
          Same as cmpRGBcolorRamp() with a corner list of "0RYW".  Provides (3*#maxChanVal+1) different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpSumRampRGB(csIdxType csIdx);
      /** Converts an integer into a color based upon a color sum-ramp: BGR == Black -> Blue -> cyan -> White.
          Same as cmpRGBcolorRamp() with a corner list of "0BCW" Provides (3*#maxChanVal+1) different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpSumRampBGR(csIdxType csIdx);
      /** Converts an integer into a color based upon a color sum-ramp: GRB == Black -> Green -> yellow -> White.
          Same as cmpRGBcolorRamp() with a corner list of "0GYW" Provides (3*#maxChanVal+1) different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpSumRampGRB(csIdxType csIdx);
      /** Converts an integer into a color based upon a color sum-ramp: GBR == Black -> Green -> cyan -> White.
          Same as cmpRGBcolorRamp() with a corner list of "0GCW" Provides (3*#maxChanVal+1) different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpSumRampGBR(csIdxType csIdx);
      /** Converts an integer into a color based upon a color sum-ramp: BRG == Black -> Blue -> magenta -> White.
          Same as cmpRGBcolorRamp() with a corner list of "0BMW" Provides (3*#maxChanVal+1) different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpSumRampBRG(csIdxType csIdx);
      /** Converts an integer into a color based upon a color sum-ramp: RBG Black -> Red -> Magenta -> White.
          Same as cmpRGBcolorRamp() with a corner list of "0RMW".  Provides (3*#maxChanVal+1) different colors.
          @param csIdx An integer 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpSumRampRBG(csIdxType csIdx);
      //@}

      /** @name Binary, Threshold Color Schemes */
      //@{
      /** Converts an integer into a color based upon a binary color ramp -- red if the integer is less than the threshold and green otherwise.
          @param csIdx     An integer
          @param threshold The threshold 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpBinaryColorRampRG(csIdxType csIdx, csIdxType threshold);
      /** Converts an integer into a color based upon a binary color ramp -- red if the integer is less than the threshold and blue otherwise.
          @param csIdx     An integer
          @param threshold The threshold 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpBinaryColorRampRB(csIdxType csIdx, csIdxType threshold);
      /** Converts an integer into a color based upon a binary color ramp -- green if the integer is less than the threshold and red otherwise.
          @param csIdx     An integer
          @param threshold The threshold 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpBinaryColorRampGR(csIdxType csIdx, csIdxType threshold);
      /** Converts an integer into a color based upon a binary color ramp -- green if the integer is less than the threshold and blue otherwise.
          @param csIdx     An integer
          @param threshold The threshold 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpBinaryColorRampGB(csIdxType csIdx, csIdxType threshold);
      /** Converts an integer into a color based upon a binary color ramp -- blue if the integer is less than the threshold and red otherwise.
          @param csIdx     An integer
          @param threshold The threshold 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpBinaryColorRampBR(csIdxType csIdx, csIdxType threshold);
      /** Converts an integer into a color based upon a binary color ramp -- blue if the integer is less than the threshold and green otherwise.
          @param csIdx     An integer
          @param threshold The threshold 
          @return Returns a reference to the current color object. */
      colorTpl& setRGBcmpBinaryColorRampBG(csIdxType csIdx, csIdxType threshold);
      //@}

      /** @name Color Ramps, Gradients, Interpolation, Binary Thresholds.
          Members in this section form the computational foundation for many of the named color schemes found in this class. */
      //@{
      /** Convert a double to a color value based upon a color ramp passing through the given sequence of corner colors at the given anchor points.
          The value of this function at \a aDouble equal to \a anchor[i] will be \a colors[i].  This is an extremely general function that is capable of
          replicating many of the more precise color ramp sequence functions in this library.  The only defects are the lack of bit level precision and the
          poor performance -- both due to the use of floating point arithmetic.  Note this function operates correctly with any channel type and with an
          arbitrary number of channels -- it is NOT limited to RGB colors or RGB color corners for anchors.
          @param aDouble The value to convert
          @param anchors Doubles for which color equals the corresponding corner.
          @param colors  A vector  of colors to use
          @return A reference to this object */
      colorTpl& cmpColorRamp(double aDouble, std::vector<double> const& anchors, std::vector<colorType> const& colors);
      /** Convert a double to a color value based upon a color ramp passing through the given sequence of corner colors.
          The value of this function at \a aDouble 0.0 and 1.0 will be colors.front and colors.back respectively.  Between these extremes the color
          will be linearly interpolated across the colors in the colors vector.
          @param aDouble The value to convert
          @param colors  A vector of colors to use
          @return A reference to this object */
      colorTpl& cmpColorRamp(double aDouble, std::vector<colorType> const& colors);
      /** This is simply a version of cmpRGBcolorRamp() that computes the length of the final argument as a C-string.
          Unlike the version of cmpRGBcolorRamp() specifying numColors, this one requires the final argument to be a real C-string -- i.e. it must have a
          terminating NULL.  Note this function uses RGB corner colors as anchors, and is thus designed to work with RGB colors.  This function is the primary
          workhorse behind many of the "cmp" color schemes in this library.
          @param csIdx The value to convert
          @param cornerColors Characters specifying color (as used by setColor)
          @return A reference to this object */
      colorTpl& cmpRGBcolorRamp(csIdxType csIdx, const char *cornerColors);
      /** Color value based upon a color ramp passing through the given sequence of corner colors at equal intervals along [0, (#maxChanVal*(numColors-1)+1)].
          At 0, the color will be the first specified color.  At (#maxChanVal*(numColors-1)+1) it will be the last color specified color.  This function is
          similar to the one taking doubles. This version doesn't allow for the specification of anchor points, but uses precise integer arithmetic.  With
          this function it is possible to precisely duplicate many of the integer ramp color scheme functions.  This function supports input conditioning.
          cornerColors need not be a real C-string -- i.e. no need for an terminating NULL.  Note this function uses RGB corner colors as anchors, and is thus
          designed to work with RGB colors.  This function is the primary workhorse behind many of the "cmp" color schemes in this library.
          @param csIdx The value to convert
          @param numColors The number of colors
          @param cornerColors Characters specifying color (as used by setColor)
          @return A reference to this object */
      colorTpl& cmpRGBcolorRamp(csIdxType csIdx, csIdxType numColors, const char *cornerColors);
      /** Set the current color to a value linearly interpolated between the two given colors.  When \a aDouble is 0, the color is col1.
          When \a aDouble is 1 the new value is col2.  This method interpolates all channels without any color space conversions and as few type conversions as
          possible.
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      colorTpl& interplColors(double aDouble, colorArgType col1, colorArgType col2);
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
      colorTpl& interplColorSpace(colorSpaceEnum space, double aDouble, colorArgType col1, colorArgType col2);
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
      colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, channelArithFltType w4, colorArgType col1, colorArgType col2, colorArgType col3, colorArgType col4);
      /** @overload */
      colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, colorArgType col1, colorArgType col2, colorArgType col3);
      /** @overload */
      colorTpl& wMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2);
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
      colorTpl& uMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, colorArgType col1, colorArgType col2, colorArgType col3, colorArgType col4);
      /** @overload */
      colorTpl& uMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2, colorArgType col3);
      /** @overload */
      colorTpl& uMean(channelArithFltType w1, colorArgType col1, colorArgType col2);
      //@}

      /** @name Logical Operators */
      //@{
      /** Performs a logical OR with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmOr(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmOr(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** Performs a logical NOR with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmNor(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmNor(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** Performs a logical AND with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmAnd(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmAnd(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** Performs a logical NAND with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmNand(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmNand(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** Performs a logical EXCLUSIVE OR (XOR) with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmXor(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmXor(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** Performs a logical NOT EXCLUSIVE OR (NXOR) with the current object and the given object and places the value in the current object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmNxor(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmNxor(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** Performs logical (bit-wise) negation of current object.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmNot(void) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmNot(void) requires (std::floating_point<clrChanT>);
      //@}

      /** @name Arithmetic Operators */
      //@{
      /** Computes the square of the difference for each channel between the given color and the current color object.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmSqDiff(colorArgType aCol);
      /** Computes the absolute value of the difference for each channel between the given color and the current color object.
          @param aCol The color to use in the computation.
          @return Returns the absolute value of the difference for each channel.*/
      colorTpl& tfrmAbsDiff(colorArgType aCol);
      /** Computes the arithmetic sum of the given color and the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmAdd(colorArgType aCol);
      /** Computes the arithmetic division of the current color by the given color.
          No check is made for division by zero.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmDiv(colorArgType aCol);
      /** Computes the arithmetic product of the given color and the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMult(colorArgType aCol);
      /** Computes the product of the given color and the current one.
          If the result of a multiplication is too large, it will be set to the maximum component value.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMultClp(colorArgType aCol);
      /** Computes the component wise scaled sign of the difference between the current color and the given one.
          As an example of the computation, the red component of the current color is computed like this:
          - R=#minChanVal  iff(R<color.R)
          - R=#meanChanVal iff(R==color.R)
          - R=#maxChanVal  iff(R>color.R)
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& ScaleSignDiff(colorArgType aCol);
      /** Computes the arithmetic difference of the given color from the current one.
          If the result a differences is negative, then that component will be set to zero.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmDiffClp(colorArgType aCol);
      /** Computes the negative of the arithmetic difference of the given color from the current one.
          This is the same as the arithmetic difference of the current color from the given color.  If the result a differences is negative, then that
          component will be set to zero.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmNegDiffClp(colorArgType aCol);
      /** Computes the arithmetic sum of the given color from the current one.
          If the result of a sum is greater than the maximum value, then that component will be set to the maximum value.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmAddClp(colorArgType aCol);
      /** Computes the arithmetic sum of the given color from the current one, then divids by dcolor.
          If the result of a sum is greater than the maximum value, then that component will be set to the maximum value.
          No check is made for division by zero.
          @param aCol The color to use for initial add.
          @param dCol The color to use for final division.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmAddDivClp(colorArgType aCol, colorArgType dCol);
      /** Computes the arithmetic difference of the given color from the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmDiff(colorArgType aCol);
      /** Computes the arithmetic modulus of the current by the given one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMod(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmMod(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** Transforms the color: r=#maxChanVal-r, g=#maxChanVal-r, and b=#maxChanVal-b
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmInvert();
      //@}

      /** @name Named Operators */
      //@{
      /** Adds 1.0 and takes the natural logarithm of each channel.
          Floating point Numbers re used for intermediate values and the result cast to a colorChanType at the end.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmLn();
      /** Linearly interpolate between the current color and the given color (at a point scaled the unit interval).
          If \a aDouble is 0, then the current color will not change.  If \a aDouble is 1, then the current color will be tooCol.
          @param aDouble Distance from the current color (on a unit interval)
          @param tooCol  The color we are interpolating with.
          @return Returns a reference to the current color object.*/
      colorTpl& interplColors(double aDouble, colorArgType tooCol);
      /** Copies the given argument into the current color object.
          Scan as copy() -- just with a name more suited to transformation code.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmCopy(colorArgType aCol);
      /** Makes the current color the maximum of the current color or the given color.
          Colors are ordered by intensity (thus the 'I' in the name)
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMaxI(colorArgType aCol);
      /** Makes the current color the minimum of the current color or the given color.
          Colors are ordered by intensity (thus the 'I' in the name)
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMinI(colorArgType aCol);
      /** Makes each component of the current color the maximum of that component and the corresponding component of the given color.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMax(colorArgType aCol);
      /** Makes each component of the current color the minimum of that component and the corresponding component of the given color.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMin(colorArgType aCol);
      /** The Shift Left Transform modifies the current color.
          @param aCol Number of bits to shift left
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmShiftL(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmShiftL(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** The Shift Right Transform modifies the current color.
          @param aCol How many bits to shift.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmShiftR(colorArgType aCol) requires (std::integral<clrChanT>);
      /** Template specialization member function differing from the above function only in supported template conditions. */
      colorTpl& tfrmShiftR(colorArgType aCol) requires (std::floating_point<clrChanT>);
      /** The Saw Transform modifies the current color: R=R iff(ra<=R<=rb), G=G iff(ga<=G<=gb), B=B iff(ba<=B<=bb).
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmSaw(colorArgType lowCol, colorArgType highCol);
      /** The Saw Transform modifies the current color: R=#maxChanVal iff(ra<=R<=rb), G=#maxChanVal iff(ga<=G<=gb), B=#maxChanVal iff(ba<=B<=bb)
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmStep(colorArgType lowCol, colorArgType highCol);
      /** The DiracTot (total) Transform modifies the current color: R=MAX,G=MAX, B=MAX iff ((R==aCol.R)&&(G==aCol.G)&&(B==aCol.B)).
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmDiracTot(colorArgType aCol);
      /** The Dirac Transform modifies the current color: R=MAX iff(R==aCol.R), G=MAX iff(G==aCol.G), B=MAX iff(B==aCol.B).
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmDirac(colorArgType aCol);
      /** The Fuzzy Dirac Transform modifies the current color: R=MAX iff(|R-ctrCol.R|<=radCol.R), G=MAX iff(|G-ctrCol.G|<=radCol.G), B=MAX iff(|B-ctrCol.B|<=radCol.B).
          @param ctrCol Center Color
          @param radCol Radius Color
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmFuzzyDirac(colorArgType ctrCol, colorArgType radCol);
      /** Computes the arithmetic mean of the given color and the current one.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmMean(colorArgType aCol);
      /** Computes the geometric mean of the given color and the current one.
          Floating point Numbers re used for intermediate values and the result cast to a colorChanType at the end.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmGmean(colorArgType aCol);
      /** Computes the clipped  geometric mean of the given color and the current one.
          Floating point Numbers re used for intermediate values and the result cast to a colorChanType at the end.
          @param aCol The color to use in the computation.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmGmeanClp(colorArgType aCol);
      /** Transform the current color by rendering it into a true grey via the same method used by the rgbLuminance() function.
          Note, the rgbLuminance() function is NOT used internally within this function for performance reasons.  This function will do the best job it can
          within the current color depth.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmGreyScale(void);
      //@}

      /** @name Color Reduction Transformations */
      //@{
      /** The 216 Palate Web Safe Transform modifies the current color into the closest web safe color from the 216 color web safe pallet.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmWebSafe216();
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Protanopia might see.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmWebSafePro216();
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Deutanopia might see.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmWebSafeDeu216();
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Tritanoptia might see.
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmWebSafeTri216();
      //@}

      /** @name Alternate Color Space Stuff */
      //@{
      /** Compute channels for given color space coordinates for the current color.
          Note RGB returns float RGB normalized to 1.0.
          @param space The color space to convert to
          @return An RGB color with double channels. */
      colorTpl<double, 3> rgb2colorSpace(colorSpaceEnum space);
      /** Compute channels for given color space coordinates for the current color.
          Note RGB returns float RGB normalized to 1.0.
          @param space The color space to stringify
          @return A string representing the color space. */
      std::string colorSpaceToString(colorSpaceEnum space);
      //@}

      /** @name Color Transformation Functions */
      //@{
      /** The Linear Grey Level Scale transform modifies the current color such that: C_n=c*C_n+b.
          This function transforms all channels --- not just RGBA.
          @param c The "contrast" value
          @param b The "brightness" value
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmLinearGreyLevelScale(double c, double b);
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
      colorTpl& tfrmLinearGreyLevelScale(colorArgType from1, colorArgType from2, colorArgType to1, colorArgType to2);
      /** The Linear Grey Level Scale transform modifies the current color such that: R=rc*R+rb, G=gc*G+gb, B=bc*B+bb.
          This function ONLY transforms the red, green, and blue channels.
          @param rc The "contrast" value for red
          @param rb The "brightness" value for red
          @param gc The "contrast" value for green
          @param gb The "brightness" value for green
          @param bc The "contrast" value for blue
          @param bb The "brightness" value for blue
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmLinearGreyLevelScale(double rc, double rb, double gc, double gb, double bc, double bb);
      /** The Standard Power Transform modifies the current color such that:
          R=#maxChanVal*(R/#maxChanVal)**p, G=#maxChanVal*(G/#maxChanVal)**p, B=#maxChanVal*(B/#maxChanVal)**p
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmStdPow(double p);
      /** The Standard Power Transform modifies the current color such that:
          R=#maxChanVal*(R/#maxChanVal)**rp, B=#maxChanVal*(B/#maxChanVal)**gp, B=#maxChanVal*(B/#maxChanVal)**bp
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmStdPow(double rp, double gp, double bp);
      /** The Standard Power Transform with p=2. The new color will be:
          R=#maxChanVal*(R/#maxChanVal)**2, G=#maxChanVal*(G/#maxChanVal)**2, B=#maxChanVal*(B/#maxChanVal)**2
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmStdPowSqr(void);
      /** The Standard Power Transform with p=1/2. The new color will be:
          R=#maxChanVal*(R/#maxChanVal)**(1/2), G=#maxChanVal*(G/#maxChanVal)**(1/2), B=#maxChanVal*(B/#maxChanVal)**(1/2)
          @return Returns a reference to the current color object.*/
      colorTpl& tfrmStdPowSqrt(void);
      //@}

      /** @name Mathematical Operations On Color(s)
          Members in this section produce non-color results. i.e. They consume the current, and possibly other colors and arguments, to produce a non-color
          result. */
      //@{
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
      channelArithSDPType rgb2GreyDotProd(channelArithSDPType redWt, channelArithSDPType greenWt, channelArithSDPType blueWt);
      /** Compute the luminance of the current color via the definition given in the ITU-R Recommendation BT.709.
          The output value will be between 0 and 1, and is given by: (0.2126*R+0.7152*G+0.0722*B)/#maxChanVal.
          @return The luminance for the current object. */
      channelArithFltType rgbLuminance(void);
      /** Compute the unscaled intensity (sum of the first three components) of the current color
          @return The unscaled intensity for the current object. */
      channelArithSPType rgbSumIntensity(void);
      /** Compute the sum of the components.
          @return Sum of components. */
      channelArithSPType chanSum(void);
      /** Compute the scaled intensity (sum of the first three components divided by the maximum intensity possible) of the current color
          @return The scaled intensity for the current object. */
      channelArithFltType rgbScaledIntensity(void);
      /** Returns the value of the largest component.
          @return The value of the largest color component currently stored.*/
      clrChanT getMaxC();
      /** Returns the value of the smallest component.
          @return The value of the smallest color component currently stored.*/
      clrChanT getMinC();
      /** Returns the value of the largest component from R, G, and B. This function is highly optimized.
          @return The value of the largest color component.*/
      clrChanT getMaxRGB();
      /** Returns the value of the smallest component from R, G, and B. This function is highly optimized.
          @return The value of the smallest color component.*/
      clrChanT getMinRGB();
      /** Compute the dot product between the current color and the given color. i.e. c1.r*c2.r+c1.g*c2.g+...
          @param aColor the given color
          @return Returns dot product.*/
      channelArithSPType dotProd(colorArgType aColor);
      /** Distance between current color and given one (sum squares) Returns the sum of the squares of the differences of the components.  Returns |c1-c2|^2
          @param aColor The given color
          @return Returns distance squared.*/
      channelArithSPType distP2sq(colorArgType aColor);
      /** Distance between current color and given one (absolute difference) Returns sum of the absolute value of the differences of the components
          @param aColor the given color
          @return Returns absolute distance squared.*/
      channelArithSPType distAbs(colorArgType aColor);
      /** Returns non-zero if the given color is logically the same as the current color.
          @return non-zero if the given color is logically the same as the current color*/
      bool isEqual(colorArgType aColor);
      /** Like isEual(), but only checks the R, G, & B channels.
          @return non-zero if the given RGB color is the same as the current color*/
      bool isEqualRGB(colorArgType aColor);
      /** Returns non-zero if the given color is logically NOT the same as the current color.
          @return non-zero if the given color is logically the same as the current color*/
      bool isNotEqual(colorArgType aColor);
      /** Returns non-zero if the given color is black (all componnets are zero)
          @return non-zero if the given color is black (all componnets are zero) */
      bool isBlack();
      /** LIke isBlack(), but only checks the R, G, & B channels
          @return non-zero if the given color is black (R, G, & B are  are zero) */
      bool isBlackRGB();
      //@}

      /** @name Channel Clipping Functions */
      //@{
      /** Clamp a value on the top end such that it will fit into a clrChanT type. Input values larger than the maximum channel value are mapped to the maximum
          channel value.  Values less than the minimum (0) are not clamped.
          @param arithValue The value to clamp */
      template <typename iT> clrChanT clipTop(iT arithValue);
      /** Clamp a value on the bottom end such that it will fit into a clrChanT type. Input values less than the minimum (0), are mapped to 0.  Note values
          greater than the maximum channel value are NOT clamped.
          @param arithValue The value to clam    p */
      template <typename iT> clrChanT clipBot(iT arithValue);
      /** Clamp a value such that it will fit into a clrChanT type. Input values less than zero are mapped to zero, and input values larger than the maximum
          channel value are mapped to the maximum q channel value.
          @param arithValue The value to clamp */
      template <typename iT> clrChanT clipAll(iT arithValue);
      //@}

  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl() {
    // We don't do anything as this throws away resources.  If the color needs cleared, we have a method for that.  This is consistent with the tradition of
    // C/C++ not initializing concrete types like int and float.
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(clrChanT cVal) {
    setChans(cVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(clrChanT c1, clrChanT c2) {
    if (numChan > 2)
      setChansToMin();
    setChans(c1, c2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(clrChanT c1, clrChanT c2, clrChanT c3) {
    if (numChan > 3)
      setChansToMin();
    setChans(c1, c2, c3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4) {
    if (numChan > 4)
      setChansToMin();
    setChans(c1, c2, c3, c4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* copy constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(const colorType& aColor) {
    /* Saftey: Yep.  Sometimes the compiler might not be able to tell if we have initalized the color object -- some of the color set code is too complex.
       Sometimes we might even want to copy an unitilzied color -- sometimes it makes the code easier to write.*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    if(goodMask)
      theColor.theInt = aColor.theColor.theInt;
    else
      std::copy_n(aColor.theColor.thePartsA, numChan, theColor.thePartsA);
#pragma GCC diagnostic pop
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(std::string colorString) {
    setColorFromString(colorString);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(const char* colorCString) {
    setColorFromString(std::string(colorCString));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::colorTpl(cornerColorEnum cornerColor) {
    setToCorner(cornerColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::~colorTpl() {
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getC0() const {
    return theColor.thePartsA[0];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getC1() const requires (numChan>1) {
    return theColor.thePartsA[1];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getC2() const requires (numChan>2) {
    return theColor.thePartsA[2];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getC3() const requires (numChan>3) {
      return theColor.thePartsA[3];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC0(clrChanT cVal) {
    /* Performance: numChan is known at compile time, so the optimizer will produce an assignment or no code at all -- i.e. the test for numChan is done at
       compile time only, and imposes zero overhead at runtime.  */
    /* Performance: The array assignment here gets optimized because the index is known at compile time.  It's just as fast as accessing a member of a union
       for example.  */
    /* Useablity: We could do this with a template, but that means we need ".template set" syntax in some cases.  That's just too uguly. */
    theColor.thePartsA[0] = cVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC1(clrChanT cVal) requires (numChan>1) {
    theColor.thePartsA[1] = cVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC2(clrChanT cVal) requires (numChan>2) {
    theColor.thePartsA[2] = cVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC3(clrChanT cVal) requires (numChan>3) {
    theColor.thePartsA[3] = cVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getChan(int chan) const {
    if((chan >= 0) && (chan < numChan)) [[likely]]
      return theColor.thePartsA[chan];
    else
      return minChanVal;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getChanNC(int chan) const {
    return theColor.thePartsA[chan];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline double
  colorTpl<clrChanT, numChan>::getC0_dbl() const {
    return convertChanToDouble(getC0());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline double
  colorTpl<clrChanT, numChan>::getC1_dbl() const {
    /* Requires: Inherits numChan>1 from getC1. */
    return convertChanToDouble(getC1());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline double
  colorTpl<clrChanT, numChan>::getC2_dbl() const {
    /* Requires: Inherits numChan>2 from getC2. */
    return convertChanToDouble(getC2());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline double
  colorTpl<clrChanT, numChan>::getC3_dbl() const {
    /* Requires: Inherits numChan>3 from getC3. */
    return convertChanToDouble(getC3());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline double
  colorTpl<clrChanT, numChan>::getChan_dbl(int chan) const {
    if((chan >= 0) && (chan < numChan)) [[likely]]
      return convertChanToDouble(getChanNC(chan));
    else
      return 0.0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline uint8_t
  colorTpl<clrChanT, numChan>::getC0_byte() const {
    return convertChanToByte(getC0());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline uint8_t
  colorTpl<clrChanT, numChan>::getC1_byte() const {
    /* Requires: Inherits numChan>1 from getC1. */
    return convertChanToByte(getC1());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline uint8_t
  colorTpl<clrChanT, numChan>::getC2_byte() const {
    /* Requires: Inherits numChan>2 from getC2. */
    return convertChanToByte(getC2());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline uint8_t
  colorTpl<clrChanT, numChan>::getC3_byte() const {
    /* Requires: Inherits numChan>3 from getC3. */
    return convertChanToByte(getC2());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline uint8_t
  colorTpl<clrChanT, numChan>::getChan_byte(int chan) const {
    if((chan >= 0) && (chan < numChan)) [[likely]]
      return convertChanToByte(getChanNC(chan));
    else
      return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getMaxC() {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getMinC() {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getMaxRGB() {
    /* Requires: Inherits numChan>2 from getC2. */
    return mjr::max3(getC0(), getC1(), getC2());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::getMinRGB() {
    /* Requires: Inherits numChan>2 from getC2. */
    return mjr::min3(getC0(), getC1(), getC2());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChanNC(int chan, clrChanT cVal) {
    theColor.thePartsA[chan] = cVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChan(int chan, clrChanT cVal) {
    if((chan >= 0) && (chan < numChan)) [[likely]]
      setChanNC(chan, cVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChanToMax(int chan) {
    if((chan >= 0) && (chan < numChan)) [[likely]]
      theColor.thePartsA[chan] = maxChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChanToMin(int chan) {
    if((chan >= 0) && (chan < numChan)) [[likely]]
      theColor.thePartsA[chan] = minChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChan_dbl(int chan, double cVal) {
    /* Performance: We expect chan to be in range most of the time.  If it is not, we waste time here computing the channel value.. */
    return setChan(chan, convertDoubleToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC0_dbl(double cVal) {
    return setC0(convertDoubleToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC1_dbl(double cVal) {
    return setC1(convertDoubleToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC2_dbl(double cVal) {
    return setC2(convertDoubleToChan(cVal));
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC3_dbl(double cVal) {
    return setC3(convertDoubleToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_dbl(double cVal) {
    return setChans(convertDoubleToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_dbl(double c1, double c2, double c3, double c4) {
    return setChans(convertDoubleToChan(c1), convertDoubleToChan(c2), convertDoubleToChan(c3), convertDoubleToChan(c4));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_dbl(double c1, double c2, double c3) {
    return setChans(convertDoubleToChan(c1), convertDoubleToChan(c2), convertDoubleToChan(c3));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_dbl(double c1, double c2) {
    return setChans(convertDoubleToChan(c1), convertDoubleToChan(c2));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::convertDoubleToChan(double cVal) const {
  /* Performance: Not all compilers recognize multiplication by 1.0 as a NOOP.  Hence the if-then below. */
    if(chanIsInt)
      return static_cast<clrChanT>(cVal * maxChanVal);
    else
      return static_cast<clrChanT>(cVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline double
  colorTpl<clrChanT, numChan>::convertChanToDouble(clrChanT cVal) const {
    if(chanIsInt)
      return static_cast<double>(cVal) / static_cast<double>(maxChanVal);
    else
      return static_cast<double>(cVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline uint8_t
  colorTpl<clrChanT, numChan>::convertChanToByte(clrChanT cVal) const requires (std::floating_point<clrChanT>) {
    return static_cast<uint8_t>(cVal * static_cast<clrChanT>(255) / maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline uint8_t
  colorTpl<clrChanT, numChan>::convertChanToByte(clrChanT cVal) const requires std::integral<clrChanT> {
    /* Performance: A good compiler *should* recgonize the case when bitsPerChan-8==0, and render this function an NOOP.  Some don't.  Hence the if-then
       below. */
    if(chanIsByte)
      return cVal;
    else
      return static_cast<uint8_t>(cVal >> (bitsPerChan-8));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::convertByteToChan(uint8_t cVal) const requires (std::integral<clrChanT>) {
    if(chanIsByte)
      return cVal;
    else
      return (static_cast<clrChanT>(cVal) << (bitsPerChan-8));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::convertByteToChan(uint8_t cVal) const requires (std::floating_point<clrChanT>) {
    return (static_cast<clrChanT>(cVal) / static_cast<clrChanT>(255));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChan_byte(int chan, uint8_t cVal) {
    /* Performance: We expect chan to be in range most of the time.  If it is not, we waste time here computing the channel value.. */
    /* Performance: When chanIsByte, convertByteToChan is a NOOP.  As it's inline, this leads to zero overhead for the chanIsByte case. */
    return setChan(chan, convertByteToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC0_byte(uint8_t cVal) {
    return setC0(convertByteToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC1_byte(uint8_t cVal) {
    return setC1(convertByteToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC2_byte(uint8_t cVal) {
    return setC2(convertByteToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setC3_byte(uint8_t cVal) {
    return setC3(convertByteToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_byte(uint8_t cVal) {
    return setChans(convertByteToChan(cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4) {
    setChans(convertByteToChan(c1), convertByteToChan(c2), convertByteToChan(c3), convertByteToChan(c4));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_byte(uint8_t c1, uint8_t c2, uint8_t c3) {
    setChans(convertByteToChan(c1), convertByteToChan(c2), convertByteToChan(c3));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans_byte(uint8_t c1, uint8_t c2) {
    setChans(convertByteToChan(c1), convertByteToChan(c2));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::ScaleSignDiff(colorArgType aCol) {
    for(int i=0; i<numChan; i++) {
      if(getChanNC(i) < aCol.getChanNC(i)) {
        theColor.thePartsA[i] = minChanVal;
      } else if(getChanNC(i) > aCol.getChanNC(i)) {
        theColor.thePartsA[i] = maxChanVal;
      } else {
        theColor.thePartsA[i] = meanChanVal;
      }
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmLn() {
    /* Performance: Even if the compiler fails to unroll this loop, the runtime is dominated by the double computations. */
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = std::log(1.0 + static_cast<double>(getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmCopy(colorArgType aCol) {
    return copy(aCol);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmOr(colorArgType aCol) requires (std::integral<clrChanT>) {
    if(goodMask)
      theColor.theInt |= aCol.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] |= aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmOr(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    /* Performance: Yep.  Sometimes floating point colors get a goodMask. */
    if(goodMask)
      theColor.theInt |= aCol.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) | std::bit_cast<channelArithLogType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNor(colorArgType aCol) requires (std::integral<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt | aCol.theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = ~(getChanNC(i) | aCol.getChanNC(i));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNor(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt | aCol.theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i)) | std::bit_cast<channelArithLogType>(aCol.getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmAnd(colorArgType aCol) requires (std::integral<clrChanT>) {
    if(goodMask)
      theColor.theInt &= aCol.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] &= aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmAnd(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    if(goodMask)
      theColor.theInt &= aCol.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) & std::bit_cast<channelArithLogType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNand(colorArgType aCol) requires (std::integral<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt & aCol.theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = ~(getChanNC(i) & aCol.getChanNC(i));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNand(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt & aCol.theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i)) & std::bit_cast<channelArithLogType>(aCol.getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmXor(colorArgType aCol) requires (std::integral<clrChanT>) {
    if(goodMask)
      theColor.theInt ^= aCol.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] ^= aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmXor(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    if(goodMask)
      theColor.theInt ^= aCol.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) ^ std::bit_cast<channelArithLogType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNxor(colorArgType aCol) requires (std::integral<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt ^ aCol.theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = ~(getChanNC(i) ^ aCol.getChanNC(i));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNxor(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt ^ aCol.theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i)) ^ std::bit_cast<channelArithLogType>(aCol.getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNot(void) requires (std::integral<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = ~(getChanNC(i));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNot(void) requires (std::floating_point<clrChanT>) {
    if(goodMask)
      theColor.theInt = ~(theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = std::bit_cast<clrChanT>(~(std::bit_cast<channelArithLogType>(getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmShiftL(colorArgType aCol) requires (std::integral<clrChanT>) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = getChanNC(i) << aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmShiftL(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    for(int i=0; i<numChan; i++)
    /* tricky: We are casting the color component being shifted bitwise to a big int; however, we are casting the shifting quantity via a static_cast. */
      theColor.thePartsA[i] = std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) <<
                                                      static_cast<uint64_t>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmShiftR(colorArgType aCol) requires (std::integral<clrChanT>) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = getChanNC(i) >> aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmShiftR(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = std::bit_cast<clrChanT>(std::bit_cast<channelArithLogType>(getChanNC(i)) >>
                                                      static_cast<uint64_t>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMultClp(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = clipTop(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmGmeanClp(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = clipTop(static_cast<channelArithSPType>(std::sqrt(static_cast<double>(getChanNC(i))   *
                                                                                static_cast<double>(aCol.getChanNC(i)))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmAddClp(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = clipTop(static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmAddDivClp(colorArgType aCol, colorArgType dCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = clipTop((static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))) /
                                      static_cast<channelArithSPType>(dCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmDiffClp(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = clipBot(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmNegDiffClp(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = clipBot(static_cast<channelArithDType>(aCol.getChanNC(i)) - static_cast<channelArithDType>(getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmAbsDiff(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(std::abs(static_cast<channelArithDType>(getChanNC(i))   -
                                                             static_cast<channelArithDType>(aCol.getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmSqDiff(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>((static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aCol.getChanNC(i)))   *
                                                    (static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aCol.getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMax(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      if(getChanNC(i) < aCol.getChanNC(i))
        theColor.thePartsA[i] = aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMin(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      if(getChanNC(i) > aCol.getChanNC(i))
        theColor.thePartsA[i] = aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmAdd(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmDiv(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) / static_cast<channelArithSPType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMult(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmGmean(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(std::sqrt(static_cast<double>(getChanNC(i)) * static_cast<double>(aCol.getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMean(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>((static_cast<channelArithSPType>(getChanNC(i)) + static_cast<channelArithSPType>(aCol.getChanNC(i))) / 2);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmDiff(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aCol.getChanNC(i)));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMod(colorArgType aCol) requires (std::integral<clrChanT>) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = getChanNC(i) % aCol.getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMod(colorArgType aCol) requires (std::floating_point<clrChanT>) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(std::fmod(static_cast<double>(getChanNC(i)), static_cast<double>(aCol.getChanNC(i))));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMaxI(colorArgType aCol) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmMinI(colorArgType aCol) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(clrChanT cVal) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = cVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(clrChanT c1, clrChanT c2) {
    /* Requires: Inherits numChan>1 from getC1. */
    /* Safety: We always have at least 1 channel, so the call to setC2 might seem unsafe here.  The setC2 method has a check on numChan. */
    /* Performance: Calling setC1 & setC2 seems like a waste here.  These are both inline functions, and modern compilers will inline them well.  Note that
       the safety check in setC1() when placed inline here will be eliminated by the optimizer because numChan is known at compile time.  The result is that
       we get an array assignment for C2 if we have enough channels, and nothing at all if the channel doesn't exist. */
    setC0(c1);
    setC1(c2);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(clrChanT c1, clrChanT c2, clrChanT c3) {
    /* Requires: Inherits numChan>2 from getC2. */
    setC0(c1);
    setC1(c2);
    setC2(c3);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(clrChanT c1, clrChanT c2, clrChanT c3, clrChanT c4) {
    /* Requires: Inherits numChan>3 from getC3. */
    setC0(c1);
    setC1(c2);
    setC2(c3);
    setC3(c4);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(std::tuple<clrChanT, clrChanT, clrChanT> chanValues) {
    /* Requires: Inherits numChan>2 from getC2. */
    setC0(std::get<0>(chanValues));
    setC1(std::get<1>(chanValues));
    setC2(std::get<2>(chanValues));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(std::tuple<clrChanT, clrChanT, clrChanT, clrChanT> chanValues) {
    /* Requires: Inherits numChan>3 from getC3. */
    setC0(std::get<0>(chanValues));
    setC1(std::get<1>(chanValues));
    setC2(std::get<2>(chanValues));
    setC3(std::get<3>(chanValues));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>::maskType
  colorTpl<clrChanT, numChan>::getMask() const {
    if(goodMask) 
      return theColor.theInt;
    else
      return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline bool
  colorTpl<clrChanT, numChan>::setMask(maskType aMask) {
    if(goodMask) {
      theColor.theInt = aMask;
      return true;
    } else 
      return false;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::copy(colorArgType aCol) {

    // if( !(setMask(aCol.getMask())))
    //   for(int i=0; i<numChan; i++)
    //     theColor.thePartsA[i] = aCol.getChanNC(i);

    if(goodMask)
      theColor.theInt = aCol.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = aCol.getChanNC(i);

    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(std::string colorHexString) {
    std::string::size_type sizeOfString = colorHexString.size();
    std::string::size_type digitsPerChan = bitsPerChan / 4;
    if (sizeOfString > 0) {  // Not empty
      if (colorHexString[0] == '#') { // Starts with hash
        if (0 == ((sizeOfString-1) % digitsPerChan)) { // Has correct number of digits
          if (std::string::npos == colorHexString.find_first_not_of("0123456789abcdefABCDEF", 1)) { // All hex digits after the pound
            std::string::size_type numChanGiven = (sizeOfString-1) / digitsPerChan;
            std::string::size_type numToSet     = numChanGiven;
            if (numChan < numChanGiven)
              numToSet = numChan;
            clrChanT curCmp;
            std::string curHexStr(digitsPerChan, 1);
            for(std::string::size_type i=0; i<numToSet; i++) {
              for(std::string::size_type j=0; j<digitsPerChan; j++) {
                curHexStr[j] = colorHexString[1+j+digitsPerChan*i];
              }
              if (sizeof(unsigned long) >= sizeof(clrChanT))
                curCmp = static_cast<clrChanT>( std::stoul(curHexStr, nullptr, 16));
              else
                curCmp = static_cast<clrChanT>(std::stoull(curHexStr, nullptr, 16));
              setChan(static_cast<int>(i), curCmp);
            }
          }
        }
      }
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromLogPackIntABGR(uint32_t anInt) {
    /* Requires: Inherits numChan>2 from setC2. */
    setC0_byte(0xFF & anInt); anInt = anInt >> 8;
    setC1_byte(0xFF & anInt); anInt = anInt >> 8;
    setC2_byte(0xFF & anInt); anInt = anInt >> 8;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromLogPackIntARGB(uint32_t anInt) {
    /* Requires: Inherits numChan>2 from setC2. */
    setC2_byte(0xFF & anInt); anInt = anInt >> 8;
    setC1_byte(0xFF & anInt); anInt = anInt >> 8;
    setC0_byte(0xFF & anInt); anInt = anInt >> 8;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx) {
    /* Requires: Inherits numChan>2 from setC2. */
    uint8_t *curByte = (uint8_t *)(&anInt);
    setC0_byte(curByte[rIdx]);
    setC1_byte(curByte[gIdx]);
    setC2_byte(curByte[bIdx]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBAfromLogPackIntABGR(uint32_t anInt) {
    /* Requires: Inherits numChan>3 from setC3. */
    setC0_byte(0xFF & anInt); anInt = anInt >> 8;
    setC1_byte(0xFF & anInt); anInt = anInt >> 8;
    setC2_byte(0xFF & anInt); anInt = anInt >> 8;
    setC3_byte(0xFF & anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBAfromLogPackIntARGB(uint32_t anInt) {
    /* Requires: Inherits numChan>3 from setC3. */
    setC2_byte(0xFF & anInt); anInt = anInt >> 8;
    setC1_byte(0xFF & anInt); anInt = anInt >> 8;
    setC0_byte(0xFF & anInt); anInt = anInt >> 8;
    setC3_byte(0xFF & anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBAfromLogPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBAfromPackIntGen(uint32_t anInt, uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx) {
    /* Requires: Inherits numChan>3 from setC3. */
    uint8_t *curByte = (uint8_t *)(&anInt);
    setC0_byte(curByte[rIdx]);
    setC1_byte(curByte[gIdx]);
    setC2_byte(curByte[bIdx]);
    setC3_byte(curByte[aIdx]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setChans(std::vector<clrChanT>& chanValues) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = chanValues[i];
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmLinearGreyLevelScale(double c, double b) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(c * static_cast<double>(getChanNC(i)) + b);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmLinearGreyLevelScale(colorArgType from1, colorArgType from2, colorArgType to1, colorArgType to2) {
    for(int i=0; i<numChan; i++) {
      double c = ( (static_cast<double>(to1.getChanNC(i))   - static_cast<double>(to2.getChanNC(i))) /
                   (static_cast<double>(from1.getChanNC(i)) - static_cast<double>(from2.getChanNC(i))) );
      double b = static_cast<double>(to1.getChanNC(i)) - c * static_cast<double>(from1.getChanNC(i));
      theColor.thePartsA[i] = static_cast<clrChanT>(c * getChanNC(i) + b);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmLinearGreyLevelScale(double rc, double rb, double gc, double gb, double bc, double bb) {
    /* Requires: Inherits numChan>3 from setC3 & getC3. */
    setC0(static_cast<clrChanT>(rc * static_cast<double>(theColor.getC0()) + rb));
    setC1(static_cast<clrChanT>(gc * static_cast<double>(theColor.getC1()) + gb));
    setC2(static_cast<clrChanT>(bc * static_cast<double>(theColor.getC2()) + bb));
    setC3(static_cast<clrChanT>(bc * static_cast<double>(theColor.getC3()) + bb));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmGreyScale(void) {
    /* Requires: Inherits numChan>2 from getC2. */
    theColor.thePartsA[0] = static_cast<clrChanT>(static_cast<channelArithFltType>(getC0()) * static_cast<channelArithFltType>(0.2126) +
                                                  static_cast<channelArithFltType>(getC1()) * static_cast<channelArithFltType>(0.7152) +
                                                  static_cast<channelArithFltType>(getC2()) * static_cast<channelArithFltType>(0.0722));
    for(int i=1; i<numChan; i++)
      theColor.thePartsA[i] = getChanNC(0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmStdPow(double p) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(std::pow(static_cast<double>(getChanNC(i)) / static_cast<double>(maxChanVal), p) * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmStdPowSqr(void) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(getChanNC(i)) /
                                                    static_cast<channelArithSPType>(maxChanVal));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmStdPowSqrt(void) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>(std::sqrt(static_cast<double>(getChanNC(i)) / static_cast<double>(maxChanVal)) *
                                                    static_cast<double>(maxChanVal));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmStdPow(double rp, double gp, double bp) {
    for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = static_cast<clrChanT>(pow(static_cast<double>(getChanNC(i)) / static_cast<double>(maxChanVal), bp) *
                                                      static_cast<double>(maxChanVal));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmSaw(colorArgType lowCol, colorArgType highCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i]  = ((lowCol.getChanNC(i) <= getChanNC(i)) && (highCol.getChanNC(i) >= getChanNC(i)) ? getChanNC(1) : 0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmStep(colorArgType lowCol, colorArgType highCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i]  = ((lowCol.getChanNC(i) <= getChanNC(i)) && (highCol.getChanNC(i) >= getChanNC(i)) ? maxChanVal : 0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmDiracTot(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      if(aCol.getChanNC(i) != getChanNC(i)) {
        return setToBlack();
        break;
      }
    return setToBlack();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmDirac(colorArgType aCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = ((aCol.getChanNC(i) == getChanNC(i)) ? maxChanVal : 0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmFuzzyDirac(colorArgType ctrCol, colorArgType radCol) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i]  = ((std::abs(ctrCol.getChanNC(i) - getChanNC(i)) <= radCol.getChanNC(i)) ? maxChanVal : 0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline void
  colorTpl<clrChanT, numChan>::setChansToMin() {
    // if( !(setMask(0)))
    //   std::fill_n(theColor.thePartsA, numChan, minChanVal);
    if(goodMask)
      theColor.theInt = static_cast<maskType>(0);
    else
      std::fill_n(theColor.thePartsA, numChan, minChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline void
  colorTpl<clrChanT, numChan>::setChansToMax() {
    if(chanIsInt && goodMask)
      theColor.theInt = ~static_cast<maskType>(0);
    else
      std::fill_n(theColor.thePartsA, numChan, maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToBlack() {
    setChansToMin();
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToWhite() {
    setChansToMax();
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToRed() {
    setChansToMin();
    setChanToMax(0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToGreen() {
    setChansToMin();
    setChanToMax(1);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToBlue() {
    setChansToMin();
    setChanToMax(2);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToCyan() {
    setChansToMax();
    setChanToMin(0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToYellow() {
    setChansToMax();
    setChanToMin(2);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToMagenta() {
    setChansToMax();
    setChanToMin(1);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToCorner(cornerColorEnum cornerColor) {
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
      default:                        return setToBlack();   break;
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToCorner(char cornerColor) {
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setToCorner(std::string cornerColor) {
    std::string::size_type sizeOfString = cornerColor.size();
    if (sizeOfString > 0) {
      if(((cornerColor[0] == 'b') || (cornerColor[0] == 'B')) && (sizeOfString > 0)) {
        if( (cornerColor[2]=='u') || (cornerColor[2]=='U') )
          setToBlue();
        else
          setToBlack();
      } else {
        setToCorner(cornerColor[0]);
      }
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setColorFromString(std::string colorString) {
    setChansToMin();
    if ( !(colorString.empty())) {
      if(colorString[0] == '#') {
        setChans(colorString);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpGreyTGA16bit(uint16_t tga16val) {
    /* Requires: Inherits numChan>1 from setC1. */
    tga16val = numberWrap(tga16val, 65536u);
    setChansToMin();
    setC1_byte(static_cast<clrChanT>( tga16val        & 0xff));
    setC0_byte(static_cast<clrChanT>((tga16val >> 8)  & 0xff));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpGreyTGA24bit(uint32_t tga24val) {
    /* Requires: Inherits numChan>2 from setC2. */
    tga24val = numberWrap(tga24val, 16777216u);
    setC1_byte(tga24val         & 0xff);
    setC0_byte((tga24val >> 8)  & 0xff);
    setC2_byte((tga24val >> 16) & 0xff);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRainbowHSV(csIdxType base, csIdxType csIdx) {
  /* Usability: The use of csIdxType sometimes requires casts in code using the library -- mostly because people like to use unadorned integer
     literals.  Unfortunately we can't simply use ints here as they are not big enough for deep images... One can still use ints for shallow, and just ignore
     any compiler warnings. */
    csIdx = numberWrap(csIdx, base);
    return setRGBfromUnitHSV(static_cast<double>(csIdx) / static_cast<double>(base), 1.0, 1.0);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRainbowLA(csIdxType base, csIdxType csIdx) {
    /* Saftey: We don't wrap csIdx because setRGBfromWavelengthLA() clamps. */
    return setRGBfromWavelengthLA((static_cast<double>(csIdx) / static_cast<double>(base)) * (maxWavelength-minWavelength) + minWavelength);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRainbowCM(csIdxType base, csIdxType csIdx, cmfInterpolationEnum interpMethod) {
    /* Saftey: We don't wrap csIdx because setRGBfromWavelengthCM() clamps. */
    return setRGBfromWavelengthCM((1.0 * static_cast<double>(csIdx) / static_cast<double>(base))*(maxWavelength-minWavelength)+minWavelength, interpMethod);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpClrCubeRainbow(csIdxType csIdx) {
    cmpRGBcolorRamp(csIdx, "RYGCBMR");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRampGrey2R(csIdxType csIdx) {
    clrChanT cVal = static_cast<clrChanT>(numberWrap(csIdx, meanChanVal));
    return setChans(static_cast<clrChanT>(meanChanVal + cVal),
                    static_cast<clrChanT>(meanChanVal - cVal),
                    static_cast<clrChanT>(meanChanVal - cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRampGrey2G(csIdxType csIdx) {
    clrChanT cVal = static_cast<clrChanT>(numberWrap(csIdx, meanChanVal));
    return setChans(static_cast<clrChanT>(meanChanVal - cVal),
                    static_cast<clrChanT>(meanChanVal + cVal),
                    static_cast<clrChanT>(meanChanVal - cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRampGrey2B(csIdxType csIdx) {
    clrChanT cVal = static_cast<clrChanT>(numberWrap(csIdx, meanChanVal));
    return setChans(static_cast<clrChanT>(meanChanVal - cVal),
                    static_cast<clrChanT>(meanChanVal - cVal),
                    static_cast<clrChanT>(meanChanVal + cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRampGrey2Y(csIdxType csIdx) {
    clrChanT cVal = static_cast<clrChanT>(numberWrap(csIdx, meanChanVal));
    return setChans(static_cast<clrChanT>(meanChanVal + cVal),
                    static_cast<clrChanT>(meanChanVal + cVal),
                    static_cast<clrChanT>(meanChanVal - cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRampGrey2C(csIdxType csIdx) {
    clrChanT cVal = static_cast<clrChanT>(numberWrap(csIdx, meanChanVal));
    return setChans(static_cast<clrChanT>(meanChanVal - cVal),
                    static_cast<clrChanT>(meanChanVal + cVal),
                    static_cast<clrChanT>(meanChanVal + cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpRampGrey2M(csIdxType csIdx) {
    clrChanT cVal = static_cast<clrChanT>(numberWrap(csIdx, meanChanVal));
    return setChans(static_cast<clrChanT>(meanChanVal + cVal),
                    static_cast<clrChanT>(meanChanVal - cVal),
                    static_cast<clrChanT>(meanChanVal + cVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpDiagRampCR(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "CR");
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpDiagRampMG(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "MG");
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpDiagRampYB(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "YB");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpConstTwoRamp(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "CMYC");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpConstOneRamp(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "BRGB");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpGreyRGB(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "0W");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpGrey(csIdxType csIdx) {
    return setChans(static_cast<clrChanT>(numberWrap(csIdx, maxChanVal)));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpGrey3x(csIdxType csIdx) {
    csIdx = numberWrap(csIdx, 3*maxChanVal);
    return setChans(static_cast<clrChanT>(csIdx / 3 + (csIdx%3==0?1:0)),
                    static_cast<clrChanT>(csIdx / 3 + (csIdx%3==1?1:0)),
                    static_cast<clrChanT>(csIdx / 3 + (csIdx%3==2?1:0)));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpGrey4x(csIdxType csIdx) {
    csIdx = numberWrap(csIdx, 4*maxChanVal);
    return setChans(static_cast<clrChanT>(csIdx / 4 + ((csIdx+1)%4==0?1:0)),
                    static_cast<clrChanT>(csIdx / 4 + ((csIdx+2)%4==0?1:0)),
                    static_cast<clrChanT>(csIdx / 4 + ((csIdx+3)%4==0?1:0)));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::cmpColorRamp(double aDouble, std::vector<double> const& anchors, std::vector<colorType> const& colors) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::cmpColorRamp(double aDouble, std::vector<colorType> const& colors) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::cmpRGBcolorRamp(csIdxType csIdx, const char *cornerColors) {
    return cmpRGBcolorRamp(csIdx, static_cast<csIdxType>(std::strlen(cornerColors)), cornerColors);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::cmpRGBcolorRamp(csIdxType csIdx, csIdxType numColors, const char *cornerColors) {
    /* Requires: Inherits numChan>2 from getC2. */
    csIdx = numberWrap(csIdx, static_cast<csIdxType>(maxChanVal * numColors - maxChanVal + 1));
    if(csIdx != 0) { [[likely]]
      for(csIdxType i=0; i<(numColors-1); i++) {
        if(csIdx <= maxChanVal) {
          clrChanT csIdxNoMore = static_cast<clrChanT>(csIdx);
          // Note: This could be MUCH better optimized!
          colorTpl<clrChanT, numChan> c1;
          colorTpl<clrChanT, numChan> c2;
          c1.setToCorner(cornerColors[i]);
          c2.setToCorner(cornerColors[i+1]);
          clrChanT r, g, b;
          if(c1.getC0() > c2.getC0()) {
            r = maxChanVal - csIdxNoMore;
          } else if(c1.getC0() < c2.getC0()) {
            r = csIdxNoMore;
          } else {
            r = c1.getC0();
          }
          if(c1.getC1() > c2.getC1()) {
            g = maxChanVal - csIdxNoMore;
          } else if(c1.getC1() < c2.getC1()) {
            g = csIdxNoMore;
          } else {
            g = c1.getC1();
          }
          if(c1.getC2() > c2.getC2()) {
            b = maxChanVal - csIdxNoMore;
          } else if(c1.getC2() < c2.getC2()) {
            b = csIdxNoMore;
          } else {
            b = c1.getC2();
          }
          return setChans(r, g, b);
        } else {
          csIdx = csIdx - maxChanVal;
        }
      }
    } else {
      return setToCorner(cornerColors[0]);
    }
    // If we got here, we had a problem.  But not much we can do about it...
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, channelArithFltType w4,
                                     colorArgType      col1, colorArgType      col2, colorArgType      col3, colorArgType      col4) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>((static_cast<channelArithFltType>(col1.getChanNC(i)) * w1) +
                                                    (static_cast<channelArithFltType>(col2.getChanNC(i)) * w2) +
                                                    (static_cast<channelArithFltType>(col3.getChanNC(i)) * w3) +
                                                    (static_cast<channelArithFltType>(col4.getChanNC(i)) * w4));

    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::wMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3,
                                     colorArgType      col1, colorArgType      col2, colorArgType      col3) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>((static_cast<channelArithFltType>(col1.getChanNC(i)) * w1) +
                                                    (static_cast<channelArithFltType>(col2.getChanNC(i)) * w2) +
                                                    (static_cast<channelArithFltType>(col3.getChanNC(i)) * w3));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::wMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2) {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = static_cast<clrChanT>((static_cast<channelArithFltType>(col1.getChanNC(i)) * w1) +
                                                    (static_cast<channelArithFltType>(col2.getChanNC(i)) * w2));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::uMean(channelArithFltType w1, channelArithFltType w2, channelArithFltType w3, colorArgType col1, colorArgType col2, colorArgType col3, colorArgType col4) {
    return wMean(w1, w2, w3, 1-w1-w2-w3, col1, col2, col3, col4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::uMean(channelArithFltType w1, channelArithFltType w2, colorArgType col1, colorArgType col2, colorArgType col3) {
    return wMean(w1, w2, 1-w1-w2, col1, col2, col3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::uMean(channelArithFltType w1, colorArgType col1, colorArgType col2) {
    return wMean(w1, 1-w1, col1, col2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::interplColorSpace(colorSpaceEnum space, double aDouble, colorArgType col1, colorArgType col2) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::interplColors(double aDouble, colorArgType col1, colorArgType col2) {
    if( (aDouble >= 0.0) && (aDouble <= 1.0) )
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i]  = static_cast<clrChanT>(mjr::interpolateLinear(static_cast<double>(col1.getChanNC(i)),
                                                                              static_cast<double>(col2.getChanNC(i)),   aDouble));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::interplColors(double aDouble, colorArgType tooCol) {
    if( (aDouble >= 0.0) && (aDouble <= 1.0) )
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i]  = static_cast<clrChanT>(mjr::interpolateLinear(static_cast<double>(getChanNC(i)),
                                                                              static_cast<double>(tooCol.getChanNC(i)),   aDouble));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpUpDownRampBr(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "YC");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpUpDownRampBg(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "YM");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpUpDownRampGr(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "MC");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpUpDownRampGb(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "MY");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpUpDownRampRg(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "CM");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpUpDownRampRb(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "CY");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpSumRampRGB(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "0RYW");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpSumRampBGR(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "0BCW");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpSumRampGRB(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "0GYW");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpSumRampGBR(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "0GCW");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpSumRampBRG(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "0BMW");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpSumRampRBG(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "0RMW");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpBinaryColorRampRG(csIdxType csIdx, csIdxType threshold) {
    if(csIdx < threshold)
      return setChans(maxChanVal, minChanVal, minChanVal);
    else
      return setChans(minChanVal, maxChanVal, minChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpBinaryColorRampRB(csIdxType csIdx, csIdxType threshold) {
    if(csIdx < threshold)
      return setChans(maxChanVal, minChanVal, minChanVal);
    else
      return setChans(minChanVal, minChanVal, maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpBinaryColorRampGR(csIdxType csIdx, csIdxType threshold) {
    if(csIdx < threshold)
      return setChans(minChanVal, maxChanVal, minChanVal);
    else
      return setChans(maxChanVal, minChanVal, minChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpBinaryColorRampGB(csIdxType csIdx, csIdxType threshold) {
    if(csIdx < threshold)
      return setChans(minChanVal, maxChanVal, minChanVal);
    else
      return setChans(minChanVal, minChanVal, maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpBinaryColorRampBR(csIdxType csIdx, csIdxType threshold) {
    if(csIdx < threshold)
      return setChans(minChanVal, minChanVal, maxChanVal);
    else
      return setChans(maxChanVal, minChanVal, minChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpBinaryColorRampBG(csIdxType csIdx, csIdxType threshold) {
    if(csIdx < threshold)
      return setChans(minChanVal, minChanVal, maxChanVal);
    else
      return setChans(minChanVal, maxChanVal, minChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpFireRamp(csIdxType csIdx) {
    return setRGBcmpSumRampRGB(csIdx);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpColdToHot(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "BCGYR");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBcmpIceToWaterToHot(csIdxType csIdx) {
    return cmpRGBcolorRamp(csIdx, "WCBYR");
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::colorComp2WebSafeColorComp(clrChanT aColorComp) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline clrChanT
  colorTpl<clrChanT, numChan>::colorComp2CloseColorComp(clrChanT aColorComp, clrChanT *discreetVals, int numVals) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmWebSafe216() {
    for(int i=0; i<numChan; i++)
      theColor.thePartsA[i] = colorComp2WebSafeColorComp(getChanNC(i));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmWebSafePro216() {
    /* Requires: Inherits numChan>2 from getC2. */
    tfrmWebSafe216();
    int colIdx = 36 * (getC0_byte() / 0x33) + 6 * (getC1_byte() / 0x33) + 1 * (getC2_byte() / 0x33) + 1;
    return setChans(webSafeColorData[colIdx][1]);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmWebSafeDeu216() {
    /* Requires: Inherits numChan>2 from getC2. */
    tfrmWebSafe216();
    int colIdx = 36 * (getC0_byte() / 0x33) + 6 * (getC1_byte() / 0x33) + 1 * (getC2_byte() / 0x33) + 1;
    return setChans(webSafeColorData[colIdx][2]);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmWebSafeTri216() {
    /* Requires: Inherits numChan>2 from getC2. */
    tfrmWebSafe216();
    int colIdx = 36 * (getC0_byte() / 0x33) + 6 * (getC1_byte() / 0x33) + 1 * (getC2_byte() / 0x33) + 1;
    return setChans(webSafeColorData[colIdx][3]);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::tfrmInvert() {
    //  MJR TODO NOTE tfrmInvert: This is just as fast as array refs...  
    //  MJR TODO NOTE tfrmInvert: We should use this universally across the library -- to isolate the code from the array specifics...
    for(int i=0; i<numChan; i++)
      setChanNC(i, maxChanVal - getChanNC(i));
    // for(int i=0; i<numChan; i++)
    //   theColor.thePartsA[i] = maxChanVal - getChanNC(i);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline typename colorTpl<clrChanT, numChan>::channelArithSDPType
  colorTpl<clrChanT, numChan>::rgb2GreyDotProd(channelArithSDPType redWt, channelArithSDPType greenWt, channelArithSDPType blueWt) {
    /* Requires: Inherits numChan>2 from getC2. */
    return static_cast<int>(static_cast<channelArithSDPType>(getC0()) * static_cast<channelArithSDPType>(redWt)   +
                            static_cast<channelArithSDPType>(getC1()) * static_cast<channelArithSDPType>(greenWt) +
                            static_cast<channelArithSDPType>(getC2()) * static_cast<channelArithSDPType>(blueWt));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>::channelArithFltType
  colorTpl<clrChanT, numChan>::rgbLuminance(void) {
    /* Requires: Inherits numChan>2 from getC2. */
    return (static_cast<channelArithFltType>(getC0()) * static_cast<channelArithFltType>(0.2126) +
            static_cast<channelArithFltType>(getC1()) * static_cast<channelArithFltType>(0.7152) +
            static_cast<channelArithFltType>(getC2()) * static_cast<channelArithFltType>(0.0722)) / static_cast<channelArithFltType>(maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>::channelArithSPType
  colorTpl<clrChanT, numChan>::rgbSumIntensity(void) {
    /* Requires: Inherits numChan>2 from getC2. */
    return (static_cast<channelArithSPType>(getC0()) +
            static_cast<channelArithSPType>(getC1()) +
            static_cast<channelArithSPType>(getC2()));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>::channelArithSPType
  colorTpl<clrChanT, numChan>::chanSum(void) {
    channelArithSPType sum = 0;
    for(int i=0; i<numChan; i++)
      sum += getChan(i);
    return (sum);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>::channelArithFltType
  colorTpl<clrChanT, numChan>::rgbScaledIntensity(void) {
    return (theColor.rgbSumIntensity() / static_cast<channelArithFltType>(numChan) / static_cast<channelArithFltType>(maxChanVal));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>::channelArithSPType
  colorTpl<clrChanT, numChan>::distP2sq(colorArgType aColor) {
    channelArithSPType daDist = 0;
    for(int i=0; i<numChan; i++)
      daDist += (static_cast<channelArithSPType>((static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aColor.getChanNC(i))) *
                                                 (static_cast<channelArithSDPType>(getChanNC(i)) - static_cast<channelArithSDPType>(aColor.getChanNC(i)))));
    return daDist;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  colorTpl<clrChanT, numChan>::channelArithSPType
  colorTpl<clrChanT, numChan>::dotProd(colorArgType aColor) {
    channelArithSPType daProd = 0;
    for(int i=0; i<numChan; i++)
      daProd += (static_cast<channelArithSPType>(getChanNC(i)) * static_cast<channelArithSPType>(aColor.getChanNC(i)));
    return daProd;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>::channelArithSPType
  colorTpl<clrChanT, numChan>::distAbs(colorArgType aColor) {
    channelArithSPType daDist = 0;
    for(int i=0; i<numChan; i++)
      daDist += static_cast<channelArithSPType>(std::abs(static_cast<channelArithDType>(getChanNC(i)) - static_cast<channelArithDType>(aColor.getChanNC(i))));
    return daDist;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline bool
  colorTpl<clrChanT, numChan>::isBlack() {
    if(goodMask)
      return (theColor.theInt == 0);
    else
      for(int i=4; i<numChan; i++)
        if(getChanNC(i) != 0)
          return 0;
    return 1;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline bool
  colorTpl<clrChanT, numChan>::isBlackRGB() {
    /* Requires: Inherits numChan>2 from getC2. */
    return ((getC0() == 0) && (getC1() == 0) && (getC2() == 0));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline bool
  colorTpl<clrChanT, numChan>::isEqualRGB(colorArgType aColor) {
    /* Requires: Inherits numChan>2 from getC2. */
    return ((getC0() == aColor.getC0()) &&
            (getC1() == aColor.getC1()) &&
            (getC2() == aColor.getC2()));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline bool
  colorTpl<clrChanT, numChan>::isEqual(colorArgType aColor) {
    if(goodMask)
      return (theColor.theInt == aColor.theColor.theInt);
    else
      for(int i=0; i<numChan; i++)
        if(getChanNC(i) != aColor.getChanNC(i))
          return 0;
    return 1;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline bool
  colorTpl<clrChanT, numChan>::isNotEqual(colorArgType aColor) {
    return !(isEqual(aColor));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromUnitHSV(double H, double S, double V) {
    return setRGBfromColorSpace(colorSpaceEnum::HSV, H*360.0, S, V);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromUnitHSL(double H, double S, double L) {
    return setRGBfromColorSpace(colorSpaceEnum::HSL, H*360.0, L, S);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromColorSpace(colorSpaceEnum space, colorTpl<double, 3> inColor) {
    /* Requires: Inherits numChan>2 from getC2. */
    return setRGBfromColorSpace(space, inColor.getC0(), inColor.getC1(), inColor.getC2());
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromColorSpace(colorSpaceEnum space, double inCh1, double inCh2, double inCh3) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline double
  colorTpl<clrChanT, numChan>::hslHelperVal(double n1, double n2, double hue) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBtoWebSafe216(int icpIdx) {
    icpIdx = numberWrap(icpIdx, 217);
    return setColorFromString((char*)(webSafeColorData[icpIdx][0]));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromICP(int icpIdx, const char **icpArray) {
    int numColorsInArray = (int)strtol(icpArray[0], NULL, 16) - 1;
    icpIdx++; // Increment icpIdx
    if( (icpIdx >= 1) && (icpIdx <= numColorsInArray) ) [[likely]]
      return setColorFromString((char*)(icpArray[icpIdx]));
    else
      return setToBlack();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromICP(int icpIdx, const uint32_t* icpArray) {
    int numColorsInArray = icpArray[0];
    icpIdx++; // Increment icpIdx
    if( (icpIdx >= 1) && (icpIdx <= numColorsInArray) ) [[likely]]
      return setRGBfromLogPackIntARGB(icpArray[icpIdx]);
    else
      return setToBlack();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromWavelengthCM(double wavelength, cmfInterpolationEnum interpMethod) {
    double rf, gf, bf;

    // Data about the color matching function table used. This should be abstracted away so that other color matching functions may be used.  Going to the
    // trouble of abstracting the color match function concept may not be worth the effort...
    const double minWL = 390.0;   // Min wavelength in table
    const double maxWL = 830.0;   // Max wavelength in table
    const int    numPT = 89;      // Number fo points in the table
    const double rScl  = 3.1673;  // Scale factors for color function
    const double gScl  = 1.0517;
    const double bScl  = 1.0019;

    // Clip the wavelength to be in range
    if(wavelength < minWL)
      wavelength = minWL;
    if(wavelength > maxWL)
      wavelength = maxWL;

    // Figure out where we are in our color function table
    double fIdx  = (wavelength-minWL)/(maxWL-minWL)*(numPT-1.0);
    int   iIdx1 = static_cast<int>(fIdx);
    int   iIdx2 = iIdx1+1;

    // If we fell off the edge, then we set our indexes to the appropriate edge
    if(iIdx2>(numPT-1)) { iIdx1 = numPT-2; iIdx2 = numPT-1; fIdx = static_cast<double>(iIdx1); }
    if(iIdx1<0)         { iIdx1 = 0;       iIdx2 = 1;       fIdx = static_cast<double>(iIdx1); }

    // Interpolate using our tabulated color matching function
    switch(interpMethod) {
      case cmfInterpolationEnum::FLOOR : // Closest with wavelength lower than given value
        rf=colMatchPoints[iIdx1][1];
        gf=colMatchPoints[iIdx1][2];
        bf=colMatchPoints[iIdx1][3];
        break;
      case cmfInterpolationEnum::CEILING : // Closest with wavelength greater than given value
        rf=colMatchPoints[iIdx2][1];
        gf=colMatchPoints[iIdx2][2];
        bf=colMatchPoints[iIdx2][3];
        break;
      case cmfInterpolationEnum::NEAREST : // Closest with wavelength to given value
        if( std::abs(wavelength-colMatchPoints[iIdx2][0]) < std::abs(wavelength-colMatchPoints[iIdx1][0])) {
          rf=colMatchPoints[iIdx2][1];
          gf=colMatchPoints[iIdx2][2];
          bf=colMatchPoints[iIdx2][3];
        } else {
          rf=colMatchPoints[iIdx1][1];
          gf=colMatchPoints[iIdx1][2];
          bf=colMatchPoints[iIdx1][3];
        }
        break;
      case cmfInterpolationEnum::LINEAR : // Linear interpolation between data points
        rf = (fIdx-static_cast<double>(iIdx1)) * (colMatchPoints[iIdx2][1] - colMatchPoints[iIdx1][1]) + colMatchPoints[iIdx1][1];
        gf = (fIdx-static_cast<double>(iIdx1)) * (colMatchPoints[iIdx2][2] - colMatchPoints[iIdx1][2]) + colMatchPoints[iIdx1][2];
        bf = (fIdx-static_cast<double>(iIdx1)) * (colMatchPoints[iIdx2][3] - colMatchPoints[iIdx1][3]) + colMatchPoints[iIdx1][3];
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<clrChanT, numChan>&
  colorTpl<clrChanT, numChan>::setRGBfromWavelengthLA(double wavelength) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  template <typename iT>
  inline clrChanT
  colorTpl<clrChanT, numChan>::clipTop(iT arithValue) {
    if(arithValue > maxChanVal)
      return maxChanVal;
    else
      return static_cast<clrChanT>(arithValue);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  template <typename iT>
  inline clrChanT
  colorTpl<clrChanT, numChan>::clipBot(iT arithValue) {
    if(arithValue < minChanVal)
      return minChanVal;
    else
      return static_cast<clrChanT>(arithValue);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  template <typename iT>
  inline clrChanT
  colorTpl<clrChanT, numChan>::clipAll(iT arithValue) {
    if(arithValue > maxChanVal)
      return maxChanVal;
    if(arithValue < minChanVal)
      return minChanVal;
    return static_cast<clrChanT>(arithValue);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline std::string
  colorTpl<clrChanT, numChan>::colorSpaceToString(colorSpaceEnum space) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrChanT, int numChan>
  inline colorTpl<double, 3>
  colorTpl<clrChanT, numChan>::rgb2colorSpace(colorSpaceEnum space) {
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
      double Y = (0.2126 * redF + 0.7152 * greenF + 0.0722 * blueF);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** i/O stream output operator for colorTpl types. */
  template <class clrChanT, int numChan>
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

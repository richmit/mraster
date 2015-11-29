// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
   @file      colorTpl.hpp
   @author    Mitch Richling <http://www.mitchr.me>
   @brief     Header for the ramColor class@EOL
   @copyright
   @parblock
   Copyright (c) 1988-2015, Mitchell Jay Richling <http://www.mitchr.me> All rights reserved.

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MJR_INCLUDE_colorTpl

#include "ramConfig.hpp"
#include "mapclamp.hpp"
#include "colorData.hpp"

#include <cmath>
#include <cstring>
#include <climits>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>

#include <type_traits>
#include <limits>

// Put everything in the mjr namespace
namespace mjr {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @brief Template Class used to house colors for ramCanvas objects.@EOL

    This template provides a rich API for color management, and may be used to store colors with a wide range of channel depth and count.  This class is
    intended to be a "small concrete" class (as defined by Bjarne Stroustrup in "The C++ Programming Language").  That is to say, it is intended for use as a
    "fundamental" type for tools requiring a space efficient and high performance set of concrete objects representing colors.  The canonical example is
    representing an image as a very large, rectangular array of colors.

    @par Size efficiency

    With an compiler supporting ISO C++, this object should take no more than the maximum of sizeof(clrChanT)*numChan, sizeof(clrMaskT), or sizeof(clrNameT).
    For example, this means that on a 64-bit computer a pointer will be larger than this object for a color with 4, or fewer, 8-bit channels.  For this
    reason, it is almost always a mistake to 'new' objects of this type and pass around pointers in order to save memory or time.

    @par Time efficiency (performance)

    For best performance:

    - Use an integer type for clrChanT
    - Use a *fast* unsigned integer type for clrMaskT such that sizeof(clrMaskT) > sizeof(clrChanT)*numChan

    Reasonably performance may also be expected when:

    - clrChanT is a floating point type
    - Use a *fast* unsigned integer type for clrMaskT such that sizeof(clrMaskT) > sizeof(clrChanT)*numChan

    @par Memory Layout

    Within this object a clrMaskT, clrNameT, and array of numChan clrCompT are placed into a union -- and thus are stacked upon each other in memory.  This is
    done for performance.  The mask type variable provides for highly optimized memory operations and logical operations.  The name type variable provides
    very high speed access to the first four channels -- the components of RGB/RGBA images -- note channel 1 is 'red', channel 2 is 'green', etc...  The
    library code is free to access channel 1 via the names or array.  The array variable provides reasonably fast access to the components in channels 5 and
    above.  Access to array elements is often 2x slower than access to struct elements.  This means that it takes 2x longer to access channel 5 than it will
    to access channel 4. This memory layout necessitates that the named red, green, blue, and alpha channels MUST be distributed across the first four
    channels.

    By convention, grey scale images use the red component of clrNameT.

    Most of the methods use the clrNameT variable to access the first four components of images.  Note that functions using named color components will work
    with high channel count images, but they will leave all unnamed channels untouched.

    @par Usage

    Several methods are provided that access and modify the internal color represented by a color object.  In most cases, methods that modify the color object
    state return a reference to the object after the change.  This provides, at a very slight performance impact, the ability to use the value returned by
    such a function in the expression in which it appears.  So, for example, it is not necessary to use two statements to change a color object's value and
    then use it in a drawing function.  As another example, this provides the ability to do "method chaining" like so: aColor.setToRed().setToBlack() -- which
    will lead to aColor being black.

    Several methods are provided that transform the color object as a whole.  For example, methods are provided to compute component wise linear histogram
    transformations.  Note that transformation methods are not provided to transform just one component of an object or a range of components.  The philosophy
    is that the class provides methods that treat the color object as a whole and not methods that operate on single components.  Just as we don't have a
    function to add the second half of two integers together -- integers are one "thingy" and so are colors. :)

    @par Construction

    Several constructors are provided.  Two are designed to directly construct RGB and RGBA colors by explicitly specifying three or four channel values.  One
    is designed to do the same for greyscale images, and for type conversion from a clrChanT.  Others are useful for type conversions.  All in all, the goal
    is to make it easy to construct color objects with a specified color.

      |--------------------------------+---------------------+------------------------------------|
      | Type                           | Member Helper       | Cast Application                   |
      |--------------------------------+---------------------+------------------------------------|
      | colorT                         | N/A                 |                                    |
      | three clrChanT                 | setColor            |                                    |
      | four clrChanT                  | setColor            |                                    |
      | one clrChanT                   | setAll              | drawPoint(x, y, 128);              |
      | Named Corner Colors via string | setColorFromString  | drawPoint(x, y, "Red");            |
      | Web hex string                 | setColorFromString  | drawPoint(x, y, "#FF0000");        |
      | Extended web hex string        | setColorFromString  | drawPoint(x, y, "##FFFF00000000"); |
      | Single character string        | setColorFromLetter  | drawPoint(x, y, "R");              |
      | Named Corner Colors via ENUM   | setColorFromCorner  | drawPoint(x, y, cornerColor::RED); |
      |--------------------------------+---------------------+------------------------------------|

    In all cases except setting from a color object (use assignment for that), a corresponding setColor*() method can be used to set the color of an existing
    object.  Note that the setColor*() API is much richer than the construction API.

    @tparam clrMaskT Integer type that is high performance on the platform of choice.  Incredible performance gains can be achieved if this type is as big as,
            but not larger than, an array o   f clrChanT that is numChan long.
    @tparam clrChanT Type to contain the channel information.  This type should be a floating point or an unsigned integral type.  Be warned that some
            functions only make since for integeral types.
    @tparam clrChanIArthT A SIGNED arithmetic type capable of holding arithmetic operations on clrChanT types.  At a minimum this type should be able to hold the
            sum and difference of two such values, and at best it should be able to hold products of such types.
    @tparam clrChanFArthT A floating point arithmetic type used for various computations with clrChanFArthT and clrChanIArthT, and clrChanT values.
    @tparam clrNameT This is a struct or union that has .red, .green, .blue, and .alpha components that are memory aligned with the elements of the component
            array.  This is used when a channel name is used.  This makes RGB and RGBA channel access VERY fast and provides a significant performance boost.

    @tparam numChan The number of channels this color will have.  Common choices are 1 for greyscale, 3 for RGB, and 4 for RGBA.
*/
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  class colorTpl {

    private:

      static_assert(std::is_arithmetic<clrChanT>::value,
                    "ERROR: clrChanT parameter of colorTpl template must be an arithmetic type");

      static_assert(std::is_floating_point<clrChanT>::value || (std::is_unsigned<clrChanT>::value && std::is_integral<clrChanT>::value),
                    "ERROR: clrChanT parameter of colorTpl template must be an unsigned integral type or a floating point type.");

      static_assert(std::is_arithmetic<clrChanIArthT>::value,
                    "ERROR: clrChanIArthT parameter of colorTpl template must be an arithmetic type");
      static_assert(std::is_floating_point<clrChanIArthT>::value || std::is_integral<clrChanIArthT>::value,
                    "ERROR: clrChanIArthT parameter of colorTpl template must be an unsigned integral type or a floating point type.");

      static_assert(sizeof(clrChanIArthT)>=sizeof(clrChanT),
                    "ERROR: sizeof clrChanIArthT parameter of colorTpl template must at least as large as sizeof clrChanT parameter.");

      static_assert(numChan>0,
                    "ERROR: the numChan parameter must be greater than zero.");
      
      /** Used to overlay variables based upon types provided as template parameters leading to dramatic performance improvements for common color types. */
      union {
          clrMaskT theInt;
          clrNameT theParts;
          clrChanT thePartsA[numChan];
      } theColor;

      const static int minWavelength = 360;     //!< Minimum wavelength for wavelength conversion
      const static int maxWavelength = 830;     //!< Maximum wavelength for wavelength conversion
      
      /* Several handy values... */

      const static int  fastMask                = (sizeof(clrMaskT)>=sizeof(clrChanT)*numChan);
      const static bool fastMaskUnsignedInt     = std::is_integral<clrChanT>::value && fastMask;

      /** Helper function for converting to web safe colors.  This function is highly optimized. */
      clrChanT colorComp2WebSafeColorComp(clrChanT aColorComp);
      /** Takes a list of values and a color component value.  Find the element in the discreet value list that is closest to the given component value.  The
          intended use is to reduce colors down to a smaller set of values -- ex: convert a color to the nearest web safe value. */
      clrChanT colorComp2CloseColorComp(clrChanT aColorComp, clrChanT *discreetVals, int numVals);
      /** This is a helper function for setColorFromNaturalHLS. */
      double hslHelperVal(double n1, double n2, double hue);

    public:

      const static bool          channelTypeIsFlt    = std::is_floating_point<clrChanT>::value;                       //!< is clrChanT a floating point type?
      const static bool          channelTypeIsInt    = std::is_integral<clrChanT>::value;                             //!< is clrChanT an integral type?
      const static int           bitsPerChan         = (int)(sizeof(clrChanT)*CHAR_BIT);                              //!< Number of bits in clrChanT
      const static bool          channelType8bitInt  = channelTypeIsInt && (bitsPerChan==8);                          //!< is clrChanT an 8-bit int?
      const static int           bitsPerPixel        = numChan*bitsPerChan;                                           //!< Number of color data bits
      const static clrChanT      maxChanVal          = (channelTypeIsInt ? std::numeric_limits<clrChanT>::max() : 1); //!< maximum value for a channel
      const static clrChanT      minChanVal          = (channelTypeIsInt ? std::numeric_limits<clrChanT>::min() : 0); //!< maximum value for a channel
      const static clrChanT      meanChanVal         = (maxChanVal-minChanVal)/2;                                     //!< middle value for a channel
      const static int           numChanNonRGB       = (numChan>3 ? numChan-3 : 0);                                   //!< number of non-RGB channels
      const static clrChanIArthT numValuesPerChan    = (clrChanIArthT)(1u<<bitsPerChan);                              //!< unique channel value approximation
      const static int           channelCount        = numChan;                                                       //!< Number of channels
      
      typedef clrChanT      channelType;          //!< Type for the channels (clrChanT)
      typedef clrChanIArthT channelIntArithType;  //!< Type for integer channel arithmetic (clrChanIArthT)
      typedef clrChanFArthT channelFltArithType;  //!< Type for floating point channel arithmetic (clrChanFArthT)
      /** @name Public Constants */
      //@{
      /** Named colors the corners of the RGB color cube. */
      enum class cornerColor { BLACK,     //!< Color cube corner color with RGB=000
                               RED,       //!< Color cube corner color with RGB=100
                               GREEN,     //!< Color cube corner color with RGB=010
                               BLUE,      //!< Color cube corner color with RGB=001
                               YELLOW,    //!< Color cube corner color with RGB=110
                               CYAN,      //!< Color cube corner color with RGB=011
                               MAGENTA,   //!< Color cube corner color with RGB=101
                               WHITE      //!< Color cube corner color with RGB=111
      };

      /** Color space interpolation methods */
      enum colorInterpMethEnum {CINTRP_RGB,     //!< RGB-space interpolation
                                CINTRP_HLS      //!< HLS-space interpolation

      };
      //@}

      /** @name Constructors: C++ Utility */
      //@{
      /** The no arg constructor is a noop -- no need to initialize millions of pixels for no good reason. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>();
      /** Copy constructor (heavily used for assignment in the ramCanvas library). */      
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>(const colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& aColor);
      //@}

      /** @name Constructors: RGB/RGBA */
      //@{
      /** This constructor directly sets the first three channels of the color object */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>(clrChanT r, clrChanT g, clrChanT b);
      /** This constructor directly sets the four channels of the color object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>(clrChanT r, clrChanT g, clrChanT b, clrChanT a);
      //@}

      /** @name Constructors: Data Conversion Focused */
      //@{
      /** Uses setAll method to set all channels to the given value */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>(clrChanT r);
      /** Uses the setColorFromCorner method to set the initialize the object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>(cornerColor ccolor);
      /** Uses the setColorFromString method to set the initialize the object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>(const char *colorString);      
      //@}
      
      /** @name Destructor */
      //@{
      /** The destructor for this class is a no-op. */
      ~colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>();
      //@}

      /** @name Component access */
      //@{
      /** Provides access to the red component of a color.
          @return The red value of the color currently stored.*/
      clrChanT getRed() const;
      /** Provides access to the green component of a color.
          @return The green value of the color currently stored.*/
      clrChanT getGreen() const;
      /** Provides access to the blue component of a color.
          @return The blue value of the color currently stored.*/
      clrChanT getBlue() const;
      /** Provides access to the alpha component of a color.
          @return The alpha value of the color currently stored.*/
      clrChanT getAlpha() const;
      /** Provides access to an indexed color channel value.  The colors are 0 indexed.  Note that the mapping from channel index and name are dependent upon
          the clrNameT template parameter!
          @param chan The channel index
          @return The the value of the indexed channel. */
      clrChanT getChan(int chan) const;
      //@}

      /** @name Component access and conversion to Float */
      //@{
      /** Provides access to the red component of a color as a floating point value in the unit interval, [0,1].
          @return The red value of the color currently stored.*/
      clrChanFArthT getRedF() const;
      /** Provides access to the green component of a color as a floating point value in the unit interval, [0,1].
          @return The green value of the color currently stored.*/
      clrChanFArthT getGreenF() const;
      /** Provides access to the blue component of a color as a floating point value in the unit interval, [0,1].
          @return The blue value of the color currently stored.*/
      clrChanFArthT getBlueF() const;
      /** Provides access to the alpha component of a color as a floating point value in the unit interval, [0,1].
          @return The alpha value of the color currently stored.*/
      clrChanFArthT getAlphaF() const;
      /** Provides access to the indexed component of a color as a floating point value in the unit interval, [0,1].
          @param chan The channel index
          @return The the value of the indexed channel. */
      clrChanFArthT getChanF(int chan) const;
      /** Provides access to the red component of a color as an unsigned 8-bit integer value in the range [0,255].
          @return The red value of the color currently stored.*/
      //@}

      /** @name Component access and conversion to unsigned 8-bit integer */
      //@{
      uint8_t getRed8bit() const;
      /** Provides access to the green component of a color an unsigned 8-bit integer value in the range [0,255].
          @return The green value of the color currently stored.*/
      uint8_t getGreen8bit() const;
      /** Provides access to the blue component of a color as an unsigned 8-bit integer value in the range [0,255].
          @return The blue value of the color currently stored.*/
      uint8_t getBlue8bit() const;
      /** Provides access to the alpha component of a color as an unsigned 8-bit integer value in the range [0,255].
          @return The alpha value of the color currently stored.*/
      uint8_t getAlpha8bit() const;
      /** Provides access to the indexed component of a color as an unsigned 8-bit integer value in the range [0,255].
          @param chan The channel index
          @return The the value of the indexed channel. */
      uint8_t getChan8bit(int chan) const;
      //@}

      /** @name Component setting */
      //@{
      /** Sets the red component of the current object.
          @param r The value to set the red component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setRed(clrChanT r);
      /** Sets the given channel to the value given.
          @param chan The channel to set
          @param cVal The value to set the channel to */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setChan(int chan, clrChanT cVal);
      /** Sets the green component of the current object.
          @param g The value to set the green component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setGreen(clrChanT g);
      /** Sets the blue component of the current object.
          @param b The value to set the blue component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setBlue(clrChanT b);
      /** Sets the alpha component of the current object.
          @param a The value to set the alpha component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAlpha(clrChanT a);
      /** Sets all components of the current object.
          @param a The value to set each channel to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAll(clrChanT a);
      //@}

      /** @name component setting with floating point numbers. */
      //@{
      /** Sets the red component of the current object from a floating point value in the unit interval, [0,1].
          @param r The value to set the red component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setRedF(clrChanFArthT r);
      /** Sets the given channel of the current object from a floating point value in the unit interval, [0,1].
          @param chan The channel to set
          @param cVal The value to set the channel to */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setChanF(int chan, clrChanFArthT cVal);
      /** Sets the green component of the current object from a floating point value in the unit interval, [0,1].
          @param g The value to set the green component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setGreenF(clrChanFArthT g);
      /** Sets the blue component of the current object from a floating point value in the unit interval, [0,1].
          @param b The value to set the blue component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setBlueF(clrChanFArthT b);
      /** Sets the alpha component of the current object from a floating point value in the unit interval, [0,1].
          @param a The value to set the alpha component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAlphaF(clrChanFArthT a);
      /** Sets all components of the current object from a floating point value in the unit interval, [0,1].
          @param a The value to set each channel to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAllF(clrChanFArthT a);
      //@}

      /** @name component setting with 8-bit, unsigned integers*/
      //@{
      /** Sets the red component of the current object from an uint8_t value in the interval [0,255].
          @param r The value to set the red component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setRed8bit(uint8_t r);
      /** Sets the given channel of the current object from an uint8_t value in the interval [0,255].
          @param chan The channel to set
          @param cVal The value to set the channel to */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setChan8bit(int chan, uint8_t cVal);
      /** Sets the green component of the current object from an uint8_t value in the interval [0,255].
          @param g The value to set the green component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setGreen8bit(uint8_t g);
      /** Sets the blue component of the current object from an uint8_t value in the interval [0,255].
          @param b The value to set the blue component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setBlue8bit(uint8_t b);
      /** Sets the alpha component of the current object from an uint8_t value in the interval [0,255].
          @param a The value to set the alpha component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAlpha8bit(uint8_t a);
      /** Sets all components of the current object from an uint8_t value in the interval [0,255].
          @param a The value to set each channel to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAll8bit(uint8_t a);
      //@}

      /** @name component setting with 64-bit, unsigned integers. */
      //@{
      /** Sets the red component of the current object from an uint64_t value in the interval [0,maxv].  Avoids round off error as much as possible by
          moving scale computations till the last moment; also avoids tedious and unsightly prescaling in application code.
          @param r The value to set the red component to
          @param maxv Floating point value corresponding to maxChanVal
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setRed64bit(uint64_t r, uint64_t maxv=std::numeric_limits<uint64_t>::max());
      /** Sets the given channel of the current object from an uint64_t value in the interval [0,maxv].  Avoids round off error as much as possible by
          moving scale computations till the last moment; also avoids tedious and unsightly prescaling in application code.
          @param chan The channel to set
          @param cVal The value to set the channel to
          @param maxv Floating point value corresponding to maxChanVal */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setChan64bit(int chan, uint64_t cVal, uint64_t maxv=std::numeric_limits<uint64_t>::max());
      /** Sets the green component of the current object from an uint64_t value in the interval [0,maxv].  Avoids round off error as much as possible by
          moving scale computations till the last moment; also avoids tedious and unsightly prescaling in application code.
          @param g    The value to set the green component to
          @param maxv Floating point value corresponding to maxChanVal
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setGreen64bit(uint64_t g, uint64_t maxv=std::numeric_limits<uint64_t>::max());
      /** Sets the blue component of the current object from an uint64_t value in the interval [0,maxv].  Avoids round off error as much as possible by
          moving scale computations till the last moment; also avoids tedious and unsightly prescaling in application code.
          @param b The value to set the blue component to
          @param maxv Floating point value corresponding to maxChanVal
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setBlue64bit(uint64_t b, uint64_t maxv=std::numeric_limits<uint64_t>::max());
      /** Sets the alpha component of the current object from an uint64_t value in the interval [0,maxv].  Avoids round off error as much as possible by
          moving scale computations till the last moment; also avoids tedious and unsightly prescaling in application code.
          @param a The value to set the alpha component to
          @param maxv Floating point value corresponding to maxChanVal
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAlpha64bit(uint64_t a, uint64_t maxv=std::numeric_limits<uint64_t>::max());
      /** Sets all components of the current object from an uint64_t value in the interval [0,maxv].  Avoids round off error as much as possible by moving
          scale computations till the last moment; also avoids tedious and unsightly prescaling in application code.
          @param a The value to set each channel to
          @param maxv Floating point value corresponding to maxChanVal
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setAll64bit(uint64_t a, uint64_t maxv=std::numeric_limits<uint64_t>::max());
      //@}

      /** @name RGB/RGBA color setting methods */
      //@{
      /** Sets the red, green, and blue components of the current object.
          @param r The value to set the red component to
          @param g The value to set the green component to
          @param b The value to set the blue component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorRGB(clrChanT r, clrChanT g, clrChanT b);
      /** Sets the red, green, blue, and alpha components of the current object.
          @param r The value to set the red component to
          @param g The value to set the green component to
          @param b The value to set the blue component to
          @param a The value to set the alpha component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorRGBA(clrChanT r, clrChanT g, clrChanT b, clrChanT a);
      //@}

      /** @name Multi-component color setting methods with data conversion */
      //@{
      /** Set the current color to one specified in the given color object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      setColorFromColor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Sets the current color based upon the contents of the given C-string.  The colorString argument may take one of three forms:
           - A C-string containing a single character. Ex: "0" 
           - A C-string containing an HTML-style, hex color specification. Ex: \#FFAABB
             Note: Each channel is set from two hex digits (0-255).
           - A C-string containing the name of a color.  Ex: "yellow"
          Black is the result if an unsupported color string is specified.
          @param colorString C-string specifying a color.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromString(const char *colorString);
      /** This function sets the current color based upon the single character given (0==black, R, G, B, M, C, Y, W=white).  This function is relatively well
          optimized.
          @param colorChar Character specifying the color
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromLetter(char colorChar);
      /** Set the color to one of the named corner colors.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromCorner(cornerColor ccolor);
      /** This function sets color based upon three uint8_t values in the range [0,255].  Note that a 255 indicates to set to a fully saturated value --
          i.e. a component given a 255 will be set to maxChanVal.
          @param r The value to set the red component to
          @param g The value to set the green component to
          @param b The value to set the blue component to
          @param a The value to set the alpha component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFrom8bit(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
      /** This function sets color based upon three uint8_t values in the range [0,255].  Note that a 255 indicates to set to a fully saturated value --
          i.e. a component given a 255 will be set to maxChanVal.
          @param r The value to set the red component to
          @param g The value to set the green component to
          @param b The value to set the blue component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFrom8bit(uint8_t r, uint8_t g, uint8_t b);
      /** This function sets color based upon three floating point values in the range [0,1].  Note that a 1 indicates to set to a fully saturated value --
          i.e. a component given a 1 will be set to maxChanVal.
          @param r The value to set the red component to
          @param g The value to set the green component to
          @param b The value to set the blue component to
          @param a The value to set the alpha component to
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromF(clrChanFArthT r, clrChanFArthT g, clrChanFArthT b, clrChanFArthT a);
      /** @overload */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromF(clrChanFArthT r, clrChanFArthT g, clrChanFArthT b);
      /** This function sets color based upon the bytes of the given integer.  The LSB (lest significant byte) of the given integer will be used to set red.
          If the integer is at least two bytes long, then the next byte will be green. Green and alpha are filled next if enough bytes exist.  Note that the
          bytes are interpreted as by setColorFrom8bit.  
          @param anInt The integer from which to extract bytes to set color
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromPackedIntRGBA(uint32_t anInt);
      /** @overload 
          @param anInt The integer from which to extract bytes to set color
          @param rIdx Location of red byte in anInt
          @param gIdx Location of green byte in anInt
          @param bIdx Location of blue byte in anInt
          @param aIdx Location of alpha byte in anInt*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromPackedIntRGBA(uint32_t anInt,
                                                                                                               uint8_t rIdx, uint8_t gIdx,
                                                                                                               uint8_t bIdx, uint8_t aIdx);
      //@}

      /** @name Set to special colors */
      //@{
      /** Set all channels to minChanVal. */
      void setChanToMin();
      /** Set all channels to maxChanVal. */
      void setChanToMax();
      /** Set the color to black.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToBlack();
      /** Set the color to white.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToWhite();
      /** Set the color to red.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToRed();
      /** Set the color to blue.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToBlue();
      /** Set the color to green.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToGreen();
      /** Set the color to cyan (RGB=011).
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToCyan();
      /** Set the color to yellow (RGB=110).
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToYellow();
      /** Set the color to magenta (RGB=101).
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setToMagenta();
      //@}
      
      /** @name Setting colors based upon other color spaces */
      //@{
      /** Set the color indicated by the given HSV values.  The 'unit' in the name indicates that the values for h, s, and v are the unit interval, [0,1].  This
          function is based upon the HSV_TO_RGB found in Foley and Van Dam.
          @param h The Hue.
          @param s The Saturation.
          @param v The Value */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromUnitHSV(float h, float s, float v);
      /** Set the color indicated by the given HSV values.  The 'natural' in the name indicates that The ranges for h, s, and v are the natural ones.  i.e. H is
          in [0,360], s and v are in the range [0,100]
          @param h The Hue.
          @param s The Saturation.
          @param v The Value */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromNaturalHSV(float h, float s, float v);
      /** Set the color indicated by the given HLS values.  The 'unit' in the name indicates that The ranges for h, s, and v are the the unit interval --
          i.e. [0,1].  The algorithm is that presented in Computer Graphics by Foley, Van Dam, Feiner, and Hughes -- 2nd edition page 596.  I have corrected a
          typeo in the text algorithm.
          @param H The Hue.
          @param L The Lightness or Luminescence
          @param S The Saturation. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&  setColorFromUnitHLS(float H, float L, float S);
      /** Set the color indicated by the given HLS values.  The 'natural' in the name indicates that The ranges for h, s, and v are the natural ones.  i.e. H is
          in [0,360], s and v are in the range [0,1].  This simply normalizes the H, and calls setColorFromNaturalHLS.
          @param H The Hue.
          @param L The Lightness or Luminescence
          @param S The Saturation. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&  setColorFromNaturalHLS(float H, float L, float S);
      /** Set the color indicated by the given wavelength.  This function uses an algorithm based upon the color matching functions as as tabulated in table 3
          from Stockman and Sharpe (2000) -- I believe they are taken from Stiles and Burch 10-degree (1959).  Four of the algorithms are based upon simple
          linear interpolation, while one is based upon exponential bump functions closely matching the color matching functions.  The method of interpolation
          may be specified via the final argument.
          @param wavelength The wavelength to convert into RGB
          @param INTRP      Specify the interpolation method:
          0 = closest lower, 
          1 = closest upper,
          2 = closest, 
          3 linear interpolation,
          4 = exponential bump map interpolation*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromWavelengthCM(float wavelength, int INTRP);
      /** overload */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromWavelengthCM(float wavelength);
      /** Set the color indicated by the given wavelength. This function uses an algorithm based upon linear approximations to the color match functions.  I
          believe the original algorithm is due to Dan Bruton, and his FORTRAN version is available (at least as of 1997) at
          http://www.physics.sfasu.edu/astro/color.html
          @param wavelength to convert */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& setColorFromWavelengthLA(float wavelength);
      //@}

      /** @name Set color based an indexed color scheme */
      //@{
      /** Sets the color based upon the web safe 216 indexed color pallet made up of the 216 colors considered safe for use on the web.  The colors are
          ordered in lexicographical ordering based upon the hexadecimal web-based color name scheme "#RRGGBB" -- i.e. 1 maps to "#000000", and 216 maps to
          "#ffffff".  Note that one can transform an rgb color into the nearest web safe color via tfrmWebSafe216().  As with all icp functions, 0 is black
          and the last color, at 217, is white.
          @param anInt An integer
          @return A reference to the current object */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& icpWebSafe216(int anInt);
      /** Sets the color based upon an indexed color pallet.  As with all icp functions, 0 is black and the last color, at 217, is white.
          @param anInt An integer
          @param icpArray The pallet data
          @return A reference to the current object */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& icpSetColor(int anInt, const char **icpArray);
      //@}

      /** @name Set color based upon color maps */
      //@{
      /** This computes a 24-bit truecolor value intended for use in producing 16-bit greyscale TGA.  This is the color scheme that should be sued for
          POVray 16-bit height files
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpGreyTGA16bit(int anInt);
      /** This computes a 24-bit truecolor value intended for use in producing 24-bit greyscale TGA.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpGreyTGA24bit(int anInt);
      /** This computes a color value based upon a linear approximation of the color match functions used to approximate wavelength to RGB conversion.  The
          linear color function approximation is not very accurate, but it is quite attractive.
          @param base The maximum number of colors
          @param anInt The index of the desired color */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRainbowLA(int base, int anInt);
      /** This computes a color value based upon an algorithm to convert wavelength to RGB that uses the Color Matching functions (setColorFromWavelengthCM).
          @param base The maximum number of colors
          @param anInt The index of the desired color
          @param INTRP Used as in setColorFromWavelengthCM() */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRainbowCM(int base, int anInt, int INTRP);
      /** overload */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRainbowCM(int base, int anInt);
      /** Computes a color value based upon a common rainbow-like color scheme based upon the HSV or HLS color space.  This rainbow is not natural in that the
          colors on the ends match each other, and the colors move in the wrong direction (red to violet).  This function uses floating point arithmetic and is
          thus prone to round off errors.  For a precise rainbow with integer arithmetic, see the function cmpClrCubeRainbow().
          @param base The maximum number of colors
          @param anInt The index of the desired color */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRainbowHSV(int base, int anInt);
      /** This computes a color value based upon a common rainbow-like color scheme based upon an edge traversal of the RGB color cube.  It is thus the same as
          using cmpColorRamp with a corner sequence of "RYGCBMR".  At least one color component is always maximal in RGB space, and one is minimum.  This
          sequence of colors corresponds to an HSV sequence from h=0 to h=360, with s=100 and v=100.  This is simply a more precise version of cmpRainbowHSV
          that is immune to round off errors as it doesn't require any floating point conversions.  This function will generate 6*maxChanVal+1 different colors.
          @param anInt The index of the desired color */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpClrCubeRainbow(int anInt);
      /** Returns a grey color given an index.  This is a true grey.  Provides (maxChanVal) different colors.  This function is NOT always the same as
          cmpColorRamp with a string of "0W" because cmpColorRamp is based upon a three channel space, while this function is based upon the number of channels
          in the current color.  For example, this function sets the alpha value of an RGBA color.  For an RGB based grey ramp, use cmpGreyRGB -- which is the
          same as cmpColorRamp with a corner string of "0W".  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpGrey(int anInt);
      /** Returns an RGB based (won't set any components beyond RGB) grey color given an index.  This is a true grey.  Provides (maxChanVal) different colors.
          This This function is is always the same as cmpColorRamp with a string of "0W".  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpGreyRGB(int anInt);
      /** A grey-like color scheme with 3*maxChanVal colors, [0,3*maxChanVal-1].  It is not a true grey, but most people can't tell when used with reasonable
          channel depths.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpGrey3x(int anInt);
      /** A grey-like color scheme with 4*maxChanVal colors, [0,4*maxChanVal-1].  It is not a true grey, but most people can't tell when used with reasonable
          channel depths.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpGrey4x(int anInt);
      /** Converts an integer into a color based upon a traversal of the diagonal of the color cube from cyan to red.  This is the same as the saturation based
          HLS ramp joining the same two colors.  The result is just as if cmpColorRamp had been called with string of "CR".  Provides about (maxChanVal*1+1)
          unique colors.  Supports input conditioning.
          @param anInt     An integer
          @return A reference to the current object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpDiagRampCR(int anInt);
      /** Converts an integer into a color based upon a traversal of the diagonal of the color cube from magenta to green.  This is the same as the saturation
          based HLS ramp joining the same two colors.  The result is just as if cmpColorRamp had been called with string of "MG".  Provides about
          (maxChanVal*1+1) unique colors.  Supports input conditioning.
          @param anInt     An integer
          @return A reference to the current object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpDiagRampMG(int anInt);
      /** Converts an integer into a color based upon a traversal of the diagonal of the color cube from yellow to blue.  This is the same as the saturation
          based HLS ramp joining the same two colors.  The result is just as if cmpColorRamp had been called with string of "YB".  Provides about
          (maxChanVal*1+1) unique colors.  Supports input conditioning.
          @param anInt     An integer
          @return A reference to the current object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpDiagRampYB(int anInt);
      /** Converts an integer into a color based upon a color cycle around the cube with constant constant brightness of two.  The result is just as if
          cmpColorRamp had been called with string of "CMYC".  Provides about (maxChanVal*3+1) unique colors.  Supports input conditioning.
          @param anInt     An integer
          @return A reference to the current object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpConstTwoRamp(int anInt);
      /** Converts an integer into a color based upon a color cycle around the cube with constant constant brightness of two.  The result is just as if
          cmpColorRamp had been called with string of "BRGB".  Provides about (maxChanVal*3+1) unique colors.  Supports input conditioning.
          @param anInt     An integer
          @return A reference to the current object. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpConstOneRamp(int anInt);
      /** Same as cmpSumRampRGB
          @param anInt An integer to convert to a color. */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpFireRamp(int anInt);
      /** Convert and integer into a color based upon the classical cold to hot ramp.  This is the same as cmpColorRamp with a corner list of "BCGYR" Provides
          (maxChanVal*4+1) unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpColdToHot(int anInt);
      /** Convert and integer into a color based upon a modified version of the classical cold to hot ramp.  This modified version corresponds to using
          cmpColorRamp with a corner list of "WCBYR" -- i.e. it starts at white (ice), moves up to blue (cold), then yellow through red (hot).  Provides
          (maxChanVal*4+1) unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpIceToWaterToHot(int anInt);
      /** Convert and integer into a color based upon the popular saturation based HLS color scheme extending from the center of the HLS color space to the red
          vertex.  The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides (meanChanVal)
          unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRampGrey2R(int anInt);
      /** Convert and integer into a color based upon the popular saturation based HLS color scheme extending from the center of the HLS color space to the
          green vertex.  The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides (meanChanVal)
          unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRampGrey2G(int anInt);
      /** Convert and integer into a color based upon the popular saturation based HLS color scheme extending from the center of the HLS color space to the blue
          vertex.  The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides (meanChanVal)
          unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRampGrey2B(int anInt);
      /** Convert and integer into a color based upon the popular saturation based HLS color scheme extending from the center of the HLS color space to the cyan
          vertex.  The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides (meanChanVal)
          unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRampGrey2C(int anInt);
      /** Convert and integer into a color based upon the popular saturation based HLS color scheme extending from the center of the HLS color space to the
          magenta vertex.  The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides
          (meanChanVal) unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRampGrey2M(int anInt);
      /** Convert and integer into a color based upon the popular saturation based HLS color scheme extending from the center of the HLS color space to the
          yellow vertex.  The same result can be obtained via a ramp from the center of the RGB color cube to the appropriate RGB vertex.  Provides
          (meanChanVal) unique colors.  Supports input conditioning.
          @param anInt The integer to convert
          @return A reference to the current object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpRampGrey2Y(int anInt);
      /** Converts an integer into a color based upon a color up-down ramp: Gg == Green Up and Green Down == cyan -> magenta.  Provides (maxChanVal) different
          colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpUpDownRampRg(int anInt);
      /** Converts an integer into a color based upon a color up-down ramp: Rb == Red Up and Blue Down == cyan -> yellow.  Provides (maxChanVal) different
          colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpUpDownRampRb(int anInt);
      /** Converts an integer into a color based upon a color up-down ramp: Gr == Green Up and Red Down == magenta -> cyan.  Provides (maxChanVal) different
          colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpUpDownRampGr(int anInt);
      /** Converts an integer into a color based upon a color up-down ramp: Gb == Green Up and Blue Down == magenta -> yellow.  Provides (maxChanVal) different
          colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpUpDownRampGb(int anInt);
      /** Converts an integer into a color based upon a color up-down ramp: Br == Blue Up and Red Down == yellow -> cyan.  Provides (maxChanVal) different
          colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpUpDownRampBr(int anInt);
      /** Converts an integer into a color based upon a color up-down ramp: Bg == Blue Up and Green Down == yellow -> magenta.  Provides (maxChanVal) different
          colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpUpDownRampBg(int anInt);
      /** Converts an integer into a color based upon a color sum-ramp: RGB == Black -> Red -> Yellow -> White.  Same as cmpColorRamp with a corner list of
          "0RYW".  Provides (3*maxChanVal+1) different colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpSumRampRGB(int anInt);
      /** Converts an integer into a color based upon a color sum-ramp: BGR == Black -> Blue -> cyan -> White.  Same as cmpColorRamp with a corner list of
          "0BCW" Provides (3*maxChanVal+1) different colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpSumRampBGR(int anInt);
      /** Converts an integer into a color based upon a color sum-ramp: GRB == Black -> Green -> yellow -> White.  Same as cmpColorRamp with a corner list of
          "0GYW" Provides (3*maxChanVal+1) different colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpSumRampGRB(int anInt);
      /** Converts an integer into a color based upon a color sum-ramp: GBR == Black -> Green -> cyan -> White.  Same as cmpColorRamp with a corner list of
          "0GCW" Provides (3*maxChanVal+1) different colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpSumRampGBR(int anInt);
      /** Converts an integer into a color based upon a color sum-ramp: BRG == Black -> Blue -> magenta -> White.  Same as cmpColorRamp with a corner list of
          "0BMW" Provides (3*maxChanVal+1) different colors.  Supports input conditioning.
          @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpSumRampBRG(int anInt);
      /** Converts an integer into a color based upon a color sum-ramp: RBG Black -> Red -> Magenta -> White.  Same as cmpColorRamp with a corner list of
          "0RMW".  Provides (3*maxChanVal+1) different colors.  Supports input conditioning.  @param anInt An integer */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpSumRampRBG(int anInt);
      //@}

      /** @name Binary, threshold color schemes */
      //@{
      /** Converts an integer into a color based upon a binary color ramp -- red if the integer is less than the threshold and green otherwise.
          @param anInt     An integer
          @param threshold The threshold */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpBinaryColorRampRG(int anInt, int threshold);
      /** Converts an integer into a color based upon a binary color ramp -- red if the integer is less than the threshold and blue otherwise.
          @param anInt     An integer
          @param threshold The threshold */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpBinaryColorRampRB(int anInt, int threshold);
      /** Converts an integer into a color based upon a binary color ramp -- green if the integer is less than the threshold and red otherwise.
          @param anInt     An integer
          @param threshold The threshold */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpBinaryColorRampGR(int anInt, int threshold);
      /** Converts an integer into a color based upon a binary color ramp -- green if the integer is less than the threshold and blue otherwise.
          @param anInt     An integer
          @param threshold The threshold */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpBinaryColorRampGB(int anInt, int threshold);
      /** Converts an integer into a color based upon a binary color ramp -- blue if the integer is less than the threshold and red otherwise.
          @param anInt     An integer
          @param threshold The threshold */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpBinaryColorRampBR(int anInt, int threshold);
      /** Converts an integer into a color based upon a binary color ramp -- blue if the integer is less than the threshold and green otherwise.
          @param anInt     An integer
          @param threshold The threshold */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpBinaryColorRampBG(int anInt, int threshold);
      //@}
      
      /** @name Color ramps, gradients, interpolation, binary thresholds. 
          Members in this section form the computational foundation for many of the named color schemes found in this class. */
      //@{
      /** Convert a double to a color value based upon a color ramp passing through the given sequence of corner colors at the given anchor points.  i.e. the
          value of this function at aDouble==anchor[i] will be colors[i].  This is an extremely general function that is capable of replicating many of the more
          precise color ramp sequence functions in this library.  The only defects are the lack of bit level precision and the poor performance -- both due to
          the use of floating point arithmetic.
          @param aDouble The value to convert
          @param numColors The number of colors and anchors passed in
          @param anchors Doubles for which color equals the corresponding corner. If anchors == NULL, then equidistant points on the unit interval will be used.
          @param colors  An array of colors to use
          @return A reference to this object */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpColorRamp(double aDouble,
                                                                                                  int numColors,
                                                                                                  double *anchors,
                                                                                                  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> *colors);
      /** This is simply a version of cmpColorRamp that computes the length of the final argument as a C-string.  Unlike the version of cmpColorRamp specifying
          numColors, this one requires the final argument to be a real C-string -- i.e. it must have a terminating NULL.
          @param anInt The value to convert
          @param colChars Characters specifying color (as used by setColor)
          @return A reference to this object */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpColorRamp(int anInt, const char *colChars);
      /** Convert an integer to a color value based upon a color ramp passing through the given sequence of corner colors at equal intervals along [0,
          (maxChanVal*(numColors-1)+1)].  At 0, the color will be the first specified color.  At (maxChanVal*(numColors-1)+1) it will be the last color
          specified color.  This function is similar to the one taking doubles. This version doesn't allow for the specification of anchor points, but uses
          precise integer arithmetic.  With this function it is possible to precisely duplicate many of the integer ramp color scheme functions.  This function
          supports input conditioning.  colChars need not be a real C-string -- i.e. no need for an terminating NULL.
          @param anInt The value to convert
          @param numColors The number of colors
          @param colChars Characters specifying color (as used by setColor)
          @return A reference to this object */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& cmpColorRamp(int anInt, int numColors, const char *colChars);
      /** Set the current color to a value linearly interpolated between the two given colors.  When aDouble is 0, the color is col1.  When aDouble is 1 the new
          value is col2.
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& interplColors(double aDouble,
                                                                                   colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                   colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2);
      /** Set the current color to a value linearly interpolated between the two given colors.  When aDouble is 0, the color is col1.  When aDouble is 1 the new
          value is col2.  The interpolation is done in HLS space -- i.e. the given colors are converted to HLS, the interpolation is done, and the result is
          converted back to RGB and the current color is set.  Unlike interplColors, this function will NOT interpolate every channel.  Rather, as this function
          deals specifically with RGB and HLS space, only the RGB channels will be interpolated.
          @param aDouble The distance from col1
          @param col1 The starting color
          @param col2 The ending color
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& interplColorsHLS(double aDouble,
                                                                                      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2);
      /** Compute the weighted mean of the given colors.  w1,w2,w3 in [0,1] and w1+w2+w3=1.
          @param w1   The first weight
          @param w2   The second weight
          @param w3   The third weight
          @param col1 The first color
          @param col2 The second color
          @param col3 The third color */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& wMean(clrChanFArthT w1, clrChanFArthT w2, clrChanFArthT w3,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col3);
      /** overload */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& wMean(clrChanFArthT w1, clrChanFArthT w2, 
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col3);
      /** Compute the weighted mean of the given colors.  w1,w2,w3 in [0,1] and w1+w2+w3=1.  Same as interplColors(wq, col1, col2).
          @param w1   The first weight
          @param w2   The second weight
          @param col1 The first color
          @param col2 The second color */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& wMean(clrChanFArthT w1, clrChanFArthT w2,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2);
      /** overload */
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& wMean(clrChanFArthT w1, 
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                           colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2);
      //@}
      
      /** @name Logical Operators. */
      //@{
      /** Performs a logical OR with the current object and the given object and places the value in the current object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmOr(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Performs a logical NOR with the current object and the given object and places the value in the current object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmNor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Performs a logical AND with the current object and the given object and places the value in the current object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmAnd(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Performs a logical NAND with the current object and the given object and places the value in the current object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmNand(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Performs a logical EXCLUSIVE OR (XOR) with the current object and the given object and places the value in the current object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmXor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Performs a logical NOT EXCLUSIVE OR (NXOR) with the current object and the given object and places the value in the current object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmNxor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Performs logical (bit-wise) negation of current object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& tfrmNot(void);
      //@}

      /** @name Arithmetic Operators. */
      //@{
      /** Computes the square of the difference for each channel between the given color and the current color object.
          @param color The color to compute the sqDiff with.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmSqDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the absolute value of the difference for each channel between the given color and the current color object.
          @param color The color to compute the absDiff with.
          @return Returns the absolute value of the difference for each channel.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmAbsDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic sum of the given color and the current one.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmAdd(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic division of the current color by the given color.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmDiv(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic product of the given color and the current one.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMult(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the product of the given color and the current one.  If the result of a multiplication is too large, it will be set to the maximum component
          value.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMultClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Modifies the current color by performing a component wise scaled sign of the difference between the current color and the given one. As an example of
          the computation, the red component of the current color is computed like this:
          - R=minChanVal  iff(R<color.R)
          - R=meanChanVal iff(R==color.R)
          - R=maxChanVal  iff(R>color.R)
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      ScaleSignDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic difference of the given color from the current one. If the result a differences is negative, then that component will be set
          to zero.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmDiffClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the negative of the arithmetic difference of the given color from the current one -- that is the same as the arithmetic difference of the
          current color from the given color.  If the result a differences is negative, then that component will be set to zero.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmNegDiffClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic sum of the given color from the current one.  If the result of a sum is greater than the maximum value, then that component
          will be set to the maximum value.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmAddClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic sum of the given color from the current one.  If the result of a sum is greater than the maximum value, then that component
          will be set to the maximum value.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmAddDivClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color,
                    colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> dcolor);
      /** Computes the arithmetic difference of the given color from the current one.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic modulus of the current by the given one.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMod(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Transforms the color: r=maxChanVal-r, g=maxChanVal-r, and b=maxChanVal-b
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmInvert();
      //@}

      /** @name Named Operators. */
      //@{
      /** Modifies the current color adding 1 and taking the natural logarithm.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& tfrmLn();
      /** Modifies the current color by linearly interpolating between the current color and the given color (at a point scaled the unit interval).  If aDouble
          is 0, then the current color will not change.  If aDouble is 1, then the current color will be tooCol.
          @param aDouble Distance from the current color (on a unit interval)
          @param tooCol  The color we are interpolating with.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      interplColors(double aDouble, colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> tooCol);
      /** Copies the given argument into the current color object.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmCopy(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Makes the current color the maximum of the current color or the given color. Colors are ordered by intensity (thus the 'I' in the name)
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMaxI(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Makes the current color the minimum of the current color or the given color. Colors are ordered by intensity (thus the 'I' in the name)
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMinI(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Makes each component of the current color the maximum of that component and the corresponding component of the given color.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMax(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Makes each component of the current color the minimum of that component and the corresponding component of the given color.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMin(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** The Shift Left Transform modifies the current color
          @param aCol Number of bits to shift left
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmShiftL(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol);
      /** The Shift Right Transform modifies the current color
          @param aCol How many bits to shift.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmShiftR(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol);
      /** The Saw Transform modifies the current color
          R=R iff(ra<=R<=rb), G=G iff(ga<=G<=gb), B=B iff(ba<=B<=bb)
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmSaw(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> lowCol,
              colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> highCol);
      /** The Saw Transform modifies the current color
          R=maxChanVal iff(ra<=R<=rb), G=maxChanVal iff(ga<=G<=gb), B=maxChanVal iff(ba<=B<=bb)
          @param lowCol lower cutoff value
          @param highCol upper cutoff value
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmStep(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> lowCol,
               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> highCol);
      /** The DiracTot (total) Transform modifies the current color:
          R=MAX,G=MAX, B=MAX iff ((R==aCol.R)&&(G==aCol.G)&&(B==aCol.B))
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmDiracTot(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol);
      /** The Dirac Transform modifies the current color:
          R=MAX iff(R==aCol.R), G=MAX iff(G==aCol.G), B=MAX iff(B==aCol.B)
          @param aCol Dirac trigger value
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmDirac(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol);
      /** The Fuzzy Dirac Transform modifies the current color:
          R=MAX iff(|R-ctrCol.R|<=radCol.R), G=MAX iff(|G-ctrCol.G|<=radCol.G), B=MAX iff(|B-ctrCol.B|<=radCol.B)
          @param ctrCol Center Color
          @param radCol Radius Color
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmFuzzyDirac(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> ctrCol,
                     colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> radCol);
      /** Computes the arithmetic mean of the given color and the current one.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmMean(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic geometric mean of the given color and the current one.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmGmean(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Computes the arithmetic geometric mean of the given color and the current one.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmGmeanClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color);
      /** Grey Scale transform modifies the current color by rendering it into a true grey via the same method used by the colorLuminance function.  Note, the
          colorLuminance function is NOT used internally within this function for performance reasons.  This function will do the best job it can within the
          current color depth.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& tfrmGreyScale(void);
      //@}

      

      /** @name Color Reduction Transformations */
      //@{
      /** The 216 Palate Web Safe Transform modifies the current color into the closest web safe color from the 216 color web safe pallet.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& tfrmWebSafe216();
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Protanopia might see.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& tfrmWebSafePro216();
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Deutanopia might see.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& tfrmWebSafeDeu216();
      /** Transforms the current color into the nearest web safe color, and then transforms it into what a person with Tritanoptia might see.
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& tfrmWebSafeTri216();
      //@}

      /** @name Alternate color space stuff */
      //@{
      int rgb2hsv(clrChanFArthT *H, clrChanFArthT *S, clrChanFArthT *V);
      int rgb2hls(clrChanFArthT *H, clrChanFArthT *L, clrChanFArthT *S);
      clrChanFArthT rgb2h();
      //@}

      /** @name Color transformation functions */
      //@{
      /** The Linear Grey Level Scale transform modifies the current color such that:
          R=c*R+b, G=c*G+b, B=c*B+b, ...
          This function transforms all channels --- not just RGBA.
          @param c The "contrast" value
          @param b The "brightness" value
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmLinearGreyLevelScale(float c, float b);
      /** The Linear Grey Level Scale transform defined by the control points to each channel of the current color.  The linear Grey Level Scale transform is
          defined by the control points, such that the "from" points are mapped into the "to" points.  For example, from1.red will map onto to1.red and
          from2.red will .  Two points define a line for each channel, and thus define a linear grey level scale transform for each channel.  Note, this
          function transforms all channels.  This function is quite slow because of all of the floating point operations required.
          @param from1 Control point mapped to argument to1
          @param from2 Control point mapped to argument to2
          @param to1 Control point mapped from argument from1
          @param to2 Control point mapped from argument from2
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmLinearGreyLevelScale(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> from1,
                               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> from2,
                               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> to1,
                               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> to2);
      /** The Linear Grey Level Scale transform modifies the current color such that:
          R=rc*R+rb, G=gc*G+gb, B=bc*B+bb.
          This function ONLY transforms the red, green, and blue channels.
          @param rc The "contrast" value for red
          @param rb The "brightness" value for red
          @param gc The "contrast" value for green
          @param gb The "brightness" value for green
          @param bc The "contrast" value for blue
          @param bb The "brightness" value for blue
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmLinearGreyLevelScale(float rc, float rb,
                               float gc, float gb,
                               float bc, float bb);
      /** The Standard Power Transform modifies the current color such that:
          R=maxChanVal*(R/maxChanVal)**p, G=maxChanVal*(G/maxChanVal)**p, B=maxChanVal*(B/maxChanVal)**p
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmStdPow(float p);
      /** The Standard Power Transform modifies the current color such that:
          R=maxChanVal*(R/maxChanVal)**rp, B=maxChanVal*(B/maxChanVal)**gp, B=maxChanVal*(B/maxChanVal)**bp
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmStdPow(float rp, float gp, float bp);
      /** The Standard Power Transform with p=2. The new color will be:
          R=maxChanVal*(R/maxChanVal)**2, G=maxChanVal*(G/maxChanVal)**2, B=maxChanVal*(B/maxChanVal)**2
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmStdPowSqr(void);
      /** The Standard Power Transform with p=1/2. The new color will be:
          R=maxChanVal*(R/maxChanVal)**(1/2), G=maxChanVal*(G/maxChanVal)**(1/2), B=maxChanVal*(B/maxChanVal)**(1/2)
          @return Returns a reference to the current color object.*/
      colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
      tfrmStdPowSqrt(void);
      //@}

      /** @name Mathematical operations on color(s) 
          Members in this section produce non-color results. i.e. They consume the current, and possibly other colors and arguments, to produce a non-color
          result. */
      //@{
      /** Use the first three channels to compute an integer representing a grey scale.  What is returned is the dot product of the given color and the three
          scalars: R*redWt+G*greenWt+B*blueWt.  This dot product is not scaled.  Common values for (redWt, greenWt, blueWt) are:
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
      int color2GreyDotProd(int redWt, int greenWt, int blueWt);
      /** Compute the luminance of the current color via the definition given in the ITU-R Recommendation BT.709 (Basic Parameter Values for the HDTV Standard
          for the Studio and for International Programme Exchange from 1990). Note this was formerly CCIR Rec 709.  The output value will be between 0 and 1,
          and is given by: (0.2126*R+0.7152*G+0.0722*B)/maxChanVal.
          @return The luminance for the current object. */
      double colorLuminance(void);
      /** Compute the unscaled intensity (sum of the components) of the current color
          @return The unscaled intensity for the current object. */
      clrChanIArthT colorSumIntensity(void);
      /** Compute the scaled intensity (sum of the components divided by the maximum intensity possible) of the current color
          @return The scaled intensity for the current object. */
      double colorScaledIntensity(void);
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
      int dotProd(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor);
      /** Distance between current color and given one (sum squares) Returns the sum of the squares of the differences of the components.  Returns |c1-c2|^2
          @param aColor The given color
          @return Returns distance squared.*/
      int distP2sq(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor);
      /** Distance between current color and given one (absolute difference) Returns sum of the absolute value of the differences of the components
          @param aColor the given color
          @return Returns absolute distance squared.*/
      int distAbs(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor);
      /** Returns non-zero if the given color is logically the same as the current color.
          @return non-zero if the given color is logically the same as the current color*/
      int isEqual(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor);
      /** Returns non-zero if the given color is logically NOT the same as the current color.
          @return non-zero if the given color is logically the same as the current color*/
      int isNotEqual(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor);
      //@}

      /** @name Channel Clipping functions */
      //@{
      /** Clamp a value on the top end such that it will fit into a clrChanT type. Input values larger than the maximum channel value are mapped to the maximum
          channel value.  Values less than the minimum (0) are not clamped.
          @param anArithComp The value to clamp */
      clrChanIArthT clipTop(clrChanIArthT anArithComp);
      /** Clamp a value on the bottom end such that it will fit into a clrChanT type. Input values less than the minimum (0), are mapped to 0.  Note values
          greater than the maximum channel value are NOT clamped.
          @param anArithComp The value to clam    p */
      clrChanIArthT clipBot(clrChanIArthT anArithComp);
      /** Clamp a value such that it will fit into a clrChanT type. Input values less than zero are mapped to zero, and input values larger than the maximum
          channel value are mapped to the maximum q channel value.
          @param anArithComp The value to clamp */
      clrChanIArthT clipAll(clrChanIArthT anArithComp);
      //@}

  };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorTpl() {
    // We don't do anything as this throws away resources.  If the color needs cleared, we have a method for that.  This is consistent with the tradition of
    // C/C++ not initializing concrete types like int and float.
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorTpl(clrChanT r) {
    setAll(r);
  }
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorTpl(clrChanT r, clrChanT g, clrChanT b) {
    theColor.theParts.red                   = r;
    if(numChan > 1) theColor.theParts.green = g;
    if(numChan > 2) theColor.theParts.blue  = b;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorTpl(clrChanT r, clrChanT g, clrChanT b, clrChanT a) {
    theColor.theParts.red                   = r;
    if(numChan > 1) theColor.theParts.green = g;
    if(numChan > 2) theColor.theParts.blue  = b;
    if(numChan > 3) theColor.theParts.alpha = a;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorTpl(const colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>& aColor) {
    if(fastMask) 
      theColor.theInt = aColor.theColor.theInt;
    else
      std::copy_n(aColor.theColor.thePartsA, numChan, theColor.thePartsA);
  }
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorTpl(const char *colorString) {
    setColorFromString(colorString);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /* constructor */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorTpl(cornerColor ccolor) {
    setColorFromCorner(ccolor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::~colorTpl() {
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getRed() const {
    return theColor.theParts.red;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getBlue() const {
    return theColor.theParts.blue;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getGreen() const {
    return theColor.theParts.green;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getAlpha() const {
    return theColor.theParts.alpha;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getChan(int chan) const {
    return theColor.thePartsA[chan];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanFArthT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getRedF() const {
    if(channelTypeIsFlt)
      return theColor.theParts.red;
    else
      return theColor.theParts.red / double(maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanFArthT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getBlueF() const {
    if(channelTypeIsFlt)
      return theColor.theParts.blue;
    else
      return theColor.theParts.blue / double(maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanFArthT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getGreenF() const {
    if(channelTypeIsFlt)
      return theColor.theParts.green;
    else
      return theColor.theParts.green / double(maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanFArthT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getAlphaF() const {
    if(channelTypeIsFlt)
      return theColor.theParts.alpha;
    else
      return theColor.theParts.alpha / double(maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanFArthT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getChanF(int chan) const {
    if(channelTypeIsFlt)
      return theColor.thePartsA[chan];
    else
      return theColor.thePartsA[chan] / double(maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  uint8_t
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getRed8bit() const {
    if(channelType8bitInt)
      return (uint8_t)(theColor.theParts.red);
    else
      return (uint8_t)(255.0 * theColor.theParts.red / maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  uint8_t
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getBlue8bit() const {
    if(channelType8bitInt)
      return (uint8_t)(theColor.theParts.blue);
    else
      return (uint8_t)(255.0 * theColor.theParts.blue / maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  uint8_t
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getGreen8bit() const {
    if(channelType8bitInt)
      return (uint8_t)(theColor.theParts.green);
    else
      return (uint8_t)(255.0 * theColor.theParts.green / maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  uint8_t
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getAlpha8bit() const {
    if(channelType8bitInt)
      return (uint8_t)(theColor.theParts.alpha);
    else
      return (uint8_t)(255.0 * theColor.theParts.alpha / maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  uint8_t
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getChan8bit(int chan) const {
    if(channelType8bitInt)
      return (uint8_t)(theColor.thePartsA[chan]);
    else
      return (uint8_t)(255.0 * theColor.thePartsA[chan] / maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getMaxC() {
    if(numChan == 1) {                                         // 1 channel
      return theColor.theParts.red;
    } else if(numChan == 2) {                                  // 2 channels
      return std::max(theColor.theParts.red, theColor.theParts.green);
    } else if(numChan == 3) {                                  // 3 channels
      return std::max(std::max(theColor.theParts.red,
                               theColor.theParts.green),
                      theColor.theParts.blue);
    } else if(numChan == 4) {                                  // 4 channels
      return std::max(std::max(theColor.theParts.red,
                               theColor.theParts.green),
                      std::max(theColor.theParts.blue,
                               theColor.theParts.alpha));
    } else {                                                   // More than 3 channels
      clrChanT theMax = minChanVal;
      for(int i=0; i<numChan; i++)
        if(theMax < theColor.thePartsA[i])
          theMax = theColor.thePartsA[i];
      return theMax;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getMinC() {
    if(numChan == 1) {                                         // 1 channel
      return theColor.theParts.red;
    } else if(numChan == 2) {                                  // 2 channels
      return std::min(theColor.theParts.red, theColor.theParts.green);
    } else if(numChan == 3) {                                  // 3 channels
      return std::min(std::min(theColor.theParts.red,
                               theColor.theParts.green),
                      theColor.theParts.blue);
    } else if(numChan == 4) {                                  // 4 channels
      return std::min(std::min(theColor.theParts.red,
                               theColor.theParts.green),
                      std::min(theColor.theParts.blue,
                               theColor.theParts.alpha));
    } else {
      clrChanT theMin = maxChanVal;
      for(int i=0; i<numChan; i++)
        if(theMin > theColor.thePartsA[i])
          theMin = theColor.thePartsA[i];
      return theMin;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getMaxRGB() {
    return std::max(std::max(theColor.theParts.red,
                             theColor.theParts.green),
                    theColor.theParts.blue);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::getMinRGB() {
    return std::min(std::min(theColor.theParts.red,
                             theColor.theParts.green),
                    theColor.theParts.blue);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setChan(int chan, clrChanT cVal) {
    if((chan >= 0) && (chan <= numChan))
      theColor.thePartsA[chan] = cVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setRed(clrChanT r) {
    theColor.theParts.red = r;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setBlue(clrChanT b) {
    theColor.theParts.blue = b;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setGreen(clrChanT g) {
    theColor.theParts.green = g;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAlpha(clrChanT a) {
    theColor.theParts.alpha = a;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAll(clrChanT aComp) {
    theColor.theParts.red     = aComp;
    if(numChan > 1)
      theColor.theParts.green = aComp;
    if(numChan > 2)
      theColor.theParts.blue  = aComp;
    if(numChan > 3)
      theColor.theParts.alpha = aComp;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = aComp;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setChanF(int chan, clrChanFArthT cVal) {
    if((chan >= 0) && (chan <= numChan))
      theColor.thePartsA[chan] = clrChanT(cVal * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setRedF(clrChanFArthT r) {
    theColor.theParts.red = clrChanT(r * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setBlueF(clrChanFArthT b) {
    theColor.theParts.blue = clrChanT(b * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setGreenF(clrChanFArthT g) {
    theColor.theParts.green = clrChanT(g * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAlphaF(clrChanFArthT a) {
    theColor.theParts.alpha = clrChanT(a * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAllF(clrChanFArthT aComp) {
    theColor.theParts.red     = clrChanT(aComp * maxChanVal);
    if(numChan > 1)
      theColor.theParts.green = clrChanT(aComp * maxChanVal);
    if(numChan > 2)
      theColor.theParts.blue  = clrChanT(aComp * maxChanVal);
    if(numChan > 3)
      theColor.theParts.alpha = clrChanT(aComp * maxChanVal);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clrChanT(aComp * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setChan64bit(int chan, uint64_t cVal, uint64_t maxv) {
    if((chan >= 0) && (chan <= numChan)) {
      if(maxChanVal == maxv)
        theColor.thePartsA[chan] = clrChanT(cVal);
      else
        theColor.thePartsA[chan] = clrChanT(1.0 * maxChanVal * cVal / maxv);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setRed64bit(uint64_t r, uint64_t maxv) {
    if(maxChanVal == maxv)
      theColor.theParts.red = clrChanT(r);
    else
      theColor.theParts.red = clrChanT(1.0 * maxChanVal * r / maxv);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setBlue64bit(uint64_t b, uint64_t maxv) {
    if(maxChanVal == maxv)
      theColor.theParts.blue = clrChanT(b);
    else
      theColor.theParts.blue = clrChanT(1.0 * maxChanVal * b / maxv);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setGreen64bit(uint64_t g, uint64_t maxv) {
    if(maxChanVal == maxv)
      theColor.theParts.green = clrChanT(g);
    else
      theColor.theParts.green = clrChanT(1.0 * maxChanVal * g / maxv);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAlpha64bit(uint64_t a, uint64_t maxv) {
    if(maxChanVal == maxv)
      theColor.theParts.alpha = clrChanT(a);
    else
      theColor.theParts.alpha = clrChanT(1.0 * maxChanVal * a / maxv);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAll64bit(uint64_t aComp, uint64_t maxv) {
    clrChanT convertedValue;
    if(maxChanVal == maxv)
      convertedValue = clrChanT(aComp);
    else
      convertedValue = clrChanT(1.0 * maxChanVal * aComp / maxv);
    theColor.theParts.red     = convertedValue;
    if(numChan > 1)
      theColor.theParts.green = convertedValue;
    if(numChan > 2)
      theColor.theParts.blue  = convertedValue;
    if(numChan > 3)
      theColor.theParts.alpha = convertedValue;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = convertedValue;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setChan8bit(int chan, uint8_t cVal) {
    if((chan >= 0) && (chan <= numChan)) {
      if(channelType8bitInt)
        theColor.thePartsA[chan] = clrChanT(cVal);
      else
        theColor.thePartsA[chan] = clrChanT(maxChanVal * cVal / 255.0);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setRed8bit(uint8_t r) {
    if(channelType8bitInt)
      theColor.theParts.red = clrChanT(r);
    else
      theColor.theParts.red = clrChanT(maxChanVal * r / 255.0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setBlue8bit(uint8_t b) {
    if(channelType8bitInt)
      theColor.theParts.blue = clrChanT(b);
    else
      theColor.theParts.blue = clrChanT(maxChanVal * b / 255.0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setGreen8bit(uint8_t g) {
    if(channelType8bitInt)
      theColor.theParts.green = clrChanT(g);
    else
      theColor.theParts.green = clrChanT(maxChanVal * g / 255.0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAlpha8bit(uint8_t a) {
    if(channelType8bitInt)
      theColor.theParts.alpha = clrChanT(a);
    else
      theColor.theParts.alpha = clrChanT(maxChanVal * a / 255.0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setAll8bit(uint8_t aComp) {
    clrChanT convertedValue;
    if(channelType8bitInt)
      convertedValue = clrChanT(aComp);
    else
      convertedValue = clrChanT(maxChanVal * aComp / 255.0);
    theColor.theParts.red     = convertedValue;
    if(numChan > 1)
      theColor.theParts.green = convertedValue;
    if(numChan > 2)
      theColor.theParts.blue  = convertedValue;
    if(numChan > 3)
      theColor.theParts.alpha = convertedValue;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = convertedValue;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @todo Optimize this function */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::ScaleSignDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    for(int i=0; i<numChan; i++) {
      if(theColor.thePartsA[i] < color.theColor.thePartsA[i]) {
        theColor.thePartsA[i] = minChanVal;
      } else if(theColor.thePartsA[i] > color.theColor.thePartsA[i]) {
        theColor.thePartsA[i] = maxChanVal;
      } else {
        theColor.thePartsA[i] = meanChanVal;
      }
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmLn() {
    theColor.theParts.red     = log(1 + theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = log(1 + theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = log(1 + theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = log(1 + theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = log(1 + theColor.thePartsA[i]);
    return *this;
  }
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmOr(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt |=  color.theColor.theInt;
    else {
      theColor.theParts.red     = theColor.theParts.red   | color.theColor.theParts.red;
      if(numChan > 1)
        theColor.theParts.green = theColor.theParts.green | color.theColor.theParts.green;
      if(numChan > 2)
        theColor.theParts.blue  = theColor.theParts.blue  | color.theColor.theParts.blue;
      if(numChan > 3)
        theColor.theParts.alpha = theColor.theParts.alpha | color.theColor.theParts.alpha;
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = theColor.thePartsA[i]   | color.theColor.thePartsA[i];
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmNor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt =  ~(theColor.theInt | color.theColor.theInt);
    else {
      theColor.theParts.red     = ~(theColor.theParts.red   | color.theColor.theParts.red);
      if(numChan > 1)
        theColor.theParts.green = ~(theColor.theParts.green | color.theColor.theParts.green);
      if(numChan > 2)
        theColor.theParts.blue  = ~(theColor.theParts.blue  | color.theColor.theParts.blue);
      if(numChan > 3)
        theColor.theParts.alpha = ~(theColor.theParts.alpha | color.theColor.theParts.alpha);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = ~(theColor.thePartsA[i]   | color.theColor.thePartsA[i]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** @todo This could be made faster with raw memory copy functions. */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmCopy(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt = color.theColor.theInt;
    else {
      theColor.theParts.red     = color.theColor.theParts.red;
      if(numChan > 1)
        theColor.theParts.green = color.theColor.theParts.green;
      if(numChan > 2)
        theColor.theParts.blue  = color.theColor.theParts.blue;
      if(numChan > 3)
        theColor.theParts.alpha = color.theColor.theParts.alpha;
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = color.theColor.thePartsA[i];
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmAnd(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt &= color.theColor.theInt;
    else {
      theColor.theParts.red     = theColor.theParts.red   & color.theColor.theParts.red;
      if(numChan > 1)
        theColor.theParts.green = theColor.theParts.green & color.theColor.theParts.green;
      if(numChan > 2)
        theColor.theParts.blue  = theColor.theParts.blue  & color.theColor.theParts.blue;
      if(numChan > 3)
        theColor.theParts.alpha = theColor.theParts.alpha & color.theColor.theParts.alpha;
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = theColor.thePartsA[i]   & color.theColor.thePartsA[i];
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmNand(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt = ~(theColor.theInt & color.theColor.theInt);
    else {
      theColor.theParts.red     = ~(theColor.theParts.red   & color.theColor.theParts.red);
      if(numChan > 1)
        theColor.theParts.green = ~(theColor.theParts.green & color.theColor.theParts.green);
      if(numChan > 2)
        theColor.theParts.blue  = ~(theColor.theParts.blue  & color.theColor.theParts.blue);
      if(numChan > 3)
        theColor.theParts.alpha = ~(theColor.theParts.alpha & color.theColor.theParts.alpha);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = ~(theColor.thePartsA[i]   & color.theColor.thePartsA[i]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmXor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt ^= color.theColor.theInt;
    else {
      theColor.theParts.red     = theColor.theParts.red   ^ color.theColor.theParts.red;
      if(numChan > 1)
        theColor.theParts.green = theColor.theParts.green ^ color.theColor.theParts.green;
      if(numChan > 2)
        theColor.theParts.blue  = theColor.theParts.blue  ^ color.theColor.theParts.blue;
      if(numChan > 3)
        theColor.theParts.alpha = theColor.theParts.alpha ^ color.theColor.theParts.alpha;
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = theColor.thePartsA[i]   ^ color.theColor.thePartsA[i];
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmNxor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt = ~(theColor.theInt ^ color.theColor.theInt);
    else {
      theColor.theParts.red     = ~(theColor.theParts.red   ^ color.theColor.theParts.red);
      if(numChan > 1)
        theColor.theParts.green = ~(theColor.theParts.green ^ color.theColor.theParts.green);
      if(numChan > 2)
        theColor.theParts.blue  = ~(theColor.theParts.blue  ^ color.theColor.theParts.blue);
      if(numChan > 3)
        theColor.theParts.alpha = ~(theColor.theParts.alpha ^ color.theColor.theParts.alpha);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = ~(theColor.thePartsA[i]   ^ color.theColor.thePartsA[i]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmNot(void) {
    if(fastMask)
      theColor.theInt = ~(theColor.theInt);
    else {
      theColor.theParts.red     = ~(theColor.theParts.red);
      if(numChan > 1)
        theColor.theParts.green = ~(theColor.theParts.green);
      if(numChan > 2)
        theColor.theParts.blue  = ~(theColor.theParts.blue);
      if(numChan > 3)
        theColor.theParts.alpha = ~(theColor.theParts.alpha);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = ~(theColor.thePartsA[i]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMultClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = clipTop(theColor.theParts.red   * color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = clipTop(theColor.theParts.green * color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = clipTop(theColor.theParts.blue  * color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = clipTop(theColor.theParts.alpha * color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clipTop(theColor.thePartsA[i]   * color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmGmeanClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = clipTop(sqrt((clrChanIArthT)theColor.theParts.red   * color.theColor.theParts.red));
    if(numChan > 1)
      theColor.theParts.green = clipTop(sqrt((clrChanIArthT)theColor.theParts.green * color.theColor.theParts.green));
    if(numChan > 2)
      theColor.theParts.blue  = clipTop(sqrt((clrChanIArthT)theColor.theParts.blue  * color.theColor.theParts.blue));
    if(numChan > 3)
      theColor.theParts.alpha = clipTop(sqrt((clrChanIArthT)theColor.theParts.alpha * color.theColor.theParts.alpha));
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clipTop(sqrt((clrChanIArthT)theColor.thePartsA[i]   * color.theColor.thePartsA[i]));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmAddClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = clipTop(theColor.theParts.red   + color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = clipTop(theColor.theParts.green + color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = clipTop(theColor.theParts.blue  + color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = clipTop(theColor.theParts.alpha + color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clipTop(theColor.thePartsA[i]   + color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmAddDivClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color,
                                                                                               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> dcolor) {
    theColor.theParts.red     = clipTop((theColor.theParts.red   + color.theColor.theParts.red)   / dcolor.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = clipTop((theColor.theParts.green + color.theColor.theParts.green) / dcolor.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = clipTop((theColor.theParts.blue  + color.theColor.theParts.blue)  / dcolor.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = clipTop((theColor.theParts.alpha + color.theColor.theParts.alpha) / dcolor.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clipTop((theColor.thePartsA[i]   + color.theColor.thePartsA[i])   / dcolor.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmDiffClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = clipBot(theColor.theParts.red   - color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = clipBot(theColor.theParts.green - color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = clipBot(theColor.theParts.blue  - color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = clipBot(theColor.theParts.alpha - color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clipBot(theColor.thePartsA[i]   - color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmNegDiffClp(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = clipBot(color.theColor.theParts.red   - theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = clipBot(color.theColor.theParts.green - theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = clipBot(color.theColor.theParts.blue  - theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = clipBot(color.theColor.theParts.alpha - theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clipBot(color.theColor.thePartsA[i]   - theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmAbsDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = abs(theColor.theParts.red   - color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = abs(theColor.theParts.green - color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = abs(theColor.theParts.blue  - color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = abs(theColor.theParts.alpha - color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = abs(theColor.thePartsA[i]   - color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmSqDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = (theColor.theParts.red   - color.theColor.theParts.red) *
      (theColor.theParts.red   - color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = (theColor.theParts.green - color.theColor.theParts.green) *
        (theColor.theParts.green - color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = (theColor.theParts.blue  - color.theColor.theParts.blue) *
        (theColor.theParts.blue  - color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = (theColor.theParts.alpha - color.theColor.theParts.alpha) *
        (theColor.theParts.alpha - color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (theColor.thePartsA[i]   - color.theColor.thePartsA[i]) *
          (theColor.thePartsA[i]   - color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMax(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(theColor.theParts.red < color.theColor.theParts.red)
      theColor.theParts.red = color.theColor.theParts.red;
    if(numChan > 1)
      if(theColor.theParts.green < color.theColor.theParts.green)
        theColor.theParts.green = color.theColor.theParts.green;
    if(numChan > 2)
      if(theColor.theParts.blue < color.theColor.theParts.blue)
        theColor.theParts.blue = color.theColor.theParts.blue;
    if(numChan > 3)
      if(theColor.theParts.alpha < color.theColor.theParts.alpha)
        theColor.theParts.alpha = color.theColor.theParts.alpha;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        if(theColor.thePartsA[i] < color.theColor.thePartsA[i])
          theColor.thePartsA[i] = color.theColor.thePartsA[i];
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMin(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(theColor.theParts.red > color.theColor.theParts.red)
      theColor.theParts.red = color.theColor.theParts.red;
    if(numChan > 1)
      if(theColor.theParts.green > color.theColor.theParts.green)
        theColor.theParts.green = color.theColor.theParts.green;
    if(numChan > 2)
      if(theColor.theParts.blue > color.theColor.theParts.blue)
        theColor.theParts.blue = color.theColor.theParts.blue;
    if(numChan > 3)
      if(theColor.theParts.alpha > color.theColor.theParts.alpha)
        theColor.theParts.alpha = color.theColor.theParts.alpha;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        if(theColor.thePartsA[i] > color.theColor.thePartsA[i])
          theColor.thePartsA[i] = color.theColor.thePartsA[i];
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmAdd(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {

    theColor.theParts.red     = (theColor.theParts.red   + color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = (theColor.theParts.green + color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = (theColor.theParts.blue  + color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = (theColor.theParts.alpha + color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (theColor.thePartsA[i]   + color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmDiv(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = (theColor.theParts.red   / color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = (theColor.theParts.green / color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = (theColor.theParts.blue  / color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = (theColor.theParts.alpha / color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (theColor.thePartsA[i]   / color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMult(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red   = (theColor.theParts.red   * color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = (theColor.theParts.green  * color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = (theColor.theParts.blue   * color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha  = (theColor.theParts.alpha * color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i]  = (theColor.thePartsA[i]   * color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmGmean(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = sqrt((clrChanIArthT)theColor.theParts.red   * color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = sqrt((clrChanIArthT)theColor.theParts.green * color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = sqrt((clrChanIArthT)theColor.theParts.blue  * color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = sqrt((clrChanIArthT)theColor.theParts.alpha * color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = sqrt((clrChanIArthT)theColor.thePartsA[i]   * color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMean(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    // Note the 2's will convert everything to integers so we get a good mean.
    theColor.theParts.red     = (theColor.theParts.red   + color.theColor.theParts.red)   /2;
    if(numChan > 1)
      theColor.theParts.green = (theColor.theParts.green + color.theColor.theParts.green) /2;
    if(numChan > 2)
      theColor.theParts.blue  = (theColor.theParts.blue  + color.theColor.theParts.blue)  /2;
    if(numChan > 3)
      theColor.theParts.alpha = (theColor.theParts.alpha + color.theColor.theParts.alpha) /2;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (theColor.thePartsA[i]   + color.theColor.thePartsA[i])   /2;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmDiff(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = (theColor.theParts.red   - color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = (theColor.theParts.green - color.theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = (theColor.theParts.blue  - color.theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = (theColor.theParts.alpha - color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (theColor.thePartsA[i]   - color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMod(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    theColor.theParts.red     = (theColor.theParts.red   % color.theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = (theColor.theParts.green % color.theColor.theParts.green);
    if(numChan > 1)
      theColor.theParts.blue  = (theColor.theParts.blue  % color.theColor.theParts.blue);
    if(numChan > 1)
      theColor.theParts.alpha = (theColor.theParts.alpha % color.theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (theColor.thePartsA[i]   % color.theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMaxI(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(numChan == 1) {                                         // 1 channel
      if((theColor.theParts.red) < (color.theColor.theParts.red)) {
        tfrmCopy(color);
      }
    } else if(numChan == 2) {                                  // 2 channels
      if((theColor.theParts.red +
          theColor.theParts.green) < (color.theColor.theParts.red +
                                      color.theColor.theParts.green)) {
        tfrmCopy(color);
      }
    } else if(numChan == 3) {                                  // 3 channels
      if((theColor.theParts.red   +
          theColor.theParts.green +
          theColor.theParts.blue) < (color.theColor.theParts.red   +
                                     color.theColor.theParts.green +
                                     color.theColor.theParts.blue)) {
        tfrmCopy(color);
      }
    } else if(numChan == 4) {                                  // 4 channels
      if((theColor.theParts.red   +
          theColor.theParts.green +
          theColor.theParts.blue  +
          theColor.theParts.alpha ) < (color.theColor.theParts.red   +
                                       color.theColor.theParts.green +
                                       color.theColor.theParts.blue  +
                                       color.theColor.theParts.alpha)) {
        tfrmCopy(color);
      }
    } else {                                                   // 5 or more channels
      clrChanIArthT thisSum = (theColor.theParts.red   +
                               theColor.theParts.green +
                               theColor.theParts.blue  +
                               theColor.theParts.alpha);
      clrChanIArthT thatSum = (color.theColor.theParts.red   +
                               color.theColor.theParts.green +
                               color.theColor.theParts.blue  +
                               color.theColor.theParts.alpha);
      for(int i=4; i<numChan; i++) {
        thisSum += theColor.thePartsA[i];
        thisSum += color.theColor.thePartsA[i];
      }
      if(thisSum < thatSum)
        tfrmCopy(color);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmMinI(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(numChan == 1) {                                         // 1 channel
      if((theColor.theParts.red) > (color.theColor.theParts.red)) {
        tfrmCopy(color);
      }
    } else if(numChan == 2) {                                  // 2 channels
      if((theColor.theParts.red   +
          theColor.theParts.green)   > (color.theColor.theParts.red   +
                                        color.theColor.theParts.green)) {
        tfrmCopy(color);
      }
    } else if(numChan == 3) {                                  // 3 channels
      if((theColor.theParts.red   +
          theColor.theParts.green +
          theColor.theParts.blue)   > (color.theColor.theParts.red   +
                                       color.theColor.theParts.green +
                                       color.theColor.theParts.blue)) {
        tfrmCopy(color);
      }
    } else if(numChan == 4) {                                  // 4 channels
      if((theColor.theParts.red   +
          theColor.theParts.green +
          theColor.theParts.blue  +
          theColor.theParts.alpha ) > (color.theColor.theParts.red   +
                                       color.theColor.theParts.green +
                                       color.theColor.theParts.blue  +
                                       color.theColor.theParts.alpha)) {
        tfrmCopy(color);
      }
    } else {                                                   // 5 or more channels
      clrChanIArthT thisSum = (theColor.theParts.red   +
                               theColor.theParts.green +
                               theColor.theParts.blue  +
                               theColor.theParts.alpha);
      clrChanIArthT thatSum = (color.theColor.theParts.red   +
                               color.theColor.theParts.green +
                               color.theColor.theParts.blue  +
                               color.theColor.theParts.alpha);
      for(int i=4; i<numChan; i++) {
        thisSum += theColor.thePartsA[i];
        thisSum += color.theColor.thePartsA[i];
      }
      if(thisSum > thatSum)
        tfrmCopy(color);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorRGB(clrChanT r, clrChanT g, clrChanT b) {
    theColor.theParts.red = r;
    if(numChan > 1)
      theColor.theParts.green = g;
    if(numChan > 2)
      theColor.theParts.blue = b;
    if(numChan > 3)
      theColor.theParts.alpha = minChanVal;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = minChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorRGBA(clrChanT r, clrChanT g, clrChanT b, clrChanT a) {
    theColor.theParts.red = r;
    if(numChan > 1)
      theColor.theParts.green = g;
    if(numChan > 2)
      theColor.theParts.blue = b;
    if(numChan > 3)
      theColor.theParts.alpha = a;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = minChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromColor(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> color) {
    if(fastMask)
      theColor.theInt = color.theColor.theInt;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i] = color.theColor.thePartsA[i];
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromLetter(char colorChar) {
    /* This case is ordered by the frequency in which colors are generally encountered.  This will vary for different applications. */
    switch(colorChar) {
    case '0': setToBlack();   break;
    case 'w':
    case 'W': setToWhite();   break;
    case 'r':
    case 'R': setToRed();     break;
    case 'g':
    case 'G': setToGreen();   break;
    case 'b':
    case 'B': setToBlue();    break;
    case 'y':
    case 'Y': setToYellow();  break;
    case 'c':
    case 'C': setToCyan();    break;
    case 'm':
    case 'M': setToMagenta(); break;
    default:  SET_ERR_COLOR;  break;
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromString(const char *colorString) {
    if( (colorString[0] == 'b') || (colorString[0] == 'B') ) {
      // Take care of blue and black (ambiguous first letter 'b')
      if( (colorString[2]=='u') || (colorString[2]=='U') )
        setToBlue();
      else
        setToBlack();
    } else if(colorString[0] == '#') {
      // Take care of #aabbcc.. color specs (HTML style)
      int numChanGiven = int((std::strlen(colorString)-1)/2);
      if(numChanGiven < 1) {
        SET_ERR_COLOR;
      } else {
        char curHexStr[3];
        clrChanT curCmp;
        curHexStr[2] = '\0';
        for(int i=0; i<std::min(numChan, numChanGiven); i++) {
          curHexStr[0] = colorString[1+2*i];
          curHexStr[1] = colorString[1+2*i+1];
          curCmp = clrChanT(strtol(curHexStr, NULL, 16));
          setChan(i, curCmp);
        }
      }
    } else {
      // Take care of the rest of the colors.
      setColorFromLetter(colorString[0]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFrom8bit(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    clrChanT convertedValueR, convertedValueG, convertedValueB, convertedValueA;
    if(channelType8bitInt) {
      convertedValueR = clrChanT(r);
      convertedValueG = clrChanT(g);
      convertedValueB = clrChanT(b);
      convertedValueA = clrChanT(a);
    } else {
      convertedValueR = clrChanT(maxChanVal * r / 255.0);
      convertedValueG = clrChanT(maxChanVal * g / 255.0);
      convertedValueB = clrChanT(maxChanVal * b / 255.0);
      convertedValueA = clrChanT(maxChanVal * a / 255.0);
    }
    setColorRGBA(convertedValueR, convertedValueG, convertedValueB, convertedValueA);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFrom8bit(uint8_t r, uint8_t g, uint8_t b) {
    clrChanT convertedValueR, convertedValueG, convertedValueB;
    if(channelType8bitInt) {
      convertedValueR = clrChanT(r);
      convertedValueG = clrChanT(g);
      convertedValueB = clrChanT(b);
    } else {
      convertedValueR = clrChanT(maxChanVal * r / 255.0);
      convertedValueG = clrChanT(maxChanVal * g / 255.0);
      convertedValueB = clrChanT(maxChanVal * b / 255.0);
    }
    setColorRGB(convertedValueR, convertedValueG, convertedValueB);
    return *this;
  }
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromF(clrChanFArthT r, clrChanFArthT g, clrChanFArthT b, clrChanFArthT a) {
    setColorRGBA(clrChanT(r*maxChanVal), clrChanT(g*maxChanVal), clrChanT(b*maxChanVal), clrChanT(a*maxChanVal));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromF(clrChanFArthT r, clrChanFArthT g, clrChanFArthT b) {
    setColorRGB(clrChanT(r*maxChanVal), clrChanT(g*maxChanVal), clrChanT(b*maxChanVal));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromPackedIntRGBA(uint32_t anInt) {
    uint8_t aByte;
    aByte = 0xFF & anInt; setRed8bit(aByte);
    if(numChan > 1) { anInt = anInt >> 8; aByte = 0xFF & anInt; setGreen8bit(aByte); }
    if(numChan > 2) { anInt = anInt >> 8; aByte = 0xFF & anInt; setBlue8bit(aByte);  }
    if(numChan > 3) { anInt = anInt >> 8; aByte = 0xFF & anInt; setAlpha8bit(aByte); }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromPackedIntRGBA(uint32_t anInt,
                                                                                                           uint8_t rIdx, uint8_t gIdx, uint8_t bIdx, uint8_t aIdx) {
    uint8_t *curByte = (uint8_t *)(&anInt);
    theColor.theParts.red                    = curByte[rIdx];
    if(numChan > 1) theColor.theParts.green  = curByte[gIdx];
    if(numChan > 2) theColor.theParts.blue   = curByte[bIdx];
    if(numChan > 3) theColor.theParts.alpha  = curByte[aIdx];
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmLinearGreyLevelScale(float c, float b) {
    theColor.theParts.red     = clrChanT(c * theColor.theParts.red   + b);
    if(numChan > 1)
      theColor.theParts.green = clrChanT(c * theColor.theParts.green + b);
    if(numChan > 2)
      theColor.theParts.blue  = clrChanT(c * theColor.theParts.blue  + b);
    if(numChan > 3)
      theColor.theParts.alpha = clrChanT(c * theColor.theParts.alpha + b);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clrChanT(c * theColor.thePartsA[i] + b);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmLinearGreyLevelScale(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> from1,
                                                                                                          colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> from2,
                                                                                                          colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> to1,
                                                                                                          colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> to2) {
    float c = 1.0*(to1.getRed()-to2.getRed())/(from1.getRed()-from2.getRed());
    float b = to1.getRed() - 1.0*c*from1.getRed();
    theColor.theParts.red     = clrChanT(c * theColor.theParts.red   + b);
    if(numChan > 1) {
      float c = 1.0*(to1.getGreen()-to2.getGreen())/(from1.getGreen()-from2.getGreen());
      float b = to1.getGreen() - 1.0*c*from1.getGreen();
      theColor.theParts.green = clrChanT(c * theColor.theParts.green + b);
    }
    if(numChan > 2) {
      float c = 1.0*(to1.getBlue()-to2.getBlue())/(from1.getBlue()-from2.getBlue());
      float b = to1.getBlue() - 1.0*c*from1.getBlue();
      theColor.theParts.blue  = clrChanT(c * theColor.theParts.blue  + b);
    }
    if(numChan > 3) {
      float c = 1.0*(to1.getAlpha()-to2.getAlpha())/(from1.getAlpha()-from2.getAlpha());
      float b = to1.getAlpha() - 1.0*c*from1.getAlpha();
      theColor.theParts.alpha = clrChanT(c * theColor.theParts.alpha + b);
    }
    if(numChan > 4)
      for(int i=4; i<numChan; i++) {
        float c = 1.0*(to1.getChan(i)-to2.getChan(i))/(from1.getChan(i)-from2.getChan(i));
        float b = to1.getChan(i) - 1.0*c*from1.getChan(i);
        theColor.thePartsA[i] = clrChanT(c * theColor.thePartsA[i] + b);
      }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmLinearGreyLevelScale(float rc, float rb, float gc, float gb, float bc, float bb) {
    theColor.theParts.red     = clrChanT(rc * theColor.theParts.red   + rb);
    if(numChan > 1)
      theColor.theParts.green = clrChanT(gc * theColor.theParts.green + gb);
    if(numChan > 2)
      theColor.theParts.blue  = clrChanT(bc * theColor.theParts.blue  + bb);
    if(numChan > 3)
      theColor.theParts.alpha = clrChanT(bc * theColor.theParts.alpha + bb);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmGreyScale(void) {
    double theGreyLevel = theColor.theParts.red   * 0.2126 +
      theColor.theParts.green * 0.7152 +
      theColor.theParts.blue  * 0.0722;
    theColor.theParts.red     = clrChanT(theGreyLevel);
    if(numChan > 1)
      theColor.theParts.green = clrChanT(theGreyLevel);
    if(numChan > 2)
      theColor.theParts.blue  = clrChanT(theGreyLevel);
    if(numChan > 3)
      theColor.theParts.alpha = clrChanT(theGreyLevel);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = clrChanT(theGreyLevel);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmStdPow(float p) {
    theColor.theParts.red     = (clrChanT)(pow(theColor.theParts.red/(float)maxChanVal,   p) * maxChanVal);
    if(numChan > 1)
      theColor.theParts.green = (clrChanT)(pow(theColor.theParts.green/(float)maxChanVal, p) * maxChanVal);
    if(numChan > 2)
      theColor.theParts.blue  = (clrChanT)(pow(theColor.theParts.blue/(float)maxChanVal,  p) * maxChanVal);
    if(numChan > 3)
      theColor.theParts.alpha = (clrChanT)(pow(theColor.theParts.alpha/(float)maxChanVal, p) * maxChanVal);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (clrChanT)(pow(theColor.thePartsA[i]/(float)maxChanVal,   p) * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmStdPowSqr(void) {
    theColor.theParts.red     = (clrChanT)(theColor.theParts.red   * theColor.theParts.red   / (double)maxChanVal);
    if(numChan > 1)
      theColor.theParts.green = (clrChanT)(theColor.theParts.green * theColor.theParts.green / (double)maxChanVal);
    if(numChan > 2)
      theColor.theParts.blue  = (clrChanT)(theColor.theParts.blue  * theColor.theParts.blue  / (double)maxChanVal);
    if(numChan > 3)
      theColor.theParts.alpha = (clrChanT)(theColor.theParts.alpha * theColor.theParts.alpha / (double)maxChanVal);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (clrChanT)(theColor.thePartsA[i]   * theColor.thePartsA[i]   / (double)maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmStdPowSqrt(void) {
    theColor.theParts.red     = (clrChanT)(sqrt(theColor.theParts.red/(double)maxChanVal)   * maxChanVal);
    if(numChan > 1)
      theColor.theParts.green = (clrChanT)(sqrt(theColor.theParts.green/(double)maxChanVal) * maxChanVal);
    if(numChan > 2)
      theColor.theParts.blue  = (clrChanT)(sqrt(theColor.theParts.blue/(double)maxChanVal)  * maxChanVal);
    if(numChan > 3)
      theColor.theParts.alpha = (clrChanT)(sqrt(theColor.theParts.alpha/(double)maxChanVal) * maxChanVal);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (clrChanT)(sqrt(theColor.thePartsA[i]/(double)maxChanVal)   * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmStdPow(float rp, float gp, float bp) {
    theColor.theParts.red     = (clrChanT)(pow(theColor.theParts.red/(float)maxChanVal,   rp) * maxChanVal);
    if(numChan > 1)
      theColor.theParts.green = (clrChanT)(pow(theColor.theParts.green/(float)maxChanVal, gp) * maxChanVal);
    if(numChan > 2)
      theColor.theParts.blue  = (clrChanT)(pow(theColor.theParts.blue/(float)maxChanVal,  bp) * maxChanVal);
    if(numChan > 3)
      theColor.theParts.alpha = (clrChanT)(pow(theColor.theParts.alpha/(float)maxChanVal, bp) * maxChanVal);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = (clrChanT)(pow(theColor.thePartsA[i]/(float)maxChanVal, bp) * maxChanVal);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmSaw(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> lowCol,
                                                                                         colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> highCol) {
    theColor.theParts.red     = ((lowCol.theColor.theParts.red   <= theColor.theParts.red)   && (highCol.theColor.theParts.red   >= theColor.theParts.red)?theColor.theParts.red:0);
    if(numChan > 1)
      theColor.theParts.green = ((lowCol.theColor.theParts.green <= theColor.theParts.green) && (highCol.theColor.theParts.green >= theColor.theParts.green)?theColor.theParts.green:0);
    if(numChan > 2)
      theColor.theParts.blue  = ((lowCol.theColor.theParts.blue  <= theColor.theParts.blue)  && (highCol.theColor.theParts.blue  >= theColor.theParts.blue)?theColor.theParts.green:0);
    if(numChan > 3)
      theColor.theParts.alpha = ((lowCol.theColor.theParts.alpha  <= theColor.theParts.alpha)  && (highCol.theColor.theParts.alpha  >= theColor.theParts.alpha)?theColor.theParts.green:0);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i]   = ((lowCol.theColor.thePartsA[i]  <= theColor.thePartsA[i])  && (highCol.theColor.thePartsA[i]  >= theColor.thePartsA[i])?theColor.theParts.green:0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmStep(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> lowCol,
                                                                                          colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> highCol) {
    theColor.theParts.red     = ((lowCol.theColor.theParts.red   <= theColor.theParts.red)   && (highCol.theColor.theParts.red   >= theColor.theParts.red)?maxChanVal:0);
    if(numChan > 1)
      theColor.theParts.green = ((lowCol.theColor.theParts.green <= theColor.theParts.green) && (highCol.theColor.theParts.green >= theColor.theParts.green)?maxChanVal:0);
    if(numChan > 2)
      theColor.theParts.blue  = ((lowCol.theColor.theParts.blue  <= theColor.theParts.blue)  && (highCol.theColor.theParts.blue  >= theColor.theParts.blue)?maxChanVal:0);
    if(numChan > 3)
      theColor.theParts.alpha = ((lowCol.theColor.theParts.alpha <= theColor.theParts.alpha) && (highCol.theColor.theParts.alpha >= theColor.theParts.alpha)?maxChanVal:0);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = ((lowCol.theColor.thePartsA[i]   <= theColor.thePartsA[i])   && (highCol.theColor.thePartsA[i]   >= theColor.thePartsA[i])?maxChanVal:0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmShiftL(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol) {
    theColor.theParts.red     = theColor.theParts.red   << aCol.theColor.theParts.red;
    if(numChan > 1)
      theColor.theParts.green = theColor.theParts.green << aCol.theColor.theParts.green;
    if(numChan > 2)
      theColor.theParts.blue  = theColor.theParts.blue  << aCol.theColor.theParts.blue;
    if(numChan > 3)
      theColor.theParts.alpha = theColor.theParts.alpha << aCol.theColor.theParts.alpha;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = theColor.thePartsA[i]   << aCol.theColor.thePartsA[i];
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmShiftR(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol) {
    theColor.theParts.red     = theColor.theParts.red   >> aCol.theColor.theParts.red;
    if(numChan > 1)
      theColor.theParts.green = theColor.theParts.green >> aCol.theColor.theParts.green;
    if(numChan > 2)
      theColor.theParts.blue  = theColor.theParts.blue  >> aCol.theColor.theParts.blue;
    if(numChan > 3)
      theColor.theParts.alpha = theColor.theParts.alpha >> aCol.theColor.theParts.alpha;
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = theColor.thePartsA[i]   >> aCol.theColor.thePartsA[i];
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmDiracTot(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol) {
    if(numChan == 1) {                                         // 1 channel
      if(aCol.theColor.theParts.red   == theColor.theParts.red)
        setToWhite();
      else
        setToBlack();
    } else if(numChan == 2) {                                  // 2 channels
      if((aCol.theColor.theParts.red   == theColor.theParts.red)   &&
         (aCol.theColor.theParts.green == theColor.theParts.green)) {
        setToWhite();
      } else {
        setToBlack();
      }
    } else if(numChan == 3) {                                  // 3 channels
      if((aCol.theColor.theParts.red   == theColor.theParts.red)   &&
         (aCol.theColor.theParts.green == theColor.theParts.green) &&
         (aCol.theColor.theParts.blue  == theColor.theParts.blue)) {
        setToWhite();
      } else {
        setToBlack();
      }
    } else if(numChan == 4) {                                  // 4 channels
      if((aCol.theColor.theParts.red   == theColor.theParts.red)   &&
         (aCol.theColor.theParts.green == theColor.theParts.green) &&
         (aCol.theColor.theParts.blue  == theColor.theParts.blue)  &&
         (aCol.theColor.theParts.alpha == theColor.theParts.alpha)) {
        setToWhite();
      } else {
        setToBlack();
      }
    } else {                                                   // 5 or more channels
      int isWhite=1;
      for(int i=4; (i<numChan)&&(isWhite); i++)
        if(aCol.theColor.thePartsA[i] != theColor.thePartsA[i])
          isWhite=0;
      if(isWhite)
        setToWhite();
      else
        setToBlack();
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmDirac(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aCol) {
    theColor.theParts.red     = ((aCol.theColor.theParts.red   == theColor.theParts.red)?maxChanVal:0);
    if(numChan > 1)
      theColor.theParts.green = ((aCol.theColor.theParts.green == theColor.theParts.green)?maxChanVal:0);
    if(numChan > 2)
      theColor.theParts.blue  = ((aCol.theColor.theParts.blue  == theColor.theParts.blue)?maxChanVal:0);
    if(numChan > 3)
      theColor.theParts.alpha = ((aCol.theColor.theParts.alpha == theColor.theParts.alpha)?maxChanVal:0);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = ((aCol.theColor.thePartsA[i] == theColor.thePartsA[i])?maxChanVal:0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmFuzzyDirac(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> ctrCol,
                                                                                                colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> radCol) {
    theColor.theParts.red     = ((abs(ctrCol.theColor.theParts.red   - theColor.theParts.red)   <= radCol.theColor.theParts.red  )?maxChanVal:0);
    if(numChan > 1)
      theColor.theParts.green = ((abs(ctrCol.theColor.theParts.green - theColor.theParts.green)  <= radCol.theColor.theParts.green)?maxChanVal:0);
    if(numChan > 2)
      theColor.theParts.blue  = ((abs(ctrCol.theColor.theParts.blue  - theColor.theParts.blue)   <= radCol.theColor.theParts.blue )?maxChanVal:0);
    if(numChan > 3)
      theColor.theParts.alpha = ((abs(ctrCol.theColor.theParts.alpha  - theColor.theParts.alpha) <= radCol.theColor.theParts.alpha )?maxChanVal:0);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = ((abs(ctrCol.theColor.thePartsA[i]  - theColor.thePartsA[i]) <= radCol.theColor.thePartsA[i] )?maxChanVal:0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  inline void colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setChanToMin() {
    if(fastMask)
      theColor.theInt = 0;
    else 
      std::fill_n(theColor.thePartsA, numChan, minChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  inline void colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setChanToMax() {
    if(fastMaskUnsignedInt)
      theColor.theInt = ~0;
    else 
      std::fill_n(theColor.thePartsA, numChan, maxChanVal);
  }

  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToBlack() {
    setChanToMin();
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @todo Make this fast. */
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToWhite() {
    setChanToMax();
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToRed() {
    setChanToMin();
    theColor.theParts.red = maxChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToGreen() {
    setChanToMin();
    theColor.theParts.green = maxChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToBlue() {
    setChanToMin();
    theColor.theParts.blue = maxChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToCyan() {
    setChanToMin();
    theColor.theParts.green = maxChanVal;
    theColor.theParts.blue  = maxChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToYellow() {
    setChanToMin();
    theColor.theParts.red   = maxChanVal;
    theColor.theParts.green = maxChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setToMagenta() {
    setChanToMin();
    theColor.theParts.red  = maxChanVal;
    theColor.theParts.blue = maxChanVal;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromCorner(cornerColor ccolor) {
    switch(ccolor) {
    case cornerColor::BLACK:    return setToBlack();   break;
    case cornerColor::WHITE:    return setToWhite();   break;
    case cornerColor::RED:      return setToRed();     break;
    case cornerColor::GREEN:    return setToGreen();   break;
    case cornerColor::BLUE:     return setToBlue();    break;
    case cornerColor::YELLOW:   return setToYellow();  break;
    case cornerColor::CYAN:     return setToCyan();    break;
    case cornerColor::MAGENTA:  return setToMagenta(); break;
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpGreyTGA16bit(int anInt) {
    anInt = IDXCOND(anInt, 65536);
    if( (anInt < 0) || (anInt > 65536) ) {
      SET_ERR_COLOR;
    } else {
      setGreen8bit(anInt         & 0xff);
      setBlue8bit( (anInt >> 8)  & 0xff);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpGreyTGA24bit(int anInt) {
    anInt = IDXCOND(anInt, 16777216);
    if( (anInt < 0) || (anInt > 16777216) ) {
      SET_ERR_COLOR;
    } else {
      setGreen8bit(anInt         & 0xff);
      setBlue8bit( (anInt >> 8)  & 0xff);
      setRed8bit(  (anInt >> 16) & 0xff);
    }
    return *this;
  }
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRainbowHSV(int base, int anInt) {
    anInt = IDXCOND(anInt, base);
    if( (anInt < minChanVal) || (anInt > base) )
      SET_ERR_COLOR;
    else 
      setColorFromUnitHSV(1.0*anInt/base, 1.0, 1.0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRainbowLA(int base, int anInt) {
    anInt = IDXCOND(anInt, base);
    if( (anInt < minChanVal) || (anInt > base) ) 
      SET_ERR_COLOR;
    else 
      setColorFromWavelengthLA((1.0*anInt/base)*(maxWavelength-minWavelength)+minWavelength);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRainbowCM(int base, int anInt) {
    anInt = IDXCOND(anInt, base);
    if( (anInt < minChanVal) || (anInt > base) ) 
      SET_ERR_COLOR;
    else 
      setColorFromWavelengthCM((1.0*anInt/base)*(maxWavelength-minWavelength)+minWavelength, 3);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRainbowCM(int base, int anInt, int INTRP) {
    anInt = IDXCOND(anInt, base);
    if( (anInt < minChanVal) || (anInt > base) ) 
      SET_ERR_COLOR;
    else 
      setColorFromWavelengthCM((1.0*anInt/base)*(maxWavelength-minWavelength)+minWavelength, INTRP);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpClrCubeRainbow(int anInt) {
    cmpColorRamp(anInt, "RYGCBMR");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRampGrey2R(int anInt) {
    if( (anInt < 0) || (anInt > meanChanVal) ) 
      SET_ERR_COLOR;
    else 
      setColorRGB(meanChanVal+anInt, meanChanVal-anInt, meanChanVal-anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRampGrey2G(int anInt) {
    if( (anInt < 0) || (anInt > meanChanVal) ) 
      SET_ERR_COLOR;
    else 
      setColorRGB(meanChanVal-anInt, meanChanVal+anInt, meanChanVal-anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRampGrey2B(int anInt) {
    if( (anInt < 0) || (anInt > meanChanVal) ) 
      SET_ERR_COLOR;
    else 
      setColorRGB(meanChanVal-anInt, meanChanVal-anInt, meanChanVal+anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRampGrey2Y(int anInt) {
    if( (anInt < 0) || (anInt > meanChanVal) ) 
      SET_ERR_COLOR;
    else 
      setColorRGB(meanChanVal+anInt, meanChanVal+anInt, meanChanVal-anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRampGrey2C(int anInt) {
    if( (anInt < 0) || (anInt > meanChanVal) ) 
      SET_ERR_COLOR;
    else 
      setColorRGB(meanChanVal-anInt, meanChanVal+anInt, meanChanVal+anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpRampGrey2M(int anInt) {
    if( (anInt < 0) || (anInt > meanChanVal) )
      SET_ERR_COLOR;
    else 
      setColorRGB(meanChanVal+anInt, meanChanVal-anInt, meanChanVal+anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpGrey(int anInt) {
    if( (anInt < minChanVal) || (anInt > maxChanVal) )
      SET_ERR_COLOR;
    else
      for(int i=0; i<numChan; i++)
        theColor.thePartsA[i]  = clrChanT(anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpDiagRampCR(int anInt) {
    cmpColorRamp(anInt, "CR");
    return *this;
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpDiagRampMG(int anInt) {
    cmpColorRamp(anInt, "MG");
    return *this;
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpDiagRampYB(int anInt) {
    cmpColorRamp(anInt, "YB");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpConstTwoRamp(int anInt) {
    cmpColorRamp(anInt, "CMYC");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpConstOneRamp(int anInt) {
    cmpColorRamp(anInt, "BRGB");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpGreyRGB(int anInt) {
    cmpColorRamp(anInt, "0W");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpGrey3x(int anInt) {
    if( (anInt < minChanVal) || (anInt > (3*maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      setColorRGB(clrChanT(anInt / 3 + (anInt%3==0?1:0)),
                  clrChanT(anInt / 3 + (anInt%3==1?1:0)),
                  clrChanT(anInt / 3 + (anInt%3==2?1:0)));
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpGrey4x(int anInt) {
    if( (anInt < minChanVal) || (anInt > (4*maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      setColorRGB(clrChanT(anInt / 4 + ((anInt+1)%4==0?1:0)),
                  clrChanT(anInt / 4 + ((anInt+2)%4==0?1:0)),
                  clrChanT(anInt / 4 + ((anInt+3)%4==0?1:0)));
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpColorRamp(double aDouble,
                                                                                              int numColors,
                                                                                              double *anchors,
                                                                                              colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> *colors) {
    double lowAnchor, highAnchor;
    if(anchors == NULL) {
      lowAnchor  = 0.0;
      highAnchor = 1.0;
    } else {
      lowAnchor  = anchors[0];
      highAnchor = anchors[numColors-1];
    }
    if( (numColors < 2) || (aDouble < lowAnchor) || (aDouble > highAnchor) ) {
      return SET_ERR_COLOR;
    } else {
      for(int i=0; i<(numColors-1); i++) {
        if(anchors == NULL) {
          lowAnchor  = double(i)/(numColors-1);
          highAnchor = double(i+1)/(numColors-1);
        } else {
          lowAnchor  = anchors[i];
          highAnchor = anchors[i+1];
        }
        if( (aDouble >= lowAnchor) && (aDouble < highAnchor) ) {
          // We have found our place!
          double betweenDist = std::abs((aDouble-lowAnchor)/(highAnchor-lowAnchor));  // We 'abs' because of possible round off error.
          return interplColors(betweenDist, colors[i], colors[i+1]);
        }
      }
    }
    // If we get here, we didn't do anything... Duno how that could happen.. )
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpColorRamp(int anInt, const char *colChars) {
    return cmpColorRamp(anInt, (int)std::strlen(colChars), colChars);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpColorRamp(int anInt, int numColors, const char *colChars) {
    anInt = IDXCOND(anInt, (maxChanVal*(numColors-1)+1));
    if( (anInt < 0) || (anInt > (maxChanVal*(numColors-1)+1)) ) {
      SET_ERR_COLOR;
    } else {
      if(anInt == 0) {
        return setColorFromLetter(colChars[0]);
      } else {
        for(int i=0; i<(numColors-1); i++) {
          if(anInt <= maxChanVal) {
            // Note: This could be MUCH better optimized!
            colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> c1;
            colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> c2;
            c1.setColorFromLetter(colChars[i]);
            c2.setColorFromLetter(colChars[i+1]);
            clrChanT r, g, b;
            if(c1.getRed() > c2.getRed()) {
              r = maxChanVal - anInt;
            } else if(c1.getRed() < c2.getRed()) {
              r = anInt;
            } else {
              r = c1.getRed();
            }
            if(c1.getGreen() > c2.getGreen()) {
              g = maxChanVal - anInt;
            } else if(c1.getGreen() < c2.getGreen()) {
              g = anInt;
            } else {
              g = c1.getGreen();
            }
            if(c1.getBlue() > c2.getBlue()) {
              b = maxChanVal - anInt;
            } else if(c1.getBlue() < c2.getBlue()) {
              b = anInt;
            } else {
              b = c1.getBlue();
            }
            return setColorRGB(r, g, b);
          } else {
            anInt = anInt - maxChanVal;
          }
        }
        // This is impossible (as anInt must be out of range, but we already checked for that)
        SET_ERR_COLOR;
      }
    }
    // If we got here, we had a problem.
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::interplColors(double aDouble,
                                                                                               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2) {
    if( (aDouble < 0.0) || (aDouble > 1.0) ) {
      SET_ERR_COLOR;
    } else {
      theColor.theParts.red      = clrChanT((col2.theColor.theParts.red   - col1.theColor.theParts.red  )*aDouble + col1.theColor.theParts.red);
      if(numChan > 1)
        theColor.theParts.green  = clrChanT((col2.theColor.theParts.green - col1.theColor.theParts.green)*aDouble + col1.theColor.theParts.green);
      if(numChan > 2)
        theColor.theParts.blue   = clrChanT((col2.theColor.theParts.blue  - col1.theColor.theParts.blue )*aDouble + col1.theColor.theParts.blue);
      if(numChan > 3)
        theColor.theParts.alpha  = clrChanT((col2.theColor.theParts.alpha - col1.theColor.theParts.alpha)*aDouble + col1.theColor.theParts.alpha);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i]  = clrChanT((col2.theColor.thePartsA[i]   - col1.theColor.thePartsA[i]  )*aDouble + col1.theColor.thePartsA[i]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::wMean(clrChanFArthT w1, clrChanFArthT w2, clrChanFArthT w3,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col3) {

    if((w1 < 0) || (w2 < 0) || (w3 < 0) || (w1 > 1) || (w2 > 1) || (w3 > 1) || (std::abs(w1+w2+w3-1) > 0.001)) {
      return SET_ERR_COLOR;
    } else {
      theColor.theParts.red     = (col1.theColor.theParts.red   * w1) + (col2.theColor.theParts.red   * w2) + (col3.theColor.theParts.red   * w3);
      if(numChan > 1)
        theColor.theParts.green = (col1.theColor.theParts.green * w1) + (col2.theColor.theParts.green * w2) + (col3.theColor.theParts.green * w3);
      if(numChan > 2)
        theColor.theParts.blue  = (col1.theColor.theParts.blue  * w1) + (col2.theColor.theParts.blue  * w2) + (col3.theColor.theParts.blue  * w3);
      if(numChan > 3)
        theColor.theParts.alpha = (col1.theColor.theParts.alpha * w1) + (col2.theColor.theParts.alpha * w2) + (col3.theColor.theParts.alpha * w3);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = (col1.theColor.thePartsA[i]   * w1) + (col2.theColor.thePartsA[i]   * w2) + (col3.theColor.thePartsA[i]   * w3);
      return *this;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::wMean(clrChanFArthT w1, clrChanFArthT w2, 
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col3) {
    return wMean(w1, w2, 1-w1-w2, col1, col2, col3);
  }

  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::wMean(clrChanFArthT w1, 
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2) {
    return wMean(w1, 1-w1, col1, col2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::wMean(clrChanFArthT w1, clrChanFArthT w2,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                       colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2) {
    if((w1 < 0) || (w2 < 0) || (w1 > 1) || (w2 > 1) || (std::abs(w1+w2-1) > 0.001)) {
      return SET_ERR_COLOR;
    } else {
      theColor.theParts.red     = (col1.theColor.theParts.red   * w1) + (col2.theColor.theParts.red   * w2);
      if(numChan > 1)
        theColor.theParts.green = (col1.theColor.theParts.green * w1) + (col2.theColor.theParts.green * w2);
      if(numChan > 2)
        theColor.theParts.blue  = (col1.theColor.theParts.blue  * w1) + (col2.theColor.theParts.blue  * w2);
      if(numChan > 3)
        theColor.theParts.alpha = (col1.theColor.theParts.alpha * w1) + (col2.theColor.theParts.alpha * w2);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i] = (col1.theColor.thePartsA[i]   * w1) + (col2.theColor.thePartsA[i]   * w2);
      return *this;
    }
  }
  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::interplColorsHLS(double aDouble,
                                                                                                  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col1,
                                                                                                  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> col2) {
    // Convert our given colors into HLS
    float H1, L1, S1;
    float H2, L2, S2;
    col1.rgb2hls(&H1, &L1, &S1);
    col2.rgb2hls(&H2, &L2, &S2);

    // Interpolate in HLS space..
    float Hi = (H2 - H1) * aDouble + H1;
    float Li = (L2 - L1) * aDouble + L1;
    float Si = (S2 - S1) * aDouble + S1;

    // Set the current color and return.
    setColorFromNaturalHLS(Hi, Li, Si);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::interplColors(double aDouble,
                                                                                               colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> tooCol) {
    if( (aDouble < 0.0) || (aDouble > 1.0) ) {
      SET_ERR_COLOR;
    } else {
      theColor.theParts.red      = clrChanT((tooCol.theColor.theParts.red   - theColor.theParts.red  )*aDouble + theColor.theParts.red);
      if(numChan > 1)
        theColor.theParts.green  = clrChanT((tooCol.theColor.theParts.green - theColor.theParts.green)*aDouble + theColor.theParts.green);
      if(numChan > 2)
        theColor.theParts.blue   = clrChanT((tooCol.theColor.theParts.blue  - theColor.theParts.blue )*aDouble + theColor.theParts.blue);
      if(numChan > 3)
        theColor.theParts.alpha  = clrChanT((tooCol.theColor.theParts.alpha - theColor.theParts.alpha)*aDouble + theColor.theParts.alpha);
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          theColor.thePartsA[i]  = clrChanT((tooCol.theColor.thePartsA[i]   - theColor.thePartsA[i]  )*aDouble + theColor.thePartsA[i]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpUpDownRampBr(int anInt) {
    cmpColorRamp(anInt, "YC");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpUpDownRampBg(int anInt) {
    cmpColorRamp(anInt, "YM");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpUpDownRampGr(int anInt) {
    cmpColorRamp(anInt, "MC");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpUpDownRampGb(int anInt) {
    cmpColorRamp(anInt, "MY");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpUpDownRampRg(int anInt) {
    cmpColorRamp(anInt, "CM");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpUpDownRampRb(int anInt) {
    cmpColorRamp(anInt, "CY");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpSumRampRGB(int anInt) {
    cmpColorRamp(anInt, "0RYW");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpSumRampBGR(int anInt) {
    cmpColorRamp(anInt, "0BCW");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpSumRampGRB(int anInt) {
    cmpColorRamp(anInt, "0GYW");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpSumRampGBR(int anInt) {
    cmpColorRamp(anInt, "0GCW");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpSumRampBRG(int anInt) {
    cmpColorRamp(anInt, "0BMW");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpSumRampRBG(int anInt) {
    cmpColorRamp(anInt, "0RMW");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpBinaryColorRampRG(int anInt, int threshold) {
    anInt = IDXCOND(anInt, maxChanVal);
    if( (anInt < minChanVal) || (anInt > (maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      if(anInt < threshold)
        setColorRGB(maxChanVal, minChanVal, minChanVal);
      else
        setColorRGB(minChanVal, maxChanVal, minChanVal);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpBinaryColorRampRB(int anInt, int threshold) {
    anInt = IDXCOND(anInt, maxChanVal);
    if( (anInt < minChanVal) || (anInt > (maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      if(anInt < threshold)
        setColorRGB(maxChanVal, minChanVal, minChanVal);
      else
        setColorRGB(minChanVal, minChanVal, maxChanVal);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpBinaryColorRampGR(int anInt, int threshold) {
    anInt = IDXCOND(anInt, maxChanVal);
    if( (anInt < minChanVal) || (anInt > (maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      if(anInt < threshold)
        setColorRGB(minChanVal, maxChanVal, minChanVal);
      else
        setColorRGB(maxChanVal, minChanVal, minChanVal);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpBinaryColorRampGB(int anInt, int threshold) {
    anInt = IDXCOND(anInt, maxChanVal);
    if( (anInt < minChanVal) || (anInt > (maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      if(anInt < threshold)
        setColorRGB(minChanVal, maxChanVal, minChanVal);
      else
        setColorRGB(minChanVal, minChanVal, maxChanVal);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpBinaryColorRampBR(int anInt, int threshold) {
    anInt = IDXCOND(anInt, maxChanVal);
    if( (anInt < minChanVal) || (anInt > (maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      if(anInt < threshold)
        setColorRGB(minChanVal, minChanVal, maxChanVal);
      else
        setColorRGB(maxChanVal, minChanVal, minChanVal);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpBinaryColorRampBG(int anInt, int threshold) {
    anInt = IDXCOND(anInt, maxChanVal);
    if( (anInt < minChanVal) || (anInt > (maxChanVal)) ) {
      SET_ERR_COLOR;
    } else {
      if(anInt < threshold)
        setColorRGB(minChanVal, minChanVal, maxChanVal);
      else
        setColorRGB(minChanVal, maxChanVal, minChanVal);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpFireRamp(int anInt) {
    cmpSumRampRGB(anInt);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpColdToHot(int anInt) {
    cmpColorRamp(anInt, "BCGYR");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::cmpIceToWaterToHot(int anInt) {
    cmpColorRamp(anInt, "WCBYR");
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorComp2WebSafeColorComp(clrChanT aColorComp) {
    clrChanT minCol;
    int minDist;
    uint8_t charCompVal;
    // Convert the compoent value to [0,255]
    if(channelType8bitInt)
      charCompVal = aColorComp;
    else
      charCompVal = (uint8_t)(255.0 * aColorComp / maxChanVal);
    // Find the closest component
    uint8_t posValue[6] = { 0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF };
    minDist = charCompVal;
    minCol = 0;
    for(int i=1;i<6;i++)
      if( abs(charCompVal - posValue[i]) < minDist ) {
        minDist = abs(charCompVal - posValue[i]);
        minCol = posValue[i];
      }
    return(minCol);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorComp2CloseColorComp(clrChanT aColorComp, clrChanT *discreetVals, int numVals) {
    clrChanT minCol = -1;
    int minDist = maxChanVal;
    // Find the closest of the discreetVals
    for(int i=0;i<numVals;i++)
      if( abs(aColorComp - discreetVals[i]) < minDist ) {
        minDist = abs(aColorComp - discreetVals[i]);
        minCol = discreetVals[i];
      }
    return(minCol);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmWebSafe216() {
    theColor.theParts.red     = colorComp2WebSafeColorComp(theColor.theParts.red);
    if(numChan > 1)
      theColor.theParts.green = colorComp2WebSafeColorComp(theColor.theParts.green);
    if(numChan > 2)
      theColor.theParts.blue  = colorComp2WebSafeColorComp(theColor.theParts.blue);
    if(numChan > 3)
      theColor.theParts.alpha = colorComp2WebSafeColorComp(theColor.theParts.alpha);
    if(numChan > 4)
      for(int i=4; i<numChan; i++)
        theColor.thePartsA[i] = colorComp2WebSafeColorComp(theColor.thePartsA[i]);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmWebSafePro216() {
    tfrmWebSafe216();
    int colIdx = 36 * (getRed8bit() / 0x33) + 6 * (getGreen8bit() / 0x33) + 1 * (getBlue8bit() / 0x33) + 1;
    if( (colIdx < 0) || (colIdx >= 218) ) {
      SET_ERR_COLOR;
    } else {
      setColorFromString(webSafeColorData[colIdx][1]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmWebSafeDeu216() {
    tfrmWebSafe216();
    int colIdx = 36 * (getRed8bit() / 0x33) + 6 * (getGreen8bit() / 0x33) + 1 * (getBlue8bit() / 0x33) + 1;
    if( (colIdx < 0) || (colIdx >= 218) ) {
      SET_ERR_COLOR;
    } else {
      setColorFromString(webSafeColorData[colIdx][2]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmWebSafeTri216() {
    tfrmWebSafe216();
    int colIdx = 36 * (getRed8bit() / 0x33) + 6 * (getGreen8bit() / 0x33) + 1 * (getBlue8bit() / 0x33) + 1;
    if( (colIdx < 0) || (colIdx >= 218) ) {
      SET_ERR_COLOR;
    } else {
      setColorFromString(webSafeColorData[colIdx][3]);
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::tfrmInvert() {
    theColor.theParts.red   = maxChanVal - theColor.theParts.red;
    theColor.theParts.green = maxChanVal - theColor.theParts.green;
    theColor.theParts.blue  = maxChanVal - theColor.theParts.blue;
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::color2GreyDotProd(int redWt, int greenWt, int blueWt) {
    return (theColor.theParts.red   * redWt +
            theColor.theParts.green * greenWt +
            theColor.theParts.blue  * blueWt);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  double
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorLuminance(void) {
    return (theColor.theParts.red   * 0.2126 +
            theColor.theParts.green * 0.7152 +
            theColor.theParts.blue  * 0.0722) / maxChanVal;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanIArthT
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorSumIntensity(void) {
    return (theColor.theParts.red   +
            theColor.theParts.green +
            theColor.theParts.blue);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  double
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::colorScaledIntensity(void) {
    return (theColor.theParts.red   +
            theColor.theParts.green +
            theColor.theParts.blue)   / (numChan * maxChanVal);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::distP2sq(
    colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor) {
    if(numChan == 1) {                                         // 1 channel
      return ((theColor.theParts.red   - aColor.theColor.theParts.red)   * (theColor.theParts.red   - aColor.theColor.theParts.red));
    } else if(numChan == 2) {                                  // 2 channels
      return ((theColor.theParts.red   - aColor.theColor.theParts.red)   * (theColor.theParts.red   - aColor.theColor.theParts.red) +
              (theColor.theParts.green - aColor.theColor.theParts.green) * (theColor.theParts.green - aColor.theColor.theParts.green));
    } else if(numChan == 3) {                                  // 3 channels
      return ((theColor.theParts.red   - aColor.theColor.theParts.red)   * (theColor.theParts.red   - aColor.theColor.theParts.red) +
              (theColor.theParts.green - aColor.theColor.theParts.green) * (theColor.theParts.green - aColor.theColor.theParts.green) +
              (theColor.theParts.blue  - aColor.theColor.theParts.blue)  * (theColor.theParts.blue  - aColor.theColor.theParts.blue));
    } else if(numChan == 4) {                                  // 4 channels
      return ((theColor.theParts.red   - aColor.theColor.theParts.red)   * (theColor.theParts.red   - aColor.theColor.theParts.red)   +
              (theColor.theParts.green - aColor.theColor.theParts.green) * (theColor.theParts.green - aColor.theColor.theParts.green) +
              (theColor.theParts.blue  - aColor.theColor.theParts.blue)  * (theColor.theParts.blue  - aColor.theColor.theParts.blue)  +
              (theColor.theParts.blue  - aColor.theColor.theParts.alpha) * (theColor.theParts.blue  - aColor.theColor.theParts.alpha));
    } else {                                                   // 5 or more channels
      clrChanIArthT daDist = ((theColor.theParts.red   - aColor.theColor.theParts.red)   * (theColor.theParts.red   - aColor.theColor.theParts.red)   +
                              (theColor.theParts.green - aColor.theColor.theParts.green) * (theColor.theParts.green - aColor.theColor.theParts.green) +
                              (theColor.theParts.blue  - aColor.theColor.theParts.blue)  * (theColor.theParts.blue  - aColor.theColor.theParts.blue)  +
                              (theColor.theParts.blue  - aColor.theColor.theParts.alpha) * (theColor.theParts.blue  - aColor.theColor.theParts.alpha));
      for(int i=4; i<numChan; i++)
        daDist +=          ((theColor.thePartsA[i]  - aColor.theColor.thePartsA[i]  ) * (theColor.thePartsA[i]   - aColor.theColor.thePartsA[i]));
      return daDist;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::dotProd(
    colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor) {
    if(numChan == 1) {                                         // 1 channel
      return (theColor.theParts.red    * aColor.theColor.theParts.red);
    } else if(numChan == 2) {                                  // 2 channels
      return ((theColor.theParts.red   * aColor.theColor.theParts.red)    +
              (theColor.theParts.green * aColor.theColor.theParts.green));
    } else if(numChan == 3) {                                  // 3 channels
      return ((theColor.theParts.red   * aColor.theColor.theParts.red)    +
              (theColor.theParts.green * aColor.theColor.theParts.green)  +
              (theColor.theParts.blue  * aColor.theColor.theParts.blue));
    } else if(numChan == 4) {                                  // 4 channels
      return ((theColor.theParts.red   * aColor.theColor.theParts.red)    +
              (theColor.theParts.green * aColor.theColor.theParts.green)  +
              (theColor.theParts.blue  * aColor.theColor.theParts.blue)   +
              (theColor.theParts.blue  * aColor.theColor.theParts.alpha));
    } else {                                                   // 5 or more channels
      int daProd = ((theColor.theParts.red   * aColor.theColor.theParts.red)    +
                    (theColor.theParts.green * aColor.theColor.theParts.green)  +
                    (theColor.theParts.blue  * aColor.theColor.theParts.blue)   +
                    (theColor.theParts.blue  * aColor.theColor.theParts.alpha));
      for(int i=4; i<numChan; i++)
        daProd += (theColor.thePartsA[i] * aColor.theColor.thePartsA[i]);
      return daProd;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::distAbs(
    colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor) {

    if(numChan == 1) {                                      // 1 channel
      return (abs((clrChanIArthT)theColor.theParts.red   - aColor.theColor.theParts.red));
    } else if(numChan == 2) {                               // 2 channels
      return (abs((clrChanIArthT)theColor.theParts.red   - aColor.theColor.theParts.red) +
              abs((clrChanIArthT)theColor.theParts.green - aColor.theColor.theParts.green));
    } else if(numChan == 3) {                               // 3 channels
      return (abs((clrChanIArthT)theColor.theParts.red   - aColor.theColor.theParts.red)   +
              abs((clrChanIArthT)theColor.theParts.green - aColor.theColor.theParts.green) +
              abs((clrChanIArthT)theColor.theParts.blue  - aColor.theColor.theParts.blue));
    } else if(numChan == 4) {                               // 4 channels
      return (abs((clrChanIArthT)theColor.theParts.red   - aColor.theColor.theParts.red)   +
              abs((clrChanIArthT)theColor.theParts.green - aColor.theColor.theParts.green) +
              abs((clrChanIArthT)theColor.theParts.blue  - aColor.theColor.theParts.blue)  +
              abs((clrChanIArthT)theColor.theParts.alpha - aColor.theColor.theParts.alpha));
    } else {                                                // 5 or more channels
      clrChanIArthT daDist = (abs((clrChanIArthT)theColor.theParts.red   - aColor.theColor.theParts.red)   +
                              abs((clrChanIArthT)theColor.theParts.green - aColor.theColor.theParts.green) +
                              abs((clrChanIArthT)theColor.theParts.blue  - aColor.theColor.theParts.blue)  +
                              abs((clrChanIArthT)theColor.theParts.alpha - aColor.theColor.theParts.alpha));
      for(int i=4; i<numChan; i++)
        daDist += abs((clrChanIArthT)theColor.thePartsA[i] - aColor.theColor.thePartsA[i]);
      return daDist;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::isEqual(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor) {
    if(fastMask) {
      return (theColor.theInt == aColor.theColor.theInt);
    } else {
      if(theColor.theParts.red != aColor.theColor.theParts.red)
        return 0;
      if(numChan > 1)
        if(theColor.theParts.green != aColor.theColor.theParts.green)
          return 0;
      if(numChan > 2)
        if(theColor.theParts.blue != aColor.theColor.theParts.blue)
          return 0;
      if(numChan > 3)
        if(theColor.theParts.alpha != aColor.theColor.theParts.alpha)
          return 0;
      if(numChan > 4)
        for(int i=4; i<numChan; i++)
          if(theColor.thePartsA[i] != aColor.theColor.thePartsA[i])
            return 0;
    }
    return 1;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::isNotEqual(colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> aColor) {
    return !(isEqual(aColor));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromUnitHSV(float h, float s, float v) {
    float f, p, q;
    float rf, gf, bf;
    double t;

    f = std::modf(h * 6.0, &t);
    int i = ((int) t) % 6;

    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - (s * (1 - f)));

    switch (i) {
    case 0:   rf = v; gf = t; bf = p; break;
    case 1:   rf = q; gf = v; bf = p; break;
    case 2:   rf = p; gf = v; bf = t; break;
    case 3:   rf = p; gf = q; bf = v; break;
    case 4:   rf = t; gf = p; bf = v; break;
    case 5:   rf = v; gf = p; bf = q; break;
    default:  rf = 0; gf = 0; bf = 0; break;
    }
    setColorRGB(clrChanT(rf*maxChanVal),
                clrChanT(gf*maxChanVal),
                clrChanT(bf*maxChanVal));
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromUnitHLS(float H, float L, float S) {
    setColorFromNaturalHLS(H*360, L, S);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromNaturalHLS(float H, float L, float S) {
    // Make sure we have appropriate L and S values
    if( (L < 0.0) || (L > 1.0) || (S < 0.0) || (S > 1.0) ) {
      SET_ERR_COLOR;
    } else {
      // Wrap h into the range [0, 360)
      double hFrac, hTmp;
      hFrac = std::modf(H, &hTmp);
      int hInt = ((int)hTmp) % 360;
      H = hFrac + hInt;
      // Compute the magic numbers..
      const double epsilon = 0.000001;
      double m1, m2;
      if(L<=0.5)
        m2 = L*(1+S);
      else
        m2 = L+S-L*S;
      m1 = 2.0*L-m2;
      // Finish up the computation
      if(S<epsilon) {
        setAllF(L);
      } else {
        setColorRGB(clrChanT(maxChanVal * hslHelperVal(m1, m2, H+120)),
                    clrChanT(maxChanVal * hslHelperVal(m1, m2, H)),
                    clrChanT(maxChanVal * hslHelperVal(m1, m2, H-120)));
      }
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  double
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::hslHelperVal(double n1, double n2, double hue) {
    if(hue>360)
      hue -= 360;
    if(hue<0)
      hue += 360;
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
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::icpWebSafe216(int anInt) {
    if( (anInt < 0) || (anInt > 217) ) {
      SET_ERR_COLOR;
    } else {
      setColorFromString((char*)(webSafeColorData[anInt][0]));
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::icpSetColor(int anInt, const char **icpArray) {
    int numColorsInArray = (int)strtol(icpArray[0], NULL, 16) - 1;
    anInt++; // Increment anInt
    if( (anInt < 1) || (anInt > numColorsInArray) ) {
      SET_ERR_COLOR;
    } else {
      setColorFromString((char*)(icpArray[anInt]));
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromWavelengthCM(float wavelength) {
    return setColorFromWavelengthCM(wavelength, 3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromWavelengthCM(float wavelength, int INTRP) {
    float rf, gf, bf;

    // Data about the color matching function table used. This should be abstracted away so that other color matching functions may be used.  Going to the
    // trouble of abstracting the color match function concept may not be worth the effort...
    const double minWL = 390;     // Min wavelength in table
    const double maxWL = 830;     // Max wavelength in table
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
    float fIdx  = (wavelength-minWL)/(maxWL-minWL)*(numPT-1);
    int   iIdx1 = int(fIdx);
    int   iIdx2 = iIdx1+1;

    // If we fell off the edge, then we set our indexes to the appropriate edge
    if(iIdx2>(numPT-1)) { iIdx1 = numPT-2; iIdx2 = numPT-1; fIdx = iIdx1; }
    if(iIdx1<0)         { iIdx1 = 0;       iIdx2 = 1;       fIdx = iIdx1; }

    // Interpolate using our tabulated color matching function
    switch(INTRP) {
    case 0 : // Closest with wavelength lower than given value
      rf=colMatchPoints[iIdx1][1];
      gf=colMatchPoints[iIdx1][2];
      bf=colMatchPoints[iIdx1][3];
      break;
    case 1 : // Closest with wavelength greater than given value
      rf=colMatchPoints[iIdx2][1];
      gf=colMatchPoints[iIdx2][2];
      bf=colMatchPoints[iIdx2][3];
      break;
    case 2 : // Closest with wavelength to given value
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
    case 3 : // Linear interpolation between data points
      rf = (fIdx-iIdx1) * (colMatchPoints[iIdx2][1] - colMatchPoints[iIdx1][1]) + colMatchPoints[iIdx1][1];
      gf = (fIdx-iIdx1) * (colMatchPoints[iIdx2][2] - colMatchPoints[iIdx1][2]) + colMatchPoints[iIdx1][2];
      bf = (fIdx-iIdx1) * (colMatchPoints[iIdx2][3] - colMatchPoints[iIdx1][3]) + colMatchPoints[iIdx1][3];
      break;
    case 4 : // Use exponential hump functions -- MJR developed algorithm 2007
      rf = 3.07/std::exp(0.0005*(wavelength-600)*(wavelength-600)) + 0.09/exp(0.005*(wavelength-425)*(wavelength-425));
      gf = 1.05/std::exp(0.0004*(wavelength-540)*(wavelength-540));
      bf = 1.00/std::exp(0.0010*(wavelength-450)*(wavelength-450));
      break;
    default:
      rf = gf = bf = 0.0;
      break;
    }

    // Make them positive and scale to a [0,1] range
    rf=(rf>0?rf:0)/rScl;
    gf=(gf>0?gf:0)/gScl;
    bf=(bf>0?bf:0)/bScl;

    // We are done.  Set the color and exit.
    setColorFromF(rf, gf, bf);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromNaturalHSV(float h, float s, float v) {
    setColorFromUnitHSV(h/360.0, s/100.0, v/100.0);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>&
  colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::setColorFromWavelengthLA(float wavelength) {
    float rf, gf, bf;

    const double minWL = 380;     // Min wavelength in table
    const double maxWL = 780;     // Max wavelength in table

    // Clip the wavelength to be in range
    if(wavelength < minWL)
      wavelength = minWL;
    if(wavelength > maxWL)
      wavelength = maxWL;

    // Compute color match functions.
    rf = gf = bf = 0;
    if       ( (wavelength >= 380) && (wavelength < 440)) {
      rf = (440-wavelength)/(440-380);
      gf = 0;
      bf = 1;
    } else if( (wavelength >= 440) && (wavelength < 490)) {
      rf = 0;
      gf = (wavelength-440)/(490-440);
      bf = 1;
    } else if( (wavelength >= 490) && (wavelength < 510)) {
      rf = 0;
      gf = 1;
      bf = (510-wavelength)/(510-490);
    } else if( (wavelength >= 510) && (wavelength < 580)) {
      rf = (wavelength-510)/(580-510);
      gf = 1;
      bf = 0;
    } else if( (wavelength >= 580) && (wavelength < 645)) {
      rf = 1;
      gf = (645-wavelength)/(645-580);
      bf = 0;
    } else if( (wavelength >= 645) && (wavelength <= 780)) {
      rf = 1;
      gf = 0;
      bf = 0;
    }

    /* Lower the intensity near edges of vision. */
    float edgeIntensityAdj;
    if(wavelength > 700) {
      edgeIntensityAdj=0.3+0.7* (780-wavelength)/(780-700);
    } else if(wavelength < 420) {
      edgeIntensityAdj=0.3+0.7*(wavelength - 380)/(420-380);
    } else {
      edgeIntensityAdj=1;
    }

    setColorFromF(edgeIntensityAdj*rf, edgeIntensityAdj*gf, edgeIntensityAdj*bf);
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanIArthT colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::clipTop(clrChanIArthT anArithComp) {
    if(anArithComp > maxChanVal)
      return maxChanVal;
    else
      return anArithComp;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanIArthT colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::clipBot(clrChanIArthT anArithComp) {
    if(anArithComp < minChanVal)
      return minChanVal;
    else
      return anArithComp;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanIArthT colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::clipAll(clrChanIArthT anArithComp) {
    if(anArithComp > maxChanVal)
      return maxChanVal;
    if(anArithComp < minChanVal)
      return minChanVal;
    return anArithComp;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::rgb2hsv(clrChanFArthT *H, clrChanFArthT *S, clrChanFArthT *V) {
    if(numChan < 3) {
      return 1;
    } else {
      clrChanT rgbMaxI = getMaxRGB();
      clrChanT rgbMinI = getMinRGB();

      float rgbMaxF = 1.0 * rgbMaxI / maxChanVal;
      float rgbMinF = 1.0 * rgbMinI / maxChanVal;

      float rangeF = rgbMaxF - rgbMinF;

      // Compute V
      *V = rgbMaxF;

      // Compute S
      if(rgbMaxI != 0)
        *S = rangeF / rgbMaxF;
      else
        *S = 0.0;

      // Compute H -- This is terrible from an optimization standpoint; however, it saves some typing. :)
      *H = rgb2h();
    }
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  int colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::rgb2hls(clrChanFArthT *H, clrChanFArthT *L, clrChanFArthT *S) {
    if(numChan < 3) {
      return 1;
    } else {
      clrChanT rgbMaxI = getMaxRGB();
      clrChanT rgbMinI = getMinRGB();

      float rgbMaxF = 1.0 * rgbMaxI / maxChanVal;
      float rgbMinF = 1.0 * rgbMinI / maxChanVal;

      float rangeF = rgbMaxF - rgbMinF;
      float sumF   = rgbMaxF + rgbMinF;

      // Compute L
      *L = sumF / 2.0;

      // Compute S & L
      if(rgbMaxI == rgbMinI) {
        *S = 0.0;
        *H = 0.0;
        return 2;
      } else {
        // Compute S
        if(*L <= 0.5)
          *S = rangeF / sumF;
        else
          *S = rangeF / ( 2.0 - sumF);
        // Compute H -- This is terrible from an optimization standpoint; however, it saves some typing. :)
        *H = rgb2h();
      }
    }
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  clrChanFArthT colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan>::rgb2h() {
    if(numChan < 3) {
      return -1.0;
    } else {
      clrChanFArthT rf = getRedF();
      clrChanFArthT gf = getGreenF();
      clrChanFArthT bf = getBlueF();

      clrChanT rgbMaxI = getMaxRGB();
      clrChanT rgbMinI = getMinRGB();

      float rgbMaxF = 1.0 * rgbMaxI / maxChanVal;
      float rgbMinF = 1.0 * rgbMinI / maxChanVal;

      float rangeF = rgbMaxF - rgbMinF;

      // Compute H -- if rgbMaxI==0 ==> rgbMaxI==rgbMinI, but we write it for clarity.  Same as S==0.0 without the possibility for round off error.
      if( (rangeF == 0) || (rgbMaxI == 0) ) {
        return 0.0;
      } else {
        float H;
        // We use the rgbMaxI to avoid round off error in comparing floating point values.
        if(theColor.theParts.red == rgbMaxI)
          H = 0.0 + (gf - bf) / rangeF;
        else if(theColor.theParts.green == rgbMaxI)
          H = 2.0 + (bf - rf) / rangeF;
        else if(theColor.theParts.blue == rgbMaxI)
          H = 4.0 + (rf - gf) / rangeF;
        else {
          return -2.0; // ERROR
        }

        H = H * 60.0;
        while(H<0)
          H += 360.0;
        while(H>=360.0)
          H -= 360.0;
        return H;
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class clrMaskT, class clrChanT, class clrChanIArthT, class clrChanFArthT, class clrNameT, int numChan>
  std::ostream& operator<< (std::ostream &out, colorTpl<clrMaskT, clrChanT, clrChanIArthT, clrChanFArthT, clrNameT, numChan> &color) {
    for(int i=0; i<numChan; i++)
      out << (uint64_t)color.getChan(i) << " ";
    return out;
  }
  
} // end namespace mjr

#define MJR_INCLUDE_colorTpl
#endif

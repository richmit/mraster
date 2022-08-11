// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      mainPage.cpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Doxygen content -- not part of the library.@EOL
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

/**
 @mainpage
 Introduction
 ============

 For a bit more detail about *MRaster*: http://richmit.github.io/mraster/index.html

 A quick start guide: http://richmit.github.io/mraster/QuickStart.html

 The code: [[https://github.com/richmit/mraster/]]

 Notes on the Code
 =================

 The code for this library all lives within the namespace of 'mjr' -- my initials.  This should help to avoid namespace conflicts.

 At this time everything is implemented in header files.

 As far as I know this code infringes upon no patents or other IP.

 Organization of the code and include files
 ==========================================

 The library is template based and the primary players, canvas and color classes, are all templates.  Common data types, 4 channel/24-bit color
 types and canvases that use them for example, all have typedefs.  In addition, the various headers implementing the templates are included by
 headers defining the typedefs.  In this way, common usage of the library requires no use of template syntax (or the extra typing).

 The include files:

   - color.hpp ......... The include file most users will include for color support
   - ramCanvas.hpp ..... The include file most users will include for ramCanvas support (includes color.hpp)
   - colorTpl.hpp ...... Implementation of the color/pixel object
   - ramCanvasTpl.hpp .. Implementation for ramCanvasTpl object
   - mjrmath.hpp ....... Simple math stuff
   - mainPage.cpp ...... Documentation

 About Color Type Templates
 ==========================

 Color types are intended to store all color information for a single pixel.  Most common image structures can be identified by the number of
 channels (Red, Green, and Blue for example) and the depth of each channel (8-bit for example).  The most common configurations are:

           |---------+---------+------+-------+------------------+-------------------------------------------------|
           | Channel |    Bits | Data |  bits |                  |                                                 |
           |   Count |     Per | Data |   per | Common Name      | Notes                                           |
           |         | Channel |      | pixel |                  |                                                 |
           |---------+---------+------+-------+------------------+-------------------------------------------------|
           |       3 |       8 | RGB  |    24 | 24-bit truecolor | Very common format.                             |
           |       4 |       8 | RGBA |    32 | truecolor+alpha  | Very common format.                             |
           |       3 |      16 | RGB  |    48 | 48-bit color     | High quality digital camera sensors.            |
           |       3 |      32 | RGB  |    96 | 96-bit color     | Usually a fusion from multiple CCDs             |
           |       1 |       8 | Grey |     8 | 8-bit greyscale  | Surveillance and Low Quality scientific imaging |
           |       1 |      16 | Grey |    16 | 16-bit greyscale | Typical scientific CCD equipment                |
           |       1 |      32 | Grey |    32 | 32-bit greyscale | High end scientific CCD equipment               |
           |---------+---------+------+-------+------------------+-------------------------------------------------|

 Several aspects of the colorTpl template are not included in the Doxygen documentation because Doxygen has trouble
 with complex meta-programming constructs.  In particular:
  - Types
    - maskType - Unsigned integer mask to cover the channel array without wasting too much space.
    - channelArithDType - Arithmetic type for differences of clrChanT values.
    - channelArithSPType - Arithmetic type for sums and products of clrChanT values.
    - channelArithSDPType - Arithmetic type for sums, differences, and products of clrChanT values.
    - channelArithFltType - Floating point type suitable for arithmetic of clrChanT values.
    - channelArithLogType - Arithmetic type suitable for for logical operations of clrChanT values.
    - csIntType - Integer type used to select colors from a color scheme
    - csFltType - Floating point type used to select colors from a color scheme
    - csNatType - A type used to  select colors from a color scheme (it will be integral when clrChanT is integral, and floating point otherwise)
  - Color Schemes
    - Predefined color scheme classes are documented here: http://richmit.github.io/mraster/ColorSchemes.html
    - Templates used to make custom color schemes:
      - csPLY_tpl - Compute a color from a polynomial space curve in the RGB color space. This is a continuous color scheme!
      - csCubeHelix_tpl - Compute a color from Dave Green's cubehelix scheme.  See: Green, D. A., 2011, Bulletin of the Astronomical Society of India, Vol.39, p.289.
      - csCC_tpl - RGB color cube gradiant color schemes 
      - csHSLh_tpl - HSL color schemes.
      - csFP_tpl - fixed size pallets
      - csCB_tpl - Color Brewer 2 variable sized pallets

 Drawing
 =======

 Primitive drawing functions generally come in several forms:

    - foo(<integer_coords>, <color>)
    - foo(<integer_coords>)
    - foo()
    - foo(<float_coords>, <color>)
    - foo(<float_coords>)
    - foo(<integer_points>, <color>)
    - foo(<integer_points>)
    - foo(<float_points>, <color>)
    - foo(<float_points>)
    - foo(<array_of_integer_points>, <color>)
    - foo(<array_of_integer_points>)
    - foo(<array_of_float_points>, <color>)
    - foo(<array_of_float_points>)

 This library supports both the "moveTo/lineTo" paradigm (i.e. move to A, draw line to B), and the "absolute" paradigm (i.e. draw a line from A to B).
 Because of this, some primitive drawing functions also have forms with fewer coordinates specified.  For example, we have a point drawing function that takes
 no arguments.  Just with fewer coordinates.  Some primitives, like circles, require extra parameters to describe the primitive.  Such parameters right before
 the color arguments or last in the argument list if no color is specified.

*/



          

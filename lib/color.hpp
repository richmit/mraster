// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      color.hpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     User include file for color types@EOL
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

#ifndef MJR_INCLUDE_color

#include <cstdint>                                                       /* std:: C stdint.h        C++11    */
#include <limits>                                                        /* C++ Numeric limits      C++11    */

#include "colorTpl.hpp"

// Put everything in the mjr namespace
namespace mjr {

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Channel Types */
  //@{
  typedef uint8_t      colChanI8;   //!< Type suitable for   8-bit unsigned color channels
  typedef uint16_t     colChanI16;  //!< Type suitable for  16-bit unsigned color channels
  typedef uint32_t     colChanI32;  //!< Type suitable for  32-bit unsigned color channels
  typedef uint64_t     colChanI64;  //!< Type suitable for  64-bit unsigned color channels
#ifdef MJR_HAVE_128_BIT_TYPES
 typedef mjr_uint128_t colChanI128; //!< Type suitable for 128-bit unsigned color channels
#endif

  typedef float       colChanF32; //!< Type suitable for 32-bit floating point color channels
  typedef double      colChanF64; //!< Type suitable for 64-bit floating point color channels
  //@}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Complete Color Types@EOL
      The following types define the most commonly used color/pixel combinations. */
  //@{
  typedef colorTpl<colChanI8,   1>  color1c8b;   //!< colorTpl:  1 Channel @   8-bit unsigned int      8  -- 8-bit Greyscale            
  typedef colorTpl<colChanI8,   2>  color2c8b;   //!< colorTpl:  2 Channel @   8-bit unsigned int     16  
  typedef colorTpl<colChanI8,   3>  color3c8b;   //!< colorTpl:  3 Channel @   8-bit unsigned int     24  -- 24-bit RGB (truecolor)
  typedef colorTpl<colChanI8,   4>  color4c8b;   //!< colorTpl:  4 Channel @   8-bit unsigned int     32  -- 24-bit RGBA (truecolor)
  typedef colorTpl<colChanI8,   5>  color5c8b;   //!< colorTpl:  5 Channel @   8-bit unsigned int     40
  typedef colorTpl<colChanI8,   6>  color6c8b;   //!< colorTpl:  6 Channel @   8-bit unsigned int     48
  typedef colorTpl<colChanI8,   7>  color7c8b;   //!< colorTpl:  7 Channel @   8-bit unsigned int     56
  typedef colorTpl<colChanI8,   8>  color8c8b;   //!< colorTpl:  8 Channel @   8-bit unsigned int     64
  typedef colorTpl<colChanI8,  16>  color16c8b;  //!< colorTpl: 16 Channel @   8-bit unsigned int    128
  typedef colorTpl<colChanI8,  32>  color32c8b;  //!< colorTpl: 32 Channel @   8-bit unsigned int    256
  typedef colorTpl<colChanI8,  64>  color64c8b;  //!< colorTpl: 64 Channel @   8-bit unsigned int    512

  typedef colorTpl<colChanI16,  1>  color1c16b;  //!< colorTpl:  1 Channel @  16-bit unsigned int     16  -- 16-bit Greyscale           
  typedef colorTpl<colChanI16,  2>  color2c16b;  //!< colorTpl:  2 Channel @  16-bit unsigned int     32  
  typedef colorTpl<colChanI16,  3>  color3c16b;  //!< colorTpl:  3 Channel @  16-bit unsigned int     48  -- 48-bit RGB
  typedef colorTpl<colChanI16,  4>  color4c16b;  //!< colorTpl:  4 Channel @  16-bit unsigned int     64  -- 48-bit RGBA
  typedef colorTpl<colChanI16,  8>  color8c16b;  //!< colorTpl:  8 Channel @  16-bit unsigned int    128
  typedef colorTpl<colChanI16, 16>  color16c16b; //!< colorTpl: 16 Channel @  16-bit unsigned int    256
  typedef colorTpl<colChanI16, 32>  color32c16b; //!< colorTpl: 32 Channel @  16-bit unsigned int    512
                                                                                          
  typedef colorTpl<colChanI32,  1>  color1c32b;  //!< colorTpl:  1 Channel @  32-bit unsigned int     32  -- 32-bit Greyscale           
  typedef colorTpl<colChanI32,  2>  color2c32b;  //!< colorTpl:  2 Channel @  32-bit unsigned int     64  
  typedef colorTpl<colChanI32,  3>  color3c32b;  //!< colorTpl:  3 Channel @  32-bit unsigned int     96  -- 96-bit RGB
  typedef colorTpl<colChanI32,  4>  color4c32b;  //!< colorTpl:  4 Channel @  32-bit unsigned int    128  -- 96-bit RGBA
  typedef colorTpl<colChanI32,  8>  color8c32b;  //!< colorTpl:  8 Channel @  32-bit unsigned int    256
  typedef colorTpl<colChanI32, 16>  color16c32b; //!< colorTpl: 16 Channel @  32-bit unsigned int    512
                                                                                          
  typedef colorTpl<colChanI64,  1>  color1c64b;  //!< colorTpl:  1 Channel @  64-bit unsigned int     64  -- 64-bit Greyscale           
  typedef colorTpl<colChanI64,  2>  color2c64b;  //!< colorTpl:  2 Channel @  64-bit unsigned int    128  
  typedef colorTpl<colChanI64,  3>  color3c64b;  //!< colorTpl:  3 Channel @  64-bit unsigned int    192  -- 192-bit RGB
  typedef colorTpl<colChanI64,  4>  color4c64b;  //!< colorTpl:  4 Channel @  64-bit unsigned int    256  -- 192-bit RGBA
  typedef colorTpl<colChanI64,  8>  color8c64b;  //!< colorTpl:  8 Channel @  64-bit unsigned int    512
                                                                                          
#ifdef MJR_HAVE_128_BIT_TYPES                    
  typedef colorTpl<colChanI128, 1> color1c128b;  //!< colorTpl:  1 Channel @ 128-bit unsigned int    128  -- 128-bit Greyscale          
  typedef colorTpl<colChanI128, 2> color2c128b;  //!< colorTpl:  2 Channel @ 128-bit unsigned int    256  
  typedef colorTpl<colChanI128, 3> color3c128b;  //!< colorTpl:  3 Channel @ 128-bit unsigned int    384  -- 384-bit RGB
  typedef colorTpl<colChanI128, 4> color4c128b;  //!< colorTpl:  4 Channel @ 128-bit unsigned int    512  -- 192-bit RGBA
#endif                                           
                                                 
  typedef colorTpl<colChanF32,  1>  color1c32F;  //!< colorTpl:  1 Channel @  32-bit floating point   32  -- 32-bit Floating Greyscale  
  typedef colorTpl<colChanF32,  2>  color2c32F;  //!< colorTpl:  2 Channel @  32-bit floating point   64  
  typedef colorTpl<colChanF32,  3>  color3c32F;  //!< colorTpl:  3 Channel @  32-bit floating point   96  -- 96-bit Floating RGB
  typedef colorTpl<colChanF32,  4>  color4c32F;  //!< colorTpl:  4 Channel @  32-bit floating point  128  -- 96-bit Floating RGBA
  typedef colorTpl<colChanF32,  8>  color8c32F;  //!< colorTpl:  8 Channel @  32-bit floating point  256
  typedef colorTpl<colChanF32, 16>  color16c32F; //!< colorTpl: 16 Channel @  32-bit floating point  512
                                                 
  typedef colorTpl<colChanF64,  1>  color1c64F;  //!< colorTpl:  1 Channel @  64-bit floating point   64  -- 64-bit Floating Greyscale
  typedef colorTpl<colChanF64,  2>  color2c64F;  //!< colorTpl:  2 Channel @  64-bit floating point  128  
  typedef colorTpl<colChanF64,  3>  color3c64F;  //!< colorTpl:  3 Channel @  64-bit floating point  192  -- 192-bit Floating RGB
  typedef colorTpl<colChanF64,  4>  color4c64F;  //!< colorTpl:  4 Channel @  64-bit floating point  256  -- 256-bit Floating RGBA
  typedef colorTpl<colChanF64,  8>  color8c64F;  //!< colorTpl:  8 Channel @  64-bit floating point  512
  //@}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Complete Color Types with Traditional Names@EOL
      Many people prefere to use tranditional, RGB/greyscale names for color types. */
  //@{
  typedef color4c8b   colorRGBA8b;   //!< colorTpl: RGBA  (8-bit int/channel) (truecolor)
  typedef color4c16b  colorRGBA16b;  //!< colorTpl: RGBA (16-bit int/channel)
  typedef color4c32b  colorRGBA32b;  //!< colorTpl: RGBA (32-bit int/channel)
  typedef color4c64b  colorRGBA64b;  //!< colorTpl: RGBA (64-bit int/channel)

  typedef color4c32F  colorRGBA32F;  //!< colorTpl: RGBA (32-bit float/channel)
  typedef color4c64F  colorRGBA64F;  //!< colorTpl: RGBA (64-bit float/channel)
                                     
  typedef color3c8b   colorRGB8b;    //!< colorTpl: RGB   (8-bit int/channel) (truecolor)
  typedef color3c16b  colorRGB16b;   //!< colorTpl: RGB  (16-bit int/channel)
  typedef color3c32b  colorRGB32b;   //!< colorTpl: RGB  (32-bit int/channel)
  typedef color3c64b  colorRGB64b;   //!< colorTpl: RGB  (64-bit int/channel)

  typedef color3c32F  colorRGB32F;   //!< colorTpl: RGB  (32-bit float/channel)
  typedef color3c64F  colorRGB64F;   //!< colorTpl: RGB  (64-bit float/channel)
                                     
  typedef color1c8b   colorGrey8b;   //!< colorTpl:   8-bit int Greyscale
  typedef color1c16b  colorGrey16b;  //!< colorTpl:  16-bit int Greyscale
  typedef color1c32b  colorGrey32b;  //!< colorTpl:  32-bit int Greyscale
  typedef color1c64b  colorGrey64b;  //!< colorTpl:  64-bit int Greyscale
#ifdef MJR_HAVE_128_BIT_TYPES
  typedef color1c128b colorGrey128b; //!< colorTpl: 128-bit int Greyscale
#endif

  typedef color1c32F  colorGrey32F;  //!< colorTpl:  32-bit float Greyscale
  typedef color1c64F  colorGrey64F;  //!< colorTpl:  64-bit float Greyscale
  //@}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Complete Color Types with 8-bit channels and commonly used orderings for R, G, B, & A@EOL
      These are commonly used by libraries like Cairo, Open GL, SDL, etc... */
  //@{
  typedef colorTpl<colChanI8,   3, 2, 1, 0>     colorBGR8b;   //!< colorTpl:  3 Channel @   8-bit unsigned int     24

  typedef colorTpl<colChanI8,   4, 1, 2, 3, 0>  colorARGB8b;   //!< colorTpl:  4 Channel @   8-bit unsigned int     32
  typedef colorTpl<colChanI8,   4, 2, 1, 0, 3>  colorBGRA8b;   //!< colorTpl:  4 Channel @   8-bit unsigned int     32
  typedef colorTpl<colChanI8,   4, 3, 2, 1, 0>  colorABGR8b;   //!< colorTpl:  4 Channel @   8-bit unsigned int     32
  //@}

} // end namespace mjr

#define MJR_INCLUDE_color
#endif

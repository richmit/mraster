// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
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
***************************************************************************************************************************************************************/

#ifndef MJR_INCLUDE_color

#include <cstdint>                                                       /* std:: C stdint.h        C++11    */
#include <limits>                                                        /* C++ Numeric limits      C++11    */

#include "ramConfig.hpp"
#include "colorTpl.hpp"

// Put everything in the mjr namespace
namespace mjr {

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Channel Types */
  //@{
  typedef uint8_t      colChan8;
  typedef uint16_t     colChan16;
  typedef uint32_t     colChan32;
  typedef uint64_t     colChan64;
  //@}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Types for arithmetic for various channel depths */
  //@{
  typedef int32_t      colChanArth8;
  typedef int64_t      colChanArth16;
  typedef int64_t      colChanArth32;  // Not big enough for *
  typedef int64_t      colChanArth64;  // Not big enough for * + -
  //@}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Types for the masks */
  //@{
  typedef uint64_t     colChanCont8x8; // Not used by any other types defined here
  typedef uint32_t     colChanCont4x8;
  typedef uint64_t     colChanCont4x16;
  typedef uint8_t      colChanCont1x8;
  typedef uint16_t     colChanCont1x16;
  typedef uint32_t     colChanCont1x32;
  typedef uint64_t     colChanCont1x64;
  //@}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Types for channel names */
  //@{
  /* Types for the names (RGB and RGBA). */
  typedef struct { colChan8   red;   colChan8   green; colChan8   blue;  colChan8   alpha; } colChanNamesRGBA4x8;
  typedef struct { colChan16  red;   colChan16  green; colChan16  blue;  colChan16  alpha; } colChanNamesRGBA4x16;

  /* Types for the names (monochrome). */
  typedef union  { colChan8   red;   colChan8   green; colChan8   blue;  colChan8   alpha; } colChanNames1x8;
  typedef union  { colChan16  red;   colChan16  green; colChan16  blue;  colChan16  alpha; } colChanNames1x16;
  typedef union  { colChan32  red;   colChan32  green; colChan32  blue;  colChan32  alpha; } colChanNames1x32;
  typedef union  { colChan64  red;   colChan64  green; colChan64  blue;  colChan64  alpha; } colChanNames1x64;
  //@}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /** @name Complete Color Types@EOL
      The following types define the most commonly used color/pixel combinations, and are what most users of will actually use in practice. */
  //@{
  typedef colorTpl<colChanCont8x8,   colChan8,   colChanArth8,  colChanNamesRGBA4x8,  8> color8c8b;    //!< colorTpl: 2 channels at  8-bits/channel

  typedef colorTpl<colChanCont4x8,   colChan8,   colChanArth8,  colChanNamesRGBA4x8,  4> colorRGBA8b;  //!< colorTpl: 24-bit truecolor with alpha (RGBA)
  typedef colorTpl<colChanCont4x16,  colChan16,  colChanArth16, colChanNamesRGBA4x16, 4> colorRGBA16b; //!< colorTpl: 48-bit truecolor with alpha (RGBA)

  typedef colorRGBA8b                                                                    color4c8b;    //!< colorTpl: Generic 4 channel  (8-bit/channel)
  typedef colorRGBA16b                                                                   color4c16b;   //!< colorTpl: Generic 4 channel (16-bit/channel)

  typedef colorTpl<colChanCont4x8,   colChan8,   colChanArth8,  colChanNamesRGBA4x8,  3> colorRGB8b;   //!< colorTpl: 24-bit truecolor without alpha (RGB)
  typedef colorTpl<colChanCont4x16,  colChan16,  colChanArth16, colChanNamesRGBA4x16, 3> colorRGB16b;  //!< colorTpl: 48-bit truecolor with alpha (RGB)

  typedef colorRGB8b                                                                     color3c8b;    //!< colorTpl: Generic 3 channel  (8-bit/channel)
  typedef colorRGB16b                                                                    color3c16b;   //!< colorTpl: Generic 3 channel (16-bit/channel)

  typedef colorTpl<colChanCont4x8,   colChan8,   colChanArth8,  colChanNamesRGBA4x8,  2> color2c8b;    //!< colorTpl: 2 channels at  8-bits/channel
  typedef colorTpl<colChanCont4x16,  colChan16,  colChanArth16, colChanNamesRGBA4x16, 2> color2c16b;   //!< colorTpl: 2 channels at 16-bits/channel

  typedef colorTpl<colChanCont1x8,   colChan8,   colChanArth8,  colChanNames1x8,      1> color1c8b;    //!< colorTpl:  8-bit uint grey-scale
  typedef colorTpl<colChanCont1x16,  colChan16,  colChanArth16, colChanNames1x16,     1> color1c16b;   //!< colorTpl: 16-bit uint grey-scale
  typedef colorTpl<colChanCont1x32,  colChan32,  colChanArth32, colChanNames1x32,     1> color1c32b;   //!< colorTpl: 32-bit uint grey-scale
  typedef colorTpl<colChanCont1x64,  colChan64,  colChanArth64, colChanNames1x64,     1> color1c64b;   //!< colorTpl: 64-bit uint grey-scale
  //@}

} // end namespace mjr

#define MJR_INCLUDE_color
#endif

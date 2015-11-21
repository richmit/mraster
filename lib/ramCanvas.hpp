// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      ramCanvas.hpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     User include file for ramCanvas types.@EOL@EOL
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

#ifndef MJR_INCLUDE_ramCanvas

#include "ramConfig.hpp"
#include "color.hpp"
#include "ramCanvasTpl.hpp"

// Put everything in the mjr namespace
namespace mjr {

  /** @name Simple Canvas Coordinate Types */
  //@{
  typedef REAL_CORD rcsimpleFltCrdT; //!< Real coordinate type
  typedef INT_CORD  simpleIntCrdT; //!< Integer coordinate type
  //@}

  /** @name Simple Color Canvas Types (3 and 4 channels at 8 bits per channel) */
  //@{
  typedef ramCanvasTpl<color4c8b,    INT_CORD, REAL_CORD> ramCanvas4c8b;       //!< Canvas type: generic 32-bit with 4 channels at 8-bit per channel. 
  typedef ramCanvasTpl<color3c8b,    INT_CORD, REAL_CORD> ramCanvas3c8b;       //!< Canvas type: generic 24-bit with 3 channels at 8-bit per channel. 
  typedef ramCanvasTpl<colorRGBA8b,  INT_CORD, REAL_CORD> ramCanvasRGBA8b;     //!< Canvas type: 24-bit true color with alpha last (RGBA)  -- 4 channels at 8-bit per channel.
  typedef ramCanvasTpl<colorRGB8b,   INT_CORD, REAL_CORD> ramCanvasRGB8b;      //!< Canvas type: 24-bit true color without alpha (RGB)     -- 3 channels at 8-bit per channel.
  //@}

  /** @name Simple Color Canvas Types (3 and 4 channels at 16 bits per channel) */
  //@{
  typedef ramCanvasTpl<color4c16b,   INT_CORD, REAL_CORD> ramCanvas4c16b;      //!< Canvas type: Generic 64-bit with 4 channels at 16-bit per channel.
  typedef ramCanvasTpl<color3c16b,   INT_CORD, REAL_CORD> ramCanvas3c16b;      //!< Canvas type: Generic 48-bit with 4 channels at 16-bit per channel. 
  typedef ramCanvasTpl<colorRGBA16b, INT_CORD, REAL_CORD> ramCanvasRGBA16b;    //!< Canvas type: 48-bit true color with alpha (RGBA)   -- 4 channels at 16-bit per channel.
  typedef ramCanvasTpl<colorRGBA16b, INT_CORD, REAL_CORD> ramCanvasRGB16b;     //!< Canvas type: 48-bit true color without alpha (RGB) -- 3 channels at 16-bit per channel.
  //@}

  /** @name Simple Monochrome Canvas Types (1 channel at various depths) */
  //@{
  typedef ramCanvasTpl<color1c8b,    INT_CORD, REAL_CORD> ramCanvas1c8b;       //!< Canvas type:  8-bit grey-scale -- 1 channel,  8-bit.
  typedef ramCanvasTpl<color1c16b,   INT_CORD, REAL_CORD> ramCanvas1c16b;      //!< Canvas type: 16-bit grey-scale -- 1 channel, 16-bit.
  typedef ramCanvasTpl<color1c32b,   INT_CORD, REAL_CORD> ramCanvas1c32b;      //!< Canvas type: 32-bit grey-scale -- 1 channel, 32-bit.
  typedef ramCanvasTpl<color1c64b,   INT_CORD, REAL_CORD> ramCanvas1c64b;      //!< Canvas type: 64-bit grey-scale -- 1 channel, 64-bit.
  //@}

  //template class ramCanvasTpl<color3c8b,    INT_CORD, REAL_CORD>;
  //template void  ramCanvas3c8b::autoMaxHistStrech();
  
} // end namespace mjr

#define MJR_INCLUDE_ramCanvas
#endif

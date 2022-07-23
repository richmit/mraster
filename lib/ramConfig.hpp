// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      ramConfig.hpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Header defining several compile options.@EOL
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

#include <cstdint>                                                       /* std:: C stdint.h        C++11    */

#ifndef MJR_INCLUDE_ramConfig

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Set to 1 to look for 128-bit integer types, and 0 to not look for them.
    Right now this only works on GCC & Clang! */
#ifndef MJR_LOOK_FOR_128_BIT_TYPES
#define MJR_LOOK_FOR_128_BIT_TYPES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Float type used for fltCrdT in predefiend ramCanvasTpl types defined in ramCanvas.hpp.*/
#ifndef REAL_CORD
#define REAL_CORD double
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Int type used for intCrdT in predefined ramCanvasTpl types defined in ramCanvas.hpp */
#ifndef INT_CORD
#define INT_CORD int
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** Support drawing modes.
    If this non-zero, then the library will support drawMode in ramCanvas objects.
    @warning Imposes a small performance impact. */
#ifndef SUPPORT_DRAWING_MODE
#define SUPPORT_DRAWING_MODE 0
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
typedef uint64_t     mjr_uintBiggest_t;   //!< The largest unsigned integer supported on the platform
typedef int64_t      mjr_intBiggest_t;    //!< The largest signed integer supported on the platform  
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Put everything in the mjr namespace
namespace mjr {

  /**@brief Class providing run time access to compile time parameters.@EOL */
  class ramConfig {
    public:

    /** @name Run time detection of compile time options */
    //@{
      static int support_drawing_mode()          { return SUPPORT_DRAWING_MODE; }
    //@}
  };

} // end namespace mjr

#define MJR_INCLUDE_ramConfig
#endif

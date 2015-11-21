// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
 @file      ramConfig.hpp
 @author    Mitch Richling <http://www.mitchr.me>
 @brief     Header defining several compile options.@EOL 
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

#ifndef MJR_INCLUDE_ramConfig

/** @brief Define color scheme index out of bound behaviour.@EOL
    Set this to the name of the function used to precondition indexes passed into color scheme functions.  Options:
          - (i)                 -- Do nothing
          - intWrap((i), (m))   -- Wrap
          - intClamp((i), (m))  -- Clamp
*/
#ifndef IDXCOND
#define IDXCOND(i, m) (i)
#endif

/** @brief Set the error color@EOL
    Set this define to the function call to set the error color.  Generally, this will be 'setToBlack()' */
#ifndef SET_ERR_COLOR
#define SET_ERR_COLOR setToBlack()
#endif

/** @brief Keep track of dirty parts of the canvis.@EOL
    A rectangle is maintained that contains the dirty region of the canvas.  
    @todo Add other dirty mark methods like a dirty pixels list, list of dirty rectangels, dirty bit mask.
    @warning This option can impose as much as a 2x penalty on drawing operations.
        - 0 none  No dirty lists
        - 1 one   Single dirty/not dirty
        - 2 box   The coordinates of a single dirty box are stored */
#ifndef DIRTY_LIST
#define DIRTY_LIST 0
#endif

/** @brief The type to use for the dirty change index.@EOL */
#ifndef DIRTY_INDEX_TYPE
#define DIRTY_INDEX_TYPE unsigned int
#endif

/** @brief Float type used for fltCrdT in predefiend ramCanvasTpl types defined in ramCanvas.hpp.@EOL*/
#ifndef REAL_CORD
#define REAL_CORD double
#endif

/** @brief Float type used for fltCompT in predefiend colorTpl types defined in color.hpp.@EOL */
#ifndef REAL_CHAN
#define REAL_CHAN float
#endif

/** @brief Int type used for intCrdT in predefiend ramCanvasTpl types defined in ramCanvas.hpp.@EOL */
#ifndef INT_CORD
#define INT_CORD int
#endif

/** @brief Always keep the Alpha color safe@EOL 
    If this define is non-zero, then the library will preserve the alpha color for normal draw operations.  
    @warning Imposes a small performance impact. */
#ifndef SUPPORT_ALWAYS_PRESERVE_ALPHA
#define SUPPORT_ALWAYS_PRESERVE_ALPHA 0
#endif

// Put everything in the mjr namespace
namespace mjr {

  /**@brief Class providing run time access to compile time parameters.@EOL */
  class ramConfig {
    public:
      
    /** @name Run time detection of compile time options */
    //@{
    static int              support_always_preserve_alpha() { return SUPPORT_ALWAYS_PRESERVE_ALPHA; }
    static int              dirty_list()                    { return DIRTY_LIST; }
    //@}
  };

} // end namespace mjr

#define MJR_INCLUDE_ramConfig
#endif

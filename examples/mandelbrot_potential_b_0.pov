// -*- Mode:pov; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      mandelbrot_potential.pov
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Render height field in mandelbrot_potential_2.tga.@EOL
 @copyright
  @parblock
  Copyright (c) 2001-2015, Mitchell Jay Richling <https://www.mitchr.me> All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of conditions, and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions, and the following disclaimer in the documentation
     and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without
     specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  @endparblock
 @filedetails
***************************************************************************************************************************************************************/

#include "colors.inc"

global_settings { assumed_gamma 1 }

camera {
  location <4.5, 3.7, -4.5>
  right 1.2*x
  look_at <0,1.2,0>
}

light_source { <0,100,-100> White }
light_source { <100,0,-100> White*0.5 }
light_source { <100,100,-100> White*0.5 }

height_field {
  tga "mandelbrot_potential_b_0.tga"
  smooth
  pigment {
    gradient y
    color_map {
      [0.00000 color Black  ]
      [0.99000 color Blue   ]
      [0.99900 color Green  ]
      [0.99990 color Yellow ]
      [0.99995 color Red    ]
      [0.99997 color White  ]
      [1.00000 color White  ]
    }
  }
  finish  {
    ambient .10
    diffuse 0.5
    reflection 0.07
    specular 0.65
    roughness 0.015
    phong 1
    phong_size 600
  }
  translate <-0.5, -0.9, -0.5>
  scale <10, 16.0, 10>
}

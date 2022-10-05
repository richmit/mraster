// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
 @file      displayImageSDL2.cpp
 @author    Mitch Richling http://www.mitchr.me/
 @date      2022-08-18
 @brief     Demonstrate how to display an image with SDL.@EOL
 @std       C++20
 @copyright 
  @parblock
  Copyright (c) 2022, Mitchell Jay Richling <http://www.mitchr.me/> All rights reserved.

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
*/
/*******************************************************************************************************************************************************.H.E.**/

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
//#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "ramCanvas.hpp"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  mjr::ramCanvas3c8b theRamCanvas;
  theRamCanvas.setIntAxOrientationY(mjr::ramCanvas3c8b::intAxisOrientation::INVERTED); // In SDL2, the 0 row of pixels is at the bottom.

  if (argc < 2) {
    std::cout << "ERROR argument required!" << std::endl;
    return 1;
  }

  int rRet;
  if((rRet=theRamCanvas.readTIFFfile(argv[1]))) {
    std::cout << "ERROR(" << rRet << ") reading file " << argv[1] << std::endl;
    return 2;
  }

  rRet = SDL_Init(SDL_INIT_VIDEO);
  if (rRet < 0) {
    std::cout << "ERROR: SDL_Init failed: " << SDL_GetError() << std::endl;
    return 3;
  }
 
  SDL_DisplayMode daDisplayMode;
  rRet = SDL_GetDesktopDisplayMode(0, &daDisplayMode);
  if (rRet < 0) {
    std::cout << "ERROR: SDL_GetDesktopDisplayMode failed: " << SDL_GetError() << std::endl;
    return 4;
  }

  if ((daDisplayMode.w-100) < theRamCanvas.getNumPixX()) {
    std::cout << "ERROR: The display is not wide enough for image" << std::endl;
    return 5;
  }

  if ((daDisplayMode.h-200) < theRamCanvas.getNumPixY()) {
    std::cout << "ERROR: The display is not tall enough for image" << std::endl;
    return 6;
  }

  SDL_Event     daSDLevent;
  SDL_Window*   daSDLwindow;
  SDL_Surface*  daSDLsurface;

  daSDLwindow  = SDL_CreateWindow("ramCanvas Observer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, theRamCanvas.getNumPixX(), theRamCanvas.getNumPixY(), SDL_WINDOW_SHOWN);
  daSDLsurface = SDL_GetWindowSurface(daSDLwindow); 

  /* Note we could SDL_BlitSurface, but it takes more code to set that up than to just copy over the bytes. :)  */
  for (int y=0; y<theRamCanvas.getNumPixY(); ++y)
    for (int x=0; x<theRamCanvas.getNumPixX(); ++x)
      ((Uint32*)daSDLsurface->pixels)[(y*daSDLsurface->w) + x] = SDL_MapRGB(daSDLsurface->format, theRamCanvas.getPxColorNC(x, y).getRed_byte(), theRamCanvas.getPxColorNC(x, y).getGreen_byte(), theRamCanvas.getPxColorNC(x, y).getBlue_byte());
  SDL_UpdateWindowSurface(daSDLwindow);

  while (1) {
    if (SDL_PollEvent(&daSDLevent) && daSDLevent.type == SDL_QUIT) {
      SDL_DestroyWindow(daSDLwindow);
      SDL_Quit();
      return 0;
    }
  }

  return 0;
}

// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/**************************************************************************************************************************************************************/
/**
   @file      glut_image.cpp
   @author    Mitch Richling <https://www.mitchr.me>
   @brief     One way to get images from a ramCanvas into OpenGL@EOL
   @std       C++98
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
   @filedetails   

   We illustrate how to use the exportRasterData() member to get data suitable for use as an OpenGL image.  Note that ramCanvas.h also supports directly an
   internal representation that is the same as that used by OpenGL --- so one can actually use the raw pixel store in the ramCanvas as OpenGL image data.  This
   program illustrates how one might get OpenGL image data if the ramCanvas for some reason was not internally compatible with OpenGL.  Note this same
   technique allows easy integration with other libraries requiring similar data formats.

***************************************************************************************************************************************************************/

#include "ramCanvas.hpp"

/* Apple puts GLUT into a framework named GLUT, while the rest of the world just sticks GLUT into the GL include directory... */
#ifdef __APPLE__
#include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>            /* Open GL Util    OpenGL*/
#endif

int XSIZE = 1024;
int YSIZE = 1024;

mjr::ramCanvas3c8b theRC = mjr::ramCanvas3c8b(XSIZE, YSIZE, -1, 1, -1, 1);

void reshapeCall(int h, int w) {
  XSIZE = h;
  YSIZE = w;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, XSIZE, 0.0, XSIZE);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0,0,XSIZE,YSIZE);
  glutPostRedisplay();
} /* end func reshapeCall */

void idleCall() {
  static int offset;
  for(int x=0; x<theRC.get_numXpix(); x++)
    for(int y=0; y<theRC.get_numXpix(); y++)
      theRC.drawPoint(x, y, mjr::color3c8b(offset+y-x,offset+x+y,offset+x-y));
  offset+=1;
  glutPostRedisplay();
} /* end func idleCall */

void displayCall() {
  static void *image;
  float xMag, yMag;

  int retVal;
  if((retVal=theRC.exportRasterData(image, 0, 0, theRC.get_numXpix()-1, theRC.get_numYpix()-1, 0, 1, 2, 3))) {
    printf("ERROR: Nonzero return from exportRasterData(): %d\n", retVal);
    return;
  }

  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2i(0,0);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  xMag = 1.0 * XSIZE / theRC.get_numXpix();
  yMag = 1.0 * YSIZE / theRC.get_numYpix();

  glPixelZoom(xMag, yMag);
  glDrawPixels(theRC.get_numXpix(), theRC.get_numYpix(), GL_RGBA, GL_UNSIGNED_BYTE, (GLubyte*)image);
  glFlush();
}  /* end func displayCall */

int main(int argc, char *argv[]) {
  for(int x=0; x<theRC.get_numXpix(); x++)
    for(int y=0; y<theRC.get_numXpix(); y++)
      theRC.drawPoint(x, y, mjr::color3c8b(y-x,x+y,x-y));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(XSIZE, YSIZE);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("ramCanvasDisplayViaGLUT");
  glutReshapeFunc(reshapeCall);
  glutDisplayFunc(displayCall);
  glutIdleFunc(idleCall);
  glutMainLoop();
  return 0;
} /* end func main */

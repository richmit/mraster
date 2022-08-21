#include "ramCanvas.hpp"                                                     // The main MRaster include

int main(void) {
  mjr::ramCanvas3c8b theRamCanvas(1024, 1024);                               // Create a canvas object
  for(int y=0;y<theRamCanvas.getNumPixY();y++)                              // Run over the rows 
    for(int x=0;x<theRamCanvas.getNumPixX();x++)                            //   and columns of the image
      theRamCanvas.drawPoint(x, y, mjr::color3c8b::csCColdeRainbow::c(x+y)); // Pick a "rainbow" color for the point
  theRamCanvas.writeTIFFfile("hello.tiff");                                  // Write out our image to disk
}

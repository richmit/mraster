// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/***************************************************************************************************************************************************************
 @file      ramCanvasTpl.hpp
 @author    Mitch Richling <https://www.mitchr.me>
 @brief     Internal include file for ramCanvas types.@EOL
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
   Note that this file is not intended for inclusion into end user application code; however, this use is quite possible in some special cases.  For a less
   complex interface, one is encouraged to include the ramCanvas.h include file instead.
***************************************************************************************************************************************************************/

#ifndef MJR_INCLUDE_ramCanvasTpl

#include "config.hpp"

#ifdef TIFF_FOUND
#include <unistd.h>                                                      /* UNIX std stf            POSIX    */
#include <tiffio.h>                                                      /* libTIFF                 libTIFF  */
#endif

#include <cmath>                                                         /* std:: C math.h          C++11    */
#include <cstdint>                                                       /* std:: C stdint.h        C++11    */
#include <fstream>                                                       /* C++ fstream             C++98    */
#include <functional>                                                    /* STL funcs               C++98    */
#include <iomanip>                                                       /* C++ stream formatting   C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <sstream>                                                       /* C++ string stream       C++      */
#include <string>                                                        /* C++ strings             C++11    */
#include <type_traits>                                                   /* C++ metaprogramming     C++11    */
#include <utility>                                                       /* STL Misc Utilities      C++11    */
#include <vector>                                                        /* STL vector              C++11    */

#include "color.hpp"
#include "ramConfig.hpp"
#include "hersheyFontData.hpp"
#include "point2d.hpp"

// Put everything in the mjr namespace
namespace mjr {

  /** @brief Class providing off-screen drawing functionality.@EOL

      This class essentially manages a 2D array of pixels (represented as colorTpl objects).  Both integer and floating point coordinates are supported.

      Coordinates
      ===========

      Traditional Mathematical Coordinate System
      ------------------------------------------

      The traditional coordinate system used in mathematics is the Cartesian Coordinate system.  In this system the axes represent real numbers which increase as
      one moves to the right or up.


                 ^ y (increasing upward)
                 |
                 . (0, 1)
                 |
                 |
                 |
        (-1,0)   | (0,0)        x (increasing to the right)
      <-.--------+--------.----->
                 |        (1,0)
                 |
                 |
                 |
                 . (0, -1)
                 |
                 v

      Traditional Computer Graphics Coordinate System
      -----------------------------------------------

      Unlike the Cartesian coordinate system, the traditional coordinates used in computer graphics have only positive, integer coordinates, the origin at the upper
      left, and the x and y coordinates increasing to the right and down.  This is a very natural choice given the discrete nature of digital displays and the
      typical layout of 2D arrays in RAM.


      (0,0)   +------------+ (numXpix-1, 0)
              |            |
              |            |
              |            |
              |            |
              |            |
              (numYpix-1, 0) +------------+ (numXpix-1, numYpix-1)

      ramConfig Coordinate Systems
      ----------------------------

      This library supports two sets of coordinates for each image:

      - Integer -- much like traditional computer graphics coordinates

      - Floating Point -- much like mathematical coordinates

      The integer coordinates are a generalization of the traditional integer coordinates used for computer graphics.  Like the traditional system, they are
      unsigned integers (so the coordinates start at 0), each pixel is one unit from the previous, and the maximum pixel coordinate is one minus the canvas size in
      that coordinate direction.  The generalization is that the origin of the coordinate system can be any of the four corners.  By default the origin is the
      lower, left corner.  Note that the memory layout of the image is not modified by the integer coordinate system -- i.e. the location of the origin is
      irrelevant when it comes to the layout of bits in RAM.  In RAM the layout is the same as the traditional coordinate system where the coordinates are the
      indexes of the image array.  What is the point?  The location of the origin is taken into consideration when the image is exported/imported by functions like
      writeRAWfile.

      @tparam intCrdT An integral type used for the integer image coordinates.  Mus be large enough to hold the value (numXpix * numYpix)
      @tparam colorT  A type for the image pixels (a color)
      @tparam fltCrdT A floating point type used for the floating point image coordinates
  */
  template <class colorT, class intCrdT, class fltCrdT>
  class ramCanvasTpl {

      static_assert(std::is_integral<intCrdT>::value,
                    "ERROR: intCrdT parameter of ramCanvasTpl template must be an integral type.");
      static_assert(std::is_signed<intCrdT>::value,
                    "ERROR: intCrdT parameter of ramCanvasTpl template must be a signed type.");
      static_assert(std::is_floating_point<fltCrdT>::value,
                    "ERROR: fltCrdT parameter of ramCanvasTpl template must be a floating point type.");

    public:

      /* Prefered typedefs */
      typedef          point2d<fltCrdT>            pointFltType;       //!< Real coordinate pair type
      typedef          point2d<intCrdT>            pointIntType;       //!< Integer coordinate pair type
      typedef          intCrdT                     coordIntType;       //!< Integer type for coordinates
      typedef          fltCrdT                     coordFltType;       //!< Real type for coordinates
      typedef          colorT                      colorType;          //!< Color type for pixels
      typedef typename colorT::channelType         colorChanType;      //!< Channel type for color type for pixels
      typedef typename colorT::channelArithType    colorChanArithType; //!< Type for integer channel arithmetic (clrChanArthT)
      typedef typename colorT::colorSpaceEnum      colorSpaceEnum;

      /* Iterators */
      typedef colorT* pixelIterator; //!< pixel store iterators
      typedef colorT* iterator;      //!< pixel store iterators

      /* Old typedefs */
      typedef point2d<fltCrdT> rcPointFlt; //!< Deprecated! \deprecated Use pointFltType instead
      typedef point2d<intCrdT> rcPointInt; //!< Deprecated! \deprecated Use pointIntType instead
      typedef          intCrdT rcCordInt;  //!< Deprecated! \deprecated Use coordIntType instead
      typedef          fltCrdT rcCordFlt;  //!< Deprecated! \deprecated Use coordFltType instead
      typedef          colorT  rcColor;    //!< Deprecated! \deprecated Use colorTpl instead

      /** Enum for real axis orientation */
      enum class realAxisOrientation { INVERTED,  //!< Real axis is inverted with respect to the integer axis
                                       NATURAL    //!< Real axis is not inverted with respect to the integer axis
      };

      /** Enum for integer axis orientation */
      enum class intAxisOrientation  { INVERTED,  //!< Zero is to the right or bottom
                                       NATURAL    //!< Zero is to the left or top
      };

      /** Enum for drawing Mode */
      enum class drawModeType { SET,
                                XOR,
                                ADDCLIP,
                                AND,
                                OR,
                                DIFFCLIP,
                                MULTCLIP
      };

      /** Enum for drawing Mode */
      enum class interpolationType { BILINEAR, //!< bilinear
                                     TRUNCATE, //!< Coordinates are truncated (fractional bits chopped off)
                                     NEAREST,  //!< Coordinates are rounded
                                     AVERAGE4, //!< Average of four sourounding pixels
                                     AVERAGE9  //!< Average of 9 sourounding pixels
                                   };

      //const static intCrdT intCrdMax = std::sqrt(std::numeric_limits<intCrdT>::max()) - 1; // Some compilers don't think sqrt(const) is const
      const static intCrdT intCrdMax = (1ul << ((sizeof(intCrdT)*CHAR_BIT-1)/2)) - 3;        //!< maximum "on canvas" integer coordinate
      const static intCrdT intCrdMin = 0;                                                    //!< maximum "on canvas" integer coordinate

    private:

      /** Endianness Identifiers. */
      enum class endianType {
        BIG,     //!< PowerPC
        LITTLE,  //!< Intel
        AUTO     //!< Whatever the platform uses
      };

      /** Image File Types. */
      enum class imgFileType { TGA,      //!< 24-bit (8-bit/chan) truecolor.      See: writeTGAstream()
                               TIFF,     //!< TIFF file                           See: writeTIFFstream()
                               BINARY,   //!< The data part of a MJR RAW file.    See: writeBINstream()
                               RAW,      //!< MJR RAW file.                       See: writeRAWstream()
      };

      const static intCrdT intCrdGrdMax = intCrdMax+1; //!< Large sentinel value (always off canvas)
      const static intCrdT intCrdGrdMin = intCrdMin-1; //!< Small sentinel value (always off canvas)

      /** @name Canvas integer coordinates */
      //@{
      intCrdT numXpix;     //!< Number of x pixels
      intCrdT numYpix;     //!< Number of y pixels
      intCrdT numPix;      //!< Number of pixels
      //@}

      /** @name Canvas real coordinates */
      //@{
      fltCrdT minRealX;    //!< x coord of min (real coord)
      fltCrdT maxRealX;    //!< x coord of max (real coord)
      fltCrdT minRealY;    //!< y coord of min (real coord)
      fltCrdT maxRealY;    //!< y coord of max (real coord)
      //@}

      /** @name Canvas real/integer coordinates conversion */
      //@{
      fltCrdT xPixWid;     //!< Width of a pixel (real coord)
      fltCrdT yPixWid;     //!< Height of a pixel (real coord)

      fltCrdT xWid;        //!< Width of the display (real coord)
      fltCrdT yWid;        //!< height of the display(real coord)
      //@}

      /** @name Axis orientation */
      //@{
      realAxisOrientation xRealAxOrientation; //!< Orientation of x axis
      realAxisOrientation yRealAxOrientation; //!< Orientation of y axis
      intAxisOrientation  xIntAxOrientation;  //!< Flip horizontally
      intAxisOrientation  yIntAxOrientation;  //!< Flip vertically
      //@}

      /** @name Canvas pixel store pointers */
      //@{
      colorT *pixels;     //!< Array to hold the color values.
      colorT *pixelsE;    //!< Point one beyond end of pixels array.
      //@}

      /** @name Drawing defaults */
      //@{
      colorT dfltColor;      //!< Default color.
      drawModeType drawMode; //!< Drawing mode.
      intCrdT dfltX;         //!< x coordinate used by default.
      intCrdT dfltY;         //!< y coordinate used by default.
      //@}

      /** @name Filled Triangle Utility Functions */
      //@{
      /** Utliity function behind the drawFillTriangle() functions.
          @param x1 The x coordinate of the first point
          @param y1 The y coordinate of the first point
          @param x2 The x coordinate of the second point
          @param y2 The y coordinate of the second point
          @param x3 The x coordinate of the third point
          @param y3 The y coordinate of the third point
          @param c1 The color of the first point (x1, y1)
          @param c2 The color of the second point (x2, y2)
          @param c3 The color of the third point (x3, y3)
          @param solid Use only c1 if true, otherwise use barycentric interpolation */
      void  drawFillTriangleUtl(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorT c1, colorT c2, colorT c3, bool solid);
      //@}

      /** @name File Writing Utility Methods */
      //@{
      /** Write an unsigned integer to a stream with given length and endianness.
          @param oStream    The ostream object to which to write
          @param endianness The endianness to use for the integer.
          @param numBytes   The number of bytes of the data parameter to use (logically the least significant bits)
          @param data       The integer to write */
      void writeUIntToStream(std::ostream& oStream, endianType endianness, int numBytes, unsigned long int data);
      /** Determine the platform's endianness. */
      endianType platformEndianness();
      /** Write a truecolor TIFF image to the given ostream

          This is the work horse image write function in mraster.

          Why TIFF? TIFF is both broadly supported and flexible enough to represent every ramCanvas image types.

          Use Cases (In order of priority)
              - Write a bit perfect TIFF representation of ramCanvas images
              - Simultaneously convert any ramCanvas into 24-bit truecolor RGB and write the resulting TIFF
              - Do all the above while simultaneously applying a homogeneous image filter

          Limitations for bit perfect (toTRU is NULL) files:

              Channel width must be one of 8, 16, or 32-bits
              Image width must be less than 2^15
              Image height must be less than 2^15
              Image data must be less than 2^32

          @param oStream    The ostream object to which to write
          @param ch4isAlpha If true, identify the first non-image channel as an alpha channel.  If toTRU!=NULL, then alpha is 255.
          @param toTRU      A functor used to transform native pixels into truecolor RGB pixels.
          @param filter     A functor used to transform each pixel. */
      int writeTIFFstream(std::ostream& oStream, bool ch4isAlpha, std::function<colorRGB8b (colorT&)> toTRU, std::function<colorT (colorT&)> filter);
      /** Write the a truecolor TGA image to the given ostream.

          Why TGA? TGA files are not well supported by modern software, so one might ask why this function exists.  I am a POV-Ray fan, and it uses a
          specialized TGA format for height maps.  That's really it...  One could use this function to dump out regular RGB images, but I suggest
          writeTIFFfile for that.

          @param oStream    The ostream object to which to write
          @param toTRU      A functor used to transform native pixels into truecolor RGB pixels.
          @param filter     A functor used to transform each pixel. */
      int writeTGAstream(std::ostream& oStream, std::function<colorRGB8b (colorT&)> toTRU, std::function<colorT (colorT&)> filter);
      /** Write the an MJR RAW format image to the given ostream

          Why? This simple file format is designed to house the more exotic images this library supports, and be easily consumed by many image processing and
          data visualization tools -- usually via a feature referred to as a raw importer.  VisIT, ParaView, and ImageJ all can read this type of data. The
          header is ASCII, and contains two newlines -- the idea being that one can do a 'head -n 2 FILENAME' on the image file, and get a human readable
          output of basic image info.  The file format is very simple:

          - Header: Byte  00-05: "MJRRAW"
          - Header: Byte  06-06: Newline
          - Header: Byte  07-25: Number of pixels on X (horizontal axis) expressed as a zero padded, decimal integer
          - Header: Byte  26-26: "x"
          - Header: Byte  27-45: Number of pixels on Y (vertical axis) expressed as a zero padded, decimal integer
          - Header: Byte  46-46: "y"
          - Header: Byte  47-73: Number of channels expressed as a zero padded, decimal integer
          - Header: Byte  74-74: "c"
          - Header: Byte  75-85: Number of bits per channel expressed as a zero padded, decimal integer
          - Header: Byte  86-86: "b"
          - Header: Byte  87-89: "SGN" for signed channels and "UNS" for unsigned channels
          - Header: Byte  90-90: "s"
          - Header: Byte  91-93: "INT" for integral channels and "FLT" for floating point channels
          - Header: Byte  94-94: "t"
          - Header: Byte  95-97: "BIG" for big endian and "LTL" for Little endian
          - Header: Byte  98-98: "i"
          - Header: Byte  99-99: Newline
          - Data:   Byte 100---: Image data -- each channel dumped in order as it looks in RAM.

          @param oStream  The ostream object to which to write
          @param filter   A functor used to transform each pixel. */
      int writeRAWstream(std::ostream& oStream, std::function<colorT (colorT&)> filter);
      /** Write the binary data for the image to the given ostream
          @param oStream  The ostream object to which to write
          @param filter   A functor used to transform each pixel. */
      int writeBINstream(std::ostream& oStream, std::function<colorT (colorT&)> filter);
      /** Write an image file with the given format and filters.  This is the work horse driver behind all the public write*file functions.
          @param fileName   The file name to write data to
          @param fileType   The type of file to write.
          @param ch4isAlpha If true, write a 32-bit RGBA file.  Otherwise write a 24-bit RGB file.  If toTRU!=NULL, then alpha is 255.
          @param toTRU      A functor used to transform native pixels into truecolor RGB pixels.
          @param filter     A functor used to transform each pixel. */
      int writeFile(std::string fileName, imgFileType fileType, bool ch4isAlpha, std::function<colorRGB8b (colorT&)> toTRU, std::function<colorT (colorT&)> filter);
      //@}

      /** @name Coordinate System Manipulation (i) */
      //@{
      /** Several internal parameters are maintained within this class that make conversion between real coordinates and integer coordinate very fast.  This
          function will update the internal parameters if the real coordinate sizes or the integer coordinate sizes have changed.  This function is intended for
          internal use. An example of when to use this function is right after the integer coordinate axes have changed via a call to newIntCoordsNC(). */
      void updRealCoords();
      /** Change the logical coordinate sizes.  It is important that the specified coordinate sizes describe an image with FEWER pixels than the previous
          sizes.  This function will NOT allocate a new pixel array, so the previous array contents will be interpreted as valid data -- just at different
          coordinates.  This function causes no memory leaks.  This function will NOT update the internal parameters related to real coordinate systems and so
          updRealCoords() should be called after this function in most cases.  This function is intended for internal use and provides no safety checks.
          @param numXpix_p The width of the new canvas
          @param numYpix_p The height of the new canvas */
      void newIntCoordsNC(intCrdT numXpix_p, intCrdT numYpix_p);
      //@}

      /** @name Plane Manipulation Methods */
      //@{
      /** Destroy the current pixel memory and reallocate a new pixel space of the given size.  This will not clear the canvas.  IT will not reallocate the
          canvas unless the new size is different from the current size.  It will not allocate a new canvas if either argument is zero or less.  Updates
          coordinates.
          @param numXpix_p The width of the new canvas
          @param numYpix_p The height of the new canvas */
      void reallocCanvas(intCrdT numXpix_p, intCrdT numYpix_p);
      /** Free the pixel memory (i) */
      void freeCanvas();
      /** Points the pixels pointer at a new pixel store, and updates coordinates.  Pixels pointer not changed if new_pixels is NULL */
      void rePointPixels(colorT *new_pixels, intCrdT new_numXpix, intCrdT new_numYpix);
      //@}

      /** @name Various helper functions */
      //@{
      /** Used to find the left and right edges of a triangle. */
      void triangleEdger(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, bool minSide, intCrdT* pts);
      //@}

    public:

      /** @name Raster Data Import And Export. */
      //@{
      /** Extract raster data from the image, and pack it into a typical form used by imaging applications.

          Each pixel is packed into a 1, 2, 3, or 4 byte memory block with the location of each channel given by redChan, blueChan, greenChan, and alphaChan.
          If one of these values is -1, then that channel is not extracted.  For example, all of them set to -1 except redChan (set to 0), an 8-bit gray scale
          image would be extracted.  One might extract 24-bit RGB with redChan=0, greenChan=1, and blueChan=2.  Add alphaChan=3, and extract 24-bit RGB with
          alpha -- sometimes called 24-bit RGBA or 32-bit RGBA.  Many systems expect the alpha bit to be first, so one might use alphaChan=0, redChan=1,
          greenChan=2, and blueChan=3 to get ARGB.  As a fine example, TARGA images use BGR -- blueChan=0, greenChan=1, and redChan=2.  In summary:
          <pre>
          Examples of how to pack various common raster data formats
          ..........RGB  RGBA  ARGB   BGR  ABGR  Grey
          redChan     0     0     1     2     3     0
          greenChan   1     1     2     1     2    -1
          blueChan    2     2     3     0     1    -1
          alphaChan  -1     3     0    -1     0    -1
          </pre>
          @param rasterData Unsigned char pointer to image data.
          If NULL,then data will be allocated for image.
          @param x1 First x coordinate first corner of sub-image to extract
          @param x2 First x coordinate second corner of sub-image to extract
          @param y1 First y coordinate first corner of sub-image to extract
          @param y2 First y coordinate second corner of sub-image to extract
          @param redChan    Channel index to use for red
          @param blueChan   Channel index to use for blue
          @param greenChan  Channel index to use for green
          @param alphaChan  Channel index to use for alpha*/
      int exportRasterData(void* &rasterData, intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, int redChan, int greenChan, int blueChan, int alphaChan);
      //@}

      /** @name Constructors & Assignment Operators */
      //@{
      /** No arg constructor.  Sets numXpix and numYpix to -1, and pixels to NULL. */
      ramCanvasTpl();
      /** Copy constructor */
      ramCanvasTpl(const ramCanvasTpl &theCanvas);
      /** Most commonly used constructor.  The real coordinates have default values with -1 as the min values and 1 used as the max values.
          @param numXpix_p   Number of pixels in the X direction
          @param numYpix_p   Number of pixels in the Y direction
          @param minRealX_p  Minimum real x coordinate value
          @param maxRealX_p  Maximum real x coordinate value
          @param minRealY_p  Minimum real y coordinate value
          @param maxRealY_p  Maximum real y coordinate value */
      ramCanvasTpl(intCrdT numXpix_p, intCrdT numYpix_p, fltCrdT minRealX_p=-1, fltCrdT maxRealX_p=1, fltCrdT minRealY_p=-1, fltCrdT maxRealY_p=1);
      /** Move constructor */
      ramCanvasTpl(ramCanvasTpl&& theCanvas);
      /** Move assignment operator */
      ramCanvasTpl& operator=(ramCanvasTpl&& theCanvas);

      //@}

      /** @name Destructor */
      //@{
      /** Destructor deallocates memory for the canvas. */
      ~ramCanvasTpl();
      //@}

      /** @name Canvas resize and crop */
      //@{
      /** Resize the canvas to the  given size.  Contents of new canvas may be random data.  Not guarnteed to reallocate the canvas.
          @param new_numXpix_p The width of the new canvas
          @param new_numYpix_p The height of the new canvas */
      void resizeCanvas(intCrdT new_numXpix_p, intCrdT new_numYpix_p);
      /** Expand the current canvas.  The current image will appear within the new canvas at the specified location.  All pixels not set by the previous image
          will be set to the given color.
          @param new_numXpix_p The width of the new canvas
          @param new_numYpix_p The height of the new canvas
          @param x1            Coord at which the left of the old image will appear in the new image
          @param y1            Coord at which the top of the old image will appear in the new image
          @param color         Color to use for the background of the new image. */
      void expandCanvas(intCrdT new_numXpix_p, intCrdT new_numYpix_p, intCrdT x1 = 0, intCrdT y1 = 0, colorT color = colorT(0,0,0));
      /** This function will crop the canvas to the given rectangular region.
          @param x1 Left, or right, edge of region to keep.
          @param x2 Right, or left, edge of region to keep.
          @param y1 Left, or right, edge of region to keep.
          @param y2 Right, or left, edge of region to keep. */
      void cropCanvas(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2);
      //@}

      /** @name Coordinate System Manipulation */
      //@{
      /** This function provides the ability to change the real coordinate system associated with a canvas.  It updates all internal parameters are required.
          @param minRealX_p  Minimum real x coordinate value
          @param maxRealX_p  Maximum real x coordinate value
          @param minRealY_p  Minimum real y coordinate value
          @param maxRealY_p  Maximum real y coordinate value */
      void newRealCoords(fltCrdT minRealX_p, fltCrdT maxRealX_p, fltCrdT minRealY_p, fltCrdT maxRealY_p);
      //@}

      /** @name Canvas Rotation and Reflection. */
      //@{
      /** Loss-less 90 degree clockwise rotation of the canvas about the center.  i.e. the top row of pixels will be on the right side after the rotation.
          The canvas will be resized as required.  The transformation is not done "in place", so enough memory is required to duplicate the canvas.  */
      void rotate90CW();
      /** Loss-less 90 degree counter clockwise rotation of the canvas about the center.  i.e. the top row of pixels will be on the left side after the
          rotation.  The canvas will be resized as required.  The transformation is not done "in place", so enough memory is required to duplicate the canvas. */
      void rotate90CCW();
      /** Loss-less 180 degree rotation of the canvas about the center.  i.e. the top row of pixels will be on the bottom side after the rotation.  The
          transformation is not done "in place", so enough memory is required to duplicate the canvas.  */
      void rotate180();
      /** Loss-less, horizontal flip of the canvas about the center.  i.e. the top row of pixels will be on the bottom side after the flip.  The
          transformation is done "in place" so no extra RAM is required. */
      void flipHorz();
      /** Loss-less, vertical flip of the canvas about the center.  i.e. the left row of pixels will be on the right side after the flip.  The transformation
          is done "in place" so no extra RAM is required. */
      void flipVert();
      /** Loss-less, vertical flip of the canvas about the center.  i.e. the top row of pixels will be on the left side after the flip, and pixel (x,y) will
          be in position (y,x).  The canvas will be resized as required.  The transformation is not done "in place", so enough memory is required to duplicate
          the canvas.   */
      void flipTranspose();
      //@}

      /** @name Canvas Scaling. */
      //@{
      /** Scale up the image using proximal interpolation -- i.e. for each source pixel we create an xfactor*xfactor box filled with the color of the original
          pixel.  The resulting images are block, but the histograms stay accurate.  The algorithm is very fast as it is very simple.
          @param xfactor The factor to scale up to -- must be a positive integer. */
      void scaleUpProximal(int xfactor);
      /** Scale down using only the upper left pixel from each block.  This will tend to highlight horizontal and vertical detail and generally sharpen up the
          image.  Much data is lost with this sort of scaling operation.
          @param xfactor The factor to scale up to -- must be a positive integer. */
      void scaleDown1pt(int xfactor);
      /** Scale down using only the pixel with maximum luminosity in each block.  Much like scaleDown1pt, this will sharpen up a scaled image, but it will
          also tend to brighten up the image as well.
          @param xfactor The factor to scale up to -- must be a positive integer. */
      void scaleDownMax(int xfactor);
      /** Scale down using the mean pixel value from each block.  This creates each pixel value by averaging all of the pixels that contribute -- i.e. a mean
          on the xfactor*xfactor pixel corresponding to each new pixel.  This algorithm tends to "fuzz-up" the result -- frequently used for super-sampling.
          @param xfactor The factor to scale down to -- must be a positive integer. */
      void scaleDownMean(int xfactor);
      //@}

      /** @name Geometric transformations (Reverse Mapping) 
          @warning These functions are under development, and the API may change */
      //@{
      /** Geometric Transform via Radial Polynomial implemented with Reverse Mapping.
          @warning These functions are under development, and the API may change

          @param errorColor The color to use for pixels with no valid mapping.
          @param interpMethod Eventually this will be the interpolation method used.  Right now it is ignored.
          @param RPoly Coefficients for Radial Polynomial with RPoly[0] being the coefficient on the highest power term -- note this direction!!!
          @param Xo X coordinate for the offset from image center
          @param Yo Y coordinate for the offset from image center */
      ramCanvasTpl geomTfrmRevRPoly(std::vector<double> const& RPoly,
                                    double Xo = 0.0,
                                    double Yo = 0.0,
                                    colorT errorColor = colorT::cornerColor::GREEN,
                                    interpolationType interpMethod = interpolationType::BILINEAR);
      /** Geometric Transform via provided mapping function implemented with Reverse Mapping.
          @warning These functions are under development, and the API may change

          @param errorColor The color to use for pixels with no valid mapping.
          @param interpMethod Eventually this will be the interpolation method used.  Right now it is ignored.
          @param f The coordinate transformation function */
      ramCanvasTpl geomTfrmRevArb(mjr::point2d<double> (*f)(double, double),
                                  colorT errorColor = colorT::cornerColor::GREEN,
                                  interpolationType interpMethod = interpolationType::BILINEAR);
      /** Homogenious Affine Geometric Transform implemented with Reverse Mapping.
          @warning These functions are under development, and the API may change

           @verbatim
           [1 0 T_x]   [S_x 0   0]   [cA  sA 0]             [x_in]    [x_out]
           [0 1 T_y]   [0   S_y 0]   [-SA cA 0]         T * [y_in] => [y_out]
           [0 0 1  ]   [0   0   1]   [0   0  1]             [1   ]    [1    ]
           @endverbatim
          @param errorColor The color to use for pixels with no valid mapping.
          @param interpMethod Eventually this will be the interpolation method used.  Right now it is ignored.
          @param HAMatrix The homogenious affine transform matrix (3x3) */
      ramCanvasTpl geomTfrmRevAff(std::vector<double> const& HAMatrix,
                                  colorT errorColor = colorT::cornerColor::GREEN,
                                  interpolationType interpMethod = interpolationType::BILINEAR);
      //@}

      /** @name Convolution */
      //@{
      /** Apply a convolution filter.
          The implementation for this method is quite naive and super slow!  Frankly, this kind of functionality should be pulled from an image processing
          library tuned for this kind of work; however, sometimes you just need a convolution filter and you don't want to go to the extra effort of using yet
          another external library.  Pixels outside the canvas are considered black. So here it is.
          @param kernel  The convolution kernel.   Must be of length kWide*kTall.
          @param kWide   The width of the kernel.  Must be odd.
          @param kTall   The height of the kernel. Must be odd.
          @param divisor Used to normalize dot product at each step.  i.e. one might say the kernel for the convolution is really kernel/divisor. */
      void convolution(double *kernel, int kWide, int kTall, double divisor);
      /** @overload */
      void convolution(double *kernel, int kSize, double divisor);
      /** @overload */
      void convolution(double *kernel, int kSize);
      /** Compute a Gaussian convolution kernel (use with divisor==1.0)
          @param kernel  Pointer to space for the convolution kernel.   Must have at least space for kSize*kSize doubles
          @param kSize   The width and height of the kernel.  Must be odd.
          @param sd      The standard deviation. */
      void computeConvolutionMatrixGausian(double *kernel, int kSize, double sd);
      /** Compute a box blur convolution kernel (use with divisor==1.0)
          @param kernel  Pointer to space for the convolution kernel.   Must have at least space for kSize*kSize doubles
          @param kSize   The width and height of the kernel.  Must be odd. */
      void computeConvolutionMatrixBox(double *kernel, int kSize);

      //@}

      /** @name Iterators */
      //@{
      colorT *begin() { return pixels;  }
      colorT *end()   { return pixelsE; }
      //@}

      /** @name Homogeneous Pixel Transformations (point operators) */
      //@{
      /** Homogeneous pixel transformations don't vary based upon the coordinates of the pixel in question, but depend only upon the value of the pixel.
          Thus, a homogeneous pixel transformation can be considered as a pixel function applied to each pixel in an image.  Many standard pixel functions are
          defined within the colorT object.  The ramCanvasTpl object must then only apply the methods available within each colorT class to support most of
          the standard homogeneous pixel transformations.  Additionally, new functions are automatically available to the ramCanvasTpl (both in the colorT
          class and new functions from other sources). */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)());
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double),                                     double);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double),                              double, double);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double),                       double, double, double);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double),                double, double, double, double);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double),         double, double, double, double, double);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double, double),  double, double, double, double, double, double);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int),                 int);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int),            int, int);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int),       int, int, int);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int, int),  int, int, int, int);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT),                          colorT);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT),                  colorT, colorT);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT),          colorT, colorT, colorT);
      /** @overload */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT, colorT),  colorT, colorT, colorT, colorT);

      /** Computes a linear grey level scale homogeneous pixel transformation with f(c)=(c-cmin)*255/(cmax-cmin) where cmin is the lowest integer value
          assumed by any pixel color component and cmax is the largest integer value assumed by any pixel color component.  This function is sometimes called
          "auto contrast adjust" or "linear auto contrast adjust". */
      void autoHistStrech();
      /** Computes a, possibly different, linear grey level scale homogeneous pixel transformation on each channel of the image such that channel n is
          transformed such that f_n(c)=(c-cmin_n)*255/(cmax_n-cmin_n) where cmin_n and cmax_n are the minimum and maximum values in channel n.  i.e. this is
          the same as applying autoHistStrech independently to each channel.*/
      void autoMaxHistStrech();
      //@}

      /** @name Canvas Combination Functions */
      //@{
      /** This function takes a ramCanvasTpl and combines it with the
          current ramCanvasTpl using mean.
          @param HPT Pointer to a binary operator.
          @param theCanvas This is the ramCanvasTpl to combine with.
          @param trgX Final X coordinate for the left of the combined region. Default: 0
          @param trgY Final Y coordinate for the top of the combined region. Default: 0
          @param srcX Left edge of the region to combine with. Default: 0
          @param srcY Top edge of the  region to combine with. Default: 0
          @param wide Width of the region to combine with. Default: -1 (indicates to edge of canvas)
          @param tall Height of the region to combine with. Default: -1 (indicates to edge of canvas) */
      void combineRamCanvasBinOp(colorT& (colorT::*HPT)(colorT),
                                 const ramCanvasTpl &theCanvas,
                                 intCrdT trgX =  0, intCrdT trgY =  0,
                                 intCrdT wide = -1, intCrdT tall = -1,
                                 intCrdT srcX =  0, intCrdT srcY =  0);
      //@}

      /** @name Statistical Canvas Combination Functions (useful for CCD imaging) */
      //@{
      /** Take a list of ramCanvasTpl objects and combine them with the current ramCanvasTpl using mean.
          @param theCanvasList This is the array of ramCanvasTpl's to combine with.
          @param N The number of canvas objects. */
      void combineRamCanvasMean(ramCanvasTpl *theCanvasList, const int N);
      //@}

      /** @name Canvas Clearing Methods */
      //@{
      /** Clear the canvas to black.  Faster than clrCanvas(BLACK).  */
      void clrCanvasToBlack();
      /** Clear the canvas.   */
      void clrCanvas();
      /** @overload */
      void clrCanvas(colorT color);
      //@}

      /** @name Default Point Methods */
      //@{
      /** Set the current default point to the given coordinates.
          @param x The x coordinate of the point to move to.
          @param y The y coordinate of the point to move to. */
      void moveTo(intCrdT x, intCrdT y);
      /** @overload */
      void moveTo(fltCrdT x, fltCrdT y);
      /** @overload */
      void moveTo(pointIntType thePoint);
      /** @overload */
      void moveTo(pointFltType thePoint);
      //@}

      /** @name Default Color Methods */
      //@{
      /** Set the default color
          @param color The color to use
          @return NONE    */
      void setDfltColor(colorT color);
      /** Set the default color by calling the color constructor with the given argument.    This is "syntax sugar".
          @param colorName The name of the color
          @return NONE    */
      void setDfltColor(const char *colorName);
      /** Set the default color by calling the color constructor with the given arguments.  This is "syntax sugar".
          @param r Red component
          @param g Green component
          @param b Blue component
          @return NONE    */
      void setDfltColor(colorChanType r, colorChanType g, colorChanType b);
      //@}

      /** @name Point drawing functions */
      //@{
      /** Draw a point at the specified coordinates with the specified color.  Overloaded versions exist with various arguments.
          @param x The x coordinate of the point
          @param y The y coordinate of the point
          @param color The color to draw the point */
      void drawPoint(intCrdT x, intCrdT y, colorT color);
      /** @overload */
      void drawPoint();
      /** @overload */
      void drawPoint(colorT color);
      /** @overload */
      void drawPoint(intCrdT x, intCrdT y);
      /** @overload */
      void drawPoint(fltCrdT x, fltCrdT y);
      /** @overload */
      void drawPoint(fltCrdT x, fltCrdT y, colorT color);
      /** @overload */
      void drawPoint(pointIntType thePoint, colorT color);
      /** @overload */
      void drawPoint(pointIntType thePoint);
      /** @overload */
      void drawPoint(pointFltType thePoint);
      /** @overload */
      void drawPoint(pointFltType thePoint, colorT color);
      //@}

      /** @name Line Drawing Methods */
      //@{
      /** Draw a line.  This function is optimized for speed, and has special code for handling lines of slope 0, 1, -1, and infinity.  Line is clipped to the
          current canvas.
          @param x1 x coordinate of the first point
          @param y1 y coordinate of the first point
          @param x2 x coordinate of the second point
          @param y2 y coordinate of the second point
          @param color The color to use
          @return NONE

          @par Performance Note
          This function will perform better if (x1,y2) and (x2,y2) are in the clip region.  Further x1<x2 will save several steps in
          the algorithm.

          @par Algorithm Notes
          This function treats lines of slope 0, 1, -1, and infinity as special cases.  Special clipping and drawing algorithms are
          used for each case.  All other lines are broken up into four classes by slope: 0<m<1, 1<m<infinity, -1<m<0, and -infinity<m<-1.  Separate line
          clipping algorithms are used for positive slope lines and for negative slope lines.

          The algorithms used to draw lines in the last four cases are related to the classic algorithm presented by Bresenham in 1965 and the
          extensions to Bresenham's algorithm given by Pitteway in 1967 and Van Aken in 1984.  The basic algorithm described by Bresenham, Pitteway, and Van
          Aken is known as the "Midpoint Algorithm".  For the case 0<m<1, the algorithm used is actually the midpoint algorithm, and the remaining cases are
          obvious extensions to the midpoint algorithm.  Each case is customized and optimized for the given slope class.

          The clipping algorithm used for the last slope classes is similar in spirit to the Cohen-Sutherland Line-Clipping algorithm, but is optimized
          for each slope class.  Several pre-checks are made in order to avoid the slope computations in the Cohen-Sutherland algorithm -- in fact intersections
          are only computed if absolutely required.  Note that the only floating point computations in this function are the intersection computations, and they
          will be avoided completely if the given line need not be clipped.*/
      void drawLine(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorT color);
      /** @overload */
      void drawLine(intCrdT x,  intCrdT y);
      /** @overload */
      void drawLine(fltCrdT x,  fltCrdT y);
      /** @overload */
      void drawLine(intCrdT x,  intCrdT y,  colorT color);
      /** @overload */
      void drawLine(fltCrdT x,  fltCrdT y,  colorT color);
      /** @overload */
      void drawLine(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2);
      /** @overload */
      void drawLine(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2);
      /** @overload */
      void drawLine(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorT color);
      /** @overload */
      void drawLine(pointFltType point1);
      /** @overload */
      void drawLine(pointFltType point1, colorT color);
      /** @overload */
      void drawLine(pointIntType point1);
      /** @overload */
      void drawLine(pointIntType point1, colorT color);
      /** @overload */
      void drawLine(pointFltType point1, pointFltType point2);
      /** @overload */
      void drawLine(pointFltType point1, pointFltType point2, colorT color);
      /** @overload */
      void drawLine(pointIntType point1, pointIntType point2);
      /** @overload */
      void drawLine(pointIntType point1, pointIntType point2, colorT color);
      //@}

      /** @name Unfilled Triangle Drawing Methods */
      //@{
      /** Draw an un-filled triangle */
      void drawTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3,  colorT color);
      /** @overload */
      void drawTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3);
      /** @overload */
      void drawTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3, colorT color);
      /** @overload */
      void drawTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3);
      /** @overload */
      void drawTriangle(pointIntType point1, pointIntType point2, pointIntType point3, colorT color);
      /** @overload */
      void drawTriangle(pointIntType point1, pointIntType point2, pointIntType point3);
      /** @overload */
      void drawTriangle(pointFltType point1, pointFltType point2, pointFltType point3, colorT color);
      /** @overload */
      void drawTriangle(pointFltType point1, pointFltType point2, pointFltType point3);
      /** @overload */
      void drawTriangle(pointIntType *thePoints, colorT color);
      /** @overload */
      void drawTriangle(pointIntType *thePoints);
      /** @overload */
      void drawTriangle(pointFltType *thePoints, colorT color);
      /** @overload */
      void drawTriangle(pointFltType *thePoints);
      //@}

      /** @name Filled Triangle Drawing Methods */
      //@{
      /** Draw a triangle filled with a solid color using a nicely optimized, horizontal scan conversion algorithm.
          @bug Triangles not entirely on the canvas are not rendered.
          @bug Degenerate trainagles are not rendered
          @param x1 The x coordinate of the first point
          @param y1 The y coordinate of the first point
          @param x2 The x coordinate of the second point
          @param y2 The y coordinate of the second point
          @param x3 The x coordinate of the third point
          @param y3 The y coordinate of the third point
          @param color The color to use for the triangle */
      void drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorT color);
      /** @overload */
      void drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3);
      /** @overload */
      void drawFillTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3, colorT color);
      /** @overload */
      void drawFillTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3);
      /** @overload */
      void drawFillTriangle(pointIntType point1, pointIntType point2, pointIntType point3, colorT color);
      /** @overload */
      void drawFillTriangle(pointIntType point1, pointIntType point2, pointIntType point3);
      /** @overload */
      void drawFillTriangle(pointFltType point1, pointFltType point2, pointFltType point3, colorT color);
      /** @overload */
      void drawFillTriangle(pointFltType point1, pointFltType point2, pointFltType point3);
      /** @overload */
      void drawFillTriangle(pointIntType *thePoints, colorT color);
      /** @overload */
      void drawFillTriangle(pointIntType *thePoints);
      /** @overload */
      void drawFillTriangle(pointFltType *thePoints, colorT color);
      /** @overload */
      void drawFillTriangle(pointFltType *thePoints);
      //@}

      /** @name Filled Triangle Drawing Methods */
      //@{
      /** Draw a filled triangle using barycentric color interpolation.
          @bug Triangles not entirely on the canvas are not rendered.
          @bug Degenerate trainagles are not rendered
          @bug Painfully slow
          @param x1     The x coordinate of the first point
          @param y1     The y coordinate of the first point
          @param x2     The x coordinate of the second point
          @param y2     The y coordinate of the second point
          @param x3     The x coordinate of the third point
          @param y3     The y coordinate of the third point
          @param color1 The color of the first point (x1, y1)
          @param color2 The color of the second point (x2, y2)
          @param color3 The color of the third point (x3, y3) */
      void drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorT color1, colorT color2, colorT color3);
      //@}

      /** @name Unfilled Rectangle Drawing Functions */
      //@{
      /** Draw an unfilled rectangle with diagonal corners located at (x1, y1) and and (x2, y2).  Best performance will be achieved if (x1, y1) is the upper
          left corner, and (x2,y2) is the lower left corner and both (x1,y1) and (x2,y2) are within the bounds of the canvas using the specified color.
          @param x1 The x coordinate of first corner
          @param y1 The y coordinate of first corner
          @param x2 The x coordinate of second corner
          @param y2 The y coordinate of second corner
          @param color The color to use
          @return NONE */
      void drawRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorT color);
      /** @overload */
      void drawRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2);
      /** @overload */
      void drawRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorT color);
      /** @overload */
      void drawRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2);
      /** @overload */
      void drawRectangle(pointIntType point1, pointIntType point2, colorT color);
      /** @overload */
      void drawRectangle(pointIntType point1, pointIntType point2);
      /** @overload */
      void drawRectangle(pointFltType point1, pointFltType point2, colorT color);
      /** @overload */
      void drawRectangle(pointFltType point1, pointFltType point2);
      /** @overload */
      void drawRectangle(pointIntType *thePoints, colorT color);
      /** @overload */
      void drawRectangle(pointIntType *thePoints);
      /** @overload */
      void drawRectangle(pointFltType *thePoints, colorT color);
      /** @overload */
      void drawRectangle(pointFltType *thePoints);
      //@}

      /** @name Filled Rectangle Drawing Methods */
      //@{
      /** Draw a filled rectangle with diagonal corners located at (x1, y1) and and (x2, y2).  Best performance will be achieved if (x1, y1) is the upper left
          corner, and (x2,y2) is the lower left corner and both (x1,y1) and (x2,y2) are within the bounds of the canvas using the specified color.
          @param x1 The x coordinate of first corner
          @param y1 The y coordinate of first corner
          @param x2 The x coordinate of second corner
          @param y2 The y coordinate of second corner
          @param color The color to use
          @return NONE */
      void drawFillRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorT color);
      /** @overload */
      void drawFillRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2);
      /** @overload */
      void drawFillRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorT color);
      /** @overload */
      void drawFillRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2);
      /** @overload */
      void drawFillRectangle(pointIntType point1, pointIntType point2, colorT color);
      /** @overload */
      void drawFillRectangle(pointIntType point1, pointIntType point2);
      /** @overload */
      void drawFillRectangle(pointFltType point1, pointFltType point2, colorT color);
      /** @overload */
      void drawFillRectangle(pointFltType point1, pointFltType point2);
      /** @overload */
      void drawFillRectangle(pointIntType *thePoints, colorT color);
      /** @overload */
      void drawFillRectangle(pointIntType *thePoints);
      /** @overload */
      void drawFillRectangle(pointFltType *thePoints, colorT color);
      /** @overload */
      void drawFillRectangle(pointFltType *thePoints);
      //@}

      /** @name Unfilled Circle Drawing Methods */
      //@{
      /** Draw an un-filled circle.  The algorithm used is based upon the one presented in "A Linear Algorithm for Incremental Digital Display of Circular
          Arcs" published in the Communications of the AMC in Feb 1977 and written by J.E. Bresenham.  Bresenham's algorithm has been significantly improved
          by using only integer arithmetic and adding second order differences to the computation -- much the way the line drawing algorithm works in this
          package.  The algorithm is essentially a scan line conversion algorithm, so the circle is always approximately one pixel thick.  One subtle point:
          The real X and Y axes in this package can have different scaling.  This means that one must pick a direction in which the radius will be measured in
          real coordinate deltas.  In this function, that direction is along the X axis -- i.e. the radius of the drawn circle will be measured
          horizontally. This function is well optimized.
          @param centerX The x coordinate of the center
          @param centerY The y coordinate of the center
          @param radiusX The radius of the circle
          @param color The color to draw the circle with */
      void drawCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorT color);
      /** @overload */
      void drawCircle(intCrdT centerX, intCrdT centerY, intCrdT radius);
      /** @overload */
      void drawCircle(intCrdT radius);
      /** @overload */
      void drawCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX, colorT color);
      /** @overload */
      void drawCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX);
      /** @overload */
      void drawCircle(fltCrdT radiusX);
      /** @overload */
      void drawCircle(pointIntType centerPoint, intCrdT radiusX, colorT color);
      /** @overload */
      void drawCircle(pointIntType centerPoint, intCrdT radiusX);
      /** @overload */
      void drawCircle(pointFltType centerPoint, fltCrdT radiusX, colorT color);
      /** @overload */
      void drawCircle(pointFltType centerPoint, fltCrdT radiusX);
      //@}

      /** @name Filled Circle Drawing Methods */
      //@{
      /** Draw an un-filled circle.  The algorithm used to compute circle edge points is the same as that used in drawCircle; however, the algorithm used to
          fill the circle is of my own design.  I doubt that it is new, but I have never come across it in my readings -- not that I have looked too hard. The
          algorithm has the advantage that most of the interior points are only drawn one time.  One subtle point: The real X and Y axes in this package can
          have different scaling.  This means that one must pick a direction in which the radius will be measured in real coordinate deltas.  In this
          function, that direction is along the X axis -- i.e. the radius of the drawn circle will be measured horizontally. This function is well optimized.
          @param centerX The x coordinate of the center
          @param centerY The y coordinate of the center
          @param radiusX The radius of the circle
          @param color The color to draw the circle with */
      void drawFillCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorT color);
      /** @overload */
      void drawFillCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX);
      /** @overload */
      void drawFillCircle(intCrdT radiusX);
      /** @overload */
      void drawFillCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX, colorT color);
      /** @overload */
      void drawFillCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX);
      /** @overload */
      void drawFillCircle(fltCrdT radiusX);
      /** @overload */
      void drawFillCircle(pointIntType centerPoint, intCrdT radiusX, colorT color);
      /** @overload */
      void drawFillCircle(pointIntType centerPoint, intCrdT radiusX);
      /** @overload */
      void drawFillCircle(pointFltType centerPoint, fltCrdT radiusX, colorT color);
      /** @overload */
      void drawFillCircle(pointFltType centerPoint, fltCrdT radiusX);
      //@}

      /** @name Piece-Wise Linear Curve Drawing Methods */
      //@{
      /** Draw Piece-Wise Linear Curves */
      void drawPLCurve(int numPoints, intCrdT *x, intCrdT *y, colorT color);
      /** @overload */
      void drawPLCurve(int numPoints, intCrdT *x, intCrdT *y);
      /** @overload */
      void drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y, colorT color);
      /** @overload */
      void drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y);
      /** @overload */
      void drawPLCurve(int numPoints, pointIntType *thePoints, colorT color);
      /** @overload */
      void drawPLCurve(int numPoints, pointIntType *thePoints);
      /** @overload */
      void drawPLCurve(int numPoints, pointFltType *thePoints, colorT color);
      /** @overload */
      void drawPLCurve(int numPoints, pointFltType *thePoints);
      //@}

      /** @name Hershey Glyph Rendering Utility Functions */
      //@{
      /** Render a glyph from the Hershey character set.  The glyph is rendered with its origin at the given coordinates.  This function is intended to provide
          only the most basic glyph rendering.  For example, glyphs are rendered with the line drawing functions, and therefore are not anti-aliased.
          @param glyphNum The character number of the glyph to render
          @param x        The x coordinate at which to render the glyph
          @param y        The x coordinate at which to render the glyph
          @param magX     The magnification of the glyph in the x direction
          @param magY     The magnification of the glyph in the y direction
          @param aColor   The color with which to render the glyph */
      void drawHersheyGlyph(int glyphNum, intCrdT x, intCrdT y, double magX, double magY, colorT aColor);
      //@}

      /** @name ASCII Character Rendering
          What are font rendering functions doing in a raster graphics library? Sometimes I like to put a label on image. :)*/
      //@{
      /** Render an ASCII C-string using Hershey ASCII Fonts.  While the string is rendered with fixed font spacing, the Hershey fonts are not fixed width fonts.
          @param aString The string
          @param aFont   The font to set the default with
          @param x       The x coordinate at which to render the first glyph
          @param y       The x coordinate at which to render the first glyph
          @param aColor  The color with which to render the glyphs
          @param cex     A factor by which to expand the size of each glyph -- 1 is a good value (the name comes from R).
          @param spc     Space to jump for each charcter -- 20 for SL fonts, 23 for DL fonts, and 25 for TL fonts.  Scaled with cex. */
      void drawString(std::string aString, hersheyFont aFont, intCrdT x, intCrdT y, colorT aColor, double cex, intCrdT spc);
      /** Renders a filled, bounding box for the given string as rendered via drawString.
          @param aString     A string to render
          @param aFont       The font to set the default with
          @param x           The x coordinate at which to render the first glyph
          @param y           The x coordinate at which to render the first glyph
          @param stringColor The color with which to render the glyphs
          @param boxColor    The color with which to render the BOX
          @param cex         A factor by which to expand the size of each glyph -- 1 is a good value (the name comes from R).
          @param spc         Space to jump for each charcter -- 20 for SL fonts, 23 for DL fonts, and 25 for TL fonts.  Scaled with cex. */
      void drawStringBox(std::string aString, hersheyFont aFont, intCrdT x, intCrdT y, colorT stringColor, colorT boxColor, double cex, intCrdT spc);
      //@}

      /** @name File Reading and Writing Methods */
      //@{
      /** Is libTIFF supported? i.e. will the readTIFFfile() method do anything? */
      bool supportLibTIFF();
      /** If the libTIFF library was found at build time, this function will read a TIFF file into current ramCanvas object.

          If libTIFF is not supported, then this function returns 32.  You can test if this method works via the supportLibTIFF() method.

          Notable features:
             - Arbitrary TIFF image file types are converted to 24-bit RGB when aRamCanvas is of type ramCanvas3c8b
               - Note aRamCanvas must be of type ramCanvas3c8b -- ramCanvas4c8b is not good enough.
             - Reasonable conversions are made in other cases.
               - if aRamCanvas has fewer channels than the TIFF file, then extra channels in the TIFF file are ignored
               - if aRamCanvas has more channels than the TIFF file, then extra channels of aRamCanvas are set to black
               - if aRamCanvas and the TIFF have different channel widths, then the TIFF data is scaled  (TIFF data is assumed to be full scale. Max tags are ignored)
             - Some effort is taken to do the right thing with respect to aRamCanvas axis orientation

          @param fileName The file name from which to read data from.
          @retval  0 Image file loaded successfully
          @retval  1 File open (TIFFOpen) failure
          @retval  2 File missing TIFF tag: IMAGEWIDTH
          @retval  3 File missing TIFF tag: IMAGELENGTH
          @retval  4 File missing TIFF tag: SAMPLESPERPIXEL
          @retval  5 File missing TIFF tag: PLANARCONFIG
          @retval  6 File missing TIFF tag: PHOTOMETRIC
          @retval  7 File missing TIFF tag: BITSPERSAMPLE
          @retval  8 File of zero width
          @retval  9 File of zero height
          @retval 10 Allocation failed (temp image buffer)
          @retval 11 Read (TIFFReadRGBAImage) failure
          @retval 12 Canvas Allocation failed (insufficient width)
          @retval 14 Canvas Allocation failed (insufficient height)
          @retval 15 TIFF bps not 8, 16, 32, or 64
          @retval 16 Allocation failed (scan line buffer)
          @retval 17 Read (TIFFReadScanline) failure
          @retval 32 TIFF read support not provided in this compile */
      int readTIFFfile(std::string fileName);
      /** Write a TIFF format image file.  Respects integer coordinate system orientation.

          \see writeTIFFstream

          @param fileName The file name to write data to
          @param toTRU    A functor used to transform native pixels into truecolor RGB pixels.
          @param filter   A functor used to transform each pixel. */
      int writeTIFFfile(std::string fileName, std::function<colorRGB8b (colorT&)> toTRU=NULL, std::function<colorT (colorT&)> filter=NULL);
      /** Write a 24-bit (8-bit per channel) RGB, TGA format graphics file.  Respects integer coordinate system orientation.

          \see writeTGAstream

          @param fileName The file name name to write data to */
      int writeTGAfile(std::string fileName);
      /** Write a MJRRAW file. Respects integer coordinate system orientation.

          \see writeRAWstream

          @param fileName The file name name to write data to
          @param filter   A functor used to transform each pixel.
          @retval 0 The write was successful.
          @retval 1 Could not open file. */
      int writeRAWfile(std::string fileName, std::function<colorT (colorT&)> filter = NULL);
      //@}

      /** @name Boolean Clip Test Methods */
      //@{
      /** Determine if the given point is within the bounds of the ramCanvasTpl.
          @param x The x coordinate of the point to test
          @param y The y coordinate of the point to test
          @return Returns a non-zero quantity if the point would be clipped. */
      int isCliped(fltCrdT x, fltCrdT y);
      /** @overload */
      int isCliped(intCrdT x, intCrdT y);
      //@}

      /** @name Coordinate Conversions. */
      //@{
      /** Convert real x coordinate to integral x coordinate
          @param x The real x coordinate value to be converted.
          @return The integer x coordinate corresponding to the given x coordinate */
      int real2intX(fltCrdT x) const;
      /** Convert real y coordinate to integral y coordinate
          @param y The real y coordinate value to be converted.
          @return The integer y coordinate corresponding to the given y coordinate */
      int real2intY(fltCrdT y) const;
      /** Convert integral x coordinate to real x coordinate
          @param x The integer x coordinate value to be converted.
          @return The real x coordinate corresponding to the given x coordinate */
      fltCrdT int2realX(intCrdT x);
      /** Convert integral y coordinate to real y coordinate
          @param y The integer y coordinate value to be converted.
          @return The real y coordinate corresponding to the given y coordinate */
      fltCrdT int2realY(intCrdT y);
      //@}

      /** @name Coordinate Delta Conversions. */
      //@{
      /** Convert real distance on the x coordinate axis to an integral distance
          @param x The real delta x to be converted
          @return integer delta x */
      int realDelta2intX(fltCrdT x) const;
      /** Convert real distance on the y coordinate axis to an integral distance
          @param y The real delta y to be converted
          @return integer delta y */
      int realDelta2intY(fltCrdT y) const;
      /** Convert integral distance on the x coordinate to a real distance
          @param x The real x coordinate value to be converted.
          @return The integer x coordinate corresponding to the given x coordinate */
      fltCrdT intDelta2realX(intCrdT x);
      /** Convert integral distance on the y coordinate to a real distance
          @param y real y coordinate value to be converted.
          @return The integer y coordinate corresponding to the given y coordinate */
      fltCrdT intDelta2realY(intCrdT y);
      //@}

      /** @name Orientation of Real Coordinate Systems */
      //@{
      /** Get the real X axis orientation
          @return INVERTED means inverted with respect to the integer axis, and NATURAL otherwise.    */
      realAxisOrientation get_xRealAxisOrientation();
      /** Set the real X axis orientation
          @param orientation The orientation (INVERTED or NATURAL)*/
      void set_xRealAxisOrientation(realAxisOrientation orientation);
      /** Get the real Y axis orientation
          @return INVERTED means inverted with respect to the integer axis, and NATURAL otherwise.    */
      realAxisOrientation get_yRealAxisOrientation();
      /** Set the real Y axis orientation
          @param orientation The orientation (INVERTED or NATURAL) */
      void set_yRealAxisOrientation(realAxisOrientation orientation);
      /** Set the real axis orientation to default (NATURAL for both X and Y axes) */
      void set_realAxisDefaultOrientation();
      //@}

      /** @name Drawing Mode */
      //@{
      /** Get the current drawing mode
          @return NATURAL means increasing to the right. */
      drawModeType get_drawMode();
      /** Set the current drawing mode
          @param newDrawMode The drawing mode */
      void set_drawMode(drawModeType newDrawMode);
      /** Set the default draw mode */
      void set_DefaultDrawMode();
      //@}

      /** @name Orientation of Integer Coordinate Systems */
      //@{
      /** Get the integer X axis orientation
          @return NATURAL means increasing to the right. */
      intAxisOrientation get_xIntAxisOrientation();
      /** Set the integer X axis orientation
          @param orientation The orientation (INVERTED or NATURAL) */
      void set_xIntAxisOrientation(intAxisOrientation orientation);
      /** Get the integer Y axis orientation
          @return NATURAL means increasing in the upward direction. */
      intAxisOrientation get_yIntAxisOrientation();
      /** Set the integer Y axis orientation
          @param orientation The orientation (INVERTED or NATURAL) */
      void set_yIntAxisOrientation(intAxisOrientation orientation);
      /** Set the integer axis orientation to default (NATURAL for both X and Y axes) */
      void set_intAxisDefaultOrientation();
      //@}

      /** @name Accessor Methods */
      //@{
      /** @return The number of pixels in the x direction. */
      intCrdT get_numXpix() const;
      /** @return The number of pixels in the y direction. */
      intCrdT get_numYpix() const;
      /** Returns a pointer to the raw pixel store.  This generally violates the ramCanvasTpl object interface; however, this may be required for performance.
          @return The number a pointer to the raw pixel store. */
      colorT *getPixels() { return pixels; }
      /** Return a clone (a copy) of the raw pixel store.  This function copies the internal pixel store and returns a pointer to this copy.
          @return Pointer to a copy of the raw pixel store. */
      colorT *clonePixels();
      //@}

      /** @name Accessor Methods */
      //@{
      fltCrdT get_minRealX() { return minRealX; } //!< x coord of min (real coord)
      fltCrdT get_maxRealX() { return maxRealX; } //!< x coord of max (real coord)
      fltCrdT get_minRealY() { return minRealY; } //!< y coord of min (real coord)
      fltCrdT get_maxRealY() { return maxRealY; } //!< y coord of max (real coord)
      fltCrdT get_xPixWid()  { return xPixWid;  } //!< Width of a pixel (real coord)
      fltCrdT get_yPixWid()  { return yPixWid;  } //!< Height of a pixel (real coord)
      fltCrdT get_xWid()     { return xWid;     } //!< Width of the display (real coord)
      fltCrdT get_yWid()     { return yWid;     } //!< height of the display(real coord)
      //@}

      /** @name Pixel Value Accessor Methods */
      //@{
      /** Returns a copy of the color at the given coordinates */
      colorT getPxColor(intCrdT x, intCrdT y) const;
      /** @overload */
      colorT getPxColor(fltCrdT x, fltCrdT y) const;
      /** @overload */
      colorT getPxColor(pointIntType thePoint) const;
      /** @overload */
      colorT getPxColor(pointFltType thePoint) const;
      //@}

      /** @param x The x coordinate of the upper left pixel to query
          @param y The y coordinate of the upper left pixel to query
          @param width The number of x pixels to query
          @param height The number of y pixels to query
          @return A ramCanvasTpl pointer that points to a new ramCanvasTpl object that is \a width pixels wide and \a height pixels tall.  The pixel values in
          the new canvas will be the same as the selected pixels from the current ramCanvasTpl.  The returned ramCanvasTpl will have the default color
          and points of the current ramCanvasTpl.  If the current ramCanvasTpl has a default point is outside of the selected ample, the returned
          ramCanvasTpl will have it's default point set to (0,0).  Clipping will be performed if required. If width is zero, then the width of the
          returned ramCanvasTpl will be from the given x coordinate to the far right edge.  If the height is zero, then the height of the returned
          ramCanvasTpl will be from the given y coordinate to lower edge of the current ramCanvasTpl.  An argument list of all zeros will return a copy
          of the current ramCanvasTpl in it's entirety.
          @retval NULL If no pixels are sampled.  This will happen, for example, if the x and y coordinates given are beyond the ramCanvasTpl. */
      ramCanvasTpl *getSubCanvas(intCrdT x, intCrdT y, intCrdT width, intCrdT height);
      //@}

      /** @name Pixel Value Accessor with Interpolation Methods */
      //@{
      /** Returns the interpolated color value at the the given coordinates using the given interpolation method
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @param interpMethod The interpolation method (default: interpolationType::BILINEAR)
          @return Interpolated color value */
      colorT getPxColorInterpolate(double x, double y, interpolationType interpMethod = interpolationType::BILINEAR);
      /** Returns the bilinear interpolated color value at the the given coordinates
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpBLin(double x, double y);
      /** Returns the truncated interpolated color value at the the given coordinates
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpTrunc(double x, double y);
      /** Returns the nearest neighbor  interpolated color value at the the given coordinates
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpNear(double x, double y);
      /** Returns the average 4 interpolated color value at the the given coordinates
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpAvg4(double x, double y);
      /** Returns the average 9 interpolated color value at the the given coordinates
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpAvg9(double x, double y);
      //@}

      /** @name NC stands for No Checks and No Clipping */
      /** The functions here work in a similar way to the non-NC functions, but with no clipping or bounds checking.  Thus, if an argument would cause
          something to be drawn beyond the bounds of the ramCanvasTpl, a core dump will most certainly result.  The intent is to provide less overhead for
          very careful code that handles clipping and error checking by itself -- a good line drawing algorithm for example. */
      //@{
      /** Draw a point with no clipping or bounds checking.
          @param x The x coordinate of the point to be drawn
          @param y The y coordinate of the point to be drawn
          @param color The color to draw the point.
          @return NONE */
      void drawPointNC(intCrdT x, intCrdT y, colorT color);
      /** Get the default point to the specified coordinates with no clipping or bounds checking.
          @param x The x coordinate of the point
          @param y The y coordinate of the point
          @return NONE */
      colorT getPxColorNC(intCrdT x, intCrdT y) const;
      /** Returns a reference to the color object for the given pixel with no clipping or bounds checking.
          @param x The x coordinate of the point
          @param y The y coordinate of the point
          @return Reference to the color object associated with the specified point */
      colorT& getPxColorRefNC(intCrdT x, intCrdT y) const;
      /** Draw a horizontal line with no clipping or bounds checking.
          @param xMin The MINIMUM x coordinate of the line to be drawn
          @param xMax The MAXIMUM x coordinate of the line to be drawn
          @param yConst The y coordinate at which the line is to be drawn
          @param color The color to draw the line
          @return NONE */
      void drawHorzLineNC(intCrdT xMin, intCrdT xMax, intCrdT yConst, colorT color);
      /** Draw a vertical line with no clipping or bounds checking.
          @param yMin The MINIMUM y coordinate of the line to be drawn
          @param yMax The MAXIMUM y coordinate of the line to be drawn
          @param xConst The x coordinate at which the line is to be drawn
          @param color The color to draw the line
          @return NONE */
      void drawVertLineNC(intCrdT yMin, intCrdT yMax, intCrdT xConst, colorT color);
      //@}

      /** @name S stands for Simple */
      //@{
      /** This function supports no special drawing options.  It simply sets the pixel to the given color.  In addition, no clipping or bounds checking is
          performed.  Thus, if an argument would cause something to be drawn beyond the bounds of the ramCanvasTpl, a core dump will most certainly result.
          The intent is to provide a less overhead for very careful code that handles clipping and error checking and drawing options by itself -- an image
          filter algorithm for example.  The options expected to be taken care of are: SUPPORT_ALWAYS_PRESERVE_ALPHA, and SUPPORT_DRAWING_MODE.  It is
          conceivable that the other draw pixel functions could call this one, but a good optimizing compiler must be used in this case or a performance
          impact will be the result.
          @param x The x coordinate of the point
          @param y The y coordinate of the point
          @param color The color with which to draw the point
          @return NONE  */
      void drawPointS(intCrdT x, intCrdT y, colorT color);
      //@}
  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Constructor
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::ramCanvasTpl() {
    //std::cout << "DEBUG: ramCanvasTpl no-arg constructor" << std::endl;
    newIntCoordsNC(-1, -1);
    pixels = NULL;
    pixelsE = NULL;
    set_realAxisDefaultOrientation();
    set_intAxisDefaultOrientation();
    set_DefaultDrawMode();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Copy Constructor
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::ramCanvasTpl(const ramCanvasTpl &theCanvas) {
    //std::cout << "DEBUG: ramCanvasTpl copy constructor" << std::endl;
    newIntCoordsNC(theCanvas.numXpix, theCanvas.numYpix);
    newRealCoords(theCanvas.minRealX, theCanvas.maxRealX, theCanvas.minRealY, theCanvas.maxRealY);
    pixels = new colorT[theCanvas.numXpix * theCanvas.numYpix];
    pixelsE = pixels + (theCanvas.numXpix * theCanvas.numYpix);
    xRealAxOrientation = theCanvas.xRealAxOrientation;
    yRealAxOrientation = theCanvas.yRealAxOrientation;
    xIntAxOrientation = theCanvas.xIntAxOrientation;
    yIntAxOrientation = theCanvas.yIntAxOrientation;
    drawMode = theCanvas.drawMode;
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        getPxColorRefNC(x, y) = theCanvas.getPxColorRefNC(x, y);
  }

//  MJR TODO NOTE <2022-06-30T15:28:38-0500> ramCanvasTpl.hpp: Impliment Copy assignment operator

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Move constructor
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::ramCanvasTpl(ramCanvasTpl<colorT, intCrdT, fltCrdT>&& theCanvas) {
    //std::cout << "DEBUG: ramCanvasTpl move constructor" << std::endl;
    newIntCoordsNC(theCanvas.numXpix, theCanvas.numYpix);
    newRealCoords(theCanvas.minRealX, theCanvas.maxRealX, theCanvas.minRealY, theCanvas.maxRealY);
    xRealAxOrientation = theCanvas.xRealAxOrientation;
    yRealAxOrientation = theCanvas.yRealAxOrientation;
    xIntAxOrientation  = theCanvas.xIntAxOrientation;
    yIntAxOrientation  = theCanvas.yIntAxOrientation;
    drawMode           = theCanvas.drawMode;
    pixels             = theCanvas.pixels;
    pixelsE            = theCanvas.pixelsE;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Move assignment operator
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>&
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::operator=(ramCanvasTpl<colorT, intCrdT, fltCrdT>&& theCanvas) {
    //std::cout << "DEBUG: ramCanvasTpl move assignment operator" << std::endl;
    if (this != &theCanvas) {
      newIntCoordsNC(theCanvas.numXpix, theCanvas.numYpix);
      newRealCoords(theCanvas.minRealX, theCanvas.maxRealX, theCanvas.minRealY, theCanvas.maxRealY);
      xRealAxOrientation = theCanvas.xRealAxOrientation;
      yRealAxOrientation = theCanvas.yRealAxOrientation;
      xIntAxOrientation  = theCanvas.xIntAxOrientation;
      yIntAxOrientation  = theCanvas.yIntAxOrientation;
      drawMode           = theCanvas.drawMode;
      pixels             = theCanvas.pixels;
      pixelsE            = theCanvas.pixelsE;
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Normal Constructor
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::ramCanvasTpl(intCrdT numXpix_p, intCrdT numYpix_p, fltCrdT minRealX_p, fltCrdT maxRealX_p, fltCrdT minRealY_p, fltCrdT maxRealY_p) {
    // std::cout << "DEBUG: ramCanvasTpl normal constructor" << std::endl;
    newIntCoordsNC(numXpix_p, numYpix_p);
    newRealCoords(minRealX_p, maxRealX_p, minRealY_p, maxRealY_p);
    pixels = new colorT[numXpix * numYpix];
    pixelsE = pixels + (numXpix * numYpix);
    set_realAxisDefaultOrientation();
    set_intAxisDefaultOrientation();
    set_DefaultDrawMode();
    clrCanvasToBlack();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::~ramCanvasTpl() {
    if(pixels != NULL) {
      delete[] pixels;
      pixels = NULL;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_drawMode(drawModeType newDrawMode) {
    drawMode = newDrawMode;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_DefaultDrawMode() {
    set_drawMode(drawModeType::SET);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  typename ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawModeType
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::get_drawMode() {
    return drawMode;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::newIntCoordsNC(intCrdT numXpix_p, intCrdT numYpix_p) {
    if( (numXpix_p <= intCrdMax) && (numYpix_p <= intCrdMax) ) {
      numPix  = numXpix_p * numYpix_p;;
      numXpix = numXpix_p;
      numYpix = numYpix_p;
    } else {
      // ERROR!!!
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::newRealCoords(fltCrdT minRealX_p, fltCrdT maxRealX_p, fltCrdT minRealY_p, fltCrdT maxRealY_p) {
    if( (minRealX_p <= maxRealX_p) && (minRealY_p <= maxRealY_p) ) {
      minRealX = minRealX_p;
      maxRealX = maxRealX_p;
      minRealY = minRealY_p;
      maxRealY = maxRealY_p;
      updRealCoords();
    } else {
      // This is an error.  We should do something about. ;)
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::updRealCoords() {
    xWid = maxRealX - minRealX;
    yWid = maxRealY - minRealY;
    xPixWid = xWid / numXpix;
    yPixWid = yWid / numYpix;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::clrCanvasToBlack() {
    ////// Diffrent ways to do it -- all about the same performance with GCC...
    //// Use std:memset
    // std::memset((void*)pixels, 0, numPix*sizeof(colorT));
    //// Use std:fill
    // colorT black;
    // black.setToBlack();
    // std::fill(pixels, pixelsE, black);
    //// Loop over pixel array
    // for(colorT* p=pixels; p<pixelsE; p++)
    //   p->setToBlack();
    //// loop over x & y coordinates
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        getPxColorRefNC(x, y).setToBlack();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::clrCanvas() {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        drawPointS(x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::clrCanvas(colorT color) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        drawPointS(x, y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::autoHistStrech() {
    colorChanType cmin = colorT::maxChanVal;
    colorChanType cmax = colorT::minChanVal;
    for(intCrdT y=0;y<numYpix;y++) {
      for(intCrdT x=0;x<numXpix;x++) {
        colorT theColor = getPxColorNC(x, y);
        colorChanType curMin = theColor.getMinC();
        colorChanType curMax = theColor.getMaxC();

        if(curMax > cmax)
          cmax = curMax;

        if(curMin < cmin)
          cmin = curMin;
      }
    }
    if(cmax-cmin > 0) {
      double c = 1.0 * static_cast<double>(colorT::maxChanVal-colorT::minChanVal) / static_cast<double>(cmax-cmin);
      double b = static_cast<double>(colorT::maxChanVal) - 1.0 * c * static_cast<double>(cmax);
      applyHomoPixTfrm(&colorT::tfrmLinearGreyLevelScale, c, b);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::autoMaxHistStrech() {
    colorT cmin; cmin.setAll(cmin.maxChanVal);
    colorT cmax; cmax.setAll(cmin.minChanVal);
    for(intCrdT y=0;y<numYpix;y++) {
      for(intCrdT x=0;x<numXpix;x++) {
        colorT theColor = getPxColorNC(x, y);
        cmin.tfrmMin(theColor);
        cmax.tfrmMax(theColor);
      }
    }
    colorChanType absCompMin = cmin.getMinC();
    colorChanType absCompMax = cmax.getMaxC();
    if(absCompMax-absCompMin > 0) {
      float rc = 1.0*(cmin.maxChanVal-cmin.minChanVal)/(cmax.getRed()-cmin.getRed());
      float rb = cmin.maxChanVal - 1.0*rc*cmax.getRed();
      float gc = 1.0*(cmin.maxChanVal-cmin.minChanVal)/(cmax.getGreen()-cmin.getGreen());
      float gb = cmin.maxChanVal - 1.0*gc*cmax.getGreen();
      float bc = 1.0*(cmin.maxChanVal-cmin.minChanVal)/(cmax.getBlue()-cmin.getBlue());
      float bb = cmin.maxChanVal - 1.0*bc*cmax.getBlue();
      applyHomoPixTfrm(&colorT::tfrmLinearGreyLevelScale, rc, rb, gc, gb, bc, bb);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)()) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT), colorT arg1) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT), colorT arg1, colorT arg2) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT), colorT arg1, colorT arg2, colorT arg3) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT, colorT), colorT arg1, colorT arg2, colorT arg3, colorT arg4) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int), int arg1) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int), int arg1, int arg2) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int), int arg1, int arg2, int arg3) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int, int), int arg1, int arg2, int arg3, int arg4) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double), double arg1) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double), double arg1, double arg2) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double), double arg1, double arg2, double arg3) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double), double arg1, double arg2, double arg3, double arg4) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double), double arg1, double arg2, double arg3, double arg4, double arg5) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4, arg5);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double, double), double arg1, double arg2, double arg3, double arg4, double arg5, double arg6) {
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4, arg5, arg6);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void ramCanvasTpl<colorT, intCrdT, fltCrdT>::combineRamCanvasBinOp(colorT& (colorT::*HPT)(colorT),
                                                                     const ramCanvasTpl &theCanvas,
                                                                     intCrdT trgX, intCrdT trgY,
                                                                     intCrdT wide, intCrdT tall,
                                                                     intCrdT srcX, intCrdT srcY) {
    // Figure out real default width
    if(wide < 0)
      wide = numXpix-trgX;

    // Make sure wide is not wider than current canvas.
    if(wide > (numXpix-srcX))
      wide = theCanvas.get_numXpix()-srcX;

    // Make sure wide is not wider than given canvas.
    if(wide > (theCanvas.get_numXpix()-srcX))
      wide = theCanvas.get_numXpix()-srcX;

    // Figure out real default tall
    if(tall < 0)
      tall = numYpix-srcY;

    // Make sure tall is not taller than current canvas.
    if(tall > (numYpix-srcY))
      tall = numYpix-srcY;

    // Make sure tall is not taller than given canvas.
    if(tall > (theCanvas.get_numYpix()-srcY))
      tall = theCanvas.get_numYpix()-srcY;

    intCrdT xMax = trgX+wide;
    intCrdT yMax = trgY+tall;
    for(intCrdT y=trgY, ys=srcY; y<yMax; y++, ys++)
      for(intCrdT x=trgX, xs=srcX; x<xMax; x++, xs++)
        (getPxColorRefNC(x, y).*HPT)(theCanvas.getPxColor(xs, ys));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::moveTo(intCrdT x, intCrdT y) {
    dfltX = x;
    dfltY = y;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::moveTo(fltCrdT x, fltCrdT y) {
    moveTo(real2intX(x), real2intY(y));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::moveTo(pointIntType thePoint) {
    moveTo(thePoint.x, thePoint.y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::moveTo(pointFltType thePoint) {
    moveTo(real2intX(thePoint.x), real2intY(thePoint.y));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::setDfltColor(colorT color) {
    dfltColor = color;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::setDfltColor(const char *colorName) {
    dfltColor = colorT(colorName);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::setDfltColor(colorChanType r, colorChanType g, colorChanType b) {
    dfltColor = colorT(r, g, b);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint() {
    drawPoint(dfltX, dfltY, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(colorT color) {
    drawPoint(dfltX, dfltY, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(intCrdT x, intCrdT y) {
    drawPoint(x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(fltCrdT x, fltCrdT y) {
    drawPoint(x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(fltCrdT x, fltCrdT y,
                                                    colorT color) {
    drawPoint(real2intX(x), real2intY(y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(pointIntType thePoint, colorT color) {
    drawPoint(thePoint.x, thePoint.y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(pointIntType thePoint) {
    drawPoint(thePoint.x, thePoint.y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(pointFltType thePoint) {
    drawPoint(real2intX(thePoint.x), real2intY(thePoint.y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(pointFltType thePoint, colorT color) {
    drawPoint(real2intX(thePoint.x), real2intY(thePoint.y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPoint(intCrdT x, intCrdT y, colorT color) {
    if((x >= 0) && (y >= 0) && (x<numXpix) && (y<numYpix))
      drawPointNC(x, y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointFltType point1) {
    intCrdT dfltXnew = real2intX(point1.x);
    intCrdT dfltYnew = real2intY(point1.y);
    drawLine(dfltX, dfltY, dfltXnew, dfltYnew, dfltColor);
    moveTo(dfltXnew, dfltYnew);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointFltType point1, colorT color) {
    intCrdT dfltXnew = real2intX(point1.x);
    intCrdT dfltYnew = real2intY(point1.y);
    drawLine(dfltX, dfltY, dfltXnew, dfltYnew, color);
    moveTo(dfltXnew, dfltYnew);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointIntType point1) {
    drawLine(dfltX, dfltY, point1.x, point1.y, dfltColor);
    moveTo(point1.x, point1.y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointIntType point1, colorT color) {
    drawLine(dfltX, dfltY, point1.x, point1.y, color);
    moveTo(point1.x, point1.y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointFltType point1, pointFltType point2) {
    drawLine(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointFltType point1, pointFltType point2, colorT color) {
    drawLine(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointIntType point1, pointIntType point2) {
    drawLine(point1.x, point1.y, point2.x, point2.y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(pointIntType point1, pointIntType point2, colorT color) {
    drawLine(point1.x, point1.y, point2.x, point2.y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(intCrdT x, intCrdT y) {
    drawLine(dfltX, dfltY, x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(fltCrdT x, fltCrdT y) {
    drawLine(dfltX, dfltY, real2intX(x), real2intY(y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(intCrdT x, intCrdT y, colorT color) {
    drawLine(dfltX, dfltY, x, y, color);
    moveTo(x, y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(fltCrdT x, fltCrdT y, colorT color) {
    intCrdT dfltXnew = real2intX(x);
    intCrdT dfltYnew = real2intY(y);
    drawLine(dfltX, dfltY, dfltXnew, dfltYnew, color);
    moveTo(dfltXnew, dfltYnew);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2) {
    drawLine(x1, y1, x2, y2, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2) {
    drawLine(x1, y1, x2, y2, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorT color) {
    drawLine(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorT color) {
    intCrdT x, y;
    if(y1 == y2) {                                                            // slope = 0
      if( (y1 < 0) || (y1 >= numYpix) )                                       // . Line off canvas case
        return;
      if(x1 > x2)                                                             // . Fix point ordering
        std::swap(x1, x2);
      if(x1 < 0)                                                              // . Clip left
        x1 = 0;
      if(x2 >= numXpix)                                                       // . Clip right
        x2 = numXpix - 1;
      drawHorzLineNC(x1, x2, y1, color);                                      // . Draw Pixels
    } else if(x1 == x2) {                                                     // slope = infinity
      if( (x1 < 0) || (x1 >= numXpix) )                                       // . Line off canvas case
        return;
      if(y1 > y2)                                                             // . Fix point ordering
        std::swap(y1, y2);
      if(y1 < 0)                                                              // . Clip top
        y1 = 0;
      if(y2 >= numYpix)                                                       // . Clip bottom
        y2 = numYpix - 1;
      drawVertLineNC(y1, y2, x1, color);                                      // . Draw Pixels
    } else {                                                                  // Slope is not infinity or 0...
      int dx, dy;
      if(x1 > x2) {                                                           // . Fix point ordering
        std::swap(x1, x2);
        std::swap(y1, y2);
      }
      dx = x2 - x1;                                                           // . Compute the slope
      dy = y2 - y1;
      if(dx == dy) {                                                          // . Slope = 1
        if( (y2 < 0) || (x2 < 0) || (x1 >= numXpix) || (y1 >= numYpix) )      // .. Line off canvas case
          return;
        if(x1 < 0) {                                                          // .. Clip left
          y1 = y1 - x1;
          x1 = 0;
        }
        if(y1 < 0) {                                                          // .. Clip top
          x1 = x1 - y1;
          y1 = 0;
        }
        if(x2 >= numXpix) {                                                   // .. Clip right
          y2 = y2 - (x2 - numXpix) - 1;
          x2 = numXpix - 1;
        }
        if(y2 >= numYpix) {                                                   // .. Clip bottom
          x2 = x2 - (y2 - numYpix) - 1;
          y2 = numYpix - 1;
        }
        for(x=x1,y=y1;x<=x2;y++,x++)                                          // .. Draw Pixels
          drawPointNC(x, y, color);
      } else if(dx == -dy) {                                                  // . Slope = -1
        if( (x2 < 0) || (y2 >= numYpix) || (x1 >= numXpix) || (y1 < 0) )      // .. Line off canvas case
          return;
        if(x1 < 0) {                                                          // .. Clip left
          y1 = y1 + x1;
          x1 = 0;
        }
        if(x2 >= numXpix) {                                                   // .. Clip right
          y2 = y2 + (x2 - (numXpix - 1));
          x2 = numXpix - 1;
        }
        if(y2 < 0) {                                                          // .. Clip top
          x2 = x2 + y2;
          y2 = 0;
        }
        if(y1 >= numYpix) {                                                   // .. Clip bottom
          x1 = x1 + (y1 - (numYpix - 1));
          y1 = numYpix - 1;
        }
        for(x=x1,y=y1;x<=x2;y--,x++)                                          // .. Draw Pixels
          drawPointNC(x, y, color);
      } else {                                                                // . Slope != 1, -1, 0, \infinity
        int s, dx2, dy2;
        dx2 = 2*dx;
        dy2 = 2*dy;
        if(dy > 0) {                                                          // .. Positive Slope
          if( (y2 < 0) || (x2 < 0) || (x1 >= numXpix) || (y1 >= numYpix) )    // ... Line off canvas case
            return;
          if(x1 < 0) {                                                        // ... Clip left
            y1 = (int)(1.0*y1-x1*dy/dx);
            x1 = 0;
          }
          if(y1 < 0) {                                                        // ... Clip top
            x1 = (int)(1.0*x1-y1*dx/dy);
            y1 = 0;
          }
          if(x2 >= numXpix) {                                                 // ... Clip right
            y2 = (int)((1.0*dy*(numXpix-1)+y1*dx-x1*dy)/dx);
            x2 = numXpix - 1;
          }
          if(y2 >= numYpix) {                                                 // ... Clip bottom
            x2 = (int)(((numYpix-1)*dx-y2*dx+x2*dy)/dy);
            y2 = numYpix - 1;
          }
//  MJR TODO NOTE <2022-06-18T13:11:56-0500> ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawLine: We use drawPoint instead of drawPointNC, can we make an off canvas decesion instead? Similar case down below.
          if(dx > dy) {                                                       // ... 0 < Slope < 1
            s = dy2 - dx;
            x=x1;
            y=y1;
            while(x<=x2) {                                                    // .... Draw Line
              drawPoint(x, y, color);
              if(s < 0) {
                s += dy2;
              } else {
                y++;
                s += dy2 - dx2;
              }
              x++;
            }
          } else {                                                            // ... 1 < Slope < infinity
            s = dy - dx2;
            x=x1;
            y=y1;
            while(y<=y2) {                                                    // .... Draw Line
              drawPoint(x, y, color);
              if(s > 0) {
                s -= dx2;
              } else {
                x++;
                s += dy2 - dx2;
              }
              y++;
            }
          }
        } else {                                                              // .. Negative Slope
          if( (x2 < 0) || (y2 >= numYpix) || (x1 >= numXpix) || (y1 < 0) )    // ... Line off canvas case
            return;
          if(x1 < 0) {                                                        // ... Clip left
            y1 = (int)(1.0*y1-x1*dy/dx);
            x1 = 0;
          }
          if(y2 < 0) {                                                        // ... Clip top
            x2 = (int)(1.0*x2-y2*dx/dy);
            y2 = 0;
          }
          if(x2 >= numXpix) {                                                 // ... Clip right
            y2 = (int)((1.0*dy*(numXpix-1)+y2*dx-x2*dy)/dx);
            x2 = numXpix - 1;
          }
          if(y1 >= numYpix) {                                                 // ... Clip bottom
            x1 = (int)(((numYpix-1)*dx-y1*dx+x1*dy)/dy);
            y1 = numYpix - 1;
          }
          if(dx > -dy) {                                                      // ... 0 > Slope > -infinity
            s = dy2 + dx;
            x=x1;
            y=y1;
            while(x<=x2) {                                                    // .... Draw Line
              drawPoint(x, y, color);
              if(s > 0) {
                s += dy2;
              } else {
                y--;
                s += dy2 + dx2;
              }
              x++;
            }
          } else {                                                            // ... -1 > Slope > -inf
            s = dy + dx2;
            x=x1;
            y=y1;
            while(y>=y2) {                                                    // .... Draw Line
              drawPoint(x, y, color);
              if(s < 0) {
                s += dx2;
              } else {
                x++;
                s += dy2 + dx2;
              }
              y--;
            }
          }
        }
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::freeCanvas() {
    newIntCoordsNC(-1, -1);
    if(pixels != NULL) {
      delete[] pixels;
      pixels=NULL;
      pixelsE=NULL;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::rePointPixels(colorT *new_pixels, intCrdT new_numXpix, intCrdT new_numYpix) {
    freeCanvas();
    newIntCoordsNC(new_numXpix, new_numYpix);
    updRealCoords();
    if(new_pixels != NULL)
      pixels = new_pixels;
    if(pixels == NULL)
      pixelsE = NULL;
    else
      pixelsE = pixels+(new_numXpix * new_numYpix);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::reallocCanvas(intCrdT numXpix_p, intCrdT numYpix_p) {
    if((numXpix_p<=0) || (numYpix_p<=0)) {
      freeCanvas();
    } else {
      if( (numXpix_p!=numXpix) || (numYpix_p!=numYpix) ) {
        colorT *new_pixels = new colorT[numXpix_p * numYpix_p];
        rePointPixels(new_pixels, numXpix_p, numYpix_p);
      } else {
        // Don't really do anything as the new size is the same as the old size...
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::resizeCanvas(intCrdT new_numXpix_p, intCrdT new_numYpix_p) {
    reallocCanvas(new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::expandCanvas(intCrdT new_numXpix_p, intCrdT new_numYpix_p, intCrdT x1, intCrdT y1, colorT color) {
    if( (new_numXpix_p != numXpix) || (new_numYpix_p != numYpix) ) {
      if(x1 >= new_numXpix_p)
        x1=0;
      if(y1 >= new_numYpix_p)
        y1=0;

      colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];

      // Fill it up with the default color.  Should only draw the ones that need it, but computers are fast...
      for(intCrdT y=0;y<new_numYpix_p;y++)
        for(intCrdT x=0;x<new_numXpix_p;x++)
          new_pixels[new_numXpix_p * (y) + (x)] = color;

      intCrdT yMax = new_numYpix_p;
      if(yMax > (new_numYpix_p-y1))
        yMax = new_numYpix_p-y1;

      intCrdT xMax = new_numXpix_p;
      if(xMax > (new_numXpix_p-x1))
        xMax = new_numXpix_p-x1;

      // Copy the old image to the new space.
      for(intCrdT y=y1;y<yMax;y++)
        for(intCrdT x=0;x<xMax;x++)
          new_pixels[new_numXpix_p * (y) + (x)] = getPxColor(x-x1, y-y1);

      rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::cropCanvas(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2) {
    if( !isCliped(x1, y1) && !isCliped(x2, y2) ) {
      if(x1 > x2)
        std::swap(x1, x2);
      if(y1 > y2)
        std::swap(y1, y2);
      intCrdT xp, yp, x, y;
      intCrdT new_numXpix_p = x2-x1+1;
      intCrdT new_numYpix_p = y2-y1+1;
      colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];

      // Copy the old image to the new space.
      for(y=y1,yp=0;y<=y2;y++,yp++)
        for(x=x1,xp=0;x<=x2;x++,xp++)
          new_pixels[new_numXpix_p * yp + xp] = getPxColor(x, y);

      rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::flipHorz() {
    for(intCrdT y=0; y<numYpix/2; y++)
      for(intCrdT x=0; x<numXpix; x++) {
        colorT aColor = getPxColor(x, numYpix-y-1);
        drawPointNC(x, numYpix-y-1, getPxColor(x, y));
        drawPointNC(x, y, aColor);
      }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::flipVert() {
    for(intCrdT x=0; x<numXpix/2; x++)
      for(intCrdT y=0; y<numYpix; y++) {
        colorT aColor = getPxColor(numXpix-x-1, y);
        drawPointNC(numXpix-x-1, y, getPxColor(x, y));
        drawPointNC(x, y, aColor);
      }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::flipTranspose() {
    intCrdT new_numXpix_p = numYpix;
    intCrdT new_numYpix_p = numXpix;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        new_pixels[new_numXpix_p * (x/*y-crd*/) + (y/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::rotate90CW() {
    intCrdT new_numXpix_p = numYpix;
    intCrdT new_numYpix_p = numXpix;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        new_pixels[new_numXpix_p * (x/*y-crd*/) + (numYpix-y-1/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::rotate90CCW() {
    intCrdT new_numXpix_p = numYpix;
    intCrdT new_numYpix_p = numXpix;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        new_pixels[new_numXpix_p * (numXpix-x-1/*y-crd*/) + (y/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::rotate180() {
    intCrdT new_numXpix_p = numXpix;
    intCrdT new_numYpix_p = numYpix;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        new_pixels[new_numXpix_p * (numYpix-y-1/*y-crd*/) + (numXpix-x-1/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  typename ramCanvasTpl<colorT, intCrdT, fltCrdT>::endianType ramCanvasTpl<colorT, intCrdT, fltCrdT>::platformEndianness() {
    unsigned int endiannessProbe = 1;
    if(((char *)&endiannessProbe)[0]) {
      return(endianType::LITTLE);
    } else {
      return(endianType::BIG);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeUIntToStream(std::ostream& oStream,
                                                            typename ramCanvasTpl<colorT, intCrdT, fltCrdT>::endianType endianness,
                                                            int numBytes,
                                                            unsigned long int data) {
    if((numBytes>0) && (numBytes<9)) {
      endianType endiannessToUse = (endianness == endianType::AUTO ? platformEndianness() : endianness);
      if(endiannessToUse ==  endianType::LITTLE) {
        for(int curByte=0; curByte<numBytes; curByte++) {
          uint8_t tmp = ((data >> (8*curByte)) & 0xff);
          oStream.write((const char *)&tmp, 1);
        }
      } else {
        for(int curByte=(numBytes-1); curByte>=0; curByte--) {
          uint8_t tmp = ((data >> (8*curByte)) & 0xff);
          oStream.write((const char *)&tmp, 1);
        }
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeTIFFstream(std::ostream& oStream,
                                                          bool ch4isAlpha,
                                                          std::function<colorRGB8b (colorT&)> toTRU,
                                                          std::function<colorT (colorT&)> filter) {
    endianType fe = endianType::LITTLE;
    //endianType fe = endianType::BIG;

    if(fe == endianType::LITTLE) {
      writeUIntToStream(oStream, fe, 2, 0x4949); // Write little endian magic number
    } else {
      writeUIntToStream(oStream, fe, 2, 0x4d4d); // Write big endian magic number
    }

    writeUIntToStream(oStream, fe, 2, 42);     // Write TIFF magic number
    writeUIntToStream(oStream, fe, 4, 8);      // IDF offset

    uint32_t tifWidth  = (uint32_t)numXpix;              // ImageWidth
    uint32_t tifLength = (uint32_t)numYpix;              // ImageLength & RowsPerStrip
    uint16_t tifBPS    = (uint32_t)colorT::bitsPerChan;  // BitsPerSample
    uint32_t tifSPP    = (uint32_t)colorT::channelCount; // SamplesPerPixel

    if(toTRU) {
      tifBPS = 8;
      tifSPP = 3;
    } else {
      if(colorT::bitsPerChan < 8)                                                           // channels too thin
        return 2;
      if(colorT::bitsPerChan > 0xffff)                                                      // channels too  fat
        return 3;
      if(colorT::channelCount < 1)                                                          // too few channels
        return 4;
      if(colorT::channelCount > 0xffff)                                                     // too many channels
        return 5;
      if(numXpix < 1)                                                                       // too skinny
        return 6;
      if(numXpix > 0x7fffffff)                                                              // too wide
        return 7;
      if(numYpix < 1)                                                                       // too short
        return 8;
      if(numYpix > 0x7fffffff)                                                              // too tall
        return 9;
      if(numXpix * colorT::bitsPerChan / 8ul * colorT::channelCount > 0xffffffff)           // rows too big
        return 10;
      if(numXpix * numYpix * colorT::channelCount * colorT::bitsPerChan / 8ul > 0xffffffff) // image too big
        return 11;
    }

    uint32_t bytePerSmp  = tifBPS / 8;                                 // Bytes per sample
    uint32_t tifSBC      = tifLength * tifWidth * bytePerSmp * tifSPP; // StripByteCounts
    bool     haveRGB     = tifSPP>=3;                                  // TRUE if this image has RGB data (at least 3 channels)
    uint16_t numImgSmp   = (haveRGB ? 3 : 1);                          // Number of samples used for image data (3 for RGB, 1 otherwise)
    uint16_t tifPMI      = (haveRGB ? 2 : 1);                          // PhotometricInterp
    bool     haveXS      = !((tifSPP==1) || (tifSPP==3));              // TRUE if this image has ExtraSamples data
    bool     haveManyXS  = tifSPP>4;                                   // TRUE if this image has MORE THAN ONE ExtraSamples data
    uint16_t numTags     = 1+14 + (haveXS ? 1 : 0);                    // Number fo tags in this image
    bool     haveManyBPS = tifSPP>1;                                   // TRUE if this image has MORE THAN ONE BitsPerSample data
    uint32_t numXS       = tifSPP - numImgSmp;                         // Number of extra samples
    uint32_t xResOff     = 14 + 12 * numTags;                          // XResolution offset
    uint32_t yResOff     = xResOff + 8;                                // YResolution offset
    uint32_t bpsOff      = yResOff + 8;                                // BitsPerSample offset
    uint32_t xsOff       = bpsOff  + (haveManyBPS ? 2 * tifSPP : 0);   // ExtraSamples offset
    uint32_t imgOff      = xsOff + (haveManyXS  ? 2 * numXS : 0);      // Image Data offset

    writeUIntToStream(oStream, fe, 2, numTags);                                                                                                                         // Tag Count
    writeUIntToStream(oStream, fe, 2, 0x100); writeUIntToStream(oStream, fe, 2, 4); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, tifWidth);  // ImageWidth
    writeUIntToStream(oStream, fe, 2, 0x101); writeUIntToStream(oStream, fe, 2, 4); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, tifLength); // ImageLength
    writeUIntToStream(oStream, fe, 2, 0x102); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, tifBPS);    writeUIntToStream(oStream, fe, 2, 0);// BitsPerSample
    writeUIntToStream(oStream, fe, 2, 0x103); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, 1);         writeUIntToStream(oStream, fe, 2, 0);// Compression
    writeUIntToStream(oStream, fe, 2, 0x106); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, tifPMI);    writeUIntToStream(oStream, fe, 2, 0);// PhotometricIn
    writeUIntToStream(oStream, fe, 2, 0x111); writeUIntToStream(oStream, fe, 2, 4); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, imgOff);    // StripOffsets
    writeUIntToStream(oStream, fe, 2, 0x112); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, 1);         writeUIntToStream(oStream, fe, 2, 0);// Orientation
    writeUIntToStream(oStream, fe, 2, 0x115); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, tifSPP); writeUIntToStream(oStream, fe, 2, 0);    // SamplesPerPixel
    writeUIntToStream(oStream, fe, 2, 0x116); writeUIntToStream(oStream, fe, 2, 4); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, tifLength); // RowsPerStrip
    writeUIntToStream(oStream, fe, 2, 0x117); writeUIntToStream(oStream, fe, 2, 4); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, tifSBC);    // StripByteCounts
    writeUIntToStream(oStream, fe, 2, 0x11A); writeUIntToStream(oStream, fe, 2, 5); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, xResOff);   // XResolution
    writeUIntToStream(oStream, fe, 2, 0x11B); writeUIntToStream(oStream, fe, 2, 5); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, yResOff);   // YResolution
    writeUIntToStream(oStream, fe, 2, 0x11C); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, 1);         writeUIntToStream(oStream, fe, 2, 0);// PlanarConf
    writeUIntToStream(oStream, fe, 2, 0x128); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, 1);         writeUIntToStream(oStream, fe, 2, 0);// ResolutionUnit
    if(haveXS) {                                                                                                                                                        // ExtraSamples
      if(haveManyXS) {
        writeUIntToStream(oStream, fe, 2, 0x152); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, numXS); writeUIntToStream(oStream, fe, 4, xsOff);
      } else {
        if(ch4isAlpha) {
          writeUIntToStream(oStream, fe, 2, 0x152); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1);        writeUIntToStream(oStream, fe, 4, 1);
        } else {
          writeUIntToStream(oStream, fe, 2, 0x152); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1);        writeUIntToStream(oStream, fe, 4, 0);
        }
      }
    }

    writeUIntToStream(oStream, fe, 2, 0x153); writeUIntToStream(oStream, fe, 2, 3); writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 2, 1);         writeUIntToStream(oStream, fe, 2, 1);// SampleFormat

    writeUIntToStream(oStream, fe, 4, 0);                                                                                                                               // IFD END
    writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, 1);                                                                                         // XResolutionData
    writeUIntToStream(oStream, fe, 4, 1); writeUIntToStream(oStream, fe, 4, 1);                                                                                         // YResolutionData
    if(haveManyBPS) {                                                                                                                                                   // YResolutionData
      for(unsigned int i=0; i<tifSPP; i++)
        writeUIntToStream(oStream, fe, 2, tifBPS);
    }
    if(haveManyXS) {                                                                                                                                                    // ExtraSamplesData
      for(unsigned int i=0; i<numXS; i++)
        if((i==numImgSmp) && ch4isAlpha) {
          writeUIntToStream(oStream, fe, 4, 1);
        } else {
          writeUIntToStream(oStream, fe, 4, 0);
        }
    }
    // Image data
    intCrdT x, y;
    bool yNat = !(yIntAxOrientation==intAxisOrientation::NATURAL);
    bool xNat = xIntAxOrientation==intAxisOrientation::NATURAL;
    for((yNat?y=0:y=(numYpix-1)); (yNat?y<numYpix:y>=0); (yNat?y++:y--)) {
      for((xNat?x=0:x=(numXpix-1)); (xNat?x<numXpix:x>=0); (xNat?x++:x--)) {
        colorT aColor = getPxColorRefNC(x, y);
        if(filter != NULL)
          aColor = filter(aColor);
        if(toTRU == NULL) {
          for(int c=0; c<aColor.channelCount; c++) {
            colorChanType aChanValue = aColor.getChan(c);
            writeUIntToStream(oStream, fe, bytePerSmp, aChanValue);
          }
        } else {
          colorRGB8b bColor = toTRU(aColor);
          oStream.put(bColor.getRed());
          oStream.put(bColor.getGreen());
          oStream.put(bColor.getBlue());
          if(ch4isAlpha)

#pragma warning( push )
#pragma warning( disable : 4309 )
#pragma warning( disable : 4068 )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
            oStream.put(255);
#pragma GCC diagnostic pop
#pragma warning( pop )
        }
      }
    }
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeTGAstream(std::ostream& oStream,
                                                         std::function<colorRGB8b (colorT&)> toTRU,
                                                         std::function<colorT     (colorT&)> filter) {
    /* Write header */
    oStream.put(0);                 /* id length */
    oStream.put(0);                 /* colourmaptype */
    oStream.put(2);                 /* datatypecode: 2 == Truecolor no encodeing, 3 == Monochrome image data  no encodeing */
    oStream.put(0);                 /* 16-bit colourmaporigin */
    oStream.put(0);
    oStream.put(0);                 /* colurmaplength */
    oStream.put(0);
    oStream.put(0);                 /* colormapdepth */
    oStream.put(0);                 /* 16-bit x_origin */
    oStream.put(0);
    oStream.put(0);                 /* 16-bit y_origon */
    oStream.put(0);
    writeUIntToStream(oStream, endianType::LITTLE, 2, numXpix);
    writeUIntToStream(oStream, endianType::LITTLE, 2, numYpix);
    oStream.put(24);              /* bits per pixel */
    oStream.put(0);               /* imagedescriptor */

    /* Write data */
    intCrdT x, y;
    /* Normally I would not resort to such trickery; however, this is an exception.  The following for loop is equivalent to switching between the two forms
       "for(y=(numYpix-1); y>=0; y--)" and "for(y=0; y<numYpix; y++)". */
    bool yNat = yIntAxOrientation==intAxisOrientation::NATURAL;
    bool xNat = xIntAxOrientation==intAxisOrientation::NATURAL;
    for((yNat?y=0:y=(numYpix-1)); (yNat?y<numYpix:y>=0); (yNat?y++:y--)) {
      for((xNat?x=0:x=(numXpix-1)); (xNat?x<numXpix:x>=0); (xNat?x++:x--)) {
        colorT aColor = getPxColorRefNC(x, y);
        if(filter != NULL)
          aColor = filter(aColor);
        if(toTRU == NULL) {
          oStream.put(aColor.getBlue8bit());
          oStream.put(aColor.getGreen8bit());
          oStream.put(aColor.getRed8bit());
        } else {
          colorRGB8b bColor = toTRU(aColor);
          oStream.put(bColor.getBlue());
          oStream.put(bColor.getGreen());
          oStream.put(bColor.getRed());
        }
      }
    }
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeBINstream(std::ostream& oStream, std::function<colorT (colorT&)> filter) {
    intCrdT x, y;
    /* Normally I would not resort to such trickery; however, this is an exception.  The following for loop is equivalent to switching between the two forms
       "for(y=(numYpix-1); y>=0; y--)" and "for(y=0; y<numYpix; y++)". */
    bool yNat = !(yIntAxOrientation==intAxisOrientation::NATURAL);
    bool xNat = xIntAxOrientation==intAxisOrientation::NATURAL;
    for((yNat?y=0:y=(numYpix-1)); (yNat?y<numYpix:y>=0); (yNat?y++:y--)) {
      for((xNat?x=0:x=(numXpix-1)); (xNat?x<numXpix:x>=0); (xNat?x++:x--)) {
        colorT aColor = getPxColorRefNC(x, y);
        if(filter != NULL)
          aColor = filter(aColor);
        for(int c=0; c<aColor.channelCount; c++) {
          colorChanType aChanValue = aColor.getChan(c);
          oStream.write((const char *)&aChanValue, sizeof(colorChanType));
        }
      }
    }
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeRAWstream(std::ostream& oStream, std::function<colorT (colorT&)> filter) {
    std::ostringstream outStringStream;
    outStringStream << "MJRRAW\n";                                                                   //  7   7
    outStringStream << std::setw(19) << std::setfill('0') << numXpix                 << "x";         // 20  27
    outStringStream << std::setw(19) << std::setfill('0') << numYpix                 << "y";         // 20  47
    outStringStream << std::setw(27) << std::setfill('0') << colorT::channelCount    << "c";         // 28  75
    outStringStream << std::setw(11) << std::setfill('0') << colorT::bitsPerChan     << "b";         // 12  87
    outStringStream << "UNS"                                                         << "s";         //  4  91
    outStringStream << "FLT"                                                         << "t";         //  4  95
    outStringStream << (platformEndianness() == endianType::LITTLE ? "LTL" : "BIG")  << "i";         //  4  99
    outStringStream                                                                  << "\n";        //  1 100
    oStream << outStringStream.str();
    writeBINstream(oStream, filter);
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeRAWfile(std::string fileName, std::function<colorT (colorT&)> filter) {
    return writeFile(fileName, imgFileType::RAW, false, NULL, filter);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeTGAfile(std::string fileName) {
    return writeFile(fileName, imgFileType::TGA, false, NULL, NULL);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeTIFFfile(std::string fileName,
                                                        std::function<colorRGB8b (colorT&)> toTRU,
                                                        std::function<colorT     (colorT&)> filter) {
    return writeFile(fileName, imgFileType::TIFF, false, toTRU, filter);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::writeFile(std::string fileName,
                                                    imgFileType fileType,
                                                    bool ch4isAlpha,
                                                    std::function<colorRGB8b (colorT&)> toTRU,
                                                    std::function<colorT     (colorT&)> filter) {
    bool useCout = ( (fileName[0] == '-') && (fileName[1] == '\0') );
    std::ostream* oStream;
    std::ofstream oFileStream;
    if(useCout) {
      oStream = &std::cout;
    } else {
      oFileStream.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
      if (oFileStream.is_open()) {
        oFileStream.imbue(std::locale::classic());
        oStream = &oFileStream;
      } else {
        return 1;
      }
    }

    switch(fileType) {
      case imgFileType::TGA    : writeTGAstream(*oStream,              toTRU, filter); break;
      case imgFileType::TIFF   : writeTIFFstream(*oStream, ch4isAlpha, toTRU, filter); break;
      case imgFileType::RAW    : writeRAWstream(*oStream, filter);                break;
      case imgFileType::BINARY : writeBINstream(*oStream, filter);                break;
    }

    if(!useCout)
      oFileStream.close();

    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::exportRasterData(void* &rasterData,
                                                           intCrdT x1,  intCrdT y1,
                                                           intCrdT x2,  intCrdT y2,
                                                           int redChan, int greenChan, int blueChan, int alphaChan) {
    if(x1 > x2)   // Get x1 < x2
      std::swap(x1, x2);
    if(y1 > y2)   // Get y1 < y2
      std::swap(y1, y2);

    if(x1 <  0)        return 1; // Outside of canvas
    if(x2 >= numXpix)  return 1; // Outside of canvas
    if(y1 <  0)        return 1; // Outside of canvas
    if(y2 >= numYpix)  return 1; // Outside of canvas
    if(x2 <  x1)       return 2; // Region too small (x direction)
    if(y2 <  y1)       return 3; // Region too small (y direction)

    int bytesPerPix = (redChan<0?0:1) + (greenChan<0?0:1) + (blueChan<0?0:1) + (alphaChan<0?0:1);
    if(bytesPerPix < 1) return 4; // Exit if no channels selected

    if(rasterData == 0) // Allocate space if rasterData==NULL.  Caller must delete[]
      rasterData = (uint8_t *) new uint8_t[(y2-y1+1)*(x2-x1+1)*bytesPerPix];

    if(rasterData == 0) return 5; // Exit if something went wrong with allocate...

    uint8_t *curPixComp = (uint8_t *)rasterData;
    for(intCrdT y=y1; y<=y2; y++) {
      for(intCrdT x=x1; x<=x2; x++) {
        colorT aColor = getPxColorNC(x, y);
        if(redChan   >= 0) curPixComp[redChan]   = aColor.getRed8bit();
        if(greenChan >= 0) curPixComp[greenChan] = aColor.getGreen8bit();
        if(blueChan  >= 0) curPixComp[blueChan]  = aColor.getBlue8bit();
        if(alphaChan >= 0) curPixComp[alphaChan] = aColor.getAlpha8bit();
        curPixComp += bytesPerPix;
      } /* end for x */
    } /* end for y */

    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::isCliped(fltCrdT x, fltCrdT y) {
    return isCliped(real2intX(x), real2intY(y));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::isCliped(intCrdT x, intCrdT y) {
    if((x >= 0) && (y >= 0) && (x<numXpix) && (y<numYpix))
      return 0;
    else
      return 1;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  typename ramCanvasTpl<colorT, intCrdT, fltCrdT>::realAxisOrientation
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::get_xRealAxisOrientation() {
    //return xRealAxOrientation
    // TODO -- CHECK ME OUT
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_xRealAxisOrientation(realAxisOrientation orientation) {
    xRealAxOrientation = orientation;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  typename ramCanvasTpl<colorT, intCrdT, fltCrdT>::realAxisOrientation
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::get_yRealAxisOrientation() {
    return xRealAxOrientation;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_yRealAxisOrientation(realAxisOrientation orientation) {
    yRealAxOrientation = orientation;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_realAxisDefaultOrientation() {
    set_xRealAxisOrientation(realAxisOrientation::NATURAL);
    set_yRealAxisOrientation(realAxisOrientation::NATURAL);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  typename ramCanvasTpl<colorT, intCrdT, fltCrdT>::intAxisOrientation
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::get_xIntAxisOrientation() {
    return xIntAxOrientation;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_xIntAxisOrientation(intAxisOrientation orientation) {
    xIntAxOrientation = orientation;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  typename ramCanvasTpl<colorT, intCrdT, fltCrdT>::intAxisOrientation
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::get_yIntAxisOrientation() {
    return yIntAxOrientation;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_yIntAxisOrientation(intAxisOrientation orientation) {
    yIntAxOrientation = orientation;
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::set_intAxisDefaultOrientation() {
    set_xIntAxisOrientation(intAxisOrientation::NATURAL);
    set_yIntAxisOrientation(intAxisOrientation::NATURAL);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::real2intX(fltCrdT x) const {
    if(xRealAxOrientation == realAxisOrientation::NATURAL)
      return (int)((x - minRealX) / xPixWid);
    else
      return (int)((maxRealX - x) / xPixWid);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::real2intY(fltCrdT y) const {
    if(yRealAxOrientation == realAxisOrientation::NATURAL)
      return (int)((y - minRealY) / yPixWid);
    else
      return (int)((maxRealY - y) / yPixWid);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::realDelta2intX(fltCrdT x) const {
      return (int)(x/xPixWid);
 }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::realDelta2intY(fltCrdT y) const {
      return (int)(y/yPixWid);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  fltCrdT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::intDelta2realX(intCrdT x) {
    return (fltCrdT)(x*xPixWid);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  fltCrdT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::intDelta2realY(intCrdT y) {
    return (fltCrdT)(y*yPixWid);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  fltCrdT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::int2realX(intCrdT x) {
    if(xRealAxOrientation == realAxisOrientation::NATURAL)
      return x * xPixWid + minRealX;
    else
      return maxRealX - x * xPixWid;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  fltCrdT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::int2realY(intCrdT y) {
    if(yRealAxOrientation == realAxisOrientation::NATURAL)
      return y * yPixWid + minRealY;
    else
      return maxRealY - y * yPixWid;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  intCrdT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::get_numXpix() const {
    return numXpix;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  intCrdT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::get_numYpix() const {
    return numYpix;
  }

  template<class colorT, class intCrdT, class fltCrdT>
  colorT *ramCanvasTpl<colorT, intCrdT, fltCrdT>::clonePixels() {
    colorT *pixelsCopy = new colorT[numXpix * numYpix];
    for(intCrdT y=0; y<numYpix; y++)
      for(intCrdT x=0; x<numXpix; x++)
        pixelsCopy[numXpix * y + x] = getPxColorNC(x, y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColor(intCrdT x, intCrdT y) const {
    if((x >= 0) && (y >= 0) && (x<numXpix) && (y<numYpix)) {
      return pixels[numXpix * y + x];
    } else {
      return colorT().setToBlack();
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColor(fltCrdT x, fltCrdT y) const {
    return getPxColor(real2intX(x), real2intY(y));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColor(pointIntType thePoint) const {
    return getPxColor(thePoint.x, thePoint.y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColor(pointFltType thePoint) const {
    return getPxColor(thePoint.x, thePoint.y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>*
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getSubCanvas(intCrdT x, intCrdT y, intCrdT width, intCrdT height) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT> *subRamCanvas =
      new ramCanvasTpl<colorT, intCrdT, fltCrdT>(width, height);

    intCrdT xMax = width+x;
    if(xMax>numXpix)
      xMax = numXpix;

    intCrdT yMax = height+y;
    if(yMax>numYpix)
      yMax = numYpix;

    for(intCrdT yi=y; yi<yMax; yi++)
      for(intCrdT xi=x; xi<xMax; xi++)
        subRamCanvas->drawPointNC(xi-x, yi-y, getPxColor(xi, yi));

    return subRamCanvas;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorInterpolate(double x, double y, interpolationType interpMethod) {
      switch (interpMethod) {
        case interpolationType::BILINEAR : return getPxColorInterpBLin(x, y);
        case interpolationType::TRUNCATE : return getPxColorInterpBLin(x, y);
        case interpolationType::NEAREST  : return getPxColorInterpBLin(x, y);
        case interpolationType::AVERAGE4 : return getPxColorInterpBLin(x, y);
        case interpolationType::AVERAGE9 : return getPxColorInterpBLin(x, y);
        default                          : return colorT("green"); // Just in case I add an enum value, and forget to update this switch.
      }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorInterpBLin(double x, double y) {
    double x1 = std::floor(x);
    double y1 = std::floor(y);
    double x2 = std::ceil(x);
    double y2 = std::ceil(y);

    intCrdT x1i = static_cast<intCrdT>(x1);
    intCrdT y1i = static_cast<intCrdT>(y1);
    intCrdT x2i = static_cast<intCrdT>(x2);
    intCrdT y2i = static_cast<intCrdT>(y2);

    if ((x1i >= 0) && (y1i >= 0) && (x2i < numXpix) && (y2i < numYpix)) {
      double eps = 0.00001;
      double xD21 = x2 - x1;
      double yD21 = y2 - y1;
      double wH = 1.0;
      if (xD21 > eps)
        wH = (x  - x1) / xD21;
      double wV = 1.0;
      if (yD21 > eps)
        wV = (y  - y1) / yD21;

      colorT c1;
      colorT c2;
      colorT cF;

      c1.interplColors(wH, pixels[numXpix * y1i + x1i], pixels[numXpix * y1i + x2i]);
      c2.interplColors(wH, pixels[numXpix * y2i + x1i], pixels[numXpix * y2i + x2i]);
      cF.interplColors(wV, c1, c2);
      return cF;
    } else {
      return colorT().setToBlack();
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorInterpTrunc(double x, double y) {
    return getPxColor(static_cast<intCrdT>(std::trunc(x)), static_cast<intCrdT>(std::trunc(y)));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorInterpNear(double x, double y) {
    return getPxColor(static_cast<intCrdT>(std::round(x)), static_cast<intCrdT>(std::round(y)));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorInterpAvg9(double x, double y) {
    intCrdT xi = static_cast<intCrdT>(std::round(x));
    intCrdT yi = static_cast<intCrdT>(std::round(y));
    colorT newColor;
    for(int chan=0; chan<colorT::channelCount; chan++) {
      colorChanArithType newChanValue = 0;
      for(intCrdT ydi=-1; ydi<=1; ydi++) {
        intCrdT icY = yi + ydi;
        for(intCrdT xdi=-1; xdi<=1; xdi++) {
          intCrdT icX = xi + xdi;
          if (!(isCliped(icX, icY))) {
            newChanValue += getPxColor(icX, icY).getChan(chan);
          }
        }
      }
      newColor.setChan(chan, static_cast<colorChanType>(newChanValue / 9));
    }
    return newColor;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorInterpAvg4(double x, double y) {
    double x1 = std::floor(x);
    double y1 = std::floor(y);
    double x2 = std::ceil(x);
    double y2 = std::ceil(y);

    intCrdT x1i = static_cast<intCrdT>(x1);
    intCrdT y1i = static_cast<intCrdT>(y1);
    intCrdT x2i = static_cast<intCrdT>(x2);
    intCrdT y2i = static_cast<intCrdT>(y2);

    if ((x1i >= 0) && (y1i >= 0) && (x2i < numXpix) && (y2i < numYpix)) {

      colorT c1 = pixels[numXpix * y1i + x1i];
      c1.tfrmMean(pixels[numXpix * y1i + x2i]);

      colorT c2 = pixels[numXpix * y2i + x1i];
      c2.tfrmMean(pixels[numXpix * y2i + x2i]);

      c1.tfrmMean(c2);

      return c1;
    } else {
      return colorT().setToBlack();
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointIntType *thePoints, colorT color) {
    drawFillTriangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, thePoints[2].x, thePoints[2].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointFltType *thePoints) {
    drawFillTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                     real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                     real2intX(thePoints[2].x), real2intY(thePoints[2].y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointFltType *thePoints, colorT color) {
    drawFillTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                     real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                     real2intX(thePoints[2].x), real2intY(thePoints[2].y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointIntType *thePoints) {
    drawFillTriangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, thePoints[2].x, thePoints[2].y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointIntType point1, pointIntType point2, pointIntType point3) {
    drawFillTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointFltType point1, pointFltType point2, pointFltType point3) {
    drawFillTriangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), real2intX(point3.x), real2intY(point3.y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointFltType point1, pointFltType point2, pointFltType point3, colorT color) {
    drawFillTriangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), real2intX(point3.x), real2intY(point3.y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(pointIntType point1, pointIntType point2, pointIntType point3, colorT color) {
    drawFillTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3) {
    drawFillTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3, colorT color) {
    drawFillTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3) {
    drawFillTriangle(x1, y1, x2, y2, x3, y3, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::triangleEdger(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, bool minSide, intCrdT* pts) {
    // This code is essentially the line drawing code with some simplifications.
    intCrdT x, y;
    if(x1 == x2) {                                                            // slope = infinity
      if(y1 > y2)                                                             // Fix point ordering
        std::swap(y1, y2);
      for(y=y1; y<=y2; y++)                                                   // Draw PIxels: drawVertLineNC(y1, y2, x1, color);
        if(minSide) { if(x1<pts[y]) pts[y]=x1; } else { if(x1>pts[y]) pts[y]=x1; };
    } else {                                                                  // Slope is not infinity or 0...
      int dx, dy;
      if(x1 > x2) {                                                           // Fix point ordering
        std::swap(x1, x2);
        std::swap(y1, y2);
      }
      dx = x2 - x1;                                                           // Compute the slope
      dy = y2 - y1;
      if(dx == dy) {                                                          // Slope = 1
        for(x=x1,y=y1;x<=x2;y++,x++)                                          // Draw Pixels
          if(minSide) { if(x<pts[y]) pts[y]=x; } else { if(x>pts[y]) pts[y]=x; };
      } else if(dx == -dy) {                                                  // Slope = -1
        for(x=x1,y=y1;x<=x2;y--,x++)                                          // Draw Pixels
          if(minSide) { if(x<pts[y]) pts[y]=x; } else { if(x>pts[y]) pts[y]=x; };
      } else {                                                                // Slope != 1, -1, 0, \infinity
        int s, dx2, dy2;
        dx2 = 2*dx;
        dy2 = 2*dy;
        if(dy > 0) {                                                          // Positive Slope
          if(dx > dy) {                                                       // 0 < Slope < 1
            s = dy2 - dx;
            x=x1;
            y=y1;
            while(x<=x2) {                                                    // Draw Line
              if(minSide) { if(x<pts[y]) pts[y]=x; } else { if(x>pts[y]) pts[y]=x; }
              if(s < 0) {
                s += dy2;
              } else {
                y++;
                s += dy2 - dx2;
              }
              x++;
            }
          } else {                                                            // 1 < Slope < infinity
            s = dy - dx2;
            x=x1;
            y=y1;
            while(y<=y2) {                                                    // Draw Line
              if(minSide) { if(x<pts[y]) pts[y]=x; } else { if(x>pts[y]) pts[y]=x; }
              if(s > 0) {
                s -= dx2;
              } else {
                x++;
                s += dy2 - dx2;
              }
              y++;
            }
          }
        } else {                                                              // Negative Slope
          if(dx > -dy) {                                                      // 0 > Slope > -infinity
            s = dy2 + dx;
            x=x1;
            y=y1;
            while(x<=x2) {                                                    // Draw Line
              if(!isCliped(x, y)) { if(minSide) { if(x<pts[y]) pts[y]=x; } else { if(x>pts[y]) pts[y]=x; } };
              if(s > 0) {
                s += dy2;
              } else {
                y--;
                s += dy2 + dx2;
              }
              x++;
            }
          } else {                                                            // -1 > Slope > -inf
            s = dy + dx2;
            x=x1;
            y=y1;
            while(y>=y2) {                                                    // Draw Line
              if(minSide) { if(x<pts[y]) pts[y]=x; } else { if(x>pts[y]) pts[y]=x; }
              if(s < 0) {
                s += dx2;
              } else {
                x++;
                s += dy2 + dx2;
              }
              y--;
            }
          }
        }
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorT color) {
    drawFillTriangleUtl(x1, y1, x2, y2, x3, y3, color, color, color, true);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3,
                                                           colorT color1, colorT color2, colorT color3) {
    drawFillTriangleUtl(x1, y1, x2, y2, x3, y3, color1, color2, color3, false);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillTriangleUtl(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3,
                                                              colorT c1, colorT c2, colorT c3, bool solid) {
    static intCrdT *minPts, *maxPts;
    static intCrdT  numPts;

    if( !(isCliped(x1, y1) || isCliped(x2, y2) || isCliped(x3, y3))) {
      ///////////////////////////////////////////////////////////////////////////////////
      // Check our work space, and allocate/reallocate as required.
      if(minPts == NULL) {               // First time in function -- allocate
        minPts = new intCrdT[numYpix];
        maxPts = new intCrdT[numYpix];
        numPts = numYpix;
      } else {                           // Not our first time!  We have a work space.
        if(numPts != numYpix) {          // Work space is wrong size -- reallocate
          delete[] minPts;
          delete[] maxPts;
          minPts = new intCrdT[numYpix];
          maxPts = new intCrdT[numYpix];
          numPts = numYpix;
        }
      }

      ///////////////////////////////////////////////////////////////////////////////////
      // Sort (x1,y1), (x2,y2), (x3,y3) so that y1 >= y2, y3 and y3 <= y2, y1
      if(y1 > y2) {             // top != 2 && bot != 1
        if(y1 > y3) {           // top != 3              y1>y2  y1>y3 y2>y3 top bot
          if(y2 > y3) {         //             bot != 2    .      .     .    .   .
                                //                         T      T     T    1   3   NOP
          } else {              //             bot != 3    .      .     .    .   .
            std::swap(y2,y3);   //                         T      T     F    1   2   SWAP(2,3)
            std::swap(x2,x3);   //                         .      .     .    .   .
            std::swap(c2,c3);   //                         .      .     .    .   .
          }                     //                         .      .     .    .   .
        } else {                // top != 1                .      .     .    .   .
          std::swap(y1,y3);     //                         T      F     U    3   2   SWAP(1,3) SWAP(2,3)
          std::swap(y2,y3);     //                         .      .     .    .   .
          std::swap(x1,x3);     //                         .      .     .    .   .
          std::swap(x2,x3);     //                         .      .     .    .   .
          if(!solid) {          //                         .      .     .    .   .
            std::swap(c1,c3);   //                         .      .     .    .   .
            std::swap(c2,c3);   //                         .      .     .    .   .
          }                     //                         .      .     .    .   .
        }                       //                         .      .     .    .   .
      } else {                  // top != 1                .      .     .    .   .
        if(y2 > y3) {           // top != 3 && bot != 2    .      .     .    .   .
          if(y1 > y3) {         //             bot != 1    .      .     .    .   .
            std::swap(y1,y2);   //                         F      T     T    2   3   SWAP(1,2)
            std::swap(x1,x2);   //                         .      .     .    .   .
            std::swap(c1,c2);   //                         .      .     .    .   .
          } else {              //             bot != 3    .      .     .    .   .
            std::swap(y1,y2);   //                         F      F     T    2   1   SWAP(1,2) SWAP(2,3)
            std::swap(y2,y3);   //                         .      .     .    .   .
            std::swap(x1,x2);   //                         .      .     .    .   .
            std::swap(x2,x3);   //                         .      .     .    .   .
            if(!solid) {        //                         .      .     .    .   .
              std::swap(c1,c2); //                         .      .     .    .   .
              std::swap(c2,c3); //                         .      .     .    .   .
            }                   //                         .      .     .    .   .
          }                     //                         .      .     .    .   .
        } else {                // top != 2 && bot != 3    .      .     .    .   .
          std::swap(y1,y3);     //                         F      U     F    3   1   SWAP(1,3)
          std::swap(x1,x3);     //                         .      .     .    .   .
          std::swap(c1,c3);     //                         .      .     .    .   .
        }
      }
      ///////////////////////////////////////////////////////////////////////////////////
      for(intCrdT y=y3; y<=y1; y++) {
        minPts[y] = intCrdGrdMax;
        maxPts[y] = intCrdGrdMin;
      }
      if(y1==y2) {                                           /*       */
        if(x1 == x2) {                                       /*   1   */
          //drawLine(x1, y1, x3, y3, c1);                    /*   |   */
          return;                                            /*   3   */
        } else if(x1 <= x2) {                                /* 1---2 */
          triangleEdger(x1, y1, x3, y3, true,  minPts);      /*  \ /  */
          triangleEdger(x2, y2, x3, y3, false, maxPts);      /*   3   */
        } else {                                             /* 2---1 */
          triangleEdger(x1, y1, x3, y3, false, maxPts);      /*  \ /  */
          triangleEdger(x2, y2, x3, y3, true,  minPts);      /*   3   */
        }                                                    /*       */
      } else if(y2==y3) {                                    /*       */
        if(x2 == x3) {                                       /*   1   */
          //drawLine(x2, y2, x1, y1, c1);                    /*   |   */
          return;                                            /*   3   */
        } else if(x2 <= x3) {                                /*   3   */
          triangleEdger(x2, y2, x1, y1, true,  minPts);      /*  / \  */
          triangleEdger(x3, y3, x1, y1, false, maxPts);      /* 1---2 */
        } else {                                             /*   3   */
          triangleEdger(x2, y2, x1, y1, false, maxPts);      /*  / \  */
          triangleEdger(x3, y3, x1, y1, true,  minPts);      /* 2---1 */
        }
      } else {
        intCrdT xli = (x1*y3-x3*y1+(x3-x1)*y2)/(y3-y1);      /*       */
        if(xli == x2) {                                      /*       */
          //drawLine(x1, y1, x3, y3, c1);                    /*  1    */
          return;                                            /*   \   */
                                                             /*    3  */
        } else if (xli < x2) {                               /*  1    Note: x1 need not equal x3 */
          triangleEdger(x2, y2, x1, y1, false, maxPts);      /*  |\   */
          triangleEdger(x2, y2, x3, y3, false, maxPts);      /*  | 2  */
          triangleEdger(x1, y1, x3, y3, true,  minPts);      /*  |/   */
                                                             /*  3    */
        } else {                                             /*    1  Note: x1 need not equal x3 */
          triangleEdger(x2, y2, x1, y1, true,  minPts);      /*   /|  */
          triangleEdger(x2, y2, x3, y3, true,  minPts);      /*  2 |  */
          triangleEdger(x1, y1, x3, y3, false, maxPts);      /*   \|  */
                                                             /*    3  */
        }
      }
      ///////////////////////////////////////////////////////////////////////////////////
      // Fill between the left and right bits.
      if(solid) {
        for(intCrdT y=y3; y<=y1; y++)
          drawLine(minPts[y], y, maxPts[y], y, c1);
      } else {
        colorChanArithType y12 = (y1 - y2);
        colorChanArithType y31 = (y3 - y1);
        colorChanArithType y23 = (y2 - y3);
        for(intCrdT y=y3; y<=y1; y++) {
          colorChanArithType y03 = (y - y3);
          colorChanArithType y10 = (y1 - y);
          colorChanArithType y30 = (y3 - y);
          colorChanArithType y02 = (y - y2);
          for(intCrdT x=minPts[y]; x<=maxPts[y]; x++) {
            double a  = std::abs(x1 * y23 + x2 * y31 + x3 * y12);
            double w1 = std::abs(x  * y23 + x2 * y30 + x3 * y02) / a;
            double w2 = std::abs(x1 * y03 + x  * y31 + x3 * y10) / a;
            drawPoint(x, y, colorT().wMean(w1, w2, 1-w1-w2, c1, c2, c3));
          }
        }
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y) {
    drawPLCurve(numPoints, x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y, colorT color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(real2intX(x[i]), real2intY(y[i]), real2intX(x[i+1]), real2intY(y[i+1]), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, intCrdT *x, intCrdT *y) {
    drawPLCurve(numPoints, x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, intCrdT *x, intCrdT *y, colorT color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(x[i], y[i], x[i+1], y[i+1], color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, pointIntType *thePoints, colorT color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(thePoints[i].x, thePoints[i].y, thePoints[i+1].x, thePoints[i+1].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, pointFltType *thePoints, colorT color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(thePoints[i].x, thePoints[i].y, thePoints[i+1].x, thePoints[i+1].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, pointIntType *thePoints) {
    drawPLCurve(numPoints, thePoints, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPLCurve(int numPoints, pointFltType *thePoints) {
    drawPLCurve(numPoints, thePoints, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointIntType *thePoints, colorT color) {
    drawTriangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, thePoints[2].x, thePoints[2].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointFltType *thePoints) {
    drawTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                 real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                 real2intX(thePoints[2].x), real2intY(thePoints[2].y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointFltType *thePoints, colorT color) {
    drawTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                 real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                 real2intX(thePoints[2].x), real2intY(thePoints[2].y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointIntType *thePoints) {
    drawTriangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, thePoints[2].x, thePoints[2].y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointIntType point1, pointIntType point2, pointIntType point3) {
    drawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointFltType point1, pointFltType point2, pointFltType point3) {
    drawTriangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), real2intX(point3.x), real2intY(point3.y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointFltType point1, pointFltType point2, pointFltType point3, colorT color) {
    drawTriangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), real2intX(point3.x), real2intY(point3.y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(pointIntType point1, pointIntType point2, pointIntType point3, colorT color) {
    drawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3) {
    drawTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3, colorT color) {
    drawTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3) {
    drawTriangle(x1, y1, x2, y2, x3, y3, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorT color) {
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x3, y3, color);
    drawLine(x3, y3, x1, y1, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(intCrdT radiusX) {
    drawCircle(dfltX, dfltY, radiusX, dfltColor);
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(fltCrdT radiusX) {
    drawCircle(dfltX, dfltY, realDelta2intX(radiusX), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(pointFltType centerPoint, fltCrdT radiusX) {
    drawCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(pointFltType centerPoint, fltCrdT radiusX, colorT color) {
    drawCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(pointIntType centerPoint, intCrdT radiusX) {
    drawCircle(centerPoint.x, centerPoint.y, radiusX, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(pointIntType centerPoint, intCrdT radiusX, colorT color) {
    drawCircle(centerPoint.x, centerPoint.y, radiusX, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX) {
    drawCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX, colorT  color) {
    drawCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX) {
    drawCircle(centerX, centerY, radiusX, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorT  color) {
    int x = 0;
    int y = radiusX;
    int d = 1 - radiusX;
    int deltaE = 3;
    int deltaSE = -2 * radiusX + 5;

    drawPoint( x+centerX, y+centerY, color);
    drawPoint( x+centerX,-y+centerY, color);
    drawPoint(-x+centerX, y+centerY, color);
    drawPoint(-x+centerX,-y+centerY, color);
    drawPoint( y+centerX, x+centerY, color);
    drawPoint( y+centerX,-x+centerY, color);
    drawPoint(-y+centerX, x+centerY, color);
    drawPoint(-y+centerX,-x+centerY, color);

    while(y>x) {
      if(d<0) {
        d += deltaE;
        deltaE += 2;
        deltaSE += 2;
      } else {
        d += deltaSE;
        deltaE += 2;
        deltaSE += 4;
        y--;
      }
      x++;
      drawPoint( x+centerX, y+centerY, color);
      drawPoint( x+centerX,-y+centerY, color);
      drawPoint(-x+centerX, y+centerY, color);
      drawPoint(-x+centerX,-y+centerY, color);
      drawPoint( y+centerX, x+centerY, color);
      drawPoint( y+centerX,-x+centerY, color);
      drawPoint(-y+centerX, x+centerY, color);
      drawPoint(-y+centerX,-x+centerY, color);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(fltCrdT radiusX) {
    drawFillCircle(dfltX, dfltY, realDelta2intX(radiusX), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(intCrdT radiusX) {
    drawFillCircle(dfltX, dfltY, radiusX, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(pointFltType centerPoint, fltCrdT radiusX, colorT color) {
    drawFillCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(pointFltType centerPoint, fltCrdT radiusX) {
    drawFillCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(pointIntType centerPoint, intCrdT radiusX, colorT color) {
    drawFillCircle(centerPoint.x, centerPoint.y, radiusX, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(pointIntType centerPoint, intCrdT radiusX) {
    drawFillCircle(centerPoint.x, centerPoint.y, radiusX, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX) {
    drawFillCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX, colorT  color) {
    drawFillCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX) {
    drawFillCircle(centerX, centerY, radiusX, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorT  color) {
    int minXY;
    int x = 0;
    int y = radiusX;
    int d = 1 - radiusX;
    int deltaE = 3;
    int deltaSE = -2 * radiusX + 5;

    if(x > y)
      minXY = y;
    else
      minXY = x;
    drawLine(  x+centerX,  y+centerY,  x+centerX,  minXY+centerY, color);
    drawLine( -x+centerX,  y+centerY, -x+centerX,  minXY+centerY, color);
    drawLine(  x+centerX, -y+centerY,  x+centerX, -minXY+centerY, color);
    drawLine( -x+centerX, -y+centerY, -x+centerX, -minXY+centerY, color);
    drawLine(  y+centerX,  x+centerY,  minXY+centerX,  x+centerY, color);
    drawLine(  y+centerX, -x+centerY,  minXY+centerX, -x+centerY, color);
    drawLine( -y+centerX,  x+centerY, -minXY+centerX,  x+centerY, color);
    drawLine( -y+centerX, -x+centerY, -minXY+centerX, -x+centerY, color);

    while(y>x) {
      if(d<0) {
        d += deltaE;
        deltaE += 2;
        deltaSE += 2;
      } else {
        d += deltaSE;
        deltaE += 2;
        deltaSE += 4;
        y--;
      }
      x++;

      if(x > y)
        minXY = y;
      else
        minXY = x;
      drawLine(  x+centerX,  y+centerY,  x+centerX,  minXY+centerY, color);
      drawLine( -x+centerX,  y+centerY, -x+centerX,  minXY+centerY, color);
      drawLine(  x+centerX, -y+centerY,  x+centerX, -minXY+centerY, color);
      drawLine( -x+centerX, -y+centerY, -x+centerX, -minXY+centerY, color);
      drawLine(  y+centerX,  x+centerY,  minXY+centerX,  x+centerY, color);
      drawLine(  y+centerX, -x+centerY,  minXY+centerX, -x+centerY, color);
      drawLine( -y+centerX,  x+centerY, -minXY+centerX,  x+centerY, color);
      drawLine( -y+centerX, -x+centerY, -minXY+centerX, -x+centerY, color);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointIntType point1, pointIntType point2, colorT color) {
    drawRectangle(point1.x, point1.y, point2.x, point2.y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointIntType point1, pointIntType point2) {
    drawRectangle(point1.x, point1.y, point2.x, point2.y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointFltType point1, pointFltType point2, colorT color) {
    drawRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointFltType point1, pointFltType point2) {
    drawRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointIntType *thePoints, colorT color) {
    drawRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointFltType *thePoints) {
    drawRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointFltType *thePoints, colorT color) {
    drawRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(pointIntType *thePoints) {
    drawRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2) {
    drawRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorT color) {
    drawRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2) {
    drawRectangle(x1, y1, x2, y2, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorT color) {
    if(x1 > x2) // Get x1 < x2
      std::swap(x1, x2);
    if(y1 > y2) // Get y1 < y2
      std::swap(y1, y2);
    if( (y1 < numYpix) && (x1 < numXpix) && (y2 >= 0) && (x2 >= 0) ) { // Part of rect visible
      int noTop, noBottom, noLeft, noRight;
      if((noTop=(y1 < 0)))
        y1 = 0;
      if((noLeft=(x1 < 0)))
        x1 = 0;
      if((noBottom=(y2 >= numYpix)))
        y2 = numYpix - 1;
      if((noRight=(x2 >= numXpix)))
        x2 = numXpix - 1;
      // Draw top/bottom/left/right lines
      if(!noLeft) // Have left
        drawVertLineNC(y1, y2, x1, color);
      if(!noRight) // Have Right
        drawVertLineNC(y1, y2, x2, color);
      if(!noTop) // Have top
        drawHorzLineNC(x1, x2, y1, color);
      if(!noBottom) // Have bottom
        drawHorzLineNC(x1, x2, y2, color);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointIntType point1, pointIntType point2, colorT color) {
    drawFillRectangle(point1.x, point1.y, point2.x, point2.y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointIntType point1, pointIntType point2) {
    drawFillRectangle(point1.x, point1.y, point2.x, point2.y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointFltType point1, pointFltType point2, colorT color) {
    drawFillRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointFltType point1, pointFltType point2) {
    drawFillRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointIntType *thePoints, colorT color) {
    drawFillRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointFltType *thePoints) {
    drawFillRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointFltType *thePoints, colorT color) {
    drawFillRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(pointIntType *thePoints) {
    drawFillRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2) {
    drawFillRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorT color) {
    drawFillRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2) {
    drawFillRectangle(x1, y1, x2, y2, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawFillRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorT color) {
    if(x1 > x2) // Get x1 < x2
      std::swap(x1, x2);
    if(y1 > y2) // Get y1 < y2
      std::swap(y1, y2);
    // Clip
    if( (y1 >= numYpix) || (x1 >= numXpix) || (y2 < 0) || (x2 < 0) )
      return;
    if(y1 < 0)
      y1 = 0;
    if(x1 < 0)
      x1 = 0;
    if(y2 >= numYpix)
      y2 = numYpix - 1;
    if(x2 >= numXpix)
      x2 = numXpix - 1;
    for(intCrdT y=y1;y<=y2;y++)
      drawHorzLineNC(x1, x2, y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  inline void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPointNC(intCrdT x, intCrdT y, colorT color) {
#if SUPPORT_ALWAYS_PRESERVE_ALPHA
    if(numChan > 3)
      colorChanType aColorComp = pixels[numXpix * y + x].getAlpha();
#endif
#if SUPPORT_DRAWING_MODE
    switch(drawMode) {
      case drawModeType::SET:
        pixels[numXpix * y + x] = color;
        break;
      case drawModeType::XOR:
        pixels[numXpix * y + x].tfrmXor(color);
        break;
      case drawModeType::ADDCLIP:
        pixels[numXpix * y + x].tfrmAddClp(color);
        break;
      case drawModeType::AND:
        pixels[numXpix * y + x].tfrmAnd(color);
        break;
      case drawModeType::OR:
        pixels[numXpix * y + x].tfrmOr(color);
        break;
      case drawModeType::DIFFCLIP:
        pixels[numXpix * y + x].tfrmDiffClp(color);
        break;
      case drawModeType::MULTCLIP:
        pixels[numXpix * y + x].tfrmMultClp(color);
        break;
    }
#else
    pixels[numXpix * y + x] = color;
#endif
#if SUPPORT_ALWAYS_PRESERVE_ALPHA
    if(numChan > 3)
      pixels[numXpix * y + x].setAlpha(aColorComp);
#endif
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  inline colorT&
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorRefNC(intCrdT x, intCrdT y) const {
    return pixels[numXpix * y + x];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  inline colorT
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::getPxColorNC(intCrdT x, intCrdT y) const {
    return pixels[numXpix * y + x];
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  inline void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawHorzLineNC(intCrdT xMin, intCrdT xMax, intCrdT yConst, colorT color) {
    // We could use a memory fill operation here if SUPPORT_ALWAYS_PRESERVE_ALPHA is OFF and SUPPORT_DRAWING_MODE is OFF or set to drawModeType::SET
    // For long line this could be WAY faster.  Just use a memfill-type operation, or even the STD algroithm fill might do that inside...
    // colorT* starti = pixels + numXpix * yConst + xMin;
    // colorT* endi   = pixels + numXpix * yConst + xMax;
    // std::fill(starti, endi, color);

    for(intCrdT x=xMin;x<=xMax;x++)
      drawPointNC(x, yConst, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  inline void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawVertLineNC(intCrdT yMin, intCrdT yMax, intCrdT xConst, colorT color) {
    for(intCrdT y=yMin;y<=yMax;y++)
      drawPointNC(xConst, y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  inline void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawPointS(intCrdT x, intCrdT y, colorT color) {
    pixels[numXpix * y + x] = color;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::scaleUpProximal(int xfactor) {
    intCrdT new_numXpix_p = xfactor*numXpix;
    intCrdT new_numYpix_p = xfactor*numYpix;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];
    for(intCrdT y=0, y1=0; y<numYpix; y++) {
      for(intCrdT x=0, x1=0; x<numXpix; x++) {
        for(int i=0; i<xfactor; i++) {
          for(int j=0; j<xfactor; j++) {
            new_pixels[new_numXpix_p * (y1/*y-crd*/) + (x1/*x-crd*/)] = getPxColor(x, y);
            x1++;
          }
          x1-=xfactor;
          y1++;
        }
        x1+=xfactor;
        y1-=xfactor;
      }
      y1+=xfactor;
    }
    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::scaleDown1pt(int xfactor) {
    intCrdT new_numXpix_p = numXpix/xfactor;
    intCrdT new_numYpix_p = numYpix/xfactor;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];
    for(intCrdT y=0, y1=0; y<new_numYpix_p; y++, y1+=xfactor)
      for(intCrdT x=0, x1=0; x<new_numXpix_p; x++, x1+=xfactor)
        new_pixels[new_numXpix_p * (y/*y-crd*/) + (x/*x-crd*/)] = getPxColor(x1, y1);

    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::scaleDownMean(int xfactor) {
    intCrdT new_numXpix_p = numXpix/xfactor;
    intCrdT new_numYpix_p = numYpix/xfactor;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];
    for(intCrdT y=0, y1=0; y<new_numYpix_p; y++, y1+=xfactor)
      for(intCrdT x=0, x1=0; x<new_numXpix_p; x++, x1+=xfactor) {
        colorChanArithType sumr = 0;
        colorChanArithType sumg = 0;
        colorChanArithType sumb = 0;
        for(int j=0; j<xfactor; j++) {
          for(int i=0; i<xfactor; i++) {
            sumr += getPxColor(x1+i, y1+j).getRed();
            sumg += getPxColor(x1+i, y1+j).getGreen();
            sumb += getPxColor(x1+i, y1+j).getBlue();
          }
        }
        sumr /= (xfactor*xfactor);
        sumg /= (xfactor*xfactor);
        sumb /= (xfactor*xfactor);

        new_pixels[new_numXpix_p * (y/*y-crd*/) + (x/*x-crd*/)] = colorT(static_cast<colorChanType>(sumr),
                                                                         static_cast<colorChanType>(sumg),
                                                                         static_cast<colorChanType>(sumb));
      }

    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::scaleDownMax(int xfactor) {
    intCrdT new_numXpix_p = numXpix/xfactor;
    intCrdT new_numYpix_p = numYpix/xfactor;
    colorT *new_pixels = new colorT[new_numXpix_p * new_numYpix_p];

    for(intCrdT y=0, y1=0; y<new_numYpix_p; y++, y1+=xfactor)
      for(intCrdT x=0, x1=0; x<new_numXpix_p; x++, x1+=xfactor) {
        colorT maxColor = colorT(0,0,0);
        for(int yi=0; yi<xfactor; yi++)
          for(int xi=0; xi<xfactor; xi++)
            maxColor.tfrmMaxI(getPxColor(xfactor*x+xi, xfactor*y+yi));
        new_pixels[new_numXpix_p * (y/*y-crd*/) + (x/*x-crd*/)] = maxColor;
      }

    rePointPixels(new_pixels, new_numXpix_p, new_numYpix_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::computeConvolutionMatrixGausian(double *kernel, int kSize, double sd) {
    for(int yi=0, yis=-(kSize/2); yi<kSize; yi++, yis++)
      for(int xi=0,xis=-(kSize/2); xi<kSize; xi++, xis++)
        kernel[kSize * yi + xi] = exp(-(xis*xis+yis*yis)/(2*sd*sd))/(sd*sd*6.283185307179586477);
    double divisor = 0;
    for(int i=0; i<(kSize*kSize); i++)
      divisor += kernel[i];
    for(int i=0; i<(kSize*kSize); i++)
      kernel[i] /= divisor;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::computeConvolutionMatrixBox(double *kernel, int kSize) {
    for(int yi=0, yis=-(kSize/2); yi<kSize; yi++, yis++)
      for(int xi=0,xis=-(kSize/2); xi<kSize; xi++, xis++)
        kernel[kSize * yi + xi] = 1.0/(kSize*kSize);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::convolution(double *kernel, int kWide, int kTall, double divisor) {
    colorT *new_pixels = new colorT[numXpix * numYpix];
    // Divisor is invalid, so we compute one to use
    if(std::abs(divisor) < 0.0001) {
      divisor = 0.0;
      for(int i=0; i<(kWide*kTall); i++)
        divisor += kernel[i];
    }
    // Apply filter
    double tmp[colorT::channelCount];
    for(intCrdT y=0; y<numYpix; y++) {
      for(intCrdT x=0; x<numXpix; x++) {
        colorT newColor;
        for(int chan=0; chan<colorT::channelCount; chan++)
          tmp[chan] = 0.0;
        for(int yi=0, yis=-(kTall/2); yi<kTall; yi++, yis++) {
          intCrdT icY = y + yis;
          for(int xi=0,xis=-(kWide/2); xi<kWide; xi++, xis++) {
            intCrdT icX = x + xis;
            if (!(isCliped(icX, icY))) {
              for(int chan=0; chan<colorT::channelCount; chan++)
                tmp[chan] += static_cast<double>(getPxColor(icX, icY).getChan(chan)) * kernel[kWide * yi + xi];
            }
          }
        }
        for(int chan=0; chan<colorT::channelCount; chan++)
          new_pixels[numXpix * y + x].setChan(chan, static_cast<colorChanType>(tmp[chan] / divisor));
      }
    }
    rePointPixels(new_pixels, numXpix, numYpix);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::convolution(double *kernel, int kSize, double divisor) {
      convolution(kernel, kSize, kSize, divisor);
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::convolution(double *kernel, int kSize) {
      convolution(kernel, kSize, kSize, 1.0);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawHersheyGlyph(int glyphNum, intCrdT x, intCrdT y, double magX, double magY, colorT aColor) {
    intCrdT x1, y1;
    int actionIsMoveTo;

    if( (glyphNum < 0) || (glyphNum > 3934) )
      glyphNum = 699;

    actionIsMoveTo=1;
    for(int i=0; i<(theHerChars[glyphNum]).numComp; i++) {
      if((theHerChars[glyphNum]).components[2*i] == ' ') {
        actionIsMoveTo = 1;
      } else {
        if(xIntAxOrientation == intAxisOrientation::INVERTED)
          x1 = static_cast<intCrdT>(magX * ('R'  -  (theHerChars[glyphNum]).components[2*i]));
        else
          x1 = static_cast<intCrdT>(magX * ((theHerChars[glyphNum]).components[2*i]  -  'R'));

        if(yIntAxOrientation == intAxisOrientation::NATURAL)
          y1 = static_cast<intCrdT>(magY * ('R' - (theHerChars[glyphNum]).components[2*i+1]));
        else
          y1 = static_cast<intCrdT>(magY * ((theHerChars[glyphNum]).components[2*i+1] - 'R'));

        if(actionIsMoveTo) {
          moveTo(x1+x, y1+y);
          actionIsMoveTo = 0;
        } else {
          drawLine(x1+x, y1+y, aColor);
        }
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawString(std::string aString, hersheyFont aFont, intCrdT x, intCrdT y, colorT aColor, double cex, intCrdT spc) {
    for(auto &c : aString) {
      int glyphNum = 0;
      if((c>=32) && (c<=126))
        glyphNum = hersheyFontAscii[(int)aFont][c-32];
      drawHersheyGlyph(glyphNum, x, y, cex, cex, aColor);
      x+=static_cast<intCrdT>(spc*cex);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  void
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::drawStringBox(std::string aString,
                                                        hersheyFont aFont,
                                                        intCrdT x, intCrdT y,
                                                        colorT stringColor, colorT boxColor,
                                                        double cex, intCrdT spc) {

    drawFillRectangle(static_cast<intCrdT>(x-spc*cex),
                      static_cast<intCrdT>(y-spc*cex),
                      static_cast<intCrdT>(x+spc*cex*static_cast<int>(aString.length())),
                      static_cast<intCrdT>(y+spc*cex),
                      boxColor);
    drawString(aString, aFont, x, y, stringColor, cex, spc);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  int
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::readTIFFfile(std::string fileName) {
#ifndef TIFF_FOUND
    return 32;
#else
    TIFF* tif;
    uint32_t wTIFF, hTIFF;
    uint16_t pmTIFF, pcTIFF, sppTIFF, bpsTIFF;

    // Open our tiff image
    if( !(tif = TIFFOpen(fileName.c_str(), "r")))
      return 1;

    // All these tags are required -- bail if any are missing.
    if( 1 != TIFFGetField(tif, TIFFTAG_IMAGEWIDTH,      &wTIFF))
      return 2;
    if( 1 != TIFFGetField(tif, TIFFTAG_IMAGELENGTH,     &hTIFF))
      return 3;
    if( 1 != TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &sppTIFF))
      return 4;
    if( 1 != TIFFGetField(tif, TIFFTAG_PLANARCONFIG,    &pcTIFF))
      return 5;
    if( 1 != TIFFGetField(tif, TIFFTAG_PHOTOMETRIC,     &pmTIFF))
      return 6;
    if( 1 != TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE,   &bpsTIFF))
      return 7;

    uint64_t cmTIFF = (1ULL << bpsTIFF) - 1ULL;

    // Dump out image metadata
    // std::cerr << "TIFF: "      << fileName << std::endl;
    // std::cerr << " T WIDTH:  " << wTIFF    << std::endl;
    // std::cerr << " T HEIGHT: " << hTIFF    << std::endl;
    // std::cerr << " T SPP:    " << sppTIFF  << std::endl;
    // std::cerr << " T PLNC:   " << pcTIFF   << std::endl;
    // std::cerr << " T PHOM:   " << pmTIFF   << std::endl;
    // std::cerr << " T BPS:    " << bpsTIFF  << std::endl;
    // std::cerr << " T MAX:    " << cmTIFF   << std::endl;

    // Check file image size and reallocate aRamCanvas
    if(wTIFF < 1)
      return 8;

    if(hTIFF < 1)
      return 9;

    resizeCanvas(wTIFF, hTIFF);

    uint32_t wRC   = get_numXpix();

    if(wTIFF != wRC)
      return 12;

    uint32_t hRC   = get_numYpix();

    if(hTIFF != hRC)
      return 14;

    uint16_t sppRC = colorT::channelCount;

    if(sppTIFF != sppRC)
      std::cerr << "WARNING: Converting channel count (from: " << sppTIFF << " to " << sppRC << ") image to RGB: " << fileName << std::endl;

    uint16_t bpsRC = colorT::bitsPerPixel / sppRC;

    if(bpsTIFF != bpsRC)
      std::cerr << "WARNING: Converting image depth (from " << bpsTIFF << "-bit to " << bpsRC << "-bit): " << fileName << std::endl;

    // std::cerr << " C WIDTH:  " << wRC    << std::endl;
    // std::cerr << " C HEIGHT: " << hRC    << std::endl;
    // std::cerr << " C SPP:    " << sppRC  << std::endl;
    // std::cerr << " C BPS:    " << bpsRC  << std::endl;

    bool yNat  = !(get_yIntAxisOrientation()==intAxisOrientation::NATURAL);
    bool xNat  = get_xIntAxisOrientation()==intAxisOrientation::NATURAL;

    // Load the image -- Use TIFFReadRGBAImage if aRamCanvas is 24-bit RGB and TIFFReadScanline otherwise.
    if((sppRC == 3) && (bpsRC == 8)) {
      if(pmTIFF != 2)
        std::cerr << "WARNING: Converting non-RGB image (photometric tag of " << pmTIFF << ") to RGB: " << fileName << std::endl;
      size_t numPix = wTIFF * hTIFF;
      uint32_t* imageBuffer = (uint32_t*)_TIFFmalloc(numPix * sizeof(uint32_t));
      if(imageBuffer == NULL)
        return 10;

      if( !(TIFFReadRGBAImage(tif, wTIFF, hTIFF, imageBuffer, 0)))
        return 11;

      for(int y=(yNat?0:(get_numYpix()-1)); (yNat?y<get_numYpix():y>=0); (yNat?y++:y--)) {
        for(int x=(xNat?0:(get_numXpix()-1)); (xNat?x<get_numXpix():x>=0); (xNat?x++:x--)) {
          drawPointNC(x, y, colorT(TIFFGetR(imageBuffer[y*wTIFF+x]), TIFFGetG(imageBuffer[y*wTIFF+x]), TIFFGetB(imageBuffer[y*wTIFF+x])));
        }
      }
      _TIFFfree(imageBuffer);
    } else {

      if( (bpsTIFF != 8) && (bpsTIFF != 16) && (bpsTIFF != 32) && (bpsTIFF != 64) )
        return 15;

      tsize_t scanlinesize = TIFFScanlineSize(tif);
      tdata_t scanLineBuffer = _TIFFmalloc(scanlinesize);

      if(scanLineBuffer == NULL)
        return 16;

      for(uint32_t row=0; row<hTIFF; row++) {
        if( !(TIFFReadScanline(tif, scanLineBuffer, row)))
          return 17;
        char* p = (char*)(scanLineBuffer);
        for(uint32_t col=0; col<wTIFF; col++) {
          int x = (xNat ? col : wTIFF-col-1);
          int y = (yNat ? row : hTIFF-row-1);
          if(sppTIFF != sppRC)
            getPxColorRefNC(x, y).setToBlack();
          for(uint16_t samp=0; samp<sppTIFF; samp++) {
            uint64_t d;
            switch(bpsTIFF) {
              case 8  : { uint8_t  tmp = *((uint8_t* )p); d = tmp; break; }
              case 16 : { uint16_t tmp = *((uint16_t*)p); d = tmp; break; }
              case 32 : { uint32_t tmp = *((uint32_t*)p); d = tmp; break; }
              case 64 : { uint64_t tmp = *((uint64_t*)p); d = tmp; break; }
              default : {                                 d = 0;   break; }
            }
            if(samp < sppRC) {
              if(bpsTIFF == bpsRC) {
                getPxColorRefNC(x, y).setChan(samp, static_cast<colorChanType>(d));
              } else {
                getPxColorRefNC(x, y).setChan64bit(samp, d, cmTIFF);
              }
            }
            p = p + (bpsTIFF/8);
          }
        }
      }
      _TIFFfree(scanLineBuffer);
    }
    TIFFClose(tif);
    return 0;
#endif
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  bool
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::supportLibTIFF() {
#ifndef TIFF_FOUND
    return true;
#else
    return false;
#endif
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::geomTfrmRevArb(mjr::point2d<double> (*f)(double, double), colorT errorColor, interpolationType interpMethod) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT> newRamCanvas(numXpix, numYpix);
    for(intCrdT y=0; y<numYpix; y++) {
      for(intCrdT x=0; x<numXpix; x++) {
        mjr::point2d<double> fv = f(x, y);
        double xD = fv.x;
        double yD = fv.y;
        if ( (xD < 0) || (yD < 0) || (xD >= numXpix) || (yD >= numYpix) ) {
          newRamCanvas.drawPointNC(x, y, errorColor);
        } else {
          newRamCanvas.drawPointNC(x, y, getPxColorInterpolate(xD, yD, interpMethod));
        }
      }
    }
    return newRamCanvas;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::geomTfrmRevAff(std::vector<double> const& HAMatrix, colorT errorColor, interpolationType interpMethod) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT> newRamCanvas(numXpix, numYpix);
    for(intCrdT y=0; y<numYpix; y++) {
      for(intCrdT x=0; x<numXpix; x++) {
        double xD = HAMatrix[0] * x + HAMatrix[1] * y + HAMatrix[2];
        double yD = HAMatrix[3] * x + HAMatrix[4] * y + HAMatrix[5];
        if ( (xD < 0) || (yD < 0) || (xD >= numXpix) || (yD >= numYpix) ) {
          newRamCanvas.drawPointNC(x, y, errorColor);
        } else {
          newRamCanvas.drawPointNC(x, y, getPxColorInterpolate(xD, yD, interpMethod));
        }
      }
    }
    return newRamCanvas;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class colorT, class intCrdT, class fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>
  ramCanvasTpl<colorT, intCrdT, fltCrdT>::geomTfrmRevRPoly(std::vector<double> const& RPoly,
                                                           double Xo,
                                                           double Yo,
                                                           colorT errorColor,
                                                           interpolationType interpMethod) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT> newRamCanvas(numXpix, numYpix);
    double srcCtrX = numXpix / 2 + Xo;
    double srcCtrY = numYpix / 2 + Yo;
    double rScale  = std::min(numXpix, numYpix) / 2;
    for(intCrdT y=0; y<numYpix; y++) {
      for(intCrdT x=0; x<numXpix; x++) {
        double xU = (x - srcCtrX);
        double yU = (y - srcCtrY);
        double rU = std::hypot(xU, yU) / rScale;
        double rD = RPoly[0];
        for (unsigned int i=1; i<RPoly.size(); i++)
          rD = rD*rU + RPoly[i];
        double xD = xU * rD + srcCtrX;
        double yD = yU * rD + srcCtrY;
        if ( (xD < 0) || (yD < 0) || (xD >= numXpix) || (yD >= numYpix) ) {
          newRamCanvas.drawPointNC(x, y, errorColor);
        } else {
          newRamCanvas.drawPointNC(x, y, getPxColorInterpolate(xD, yD, interpMethod));
        }
      }
    }
    return newRamCanvas;
  }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   template<class colorT, class intCrdT, class fltCrdT>
//   std::vector<double>
//   ramCanvasTpl<colorT, intCrdT, fltCrdT>::homogeneousAffineMatrixMult(std::vector<double> const& HAMatrix1, std::vector<double> const& HAMatrix2) {
//     std::vector<double> matrixProduct(9);
//     for(int i=0;i<3;i++) { // row
//       for(int j=0;j<3;j++) { // col
//         matrixProduct[i*3+j] = 0.0;
//         for(int k=0;k<3;k++) {
//           matrixProduct[i*3+j] += =hamatrix1[i*3+k]*hamatrix2[k*3+j];
//         }
//       }
//     }
//     return matrixProduct;
//   }

} // end namespace mjr

#define MJR_INCLUDE_ramCanvasTpl
#endif

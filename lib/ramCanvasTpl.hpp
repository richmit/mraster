// -*- Mode:C++; Coding:us-ascii-unix; fill-column:158 -*-
/*******************************************************************************************************************************************************.H.S.**/
/**
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
*/
/*******************************************************************************************************************************************************.H.E.**/

#ifndef MJR_INCLUDE_ramCanvasTpl

#ifdef TIFF_FOUND
#include <unistd.h>                                                      /* UNIX std stf            POSIX    */
#include <tiffio.h>                                                      /* libTIFF                 libTIFF  */
#endif

#include <algorithm>                                                     /* STL algorithm           C++11    */
#include <chrono>                                                        /* time                    C++11    */
#include <cmath>                                                         /* std:: C math.h          C++11    */
#include <complex>                                                       /* Complex Numbers         C++11    */
#include <cstdint>                                                       /* std:: C stdint.h        C++11    */
#include <fstream>                                                       /* C++ fstream             C++98    */
#include <functional>                                                    /* STL funcs               C++98    */
#include <iomanip>                                                       /* C++ stream formatting   C++11    */
#include <iostream>                                                      /* C++ iostream            C++11    */
#include <iterator>                                                      /* STL Iterators           C++11    */
#include <list>                                                          /* STL list                C++11    */
#include <map>                                                           /* STL map                 C++11    */
#include <numbers>                                                       /* C++ math constants      C++20    */
#include <random>                                                        /* C++ random numbers      C++11    */
#include <sstream>                                                       /* C++ string stream       C++      */
#include <stdexcept>                                                     /* Exceptions              C++11    */
#include <string>                                                        /* C++ strings             C++11    */
#include <type_traits>                                                   /* C++ metaprogramming     C++11    */
#include <utility>                                                       /* STL Misc Utilities      C++11    */
#include <vector>                                                        /* STL vector              C++11    */ 

#include "color.hpp"
#include "hersheyFont.hpp"
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


                        (0,0)   +------------+ (numPixX-1, 0)
                                |            |
                                |            |
                                |            |
                                |            |
                                |            |
                 (numPixY-1, 0) +------------+ (numPixX-1, numPixY-1)

      ramCanvas Coordinate Systems
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

      @tparam intCrdT An integral type used for the integer image coordinates.  Should be signed, and at least  @f$ 4\cdot\log_2(\mathtt{numPixX} \cdot \mathtt{numPixY}) @f$ bits in size
      @tparam colorT  A type for the image pixels (a color)
      @tparam fltCrdT A floating point type used for the floating point image coordinates
      @tparam enableDrawModes If true, enables drawing modes othe than drawModeType::SET. */
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
  class ramCanvasTpl {
    public:

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Handy ramCanvasTpl converter classes. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This class is an incomplete rcConverter (no getPxColorNC method) that provides a nice base for homogenious rcConverters. */
      template<class inRamCanvasT>
      class rcConverterHomoBase {
        public:
          inRamCanvasT& attachedRC;
          rcConverterHomoBase(inRamCanvasT& aRC) : attachedRC(aRC) {  }
          inline bool isIntAxOrientationNaturalX() { return attachedRC.isIntAxOrientationNaturalX(); }
          inline bool isIntAxOrientationNaturalY() { return attachedRC.isIntAxOrientationNaturalY(); }
          inline typename inRamCanvasT::coordIntType getNumPixX() { return attachedRC.getNumPixX(); }
          inline typename inRamCanvasT::coordIntType getNumPixY() { return attachedRC.getNumPixY(); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      template<class inRamCanvasT>
      class rcConverterIdentity : public rcConverterHomoBase<inRamCanvasT>  {
        public:
          rcConverterIdentity(inRamCanvasT& aRC) : rcConverterHomoBase<inRamCanvasT>(aRC) {  }
          typedef typename inRamCanvasT::colorType colorType;
          inline colorType getPxColorNC(typename inRamCanvasT::coordIntType x, typename inRamCanvasT::coordIntType y) { return rcConverterHomoBase<inRamCanvasT>::attachedRC.getPxColorNC(x, y); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      template<class inRamCanvasT>
      class rcConverterRGBbyte : public rcConverterHomoBase<inRamCanvasT>  {
        public:
          rcConverterRGBbyte(inRamCanvasT& aRC) : rcConverterHomoBase<inRamCanvasT>(aRC) {  }
          typedef typename inRamCanvasT::colorType::colConRGBbyte colorType;
          inline colorType getPxColorNC(typename inRamCanvasT::coordIntType x, typename inRamCanvasT::coordIntType y) { return rcConverterHomoBase<inRamCanvasT>::attachedRC.getPxColorNC(x, y).getColConRGB_byte(); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      template<class inRamCanvasT>
      class rcConverterRGBAbyte {
        public:
          rcConverterRGBAbyte(inRamCanvasT& aRC) : rcConverterHomoBase<inRamCanvasT>(aRC) {  }
          typedef typename inRamCanvasT::colorType::colConRGBAbyte colorType;
          inline colorType getPxColorNC(typename inRamCanvasT::coordIntType x, typename inRamCanvasT::coordIntType y) { return rcConverterHomoBase<inRamCanvasT>::attachedRC.getPxColorNC(x, y).getColConRGBA_byte(); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      template<class inRamCanvasT>
      class rcConverterRGBdbl {
        public:
          rcConverterRGBdbl(inRamCanvasT& aRC) : rcConverterHomoBase<inRamCanvasT>(aRC) {  }
          typedef typename inRamCanvasT::colorType::colConRGBdbl colorType;
          inline colorType getPxColorNC(typename inRamCanvasT::coordIntType x, typename inRamCanvasT::coordIntType y) { return rcConverterHomoBase<inRamCanvasT>::attachedRC.getPxColorNC(x, y).getColConRGB_dbl(); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      template<class inRamCanvasT>
      class rcConverterRGBAdbl {
        public:
          rcConverterRGBAdbl(inRamCanvasT& aRC) : rcConverterHomoBase<inRamCanvasT>(aRC) {  }
          typedef typename inRamCanvasT::colorType::colConRGBAdbl colorType;
          inline colorType getPxColorNC(typename inRamCanvasT::coordIntType x, typename inRamCanvasT::coordIntType y) { return rcConverterHomoBase<inRamCanvasT>::attachedRC.getPxColorNC(x, y).getColConRGBA_dbl(); }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Colorize a ramCanvasTpl with integer channels using a color scheme. */
      template<class inRamCanvasT, class outColorT, class colorScheme, bool clamp, int factor, int chan>
      class rcConverterColorScheme : public rcConverterHomoBase<inRamCanvasT>  {
        public:
          rcConverterColorScheme(inRamCanvasT& aRC) : rcConverterHomoBase<inRamCanvasT>(aRC) {  }
          typedef outColorT colorType;
          inline colorType getPxColorNC(typename inRamCanvasT::coordIntType x, typename inRamCanvasT::coordIntType y) { 
            typename outColorT::csIntType csi = static_cast<typename outColorT::csIntType>(rcConverterHomoBase<inRamCanvasT>::attachedRC.getPxColorNC(x, y).getChan(chan) * factor);
            if (clamp)
              csi = mjr::intClamp(csi, colorScheme::numC-1);
            return colorScheme::c(csi); 
          }
      };
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert a ramCanvasTpl to a greyscale image using colorT::intensity(). */
      template<class inRamCanvasT, class outColorChanT>
      class rcConverterMonoIntensity : public rcConverterHomoBase<inRamCanvasT>  {
        public:
          rcConverterMonoIntensity(inRamCanvasT& aRC) : rcConverterHomoBase<inRamCanvasT>(aRC) {  }
          typedef colorTpl<outColorChanT, 1> colorType;
          inline colorType getPxColorNC(typename inRamCanvasT::coordIntType x, typename inRamCanvasT::coordIntType y) { 
            return static_cast<outColorChanT>(rcConverterHomoBase<inRamCanvasT>::attachedRC.getPxColorNC(x, y).intensity());
          }
      };
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Typedefs related to template parameters */
      //@{
      typedef point2d<fltCrdT>      pointFltType; //!< Real coordinate pair type
      typedef point2d<intCrdT>      pointIntType; //!< Integer coordinate pair type
      typedef std::complex<fltCrdT> cplxFltType;  //!< Real coordinate complex type (Provided for convince -- not used in ramCanvasTpl)
      typedef std::complex<intCrdT> cplxIntType;  //!< Integer coordinate complex type (Provided for convince -- not used in ramCanvasTpl)
      typedef intCrdT               coordIntType; //!< Integer type for coordinates
      typedef fltCrdT               coordFltType; //!< Real type for coordinates
      typedef colorT                colorType;    //!< Color type for pixels
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Typedefs related to colorT */
      //@{
      typedef typename colorT::channelType          colorChanType;           //!< colorT: Channel type
      typedef typename colorT::maskType             colorMaskType;           //!< colorT: Mask type
      typedef typename colorT::channelArithDType    colorChanArithDType;     //!< colorT: Channel arithmatic (Int: -)
      typedef typename colorT::channelArithSPType   colorChanArithSPType;    //!< colorT: Channel arithmatic (Int: +*)
      typedef typename colorT::channelArithSDPType  colorChanArithSDPType;   //!< colorT: Channel arithmatic (Int: +-*)
      typedef typename colorT::channelArithFltType  colorChanArithFltType;   //!< colorT: Channel arithmatic (Flt: +-*)
      typedef typename colorT::channelArithLogType  colorChanArithLogType;   //!< colorT: Channel arithmatic (Int: ^|&~)
      typedef typename colorT::colorSpaceEnum       colorSpaceEnum;          //!< colorT: Color spaces
      typedef typename colorT::cornerColorEnum      colorCornerEnum;         //!< colorT: RGB Color Corners
      typedef typename colorT::colorArgType         colorArgType;            //!< colorT: Argument passing type
      typedef typename colorT::colorPtrType         colorPtrType;            //!< colorT: Pointer to color
      typedef typename colorT::colorRefType         colorRefType;            //!< colorT: Ref to a color
      typedef typename colorT::colorCRefType        colorCRefType;           //!< colorT: Const Ref to a color
      typedef typename colorT::csIntType            csIntType;               //!< colorT: Color Scheme Integer Type
      typedef typename colorT::csFltType            csFltType;               //!< colorT: Color Scheme Float Type
      typedef typename colorT::csNatType            csNatType;               //!< colorT: Color Scheme Natural Type
      typedef typename colorT::cmfInterpolationEnum cmfInterpolationEnum;    //!< colorT: Interpolation for color match functions
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Iterator Typedefs */
      //@{
      typedef colorT* pixelIterator; //!< pixel store iterators
      typedef colorT* iterator;      //!< pixel store iterators
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Enumerations */
      //@{
      /** Enum for real axis orientation */
      enum class realAxisOrientation { INVERTED,  //!< Real axis is inverted with respect to the integer axis
                                       NATURAL    //!< Real axis is not inverted with respect to the integer axis
      };

      /** Enum for integer axis orientation.

       Note integer axis orientation has no impact on the in-ram representation of the image.  i.e. Pixel (0,0) will always be the first element of the pixels
       array.  The integer axis orientation is used to arrange the pixels when a canvas is saved/loaded to/from an image file. */
      enum class intAxisOrientation  { INVERTED,  //!< Zero is to the right or bottom
                                       NATURAL    //!< Zero is to the left or top
      };

      /** Enum for drawing Mode */
      enum class drawModeType { SET,       //!< Simply set the pixel value to the new value
                                XOR,       //!< See: tfrmXor()
                                ADDCLAMP,  //!< See: tfrmAddClamp()
                                AND,       //!< See: tfrmAnd()
                                OR,        //!< See: tfrmOr()
                                DIFFCLAMP, //!< See: tfrmDiffClamp()
                                MULTCLAMP  //!< See: tfrmMultClamp()
      };

      /** Enum for drawing Mode */
      enum class interpolationType { BILINEAR, //!< bilinear
                                     TRUNCATE, //!< Coordinates are truncated (fractional bits chopped off)
                                     NEAREST,  //!< Coordinates are rounded
                                     AVERAGE4, //!< Average of four sourounding pixels
                                     AVERAGE9  //!< Average of 9 sourounding pixels
                                   };

      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Logical Maximum for intCrdT values */
      //@{
      const static intCrdT intCrdMax = (1ul << ((sizeof(intCrdT)*CHAR_BIT-1)/2)) - 3;        //!< maximum ro numPixX, numPixY, & numPix.
      //@}

    private:

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Private Enumerations */
      //@{
      /** Endianness Identifiers. */
      enum class endianType {
        BIG,     //!< PowerPC
        LITTLE,  //!< Intel
        AUTO     //!< Whatever the platform uses
      };
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name intCrd Guard Valus */
      //@{
      const static intCrdT intCrdGrdMax = intCrdMax+1; //!< Large sentinel value (always off canvas)
      const static intCrdT intCrdGrdMin = -1;          //!< Small sentinel value (always off canvas)
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas integer coordinates */
      //@{
      intCrdT numPixX;  //!< Number of x pixels
      intCrdT numPixY;  //!< Number of y pixels
      intCrdT numPix;   //!< Number of pixels
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas real coordinates */
      //@{
      fltCrdT minRealX; //!< x coord of min (real coord)
      fltCrdT maxRealX; //!< x coord of max (real coord)
      fltCrdT minRealY; //!< y coord of min (real coord)
      fltCrdT maxRealY; //!< y coord of max (real coord)
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas real/integer coordinates conversion */
      //@{
      fltCrdT pixWidX;    //!< Width of a pixel (real coord)
      fltCrdT pixWidY;    //!< Height of a pixel (real coord)

      fltCrdT canvasWidX; //!< Width of the canvas (real coord)
      fltCrdT canvasWidY; //!< height of the canvas (real coord)
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Axis orientation */
      //@{
      realAxisOrientation realAxOrientationX; //!< Orientation of x axis
      realAxisOrientation realAxOrientationY; //!< Orientation of y axis
      intAxisOrientation  intAxOrientationX;  //!< Flip horizontally
      intAxisOrientation  intAxOrientationY;  //!< Flip vertically
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas pixel store pointers */
      //@{
      colorT *pixels;  //!< Array to hold the color values.
      colorT *pixelsE; //!< Point one beyond end of pixels array.
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Drawing defaults */
      //@{
      colorT       dfltColor; //!< Default color.
      drawModeType drawMode;  //!< Drawing mode.
      intCrdT      dfltX;     //!< x coordinate used by default.
      intCrdT      dfltY;     //!< y coordinate used by default.
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Filled Triangle Utility Functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Utliity function behind the drawFillTriangle() functions.
          @bug Not thread safe
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
      void drawFillTriangleUtl(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorT c1, colorT c2, colorT c3, bool solid);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name File Writing Utility Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Write an unsigned integer to a stream with given length and endianness.
          @param oStream    The ostream object to which to write
          @param endianness The endianness to use for the integer.
          @param numBytes   The number of bytes of the data parameter to use (logically the least significant bits)
          @param data       The integer to write */
      void writeUIntToStream(std::ostream& oStream, endianType endianness, int numBytes, uint64_t data);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Determine the platform's endianness. */
      endianType platformEndianness();
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Coordinate System Manipulation (i) */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Several internal parameters are maintained within this class that make conversion between real coordinates and integer coordinate very fast.  This
          function will update the internal parameters if the real coordinate sizes or the integer coordinate sizes have changed.  This function is intended for
          internal use. An example of when to use this function is right after the integer coordinate axes have changed via a call to newIntCoordsNC(). */
      void updRealCoords();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Change the logical coordinate sizes.
          It is important that the specified coordinate sizes describe an image with FEWER pixels than the previous sizes.  This function will NOT allocate a
          new pixel array, so the previous array contents will be interpreted as valid data -- just at different coordinates.  This function causes no memory
          leaks.  This function will NOT update the internal parameters related to real coordinate systems and so updRealCoords() should be called after this
          function in most cases.  This function is intended for internal use and provides no safety checks.
          @param numPixX_p The width of the new canvas
          @param numPixY_p The height of the new canvas */
      void newIntCoordsNC(intCrdT numPixX_p, intCrdT numPixY_p);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Plane Manipulation Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Destroy the current pixel memory and reallocate a new pixel space of the given size.
          This will not clear the canvas.  IT will not reallocate the canvas unless the new size is different from the current size.  It will not allocate a
          new canvas if either argument is zero or less.  Updates coordinates.
          @param numPixX_p The width of the new canvas
          @param numPixY_p The height of the new canvas */
      void reallocCanvas(intCrdT numPixX_p, intCrdT numPixY_p);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Free the pixel memory (i) */
      void freeCanvas();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Points the pixels pointer at a new pixel store, and updates coordinates.  Pixels pointer not changed if new_pixels is NULL */
      void rePointPixels(colorT *new_pixels, intCrdT new_numPixX, intCrdT new_numPixY);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Various helper functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Used to find the left and right edges of a triangle. */
      void triangleEdger(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT* pts, bool findMin);
      //@}

    public:

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Raster Data Import And Export. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
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

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Constructors & Assignment Operators */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** No arg constructor.  Sets numPixX and numPixY to -1, and pixels to NULL. */
      ramCanvasTpl();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Copy constructor */
      ramCanvasTpl(const ramCanvasTpl &theCanvas);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Most commonly used constructor.
          The real coordinates have default values with -1 as the min values and 1 used as the max values.
          @param numPixX_p   Number of pixels in the X direction
          @param numPixY_p   Number of pixels in the Y direction
          @param minRealX_p  Minimum real x coordinate value
          @param maxRealX_p  Maximum real x coordinate value
          @param minRealY_p  Minimum real y coordinate value
          @param maxRealY_p  Maximum real y coordinate value */
      ramCanvasTpl(intCrdT numPixX_p, intCrdT numPixY_p, fltCrdT minRealX_p=-1, fltCrdT maxRealX_p=1, fltCrdT minRealY_p=-1, fltCrdT maxRealY_p=1);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Move constructor */
      ramCanvasTpl(ramCanvasTpl&& theCanvas);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Move assignment operator */
      ramCanvasTpl& operator=(ramCanvasTpl&& theCanvas);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Destructor */
      //@{
      /** Destructor deallocates memory for the canvas. */
      ~ramCanvasTpl();
      //@}


      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas Compositing

          @warning These functions are experimental!  Functionality and API are likely to change in the future.

      */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Adjoin the canvas to the side of the current canvas.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param theCanvas The canvas to adjoin. */
      void adjoinCanvasRight(const ramCanvasTpl &theCanvas) { 
        intCrdT origNumPixX = getNumPixX(); 
        expandCanvas(origNumPixX + theCanvas.getNumPixX(), std::max(getNumPixY(), theCanvas.getNumPixY())); 
        insertCanvas(theCanvas, origNumPixX);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Adjoin the canvas to the side of the current canvas.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param theCanvas The canvas to adjoin. */
      void adjoinCanvasLeft(const ramCanvasTpl &theCanvas) {
        intCrdT origNumPixX = getNumPixX();
        expandCanvas(origNumPixX + theCanvas.getNumPixX(), std::max(getNumPixY(), theCanvas.getNumPixY()), origNumPixX);
        insertCanvas(theCanvas);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Adjoin the canvas to the side of the current canvas.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param theCanvas The canvas to adjoin. */
      void adjoinCanvasBottom(const ramCanvasTpl &theCanvas) {
        intCrdT origNumPixY = getNumPixY();
        expandCanvas(std::max(getNumPixX(), theCanvas.getNumPixX()), origNumPixY + theCanvas.getNumPixY(), 0, origNumPixY);
        insertCanvas(theCanvas, 0, 0);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Adjoin the canvas to the side of the current canvas.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param theCanvas The canvas to adjoin. */
      void adjoinCanvasTop(const ramCanvasTpl &theCanvas) {
        intCrdT origNumPixY = getNumPixY();
        expandCanvas(std::max(getNumPixX(), theCanvas.getNumPixX()), origNumPixY + theCanvas.getNumPixY());
        insertCanvas(theCanvas, 0, origNumPixY);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw the given canvas at the indicated point.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param theCanvas The canvas to draw on the current canvas.
          @param x1        X coordinate at which to place the canvas.
          @param y1        Y coordinate at which to place the canvas. */
      void insertCanvas(const ramCanvasTpl &theCanvas, intCrdT x1 = 0, intCrdT y1 = 0) {
        for(intCrdT y=0; y<theCanvas.getNumPixY(); y++)
          for(intCrdT x=0; x<theCanvas.getNumPixX(); x++)
            drawPoint(x1+x, y1+y, theCanvas.getPxColorRefNC(x, y));
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas resize and crop */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Resize the canvas to the  given size.
          Contents of new canvas may be random data.  Not guarnteed to reallocate the canvas.
          @param new_numPixX_p The width of the new canvas
          @param new_numPixY_p The height of the new canvas */
      void resizeCanvas(intCrdT new_numPixX_p, intCrdT new_numPixY_p);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Expand the current canvas.
          The current image will appear within the new canvas at the specified location.  All pixels not set by the previous image
          will be set to the given color.
          @param new_numPixX_p The width of the new canvas
          @param new_numPixY_p The height of the new canvas
          @param x1            Coord at which the left of the old image will appear in the new image
          @param y1            Coord at which the top of the old image will appear in the new image
          @param color         Color to use for the background of the new image. */
      void expandCanvas(intCrdT new_numPixX_p, intCrdT new_numPixY_p, intCrdT x1 = 0, intCrdT y1 = 0, colorArgType color = colorT(colorT::minChanVal));
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This function will crop the canvas to the given rectangular region.
          @param x1 Left, or right, edge of region to keep.
          @param x2 Right, or left, edge of region to keep.
          @param y1 Left, or right, edge of region to keep.
          @param y2 Right, or left, edge of region to keep. */
      void cropCanvas(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Coordinate System Manipulation */
      //@{
      /** Change the real coordinate system associated with a canvas.
          It updates all internal parameters are required.
          @param minRealX_p  Minimum real x coordinate value
          @param maxRealX_p  Maximum real x coordinate value
          @param minRealY_p  Minimum real y coordinate value
          @param maxRealY_p  Maximum real y coordinate value */
      void newRealCoords(fltCrdT minRealX_p, fltCrdT maxRealX_p, fltCrdT minRealY_p, fltCrdT maxRealY_p);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas comparison */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Return true if given canvas and current canvas are the same size. */
      inline bool isSameSize(ramCanvasTpl const & inRC) const { 
        if ((numPixY == inRC.getNumPixY()) && (numPixX == inRC.getNumPixX())) 
          return true;
        else 
          return false;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Return true if given canvas and current canvas are *NOT* the same size. */
      inline bool isNotSameSize(ramCanvasTpl const & inRC) const { 
        if ((numPixY == inRC.getNumPixY()) && (numPixX == inRC.getNumPixX())) 
          return false;
        else 
          return true;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Return true if corresponding pixels in each canvas are "close" as defined by colorTpl::isClose(). */
      inline bool isClose(ramCanvasTpl const & inRC, colorChanType epsilon) const { 
        if (isNotSameSize(inRC))
          return false;
        for(intCrdT y=0; y<numPixY; y++)
          for(intCrdT x=0; x<numPixX; x++)
            if ( !(getPxColorRefNC(x, y).isClose(inRC.getPxColorRefNC(x, y), epsilon)))
              return false;
        return true;
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Return true if corresponding pixels in each canvas are "equal" as defined by colorTpl::isEqual(). */
      inline bool isEqual(ramCanvasTpl const & inRC) const { 
        if (isNotSameSize(inRC))
          return false;
        for(intCrdT y=0; y<numPixY; y++)
          for(intCrdT x=0; x<numPixX; x++)
            if ( !(getPxColorRefNC(x, y).isEqual(inRC.getPxColorRefNC(x, y))))
              return false;
        return true;
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas Rotation and Reflection. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Loss-less 90 degree clockwise rotation of the canvas about the center.
          The top row of pixels will be on the right side after the rotation.  The canvas will be resized as required.  The transformation is not done
          "in place", so enough memory is required to duplicate the canvas.  */
      void rotate90CW();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Loss-less 90 degree counter clockwise rotation of the canvas about the center.
          The top row of pixels will be on the left side after the rotation.  The canvas will be resized as required.  The transformation is not done "in
          place", so enough memory is required to duplicate the canvas. */
      void rotate90CCW();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Loss-less 180 degree rotation of the canvas about the center.
          The top row of pixels will be on the bottom side after the rotation.  The transformation is not done "in place", so enough memory is required to
          duplicate the canvas.  */
      void rotate180();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Loss-less, horizontal flip of the canvas about the center.
          The top row of pixels will be on the bottom side after the flip.  The transformation is done "in place" so no extra RAM is required. */
      void flipHorz();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Loss-less, vertical flip of the canvas about the center.
          The left row of pixels will be on the right side after the flip.  The transformation is done "in place" so no extra RAM is required. */
      void flipVert();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Loss-less, vertical flip of the canvas about the center.
          The top row of pixels will be on the left side after the flip, and pixel (x,y) will be in position (y,x).  The canvas will be resized as required.
          The transformation is not done "in place", so enough memory is required to duplicate the canvas.  */
      void flipTranspose();
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas Scaling. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Scale up the image using proximal interpolation.
          For each source pixel we create an xfactor*xfactor box filled with the color of the original pixel.  The resulting images are block, but the
          histograms stay accurate.  The algorithm is very fast as it is very simple.
          @param xfactor The factor to scale up to -- must be a positive integer. */
      void scaleUpProximal(int xfactor);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Scale down using only the upper left pixel from each block.
          This will tend to highlight horizontal and vertical detail and generally sharpen up the image.  Much data is lost with this sort of scaling
          operation.
          @param xfactor The factor to scale up to -- must be a positive integer. */
      void scaleDown1pt(int xfactor);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Scale down using only the pixel with maximum luminosity in each block.
          Much like scaleDown1pt(), this will sharpen up a scaled image, but it will also tend to brighten up the image as well.
          @param xfactor The factor to scale up to -- must be a positive integer. */
      void scaleDownMax(int xfactor);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Scale down using the mean pixel value from each block.
          This creates each pixel value by averaging all of the pixels that contribute -- i.e. a mean on the xfactor*xfactor pixel corresponding to each new
          pixel.  This algorithm tends to "fuzz-up" the result -- frequently used for super-sampling.
          @param xfactor The factor to scale down to -- must be a positive integer. */
      void scaleDownMean(int xfactor);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Geometric transformations (Reverse Mapping)

          @warning These functions are experimental!  Functionality and API are likely to change in the future.
      */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Geometric Transform via Radial Polynomial implemented with Reverse Mapping.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param RPoly        RPoly is a vector listing the coefficients of a univariate polynomial in lexicographical order -- 
                              i.e. RPoly[0] is the coefficients on the highest power term.
          @param rScale       Scale to apply before the transformation to the *radius*.
          @param Xo           X coordinate for origin translation -- applied before RPoly and reversed after RPoly & scale.
          @param Yo           Y coordinate for origin translation -- applied before RPoly and reversed after RPoly & scale.
          @param oScale       Scale to apply after RPoly and before reverse translation.
          @param errorColor   The color to use for pixels with no valid mapping.
          @param interpMethod Eventually this will be the interpolation method used. */
      ramCanvasTpl geomTfrmRevRPoly(std::vector<double> const& RPoly,
                                    double rScale,
                                    double Xo,
                                    double Yo,
                                    double oScale,
                                    colorArgType errorColor = colorCornerEnum::GREEN,
                                    interpolationType interpMethod = interpolationType::BILINEAR);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Geometric Transform via bivariate polynomial implemented with Reverse Mapping.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param BiPolyX      Coefficients for a bivariate polynomial in lexicographical order -- used to map x coordinates.
          @param BiPolyY      Coefficients for a bivariate polynomial in lexicographical order -- used to map y coordinates.
          @param Xo           X coordinate for origin translation -- applied before BiPoly*and reversed after BiPoly*& scale.
          @param Yo           Y coordinate for origin translation -- applied before BiPoly*and reversed after BiPoly*& scale.
          @param oScale       Scale to apply after BiPoly*and before reverse translation.
          @param errorColor   The color to use for pixels with no valid mapping.
          @param interpMethod Eventually this will be the interpolation method used. */
      ramCanvasTpl geomTfrmRevBiPoly(std::vector<double> const& BiPolyX,
                                     std::vector<double> const& BiPolyY,
                                     double Xo,
                                     double Yo,
                                     double oScale,
                                     colorArgType errorColor = colorCornerEnum::GREEN,
                                     interpolationType interpMethod = interpolationType::BILINEAR);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Homogenious Affine Geometric Transform implemented with Reverse Mapping.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

           @verbatim
           [1 0 T_x]   [S_x 0   0]   [cA  sA 0]             [x_in]    [x_out]
           [0 1 T_y]   [0   S_y 0]   [-SA cA 0]         T * [y_in] => [y_out]
           [0 0 1  ]   [0   0   1]   [0   0  1]             [1   ]    [1    ]
           @endverbatim
          @param HAMatrix     Homogeneous affine transform matrix -- 9 elements interpreted as a row major order 3x3 matrix.
          @param Xo           X coordinate for origin translation -- applied before HAMatrixand reversed after HAMatrix& scale.
          @param Yo           Y coordinate for origin translation -- applied before HAMatrixand reversed after HAMatrix& scale.
          @param oScale       Scale to apply after HAMatrixand before reverse translation.
          @param errorColor   The color to use for pixels with no valid mapping.
          @param interpMethod Eventually this will be the interpolation method used. */
      ramCanvasTpl geomTfrmRevAff(std::vector<double> const& HAMatrix,
                                  double Xo,
                                  double Yo,
                                  double oScale,
                                  colorArgType errorColor = colorCornerEnum::GREEN,
                                  interpolationType interpMethod = interpolationType::BILINEAR);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Geometric Transform via provided mapping function implemented with Reverse Mapping.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param f            The coordinate transformation function 
          @param Xo           X coordinate for origin translation -- applied before f and reversed after f & scale.
          @param Yo           Y coordinate for origin translation -- applied before f and reversed after f & scale.
          @param oScale       Scale to apply after f and before reverse translation.
          @param errorColor   The color to use for pixels with no valid mapping.
          @param interpMethod Eventually this will be the interpolation method used. */
      ramCanvasTpl geomTfrmRevArb(mjr::point2d<double> (*f)(double, double),
                                  double Xo,
                                  double Yo,
                                  double oScale,
                                  colorArgType errorColor = colorCornerEnum::GREEN,
                                  interpolationType interpMethod = interpolationType::BILINEAR);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Apply Convolution */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Apply a convolution filter.
          The implementation for this method is quite naive and super slow!  Frankly, this kind of functionality is beyond the scope of this library; however,
          sometimes you just need a convolution filter and you don't want to go to the extra effort of using yet another external library.  Pixels outside the
          canvas are considered black.
          @param kernel  The convolution kernel.   Must be of length kWide*kTall.
          @param kWide   The width of the kernel.  Must be odd.
          @param kTall   The height of the kernel. Must be odd.
          @param divisor Used to normalize dot product at each step.  i.e. one might say the kernel for the convolution is really kernel/divisor. */
      void convolution(double *kernel, int kWide, int kTall, double divisor);
      void convolution(double *kernel, int kSize, double divisor);
      void convolution(double *kernel, int kSize);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Compute Convolution Kernels */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute a Gaussian convolution kernel (use with divisor==1.0).
          @param kernel  Pointer to space for the convolution kernel.   Must have at least space for kSize*kSize doubles
          @param kSize   The width and height of the kernel.  Must be odd.
          @param sd      The standard deviation. */
      void computeConvolutionMatrixGausian(double *kernel, int kSize, double sd);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Compute a box blur convolution kernel (use with divisor==1.0).
          @param kernel  Pointer to space for the convolution kernel.   Must have at least space for kSize*kSize doubles
          @param kSize   The width and height of the kernel.  Must be odd. */
      void computeConvolutionMatrixBox(double *kernel, int kSize);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Iterators */
      //@{
      colorT *begin() { return pixels;  }
      colorT *end()   { return pixelsE; }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Functional Homogeneous Pixel Transformations (point operators) */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Apply a homogeneous pixel transformation.
          Homogeneous pixel transformations don't vary based upon the coordinates of the pixel in question, but depend only upon the value of the pixel.
          Thus, a homogeneous pixel transformation can be considered as a pixel function applied to each pixel in an image.  Many standard pixel functions are
          defined within the colorT object.  The ramCanvasTpl object must then only apply the methods available within each colorT class to support most of
          the standard homogeneous pixel transformations.  Additionally, new functions are automatically available to the ramCanvasTpl (both in the colorT
          class and new functions from other sources). */
      void applyHomoPixTfrm(colorT& (colorT::*HPT)());
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double),                                          double);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double),                                  double, double);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double),                          double, double, double);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double),                  double, double, double, double);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double),          double, double, double, double, double);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double, double),  double, double, double, double, double, double);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int),                 int);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int),            int, int);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int),       int, int, int);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int, int),  int, int, int, int);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT),                          colorT);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT),                  colorT, colorT);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT),          colorT, colorT, colorT);
      void applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT, colorT),  colorT, colorT, colorT, colorT);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Predefined Homogeneous Pixel Transformations (point operators) */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes a linear grey level scale homogeneous pixel transformation.
          f(c)=(c-cmin)*maxChanVal/(cmax-cmin) where cmin is the lowest integer value assumed by any pixel color component and cmax is the largest integer value
          assumed by any pixel color component.  This function is sometimes called "auto contrast adjust" or "linear auto contrast adjust". */
      void autoHistStrech();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Computes a, possibly different, linear grey level scale homogeneous pixel transformation on each channel of the image.
          Channel n is transformed such that f_n(c)=(c-cmin_n)*maxChanVal/(cmax_n-cmin_n) where cmin_n and cmax_n are the minimum and maximum values in channel n.
          i.e. this is the same as applying autoHistStrech independently to each channel.*/
      void autoMaxHistStrechRGB();
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas Combination Functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** This function takes a ramCanvasTpl and combines it with the current ramCanvasTpl using the provided binary operator.
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

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Statistical Canvas Combination Functions (useful for CCD imaging) */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Take a list of ramCanvasTpl objects and combine them with the current ramCanvasTpl using mean.
          @param theCanvasList This is the array of ramCanvasTpl's to combine with.
          @param N The number of canvas objects. */
      void combineRamCanvasMean(ramCanvasTpl *theCanvasList, const int N);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas Clearing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clear the canvas to black.  Faster than clrCanvas().  */
      void clrCanvasToBlack();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clear the canvas to black.  Faster than clrCanvas().  */
      void clrCanvasToWhite();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the given channel to the minimum value. */
      void clrCanvasChannelToMin(int chan);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the given channel to the maximum value. */
      void clrCanvasChannelToMax(int chan);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Clear the canvas.   */
      void clrCanvas();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @overload */
      void clrCanvas(colorArgType color);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Default Point Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the current default point to the given coordinates.
          @param x The x coordinate of the point to move to.
          @param y The y coordinate of the point to move to. */
      inline void moveTo(intCrdT x, intCrdT y)  { dfltX = x; dfltY = y; }
      inline void moveTo(fltCrdT x, fltCrdT y)  { moveTo(real2intX(x), real2intY(y)); }
      inline void moveTo(pointIntType thePoint) { moveTo(thePoint.x, thePoint.y); }
      inline void moveTo(pointFltType thePoint) { moveTo(real2intX(thePoint.x), real2intY(thePoint.y)); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Default Color Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the default color */
      inline void setDfltColor(colorArgType color)                                { dfltColor = color; }
      inline void setDfltColor(std::string cornerColor)                           { dfltColor.setToCorner(cornerColor); }
      inline void setDfltColor(const char* cornerColor)                           { dfltColor.setToCorner(std::string(cornerColor)); }
      inline void setDfltColor(colorChanType r, colorChanType g, colorChanType b) { dfltColor.setChansRGB(r, g, b); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Point drawing functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a point at the specified coordinates with the specified color.
          Overloaded versions exist with various arguments.
          @param x The x coordinate of the point
          @param y The y coordinate of the point
          @param color The color to draw the point */
      inline void drawPoint(intCrdT x, intCrdT y, colorArgType color) {
        if(isOnCanvas(x, y))
          drawPointNC(x, y, color);
      }
      inline void drawPoint()                                          { drawPoint(dfltX, dfltY, dfltColor); }
      inline void drawPoint(colorArgType color)                        { drawPoint(dfltX, dfltY, color); }
      inline void drawPoint(intCrdT x, intCrdT y)                      { drawPoint(x, y, dfltColor); }
      inline void drawPoint(fltCrdT x, fltCrdT y)                      { drawPoint(x, y, dfltColor); }
      inline void drawPoint(fltCrdT x, fltCrdT y,  colorArgType color) { drawPoint(real2intX(x), real2intY(y), color); }
      inline void drawPoint(pointIntType thePoint, colorArgType color) { drawPoint(thePoint.x, thePoint.y, color); }
      inline void drawPoint(pointIntType thePoint)                     { drawPoint(thePoint.x, thePoint.y, dfltColor); }
      inline void drawPoint(pointFltType thePoint)                     { drawPoint(real2intX(thePoint.x), real2intY(thePoint.y), dfltColor); }
      inline void drawPoint(pointFltType thePoint, colorArgType color) { drawPoint(real2intX(thePoint.x), real2intY(thePoint.y), color); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Line Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a line.
          This function is optimized for speed, and has special code for handling lines of slope 0, 1, -1, and infinity.  Line is clipped to the
          current canvas.
          @param x1 x coordinate of the first point
          @param y1 y coordinate of the first point
          @param x2 x coordinate of the second point
          @param y2 y coordinate of the second point
          @param color The color to use

          @par Performance Note
          This function will perform better if (x1,y2) and (x2,y2) are in the clip region.  Further x1<x2 will save several steps in
          the algorithm.

          @par Algorithm Notes
          This function treats lines of slope 0, 1, -1, and infinity as special cases.  Special clipping and drawing algorithms are used for each case.  All
          other lines are broken up into four classes by slope: 0<m<1, 1<m<infinity, -1<m<0, and -infinity<m<-1.  Separate line clipping algorithms are used
          for positive slope lines and for negative slope lines.

          The algorithms used to draw lines in the last four cases are related to the classic algorithm presented by Bresenham in 1965 and the
          extensions to Bresenham's algorithm given by Pitteway in 1967 and Van Aken in 1984.  The basic algorithm described by Bresenham, Pitteway, and Van
          Aken is known as the "Midpoint Algorithm".  For the case 0<m<1, the algorithm used is actually the midpoint algorithm, and the remaining cases are
          obvious extensions to the midpoint algorithm.  Each case is customized and optimized for the given slope class.

          The clipping algorithm used for the last slope classes is similar in spirit to the Cohen-Sutherland Line-Clipping algorithm, but is optimized
          for each slope class.  Several pre-checks are made in order to avoid the slope computations in the Cohen-Sutherland algorithm -- in fact intersections
          are only computed if absolutely required.  Note that the only floating point computations in this function are the intersection computations, and they
          will be avoided completely if the given line need not be clipped.*/
      void drawLine(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorArgType color);
      inline void drawLine(pointFltType point1)                                                { drawLine( dfltX, dfltY, real2intX(point1.x), real2intY(point1.y), dfltColor); }
      inline void drawLine(pointFltType point1, colorArgType color)                            { drawLine( dfltX, dfltY, real2intX(point1.x), real2intY(point1.y), color); }
      inline void drawLine(pointIntType point1)                                                { drawLine( dfltX, dfltY, point1.x, point1.y, dfltColor); }
      inline void drawLine(pointIntType point1, colorArgType color)                            { drawLine( dfltX, dfltY, point1.x, point1.y, color); }
      inline void drawLine(pointFltType point1, pointFltType point2)                           { drawLine(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), dfltColor); }
      inline void drawLine(pointFltType point1, pointFltType point2, colorArgType color)       { drawLine(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), color); }
      inline void drawLine(pointIntType point1, pointIntType point2)                           { drawLine( point1.x, point1.y, point2.x, point2.y, dfltColor); }
      inline void drawLine(pointIntType point1, pointIntType point2, colorArgType color)       { drawLine( point1.x, point1.y, point2.x, point2.y, color); }
      inline void drawLine(intCrdT x, intCrdT y)                                               { drawLine( dfltX, dfltY, x, y, dfltColor); }
      inline void drawLine(fltCrdT x, fltCrdT y)                                               { drawLine( dfltX, dfltY, real2intX(x), real2intY(y), dfltColor); }
      inline void drawLine(intCrdT x, intCrdT y, colorArgType color)                           { drawLine( dfltX, dfltY, x, y, color); }
      inline void drawLine(fltCrdT x, fltCrdT y, colorArgType color)                           { drawLine( dfltX, dfltY, real2intX(x), real2intY(y), color); }
      inline void drawLine(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2)                     { drawLine( x1, y1, x2, y2, dfltColor); }
      inline void drawLine(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2)                     { drawLine( x1, y1, x2, y2, dfltColor); }
      inline void drawLine(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorArgType color) { drawLine( real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), color); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Unfilled Triangle Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw an un-filled triangle
          @bug Some pixels may be drawn more than once.
          @param x1 The x coordinate of the first point
          @param y1 The y coordinate of the first point
          @param x2 The x coordinate of the second point
          @param y2 The y coordinate of the second point
          @param x3 The x coordinate of the third point
          @param y3 The y coordinate of the third point
          @param color The color to use for the triangle */
      void drawTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3,  colorArgType color);
      inline void drawTriangle(pointIntType *thePoints, colorArgType color)                                                { drawTriangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, thePoints[2].x, thePoints[2].y, color); }
      inline void drawTriangle(pointFltType *thePoints)                                                                    { drawTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                                                                                                                                          real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                                                                                                                                          real2intX(thePoints[2].x), real2intY(thePoints[2].y), dfltColor); }
      inline void drawTriangle(pointFltType *thePoints, colorArgType color)                                                { drawTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                                                                                                                                          real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                                                                                                                                          real2intX(thePoints[2].x), real2intY(thePoints[2].y), color); }
      inline void drawTriangle(pointIntType *thePoints)                                                                    { drawTriangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, thePoints[2].x, thePoints[2].y, dfltColor); }
      inline void drawTriangle(pointIntType point1, pointIntType point2, pointIntType point3)                              { drawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, dfltColor); }
      inline void drawTriangle(pointFltType point1, pointFltType point2, pointFltType point3)                              { drawTriangle(real2intX(point1.x), real2intY(point1.y),
                                                                                                                                          real2intX(point2.x), real2intY(point2.y),
                                                                                                                                          real2intX(point3.x), real2intY(point3.y), dfltColor); }
      inline void drawTriangle(pointFltType point1, pointFltType point2, pointFltType point3, colorArgType color)          { drawTriangle(real2intX(point1.x), real2intY(point1.y),
                                                                                                                                          real2intX(point2.x), real2intY(point2.y),
                                                                                                                                          real2intX(point3.x), real2intY(point3.y), color); }
      inline void drawTriangle(pointIntType point1, pointIntType point2, pointIntType point3, colorArgType color)          { drawTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, color); }
      inline void drawTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3)                     { drawTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), dfltColor); }
      inline void drawTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3, colorArgType color) { drawTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), color); }
      inline void drawTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3)                     { drawTriangle(x1, y1, x2, y2, x3, y3, dfltColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Filled Triangle Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a triangle filled with a solid color using a nicely optimized, horizontal scan conversion algorithm.
          @bug Triangles not entirely on the canvas are not rendered.
          @bug Not thread safe.
          @param x1 The x coordinate of the first point
          @param y1 The y coordinate of the first point
          @param x2 The x coordinate of the second point
          @param y2 The y coordinate of the second point
          @param x3 The x coordinate of the third point
          @param y3 The y coordinate of the third point
          @param color The color to use for the triangle */
      void drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorArgType color);
      inline void drawFillTriangle(pointIntType *thePoints, colorArgType color)                                                { drawFillTriangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, thePoints[2].x, thePoints[2].y, color); }
      inline void drawFillTriangle(pointFltType *thePoints)                                                                    { drawFillTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                                                                                                                                                  real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                                                                                                                                                  real2intX(thePoints[2].x), real2intY(thePoints[2].y), dfltColor); }
      inline void drawFillTriangle(pointFltType *thePoints, colorArgType color)                                                { drawFillTriangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y),
                                                                                                                                                  real2intX(thePoints[1].x), real2intY(thePoints[1].y),
                                                                                                                                                  real2intX(thePoints[2].x), real2intY(thePoints[2].y), color); }
      inline void drawFillTriangle(pointIntType *thePoints)                                                                    { drawFillTriangle(thePoints[0].x, thePoints[0].y,
                                                                                                                                                  thePoints[1].x, thePoints[1].y,
                                                                                                                                                  thePoints[2].x, thePoints[2].y, dfltColor); }
      inline void drawFillTriangle(pointIntType point1, pointIntType point2, pointIntType point3)                              { drawFillTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, dfltColor); }
      inline void drawFillTriangle(pointFltType point1, pointFltType point2, pointFltType point3)                              { drawFillTriangle(real2intX(point1.x), real2intY(point1.y),
                                                                                                                                                  real2intX(point2.x), real2intY(point2.y),
                                                                                                                                                  real2intX(point3.x), real2intY(point3.y), dfltColor); }
      inline void drawFillTriangle(pointFltType point1, pointFltType point2, pointFltType point3, colorArgType color)          { drawFillTriangle(real2intX(point1.x), real2intY(point1.y),
                                                                                                                                                  real2intX(point2.x), real2intY(point2.y),
                                                                                                                                                  real2intX(point3.x), real2intY(point3.y), color); }
      inline void drawFillTriangle(pointIntType point1, pointIntType point2, pointIntType point3, colorArgType color)          { drawFillTriangle(point1.x, point1.y, point2.x, point2.y, point3.x, point3.y, color); }
      inline void drawFillTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3)                     { drawFillTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), dfltColor); }
      inline void drawFillTriangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, fltCrdT x3, fltCrdT y3, colorArgType color) { drawFillTriangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), real2intX(x3), real2intY(y3), color); }
      inline void drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3)                     { drawFillTriangle(x1, y1, x2, y2, x3, y3, dfltColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Shaded Triangle Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
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
      void drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorArgType color1, colorArgType color2, colorArgType color3);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Unfilled Rectangle Drawing Functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw an unfilled rectangle with diagonal corners located at (x1, y1) and and (x2, y2).
          Best performance will be achieved if (x1, y1) is the upper left corner, and (x2,y2) is the lower left corner and both (x1,y1) and (x2,y2) are within
          the bounds of the canvas using the specified color.
          @param x1 The x coordinate of first corner
          @param y1 The y coordinate of first corner
          @param x2 The x coordinate of second corner
          @param y2 The y coordinate of second corner
          @param color The color to use */
      void drawRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorArgType color);
      inline void drawRectangle(pointIntType point1, pointIntType point2, colorArgType color)       { drawRectangle(point1.x, point1.y, point2.x, point2.y, color); }
      inline void drawRectangle(pointIntType point1, pointIntType point2)                           { drawRectangle(point1.x, point1.y, point2.x, point2.y, dfltColor); }
      inline void drawRectangle(pointFltType point1, pointFltType point2, colorArgType color)       { drawRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), color); }
      inline void drawRectangle(pointFltType point1, pointFltType point2)                           { drawRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), dfltColor); }
      inline void drawRectangle(pointIntType *thePoints, colorArgType color)                        { drawRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, color); }
      inline void drawRectangle(pointFltType *thePoints)                                            { drawRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), dfltColor); }
      inline void drawRectangle(pointFltType *thePoints, colorArgType color)                        { drawRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), color); }
      inline void drawRectangle(pointIntType *thePoints)                                            { drawRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, dfltColor); }
      inline void drawRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2)                     { drawRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), dfltColor); }
      inline void drawRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorArgType color) { drawRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), color); }
      inline void drawRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2)                     { drawRectangle(x1, y1, x2, y2, dfltColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Filled Rectangle Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a filled rectangle with diagonal corners located at (x1, y1) and and (x2, y2).
          Best performance will be achieved if (x1, y1) is the upper left corner, and (x2,y2) is the lower left corner and both (x1,y1) and (x2,y2) are within
          the bounds of the canvas using the specified color.
          @param x1 The x coordinate of first corner
          @param y1 The y coordinate of first corner
          @param x2 The x coordinate of second corner
          @param y2 The y coordinate of second corner
          @param color The color to use */
      void drawFillRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorArgType color);
      inline void drawFillRectangle(pointIntType point1, pointIntType point2, colorArgType color)       { drawFillRectangle(point1.x, point1.y, point2.x, point2.y, color); }
      inline void drawFillRectangle(pointIntType point1, pointIntType point2)                           { drawFillRectangle(point1.x, point1.y, point2.x, point2.y, dfltColor); }
      inline void drawFillRectangle(pointFltType point1, pointFltType point2, colorArgType color)       { drawFillRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), color); }
      inline void drawFillRectangle(pointFltType point1, pointFltType point2)                           { drawFillRectangle(real2intX(point1.x), real2intY(point1.y), real2intX(point2.x), real2intY(point2.y), dfltColor); }
      inline void drawFillRectangle(pointIntType *thePoints, colorArgType color)                        { drawFillRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, color); }
      inline void drawFillRectangle(pointFltType *thePoints)                                            { drawFillRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), dfltColor); }
      inline void drawFillRectangle(pointFltType *thePoints, colorArgType color)                        { drawFillRectangle(real2intX(thePoints[0].x), real2intY(thePoints[0].y), real2intX(thePoints[1].x), real2intY(thePoints[1].y), color); }
      inline void drawFillRectangle(pointIntType *thePoints)                                            { drawFillRectangle(thePoints[0].x, thePoints[0].y, thePoints[1].x, thePoints[1].y, dfltColor); }
      inline void drawFillRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2)                     { drawFillRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), dfltColor); }
      inline void drawFillRectangle(fltCrdT x1, fltCrdT y1, fltCrdT x2, fltCrdT y2, colorArgType color) { drawFillRectangle(real2intX(x1), real2intY(y1), real2intX(x2), real2intY(y2), color); }
      inline void drawFillRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2)                     { drawFillRectangle(x1, y1, x2, y2, dfltColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Unfilled Circle Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw an un-filled circle.
          The algorithm used is based upon the one presented in "A Linear Algorithm for Incremental Digital Display of Circular Arcs" published in the
          Communications of the AMC in Feb 1977 and written by J.E. Bresenham.  Bresenham's algorithm has been significantly improved by using only integer
          arithmetic and adding second order differences to the computation -- much the way the line drawing algorithm works in this package.  The algorithm
          is essentially a scan line conversion algorithm, so the circle is always approximately one pixel thick.  One subtle point: The real X and Y axes in
          this package can have different scaling.  This means that one must pick a direction in which the radius will be measured in real coordinate deltas.
          In this function, that direction is along the X axis -- i.e. the radius of the drawn circle will be measured horizontally. This function is well
          optimized.
          @bug Draws everyting even if it's off the canvas.
          @param centerX The x coordinate of the center
          @param centerY The y coordinate of the center
          @param radiusX The radius of the circle
          @param color The color to draw the circle with */
      void drawCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorArgType color);
      inline void drawCircle(intCrdT radiusX)                                                       { drawCircle(dfltX, dfltY, radiusX, dfltColor); }
      inline void drawCircle(fltCrdT radiusX)                                                       { drawCircle(dfltX, dfltY, realDelta2intX(radiusX), dfltColor); }
      inline void drawCircle(pointFltType centerPoint, fltCrdT radiusX)                             { drawCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), dfltColor); }
      inline void drawCircle(pointFltType centerPoint, fltCrdT radiusX, colorArgType color)         { drawCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), color); }
      inline void drawCircle(pointIntType centerPoint, intCrdT radiusX)                             { drawCircle(centerPoint.x, centerPoint.y, radiusX, dfltColor); }
      inline void drawCircle(pointIntType centerPoint, intCrdT radiusX, colorArgType color)         { drawCircle(centerPoint.x, centerPoint.y, radiusX, color); }
      inline void drawCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX)                     { drawCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), dfltColor); }
      inline void drawCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX, colorArgType color) { drawCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), color); }
      inline void drawCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX)                     { drawCircle(centerX, centerY, radiusX, dfltColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Filled Circle Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw an un-filled circle.
          The algorithm used to compute circle edge points is the same as that used in drawCircle; however, the algorithm used to fill the circle is of my own
          design.  I doubt that it is new, but I have never come across it in my readings -- not that I have looked too hard. The algorithm has the advantage
          that most of the interior points are only drawn one time.  One subtle point: The real X and Y axes in this package can have different scaling.  This
          means that one must pick a direction in which the radius will be measured in real coordinate deltas.  In this function, that direction is along the
          X axis -- i.e. the radius of the drawn circle will be measured horizontally. This function is well optimized.
          @bug Draws everyting even if it's off the canvas.
          @param centerX The x coordinate of the center
          @param centerY The y coordinate of the center
          @param radiusX The radius of the circle
          @param color The color to draw the circle with */
      void drawFillCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorArgType color);
      inline void drawFillCircle(fltCrdT radiusX)                                                       { drawFillCircle(dfltX, dfltY, realDelta2intX(radiusX), dfltColor); }
      inline void drawFillCircle(intCrdT radiusX)                                                       { drawFillCircle(dfltX, dfltY, radiusX, dfltColor); }
      inline void drawFillCircle(pointFltType centerPoint, fltCrdT radiusX, colorArgType color)         { drawFillCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), color); }
      inline void drawFillCircle(pointFltType centerPoint, fltCrdT radiusX)                             { drawFillCircle(real2intX(centerPoint.x), real2intY(centerPoint.y), realDelta2intX(radiusX), dfltColor); }
      inline void drawFillCircle(pointIntType centerPoint, intCrdT radiusX, colorArgType color)         { drawFillCircle(centerPoint.x, centerPoint.y, radiusX, color); }
      inline void drawFillCircle(pointIntType centerPoint, intCrdT radiusX)                             { drawFillCircle(centerPoint.x, centerPoint.y, radiusX, dfltColor); }
      inline void drawFillCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX)                     { drawFillCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), dfltColor); }
      inline void drawFillCircle(fltCrdT centerX, fltCrdT centerY, fltCrdT radiusX, colorArgType color) { drawFillCircle(real2intX(centerX), real2intY(centerY), realDelta2intX(radiusX), color); }
      inline void drawFillCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX)                     { drawFillCircle(centerX, centerY, radiusX, dfltColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Piece-Wise Linear Curve Drawing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw Piece-Wise Linear Curves
          @bug Some pixels may be drawn more than once.
      */
      void drawPLCurve(int numPoints, intCrdT *x, intCrdT *y, colorArgType color);
      void drawPLCurve(int numPoints, intCrdT *x, intCrdT *y);
      void drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y, colorArgType color);
      void drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y);
      void drawPLCurve(int numPoints, pointIntType *thePoints, colorArgType color);
      void drawPLCurve(int numPoints, pointIntType *thePoints);
      void drawPLCurve(int numPoints, pointFltType *thePoints, colorArgType color);
      void drawPLCurve(int numPoints, pointFltType *thePoints);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Hershey Glyph Rendering Utility Functions */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Render a glyph from the Hershey character set.
          The glyph is rendered with its origin at the given coordinates.  This function is intended to provide only the most basic glyph rendering.  For
          example, glyphs are rendered with the line drawing functions, and therefore are not anti-aliased.
          @param glyphNum The character number of the glyph to render
          @param x        The x coordinate at which to render the glyph
          @param y        The x coordinate at which to render the glyph
          @param magX     The magnification of the glyph in the x direction
          @param magY     The magnification of the glyph in the y direction
          @param aColor   The color with which to render the glyph */
      void drawHersheyGlyph(int glyphNum, intCrdT x, intCrdT y, double magX, double magY, colorArgType aColor);
      void drawHersheyGlyph(int glyphNum, fltCrdT x, fltCrdT y, double magX, double magY, colorArgType aColor) { drawHersheyGlyph(glyphNum, real2intX(x), real2intY(y), magX, magY, aColor); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name ASCII Character Rendering.
          What are font rendering functions doing in a raster graphics library? Sometimes I like to put a label on image.*/
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Render a string using Hershey ASCII Fonts.
          While the string is rendered with fixed font spacing, the Hershey fonts are not fixed width fonts.
          @param aString The string
          @param aFont   The font to set the default with
          @param x       The x coordinate at which to render the first glyph
          @param y       The x coordinate at which to render the first glyph
          @param aColor  The color with which to render the glyphs
          @param cex     A factor by which to expand the size of each glyph -- 1 is a good value (the name comes from R).
          @param spc     Space to jump for each charcter -- 20 for SL fonts, 23 for DL fonts, and 25 for TL fonts.  Scaled with cex. */
      void drawString(std::string aString, mjr::hershey::font aFont, intCrdT x, intCrdT y, colorArgType aColor, double cex, intCrdT spc);
      void drawString(std::string aString, mjr::hershey::font aFont, fltCrdT x, fltCrdT y, colorArgType aColor, double cex, intCrdT spc) {
        drawString(aString, aFont, real2intX(x), real2intY(y), aColor, cex, spc);
      }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Renders a filled, bounding box for the given string as rendered via drawString.
          @param aString     A string to render
          @param aFont       The font to set the default with
          @param x           The x coordinate at which to render the first glyph
          @param y           The x coordinate at which to render the first glyph
          @param stringColor The color with which to render the glyphs
          @param boxColor    The color with which to render the BOX
          @param cex         A factor by which to expand the size of each glyph -- 1 is a good value (the name comes from R).
          @param spc         Space to jump for each charcter -- 20 for SL fonts, 23 for DL fonts, and 25 for TL fonts.  Scaled with cex. */
      void drawStringBox(std::string aString, mjr::hershey::font aFont, intCrdT x, intCrdT y, colorArgType stringColor, colorArgType boxColor, double cex, intCrdT spc);
      void drawStringBox(std::string aString, mjr::hershey::font aFont, fltCrdT x, fltCrdT y, colorArgType stringColor, colorArgType boxColor, double cex, intCrdT spc) {
        drawStringBox(aString, aFont, real2intX(x), real2intY(y), stringColor, boxColor, cex, spc);
      }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name File Reading and Writing Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Is libTIFF supported -- that is: will the readTIFFfile() method do anything? 
          Note that readTIFFfile() is the only method that needs libTIFF.  In particular, writeTIFFfile() works without libTIFF. */
      bool supportLibTIFF();
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
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
          @retval 18 Sample Format is not unsigned integer or IEEE floating point
          @retval 19 File and ramCanvas samples per pixel (channel count) differs
          @retval 20 File and ramCanvas channel depth differ
          @retval 21 File and ramCanvas channel format (int vs float) differ
          @retval 22 Planar configuration is invalid (not 1 or 2)
          @retval 32 TIFF read support not provided in this compile */
      int readTIFFfile(std::string fileName);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Write a TIFF format image file.  Respects integer coordinate system orientation.

          Why TIFF? TIFF is both broadly supported and flexible enough to represent almost every ramCanvas image type perfectly.

          Use Cases (In order of priority)
              - Write a bit perfect TIFF representation of ramCanvas images
              - Simultaneously convert any ramCanvas into 24-bit truecolor RGB and write the resulting TIFF
              - Do all the above while simultaneously applying a homogeneous image filter

          Limitations
              - Channels must be no more than 64-bits wide
              - No more than 2^16-1 channels
              - Image width no more than 2^32-1 (normally intCrdT limits this to 2^31-1)
              - Image height no more than 2^32-1 (normally intCrdT limits this to 2^31-1)
              - Image row data size (numPixX * colorT::bitsPerChan * colorT::channelCount / 8) must be less than 2^32-1 bytes
              - Image data must be less than 2^32-1 bytes

          Limitations for bit perfect (toTRU is NULL) files:
              - Channels must be uint8_t, uint16_t, uint32_t, uint64_t, float (32-bit), or double (64-bit)

          @param fileName The file name to write data to
          @param rcConverter An rcConverter object instance
          @param markAlpha   If an alpha channel is present, then mark it as such in the TIFF file.
          @return Status of I/O
          @retval  0 Everything seems to have worked
          @retval  2 Image channels are too shallow for TIFF format
          @retval  3 Image channels are too deep for TIFF format
          @retval  4 Image has too few channels for TIFF format
          @retval  5 Image has too many channels for TIFF format
          @retval  6 Image has too few columns for TIFF format
          @retval  7 Image has too many columns for TIFF format
          @retval  8 Image has too few rows for TIFF format
          @retval  9 Image has too few rows for TIFF format
          @retval 10 Image rows are too large (too much data) for TIFF format
          @retval 11 Image is too large (too much data)  for TIFF format */
      template <class rcConT> int writeTIFFfile(std::string fileName, rcConT rcConverter, bool markAlpha);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Simplified overload for writeTIFFfile() that only requires the filename. */
      int writeTIFFfile(std::string fileName, bool markAlpha = true);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Write a 24-bit (8-bit per channel) RGB, TGA format graphics file.  Respects integer coordinate system orientation.

          Why TGA? TGA files are not well supported by modern software.  When supported, it is normally only 8-bit RGBA.  With these limitations one might ask
          why this function exists.  I am a POV-Ray fan, and it uses a specialized TGA format for height maps.  That's really it...  One could use this
          function to dump out regular RGB images, but I suggest writeTIFFfile() for that.

          Note TGA files are 8-bit files, and *_byte functions are used to convert channel values to 8-bit before being written.  

          @param fileName The file name name to write data to
          @return Status of I/O
          @retval  0 Everything seems to have worked
          @retval  1 File open failure
          @retval  6 Image of zero width
          @retval  7 Image too wide for TGA format (> 2^16-1)
          @retval  8 Image of zero height
          @retval  9 Image too tall for TGA format (> 2^16-1) */
      int writeTGAfile(std::string fileName);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Read RAW file

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @bug Floating point data is read directly from disk as-is without regard for endianness.  I have no plans to fix this because I'm not sure what a
               good fix looks like

          @retval  0 Image file loaded successfully
          @retval  1 File open failure
          @retval  2 NOT USED
          @retval  3 NOT USED
          @retval  4 NOT USED
          @retval  5 NOT USED
          @retval  6 NOT USED
          @retval  7 NOT USED
          @retval  8 File of zero width
          @retval  9 File of zero height
          @retval 10 NOT USED
          @retval 11 Read failure
          @retval 12 Canvas Allocation failed (insufficient width)
          @retval 14 Canvas Allocation failed (insufficient height)
          @retval 15 bps not 8, 16, 32, or 64
          @retval 16 NOT USED
          @retval 17 NOT USED
          @retval 18 Sample Format is not unsigned integer or IEEE floating point
          @retval 19 File and ramCanvas samples per pixel (channel count) differs
          @retval 20 File and ramCanvas channel depth differ
          @retval 21 File and ramCanvas channel format (int vs float) differ
          @retval 22 NOT USED
          @retval 23 File is signed integer or unsigned float
          @retval 24 File is missing MJRRAW magic number
          @retval 25 Image data read failure (file may have ended prematurely)
          @retval 26 Malformed header
          @retval 27 Image is too wide to be supported by ramCanvas
          @retval 28 Image is too tall to be supported by ramCanvas
          @retval 29 Error reading numbers in header
          @retval 32 NOT USED
          @retval 33 Image width missing from header
          @retval 34 Image height missing from header
          @retval 35 Image channel count missing from header
          @retval 36 Image channel depth missing from header */
      int readRAWfile(std::string fileName);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Write a MJRRAW file. Respects integer coordinate system orientation.

          Why? This simple file format is designed to house the more exotic images this library supports, and be easily consumed by many image processing and
          data visualization tools -- usually via a feature referred to as a raw importer.  ImageMagick, VisIT, ParaView, and ImageJ all can read this type of
          data. The header is exactly 100 bytes, ASCII, and contains two newlines.  The idea being that one can do a 'head -n 2 FILENAME' on the image file,
          and get a human readable output of basic image info that also happens to be easy to parse.  The first line of the header is the text "MJRRAW".  The
          second line of the header consists of a sequence of values& value labels and followed by enough zero characters to pad to get to the 100 byte mark.
          That's 100 bytes for the two lines including the two newline characters.  The values consist of uppercase letters and numbers, and each label is a
          single lower case letter.  If a value is a number, then it is expressed as a decimal number in ASCII using -- it may be zero padded.  While the code
          in ramCanvasTpl doesn't make assumptions about the order of the header values, some of the example scripts require them to be in the following
          order: x, y, c, b, s, t, & i.  The header is followed by the binary image.

          Labels:
            - x: Number of pixels on X (horizontal axis) expressed as a zero padded, decimal integer
            - y: Number of pixels on Y (vertical axis) expressed as a zero padded, decimal integer
            - c: Number of channels expressed as a zero padded, decimal integer
            - b: Number of bits per channel expressed as a zero padded, decimal integer
            - s: Channel signdness (ignored for floating point channels)
              - UNS: Unsigned data.  DEFAULT VALUE.
              - SGN: Signed data
            - t: Channel type
              - INT: Integral channels.  DEFAULT VALUE.
              - FLT: Floating point channels
            - i: endianness
              - BIG: Big endian 
              - LTL: Little endian
              - UNK: Unknown.  DEFAULT VALUE.  For read we assume file matches system running the code.  
            - Currently reserved, but unused labels
              - p: Pixel format
                - MXL: Each pixel of the image is written in sequence.  DEFAULT VALUE.
                - PLN: Each channel of the *image* is written in sequence.
                - BIT: For bit-masks with 8 bits packed in a byte.  
              - z: Compression
                - 000: No compression.  DEFAULT VALUE.
                - ZLB: Zlib.
                - GZP: Gzip.

          Two headers that both specify a 256x128 image with 3 unsigned 8-bit integer channels encoded little endian:

                      MJRRAW
                      256x128y3c8bUNSsINTtLTLi00000000000000000000000000000000000000000000000000000000000000000000

                      MJRRAW
                      0000000000000000256x0000000000000000128y000000000000000000000000003c00000000008bSGNsINTtLTLi

          @param fileName    The file name name to write data to
          @param rcConverter An rcConverter object instance
          @retval 0 The write was successful.
          @retval 1 Could not open file. */
      template <class rcConT> int writeRAWfile(std::string fileName, rcConT rcConverter);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Simplified overload for writeRAWfile() that only requires the filename. */
      int writeRAWfile(std::string fileName);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Boolean Clip Test Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Determine if the given point is within the bounds of the ramCanvasTpl.
          @param x The x coordinate of the point to test
          @param y The y coordinate of the point to test
          @return Returns true if the point would be clipped. */
      inline int isCliped(fltCrdT x, fltCrdT y) const { return isCliped(real2intX(x), real2intY(y)); }
      inline int isCliped(intCrdT x, intCrdT y) const { return ((x < 0) || (y < 0) || (x >= numPixX) || (y >= numPixY)); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Determine if the given point is within the bounds of the ramCanvasTpl.
          @param x The x coordinate of the point to test
          @param y The y coordinate of the point to test
          @return Returns true if the point would be not be clipped. */
      inline int isOnCanvas(fltCrdT x, fltCrdT y) const { return isCliped(real2intX(x), real2intY(y)); }
      inline int isOnCanvas(intCrdT x, intCrdT y) const { return ((x >= 0) && (y >= 0) && (x < numPixX) && (y < numPixY)); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Coordinate Conversions. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert real x coordinate to integral x coordinate
          @param x The real x coordinate value to be converted.
          @return The integer x coordinate corresponding to the given x coordinate */
      intCrdT real2intX(fltCrdT x) const;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert real y coordinate to integral y coordinate
          @param y The real y coordinate value to be converted.
          @return The integer y coordinate corresponding to the given y coordinate */
      intCrdT real2intY(fltCrdT y) const;
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert integral x coordinate to real x coordinate
          @param x The integer x coordinate value to be converted.
          @return The real x coordinate corresponding to the given x coordinate */
      fltCrdT int2realX(intCrdT x);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert integral y coordinate to real y coordinate
          @param y The integer y coordinate value to be converted.
          @return The real y coordinate corresponding to the given y coordinate */
      fltCrdT int2realY(intCrdT y);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Coordinate Pair Conversions. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert real x & y coordinates to integer x & y coordinates
          @param x The integer x coordinate value to be converted.
          @param y The integer y coordinate value to be converted.
          @return The real x & y coordinates corresponding to the given integer x & y coordinates */
      inline pointFltType int2real(intCrdT x, intCrdT y) { return point2d(int2realX(x), int2realY(y)); }
      /** Convert integer x & y coordinates to real x & y coordinates
          @param x The real x coordinate value to be converted.
          @param y The real y coordinate value to be converted.
          @return The integer x & y coordinates corresponding to the given real x & y coordinates */
      inline pointIntType real2int(intCrdT x, intCrdT y) { return point2d(real2intX(x), real2intY(y)); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Pixel Corner Coordinates.

       @warning These functions are experimental!  Functionality and API are likely to change in the future.

      */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Given integer x & y coordinates, produce real x & y coordinates for one of the pixel's corners.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param x       The integer x coordinate value to be converted.
          @param y       The integer y coordinate value to be converted.
          @param cornerX The integer x coordinate of the corner -- should be 0 or 1.
          @param cornerY The integer y coordinate of the corner -- should be 0 or 1.
          @return The real x & y coordinates corresponding to the requested corner */
      inline pointFltType int2corner(intCrdT x, intCrdT y, int cornerX, int cornerY)  { return point2d(int2realX(x+cornerX)-pixWidX/2.0, int2realY(y+cornerY)-pixWidY/2.0); }
      /** Given integer x & y coordinates and a corner index, produce real x & y coordinates for one of the pixel's corners.

          @warning This function is experimental!  Functionality and API are likely to change in the future.

          @param x           The integer x coordinate value to be converted.
          @param y           The integer y coordinate value to be converted.
          @param cornerIndex Corner index. 0 => (0, 0); 1 => (0, 1); 2 => (1, 0); 3 => (1, 1); 
          @return The real x & y coordinates corresponding to the requested corner */
      inline pointFltType int2corner(intCrdT x, intCrdT y, int cornerIndex)           { return int2corner(x, y, (cornerIndex >> 1), (cornerIndex & 1));                     }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Coordinate Delta Conversions. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert real distance on the x coordinate axis to an integral distance
          @param x The real delta x to be converted
          @return integer delta x */
      inline intCrdT realDelta2intX(fltCrdT x) const { return static_cast<intCrdT>(static_cast<fltCrdT>(x)/pixWidX); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert real distance on the y coordinate axis to an integral distance
          @param y The real delta y to be converted
          @return integer delta y */
      inline intCrdT realDelta2intY(fltCrdT y) const { return static_cast<intCrdT>(static_cast<fltCrdT>(y)/pixWidY); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert integral distance on the x coordinate to a real distance
          @param x The real x coordinate value to be converted.
          @return The integer x coordinate corresponding to the given x coordinate */
      inline fltCrdT intDelta2realX(intCrdT x) const { return static_cast<fltCrdT>(x)*pixWidX; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Convert integral distance on the y coordinate to a real distance
          @param y real y coordinate value to be converted.
          @return The integer y coordinate corresponding to the given y coordinate */
      inline fltCrdT intDelta2realY(intCrdT y) const { return static_cast<fltCrdT>(y)*pixWidY; }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Orientation of Real Coordinate Systems */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Get the real X axis orientation
          @return INVERTED means inverted with respect to the integer axis, and NATURAL otherwise.    */
      inline realAxisOrientation getRealAxOrientationX() { return realAxOrientationX; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the real X axis orientation
          @param orientation The orientation (INVERTED or NATURAL)*/
       inline void setRealAxOrientationX(realAxisOrientation orientation) { realAxOrientationX = orientation; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Get the real Y axis orientation
          @return INVERTED means inverted with respect to the integer axis, and NATURAL otherwise.    */
      inline realAxisOrientation getRealAxOrientationY() { return realAxOrientationX; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the real Y axis orientation
          @param orientation The orientation (INVERTED or NATURAL) */
      inline void setRealAxOrientationY(realAxisOrientation orientation) { realAxOrientationY = orientation; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the real axis orientation to default (NATURAL for both X and Y axes) */
      inline void setRealAxisDefaultOrientation() { setRealAxOrientationX(realAxisOrientation::NATURAL); setRealAxOrientationY(realAxisOrientation::NATURAL); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Drawing Mode */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Get the current drawing mode.
       @return The drawing mode */
      inline drawModeType getDrawMode()                         { return drawMode; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the current drawing mode
          NOOP if enableDrawModes is false.
          @param newDrawMode The drawing mode */
      inline void         setDrawMode(drawModeType newDrawMode) { if (enableDrawModes) drawMode = newDrawMode; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the default draw mode */
      inline void         setDefaultDrawMode()                  { setDrawMode(drawModeType::SET); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Orientation of Integer Coordinate Systems */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Get the integer X axis orientation
          @return NATURAL means increasing to the right. */
      inline intAxisOrientation getIntAxOrientationX() { return intAxOrientationX; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Is the integer X axis NATURAL?
          @return true means increasing to the right. */
      inline bool isIntAxOrientationNaturalX() { return (intAxOrientationX == intAxisOrientation::NATURAL); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the integer X axis orientation
          @param orientation The orientation (INVERTED or NATURAL) */
      inline void setIntAxOrientationX(intAxisOrientation orientation) { intAxOrientationX = orientation; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Get the integer Y axis orientation
          @return NATURAL means increasing in the upward direction. */
      inline bool isIntAxOrientationNaturalY() { return (intAxOrientationY == intAxisOrientation::NATURAL); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Is the integer Y axis orientation NATURAL?
          @return NATURAL means increasing in the upward direction. */
      inline intAxisOrientation getIntAxOrientationY() { return intAxOrientationY; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the integer Y axis orientation
          @param orientation The orientation (INVERTED or NATURAL) */
      inline void setIntAxOrientationY(intAxisOrientation orientation) { intAxOrientationY = orientation; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Set the integer axis orientation to default (NATURAL for both X and Y axes) */
      inline void setIntAxisDefaultOrientation() { setIntAxOrientationX(intAxisOrientation::NATURAL); setIntAxOrientationY(intAxisOrientation::NATURAL); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Accessor Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @return The number of pixels in the x direction. */
      inline intCrdT getNumPixX() const { return numPixX; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** @return The number of pixels in the y direction. */
      inline intCrdT getNumPixY() const { return numPixY; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns a pointer to the raw pixel store.
          This generally violates the ramCanvasTpl object interface; however, this may be required for performance.
          @return The number a pointer to the raw pixel store. */
      colorT *getPixels() { return pixels; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Return a clone (a copy) of the raw pixel store.
          This function copies the internal pixel store and returns a pointer to this copy.
          @return Pointer to a copy of the raw pixel store. */
      colorT *clonePixels();
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Real Coordinate Accessor Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      fltCrdT getMinRealX()   { return minRealX;    }                        //!< x coord of min (real coord)
      fltCrdT getMaxRealX()   { return maxRealX;    }                        //!< x coord of max (real coord)
      fltCrdT getMinRealY()   { return minRealY;    }                        //!< y coord of min (real coord)
      fltCrdT getMaxRealY()   { return maxRealY;    }                        //!< y coord of max (real coord)
      fltCrdT getPixWidX()    { return pixWidX;     }                        //!< Width of a pixel (real coord)
      fltCrdT getPixWidY()    { return pixWidY;     }                        //!< Height of a pixel (real coord)
      fltCrdT getCanvasWidX() { return canvasWidX;  }                        //!< Width of the display (real coord)
      fltCrdT getCanvasWidY() { return canvasWidY;  }                        //!< height of the display(real coord)
      fltCrdT getCanvasWidD() { return std::hypot(canvasWidX, canvasWidY); } //!< Width of the display (real coord)
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Pixel Value Accessor Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns a copy of the color at the given coordinates */
      colorT getPxColor(intCrdT x, intCrdT y) const;
      inline colorT getPxColor(fltCrdT x, fltCrdT y)  const { return getPxColor(real2intX(x), real2intY(y)); }
      inline colorT getPxColor(pointIntType thePoint) const { return getPxColor(thePoint.x, thePoint.y); }
      inline colorT getPxColor(pointFltType thePoint) const { return getPxColor(thePoint.x, thePoint.y); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Pixel Value Accessor with Interpolation Methods */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the interpolated color value at the the given coordinates using the given interpolation method.
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @param interpMethod The interpolation method (default: interpolationType::BILINEAR)
          @return Interpolated color value */
      colorT getPxColorInterpolate(double x, double y, interpolationType interpMethod = interpolationType::BILINEAR);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the bilinear interpolated color value at the the given coordinates.
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpBLin(double x, double y);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the truncated interpolated color value at the the given coordinates.
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpTrunc(double x, double y);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the nearest neighbor  interpolated color value at the the given coordinates.
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpNear(double x, double y);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the average 4 interpolated color value at the the given coordinates.
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpAvg4(double x, double y);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns the average 9 interpolated color value at the the given coordinates.
          @param x The x coordinate (the type is double, but the coordinate is in the integer coordinate space.  i.e. x=1.5 is between x=1 and x=2)
          @param y The y coordinate
          @return Interpolated color value */
      colorT getPxColorInterpAvg9(double x, double y);
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name NC stands for No Checks and No Clipping */
      /** The functions here work in a similar way to the non-NC functions, but with no clipping or bounds checking.  Thus, if an argument would cause
          something to be drawn beyond the bounds of the ramCanvasTpl, a core dump will most certainly result.  The intent is to provide less overhead for
          very careful code that handles clipping and error checking by itself -- a good line drawing algorithm for example. */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a point with no clipping or bounds checking.
          @param x The x coordinate of the point to be drawn
          @param y The y coordinate of the point to be drawn
          @param color The color to draw the point. */
      void drawPointNC(intCrdT x, intCrdT y, colorArgType color);
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Get the default point to the specified coordinates with no clipping or bounds checking.
          @param x The x coordinate of the point
          @param y The y coordinate of the point */
      inline colorT  getPxColorNC(intCrdT x, intCrdT y) const { return pixels[numPixX * y + x]; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Returns a reference to the color object for the given pixel with no clipping or bounds checking.
          @param x The x coordinate of the point
          @param y The y coordinate of the point
          @return Reference to the color object associated with the specified point */
      inline colorT& getPxColorRefNC(intCrdT x, intCrdT y) const { return pixels[numPixX * y + x]; }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a horizontal line with no clipping or bounds checking.
          @param xMin The MINIMUM x coordinate of the line to be drawn
          @param xMax The MAXIMUM x coordinate of the line to be drawn
          @param yConst The y coordinate at which the line is to be drawn
          @param color The color to draw the line */
      inline void drawHorzLineNC(intCrdT xMin, intCrdT xMax, intCrdT yConst, colorArgType color) { for(intCrdT x=xMin;x<=xMax;x++) drawPointNC(x, yConst, color); }
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a vertical line with no clipping or bounds checking.
          @param yMin The MINIMUM y coordinate of the line to be drawn
          @param yMax The MAXIMUM y coordinate of the line to be drawn
          @param xConst The x coordinate at which the line is to be drawn
          @param color The color to draw the line */
      inline void drawVertLineNC(intCrdT yMin, intCrdT yMax, intCrdT xConst, colorArgType color) { for(intCrdT y=yMin;y<=yMax;y++) drawPointNC(xConst, y, color); }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name S stands for Simple */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      /** Draw a point without any special drawing options.
          It simply sets the pixel to the given color.  In addition, no clipping or bounds checking is performed.  Thus, if an argument would cause something
          to be drawn beyond the bounds of the ramCanvasTpl, a segfault will most certainly result.  The intent is to provide a less overhead for very
          careful code that handles clipping and error checking and drawing options by itself -- an image filter algorithm for example.  Note that enableDrawModes
          is ignored.
          @param x The x coordinate of the point
          @param y The y coordinate of the point
          @param color The color with which to draw the point */
      inline void drawPointS(intCrdT x, intCrdT y, colorArgType color) { pixels[numPixX * y + x] = color; }
      //@}

      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /** @name Canvas Level Colorization.
       These are tools designed to make things like escape time fractals very easy to create.

       @warning These functions are experimental!  Functionality and API are likely to change in the future.

      */
      //@{
      //--------------------------------------------------------------------------------------------------------------------------------------------------------
      void colorizeFltCanvas(std::function<colorT (fltCrdT, fltCrdT)> cFun);
      void colorizeFltCanvas(std::function<colorT (pointFltType)> cFun);

      void colorizeIntCanvas(std::function<colorT (intCrdT, intCrdT)> cFun);
      void colorizeIntCanvas(std::function<colorT (pointIntType)> cFun);
      //@}

  };

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Constructor
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::ramCanvasTpl() {
    newIntCoordsNC(-1, -1);
    pixels = NULL;
    pixelsE = NULL;
    setRealAxisDefaultOrientation();
    setIntAxisDefaultOrientation();
    setDefaultDrawMode();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Copy Constructor
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::ramCanvasTpl(const ramCanvasTpl &theCanvas) {
    newIntCoordsNC(theCanvas.numPixX, theCanvas.numPixY);
    newRealCoords(theCanvas.minRealX, theCanvas.maxRealX, theCanvas.minRealY, theCanvas.maxRealY);
    pixels = new colorT[theCanvas.numPixX * theCanvas.numPixY];
    pixelsE = pixels + (theCanvas.numPixX * theCanvas.numPixY);
    realAxOrientationX = theCanvas.realAxOrientationX;
    realAxOrientationY = theCanvas.realAxOrientationY;
    intAxOrientationX = theCanvas.intAxOrientationX;
    intAxOrientationY = theCanvas.intAxOrientationY;
    drawMode = theCanvas.drawMode;
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        getPxColorRefNC(x, y) = theCanvas.getPxColorRefNC(x, y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Move constructor
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::ramCanvasTpl(ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>&& theCanvas) {
    newIntCoordsNC(theCanvas.numPixX, theCanvas.numPixY);
    newRealCoords(theCanvas.minRealX, theCanvas.maxRealX, theCanvas.minRealY, theCanvas.maxRealY);
    realAxOrientationX = theCanvas.realAxOrientationX;
    realAxOrientationY = theCanvas.realAxOrientationY;
    intAxOrientationX  = theCanvas.intAxOrientationX;
    intAxOrientationY  = theCanvas.intAxOrientationY;
    drawMode           = theCanvas.drawMode;
    pixels             = theCanvas.pixels;
    pixelsE            = theCanvas.pixelsE;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Move assignment operator
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>&
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::operator=(ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>&& theCanvas) {
    if (this != &theCanvas) {
      newIntCoordsNC(theCanvas.numPixX, theCanvas.numPixY);
      newRealCoords(theCanvas.minRealX, theCanvas.maxRealX, theCanvas.minRealY, theCanvas.maxRealY);
      realAxOrientationX = theCanvas.realAxOrientationX;
      realAxOrientationY = theCanvas.realAxOrientationY;
      intAxOrientationX  = theCanvas.intAxOrientationX;
      intAxOrientationY  = theCanvas.intAxOrientationY;
      drawMode           = theCanvas.drawMode;
      pixels             = theCanvas.pixels;
      pixelsE            = theCanvas.pixelsE;
    }
    return *this;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Normal Constructor
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::ramCanvasTpl(intCrdT numPixX_p, intCrdT numPixY_p, fltCrdT minRealX_p, fltCrdT maxRealX_p, fltCrdT minRealY_p, fltCrdT maxRealY_p) {
    newIntCoordsNC(numPixX_p, numPixY_p);
    newRealCoords(minRealX_p, maxRealX_p, minRealY_p, maxRealY_p);
    pixels = new colorT[numPixX * numPixY];
    pixelsE = pixels + (numPixX * numPixY);
    setRealAxisDefaultOrientation();
    setIntAxisDefaultOrientation();
    setDefaultDrawMode();
    clrCanvasToBlack();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::~ramCanvasTpl() {
    if(pixels != NULL) {
      delete[] pixels;
      pixels = NULL;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::newIntCoordsNC(intCrdT numPixX_p, intCrdT numPixY_p) {
    if( (numPixX_p <= intCrdMax) && (numPixY_p <= intCrdMax) ) {
      numPix  = numPixX_p * numPixY_p;;
      numPixX = numPixX_p;
      numPixY = numPixY_p;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::newRealCoords(fltCrdT minRealX_p, fltCrdT maxRealX_p, fltCrdT minRealY_p, fltCrdT maxRealY_p) {
    if( (minRealX_p <= maxRealX_p) && (minRealY_p <= maxRealY_p) ) {
      minRealX = minRealX_p;
      maxRealX = maxRealX_p;
      minRealY = minRealY_p;
      maxRealY = maxRealY_p;
      updRealCoords();
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::updRealCoords() {
    canvasWidX = maxRealX - minRealX;
    canvasWidY = maxRealY - minRealY;
    pixWidX = canvasWidX / numPixX;
    pixWidY = canvasWidY / numPixY;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::clrCanvasChannelToMin(int chan) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        getPxColorRefNC(x, y).setChanToMin(chan);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::clrCanvasChannelToMax(int chan) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        getPxColorRefNC(x, y).setChanToMax(chan);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::clrCanvasToBlack() {
    ////// Diffrent ways to do it -- unless otherwise noted, all of them are about the same performance with GCC if colorT has a fast mask

    //// Use std:memset
    // std::memset((void*)pixels, 0, numPix*sizeof(colorT));

    //// Use std::fill
    // colorT black;
    // black.setToBlack();
    // std::fill(pixels, pixelsE, black);

    //// Loop over pixel array
    // for(colorT* p=pixels; p<pixelsE; p++)
    //   p->setToBlack();

    //// loop over x & y coordinates
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        getPxColorRefNC(x, y).setToBlack();

    //// Call clrCanvas with black (this one is *way* slower)
    // clrCanvas(colorT(colorCornerEnum::BLACK));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::clrCanvasToWhite() {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        getPxColorRefNC(x, y).setToWhite();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::clrCanvas() {
    clrCanvas(dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::clrCanvas(colorArgType color) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        drawPointS(x, y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::autoHistStrech() {
    colorChanType cmin = colorT::maxChanVal;
    colorChanType cmax = colorT::minChanVal;
    for(intCrdT y=0;y<numPixY;y++) {
      for(intCrdT x=0;x<numPixX;x++) {
        colorT daColor = getPxColorNC(x, y);
        colorChanType curMin = daColor.getMinC();
        colorChanType curMax = daColor.getMaxC();
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::autoMaxHistStrechRGB() {
    colorT cmin; cmin.setChans(cmin.maxChanVal);
    colorT cmax; cmax.setChans(cmin.minChanVal);
    for(intCrdT y=0;y<numPixY;y++) {
      for(intCrdT x=0;x<numPixX;x++) {
        colorT daColor = getPxColorNC(x, y);
        cmin.tfrmMin(daColor);
        cmax.tfrmMax(daColor);
      }
    }
    colorChanType absCompMin = cmin.getMinC();
    colorChanType absCompMax = cmax.getMaxC();
    if(absCompMax-absCompMin > 0) {
      double rc = 1.0*static_cast<double>(cmin.maxChanVal-cmin.minChanVal)/static_cast<double>(cmax.getRed()-cmin.getRed());
      double rb = cmin.maxChanVal - 1.0*rc*cmax.getRed();
      double gc = 1.0*static_cast<double>(cmin.maxChanVal-cmin.minChanVal)/static_cast<double>(cmax.getGreen()-cmin.getGreen());
      double gb = cmin.maxChanVal - 1.0*gc*cmax.getGreen();
      double bc = 1.0*static_cast<double>(cmin.maxChanVal-cmin.minChanVal)/static_cast<double>(cmax.getBlue()-cmin.getBlue());
      double bb = cmin.maxChanVal - 1.0*bc*cmax.getBlue();
      applyHomoPixTfrm(&colorT::tfrmLinearGreyLevelScaleRGB, rc, rb, gc, gb, bc, bb);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)()) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT), colorT arg1) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT), colorT arg1, colorT arg2) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT), colorT arg1, colorT arg2, colorT arg3) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(colorT, colorT, colorT, colorT), colorT arg1, colorT arg2, colorT arg3, colorT arg4) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int), int arg1) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int), int arg1, int arg2) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int), int arg1, int arg2, int arg3) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(int, int, int, int), int arg1, int arg2, int arg3, int arg4) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double), double arg1) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double), double arg1, double arg2) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double), double arg1, double arg2, double arg3) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double),
                                                                              double arg1, double arg2, double arg3, double arg4) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double),
                                                                              double arg1, double arg2, double arg3, double arg4, double arg5) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4, arg5);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::applyHomoPixTfrm(colorT& (colorT::*HPT)(double, double, double, double, double, double),
                                                                                          double arg1, double arg2, double arg3, double arg4, double arg5, double arg6) {
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        (getPxColorRefNC(x, y).*HPT)(arg1, arg2, arg3, arg4, arg5, arg6);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::combineRamCanvasBinOp(colorT& (colorT::*HPT)(colorT),
                                                                                               const ramCanvasTpl &theCanvas,
                                                                                               intCrdT trgX, intCrdT trgY,
                                                                                               intCrdT wide, intCrdT tall,
                                                                                               intCrdT srcX, intCrdT srcY) {
    // Figure out real default width
    if(wide < 0)
      wide = numPixX-trgX;

    // Make sure wide is not wider than current canvas.
    if(wide > (numPixX-srcX))
      wide = theCanvas.getNumPixX()-srcX;

    // Make sure wide is not wider than given canvas.
    if(wide > (theCanvas.getNumPixX()-srcX))
      wide = theCanvas.getNumPixX()-srcX;

    // Figure out real default tall
    if(tall < 0)
      tall = numPixY-srcY;

    // Make sure tall is not taller than current canvas.
    if(tall > (numPixY-srcY))
      tall = numPixY-srcY;

    // Make sure tall is not taller than given canvas.
    if(tall > (theCanvas.getNumPixY()-srcY))
      tall = theCanvas.getNumPixY()-srcY;

    intCrdT xMax = trgX+wide;
    intCrdT yMax = trgY+tall;
    for(intCrdT y=trgY, ys=srcY; y<yMax; y++, ys++)
      for(intCrdT x=trgX, xs=srcX; x<xMax; x++, xs++)
        (getPxColorRefNC(x, y).*HPT)(theCanvas.getPxColor(xs, ys));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawLine(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorArgType color) {
    moveTo(x2, y2);                                                           // Do this first
    intCrdT x, y;
    if(y1 == y2) {                                                            // slope = 0
      if( (y1 < 0) || (y1 >= numPixY) )                                       // . Line off canvas case
        return;
      if(x1 > x2)                                                             // . Fix point ordering
        std::swap(x1, x2);
      if(x1 < 0)                                                              // . Clip left
        x1 = 0;
      if(x2 >= numPixX)                                                       // . Clip right
        x2 = numPixX - 1;
      drawHorzLineNC(x1, x2, y1, color);                                      // . Draw Pixels
    } else if(x1 == x2) {                                                     // slope = infinity
      if( (x1 < 0) || (x1 >= numPixX) )                                       // . Line off canvas case
        return;
      if(y1 > y2)                                                             // . Fix point ordering
        std::swap(y1, y2);
      if(y1 < 0)                                                              // . Clip top
        y1 = 0;
      if(y2 >= numPixY)                                                       // . Clip bottom
        y2 = numPixY - 1;
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
        if( (y2 < 0) || (x2 < 0) || (x1 >= numPixX) || (y1 >= numPixY) )      // .. Line off canvas case
          return;
        if(x1 < 0) {                                                          // .. Clip left
          y1 = y1 - x1;
          x1 = 0;
        }
        if(y1 < 0) {                                                          // .. Clip top
          x1 = x1 - y1;
          y1 = 0;
        }
        if(x2 >= numPixX) {                                                   // .. Clip right
          y2 = y2 - (x2 - numPixX) - 1;
          x2 = numPixX - 1;
        }
        if(y2 >= numPixY) {                                                   // .. Clip bottom
          x2 = x2 - (y2 - numPixY) - 1;
          y2 = numPixY - 1;
        }
        for(x=x1,y=y1;x<=x2;y++,x++)                                          // .. Draw Pixels
          drawPointNC(x, y, color);
      } else if(dx == -dy) {                                                  // . Slope = -1
        if( (x2 < 0) || (y2 >= numPixY) || (x1 >= numPixX) || (y1 < 0) )      // .. Line off canvas case
          return;
        if(x1 < 0) {                                                          // .. Clip left
          y1 = y1 + x1;
          x1 = 0;
        }
        if(x2 >= numPixX) {                                                   // .. Clip right
          y2 = y2 + (x2 - (numPixX - 1));
          x2 = numPixX - 1;
        }
        if(y2 < 0) {                                                          // .. Clip top
          x2 = x2 + y2;
          y2 = 0;
        }
        if(y1 >= numPixY) {                                                   // .. Clip bottom
          x1 = x1 + (y1 - (numPixY - 1));
          y1 = numPixY - 1;
        }
        for(x=x1,y=y1;x<=x2;y--,x++)                                          // .. Draw Pixels
          drawPointNC(x, y, color);
      } else {                                                                // . Slope != 1, -1, 0, \infinity
        int s, dx2, dy2;
        dx2 = 2*dx;
        dy2 = 2*dy;
        if(dy > 0) {                                                          // .. Positive Slope
          if( (y2 < 0) || (x2 < 0) || (x1 >= numPixX) || (y1 >= numPixY) )    // ... Line off canvas case
            return;
          if(x1 < 0) {                                                        // ... Clip left
            y1 = (int)(1.0*y1-x1*dy/dx);
            x1 = 0;
          }
          if(y1 < 0) {                                                        // ... Clip top
            x1 = (int)(1.0*x1-y1*dx/dy);
            y1 = 0;
          }
          if(x2 >= numPixX) {                                                 // ... Clip right
            y2 = (int)((1.0*dy*(numPixX-1)+y1*dx-x1*dy)/dx);
            x2 = numPixX - 1;
          }
          if(y2 >= numPixY) {                                                 // ... Clip bottom
            x2 = (int)(((numPixY-1)*dx-y2*dx+x2*dy)/dy);
            y2 = numPixY - 1;
          }
//  MJR TODO NOTE drawLine: We use drawPoint instead of drawPointNC, can we make an off canvas decesion instead? Similar case down below.
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
          if( (x2 < 0) || (y2 >= numPixY) || (x1 >= numPixX) || (y1 < 0) )    // ... Line off canvas case
            return;
          if(x1 < 0) {                                                        // ... Clip left
            y1 = (int)(1.0*y1-x1*dy/dx);
            x1 = 0;
          }
          if(y2 < 0) {                                                        // ... Clip top
            x2 = (int)(1.0*x2-y2*dx/dy);
            y2 = 0;
          }
          if(x2 >= numPixX) {                                                 // ... Clip right
            y2 = (int)((1.0*dy*(numPixX-1)+y2*dx-x2*dy)/dx);
            x2 = numPixX - 1;
          }
          if(y1 >= numPixY) {                                                 // ... Clip bottom
            x1 = (int)(((numPixY-1)*dx-y1*dx+x1*dy)/dy);
            y1 = numPixY - 1;
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::freeCanvas() {
    newIntCoordsNC(-1, -1);
    if(pixels != NULL) {
      delete[] pixels;
      pixels=NULL;
      pixelsE=NULL;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::rePointPixels(colorT *new_pixels, intCrdT new_numPixX, intCrdT new_numPixY) {
    freeCanvas();
    newIntCoordsNC(new_numPixX, new_numPixY);
    updRealCoords();
    if(new_pixels != NULL)
      pixels = new_pixels;
    if(pixels == NULL)
      pixelsE = NULL;
    else
      pixelsE = pixels+(new_numPixX * new_numPixY);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::reallocCanvas(intCrdT numPixX_p, intCrdT numPixY_p) {
    if((numPixX_p<=0) || (numPixY_p<=0)) {
      freeCanvas();
    } else {
      if( (numPixX_p!=numPixX) || (numPixY_p!=numPixY) ) {
        colorT *new_pixels = new colorT[numPixX_p * numPixY_p];
        rePointPixels(new_pixels, numPixX_p, numPixY_p);
      } else {
        // Don't really do anything as the new size is the same as the old size...
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::resizeCanvas(intCrdT new_numPixX_p, intCrdT new_numPixY_p) {
    reallocCanvas(new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::expandCanvas(intCrdT new_numPixX_p, intCrdT new_numPixY_p, intCrdT x1, intCrdT y1, colorArgType color) {
    if( (new_numPixX_p != numPixX) || (new_numPixY_p != numPixY) ) {

      colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];

      // Fill it up with the default color.  Should only draw the ones that need it, but computers are fast...
      for(intCrdT y=0;y<new_numPixY_p;y++)
        for(intCrdT x=0;x<new_numPixX_p;x++)
          new_pixels[new_numPixX_p * (y) + (x)] = color;

      intCrdT yMax = std::min(numPixY+y1, new_numPixY_p);
      intCrdT xMax = std::min(numPixX+x1, new_numPixX_p);

      // Copy the old image to the new space.
      if ((x1 < new_numPixX_p) && (y1 < new_numPixY_p))
        for(intCrdT y=y1;y<yMax;y++)
          for(intCrdT x=x1;x<xMax;x++)
            new_pixels[new_numPixX_p * (y) + (x)] = getPxColor(x-x1, y-y1);

      rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::cropCanvas(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2) {
    if( !isCliped(x1, y1) && !isCliped(x2, y2) ) {
      if(x1 > x2)
        std::swap(x1, x2);
      if(y1 > y2)
        std::swap(y1, y2);
      intCrdT xp, yp, x, y;
      intCrdT new_numPixX_p = x2-x1+1;
      intCrdT new_numPixY_p = y2-y1+1;
      colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];

      // Copy the old image to the new space.
      for(y=y1,yp=0;y<=y2;y++,yp++)
        for(x=x1,xp=0;x<=x2;x++,xp++)
          new_pixels[new_numPixX_p * yp + xp] = getPxColor(x, y);

      rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::flipHorz() {
    for(intCrdT y=0; y<numPixY/2; y++)
      for(intCrdT x=0; x<numPixX; x++) {
        colorT aColor = getPxColor(x, numPixY-y-1);
        drawPointNC(x, numPixY-y-1, getPxColor(x, y));
        drawPointNC(x, y, aColor);
      }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::flipVert() {
    for(intCrdT x=0; x<numPixX/2; x++)
      for(intCrdT y=0; y<numPixY; y++) {
        colorT aColor = getPxColor(numPixX-x-1, y);
        drawPointNC(numPixX-x-1, y, getPxColor(x, y));
        drawPointNC(x, y, aColor);
      }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::flipTranspose() {
    intCrdT new_numPixX_p = numPixY;
    intCrdT new_numPixY_p = numPixX;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        new_pixels[new_numPixX_p * (x/*y-crd*/) + (y/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::rotate90CW() {
    intCrdT new_numPixX_p = numPixY;
    intCrdT new_numPixY_p = numPixX;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        new_pixels[new_numPixX_p * (numPixX-x-1/*y-crd*/) + (y/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::rotate90CCW() {
    intCrdT new_numPixX_p = numPixY;
    intCrdT new_numPixY_p = numPixX;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        new_pixels[new_numPixX_p * (x/*y-crd*/) + (numPixY-y-1/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::rotate180() {
    intCrdT new_numPixX_p = numPixX;
    intCrdT new_numPixY_p = numPixY;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        new_pixels[new_numPixX_p * (numPixY-y-1/*y-crd*/) + (numPixX-x-1/*x-crd*/)] = getPxColor(x, y);
    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline typename ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::endianType
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::platformEndianness() {
    unsigned int endiannessProbe = 1;
    if(((char *)&endiannessProbe)[0]) {
      return endianType::LITTLE;
    } else {
      return endianType::BIG;
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::writeUIntToStream(std::ostream& oStream,
                                                                               typename ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::endianType endianness,
                                                                               int numBytes,
                                                                               uint64_t data) {
    if(numBytes>0) {
      if (numBytes == 1) {
        uint8_t tmp = (data & 0xff);
        oStream.write((const char *)&tmp, 1);
      } else {
        if (numBytes<9) {
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
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::colorizeFltCanvas(std::function<colorT (fltCrdT, fltCrdT)> cFun) {
    for(intCrdT yi=0;yi<numPixY;yi++) {
      for(intCrdT xi=0;xi<numPixX;xi++) {
        fltCrdT xf = int2realX(xi);
        fltCrdT yf = int2realY(yi);
        colorT aColor = cFun(xf, yf);
        drawPoint(xi, yi, aColor);
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::colorizeFltCanvas(std::function<colorT (pointFltType)> cFun) {
    for(intCrdT yi=0;yi<numPixY;yi++) {
      for(intCrdT xi=0;xi<numPixX;xi++) {
        pointFltType xyPt(int2realX(xi), int2realY(yi));
        colorT aColor = cFun(xyPt);
        drawPoint(xi, yi, aColor);
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::colorizeIntCanvas(std::function<colorT (intCrdT, intCrdT)> cFun) {
    for(intCrdT yi=0;yi<numPixY;yi++) {
      for(intCrdT xi=0;xi<numPixX;xi++) {
        colorT aColor = cFun(xi, yi);
        drawPoint(xi, yi, aColor);
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::colorizeIntCanvas(std::function<colorT (pointIntType)> cFun) {
    for(intCrdT yi=0;yi<numPixY;yi++) {
      for(intCrdT xi=0;xi<numPixX;xi++) {
        pointIntType xyPt(xi, yi);
        colorT aColor = cFun(xyPt);
        drawPoint(xi, yi, aColor);
      }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::writeTGAfile(std::string fileName) {

    std::ofstream outStream;
    outStream.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (outStream.is_open())
      outStream.imbue(std::locale::classic());
    else 
      return 1;

    if(numPixX < 1)      // too skinny
      return 6;
    if(numPixX > 0xffff) // too wide
      return 7;
    if(numPixY < 1)      // too short
      return 8;
    if(numPixY > 0xffff) // too tall
      return 9;

    /* Write header */
    writeUIntToStream(outStream, endianType::LITTLE, 1, 0);       // id length
    writeUIntToStream(outStream, endianType::LITTLE, 1, 0);       // colourmaptype
    writeUIntToStream(outStream, endianType::LITTLE, 1, 2);       // datatypecode: 2 == Truecolor RGB 8-bit, 3 == Monochrome
    writeUIntToStream(outStream, endianType::LITTLE, 2, 0);       // 16-bit colourmaporigin
    writeUIntToStream(outStream, endianType::LITTLE, 2, 0);       // colurmaplength
    writeUIntToStream(outStream, endianType::LITTLE, 1, 0);       // colormapdepth
    writeUIntToStream(outStream, endianType::LITTLE, 2, 0);       // 16-bit x_origin
    writeUIntToStream(outStream, endianType::LITTLE, 2, 0);       // 16-bit y_origon
    writeUIntToStream(outStream, endianType::LITTLE, 2, numPixX); // Width
    writeUIntToStream(outStream, endianType::LITTLE, 2, numPixY); // Height
    writeUIntToStream(outStream, endianType::LITTLE, 1, 24);      // bits per pixel
    writeUIntToStream(outStream, endianType::LITTLE, 1, 0);       // imagedescriptor

    /* Write data */
    intCrdT x, y;
    /* Normally I would not resort to such trickery; however, this is an exception.  The following for loop is equivalent to switching between the two forms
       "for(y=(numPixY-1); y>=0; y--)" and "for(y=0; y<numPixY; y++)". */
    bool yNat = isIntAxOrientationNaturalY();
    bool xNat = isIntAxOrientationNaturalX();
    for((yNat?y=0:y=(numPixY-1)); (yNat?y<numPixY:y>=0); (yNat?y++:y--)) {
      for((xNat?x=0:x=(numPixX-1)); (xNat?x<numPixX:x>=0); (xNat?x++:x--)) {
        colorT aColor = getPxColorRefNC(x, y);
        writeUIntToStream(outStream, endianType::LITTLE, 1, aColor.getChan_byte(aColor.bestBlueChan()));
        writeUIntToStream(outStream, endianType::LITTLE, 1, aColor.getChan_byte(aColor.bestGreenChan()));
        writeUIntToStream(outStream, endianType::LITTLE, 1, aColor.getChan_byte(aColor.bestRedChan()));
      }
    }
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::writeRAWfile(std::string fileName) {
    auto tmp = rcConverterIdentity<ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>>(*this);
    return writeRAWfile(fileName, tmp);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    template <class rcConT>
    inline int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::writeRAWfile(std::string fileName, rcConT rcConverter) {

    std::ofstream outStream;
    outStream.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (outStream.is_open()) 
      outStream.imbue(std::locale::classic());
    else 
      return 1;

    outStream << "MJRRAW\n";                                                                    //  7   7
    outStream << std::setw(19) << std::setfill('0') << rcConverter.getNumPixX()         << "x"; // 20  27
    outStream << std::setw(19) << std::setfill('0') << rcConverter.getNumPixY()         << "y"; // 20  47
    outStream << std::setw(27) << std::setfill('0') << rcConT::colorType::channelCount  << "c"; // 28  75
    outStream << std::setw(11) << std::setfill('0') << rcConT::colorType::bitsPerChan   << "b"; // 12  87
    outStream << (rcConT::colorType::chanIsUnsigned ? "UNS" : "SGN")                    << "s"; //  4  91
    outStream << (rcConT::colorType::chanIsInt ? "INT" : "FLT")                         << "t"; //  4  95
    outStream << (platformEndianness() == endianType::LITTLE ? "LTL" : "BIG")           << "i"; //  4  99
    outStream << "\n";                                                                          //  1 100

    intCrdT x, y;
    /* Normally I would not resort to such trickery; however, this is an exception.  The following for loop is equivalent to switching between the two forms
       "for(y=(rcConverter.getNumPixY()-1); y>=0; y--)" and "for(y=0; y<rcConverter.getNumPixY(); y++)". */
    bool yNat = !(rcConverter.isIntAxOrientationNaturalY());
    bool xNat = rcConverter.isIntAxOrientationNaturalX();
    for((yNat?y=0:y=(rcConverter.getNumPixY()-1)); (yNat?y<rcConverter.getNumPixY():y>=0); (yNat?y++:y--)) {
      for((xNat?x=0:x=(rcConverter.getNumPixX()-1)); (xNat?x<rcConverter.getNumPixX():x>=0); (xNat?x++:x--)) {
        typename rcConT::colorType aColor = rcConverter.getPxColorNC(x, y);
        for(int c=0; c<aColor.channelCount; c++) {
          typename rcConT::colorType::channelType aChanValue = aColor.getChan(c);
          outStream.write((const char *)&aChanValue, sizeof(colorChanType));
        }
      }
    }
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::writeTIFFfile(std::string fileName, bool markAlpha) {
    rcConverterIdentity<ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>> tmp(*this);
    return writeTIFFfile(fileName, tmp, markAlpha);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    template <class rcConT> 
    inline int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::writeTIFFfile(std::string fileName, rcConT rcConverter, bool markAlpha) {

    if(rcConT::colorType::bitsPerChan < 8)                   // channels too thin
      return 2;
    if(rcConT::colorType::bitsPerChan > 0xffff)              // channels too fat
      return 3;
    if(rcConT::colorType::channelCount < 1)                  // too few channels
      return 4;
    if(rcConT::colorType::channelCount > 0xffff)             // too many channels
      return 5;
    if(rcConverter.getNumPixX() < 1)                         // too skinny
      return 6;
    if(rcConverter.getNumPixX() > 0x7fffffff)                // too wide
      return 7;
    if(rcConverter.getNumPixY() < 1)                         // too short
      return 8;
    if(rcConverter.getNumPixY() > 0x7fffffff)                // too tall
      return 9;
    unsigned long bytesPerRow = rcConverter.getNumPixX() * rcConT::colorType::bitsPerChan / 8ul * rcConT::colorType::channelCount;
    if(bytesPerRow > 0xffffffff)                             // rows too big
      return 10;
    if(bytesPerRow * rcConverter.getNumPixY() > 0xfffffffff) // image too big
      return 11;

    // //grep -E '^#define[[:space:]]+(TIFF_BIGENDIAN|TIFF_LITTLEENDIAN|PHOTOMETRIC_RGB|PHOTOMETRIC_MINISBLACK|PLANARCONFIG_CONTIG|ORIENTATION_TOPLEFT|RESUNIT_NONE|SAMPLEFORMAT_UINT|SAMPLEFORMAT_IEEEFP)' /mingw64/include/tiff.h
    const uint16_t tcTIFF_BIGENDIAN          = 0x4d4d;  /* Magic number for big endian */
    const uint16_t tcTIFF_LITTLEENDIAN       = 0x4949;  /* Magic number for little endian */
    const uint16_t tcPHOTOMETRIC_MINISBLACK  = 1;       /* min value is black */
    const uint16_t tcPHOTOMETRIC_RGB         = 2;       /* RGB color model */
    const uint16_t tcORIENTATION_TOPLEFT     = 1;       /* row 0 top, col 0 lhs */
    const uint16_t tcPLANARCONFIG_CONTIG     = 1;       /* single image plane */
    const uint16_t tcRESUNIT_NONE            = 1;       /* no meaningful units */
    const uint16_t tcSAMPLEFORMAT_UINT       = 1;       /* !unsigned integer data */
    const uint16_t tcSAMPLEFORMAT_IEEEFP     = 3;       /* !IEEE floating point data */

    // //grep -E '^#define[[:space:]]+TIFFTAG_(IMAGEWIDTH|IMAGELENGTH|BITSPERSAMPLE|PHOTOMETRIC|ORIENTATION|SAMPLESPERPIXEL|PLANARCONFIG|RESOLUTIONUNIT|COMPRESSION|STRIPOFFSETS|ROWSPERSTRIP|STRIPBYTECOUNTS|XRESOLUTION|YRESOLUTION|EXTRASAMPLES|SAMPLEFORMAT)' /mingw64/include/tiff.h
    // const uint16_t tcTIFFTAG_IMAGEWIDTH      =      256; /* image width in pixels */
    // const uint16_t tcTIFFTAG_IMAGELENGTH     =      257; /* image height in pixels */
    // const uint16_t tcTIFFTAG_BITSPERSAMPLE   =      258; /* bits per channel (sample) */
    // const uint16_t tcTIFFTAG_COMPRESSION     =      259; /* data compression technique */
    // const uint16_t tcTIFFTAG_PHOTOMETRIC     =      262; /* photometric interpretation */
    // const uint16_t tcTIFFTAG_STRIPOFFSETS    =      273; /* offsets to data strips */
    // const uint16_t tcTIFFTAG_ORIENTATION     =      274; /* +image orientation */
    // const uint16_t tcTIFFTAG_SAMPLESPERPIXEL =      277; /* samples per pixel */
    // const uint16_t tcTIFFTAG_ROWSPERSTRIP    =      278; /* rows per strip of data */
    // const uint16_t tcTIFFTAG_STRIPBYTECOUNTS =      279; /* bytes counts for strips */
    // const uint16_t tcTIFFTAG_XRESOLUTION     =      282; /* pixels/resolution in x */
    // const uint16_t tcTIFFTAG_YRESOLUTION     =      283; /* pixels/resolution in y */
    // const uint16_t tcTIFFTAG_PLANARCONFIG    =      284; /* storage organization */
    // const uint16_t tcTIFFTAG_RESOLUTIONUNIT  =      296; /* units of resolutions */
    // const uint16_t tcTIFFTAG_EXTRASAMPLES    =      338; /* !info about extra samples */
    // const uint16_t tcTIFFTAG_SAMPLEFORMAT    =      339; /* !data sample format */

    endianType fe          = platformEndianness();                                                         // Endian Type
    uint16_t   endianNum   = (fe == endianType::LITTLE ? tcTIFF_LITTLEENDIAN : tcTIFF_BIGENDIAN);          // Endianness Magic Number
    uint32_t   tifWidth    = (uint32_t)rcConverter.getNumPixX();                                           // ImageWidth
    uint32_t   tifLength   = (uint32_t)rcConverter.getNumPixY();                                           // ImageLength & RowsPerStrip
    uint32_t   tifSPP      = (uint32_t)rcConT::colorType::channelCount;                                    // SamplesPerPixel
    uint16_t   tifBPS      = (uint16_t)(rcConT::colorType::bitsPerChan);                                   // BitsPerSample
    uint32_t   bytePerSmp  = tifBPS / 8;                                                                   // Bytes per sample
    uint32_t   tifSBC      = tifLength * tifWidth * bytePerSmp * tifSPP;                                   // StripByteCounts
    bool       haveRGB     = tifSPP>=3;                                                                    // TRUE if this image has RGB data (at least 3 channels)
    uint16_t   numImgSmp   = (haveRGB ? 3 : 1);                                                            // Number of samples used for image data (3 for RGB, 1 otherwise)
    uint16_t   tifPMI      = (haveRGB ? tcPHOTOMETRIC_RGB : tcPHOTOMETRIC_MINISBLACK);                     // PhotometricInterp
    uint16_t   tifPC       = tcPLANARCONFIG_CONTIG;                                                        // Planarconfig
    uint16_t   tifOri      = tcORIENTATION_TOPLEFT;                                                        // Orientation
    uint16_t   tifResU     = tcRESUNIT_NONE;                                                               // Resolution Unit
    bool       haveXS      = !((tifSPP==1) || (tifSPP==3));                                                // TRUE if this image has ExtraSamples data
    bool       haveManyXS  = tifSPP>4;                                                                     // TRUE if this image has MORE THAN ONE ExtraSamples data
    uint16_t   numTags     = 1+14 + (haveXS ? 1 : 0);                                                      // Number fo tags in this image
    bool       haveManyBPS = tifSPP>1;                                                                     // TRUE if this image has MORE THAN ONE BitsPerSample data
    uint32_t   numXS       = tifSPP - numImgSmp;                                                           // Number of extra samples
    uint32_t   xResOff     = 14 + 12 * numTags;                                                            // XResolution offset
    uint32_t   yResOff     = xResOff + 8;                                                                  // YResolution offset
    uint32_t   bpsOff      = yResOff + 8;                                                                  // BitsPerSample offset
    uint32_t   xsOff       = bpsOff  + (haveManyBPS ? 2 * tifSPP : 0);                                     // ExtraSamples offset
    uint32_t   imgOff      = xsOff + (haveManyXS  ? 2 * numXS : 0);                                        // Image Data offset
    uint16_t   sampFmt     = (rcConT::colorType::chanIsInt ? tcSAMPLEFORMAT_UINT : tcSAMPLEFORMAT_IEEEFP); // SampleFormat (1=unsigned, 3=IEEE)

    std::ofstream outStream;
    outStream.open(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
    if (outStream.is_open()) 
      outStream.imbue(std::locale::classic());
    else 
      return 1;
    
    writeUIntToStream(outStream, fe, 2, endianNum);                                                                                 // Write: little endian magic number
    writeUIntToStream(outStream, fe, 2, 42);                                                                                        // Write: TIFF magic number
    writeUIntToStream(outStream, fe, 4, 8);                                                                                         // Write: IDF offset
    writeUIntToStream(outStream, fe, 2, numTags);                                                                                   // Tag Count
    writeUIntToStream(outStream, fe, 2, 0x100); writeUIntToStream(outStream, fe, 2, 4);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, tifWidth);                                          // ImageWidth
    writeUIntToStream(outStream, fe, 2, 0x101); writeUIntToStream(outStream, fe, 2, 4);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, tifLength);                                         // ImageLength
    writeUIntToStream(outStream, fe, 2, 0x102); writeUIntToStream(outStream, fe, 2, 3);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 2, tifBPS);    writeUIntToStream(outStream, fe, 2, 0); // BitsPerSample
    writeUIntToStream(outStream, fe, 2, 0x103); writeUIntToStream(outStream, fe, 2, 3);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 2, 1);         writeUIntToStream(outStream, fe, 2, 0); // Compression
    writeUIntToStream(outStream, fe, 2, 0x106); writeUIntToStream(outStream, fe, 2, 3);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 2, tifPMI);    writeUIntToStream(outStream, fe, 2, 0); // PhotometricIn
    writeUIntToStream(outStream, fe, 2, 0x111); writeUIntToStream(outStream, fe, 2, 4);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, imgOff);                                            // StripOffsets
    writeUIntToStream(outStream, fe, 2, 0x112); writeUIntToStream(outStream, fe, 2, 3);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 2, tifOri);    writeUIntToStream(outStream, fe, 2, 0); // Orientation
    writeUIntToStream(outStream, fe, 2, 0x115); writeUIntToStream(outStream, fe, 2, 3);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 2, tifSPP);    writeUIntToStream(outStream, fe, 2, 0); // SamplesPerPixel
    writeUIntToStream(outStream, fe, 2, 0x116); writeUIntToStream(outStream, fe, 2, 4);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, tifLength);                                         // RowsPerStrip
    writeUIntToStream(outStream, fe, 2, 0x117); writeUIntToStream(outStream, fe, 2, 4);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, tifSBC);                                            // StripByteCounts
    writeUIntToStream(outStream, fe, 2, 0x11A); writeUIntToStream(outStream, fe, 2, 5);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, xResOff);                                           // XResolution
    writeUIntToStream(outStream, fe, 2, 0x11B); writeUIntToStream(outStream, fe, 2, 5);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, yResOff);                                           // YResolution
    writeUIntToStream(outStream, fe, 2, 0x11C); writeUIntToStream(outStream, fe, 2, 3);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 2, tifPC);     writeUIntToStream(outStream, fe, 2, 0); // PlanarConf
    writeUIntToStream(outStream, fe, 2, 0x128); writeUIntToStream(outStream, fe, 2, 3);
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 2, tifResU);   writeUIntToStream(outStream, fe, 2, 0); // ResolutionUnit
    if(haveXS) {                                                                                                                    // ExtraSamples
      if(haveManyXS) {
        writeUIntToStream(outStream, fe, 2, 0x152); writeUIntToStream(outStream, fe, 2, 3);
        writeUIntToStream(outStream, fe, 4, numXS); writeUIntToStream(outStream, fe, 4, xsOff);
      } else {
        if(markAlpha) {                                                                                                             // is chan4alpha
          writeUIntToStream(outStream, fe, 2, 0x152); writeUIntToStream(outStream, fe, 2, 3);
          writeUIntToStream(outStream, fe, 4, 1);     writeUIntToStream(outStream, fe, 4, 1);
        } else {
          writeUIntToStream(outStream, fe, 2, 0x152); writeUIntToStream(outStream, fe, 2, 3);
          writeUIntToStream(outStream, fe, 4, 1);     writeUIntToStream(outStream, fe, 4, 0);
        }
      }
    }

    writeUIntToStream(outStream, fe, 2, 0x153);
    writeUIntToStream(outStream, fe, 2, 3);     writeUIntToStream(outStream, fe, 4, 1);
    writeUIntToStream(outStream, fe, 2, sampFmt); writeUIntToStream(outStream, fe, 2, 0);                                           // SampleFormat

    writeUIntToStream(outStream, fe, 4, 0);                                                                                         // IFD END
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, 1);                                                 // XResolutionData
    writeUIntToStream(outStream, fe, 4, 1); writeUIntToStream(outStream, fe, 4, 1);                                                 // YResolutionData
    if(haveManyBPS) {                                                                                                               // YResolutionData
      for(unsigned int i=0; i<tifSPP; i++)
        writeUIntToStream(outStream, fe, 2, tifBPS);
    }
    if(haveManyXS)                                                                                                                  // ExtraSamplesData (can't be RGBA is on xtra, not many)
      for(unsigned int i=0; i<numXS; i++)
        writeUIntToStream(outStream, fe, 4, 0);
                                                                                                                                    // Image data
    intCrdT x, y;
    bool yNat = !(rcConverter.isIntAxOrientationNaturalY());
    bool xNat = rcConverter.isIntAxOrientationNaturalX();
    for((yNat?y=0:y=(rcConverter.getNumPixY()-1)); (yNat?y<rcConverter.getNumPixY():y>=0); (yNat?y++:y--)) {
      for((xNat?x=0:x=(rcConverter.getNumPixX()-1)); (xNat?x<rcConverter.getNumPixX():x>=0); (xNat?x++:x--)) {
        typename rcConT::colorType aColor = rcConverter.getPxColorNC(x, y);
        for(int c=0; c<aColor.channelCount; c++) {
          typename rcConT::colorType::channelType aChanValue = aColor.getChan(c);
          if (rcConT::colorType::chanIsInt)
            writeUIntToStream(outStream, fe, bytePerSmp, aChanValue);                                                               // Sample Data
          else
            outStream.write((const char *)&aChanValue, bytePerSmp);                                                                 // Sample Data
        }
      }
    }

    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::exportRasterData(void* &rasterData,
                                                                              intCrdT x1,  intCrdT y1,
                                                                              intCrdT x2,  intCrdT y2,
                                                                              int redChan, int greenChan, int blueChan, int alphaChan) {
    if(x1 > x2)   // Get x1 < x2
      std::swap(x1, x2);
    if(y1 > y2)   // Get y1 < y2
      std::swap(y1, y2);

    if(x1 <  0)        return 1; // Outside of canvas
    if(x2 >= numPixX)  return 1; // Outside of canvas
    if(y1 <  0)        return 1; // Outside of canvas
    if(y2 >= numPixY)  return 1; // Outside of canvas
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
        if(redChan   >= 0) curPixComp[redChan]   = aColor.getChan_byte(aColor.bestRedChan());
        if(greenChan >= 0) curPixComp[greenChan] = aColor.getChan_byte(aColor.bestGreenChan());
        if(blueChan  >= 0) curPixComp[blueChan]  = aColor.getChan_byte(aColor.bestBlueChan());
        if(alphaChan >= 0) curPixComp[alphaChan] = aColor.getChan_byte(aColor.bestAlphaChan());
        curPixComp += bytesPerPix;
      } /* end for x */
    } /* end for y */

    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline intCrdT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::real2intX(fltCrdT x) const {
    if(realAxOrientationX == realAxisOrientation::NATURAL)
      return static_cast<intCrdT>((static_cast<fltCrdT>(x) - minRealX) / pixWidX);
    else
      return static_cast<intCrdT>((maxRealX - static_cast<fltCrdT>(x)) / pixWidX);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline intCrdT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::real2intY(fltCrdT y) const {
    if(realAxOrientationY == realAxisOrientation::NATURAL)
      return static_cast<intCrdT>((static_cast<fltCrdT>(y) - minRealY) / pixWidY);
    else
      return static_cast<intCrdT>((maxRealY - static_cast<fltCrdT>(y)) / pixWidY);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline fltCrdT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::int2realX(intCrdT x) {
    if(realAxOrientationX == realAxisOrientation::NATURAL)
      return static_cast<fltCrdT>(x) * pixWidX + minRealX;
    else
      return maxRealX - static_cast<fltCrdT>(x) * pixWidX;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline fltCrdT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::int2realY(intCrdT y) {
    if(realAxOrientationY == realAxisOrientation::NATURAL)
      return static_cast<fltCrdT>(y) * pixWidY + minRealY;
    else
      return maxRealY - static_cast<fltCrdT>(y) * pixWidY;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    colorT*
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::clonePixels() {
    colorT *pixelsCopy = new colorT[numPixX * numPixY];
    for(intCrdT y=0; y<numPixY; y++)
      for(intCrdT x=0; x<numPixX; x++)
        pixelsCopy[numPixX * y + x] = getPxColorNC(x, y);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline colorT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::getPxColor(intCrdT x, intCrdT y) const {
    if(isOnCanvas(x, y)) [[likely]]
      return pixels[numPixX * y + x];
    else
      return colorT().setToBlack();
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline colorT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::getPxColorInterpolate(double x, double y, interpolationType interpMethod) {
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    colorT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::getPxColorInterpBLin(double x, double y) {
    double x1 = std::floor(x);
    double y1 = std::floor(y);
    double x2 = std::ceil(x);
    double y2 = std::ceil(y);

    intCrdT x1i = static_cast<intCrdT>(x1);
    intCrdT y1i = static_cast<intCrdT>(y1);
    intCrdT x2i = static_cast<intCrdT>(x2);
    intCrdT y2i = static_cast<intCrdT>(y2);

    colorT cF;

    if ((x1i >= 0) && (y1i >= 0) && (x2i < numPixX) && (y2i < numPixY)) {
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
      c1.linearInterpolate(wH, getPxColorRefNC(x1i, y1i), getPxColorRefNC(x2i, y1i));
      c2.linearInterpolate(wH, getPxColorRefNC(x1i, y2i), getPxColorRefNC(x2i, y2i));
      cF.linearInterpolate(wV, c1, c2);
    } else {
      cF.setToBlack();
    }
    return cF;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline colorT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::getPxColorInterpTrunc(double x, double y) {
    return getPxColor(static_cast<intCrdT>(std::trunc(x)), static_cast<intCrdT>(std::trunc(y)));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline colorT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::getPxColorInterpNear(double x, double y) {
    return getPxColor(static_cast<intCrdT>(std::round(x)), static_cast<intCrdT>(std::round(y)));
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline colorT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::getPxColorInterpAvg9(double x, double y) {
    intCrdT xi = static_cast<intCrdT>(std::round(x));
    intCrdT yi = static_cast<intCrdT>(std::round(y));
    colorT newColor;
    for(int chan=0; chan<colorT::channelCount; chan++) {
      colorChanArithSDPType newChanValue = 0;
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    colorT
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::getPxColorInterpAvg4(double x, double y) {
    double x1 = std::floor(x);
    double y1 = std::floor(y);
    double x2 = std::ceil(x);
    double y2 = std::ceil(y);

    intCrdT x1i = static_cast<intCrdT>(x1);
    intCrdT y1i = static_cast<intCrdT>(y1);
    intCrdT x2i = static_cast<intCrdT>(x2);
    intCrdT y2i = static_cast<intCrdT>(y2);

    if ((x1i >= 0) && (y1i >= 0) && (x2i < numPixX) && (y2i < numPixY)) {

      colorT c1 = pixels[numPixX * y1i + x1i];
      c1.tfrmMean(pixels[numPixX * y1i + x2i]);

      colorT c2 = pixels[numPixX * y2i + x1i];
      c2.tfrmMean(pixels[numPixX * y2i + x2i]);

      c1.tfrmMean(c2);

      return c1;
    } else {
      return colorT().setToBlack();
    }
  }

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
//   requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
//     void
//     ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::triangleEdger(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT* pts) {
//     moveTo(x2, y2);                                                           // Do this first
//     intCrdT x, y;
//     if(y1 == y2) {                                                            // slope = 0
//       if( (y1 < 0) || (y1 >= numPixY) )                                       // . Line off canvas case
//         return;
//       if(x1 > x2)                                                             // . Fix point ordering
//         std::swap(x1, x2);
//       if(x1 < 0)                                                              // . Clip left
//         x1 = 0;
//       if(x2 >= numPixX)                                                       // . Clip right
//         x2 = numPixX - 1;
//       //drawHorzLineNC(x1, x2, y1, color);                                      // . Draw Pixels
//       return;  // mark edge
//     } else if(x1 == x2) {                                                     // slope = infinity
//       if( (x1 < 0) || (x1 >= numPixX) )                                       // . Line off canvas case
//         return;
//       if(y1 > y2)                                                             // . Fix point ordering
//         std::swap(y1, y2);
//       if(y1 < 0)                                                              // . Clip top
//         y1 = 0;
//       if(y2 >= numPixY)                                                       // . Clip bottom
//         y2 = numPixY - 1;
//       //drawVertLineNC(y1, y2, x1, color);                                      // . Draw Pixels
//       for(y=y1; y<=y2; y++) pts[y] = x1;  // mark edge
//     } else {                                                                  // Slope is not infinity or 0...
//       int dx, dy;
//       if(x1 > x2) {                                                           // . Fix point ordering
//         std::swap(x1, x2);
//         std::swap(y1, y2);
//       }
//       dx = x2 - x1;                                                           // . Compute the slope
//       dy = y2 - y1;
//       if(dx == dy) {                                                          // . Slope = 1
//         if( (y2 < 0) || (x2 < 0) || (x1 >= numPixX) || (y1 >= numPixY) )      // .. Line off canvas case
//           return;
//         if(x1 < 0) {                                                          // .. Clip left
//           y1 = y1 - x1;
//           x1 = 0;
//         }
//         if(y1 < 0) {                                                          // .. Clip top
//           x1 = x1 - y1;
//           y1 = 0;
//         }
//         if(x2 >= numPixX) {                                                   // .. Clip right
//           y2 = y2 - (x2 - numPixX) - 1;
//           x2 = numPixX - 1;
//         }
//         if(y2 >= numPixY) {                                                   // .. Clip bottom
//           x2 = x2 - (y2 - numPixY) - 1;
//           y2 = numPixY - 1;
//         }
//         for(x=x1,y=y1;x<=x2;y++,x++)                                          // .. Draw Pixels
//           //drawPointNC(x, y, color);
//           pts[y] = x; // mark edge
//       } else if(dx == -dy) {                                                  // . Slope = -1
//         if( (x2 < 0) || (y2 >= numPixY) || (x1 >= numPixX) || (y1 < 0) )      // .. Line off canvas case
//           return;
//         if(x1 < 0) {                                                          // .. Clip left
//           y1 = y1 + x1;
//           x1 = 0;
//         }
//         if(x2 >= numPixX) {                                                   // .. Clip right
//           y2 = y2 + (x2 - (numPixX - 1));
//           x2 = numPixX - 1;
//         }
//         if(y2 < 0) {                                                          // .. Clip top
//           x2 = x2 + y2;
//           y2 = 0;
//         }
//         if(y1 >= numPixY) {                                                   // .. Clip bottom
//           x1 = x1 + (y1 - (numPixY - 1));
//           y1 = numPixY - 1;
//         }
//         for(x=x1,y=y1;x<=x2;y--,x++)                                          // .. Draw Pixels
//           //drawPointNC(x, y, color);
//           pts[y] = x; // mark edge
//       } else {                                                                // . Slope != 1, -1, 0, \infinity
//         int s, dx2, dy2;
//         dx2 = 2*dx;
//         dy2 = 2*dy;
//         if(dy > 0) {                                                          // .. Positive Slope
//           if( (y2 < 0) || (x2 < 0) || (x1 >= numPixX) || (y1 >= numPixY) )    // ... Line off canvas case
//             return;
//           if(x1 < 0) {                                                        // ... Clip left
//             y1 = (int)(1.0*y1-x1*dy/dx);
//             x1 = 0;
//           }
//           if(y1 < 0) {                                                        // ... Clip top
//             x1 = (int)(1.0*x1-y1*dx/dy);
//             y1 = 0;
//           }
//           if(x2 >= numPixX) {                                                 // ... Clip right
//             y2 = (int)((1.0*dy*(numPixX-1)+y1*dx-x1*dy)/dx);
//             x2 = numPixX - 1;
//           }
//           if(y2 >= numPixY) {                                                 // ... Clip bottom
//             x2 = (int)(((numPixY-1)*dx-y2*dx+x2*dy)/dy);
//             y2 = numPixY - 1;
//           }
//           if(dx > dy) {                                                       // ... 0 < Slope < 1
//             s = dy2 - dx;
//             x=x1;
//             y=y1;
//             while(x<=x2) {                                                    // .... Draw Line
//               //drawPoint(x, y, color);
//               pts[y] = x; // mark edge
//               if(s < 0) {
//                 s += dy2;
//               } else {
//                 y++;
//                 s += dy2 - dx2;
//               }
//               x++;
//             }
//           } else {                                                            // ... 1 < Slope < infinity
//             s = dy - dx2;
//             x=x1;
//             y=y1;
//             while(y<=y2) {                                                    // .... Draw Line
//               //drawPoint(x, y, color);
//               pts[y] = x; // mark edge
//               if(s > 0) {
//                 s -= dx2;
//               } else {
//                 x++;
//                 s += dy2 - dx2;
//               }
//               y++;
//             }
//           }
//         } else {                                                              // .. Negative Slope
//           if( (x2 < 0) || (y2 >= numPixY) || (x1 >= numPixX) || (y1 < 0) )    // ... Line off canvas case
//             return;
//           if(x1 < 0) {                                                        // ... Clip left
//             y1 = (int)(1.0*y1-x1*dy/dx);
//             x1 = 0;
//           }
//           if(y2 < 0) {                                                        // ... Clip top
//             x2 = (int)(1.0*x2-y2*dx/dy);
//             y2 = 0;
//           }
//           if(x2 >= numPixX) {                                                 // ... Clip right
//             y2 = (int)((1.0*dy*(numPixX-1)+y2*dx-x2*dy)/dx);
//             x2 = numPixX - 1;
//           }
//           if(y1 >= numPixY) {                                                 // ... Clip bottom
//             x1 = (int)(((numPixY-1)*dx-y1*dx+x1*dy)/dy);
//             y1 = numPixY - 1;
//           }
//           if(dx > -dy) {                                                      // ... 0 > Slope > -infinity
//             s = dy2 + dx;
//             x=x1;
//             y=y1;
//             while(x<=x2) {                                                    // .... Draw Line
//               //drawPoint(x, y, color);
//               pts[y] = x; // mark edge
//               if(s > 0) {
//                 s += dy2;
//               } else {
//                 y--;
//                 s += dy2 + dx2;
//               }
//               x++;
//             }
//           } else {                                                            // ... -1 > Slope > -inf
//             s = dy + dx2;
//             x=x1;
//             y=y1;
//             while(y>=y2) {                                                    // .... Draw Line
//               //drawPoint(x, y, color);
//               pts[y] = x; // mark edge
//               if(s < 0) {
//                 s += dx2;
//               } else {
//                 x++;
//                 s += dy2 + dx2;
//               }
//               y--;
//             }
//           }
//         }
//       }
//     }
//   }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::triangleEdger(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT* pts, bool findMin) {
    // This code is essentially the line drawing code with some simplifications.
    intCrdT x, y;
    if(x1 == x2) {                                                            // slope = infinity
      if(y1 > y2)                                                             // Fix point ordering
        std::swap(y1, y2);
      for(y=y1; y<=y2; y++)                                                   // Draw PIxels: drawVertLineNC(y1, y2, x1, color);
        pts[y]=x1; // set bound
    } else {                                                                  // Slope is not infinity or 0...
      int dx, dy;
      if(x1 > x2) {                                                           // Fix point ordering
        std::swap(x1, x2);
        std::swap(y1, y2);
      }
      dx = x2 - x1;                                                           // Compute the slope
      dy = y2 - y1;
      if(dx == dy) {                                                          // Slope = 1
        for(x=x1,y=y1;x<=x2;y++,x++)                                         // Draw Pixels
          pts[y]=x; // set bound
      } else if(dx == -dy) {                                                  // Slope = -1
        for(x=x1,y=y1;x<=x2;y--,x++)                                          // Draw Pixels
          pts[y]=x; // set bound
      } else {                                                                // Slope != 1, -1, 0, \infinity
        int s, dx2, dy2;
        dx2 = 2*dx;
        dy2 = 2*dy;
        if(dy > 0) {                                                          // Positive Slope
          if(dx > dy) {                                                       // 0 < Slope < 1
            if (findMin) {
              s = dy2 - dx;
              x=x1;
              y=y1;
              intCrdT lastY=y-1;
              while(x<=x2) {                                                    // Draw Line
                if (y != lastY)
                  pts[y]=x; // set bound
                lastY = y;
                if(s < 0) {
                  s += dy2;
                } else {
                  y++;
                  s += dy2 - dx2;
                }
                x++;
              }
            } else { // works.
              s = dy2 - dx;
              x=x1;
              y=y1;
              while(x<=x2) {                                                    // Draw Line
                pts[y]=x; // set bound
                if(s < 0) {
                  s += dy2;
                } else {
                  y++;
                  s += dy2 - dx2;
                }
                x++;
              }
            }
          } else {                                                            // 1 < Slope < infinity
            s = dy - dx2;
            x=x1;
            y=y1;
            while(y<=y2) {                                                    // Draw Line
              pts[y]=x; // set bound
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
          if(dx > -dy) {                                                      // 0 > Slope > -1
            if (findMin) {
              s = dy2 + dx;
              x=x1;
              y=y1;
              intCrdT lastY=y-1;
              while(x<=x2) {                                                    // Draw Line
                if (y != lastY)
                  pts[y]=x; // set bound
                lastY = y;
                if(s > 0) {
                  s += dy2;
                } else {
                  y--;
                  s += dy2 + dx2;
                }
                x++;
              }
            } else {
              s = dy2 + dx;
              x=x1;
              y=y1;
              while(x<=x2) {                                                    // Draw Line
                pts[y]=x; // set bound
                if(s > 0) {
                  s += dy2;
                } else {
                  y--;
                  s += dy2 + dx2;
                }
                x++;
              }
            }
          } else {                                                            // -1 > Slope > -inf
            s = dy + dx2;
            x=x1;
            y=y1;
            while(y>=y2) {                                                    // Draw Line
              pts[y]=x; // set bound
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawFillTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorArgType color) {
    drawFillTriangleUtl(x1, y1, x2, y2, x3, y3, color, color, color, true);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawFillTriangle(intCrdT x1, intCrdT y1,
                                                                              intCrdT x2, intCrdT y2,
                                                                              intCrdT x3, intCrdT y3,
                                                                              colorArgType  color1, colorArgType color2, colorArgType  color3) {
    drawFillTriangleUtl(x1, y1, x2, y2, x3, y3, color1, color2, color3, false);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawFillTriangleUtl(intCrdT x1, intCrdT y1,
                                                                                 intCrdT x2, intCrdT y2,
                                                                                 intCrdT x3, intCrdT y3,
                                                                                 colorT c1, colorT c2, colorT c3, bool solid) { // Not colorArgType because of std::swap
    static intCrdT *minPts, *maxPts;
    static intCrdT  numPts;

    if( isCliped(x1, y1) || isCliped(x2, y2) || isCliped(x3, y3))
      return;

    ///////////////////////////////////////////////////////////////////////////////////
    // Check our work space, and allocate/reallocate as required.
    if(minPts == NULL) {               // First time in function -- allocate
      minPts = new intCrdT[numPixY];
      maxPts = new intCrdT[numPixY];
      numPts = numPixY;
    } else {                           // Not our first time!  We have a work space.
      if(numPts != numPixY) {          // Work space is wrong size -- reallocate
        delete[] minPts;
        delete[] maxPts;
        minPts = new intCrdT[numPixY];
        maxPts = new intCrdT[numPixY];
        numPts = numPixY;
      }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    if (!(solid) && ((x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2)) == 0))
      return;

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

    ///////////////////////////////////////////////////////////////////////////////////////
    /* cA    y1==y2 point    1,2,3                                                       */
    /* cB-cG y1==y2 h line   1,2---3   3---1,2   1,3---2   2---1,3   2,3---1   1---2,3   */
    /* cH-cJ y1==y2 v line   1,2  1,2   1,2                                              */
    /*                         \   |    /                                                */
    /*                          3  3   3                                                 */
    /* cK-cL y1==y2 tri      1---2   2---1                                               */
    /*                        \ /     \ /                                                */
    /*                         3       3                                                 */
    /* cM-cO y2=y3 v line     1      1      1                                            */
    /*                         \     |     /                                             */
    /*                         2,3  2,3  2,3                                             */
    /* cP-cQ y2=y3 tri         1      1                                                  */
    /*                        / \    / \                                                 */
    /*                       2---3  3---2                                                */
    /* cR-cS General         1       1    Note x1 need not equal x3 in these cases!      */
    /*                       |\     /|    It is just difficult to draw a case with       */
    /*                       | 2   2 |    x1 != x3 with tiny ASCII art...                */
    /*                       |/     \|                                                   */
    /*                       3       3                                                   */
    ///////////////////////////////////////////////////////////////////////////////////////

    if(y1==y3) {                                        // cA-cG
      minPts[y1] = mjr::min3(x1, x2, x3);               //
      maxPts[y1] = mjr::max3(x1, x2, x3);               //
    } else {                                            // cH-cS
      if(y1==y2) {                                      //   cH-cL
        if(x1==x2) {                                    //     cH-cJ
          triangleEdger(x1, y1, x3, y3, minPts, true);  //
          triangleEdger(x2, y2, x3, y3, maxPts, false); //
        } else if(x1<x2) {                              //     cK
          triangleEdger(x1, y1, x3, y3, minPts, true);  //
          triangleEdger(x2, y2, x3, y3, maxPts, false); //
        } else  {                                       //     cJ
          triangleEdger(x1, y1, x3, y3, maxPts, false); //
          triangleEdger(x2, y2, x3, y3, minPts, true);  //
        }                                               //
      } else if(y2==y3) {                               //   cM-cQ
        if(x2==x3) {                                    //     cM-cO
          triangleEdger(x1, y1, x3, y3, minPts, true);  //
          triangleEdger(x2, y2, x1, y1, maxPts, false); //
        } else if(x2<x3) {                              //     cP
          triangleEdger(x1, y1, x3, y3, maxPts, false); //
          triangleEdger(x2, y2, x1, y1, minPts, true);  //
        } else  {                                       //     cQ
          triangleEdger(x1, y1, x3, y3, minPts, true);  //
          triangleEdger(x2, y2, x1, y1, maxPts, false); //
        }                                               //
      } else {                                          //   cR-cS
        double xOt = (x1*y3+x3*y2-x1*y2-x3*y1);         //
        double xOb = (y3-y1);                           //
        if(xOt/xOb < x2) {                              //     cR
          triangleEdger(x1, y1, x3, y3, minPts, true);  //
          triangleEdger(x2, y2, x1, y1, maxPts, false); //
          triangleEdger(x2, y2, x3, y3, maxPts, false); //
        } else {                                        //     cS
          triangleEdger(x1, y1, x3, y3, maxPts, false); //
          triangleEdger(x2, y2, x1, y1, minPts, true);  //
          triangleEdger(x2, y2, x3, y3, minPts, true);  //
        }                                               //
      }                                                 //
    }                                                   //

    ///////////////////////////////////////////////////////////////////////////////////
    // Fill between the left and right bits.
    if(solid) {
      for(intCrdT y=y3; y<=y1; y++)
        drawLine(minPts[y], y, maxPts[y], y, c1);
    } else {
      for(intCrdT y=y3; y<=y1; y++)
        for(intCrdT x=minPts[y]; x<=maxPts[y]; x++) {
          /* Performance & Correctness: This code seems very poorly optimized.  Especially the computation of w3 instead of simply using 1-w1-w2, and the
             division by the sum w1+w2+s3 instead of by the total triangle area.  We are working with integer coordinates, and thus we have some fluff in the
             computations.  Sometimes, for example, the coordinates of a fill point won't, technically, be in the triangle.  Or the sum of the areas
             sub-triangles might not equal the total area.  So we compute w3 and divide by the sum so that we *always* get consistent results and coloring on
             the edges of triangles regardless of the order of the given points.  Yea, it slows things down, but my use cases for filled triangles demand
             consistency and accuracy on edges.  The repeated common expressions are optimized by the compiler.  This branch is roughly 15x slower than the
             solid branch above. */
          colorChanArithFltType w1 = std::abs(static_cast<colorChanArithFltType>( x*(y2 - y3) + x2*(y3 -  y) + x3*(y  - y2)));
          colorChanArithFltType w2 = std::abs(static_cast<colorChanArithFltType>(x1*(y  - y3) +  x*(y3 - y1) + x3*(y1 -  y)));
          colorChanArithFltType w3 = std::abs(static_cast<colorChanArithFltType>(x1*(y2 -  y) + x2*(y  - y1) +  x*(y1 - y2)));
          drawPointNC(x, y, colorT().wMean(w1/(w1+w2+w3), w2/(w1+w2+w3), w3/(w1+w2+w3), c1, c2, c3));
        }
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y) {
    drawPLCurve(numPoints, x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, fltCrdT *x, fltCrdT *y, colorArgType color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(real2intX(x[i]), real2intY(y[i]), real2intX(x[i+1]), real2intY(y[i+1]), color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, intCrdT *x, intCrdT *y) {
    drawPLCurve(numPoints, x, y, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, intCrdT *x, intCrdT *y, colorArgType color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(x[i], y[i], x[i+1], y[i+1], color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, pointIntType *thePoints, colorArgType color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(thePoints[i].x, thePoints[i].y, thePoints[i+1].x, thePoints[i+1].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, pointFltType *thePoints, colorArgType color) {
    for(int i=0; i<numPoints-1; i++)
      drawLine(thePoints[i].x, thePoints[i].y, thePoints[i+1].x, thePoints[i+1].y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, pointIntType *thePoints) {
    drawPLCurve(numPoints, thePoints, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPLCurve(int numPoints, pointFltType *thePoints) {
    drawPLCurve(numPoints, thePoints, dfltColor);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawTriangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, intCrdT x3, intCrdT y3, colorArgType color) {
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x3, y3, color);
    drawLine(x3, y3, x1, y1, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorArgType  color) {
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawFillCircle(intCrdT centerX, intCrdT centerY, intCrdT radiusX, colorArgType  color) {
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorArgType color) {
    if(x1 > x2) // Get x1 < x2
      std::swap(x1, x2);
    if(y1 > y2) // Get y1 < y2
      std::swap(y1, y2);
    if( (y1 < numPixY) && (x1 < numPixX) && (y2 >= 0) && (x2 >= 0) ) { // Part of rect visible
      int noTop, noBottom, noLeft, noRight;
      if((noTop=(y1 < 0)))
        y1 = 0;
      if((noLeft=(x1 < 0)))
        x1 = 0;
      if((noBottom=(y2 >= numPixY)))
        y2 = numPixY - 1;
      if((noRight=(x2 >= numPixX)))
        x2 = numPixX - 1;
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawFillRectangle(intCrdT x1, intCrdT y1, intCrdT x2, intCrdT y2, colorArgType color) {
    if(x1 > x2) // Get x1 < x2
      std::swap(x1, x2);
    if(y1 > y2) // Get y1 < y2
      std::swap(y1, y2);
    // Clip
    if( (y1 >= numPixY) || (x1 >= numPixX) || (y2 < 0) || (x2 < 0) )
      return;
    if(y1 < 0)
      y1 = 0;
    if(x1 < 0)
      x1 = 0;
    if(y2 >= numPixY)
      y2 = numPixY - 1;
    if(x2 >= numPixX)
      x2 = numPixX - 1;
    for(intCrdT y=y1;y<=y2;y++)
      drawHorzLineNC(x1, x2, y, color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawPointNC(intCrdT x, intCrdT y, colorArgType color) {
    /* Performance: We are depending on the compiler to eliminate this if statement because enableDrawModes is a compile time constant. */
    if (enableDrawModes)
      switch(drawMode) {
        case drawModeType::SET:       getPxColorRefNC(x, y).copy(color);          break;
        case drawModeType::XOR:       getPxColorRefNC(x, y).tfrmXor(color);       break;
        case drawModeType::ADDCLAMP:  getPxColorRefNC(x, y).tfrmAddClamp(color);  break;
        case drawModeType::AND:       getPxColorRefNC(x, y).tfrmAnd(color);       break;
        case drawModeType::OR:        getPxColorRefNC(x, y).tfrmOr(color);        break;
        case drawModeType::DIFFCLAMP: getPxColorRefNC(x, y).tfrmDiffClamp(color); break;
        case drawModeType::MULTCLAMP: getPxColorRefNC(x, y).tfrmMultClamp(color); break;
      }
    else
      getPxColorRefNC(x, y).copy(color);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::scaleUpProximal(int xfactor) {
    intCrdT new_numPixX_p = xfactor*numPixX;
    intCrdT new_numPixY_p = xfactor*numPixY;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];
    for(intCrdT y=0, y1=0; y<numPixY; y++) {
      for(intCrdT x=0, x1=0; x<numPixX; x++) {
        for(int i=0; i<xfactor; i++) {
          for(int j=0; j<xfactor; j++) {
            new_pixels[new_numPixX_p * y1 + x1] = getPxColor(x, y);
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
    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::scaleDown1pt(int xfactor) {
    intCrdT new_numPixX_p = numPixX/xfactor;
    intCrdT new_numPixY_p = numPixY/xfactor;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];
    for(intCrdT y=0, y1=0; y<new_numPixY_p; y++, y1+=xfactor)
      for(intCrdT x=0, x1=0; x<new_numPixX_p; x++, x1+=xfactor)
        new_pixels[new_numPixX_p * y + x] = getPxColor(x1, y1);

    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::scaleDownMean(int xfactor) {
    intCrdT new_numPixX_p = numPixX/xfactor;
    intCrdT new_numPixY_p = numPixY/xfactor;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];
    for(intCrdT y=0, y1=0; y<new_numPixY_p; y++, y1+=xfactor)
      for(intCrdT x=0, x1=0; x<new_numPixX_p; x++, x1+=xfactor) {
        std::vector<colorChanArithSDPType> sums(colorT::channelCount, static_cast<colorChanArithSDPType>(0));
        for(int j=0; j<xfactor; j++)
          for(int i=0; i<xfactor; i++)
            for(int c=0; c<colorT::channelCount; c++)
              sums[c] += getPxColor(x1+i, y1+j).getChan(c);
        colorT aColor;
        for(int c=0; c<colorT::channelCount; c++)
          aColor.setChan(c, static_cast<colorChanType>(sums[c] / (xfactor*xfactor)));
        new_pixels[new_numPixX_p * y + x] = aColor;
      }

    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::scaleDownMax(int xfactor) {
    intCrdT new_numPixX_p = numPixX/xfactor;
    intCrdT new_numPixY_p = numPixY/xfactor;
    colorT *new_pixels = new colorT[new_numPixX_p * new_numPixY_p];

    for(intCrdT y=0, y1=0; y<new_numPixY_p; y++, y1+=xfactor)
      for(intCrdT x=0, x1=0; x<new_numPixX_p; x++, x1+=xfactor) {
        colorT maxColor = getPxColor(xfactor*x, xfactor*y);
        for(int yi=0; yi<xfactor; yi++)
          for(int xi=0; xi<xfactor; xi++)
            maxColor.tfrmMaxI(getPxColor(xfactor*x+xi, xfactor*y+yi));
        new_pixels[new_numPixX_p * y + x] = maxColor;
      }

    rePointPixels(new_pixels, new_numPixX_p, new_numPixY_p);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::computeConvolutionMatrixGausian(double *kernel, int kSize, double sd) {
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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::computeConvolutionMatrixBox(double *kernel, int kSize) {
    for(int yi=0, yis=-(kSize/2); yi<kSize; yi++, yis++)
      for(int xi=0,xis=-(kSize/2); xi<kSize; xi++, xis++)
        kernel[kSize * yi + xi] = 1.0/(kSize*kSize);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::convolution(double *kernel, int kWide, int kTall, double divisor) {
    colorT *new_pixels = new colorT[numPixX * numPixY];
    // Divisor is invalid, so we compute one to use
    if(std::abs(divisor) < 0.0001) {
      divisor = 0.0;
      for(int i=0; i<(kWide*kTall); i++)
        divisor += kernel[i];
    }
    // Apply filter
    double tmp[colorT::channelCount];
    for(intCrdT y=0; y<numPixY; y++) {
      for(intCrdT x=0; x<numPixX; x++) {
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
          new_pixels[numPixX * y + x].setChan(chan, static_cast<colorChanType>(tmp[chan] / divisor));
      }
    }
    rePointPixels(new_pixels, numPixX, numPixY);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::convolution(double *kernel, int kSize, double divisor) {
    convolution(kernel, kSize, kSize, divisor);
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::convolution(double *kernel, int kSize) {
    convolution(kernel, kSize, kSize, 1.0);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawHersheyGlyph(int glyphNum, intCrdT x, intCrdT y, double magX, double magY, colorArgType aColor) {
    intCrdT x1, y1;
    int actionIsMoveTo;

    if( (glyphNum < 0) || (glyphNum > 3934) )
      glyphNum = 699;

    actionIsMoveTo=1;
    for(int i=0; i<(mjr::hershey::chars[glyphNum]).numComp; i++) {
      if((mjr::hershey::chars[glyphNum]).components[2*i] == ' ') {
        actionIsMoveTo = 1;
      } else {
        if(isIntAxOrientationNaturalX())
          x1 = static_cast<intCrdT>(magX * ((mjr::hershey::chars[glyphNum]).components[2*i]  -  'R'));
        else
          x1 = static_cast<intCrdT>(magX * ('R'  -  (mjr::hershey::chars[glyphNum]).components[2*i]));

        if(isIntAxOrientationNaturalY())
          y1 = static_cast<intCrdT>(magY * ('R' - (mjr::hershey::chars[glyphNum]).components[2*i+1]));
        else
          y1 = static_cast<intCrdT>(magY * ((mjr::hershey::chars[glyphNum]).components[2*i+1] - 'R'));

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
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawString(std::string aString, mjr::hershey::font aFont, intCrdT x, intCrdT y, colorArgType aColor, double cex, intCrdT spc) {
    for(auto &c : aString) {
      int glyphNum = 0;
      if((c>=32) && (c<=126))
        glyphNum = mjr::hershey::ascii2hershey[(int)aFont][c-32];
      drawHersheyGlyph(glyphNum, x, y, cex, cex, aColor);
      x+=static_cast<intCrdT>(spc*cex);
    }
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline void
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::drawStringBox(std::string aString,
                                                                           mjr::hershey::font aFont,
                                                                           intCrdT x, intCrdT y,
                                                                           colorArgType stringColor, colorArgType boxColor,
                                                                           double cex, intCrdT spc) {
    drawFillRectangle(static_cast<intCrdT>(x-spc*cex),
                      static_cast<intCrdT>(y-spc*cex),
                      static_cast<intCrdT>(x+spc*cex*static_cast<int>(aString.length())),
                      static_cast<intCrdT>(y+spc*cex),
                      boxColor);
    drawString(aString, aFont, x, y, stringColor, cex, spc);
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::readRAWfile(std::string fileName) {
    char strBuf[256];

    std::ifstream iStream(fileName, std::ios_base::binary);

    if (!(iStream.good()))
      return 1;

    iStream.getline(strBuf, 10, '\n');
    if (!(iStream.good()))
      return 11;
    if (iStream.gcount() != 7)
      return 24;
    if(std::string(strBuf) != std::string("MJRRAW"))
      return 24;

    int  fileWide       = -1;
    int  fileTall       = -1;
    int  fileChans      = -1;
    int  fileBitPerChan = -1;
    bool fileIsSGN = true, fileHasS = false;
    bool fileIsInt = true, fileHasT = false;
    bool fileIsLTL = true, fileHasI = false;

    iStream.getline(strBuf, 100, '\n');
    if (!(iStream.good()))
      return 11;
    if (iStream.gcount() != 93)
      return 26;

    std::string::size_type tagIdx;
    std::string::size_type prcIdx = 0;
    std::string strBufS(strBuf);
    std::string delChrs("abcdefghijklmnopqrstuvwxyz");
    int stoiErrorCount = 0;

    while(true) {
      tagIdx = strBufS.find_first_of(delChrs, prcIdx);
      if (tagIdx == std::string::npos)
        break;
      // std::cout << "suc: " << strBufS.substr(prcIdx)  << std::endl;
      // std::cout << "tok: " << strBufS.substr(prcIdx, tagIdx-prcIdx)  << std::endl;
      try {
        switch(strBufS[tagIdx]) {
          case 'x' : fileWide       = std::stoi(strBufS.substr(prcIdx, tagIdx-prcIdx)); break;
          case 'y' : fileTall       = std::stoi(strBufS.substr(prcIdx, tagIdx-prcIdx)); break;
          case 'c' : fileChans      = std::stoi(strBufS.substr(prcIdx, tagIdx-prcIdx)); break;
          case 'b' : fileBitPerChan = std::stoi(strBufS.substr(prcIdx, tagIdx-prcIdx)); break;
          case 's' : fileIsSGN      = (strBufS[prcIdx] == 'S'); fileHasS = true;        break;
          case 't' : fileIsInt      = (strBufS[prcIdx] == 'I'); fileHasT = true;        break;
          case 'i' : fileIsLTL      = (strBufS[prcIdx] == 'L'); fileHasI = true;        break;
        }
      } catch (...) {
        stoiErrorCount++;
      }
      prcIdx=tagIdx+1;
    }

    int fileBytePerChan = fileBitPerChan / 8;

    // std::cout <<  "fileWide         " << fileWide        << std::endl;
    // std::cout <<  "fileTall         " << fileTall        << std::endl;
    // std::cout <<  "fileChans        " << fileChans       << std::endl;
    // std::cout <<  "fileBitPerChan   " << fileBitPerChan  << std::endl;
    // std::cout <<  "fileIsSGN        " << fileIsSGN       << std::endl;
    // std::cout <<  "fileIsInt        " << fileIsInt       << std::endl;
    // std::cout <<  "fileIsLTL        " << fileIsLTL       << std::endl;
    // std::cout <<  "fileBytePerChan: " << fileBytePerChan << std::endl;

    if (stoiErrorCount > 0)
      return 29;

    if (fileWide < 0)
      return 33;
    if (fileTall < 0)
      return 34;
    if (fileChans < 0)
      return 35;
    if (fileBitPerChan < 0)
      return 36;

    if (fileWide == 0)
      return 8;
    if (fileTall == 0)
      return 9;

    if (fileWide > intCrdMax)
      return 27;
    if (fileTall > intCrdMax)
      return 28;

    resizeCanvas(fileWide, fileTall);

    if (fileWide != numPixX)
      return(12);
    if (fileTall != numPixY)
      return(14);

    if (!(fileHasT))
      fileIsInt = true;

    if (!(fileHasS))
      fileIsSGN = ( !(fileIsInt));  // If file is missing 's', then assume it's compatable with 't'

    if ((colorT::chanIsInt && fileIsSGN))
      return 23;

    if ((colorT::chanIsInt   && !fileIsInt) ||
        (colorT::chanIsFloat &&  fileIsInt))
      return 21;

    if(fileChans != colorT::channelCount)
      return 19;

    if(fileBitPerChan != colorT::bitsPerChan)
      return 20;

    if (!(fileHasI))
      fileIsLTL = (platformEndianness() == endianType::LITTLE);  // missing 'i', then assume LITTLE.

    bool reverseBits = ((  fileIsLTL  && (platformEndianness() == endianType::BIG)) ||
                        (!(fileIsLTL) && (platformEndianness() == endianType::LITTLE)));

    intCrdT x, y;
    bool yNat = !(isIntAxOrientationNaturalY());
    bool xNat = isIntAxOrientationNaturalX();
    for((yNat?y=0:y=(numPixY-1)); (yNat?y<numPixY:y>=0); (yNat?y++:y--)) {
      for((xNat?x=0:x=(numPixX-1)); (xNat?x<numPixX:x>=0); (xNat?x++:x--)) {
        for(int ci=0; ci<fileChans; ci++) {
          /* performance: An if inside a triple nexted for loop!  Ouch.  But chanIsInt is a compile time constant, so this should be reduced to just the
             branch of the if that is true.  Same wit the if statement inside the else clause of this if.*/
          if (colorT::chanIsInt) {
            colorChanArithLogType shft  = (reverseBits ? colorT::bitsPerChan-8 : 0);
            /* Note that colorChanArithLogType is always an unsigned integer type, and thus we avoid compiler errors when trying to use | on a float.
               When chanIsInt, colorChanArithLogType is the same as colorChanType when chanIsInt -- so a NOOP because this part of the if only gets
               run when chanIsInt. */
            colorChanArithLogType pv = 0;
            for(int bi=0; bi<fileBytePerChan; bi++) {
              colorChanArithLogType uch = (unsigned char)iStream.get();
              if (!(iStream.good()))
                return 25;
              if (iStream.gcount() != 1)
                return 25;
              pv = pv | static_cast<colorChanArithLogType>(uch << shft);

              if (reverseBits)
                shft -= 8;
              else
                shft += 8;

            }
            getPxColorRefNC(x, y).setChan(ci, static_cast<colorChanType>(pv));
          } else {
            iStream.read(strBuf, fileBytePerChan);
            getPxColorRefNC(x, y).setChan(ci, *((colorChanType*)strBuf));
          }
        }
      }
    }
    iStream.close();
    return 0;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    int
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::readTIFFfile(std::string fileName) {
#ifndef TIFF_FOUND
    std::cerr << "ERROR: libTIFF no supported: readTIFFfile can't read " << fileName << std::endl;
    return 32;
#else
    TIFF* tif;
    uint32_t wTIFF, hTIFF;
    uint16_t pmTIFF, pcTIFF, sppTIFF, bpsTIFF, fmtTIFF;

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

    // This one is not required.  If it's missing, it's 1 (unsigned integer).
    if( 1 != TIFFGetField(tif, TIFFTAG_SAMPLEFORMAT,   &fmtTIFF))
      fmtTIFF = 1;

    //  MJR TODO NOTE We don't know how to deal with pallet images (pmTIFF == PHOTOMETRIC_PALETTE).  Should check for that.
    //  MJR TODO NOTE We don't know how to deal with tiled images.  Should check for that.

    //uint64_t cmTIFF = (1ULL << bpsTIFF) - 1ULL;

    // // Dump out image metadata
    // std::cerr << "TIFF: "      << fileName << std::endl;
    // std::cerr << " T WIDTH:  " << wTIFF    << std::endl;
    // std::cerr << " T HEIGHT: " << hTIFF    << std::endl;
    // std::cerr << " T SPP:    " << sppTIFF  << std::endl;
    // std::cerr << " T PLNC:   " << pcTIFF   << std::endl;
    // std::cerr << " T PHOM:   " << pmTIFF   << std::endl;
    // std::cerr << " T BPS:    " << bpsTIFF  << std::endl;
    // std::cerr << " T MAX:    " << cmTIFF   << std::endl;
    // std::cerr << " T FMT:    " << fmtTIFF  << std::endl;

    // Check file image size and reallocate aRamCanvas
    if(wTIFF < 1)
      return 8;

    if(hTIFF < 1)
      return 9;

    resizeCanvas(wTIFF, hTIFF);

    uint32_t wRC   = getNumPixX();

    if ((pcTIFF != PLANARCONFIG_CONTIG) && (pcTIFF != PLANARCONFIG_SEPARATE))
      return 22;

    if(wTIFF != wRC)
      return 12;

    uint32_t hRC   = getNumPixY();

    if(hTIFF != hRC)
      return 14;

    uint16_t sppRC = colorT::channelCount;

    if(sppTIFF != sppRC)
      return 19;

    uint16_t bpsRC = colorT::bitsPerPixel / sppRC;

    if(bpsTIFF != bpsRC)
      return 20;

    // We only suport SAMPLEFORMAT_UINT & SAMPLEFORMAT_IEEEFP
    if ((fmtTIFF != SAMPLEFORMAT_UINT) && (fmtTIFF != SAMPLEFORMAT_IEEEFP))
      return 18;

    if ((  colorType::chanIsInt  && (SAMPLEFORMAT_UINT != 1)) ||
        (!(colorType::chanIsInt) && (SAMPLEFORMAT_IEEEFP != 3)))
      return 21;

    bool yNat  = !(isIntAxOrientationNaturalY());
    bool xNat  = isIntAxOrientationNaturalX();
    tsize_t scanlinesize = TIFFScanlineSize(tif);
    tdata_t scanLineBuffer = _TIFFmalloc(scanlinesize);

    if(scanLineBuffer == NULL)
      return 16;

    if (pcTIFF == PLANARCONFIG_CONTIG) { // Chunky
      for(uint32_t row=0; row<hTIFF; row++) {
        if( !(TIFFReadScanline(tif, scanLineBuffer, row)))
          return 17;
        char* p = (char*)(scanLineBuffer);
        for(uint32_t col=0; col<wTIFF; col++) {
          int x = (xNat ? col : wTIFF-col-1);
          int y = (yNat ? row : hTIFF-row-1);
          for(uint16_t samp=0; samp<sppTIFF; samp++) {
            getPxColorRefNC(x, y).setChan(samp, static_cast<colorChanType>(*p));
            p = p + (bpsTIFF/8);
          }
        }
      }
    } else if (pcTIFF == PLANARCONFIG_SEPARATE) { // planar
      for(uint16_t samp=0; samp<sppTIFF; samp++) {
        for(uint32_t row=0; row<hTIFF; row++) {
          if( !(TIFFReadScanline(tif, scanLineBuffer, row, samp)))
            return 17;
          char* p = (char*)(scanLineBuffer);
          for(uint32_t col=0; col<wTIFF; col++) {
            int x = (xNat ? col : wTIFF-col-1);
            int y = (yNat ? row : hTIFF-row-1);
            getPxColorRefNC(x, y).setChan(samp, static_cast<colorChanType>(*p));
            p = p + (bpsTIFF/8);
          }
        }
      }
    }

    _TIFFfree(scanLineBuffer);
    TIFFClose(tif);
    return 0;
#endif
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    inline bool
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::supportLibTIFF() {
#ifndef TIFF_FOUND
    return true;
#else
    return false;
#endif
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::geomTfrmRevArb(mjr::point2d<double> (*f)(double, double), 
                                                                            double Xo,
                                                                            double Yo,
                                                                            double oScale,
                                                                            colorArgType errorColor, 
                                                                            interpolationType interpMethod) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes> newRamCanvas(numPixX, numPixY);
    for(intCrdT y=0; y<numPixY; y++) {
      for(intCrdT x=0; x<numPixX; x++) {
        double xT = (x-Xo);
        double yT = (y-Yo);
        mjr::point2d<double> fv = f(xT, yT);
        double xS = fv.x / oScale + Xo;
        double yS = fv.y / oScale + Yo;
        if (isCliped(static_cast<intCrdT>(xS), static_cast<intCrdT>(yS))) {
          newRamCanvas.drawPointNC(x, y, errorColor);
        } else {
          newRamCanvas.drawPointNC(x, y, getPxColorInterpolate(xS, yS, interpMethod));
        }
      }
    }
    return newRamCanvas;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::geomTfrmRevAff(std::vector<double> const& HAMatrix, 
                                                                            double Xo,
                                                                            double Yo,
                                                                            double oScale,
                                                                            colorArgType errorColor, 
                                                                            interpolationType interpMethod) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes> newRamCanvas(numPixX, numPixY);
    for(intCrdT y=0; y<numPixY; y++) {
      for(intCrdT x=0; x<numPixX; x++) {
        double xT = x-Xo;
        double yT = y-Yo;
        double xS = (HAMatrix[0] * xT + HAMatrix[1] * yT + HAMatrix[2]) / oScale + Xo;
        double yS = (HAMatrix[3] * xT + HAMatrix[4] * yT + HAMatrix[5]) / oScale + Yo;
        if (isCliped(static_cast<intCrdT>(xS), static_cast<intCrdT>(yS))) {
          newRamCanvas.drawPointNC(x, y, errorColor);
        } else {
          newRamCanvas.drawPointNC(x, y, getPxColorInterpolate(xS, yS, interpMethod));
        }
      }
    }
    return newRamCanvas;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::geomTfrmRevRPoly(std::vector<double> const& RPoly,
                                                                              double rScale,
                                                                              double Xo,
                                                                              double Yo,
                                                                              double oScale,
                                                                              colorArgType errorColor,
                                                                              interpolationType interpMethod) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes> newRamCanvas(numPixX, numPixY);
    for(intCrdT y=0; y<numPixY; y++) {
      for(intCrdT x=0; x<numPixX; x++) {
        double xT = (x - Xo);
        double yT = (y - Yo);
        double rT = std::hypot(xT, yT) / rScale;
        // TODO: Use mjr::evalUniPoly
        double rS = RPoly[0];
        for (unsigned int i=1; i<RPoly.size(); i++)
          rS = rS*rT + RPoly[i];
        double xS = xT * rS / oScale + Xo;
        double yS = yT * rS / oScale + Yo;
        if (isCliped(static_cast<intCrdT>(xS), static_cast<intCrdT>(yS))) {
          newRamCanvas.drawPointNC(x, y, errorColor);
        } else {
          newRamCanvas.drawPointNC(x, y, getPxColorInterpolate(xS, yS, interpMethod));
        }
      }
    }
    return newRamCanvas;
  }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class colorT, class intCrdT, class fltCrdT, bool enableDrawModes>
  requires (std::is_integral<intCrdT>::value && std::is_signed<intCrdT>::value && std::is_floating_point<fltCrdT>::value)
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes>::geomTfrmRevBiPoly(std::vector<double> const& BiPolyX,
                                                                               std::vector<double> const& BiPolyY,
                                                                               double Xo,
                                                                               double Yo,
                                                                               double oScale,
                                                                               colorArgType errorColor,
                                                                               interpolationType interpMethod) {
    ramCanvasTpl<colorT, intCrdT, fltCrdT, enableDrawModes> newRamCanvas(numPixX, numPixY);
    for(intCrdT y=0; y<numPixY; y++) {
      for(intCrdT x=0; x<numPixX; x++) {
        double xT = (x-Xo);
        double yT = (y-Yo);
        double xS = mjr::evalBiPoly(BiPolyX, xT, yT) / oScale + Xo;
        double yS = mjr::evalBiPoly(BiPolyY, xT, yT) / oScale + Yo;
        if (isCliped(static_cast<intCrdT>(xS), static_cast<intCrdT>(yS))) {
          newRamCanvas.drawPointNC(x, y, errorColor);
        } else {
          newRamCanvas.drawPointNC(x, y, getPxColorInterpolate(xS, yS, interpMethod));
        }
      }
    }
    return newRamCanvas;
  }

} // end namespace mjr

#define MJR_INCLUDE_ramCanvasTpl
#endif

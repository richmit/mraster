#ifndef MJR_INCLUDE_rcPixelFilters

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Put everything in the mjr namespace
namespace mjr {
  /** @brief Namespace for ramCanvas Pixel Filters.

      mjr::ramCanvasPixelFilter objects attach to, and override, the minimal pixel access interface of another object.  The idea is to provide an alternate
      pixel access interface that may modify the data in transit.  In this way they mjr::ramCanvasPixelFilter objects provide an alternate "view" of the pixel
      data. For example mjr::ramCanvasTpl::writeTIFFfile() can use mjr::ramCanvasPixelFilter::RGBbyte to write a 24-bit RGB image from a source
      mjr::ramCanvasTpl object containing floating point channels.  Note that mjr::ramCanvasPixelFilter objects themselves provide a minimal pixel access
      interface, and thus mjr::ramCanvasPixelFilter objects can be attached to other mjr::ramCanvasPixelFilter objects allowing one to chain together a list of
      pixel data filters.

      The minimal pixel access interface for a mjr::ramCanvasTpl-like object consists of the following seven members:

        - isIntAxOrientationNaturalX()
        - isIntAxOrientationNaturalY()
        - getNumPixX()
        - getNumPixY()
        - getPxColorNC(x, y) 
        - colorType
        - coordIntType

      It is important to remember that mjr::ramCanvasPixelFilter objects can modify not just the pixel data but the size of a mjr::ramCanvasTpl object.  For
      example, mjr::ramCanvasPixelFilter::ScaleDownMean can be used to virtually resize a mjr::ramCanvasTpl object!  For this reason it is important to use the
      getNumPixX() and getNumPixY() methods when working with pixel data.

      Note the pixel interface provided by mjr::ramCanvasPixelFilter objects might be described with the adjectives: *minimal*, *fast*, and *unsafe*!  The
      interface is unsafe in that it provides access to getPxColorNC() and *not* getPxColor().  That means no bounds checks are made on pixel coordinates.  In
      short, mjr::ramCanvasPixelFilter objects are intended to be consumed by code that has the necessary bounds checks built in.  Keep this in mind if you use
      them for something else!
      */
  namespace ramCanvasPixelFilter {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /** @name ramCanvasTpl pixel filter classes. */
    //@{
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** An incomplete class (no getPxColorNC method) that provides a nice base for homogeniouss pixel filters
        \tparam sourceT The type of the ram canvas to filter. */
    template<class sourceT>
    class FixGeomBase {
      public:
        sourceT& attachedRC;
        FixGeomBase(sourceT& aRC) : attachedRC(aRC) {  }
        typedef typename sourceT::coordIntType coordIntType;
        inline bool isIntAxOrientationNaturalX() { return attachedRC.isIntAxOrientationNaturalX(); }
        inline bool isIntAxOrientationNaturalY() { return attachedRC.isIntAxOrientationNaturalY(); }
        inline coordIntType getNumPixX() { return attachedRC.getNumPixX(); }
        inline coordIntType getNumPixY() { return attachedRC.getNumPixY(); }
        //virtual colorType getPxColorNC(coordIntType x, coordIntType y) = 0;
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Identity filter -- i.e. NOP. */
    template<class sourceT>
    class Identity : public FixGeomBase<sourceT>  {
      public:
        Identity(sourceT& aRC) : FixGeomBase<sourceT>(aRC) {  }
        typedef typename sourceT::colorType    colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) { return FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y); }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Convert to an RGB color image with 8-bit integer channels. */
    template<class sourceT>
    class RGBbyte : public FixGeomBase<sourceT>  {
      public:
        RGBbyte(sourceT& aRC) : FixGeomBase<sourceT>(aRC) {  }
        typedef typename sourceT::colorType::colConRGBbyte colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) { return FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y).getColConRGB_byte(); }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Convert to an RGBA color image with 8-bit integer channels. */
    template<class sourceT>
    class RGBAbyte : public FixGeomBase<sourceT>  {
      public:
        RGBAbyte(sourceT& aRC) : FixGeomBase<sourceT>(aRC) {  }
        typedef typename sourceT::colorType::colConRGBAbyte colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) { return FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y).getColConRGBA_byte(); }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Convert to an RGB color image with 64-bit floating point channels. */
    template<class sourceT>
    class RGBdbl : public FixGeomBase<sourceT>  {
      public:
        RGBdbl(sourceT& aRC) : FixGeomBase<sourceT>(aRC) {  }
        typedef typename sourceT::colorType::colConRGBdbl colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) { return FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y).getColConRGB_dbl(); }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Convert to an RGBA color image with 64-bit floating point channels. */
    template<class sourceT>
    class RGBAdbl : public FixGeomBase<sourceT>  {
      public:
        RGBAdbl(sourceT& aRC) : FixGeomBase<sourceT>(aRC) {  }
        typedef typename sourceT::colorType::colConRGBAdbl colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) { return FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y).getColConRGBA_dbl(); }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Monochrome transformation using colorT::intensityScaled(). */
    template<class sourceT, class outColorChanT>
    class MonoIntensity : public FixGeomBase<sourceT>  {
      public:
        MonoIntensity(sourceT& aRC) : FixGeomBase<sourceT>(aRC) {  }
        typedef colorTpl<outColorChanT, 1>     colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) {
          return static_cast<outColorChanT>(FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y).intensityScaled() * colorType::maxChanVal);
        }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Colorize by applying a color scheme to a single channel automatically mapping max channel value to max color scheme index.
        \tparam outColorT Color type to return. 
        \tparam chan      Channel to use from the input image. */
    template<class sourceT, class outColorT, class colorScheme, int chan = 0>
    requires(std::same_as<outColorT, decltype(colorScheme::c(1))> && (chan>=0) && (chan<outColorT::channelCount))
    class ColorSchemeOnChan : public FixGeomBase<sourceT>  {
      public:
        ColorSchemeOnChan(sourceT& aRC) : FixGeomBase<sourceT>(aRC) {  }
        typedef outColorT colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) {
          if constexpr (sourceT::colorType::chanIsInt) {
            return colorScheme::c(static_cast<outColorT::csIntType>(mjr::math::linm::gen_map(static_cast<sourceT::colorType::channelArithSDPType>(FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y).getChan(chan)),
                                                                                             static_cast<sourceT::colorType::channelArithSDPType>(sourceT::colorType::minChanVal),
                                                                                             static_cast<sourceT::colorType::channelArithSDPType>(sourceT::colorType::maxChanVal),
                                                                                             static_cast<sourceT::colorType::channelArithSDPType>(0), 
                                                                                             static_cast<sourceT::colorType::channelArithSDPType>(colorScheme::numC - 1))));
          } else {
            return colorScheme::c(static_cast<outColorT::csFltType>(FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y).getChan(chan)));
          }
        }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Transform an image with a pixel function.
        \tparam outColorT Color type to return. 
        \tparam chan      Channel to use from the input image. */
    template<class sourceT, class outColorT = sourceT::colorType>
    class FuncHomoTransform : public FixGeomBase<sourceT>  {
      public:
        typedef std::function<outColorT(typename sourceT::colorType)> ctf_t;
      private:
        ctf_t ctf;
      public:
        FuncHomoTransform(sourceT& aRC, ctf_t colorTransformFunction) : FixGeomBase<sourceT>(aRC), ctf(colorTransformFunction) {  }
        typedef outColorT colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline colorType getPxColorNC(coordIntType x, coordIntType y) { return ctf(FixGeomBase<sourceT>::attachedRC.getPxColorNC(x, y)); }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Scale down a canvis using a method similar to ramCanvasTpl::scaleDownMean(). */
    template<class sourceT, int factor>
    class ScaleDownMean {
      public:
        sourceT& attachedRC;
        ScaleDownMean(sourceT& aRC) : attachedRC(aRC) {  }
        typedef typename sourceT::colorType    colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline bool isIntAxOrientationNaturalX() { return attachedRC.isIntAxOrientationNaturalX(); }
        inline bool isIntAxOrientationNaturalY() { return attachedRC.isIntAxOrientationNaturalY(); }
        inline coordIntType getNumPixX() { return attachedRC.getNumPixX() / factor; }
        inline coordIntType getNumPixY() { return attachedRC.getNumPixY() / factor; }
        inline colorType getPxColorNC(coordIntType x, coordIntType y) {
          coordIntType x0 = x * factor;
          coordIntType y0 = y * factor;
          colorType retColor(static_cast<colorType::channelType>(0));
          for(int c=0; c<colorType::channelCount; c++) {
            typename colorType::channelArithSPType sum = static_cast<colorType::channelArithSPType>(0);
            for(coordIntType yi=0; yi<factor; yi++) {
              for(coordIntType xi=0; xi<factor; xi++) {
                sum += attachedRC.getPxColorNC(xi+x0, yi+y0).getChanNC(c);
              }
            }
            retColor.setChanNC(c, static_cast<colorType::channelType>(sum/factor/factor));
          }
          return retColor;
        }
    };
    //--------------------------------------------------------------------------------------------------------------------------------------------------------
    /** Rotate image 90 degrees clockwise. */
    template<class sourceT>
    class Rotate90CW {
      public:
        sourceT& attachedRC;
        Rotate90CW(sourceT& aRC) : attachedRC(aRC) {  }
        typedef typename sourceT::colorType    colorType;
        typedef typename sourceT::coordIntType coordIntType;
        inline bool isIntAxOrientationNaturalX() { return attachedRC.isIntAxOrientationNaturalX(); }
        inline bool isIntAxOrientationNaturalY() { return attachedRC.isIntAxOrientationNaturalY(); }
        inline coordIntType getNumPixX() { return attachedRC.getNumPixY(); }
        inline coordIntType getNumPixY() { return attachedRC.getNumPixX(); }
        inline colorType getPxColorNC(coordIntType x, coordIntType y) { return attachedRC.getPxColorNC((attachedRC.getNumPixY()-1)-y, x); }
    };
    //@}
  }
} // end namespace mjr

#define MJR_INCLUDE_rcPixelFilters
#endif

#ifndef MJR_INCLUDE_hersheyFonts

namespace mjr {

  enum class hersheyFont { 
      GREEK_SL_SANSERIF = 0,  // greek sans-serif  single lines
      GREEK_DL_SERIF    = 1,  // greek sans-serif  double lines
      ROMAN_SL_SANSERIF = 2,  // roman sans-serif  single lines
      ROMAN_DL_SERIF    = 3,  // roman sans-serif  double lines
      ROMAN_TL_SERIF    = 4   // roman serif       triple lines
  };


  struct herChar {
      int charNum;            // 
      int numComp;            // 
      const char *components; // 
  };

  extern const int hersheyFontAscii[5][95];

  extern const herChar theHerChars[3935];

  
}; // namespace mjr

#define MJR_INCLUDE_hersheyFonts
#endif



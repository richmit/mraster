#ifndef CONFIG_H
#define CONFIG_H

#ifndef MRASTER_CMAKE_BUILD
#define MRASTER_CMAKE_BUILD 0
#endif

#define MRASTER_CMAKE_CONFIG  0

static_assert(MRASTER_CMAKE_CONFIG == MRASTER_CMAKE_BUILD,
                  "ERROR: Cmake build detected, but mraster_config.hpp included from lib/ -- not build/.  Quick fix: Delete mraster_config.hpp in lib/ directory.");

#define MRASTER_PROJECT_NAME  "MRaster"

#define MRASTER_VERSION       "0.0.0.0"
#define MRASTER_VERSION_MAJOR 0
#define MRASTER_VERSION_MINOR 0
#define MRASTER_VERSION_PATCH 0
#define MRASTER_VERSION_TWEAK 0
#define MRASTER_VERSION_TAG   "v0.0.0.0"
#define MRASTER_VERSION_DATE  "0000-00-00"

#define MRASTER_FOUND_DOXYGEN 0
#define MRASTER_FOUND_TIFF    0
#define MRASTER_FOUND_OPENGL  0
#define MRASTER_FOUND_GLUT    0
#define MRASTER_FOUND_OPENMP  0
#define MRASTER_FOUND_SDL2    0
#define MRASTER_FOUND_BTEST   0

#define MRASTER_OPT_128_INT 0
#define MRASTER_OPT_BTEST   0
#define MRASTER_OPT_DOXYGEN 0
#define MRASTER_OPT_OPENGL  0
#define MRASTER_OPT_OPENMP  0
#define MRASTER_OPT_SDL2    0
#define MRASTER_OPT_TIFF    0

#endif

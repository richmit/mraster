######################################################################################################################################################

#
# MSYS instructions
#
# From the msys2 shell use something like this:
#
#   mkdir build; cd build
#
# Then do this
#
#   echo "RUN CMAKE"; cmake -G "MSYS Makefiles" -DCMAKE_CXX_COMPILER=/mingw64/bin/clang++.exe -DO_TIFF=YES ..
#
# or this
#
#   echo "RUN CMAKE"; cmake -G "MSYS Makefiles" -DCMAKE_CXX_COMPILER=/mingw64/bin/g++.exe     -DO_TIFF=YES ..
#
# Other "O" options include: O_DOXYGEN, O_TIFF, O_OPENGL, O_OPENMP, O_PNG, O_IM, & O_STATIC
#
# Leave off the -DCMAKE_CXX_COMPILER... option to use the default compiler
# 

######################################################################################################################################################
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

######################################################################################################################################################
# Proejct meta data

project(MRaster CXX)

set(PROJECT_VERSION_DATE  20190120)
set(PROJECT_VERSION_ID    2)
mark_as_advanced(PROJECT_VERSION_DATE PROJECT_VERSION_ID)

######################################################################################################################################################
# Here are the options we use to modify the build -- these options are passed to cmake like so: cmake -DO_OPENSSL=YES or -DO_OPENSSL=NO

OPTION(O_DOXYGEN "Include support for doxygen"         ON  )
OPTION(O_TIFF    "Include support for libTIFF"         ON  )
OPTION(O_OPENGL  "Include support for OpenGL & GLUT"   ON  )
OPTION(O_OPENMP  "Include support for OpenMP"          ON  )
OPTION(O_PNG     "Include support for libPNG"          OFF )
OPTION(O_IM      "Include support for ImageMagick"     OFF )
OPTION(O_MOVIE   "Include support making movies"       ON  )
OPTION(O_RAY     "Include support ray-tracing"         ON  )
OPTION(O_STATIC  "Build a static library"              ON  )

set(POVRAY_HINT "c:/Program Files/POV-Ray/v3.7/bin/")

######################################################################################################################################################

if(O_STATIC)
  add_library(mrr STATIC lib/colorData.cpp lib/hersheyFontData.cpp)
else()
  add_library(mrr SHARED lib/colorData.cpp lib/hersheyFontData.cpp)
endif()

######################################################################################################################################################
# Find tools & libraries used to build primary/secondary/tertiary targets

if(O_MOVIE)
  find_program(MAKEMOV avconv)
  find_program(MAKEMOV ffmpeg)
  if(${MAKEMOV} STREQUAL "MAKEMOV-NOTFOUND")
    message(WARNING "Could not find movie making command for MAKEMOV")
  endif()
endif()

if(O_RAY)
  find_program(POVRAY pvengine HINTS ${POVRAY_HINT})
  find_program(POVRAY povray)
  if(${POVRAY} STREQUAL "POVRAY-NOTFOUND")
    message(WARNING "Could not find POV-ray for POVRAY")
  endif()
endif()

if(O_DOXYGEN)
  find_package(Doxygen)
endif()

if(O_TIFF)
  find_package(TIFF)
endif()

if(O_OPENGL)
  find_package(OpenGL)
  find_package(GLUT)
endif()

if(O_OPENMP)
  find_package(OpenMP)
endif()

if(O_PNG)
  find_package(PNG)
endif()

if(O_IM)
  find_package(ImageMagick COMPONENTS MagickWand MagickCore)
endif()

######################################################################################################################################################

set(TARGETS_REQ_NONE   "apollony" "circles" "apomorph" "bifurcation_diagram" "biomorph1" "biomorph2" "bmark" "chaos_game" "color_all" "color_lut_ramp_cube"  "dlaSeed" "cplxColor"
                       "color_lut_ramp_misc" "color_interp_hls_vs_rgb" "mandelbrot_distance" "level_curves" "mandelbrot_bm_cplx" "mandelbrot_bm_cplx_hyper"
                       "mandelbrot_bm_real" "newton_max_mod" "newton_z6" "newton_half" "newton_vs" "newton_bm_cplx" "newton_bm_real" "mandelbrot_binary"
                       "peterdejong" "peterdejongM" "mandelbrot_potential" "sic" "sic_search" "sierpinski_triangle" "test_draw_btriangle" "test_draw_color"
                       "test_draw_misc" "test_draw_primatives" "testPoint" "tippets" "mandelbrot_triangle" "mandelbrot_emboss" "mandelbrot_orbits"
                       )
set(TARGETS_REQ_MRRL   "test_draw_fonts" "test_draw_strings" "test_draw_glyph" "color_web_triangle" "color_web_rectangle" "color_lut_indexed" "color_lut_rainbows" )
set(TARGETS_REQ_OPENGL "glut_image")
set(TARGETS_REQ_TIFF   "img_process" "dlaBrownian" "dlaDrift")
set(TARGETS_REQ_OPENMP "mandelbrot_bm_cplx_openmp")

# Construct list of targets we can build
set(EXAMPLE_TARGETS ${TARGETS_REQ_NONE})
list(APPEND EXAMPLE_TARGETS ${TARGETS_REQ_MRRL})
if(OpenGL_FOUND AND GLUT_FOUND)
  list(APPEND EXAMPLE_TARGETS ${TARGETS_REQ_OPENGL})
else()
  message(WARNING "OpenGL/GLUT programs will NOT be built!.")
endif()
if(OpenMP_FOUND)
  list(APPEND EXAMPLE_TARGETS ${TARGETS_REQ_OPENMP})
else()
  message(WARNING "OpenMP pragmmas will NOT be built!")
endif()
if(TIFF_FOUND)
  list(APPEND EXAMPLE_TARGETS ${TARGETS_REQ_TIFF})
else()
  message(WARNING "TIFF pragmmas will NOT be built!")
endif()

# Add a target for each example we can build
foreach(CURTGT IN LISTS EXAMPLE_TARGETS)
  add_executable(${CURTGT} "examples/${CURTGT}.cpp")
  target_include_directories(${CURTGT} PRIVATE lib)
  target_compile_features(${CURTGT} PUBLIC cxx_auto_type)
  target_include_directories(${CURTGT} PRIVATE ${CMAKE_BINARY_DIR})
  
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${CURTGT} PUBLIC -Wstrict-overflow=0)
    target_compile_options(${CURTGT} PUBLIC -ffast-math)
    target_compile_options(${CURTGT} PUBLIC -Wall)
    target_compile_options(${CURTGT} PUBLIC -O5)
    if(CMAKE_CXX_PLATFORM_ID STREQUAL "MinGWx")
      target_compile_options(${CURTGT} PUBLIC -static-libgcc)
      target_compile_options(${CURTGT} PUBLIC -static-libstdc++)
    endif()
  elseif((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang"))
    target_compile_options(${CURTGT} PUBLIC -Wstrict-overflow=0)
    target_compile_options(${CURTGT} PUBLIC -ffast-math)
    target_compile_options(${CURTGT} PUBLIC -Wall)
    target_compile_options(${CURTGT} PUBLIC -O3)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    target_compile_options(${CURTGT} PUBLIC -Wall)
    target_compile_options(${CURTGT} PUBLIC -O3)
  elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(FATAL_ERROR "MSVC not currently supported")
  endif()
endforeach(CURTGT)

# Add link requirements for examples using the mrraster library (not just headers)
foreach(CURTGT IN LISTS TARGETS_REQ_MRRL)
  target_link_libraries(${CURTGT} mrr)
endforeach(CURTGT)

# Add build requirements for examples using OpenGL
if(OpenGL_FOUND AND GLUT_FOUND)
  foreach(CURTGT IN LISTS TARGETS_REQ_OPENGL)
    target_include_directories(${CURTGT} PRIVATE ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIR} )
    target_link_libraries(${CURTGT} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
  endforeach(CURTGT)
endif()

# Add builtd requirements for examples using OpenMP
if (OPENMP_FOUND)
  foreach(CURTGT IN LISTS TARGETS_REQ_OPENMP)
    target_compile_options(${CURTGT} PUBLIC ${OpenMP_CXX_FLAGS})
    target_include_directories(${CURTGT} PRIVATE ${OpenMP_INCLUDE_PATH})
    target_link_libraries(${CURTGT} ${OpenMP_CXX_LIBRARIES}) # ${PROJECT_LINK_LIBS}). 
  endforeach(CURTGT)
endif()

# Add builtd requirements for examples using libTIFF
if(TIFF_FOUND)
  foreach(CURTGT IN LISTS TARGETS_REQ_TIFF)
    target_include_directories(${CURTGT} PRIVATE ${TIFF_INCLUDE_DIRS})
    target_link_libraries(${CURTGT} ${TIFF_LIBRARIES})
  endforeach(CURTGT)
endif()

# The circles target needs drawing mode support
target_compile_definitions(circles PUBLIC SUPPORT_DRAWING_MODE=1)

######################################################################################################################################################

add_custom_target(clean-images
  COMMAND  rm -f *.tga *.tif *.tiff *.mrw *.bin
  COMMENT "Cleaning Image files"
)

######################################################################################################################################################

# Add targets using povray

######################################################################################################################################################

# Add targets making movies

######################################################################################################################################################
# Generate an include file with various methdata about the build.  

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.hpp.cmake ${CMAKE_BINARY_DIR}/config.hpp)

######################################################################################################################################################

# Add targets for documentation
if(Doxygen_FOUND)
  foreach(DOXINPUT IN ITEMS "lib" "examples")
    message("Info: Generateing doxygen target for ${DOXINPUT}")
    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Doxyfile.cmake ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}/Doxyfile)
    add_custom_target(doc-${DOXINPUT}
      COMMAND ${DOXYGEN_EXECUTABLE} > dox.out
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/doc-${DOXINPUT}
      COMMENT "Generating documentation with Doxygen"
      VERBATIM)
  endforeach(DOXINPUT)
else()
  message("Warning: Doxygen not found.  No documentation targets!")
endif()


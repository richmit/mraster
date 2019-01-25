
#ifndef CONFIG_H
#define CONFIG_H


#cmakedefine TIFF_FOUND
#cmakedefine OpenMP_FOUND
#cmakedefine OpenGL_FOUND
#cmakedefine Doxygen_FOUND
#cmakedefine ImageMagick_FOUND
#cmakedefine PNG_FOUND

#define PROJECT_DATE      @PROJECT_VERSION_DATE@
#define PROJECT_VERSION   @PROJECT_VERSION_ID@
#define PROJECT_NAME      "@CMAKE_PROJECT_NAME@"

#endif

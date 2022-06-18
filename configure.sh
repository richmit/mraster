#!/bin/bash

# Use: configure.sh [TARGET_TYPE]
#
#      TARGET_TYPE is the cmake -G option
#
# If TARGET_TYPE is not provided, then
#   * If $MSYSTEM is set, "MSYS Makefiles" will be used
#   * Otherwise, no -G will be the system default

FORCE_BUILD=

if [ -e examples -a -e lib -a -e CMakeLists.txt ] ; then
  if [ -n "$FORCE_BUILD" -a -e build ] ; then
    echo "The 'build' directory already exists.  Remove it, and run this script again."
  else
    mkdir build
    cd build

    if [ -n "$MSYSTEM" ] ; then
      CMAKE_G='MSYS Makefiles'
    fi
    if [ -n "$1" ] ; then
      CMAKE_G=$1
    fi

    if [ -n "$CMAKE_G" ] ; then
      cmake -G "$CMAKE_G" ../
    else
      cmake ../
    fi

    echo "Now: 'cd build' & make soemthing!"
  fi
else
    echo "Can't find one or more of examples/, lib/, or CMakeLists.txt.  Are you in the correct directory?"
fi

#!/bin/bash

if [ -e examples -a -e lib -a -e CMakeLists.txt ] ; then
  if [ -e build ] ; then
    echo "The 'build' directory already exists.  Remove it, and run this script again."
  else
    mkdir build
    cd build
    cmake -G 'MSYS Makefiles' ../
    echo "Now: 'cd build' & make soemthing!"
  fi
else
    echo "Can't find one or more of examples/, lib/, or CMakeLists.txt.  Are you in the correct directory?"
fi


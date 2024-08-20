#!/bin/sh

# This little script publishes the doxygen documentation on the web
#  - Make sure "PROJECT_VERSION_ID" in CMakeLists.txt is set to the tag-name
#  - Make sure the doxygen documentation has been deployed with the correct tag-name
#  - Make sure next-tag.org file exists for the tag comment

if [ -e ~/world/my_prog/mraster/build ]; then
  cd ~/world/my_prog/mraster/build
  if [ -e ~/Documents/WWW/site/SS/mraster/ ];  then
    make doc-lib
    make doc-examples
    if [ -e doc-lib/autodocs/html/index.html -a -e doc-examples/autodocs/html/index.html ]; then
      rm -rf ~/Documents/WWW/site/SS/mraster/doc-lib
      rm -rf ~/Documents/WWW/site/SS/mraster/doc-examples
      mv doc-lib doc-examples/ ~/Documents/WWW/site/SS/mraster/
      echo "INFO: Documentation deployed:"
      ls -ld ~/Documents/WWW/site/SS/mraster/doc-*
    else
      echo "ERROR: Could not find generated doxygen documentation!"
    fi
  else
    echo "ERROR: Could not find mraster web directory: ~/Documents/WWW/site/SS/mraster/"
  fi
else
  echo "ERROR: Could not find mraster build directory: ~/world/my_prog/mraster/build"
fi

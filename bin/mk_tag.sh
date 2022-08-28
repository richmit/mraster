#!/bin/sh

# This script helps me create new tags (releases) for MRaster.  In particular:
#  - Make sure "PROJECT_VERSION_ID" in CMakeLists.txt is set to the tag-name
#  - Make sure the doxygen documentation has been deployed with the correct tag-name
#  - Make sure next-tag.org file exists for the tag comment

# If we don't have a CMakeLists.txt, then we are in the wrong directory.
if [ -e CMakeLists.txt ]; then
  echo "Found CMakeLists.txt"
else
  echo "Could not find CMakeLists.txt!"
  exit
fi

# Get the tag name out of CMakeLists.txt
TAG_NAME=$(grep '^set(PROJECT_VERSION_ID' CMakeLists.txt | sed 's/^.* //; s/)$//')

# Make sure the tag doesn't already exist
if git show-ref --tags "$TAG_NAME" --quiet; then
  echo "Tag already exists!!"
  exit
fi

# Make sure the tag is in the doxygen documentation too
if grep -Fq "PROJECT_NAME           = \"MRaster $TAG_NAME lib\"" ~/world/WWW/site/SS/mraster/doc-lib/Doxyfile; then
  echo "Deployed doxygen documentation has correct tag string"
else
  echo "Deployed doxygen documentation has incorrect tag string:"
  echo "   ~/world/WWW/site/SS/mraster/doc-lib/Doxyfile:"
  grep "^PROJECT_NAME" ~/world/WWW/site/SS/mraster/doc-lib/Doxyfile | sed 's/^/   /'
  exit
fi

# We need the next-tag.org file for the tag comment.
if [ -e next-tag.org ]; then
  echo "Found next-tag.org"
else
  echo "Could not find next-tag.org!"
  exit
fi

if git diff-index --quiet HEAD; then
  echo "git state is clean"
else
  echo "git state is unclean."
  git status  
  exit
fi

# Actually do something. :)
git tag "$TAG_NAME" -F next-tag.org

# Tell the world the good news.
echo "TAG CREATED WITH FOLLOWING COMMIT MESSAGE:"
echo "================================================================================"
cat next-tag.org
echo "================================================================================"

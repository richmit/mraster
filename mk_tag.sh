#!/bin/sh

# This script helps me create new tags (releases) for MRaster.  In particular:
#  - Make sure "PROJECT_VERSION_ID" in CMakeLists.txt is set to the tag-name
#  - Make sure the doxygen documentation has been deployed with the correct tag-name
#  - Make sure next-tag.org file exists for the tag comment

TAG_NAME="$1"

if git show-ref --tags "$TAG_NAME" --quiet; then
  echo "Tag already exists!!"
  exit
fi

if [ -e CMakeLists.txt ]; then
  echo "Found CMakeLists.txt"
else
  echo "Could not find CMakeLists.txt!"
  exit
fi

if grep -Fq "set(PROJECT_VERSION_ID    $TAG_NAME)" CMakeLists.txt; then
  echo "CMakeLists.txt has correct tag string"
else
  echo "CMakeLists.txt has incorrect tag string:"
  grep '^set(PROJECT_VERSION_ID' CMakeLists.txt | sed 's/^/   /'
  exit
fi

if grep -Fq "PROJECT_NAME           = \"MRaster $TAG_NAME lib\"" ~/world/WWW/site/SS/mraster/doc-lib/Doxyfile; then
  echo "Deployed doxygen documentation has correct tag string"
else
  echo "Deployed doxygen documentation has incorrect tag string:"
  echo "   ~/world/WWW/site/SS/mraster/doc-lib/Doxyfile:"
  grep "^PROJECT_NAME" ~/world/WWW/site/SS/mraster/doc-lib/Doxyfile | sed 's/^/   /'
  exit
fi

if [ -e next-tag.org ]; then
  echo "Found next-tag.org"
else
  echo "Could not find next-tag.org!"
  exit
fi

git tag "$TAG_NAME" -F next-tag.org

echo "TAG CREATED WITH FOLLOWING COMMIT MESSAGE:"
echo "================================================================================"
cat next-tag.org
echo "================================================================================"



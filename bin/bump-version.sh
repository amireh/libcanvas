#!/usr/bin/env bash
#
# Helper script for bumping up the version of libcanvas.
#
# Usage: ./bin/bump-version.sh [major|minor|patch|build]

function print_usage {
  echo "Usage: ./bump-version.sh [major|minor|patch|build]"
}

# Replace version strings in the source CMakeLists.txt
#
# @param [Integer] Major version number
# @param [Integer] Minor version number
# @param [Integer] Patch version number
# @param [String] Build version identifier
# @param [String] /path/to/CMakeLists.txt
function bump_cmake {
  perl -p -i -e "s/CANVAS_VERSION_MAJOR \w+/CANVAS_VERSION_MAJOR ${1}/" "${5}"
  perl -p -i -e "s/CANVAS_VERSION_MINOR \w+/CANVAS_VERSION_MINOR ${2}/" "${5}"
  perl -p -i -e "s/CANVAS_VERSION_PATCH \w+/CANVAS_VERSION_PATCH ${3}/" "${5}"
  perl -p -i -e "s/CANVAS_VERSION_BUILD \"?\w+\"?/CANVAS_VERSION_BUILD \"${4}\"/" "${5}"
}

# Replace version string in Doxygen's config file (Doxyfile)
#
# @param [String] version string
# @param [String] /path/to/Doxyfile
function bump_doxygen {
  perl -p -i -e "s/PROJECT_NUMBER(\s+)=.*\$/PROJECT_NUMBER\$1= ${1}/" "${2}"
}

CONFIG_FILE="include/canvas/canvas_config.hpp"

if [ ! -f "${CONFIG_FILE}" ]; then
  echo "Error: unable to find config file to parse the version string from."
  echo "Expected location: ${CONFIG_FILE}"
  echo "Aborting."
  exit 1
fi

VERSIONS=($(cat "${CONFIG_FILE}" | grep VERSION_ | awk '{print $3}'))

VMAJOR=${VERSIONS[0]}
VMINOR=${VERSIONS[1]}
VPATCH=${VERSIONS[2]}
VBUILD=${VERSIONS[3]//\"/}

case "$1" in
  major)
    echo "Performing a Major release bump."
    VMAJOR=$((VMAJOR+1))
  ;;
  minor)
    echo "Performing a Minor release bump."
    VMINOR=$((VMINOR+1))
  ;;
  patch)
    echo "Performing a Patch release bump."
    VPATCH=$((VPATCH+1))
  ;;
  build)
    echo "Performing a Build release bump."
    case "${VBUILD}" in
      a)
        VBUILD="b"
      ;;
      b)
        VBUILD="c"
      ;;
      c)
        VBUILD="d"
      ;;
      *)
        echo "Error: build fragment is already at the latest (d)"
        exit 1
    esac
  ;;
  *)
    print_usage
    exit 1
esac

VERSION="${VMAJOR}.${VMINOR}.${VPATCH}-${VBUILD}"

echo "Next release will be: ${VERSION}"
echo -n "Continue? [Y/n] "
read confirmation

if [ "${confirmation}" == "n" ]; then
  echo "Cancelled."
  exit 0
fi

bump_cmake $VMAJOR $VMINOR $VPATCH $VBUILD ./CMakeLists.txt
bump_doxygen "${VERSION}" ./Doxyfile

echo "CMake and Doxygen config files have been updated, you should now re-run cmake."
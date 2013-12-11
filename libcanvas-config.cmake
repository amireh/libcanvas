# Locate canvas Shared library
#
# This module defines:
#  CANVAS_FOUND, if false, do not try to link to canvas
#  CANVAS_LIBRARY
#  CANVAS_INCLUDE_DIRS, where to find canvas/canvas.hpp

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR} )

FIND_PACKAGE(YAJL REQUIRED)
FIND_PACKAGE(CURL REQUIRED)

SET(CANVAS_PATHS
  /usr
  /usr/local
  /usr/local/libcanvas
  /opt
  /opt/local
  /opt/local/libcanvas
)

FIND_PATH(CANVAS_INCLUDE_DIR canvas/canvas.hpp
  HINTS
  PATH_SUFFIXES include
  PATHS
  ${CANVAS_PATHS}
)

FIND_LIBRARY(CANVAS_LIBRARY
  NAMES canvas
  HINTS
  PATH_SUFFIXES lib
  PATHS
  ${CANVAS_PATHS}
)

IF(CANVAS_LIBRARY AND CANVAS_INCLUDE_DIR)
  SET(CANVAS_INCLUDE_DIRS
      ${CANVAS_INCLUDE_DIR}
      ${YAJL_INCLUDE_DIRS}
      ${CURL_INCLUDE_DIRS})

  SET(CANVAS_LIBRARIES
    ${CANVAS_LIBRARY}
    ${YAJL_LIBRARIES}
    ${CURL_LIBRARIES})

  SET( CANVAS_FOUND TRUE )
  MESSAGE(STATUS "Found libcanvas")
ELSE()
  MESSAGE(STATUS "Error! Could not find libcanvas")
ENDIF()

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(libcanvas
  DEFAULT_MSG
  CANVAS_LIBRARY
  CANVAS_INCLUDE_DIR)

MARK_AS_ADVANCED(CANVAS_INCLUDE_DIR CANVAS_LIBRARY)

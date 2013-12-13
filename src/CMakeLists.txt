SET(CANVAS_INCLUDE_DIR "../include/canvas")
SET(CANVAS_SRC
  ${CANVAS_INCLUDE_DIR}/http/response.hpp
  ${CANVAS_INCLUDE_DIR}/parsers/course_parser.hpp
  ${CANVAS_INCLUDE_DIR}/resources/course.hpp
  ${CANVAS_INCLUDE_DIR}/canvas.hpp
  ${CANVAS_INCLUDE_DIR}/exception.hpp
  ${CANVAS_INCLUDE_DIR}/file_manager.hpp
  ${CANVAS_INCLUDE_DIR}/logger.hpp
  ${CANVAS_INCLUDE_DIR}/parser.hpp
  ${CANVAS_INCLUDE_DIR}/resource.hpp
  ${CANVAS_INCLUDE_DIR}/session.hpp
  ${CANVAS_INCLUDE_DIR}/settings.hpp
  ${CANVAS_INCLUDE_DIR}/utility.hpp

  parsers/course_parser.cpp
  resources/course.cpp
  file_manager.cpp
  logger.cpp
  parser.cpp
  session.cpp
  settings.cpp
)

# the executable
ADD_LIBRARY(canvas SHARED ${CANVAS_SRC})
#~ ADD_LIBRARY(algol_static STATIC ${CANVAS_SRC})

SET_TARGET_PROPERTIES(canvas PROPERTIES VERSION ${CANVAS_VERSION})

INSTALL(TARGETS canvas LIBRARY DESTINATION lib)
#~ INSTALL(TARGETS algol_static ARCHIVE DESTINATION lib)

MESSAGE(STATUS "Version: " ${CANVAS_VERSION})

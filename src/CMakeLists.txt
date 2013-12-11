# add sources
SET(CANVAS_SRC
  ../include/canvas/canvas.hpp
  logger.cpp
  settings.cpp
  session.cpp
)

# the executable
ADD_LIBRARY(canvas SHARED ${CANVAS_SRC})
#~ ADD_LIBRARY(algol_static STATIC ${CANVAS_SRC})

SET_TARGET_PROPERTIES(canvas PROPERTIES VERSION ${CANVAS_VERSION})

INSTALL(TARGETS canvas LIBRARY DESTINATION lib)
#~ INSTALL(TARGETS algol_static ARCHIVE DESTINATION lib)

MESSAGE(STATUS "Version: " ${CANVAS_VERSION})

SET(CANVAS_INCLUDE_DIR "../include/canvas")
SET(CANVAS_SRC
  ${CANVAS_INCLUDE_DIR}/http/response.hpp
  ${CANVAS_INCLUDE_DIR}/resources/course.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_submission.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_question.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_question_prototypes/answerable.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/multiple_choice.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/true_false.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_question_answer.hpp
  ${CANVAS_INCLUDE_DIR}/resources/student.hpp
  ${CANVAS_INCLUDE_DIR}/canvas.hpp
  ${CANVAS_INCLUDE_DIR}/exception.hpp
  ${CANVAS_INCLUDE_DIR}/file_manager.hpp
  ${CANVAS_INCLUDE_DIR}/logger.hpp
  ${CANVAS_INCLUDE_DIR}/resource_parser.hpp
  ${CANVAS_INCLUDE_DIR}/resource.hpp
  ${CANVAS_INCLUDE_DIR}/session.hpp
  ${CANVAS_INCLUDE_DIR}/settings.hpp
  ${CANVAS_INCLUDE_DIR}/utility.hpp

  resources/course.cpp
  resources/quiz.cpp
  resources/quiz_submission.cpp
  resources/quiz_question.cpp
  resources/quiz_question_prototypes/answerable.cpp
  resources/quiz_questions/multiple_choice.cpp
  resources/quiz_questions/true_false.cpp
  resources/quiz_question_answer.cpp
  resources/student.cpp
  canvas.cpp
  file_manager.cpp
  logger.cpp
  resource.cpp
  resource_parser.cpp
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

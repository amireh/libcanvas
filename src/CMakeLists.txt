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
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/fill_in_the_blank.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/fill_in_multiple_blanks.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/essay.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/calculated.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/numerical.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/matching.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/multiple_dropdowns.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_questions/multiple_answers.hpp
  ${CANVAS_INCLUDE_DIR}/resources/quiz_question_answer.hpp
  ${CANVAS_INCLUDE_DIR}/resources/calculated_answer.hpp
  ${CANVAS_INCLUDE_DIR}/resources/matching_answer.hpp
  ${CANVAS_INCLUDE_DIR}/resources/student.hpp
  ${CANVAS_INCLUDE_DIR}/canvas.hpp
  ${CANVAS_INCLUDE_DIR}/exception.hpp
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
  resources/quiz_questions/fill_in_the_blank.cpp
  resources/quiz_questions/fill_in_multiple_blanks.cpp
  resources/quiz_questions/essay.cpp
  resources/quiz_questions/calculated.cpp
  resources/quiz_questions/numerical.cpp
  resources/quiz_questions/matching.cpp
  resources/quiz_questions/multiple_dropdowns.cpp
  resources/quiz_questions/multiple_answers.cpp
  resources/quiz_question_answer.cpp
  resources/calculated_answer.cpp
  resources/matching_answer.cpp
  resources/student.cpp
  canvas.cpp
  logger.cpp
  resource.cpp
  resource_parser.cpp
  session.cpp
  settings.cpp
)

IF (CANVAS_SHARED)
  ADD_LIBRARY(canvas SHARED ${CANVAS_SRC})
ELSE()
  ADD_LIBRARY(canvas STATIC ${CANVAS_SRC})
ENDIF()

SET_TARGET_PROPERTIES(canvas PROPERTIES VERSION ${CANVAS_VERSION})

IF (CANVAS_SHARED)
  INSTALL(TARGETS canvas LIBRARY DESTINATION lib)
ELSE()
  INSTALL(TARGETS canvas ARCHIVE DESTINATION lib)
ENDIF()

MESSAGE(STATUS "Version: " ${CANVAS_VERSION})

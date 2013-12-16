#include <gtest/gtest.h>
#include "canvas/resources/course.hpp"
#include "canvas/parsers/course_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class course_test : public ::testing::Test {
  protected:
    course* course_;
    course_parser course_parser_;
    session session_;
  };

  TEST_F(course_test, load_quizzes) {
    course_ = course_parser_.from_json(load_fixture("course.json"));
    session_.authenticate(CANVAS_SPEC_API_TOKEN);

    ASSERT_NO_THROW(
      course_->load_quizzes(session_, [&](bool success) {
        ASSERT_TRUE(success);
        ASSERT_TRUE(course_->get_quizzes().size() > 0);
      });
    );

    delete course_;
  }
} // namespace cnvs
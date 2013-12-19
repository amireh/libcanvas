#include <gtest/gtest.h>
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class course_test : public ::testing::Test {
  protected:
    course* course_;
    resource_parser parser_;
    session session_;
  };

  TEST_F(course_test, load_quizzes) {
    course_ = parser_.parse_resource<course>(load_fixture("course.json"));
    session_.authenticate(CANVAS_SPEC_API_TOKEN);

    ASSERT_NO_THROW(
      course_->load_quizzes(session_, [&](bool success) {
        ASSERT_TRUE(success);
      });
    );

    delete course_;
  }

  TEST_F(course_test, deserialize) {
    string_t json = load_fixture("course.json");

    ASSERT_NO_THROW(course_ = parser_.parse_resource<course>(json););
    ASSERT_TRUE(course_);
    ASSERT_EQ(course_->id(), 1);
    ASSERT_EQ(course_->get_name(), "Linear Algebra");
    ASSERT_EQ(course_->get_code(), "Linear");
    ASSERT_EQ(course_->get_workflow_state(), "available");

    delete course_;
  }

  TEST_F(course_test, bulk_parsing) {
    string_t json = load_fixture("courses.json");
    std::vector<course*> courses = parser_.parse_resources<course>(json);

    ASSERT_EQ(courses.size(), 2);
    ASSERT_EQ(courses.at(0)->id(), 1);
    ASSERT_EQ(courses.at(1)->id(), 2);

    std::for_each(courses.begin(), courses.end(), [](course* c) { delete c; });
    courses.clear();
  }
} // namespace cnvs
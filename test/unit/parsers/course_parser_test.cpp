#include <gtest/gtest.h>
#include "canvas/session.hpp"
#include "canvas/file_manager.hpp"
#include "canvas/parsers/course_parser.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class course_parser_test : public ::testing::Test {
  protected:
    session session_;
    course_parser parser_;
    course* course_;
  };

  TEST_F(course_parser_test, from_json) {
    string_t json = load_fixture("course.json");

    ASSERT_NO_THROW(course_ = parser_.from_json(json););
    ASSERT_TRUE(course_);
    ASSERT_EQ(course_->id(), 1);
    ASSERT_EQ(course_->get_name(), "Linear Algebra");
    ASSERT_EQ(course_->get_code(), "Linear");
    ASSERT_EQ(course_->get_workflow_state(), "available");

    delete course_;
  }

  TEST_F(course_parser_test, from_json_collection) {
    string_t json = load_fixture("courses.json");
    parser::json_documents_t json_courses;

    ASSERT_NO_THROW(json_courses = parser_.json_documents(json));
    ASSERT_EQ(json_courses.size(), 1);
    ASSERT_NO_THROW(course_ = parser_.from_json(json_courses.front()););
    ASSERT_TRUE(course_);
    ASSERT_EQ(course_->id(), 1);
    ASSERT_EQ(course_->get_name(), "Linear Algebra");
    ASSERT_EQ(course_->get_code(), "Linear");
    ASSERT_EQ(course_->get_workflow_state(), "available");

    delete course_;
  }
} // namespace cnvs
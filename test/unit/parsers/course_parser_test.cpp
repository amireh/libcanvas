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

  TEST_F(course_parser_test, bulk_parsing) {
    string_t json = load_fixture("courses.json");
    std::vector<course*> courses = parser_.parse_resources<course>(json);

    ASSERT_EQ(courses.size(), 2);
    ASSERT_EQ(courses.at(0)->id(), 1);
    ASSERT_EQ(courses.at(1)->id(), 2);

    std::for_each(courses.begin(), courses.end(), [](course* c) { delete c; });
    courses.clear();
  }
} // namespace cnvs
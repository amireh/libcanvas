#include <gtest/gtest.h>
#include "canvas/session.hpp"
#include "canvas/file_manager.hpp"
#include "canvas/parsers/course_parser.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class course_parser_test : public ::testing::Test {
  protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    session session_;
    course_parser parser_;
    course* course_;
  };

  TEST_F(course_parser_test, from_json) {
    session_.authenticate(CANVAS_SPEC_API_TOKEN);

    string_t json;
    ASSERT_TRUE(file_manager::singleton().load_file(fixture("course.json"), json));

    ASSERT_NO_THROW(course_ = parser_.from_json(json););

    ASSERT_TRUE(course_);
    ASSERT_TRUE(course_->id() == 1);
    ASSERT_TRUE(course_->name() == "Linear Algebra");
    ASSERT_TRUE(course_->code() == "Linear");
    ASSERT_TRUE(course_->workflow_state() == "available");
    delete course_;
  }
} // namespace cnvs
#include <gtest/gtest.h>
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class course_test : public ::testing::Test {
  protected:
    Course* mCourse;
    ResourceParser parser_;
    Session mSession;
  };

  TEST_F(course_test, loadQuizzes) {
    mCourse = parser_.parseResource<Course>(load_fixture("course.json"));
    mSession.authenticate(CANVAS_SPEC_API_TOKEN);

    ASSERT_NO_THROW(
      mCourse->loadQuizzes(mSession, [&](bool success) {
        ASSERT_TRUE(success);
      });
    );

    delete mCourse;
  }

  TEST_F(course_test, deserialize) {
    String json = load_fixture("course.json");

    ASSERT_NO_THROW(mCourse = parser_.parseResource<Course>(json););
    ASSERT_TRUE(mCourse);
    ASSERT_EQ(mCourse->id(), 1);
    ASSERT_EQ(mCourse->name(), "Linear Algebra");
    ASSERT_EQ(mCourse->code(), "Linear");
    ASSERT_EQ(mCourse->workflowState(), "available");

    delete mCourse;
  }

  TEST_F(course_test, bulk_parsing) {
    String json = load_fixture("courses.json");
    std::vector<Course*> courses = parser_.parseResources<Course>(json);

    ASSERT_EQ(courses.size(), 2);
    ASSERT_EQ(courses.at(0)->id(), 1);
    ASSERT_EQ(courses.at(1)->id(), 2);

    std::for_each(courses.begin(), courses.end(), [](Course* c) { delete c; });
    courses.clear();
  }
} // namespace cnvs

#include <gtest/gtest.h>
#include "canvas/resources/student.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class student_test : public ::testing::Test {
  protected:
    Student student;
    ResourceParser parser;
    Session session;
  };

  TEST_F(student_test, loadCourses) {
    session.authenticate(CANVAS_SPEC_API_TOKEN);

    ASSERT_NO_THROW(
      student.loadCourses(session, [&](bool success) {
        ASSERT_TRUE(success);
        ASSERT_NE(student.courses().size(), 0);
      });
    );
  }

  TEST_F(student_test, loadIdentity) {
    session.authenticate(CANVAS_SPEC_API_TOKEN);

    ASSERT_NO_THROW(
      student.loadIdentity(session, [&](bool success) {
        ASSERT_TRUE(success);
        ASSERT_NE(student.id(), 0);
      });
    );
  }

} // namespace cnvs

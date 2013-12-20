#include <gtest/gtest.h>
#include "canvas/resources/student.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class StudentTest : public ::testing::Test {
  public:
    StudentTest() {
      student.setApiToken(CANVAS_SPEC_API_TOKEN);
      session.authenticate(student);
    }

  protected:
    Student student;
    ResourceParser parser;
    Session session;
  };

  TEST_F(StudentTest, loadCourses) {
    ASSERT_NO_THROW(
      student.loadCourses(session, [&](bool success) {
        ASSERT_TRUE(success);
        ASSERT_NE(student.courses().size(), 0);
      });
    );
  }

  TEST_F(StudentTest, loadIdentity) {
    ASSERT_NO_THROW(
      student.loadIdentity(session, [&](bool success) {
        ASSERT_TRUE(success);
        ASSERT_NE(student.id(), 0);
      });
    );
  }

  TEST_F(StudentTest, loadQuizSubmission) {
    Course course(1);
    Quiz quiz(1, &course);

    ASSERT_NO_THROW(
      student.loadQuizSubmission(session, quiz, [&](bool success) {
        ASSERT_TRUE(success);
        ASSERT_NE(student.quizSubmission(quiz), nullptr);
      });
    );
  }
} // namespace cnvs

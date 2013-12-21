#include <gtest/gtest.h>
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class QuizTest : public ::testing::Test {
  public:
    QuizTest() : mCourse(1) {
      mSession.authenticate(CANVAS_SPEC_API_TOKEN);
    }
  protected:
    Course mCourse;
    Quiz mQuiz;
    ResourceParser mParser;
    Session mSession;
  };

  TEST_F(QuizTest, loadQuestions) {
    mQuiz.setCourse(&mCourse);
    mQuiz.deserialize(loadFixture("quiz.json"));

    ASSERT_NO_THROW(
      mQuiz.loadQuestions(loadFixture("quiz_questions.json"));
    );

    ASSERT_NE(mQuiz.questions().size(), 0);
  }

  TEST_F(QuizTest, remotelyLoadsQuestions) {
    mQuiz.setCourse(&mCourse);
    mQuiz.deserialize(loadFixture("quiz.json"));

    ASSERT_NO_THROW(
      mQuiz.loadQuestions(mSession, [&](bool success) {
        ASSERT_TRUE(success);
        ASSERT_NE(mQuiz.questions().size(), 0);
      });
    );
  }

  TEST_F(QuizTest, deserialize) {
    ASSERT_NO_THROW(mQuiz.deserialize(loadFixture("quiz.json")););
    ASSERT_EQ(mQuiz.id(), 1);
    ASSERT_EQ(mQuiz.title(), "CNVS-9750");
  }

} // namespace cnvs

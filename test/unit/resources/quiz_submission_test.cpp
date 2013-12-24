#include <gtest/gtest.h>
#include "canvas/resources/quiz_submission.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"
#include "hippomocks.h"

namespace Canvas {

  class QuizSubmissionTest : public ::testing::Test {
  public:
    QuizSubmissionTest() : course(), quiz() {
      course.deserialize(loadFixture("course.json"));
      quiz.deserialize(loadFixture("quiz.json"));
      quiz.loadQuestions(loadFixture("quiz_questions.json"));
    }

  protected:
    Course course;
    Quiz quiz;
  };

  TEST_F(QuizSubmissionTest, deserialize) {
    QuizSubmission qs;

    ASSERT_NO_THROW(
      qs.deserialize(loadFixture("quiz_submission.json"));
    );

    ASSERT_EQ(qs.attempt(), 15);
    ASSERT_EQ(qs.startedAt(), "2013-12-23T11:55:14Z");
    ASSERT_EQ(qs.finishedAt(), "");
    ASSERT_EQ(qs.endAt(), "");
    ASSERT_EQ(qs.validationToken(), "37a09785de80dc1a9b04c3ba495cf6df92fc6fd1a0535ec9eb9b7bb5092991c5");
    ASSERT_EQ(qs.score(), 0);
    ASSERT_EQ(qs.keptScore(), 6.16666666666667);
    ASSERT_EQ(qs.submissionId(), 1);
    ASSERT_EQ(qs.userId(), 2);
    ASSERT_EQ(qs.isComplete(), false);
    ASSERT_EQ(qs.isTakeable(), true);
    ASSERT_EQ(qs.isPendingReview(), false);
  }

  TEST_F(QuizSubmissionTest, saveWithQq) {
    MockRepository mocks;
    Session *session = mocks.InterfaceMock<Session>();

    QuizSubmission qs(1, &quiz);
    QuizQuestion const* qq = quiz.questions()[0];

    mocks.ExpectCall(session, Session::put).Return(1);

    ASSERT_NO_THROW(qs.save(qq, *session););
  }

  TEST_F(QuizSubmissionTest, loadAnswers) {
    QuizSubmission qs(1, &quiz);

    ASSERT_NO_THROW(
      qs.deserialize(loadFixture("quiz_submission.json"));
      qs.loadAnswers(loadFixture("quiz_submission_questions.json"));
    );
  }

} // namespace Canvas

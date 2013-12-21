#include <gtest/gtest.h>
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_submission.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class QuizQuestionTest : public ::testing::Test {
  public:
    QuizQuestionTest() {
    }

  protected:
    ResourceParser mParser;
  };

  TEST_F(QuizQuestionTest, deserialize) {
    QuizQuestion* qq = mParser.parseResource<QuizQuestion>(loadFixture("quiz_question.json"));

    ASSERT_EQ(qq->id(), 1);
    ASSERT_EQ(qq->name(), "MC Q");
    ASSERT_EQ(qq->type(), "multiple_choice_question");
    ASSERT_EQ(qq->text(), "<p>A, B, C, or D?</p>");
    ASSERT_EQ(qq->pointsPossible(), 1);
    ASSERT_EQ(qq->correctComments(), "Correct");
    ASSERT_EQ(qq->incorrectComments(), "Incorrect");
    ASSERT_EQ(qq->neutralComments(), "Donno");
    ASSERT_EQ(qq->groupId(), 0);

    delete qq;
  }

  TEST_F(QuizQuestionTest, buildsUrlWhenQuizIsSet) {
    QuizQuestion qq;
    Course course(1);
    Quiz quiz(1, &course);

    ASSERT_EQ(qq.url(), "");

    qq.deserialize(loadFixture("quiz_question.json"));
    ASSERT_EQ(qq.url(), "");

    qq.setQuiz(&quiz);
    ASSERT_EQ(qq.url(), "/courses/1/quizzes/1/questions/1");
  }

  TEST_F(QuizQuestionTest, answerUrl) {
    QuizQuestion qq;
    QuizSubmission qs(1);

    qq.deserialize(loadFixture("quiz_question.json"));
    ASSERT_EQ(qq.answerUrl(qs), "/quiz_submissions/1/questions/1");
  }

} // namespace cnvs

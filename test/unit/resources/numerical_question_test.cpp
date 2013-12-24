#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/numerical.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/numerical.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/numerical.json");

  TEST(NumericalQuizQuestionTest, deserializeAnswer) {
    Numerical qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_EQ(qq.answer(), 22.1);
  }

  TEST(NumericalQuizQuestionTest, setAnswer) {
    Numerical qq;

    qq.deserialize(questionFixture);

    ASSERT_EQ(qq.answer(), 0.0);

    qq.setAnswer(12.4);
    ASSERT_EQ(qq.answer(), 12.4);

    qq.setAnswer(0);
    ASSERT_EQ(qq.answer(), 0);
  }

  TEST(NumericalQuizQuestionTest, serializeAnswer) {
    Numerical qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.setAnswer(33.24);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_EQ(document["answer"].asDouble(), 33.24);
  }

} // namespace QuizQuestions
} // namespace Canvas

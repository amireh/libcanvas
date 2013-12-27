#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/fill_in_the_blank.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/fill_in_the_blank.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/fill_in_the_blank.json");

  TEST(FillInTheBlankQuizQuestionTest, deserializesAnswers) {
    FillInTheBlank qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );
  }

  TEST(FillInTheBlankQuizQuestionTest, deserializeAnswer) {
    FillInTheBlank qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_EQ(qq.filledAnswer(), "Foobar.");
  }

  TEST(FillInTheBlankQuizQuestionTest, fill) {
    FillInTheBlank qq;

    qq.deserialize(questionFixture);

    ASSERT_EQ(qq.filledAnswer(), "");

    qq.fill("Hi.");
    ASSERT_EQ(qq.filledAnswer(), "Hi.");

    qq.fill("Bye.");
    ASSERT_EQ(qq.filledAnswer(), "Bye.");
  }

  TEST(FillInTheBlankQuizQuestionTest, serializeAnswer) {
    FillInTheBlank qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.fill("Hi.");

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_EQ(document["answer"].asString(), "Hi.");
  }

  TEST(FillInTheBlankQuizQuestionTest, isAnswered) {
    FillInTheBlank qq;

    qq.deserialize(questionFixture);
    ASSERT_FALSE(qq.isAnswered());
    qq.fill("Hi.");
    ASSERT_TRUE(qq.isAnswered());
  }

  TEST(FillInTheBlankQuizQuestionTest, isAnsweredFromDeserializedAnswer) {
    FillInTheBlank qq;

    qq.deserialize(questionFixture);
    qq.deserializeAnswer(answerFixture);

    ASSERT_TRUE(qq.isAnswered());
  }
} // namespace QuizQuestions
} // namespace Canvas

#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/essay.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/essay.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/essay.json");

  TEST(EssayQuizQuestionTest, deserializesAnswers) {
    Essay qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );
  }

  TEST(EssayQuizQuestionTest, deserializeAnswer) {
    Essay qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_EQ(qq.filledAnswer(), "Hello World!");
  }

  TEST(EssayQuizQuestionTest, fill) {
    Essay qq;

    qq.deserialize(questionFixture);

    ASSERT_EQ(qq.filledAnswer(), "");

    qq.fill("Hi.");
    ASSERT_EQ(qq.filledAnswer(), "Hi.");

    qq.fill("Bye.");
    ASSERT_EQ(qq.filledAnswer(), "Bye.");
  }

  TEST(EssayQuizQuestionTest, serializeAnswer) {
    Essay qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.fill("Hi.");

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_EQ(document["answer"].asString(), "Hi.");
  }

  TEST(EssayQuizQuestionTest, isAnswered) {
    Essay qq;

    qq.deserialize(questionFixture);
    ASSERT_FALSE(qq.isAnswered());
    qq.fill("Hello.");
    ASSERT_TRUE(qq.isAnswered());
  }

  TEST(EssayQuizQuestionTest, isAnsweredFromDeserializedAnswer) {
    Essay qq;

    qq.deserialize(questionFixture);
    qq.deserializeAnswer(answerFixture);

    ASSERT_TRUE(qq.isAnswered());
  }
} // namespace QuizQuestions
} // namespace Canvas

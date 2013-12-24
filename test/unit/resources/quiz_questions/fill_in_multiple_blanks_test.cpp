#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/fill_in_multiple_blanks.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/fill_in_multiple_blanks.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/fill_in_multiple_blanks.json");
  static const String answerFixture2 =
    loadFixture("quiz_submission_questions/fill_in_multiple_blanks2.json");

  TEST(FillInMultipleBlanksQuizQuestionTest, deserialize) {
    FillInMultipleBlanks qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.blanks().size(), 2);
    ASSERT_EQ(qq.blanks()[0], "color1");
    ASSERT_EQ(qq.blanks()[1], "color2");
  }

  TEST(FillInMultipleBlanksQuizQuestionTest, deserializesAnswer) {
    FillInMultipleBlanks qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_EQ(qq.filledAnswer("color1"), "red");
    ASSERT_EQ(qq.filledAnswer("color2"), "green");
  }

  TEST(FillInMultipleBlanksQuizQuestionTest, deserializesAnswerWithIncompleteData) {
    FillInMultipleBlanks qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture2);
    );

    ASSERT_EQ(qq.filledAnswer("color1"), "red");
    ASSERT_EQ(qq.filledAnswer("color2"), "");
  }

  TEST(FillInMultipleBlanksQuizQuestionTest, fill) {
    FillInMultipleBlanks qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_NO_THROW(qq.fill("color1", "adooken"););
    ASSERT_EQ(qq.filledAnswer("color1"), "adooken");
  }

  TEST(FillInMultipleBlanksQuizQuestionTest, fillWithInvalidBlank) {
    FillInMultipleBlanks qq;

    ASSERT_THROW(qq.fill("color1", "adooken"), std::invalid_argument);
  }

  TEST(FillInMultipleBlanksQuizQuestionTest, serializeAnswer) {
    FillInMultipleBlanks qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.fill("color1", "Hi.");

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_TRUE(document["answer"].isMember("color1"));
    ASSERT_EQ(document["answer"]["color1"].asString(), "Hi.");
    ASSERT_EQ(document["answer"]["color2"].asString(), "");
  }
} // namespace QuizQuestions
} // namespace Canvas

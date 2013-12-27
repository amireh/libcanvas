#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/multiple_dropdowns.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/multiple_dropdowns.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/multiple_dropdowns.json");
  static const String answerFixture2 =
    loadFixture("quiz_submission_questions/multiple_dropdowns2.json");

  TEST(MultipleDropdownsQuizQuestionTest, deserialize) {
    MultipleDropdowns qq;

    // ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    // );

    ASSERT_EQ(qq.answers().size(), 4);
    ASSERT_EQ(qq.blanks().size(), 2);
    ASSERT_EQ(qq.blanks()[0], "organ");
    ASSERT_EQ(qq.blanks()[1], "color");
  }

  TEST(MultipleDropdownsQuizQuestionTest, answersForBlank) {
    MultipleDropdowns qq;

    qq.deserialize(questionFixture);

    ASSERT_EQ(qq.answers().size(), 4);
    ASSERT_EQ(qq.answers("organ").size(), 2);
    ASSERT_EQ(qq.answers("color").size(), 2);
  }

  TEST(MultipleDropdownsQuizQuestionTest, deserializesAnswer) {
    MultipleDropdowns qq;

    qq.deserialize(questionFixture);
    qq.deserializeAnswer(answerFixture);

    ASSERT_EQ(qq.chosenAnswer("organ")->id(), 3208);
    ASSERT_EQ(qq.chosenAnswer("color"), nullptr);
  }

  TEST(MultipleDropdownsQuizQuestionTest, deserializesAnswerWithIncompleteData) {
    MultipleDropdowns qq;

    qq.deserialize(questionFixture);
    qq.deserializeAnswer(answerFixture2);

    ASSERT_EQ(qq.chosenAnswer("organ")->id(), 3208);
    ASSERT_EQ(qq.chosenAnswer("color"), nullptr);
  }

  TEST(MultipleDropdownsQuizQuestionTest, choose) {
    MultipleDropdowns qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    std::vector<ID> answerIds({ 3208, 8331, 1381, 1638 });

    for (auto answerId : answerIds) {
      ASSERT_NO_THROW(qq.choose("organ", answerId););
      ASSERT_EQ(qq.chosenAnswer("organ")->id(), answerId);
    }
  }

  TEST(MultipleDropdownsQuizQuestionTest, fillWithInvalidBlank) {
    MultipleDropdowns qq;

    ASSERT_THROW(qq.choose("organ", 8331), std::invalid_argument);
  }

  TEST(MultipleDropdownsQuizQuestionTest, serializeAnswer) {
    MultipleDropdowns qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.choose("organ", 8331);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_TRUE(document["answer"].isMember("organ"));
    ASSERT_FALSE(document["answer"].isMember("color"));
    ASSERT_EQ(document["answer"]["organ"].asInt(), 8331);
  }

  TEST(MultipleDropdownsQuizQuestionTest, isAnswered) {
    MultipleDropdowns qq;

    qq.deserialize(questionFixture);
    ASSERT_FALSE(qq.isAnswered());

    qq.choose("organ", 8331);
    ASSERT_TRUE(qq.isAnswered());
  }

  TEST(MultipleDropdownsQuizQuestionTest, isAnsweredFromDeserializedAnswer) {
    MultipleDropdowns qq;

    qq.deserialize(questionFixture);
    qq.deserializeAnswer(answerFixture);

    ASSERT_TRUE(qq.isAnswered());
  }
} // namespace QuizQuestions
} // namespace Canvas

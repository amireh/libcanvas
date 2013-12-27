#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/multiple_choice.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/multiple_choice.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/multiple_choice.json");

  TEST(MultipleChoiceQuizQuestionTest, deserializesAnswers) {
    MultipleChoice qq;
    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.answers().size(), 4);
    ASSERT_EQ(qq.answers()[0]->text(), "A");
    ASSERT_EQ(qq.answers()[1]->text(), "B");
    ASSERT_EQ(qq.answers()[2]->text(), "C");
    ASSERT_EQ(qq.answers()[3]->text(), "D");
  }

  TEST(MultipleChoiceQuizQuestionTest, deserializeAnswer) {
    MultipleChoice qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_TRUE(qq.chosenAnswer());
    ASSERT_EQ(qq.chosenAnswer(), qq.answers()[1]);
    ASSERT_EQ(qq.chosenAnswer()->id(), 8899);
  }

  TEST(MultipleChoiceQuizQuestionTest, choose) {
    MultipleChoice qq;

    qq.deserialize(questionFixture);

    ASSERT_EQ(qq.chosenAnswer(), nullptr);

    qq.choose(qq.answers()[0]);
    ASSERT_EQ(qq.chosenAnswer(), qq.answers()[0]);

    qq.choose(qq.answers()[1]);
    ASSERT_EQ(qq.chosenAnswer(), qq.answers()[1]);
  }

  TEST(MultipleChoiceQuizQuestionTest, chooseWithInvalidAnswer) {
    MultipleChoice qq;
    MultipleChoice qq2;

    qq.deserialize(questionFixture);
    qq2.deserialize(loadFixture("quiz_questions/multiple_choice_2.json"));

    ASSERT_THROW(qq.choose(nullptr), std::invalid_argument);
    ASSERT_THROW(qq.choose(qq2.answers()[0]), std::invalid_argument);
  }

  TEST(MultipleChoiceQuizQuestionTest, serializeAnswer) {
    MultipleChoice qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.choose(qq.answers()[0]);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_EQ(document["answer"].asUInt(), qq.answers()[0]->id());

    qq.choose(qq.answers()[1]);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_EQ(document["answer"].asUInt(), qq.answers()[1]->id());
  }

  TEST(MultipleChoiceQuizQuestionTest, isAnswered) {
    MultipleChoice qq;

    qq.deserialize(questionFixture);
    ASSERT_FALSE(qq.isAnswered());

    qq.choose(qq.answers()[1]);
    ASSERT_TRUE(qq.isAnswered());
  }

  TEST(MultipleChoiceQuizQuestionTest, isAnsweredFromDeserializedAnswer) {
    MultipleChoice qq;

    qq.deserialize(questionFixture);
    qq.deserializeAnswer(answerFixture);

    ASSERT_TRUE(qq.isAnswered());
  }
} // namespace QuizQuestions
} // namespace Canvas

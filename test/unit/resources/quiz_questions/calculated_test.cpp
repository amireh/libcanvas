#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/calculated.hpp"
#include "canvas/resources/quiz_submission.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/calculated.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/calculated.json");

  TEST(CalculatedQuizQuestionTest, deserializesAnswers) {
    Calculated qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.answers().size(), 10);
    ASSERT_EQ(qq.answers()[0]->correctValue(), 14.7);
    ASSERT_EQ(qq.answers()[0]->variableValue("x"), 9.7);
    ASSERT_EQ(qq.answers()[0]->id(), 3979);
  }

  TEST(CalculatedQuizQuestionTest, deserializesVariables) {
    Calculated qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.variables().size(), 1);
    ASSERT_EQ(qq.variables()[0].name, "x");
    ASSERT_EQ(qq.variables()[0].min, 1);
    ASSERT_EQ(qq.variables()[0].max, 10);
    ASSERT_EQ(qq.variables()[0].precision, 2);
  }

  TEST(CalculatedQuizQuestionTest, deserializeAnswer) {
    Calculated qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_EQ(qq.answer(), 25.4);
  }

  TEST(CalculatedQuizQuestionTest, setAnswer) {
    Calculated qq;

    qq.deserialize(questionFixture);

    ASSERT_EQ(qq.answer(), 0.0);

    qq.setAnswer(12.4);
    ASSERT_EQ(qq.answer(), 12.4);

    qq.setAnswer(0);
    ASSERT_EQ(qq.answer(), 0);
  }

  TEST(CalculatedQuizQuestionTest, serializeAnswer) {
    Calculated qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.setAnswer(33.24);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_EQ(document["answer"].asDouble(), 33.24);
  }


  TEST(CalculatedQuizQuestionTest, variableValue) {
    Calculated qq;
    QuizSubmission qs(1);

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    double consistentValue = qq.variableValue(qs, qq.variable("x"));

    ASSERT_EQ(consistentValue, qq.variableValue(qs, qq.variable("x")));
  }

  TEST(CalculatedQuizQuestionTest, variableValues) {
    Calculated qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    std::vector<double> values = qq.variableValues(qq.variable("x"));

    ASSERT_EQ(values.size(), 10);
  }

  TEST(CalculatedQuizQuestionTest, isAnswered) {
    Calculated qq;

    qq.deserialize(questionFixture);
    ASSERT_FALSE(qq.isAnswered());
    qq.setAnswer(55);
    ASSERT_TRUE(qq.isAnswered());
  }

  TEST(CalculatedQuizQuestionTest, isAnsweredFromDeserializedAnswer) {
    Calculated qq;

    qq.deserialize(questionFixture);
    qq.deserializeAnswer(answerFixture);

    ASSERT_TRUE(qq.isAnswered());
  }

} // namespace QuizQuestions
} // namespace Canvas

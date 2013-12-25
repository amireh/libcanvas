#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/multiple_answers.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/multiple_answers.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/multiple_answers.json");

  TEST(MultipleAnswersQuizQuestionTest, deserialize) {
    MultipleAnswers qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.answers().size(), 3);
  }

  TEST(MultipleAnswersQuizQuestionTest, deserializeAnswer) {
    MultipleAnswers qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_EQ(qq.chosenAnswers().size(), 2);
    ASSERT_TRUE(qq.isChosen(5514));
    ASSERT_TRUE(qq.isChosen(4261));
    ASSERT_FALSE(qq.isChosen(3322));
    ASSERT_FALSE(qq.isChosen(1234));
  }

  TEST(MultipleAnswersQuizQuestionTest, choose) {
    MultipleAnswers qq;

    qq.deserialize(questionFixture);

    ASSERT_FALSE(qq.isChosen(5514));

    qq.choose(5514);
    ASSERT_TRUE(qq.isChosen(5514));

    qq.choose(4261);
    ASSERT_TRUE(qq.isChosen(4261));
  }

  TEST(MultipleAnswersQuizQuestionTest, chooseWithInvalidAnswer) {
    MultipleAnswers qq;

    qq.deserialize(questionFixture);

    ASSERT_THROW(qq.choose(nullptr), std::invalid_argument);
    ASSERT_THROW(qq.choose(123), std::invalid_argument);
    ASSERT_THROW(qq.choose((ID)0), std::invalid_argument);
  }

  TEST(MultipleAnswersQuizQuestionTest, unchoose) {
    MultipleAnswers qq;

    qq.deserialize(questionFixture);

    qq.choose(5514);
    ASSERT_TRUE(qq.isChosen(5514));

    qq.unchoose(5514);
    ASSERT_FALSE(qq.isChosen(5514));

    QuizQuestionAnswer *answer = qq.answers()[0];

    qq.choose(answer);
    ASSERT_TRUE(qq.isChosen(answer));

    qq.unchoose(answer);
    ASSERT_FALSE(qq.isChosen(answer));

    ASSERT_NO_THROW(qq.unchoose(answer););
  }

  TEST(MultipleAnswersQuizQuestionTest, serializeAnswer) {
    MultipleAnswers qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.choose(5514);
    qq.choose(4261);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););

    ASSERT_TRUE(document["answer"].isArray());
    ASSERT_EQ(document["answer"].size(), 2);
    ASSERT_TRUE(document["answer"][0].isInt());
    ASSERT_TRUE(document["answer"][1].isInt());

    ID first = document["answer"][0].asUInt();
    ID second = document["answer"][0].asUInt();

    ASSERT_TRUE(first == 5514 || first == 4261);
    ASSERT_TRUE(second == 5514 || second == 4261);
  }

  TEST(MultipleAnswersQuizQuestionTest, serializeAnswerWithNoSelection) {
    MultipleAnswers qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););

    ASSERT_TRUE(document["answer"].isNull());
  }
} // namespace QuizQuestions
} // namespace Canvas

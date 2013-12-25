#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/matching.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {
  static const String questionFixture =
    loadFixture("quiz_questions/matching.json");
  static const String answerFixture =
    loadFixture("quiz_submission_questions/matching.json");

  TEST(MatchingQuizQuestionTest, deserialize) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );
  }

  TEST(MatchingQuizQuestionTest, deserializesAnswers) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.answers().size(), 3);
  }

  TEST(MatchingQuizQuestionTest, deserializesMatches) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.matches().size(), 6);
  }

  TEST(MatchingQuizQuestionTest, deserializesDistractors) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_EQ(qq.distractors().size(), 3);
  }

  TEST(MatchingQuizQuestionTest, deserializeAnswer) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
      qq.deserializeAnswer(answerFixture);
    );

    ASSERT_EQ(qq.matchedPairs().size(), 1);
    ASSERT_EQ(qq.matchedPair(qq.findAnswer(5750)).id, 190);
    ASSERT_EQ(qq.matchedPair("Who are you waiting for?").id, 190);
  }

  TEST(MatchingQuizQuestionTest, matchPair) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_NO_THROW(qq.matchPair(qq.findAnswer(5750), 190););
    ASSERT_EQ(qq.matchedPair(qq.findAnswer(5750)).id, 190);
    ASSERT_NO_THROW(qq.matchPair(qq.findAnswer(5750), 6142););
    ASSERT_EQ(qq.matchedPair(qq.findAnswer(5750)).id, 6142);
    ASSERT_NO_THROW(qq.matchPair("What happened to Bob?", "He broke his leg."););
  }

  TEST(MatchingQuizQuestionTest, matchPairWithBadMatch) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_THROW(qq.matchPair(qq.findAnswer(5750), 123), std::invalid_argument);
    ASSERT_THROW(qq.matchPair("What happened to Bob?", "Foo."), std::invalid_argument);
  }

  TEST(MatchingQuizQuestionTest, matchPairWithBadAnswer) {
    Matching qq;

    ASSERT_NO_THROW(
      qq.deserialize(questionFixture);
    );

    ASSERT_THROW(qq.matchPair(qq.findAnswer(123), 6142), std::invalid_argument);
    ASSERT_THROW(qq.matchPair("Where?", "He broke his leg."), std::invalid_argument);
    ASSERT_THROW(qq.matchPair(nullptr, 6142), std::invalid_argument);
  }

  // TEST(MatchingQuizQuestionTest, setAnswer) {
  //   Matching qq;

  //   qq.deserialize(questionFixture);

  //   ASSERT_EQ(qq.answer(), 0.0);

  //   qq.setAnswer(12.4);
  //   ASSERT_EQ(qq.answer(), 12.4);

  //   qq.setAnswer(0);
  //   ASSERT_EQ(qq.answer(), 0);
  // }

  TEST(MatchingQuizQuestionTest, serializeAnswer) {
    Matching qq;
    JSONValue document;

    qq.deserialize(questionFixture);

    qq.matchPair(qq.findAnswer(5750), 6545);
    qq.matchPair(qq.findAnswer(5732), 6142);

    ASSERT_NO_THROW(document = qq.serializeAnswer(););
    ASSERT_TRUE(document["answer"].isArray());
    ASSERT_FALSE(document["answer"][0].isNull());

    ASSERT_TRUE(document["answer"][0]["answer_id"].isUInt());
    ASSERT_TRUE(document["answer"][0]["match_id"].isUInt());
    ASSERT_TRUE(document["answer"][1]["answer_id"].isUInt());
    ASSERT_TRUE(document["answer"][1]["match_id"].isUInt());

    ID firstItemId = document["answer"][0]["answer_id"].asUInt();
    int idx1 = 0, idx2 = 1;

    if (firstItemId != 5750) {
      idx1 = 1;
      idx2 = 0;
    }

    ASSERT_EQ(document["answer"][idx1]["answer_id"].asUInt(), 5750);
    ASSERT_EQ(document["answer"][idx1]["match_id"].asUInt(), 6545);
    ASSERT_EQ(document["answer"][idx2]["answer_id"].asUInt(), 5732);
    ASSERT_EQ(document["answer"][idx2]["match_id"].asUInt(), 6142);
  }

} // namespace QuizQuestions
} // namespace Canvas

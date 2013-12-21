#include <gtest/gtest.h>
#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resources/quiz_submission.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class QuizQuestionAnswerTest : public ::testing::Test {
  };

  TEST(QuizQuestionAnswerTest, deserialize) {
    QuizQuestionAnswer answer;

    ASSERT_NO_THROW(
      answer.deserialize(loadFixture("quiz_question_answer.json"));
    );

    ASSERT_EQ(answer.id(), 3023);
    ASSERT_EQ(answer.text(), "A");
    ASSERT_EQ(answer.comments(), "Adooken.");
    ASSERT_EQ(answer.weight(), 100);
  }

} // namespace cnvs

#include <gtest/gtest.h>
#include "canvas/resources/quiz_questions/multiple_choice.hpp"
#include "test_helper.hpp"

namespace Canvas {
namespace QuizQuestions {

  TEST(MultipleChoiceQuizQuestionTest, deserializesAnswers) {
    MultipleChoice qq;

    ASSERT_NO_THROW(
      qq.deserialize(loadFixture("quiz_questions/multiple_choice.json"));
    );

    ASSERT_EQ(qq.answers().size(), 4);
    ASSERT_EQ(qq.answers()[0]->text(), "A");
    ASSERT_EQ(qq.answers()[1]->text(), "B");
    ASSERT_EQ(qq.answers()[2]->text(), "C");
    ASSERT_EQ(qq.answers()[3]->text(), "D");
  }

} // namespace QuizQuestions
} // namespace Canvas

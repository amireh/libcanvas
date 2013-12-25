#include <gtest/gtest.h>
#include "canvas/resource.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_submission.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  static JSONValue jsonFixture(String json) {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    return root;
  }

  class SpecQuestion : public QuizQuestion {
  public:
    virtual JSONValue serializeAnswer() const {}
  };

  TEST(QuizQuestionTest, deserialize) {
    SpecQuestion qq;

    qq.deserialize(loadFixture("quiz_question.json"));

    ASSERT_EQ(qq.id(), 1);
    ASSERT_EQ(qq.name(), "MC Q");
    ASSERT_EQ(qq.type(), "multiple_choice_question");
    ASSERT_EQ(qq.text(), "<p>A, B, C, or D?</p>");
    ASSERT_EQ(qq.pointsPossible(), 1);
    ASSERT_EQ(qq.correctComments(), "Correct");
    ASSERT_EQ(qq.incorrectComments(), "Incorrect");
    ASSERT_EQ(qq.neutralComments(), "Donno");
    ASSERT_EQ(qq.groupId(), 0);
    ASSERT_EQ(qq.isMarked(), false);
  }

  TEST(QuizQuestionTest, buildsUrlWhenQuizIsSet) {
    SpecQuestion qq;
    Course course(1);
    Quiz quiz(1, &course);

    ASSERT_EQ(qq.url(), "");

    qq.deserialize(loadFixture("quiz_question.json"));
    ASSERT_EQ(qq.url(), "");

    qq.setQuiz(&quiz);
    ASSERT_EQ(qq.url(), "/courses/1/quizzes/1/questions/1");
  }

  TEST(QuizQuestionTest, answerUrl) {
    SpecQuestion qq;
    QuizSubmission qs(1);

    qq.deserialize(loadFixture("quiz_question.json"));
    ASSERT_EQ(qq.answerUrl(qs), "/quiz_submissions/1/questions/1");
  }

  TEST(QuizQuestionTest, mark) {
    SpecQuestion qq;

    ASSERT_EQ(qq.isMarked(), false);
    qq.mark(true);
    ASSERT_EQ(qq.isMarked(), true);
  }

  TEST(QuizQuestionTest, deserializeMarkedStatus) {
    SpecQuestion qq;
    JSONValue fixture;

    fixture = jsonFixture("{ \"marked\": \"true\" }");
    qq.deserializeAnswer(fixture);

    ASSERT_EQ(qq.isMarked(), true);

    fixture = jsonFixture("{ \"marked\": \"false\" }");
    qq.deserializeAnswer(fixture);
    ASSERT_EQ(qq.isMarked(), false);
  }

} // namespace cnvs

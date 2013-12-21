/*
 *  Copyright (C) 2013 Algol Labs <ahmad@algollabs.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_submission.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/session.hpp"
#include "canvas/utility.hpp"

namespace Canvas {
  QuizQuestion::QuizQuestion()
  : Resource(0),
    mQuiz(nullptr)
  {
    reset();
  }

  QuizQuestion::QuizQuestion(ID id)
  : Resource(id),
    mQuiz(nullptr)
  {
    reset();
  }

  QuizQuestion::QuizQuestion(ID id, Quiz const* quiz)
  : Resource(id),
    mQuiz(quiz)
  {
    reset();
    buildUrl();
  }

  QuizQuestion::~QuizQuestion() {
    mQuiz = nullptr;
  }

  void QuizQuestion::reset() {
    mPointsPossible = 0;
    mPosition = 0;
    mGroupId = 0;
  }

  Quiz const* QuizQuestion::quiz() const {
    return mQuiz;
  }

  String const& QuizQuestion::name() const {
    return mName;
  }

  String const& QuizQuestion::type() const {
    return mType;
  }

  String const& QuizQuestion::text() const {
    return mText;
  }

  String const& QuizQuestion::correctComments() const {
    return mCorrectComments;
  }

  String const& QuizQuestion::incorrectComments() const {
    return mIncorrectComments;
  }

  String const& QuizQuestion::neutralComments() const {
    return mNeutralComments;
  }

  int QuizQuestion::pointsPossible() const {
    return mPointsPossible;
  }

  ID QuizQuestion::groupId() const {
    return mGroupId;
  }

  int QuizQuestion::position() const {
    return mPosition;
  }

  void QuizQuestion::deserialize(Json::Value& root) {
    mId = root.get("id", 0).asUInt();
    mName = root.get("question_name", "Question" + utility::stringify(mId)).asString();
    mType = root.get("question_type", "unknown_question").asString();
    mText = root.get("question_text", "").asString();
    mGroupId = root.get("quiz_group_id", 0).asUInt();
    mPointsPossible = root.get("points_possible", 0).asUInt();
    mCorrectComments = root.get("correct_comments", "").asString();
    mIncorrectComments = root.get("incorrect_comments", "").asString();
    mNeutralComments = root.get("neutral_comments", "").asString();

    buildUrl();
  }

  void QuizQuestion::buildUrl() {
    if (!mQuiz) {
      return;
    }

    mUrl = mQuiz->url() + "/questions/" + utility::stringify(id());
  }

  void QuizQuestion::setQuiz(Quiz const *quiz) {
    mQuiz = quiz;
    buildUrl();
  }

  URI QuizQuestion::answerUrl(QuizSubmission const &qs) const {
    return "/quiz_submissions/" +
      utility::stringify(qs.id()) +
      "/questions/" +
      utility::stringify(id());
  }

  QuizQuestions::MultipleChoice* QuizQuestion::asMultipleChoice() {
    return this->toActualType<QuizQuestions::MultipleChoice>("multiple_choice_question");
  }
}
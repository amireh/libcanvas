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
#include "canvas/resource_parser.hpp"
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
    mMarked = false;
    mAnswered = false;
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

  void QuizQuestion::deserialize(Json::Value& document) {
    mId = ResourceParser::parseId(document, "id");

    if (document["question_name"].isString()) {
      mName = document.get("question_name", "Question" + Utility::stringify(mId)).asString();
    }

    if (document["question_type"].isString()) {
      mType = document.get("question_type", "unknown_question").asString();
    }

    if (document["question_text"].isString()) {
      mText = document.get("question_text", "").asString();
    }

    if (document["correct_comments"].isString()) {
      mCorrectComments = document.get("correct_comments", "").asString();
    }

    if (document["incorrect_comments"].isString()) {
      mIncorrectComments = document.get("incorrect_comments", "").asString();
    }

    if (document["neutral_comments"].isString()) {
      mNeutralComments = document.get("neutral_comments", "").asString();
    }

    if (document["quiz_group_id"].isInt()) {
      mGroupId = document.get("quiz_group_id", 0).asUInt();
    }

    if (document["position"].isInt()) {
      mPosition = document.get("position", 0).asInt();
    }

    if (document["points_possible"].isInt()) {
      mPointsPossible = document.get("points_possible", 0).asUInt();
    }

    buildUrl();
  }

  void QuizQuestion::deserializeAnswer(const String& json) {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    deserializeAnswer(root);
  }

  void QuizQuestion::deserializeAnswer(const JSONValue& document) {
    if (document.isMember("marked")) {
      mMarked = ResourceParser::parseBool(document["marked"]);
    }
  }

  void QuizQuestion::buildUrl() {
    if (!mQuiz) {
      return;
    }

    mUrl = mQuiz->url() + "/questions/" + Utility::stringify(id());
  }

  void QuizQuestion::setQuiz(Quiz const *quiz) {
    mQuiz = quiz;
    buildUrl();
  }

  URI QuizQuestion::answerUrl(QuizSubmission const &qs) const {
    return "/quiz_submissions/" +
      Utility::stringify(qs.id()) +
      "/questions/" +
      Utility::stringify(id());
  }

  QuizQuestions::MultipleChoice* QuizQuestion::asMultipleChoice() {
    return this->toActualType<QuizQuestions::MultipleChoice>("multiple_choice_question");
  }

  QuizQuestions::MultipleChoice const* QuizQuestion::asMultipleChoice() const {
    return this->toActualType<QuizQuestions::MultipleChoice>("multiple_choice_question");
  }

  QuizQuestions::TrueFalse* QuizQuestion::asTrueFalse() {
    return this->toActualType<QuizQuestions::TrueFalse>("true_false_question");
  }

  QuizQuestions::TrueFalse const* QuizQuestion::asTrueFalse() const {
    return this->toActualType<QuizQuestions::TrueFalse>("true_false_question");
  }

  QuizQuestions::FillInTheBlank* QuizQuestion::asFillInTheBlank() {
    return this->toActualType<QuizQuestions::FillInTheBlank>("short_answer_question");
  }

  QuizQuestions::FillInTheBlank const* QuizQuestion::asFillInTheBlank() const {
    return this->toActualType<QuizQuestions::FillInTheBlank>("short_answer_question");
  }

  QuizQuestions::FillInMultipleBlanks* QuizQuestion::asFillInMultipleBlanks() {
    return this->toActualType<QuizQuestions::FillInMultipleBlanks>("fill_in_multiple_blanks_question");
  }

  QuizQuestions::FillInMultipleBlanks const* QuizQuestion::asFillInMultipleBlanks() const {
    return this->toActualType<QuizQuestions::FillInMultipleBlanks>("fill_in_multiple_blanks_question");
  }

  QuizQuestions::Essay* QuizQuestion::asEssay() {
    return this->toActualType<QuizQuestions::Essay>("essay_question");
  }

  QuizQuestions::Essay const* QuizQuestion::asEssay() const {
    return this->toActualType<QuizQuestions::Essay>("essay_question");
  }

  QuizQuestions::Calculated* QuizQuestion::asCalculated() {
    return this->toActualType<QuizQuestions::Calculated>("calculated_question");
  }

  QuizQuestions::Calculated const* QuizQuestion::asCalculated() const {
    return this->toActualType<QuizQuestions::Calculated>("calculated_question");
  }

  QuizQuestions::Numerical* QuizQuestion::asNumerical() {
    return this->toActualType<QuizQuestions::Numerical>("numerical_question");
  }

  QuizQuestions::Numerical const* QuizQuestion::asNumerical() const {
    return this->toActualType<QuizQuestions::Numerical>("numerical_question");
  }

  QuizQuestions::Matching* QuizQuestion::asMatching() {
    return this->toActualType<QuizQuestions::Matching>("matching_question");
  }

  QuizQuestions::Matching const* QuizQuestion::asMatching() const {
    return this->toActualType<QuizQuestions::Matching>("matching_question");
  }

  QuizQuestions::MultipleDropdowns* QuizQuestion::asMultipleDropdowns() {
    return this->toActualType<QuizQuestions::MultipleDropdowns>("multiple_dropdowns_question");
  }

  QuizQuestions::MultipleDropdowns const* QuizQuestion::asMultipleDropdowns() const {
    return this->toActualType<QuizQuestions::MultipleDropdowns>("multiple_dropdowns_question");
  }

  QuizQuestions::MultipleAnswers* QuizQuestion::asMultipleAnswers() {
    return this->toActualType<QuizQuestions::MultipleAnswers>("multiple_answers_question");
  }

  QuizQuestions::MultipleAnswers const* QuizQuestion::asMultipleAnswers() const {
    return this->toActualType<QuizQuestions::MultipleAnswers>("multiple_answers_question");
  }

  bool QuizQuestion::isMarked() const {
    return mMarked;
  }

  void QuizQuestion::mark(bool marked) {
    mMarked = marked;
  }

  bool QuizQuestion::isAnswered() const {
    return mAnswered;
  }

  void QuizQuestion::flagAnswered() {
    mAnswered = true;
    // TODO: maybe we can broadcast this change to interested parties
  }

  void QuizQuestion::flagUnanswered() {
    mAnswered = false;
  }
}
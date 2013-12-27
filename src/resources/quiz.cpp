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

#include "canvas/resources/quiz.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_questions/multiple_choice.hpp"
#include "canvas/resources/quiz_questions/true_false.hpp"
#include "canvas/resources/quiz_questions/fill_in_the_blank.hpp"
#include "canvas/resources/quiz_questions/fill_in_multiple_blanks.hpp"
#include "canvas/resources/quiz_questions/essay.hpp"
#include "canvas/resources/quiz_questions/calculated.hpp"
#include "canvas/resources/quiz_questions/numerical.hpp"
#include "canvas/resources/quiz_questions/matching.hpp"
#include "canvas/resources/quiz_questions/multiple_dropdowns.hpp"
#include "canvas/resources/quiz_questions/multiple_answers.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "canvas/utility.hpp"
#include <cstdio>
#include <cstring>

namespace Canvas {
  Quiz::Quiz()
  : Resource(),
    mCourse(nullptr) {
      reset();
  }

  Quiz::Quiz(ID id, Course* course)
  : Resource(id),
    mCourse(course) {

    reset();
    buildUrl();
  }

  Quiz::~Quiz() {
    std::for_each(mQuestions.begin(), mQuestions.end(), [](QuizQuestion* qq) {
      delete qq;
    });

    mQuestions.clear();
  }

  void Quiz::setCourse(Course* course) {
    mCourse = course;
    buildUrl();
  }

  Course const* Quiz::course() const {
    return mCourse;
  }

  String const& Quiz::title() const {
    return mTitle;
  }

  const String &Quiz::description() const {
    return mDescription;
  }

  bool Quiz::isPublished() const {
    return mPublished;
  }

  bool Quiz::isOQAAT() const {
    return mOQAAT;
  }

  bool Quiz::showCorrectAnswers() const {
    return mShowCorrectAnswers;
  }

  bool Quiz::locked() const {
    return mLocked;
  }

  String const& Quiz::accessCode() const {
    return mAccessCode;
  }

  uint Quiz::pointsPossible() const {
    return mPointsPossible;
  }

  int Quiz::allowedAttempts() const {
    return mAllowedAttempts;
  }

  uint Quiz::questionCount() const {
    return mQuestionCount;
  }

  int Quiz::timeLimit() const {
    return mTimeLimit;
  }

  void Quiz::deserialize(JSONValue& document) {
    mId = ResourceParser::parseId(document, "id");

    if (document["title"].isString()) {
      mTitle = document.get("title", "Unnamed Quiz").asString();
    }

    if (document["description"].isString()) {
      mDescription = document.get("description", "").asString();
    }

    if (document["points_possible"].isNumeric()) {
      mPointsPossible = document.get("points_possible", "0").asUInt();
    }

    if (document["allowed_attempts"].isNumeric()) {
      mAllowedAttempts = document.get("allowed_attempts", "-1").asInt();
    }

    if (document["question_count"].isNumeric()) {
      mQuestionCount = document.get("question_count", "0").asUInt();
    }

    if (document["time_limit"].isNumeric()) {
      mTimeLimit = document.get("time_limit", "-1").asInt();
    }

    if (document.isMember("one_question_at_a_time")) {
      mOQAAT = ResourceParser::parseBool(document["one_question_at_a_time"]);
    }

    if (document.isMember("locked_for_user")) {
      mLocked = ResourceParser::parseBool(document["locked_for_user"]);
    }

    if (document.isMember("show_correct_answers")) {
      mShowCorrectAnswers = ResourceParser::parseBool(document["show_correct_answers"]);
    }

    if (document.isMember("published")) {
      mPublished = ResourceParser::parseBool(document["published"]);
    }

    buildUrl();
  }

  void Quiz::loadQuestions(Session &session, AsyncCallback callback) {
    session.get(url() + "/questions?per_page=50",
      [&](bool success, HTTP::Response response) -> void {
        if (success) {
          loadQuestions(response.body);
        }

        callback(success);
    });
  }

  void Quiz::loadQuestions(String const& documents) {
    Json::Value qqDocuments;
    Json::Reader reader;

    if (!reader.parse( documents, qqDocuments )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    for (Json::Value &qqDocument : qqDocuments) {
      QuizQuestion *qq = nullptr;

      String qqType = qqDocument["question_type"].asString();
      ID qqId = qqDocument["id"].asUInt();

      if (qqType == "multiple_choice_question") {
        qq = new QuizQuestions::MultipleChoice(qqId, this);
      }
      else if (qqType == "true_false_question") {
        qq = new QuizQuestions::TrueFalse(qqId, this);
      }
      else if (qqType == "short_answer_question") {
        qq = new QuizQuestions::FillInTheBlank(qqId, this);
      }
      else if (qqType == "fill_in_multiple_blanks_question") {
        qq = new QuizQuestions::FillInMultipleBlanks(qqId, this);
      }
      else if (qqType == "essay_question") {
        qq = new QuizQuestions::Essay(qqId, this);
      }
      else if (qqType == "calculated_question") {
        qq = new QuizQuestions::Calculated(qqId, this);
      }
      else if (qqType == "numerical_question") {
        qq = new QuizQuestions::Numerical(qqId, this);
      }
      else if (qqType == "matching_question") {
        qq = new QuizQuestions::Matching(qqId, this);
      }
      else if (qqType == "multiple_dropdowns_question") {
        qq = new QuizQuestions::MultipleDropdowns(qqId, this);
      }
      else if (qqType == "multiple_answers_question") {
        qq = new QuizQuestions::MultipleAnswers(qqId, this);
      }
      else {
        // TODO: throw something here?
      }

      if (qq) {
        qq->deserialize(qqDocument);
        qq->setQuiz(this);

        mQuestions.push_back(qq);
      }
    }
  }

  void Quiz::buildUrl()
  {
    if (!mCourse) {
      return;
    }

    mUrl = mCourse->url() + "/quizzes/" + Utility::stringify(mId);
  }

  void Quiz::reset() {
    mPublished = false;
    mPointsPossible = 0;
    mAllowedAttempts = 0;
    mQuestionCount = 0;
    mTimeLimit = 0;
    mOQAAT = false;
    mLocked = false;
    mShowCorrectAnswers = false;
  }

  Quiz::Questions const& Quiz::questions() const {
    return mQuestions;
  }
} // namespace cnvs

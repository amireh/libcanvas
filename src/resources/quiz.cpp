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
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "canvas/utility.hpp"
#include <cstdio>
#include <cstring>

namespace Canvas {
  Quiz::Quiz()
  : Resource(),
    mCourse(nullptr) {
  }

  Quiz::Quiz(ID id, Course* course)
  : Resource(id),
    mCourse(course) {

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

  void Quiz::deserialize(JSONValue& root) {
    mId = root.get("id", 0).asUInt();
    mTitle = root.get("title", "Unnamed Quiz").asString();
    mDescription = root.get("description", "").asString();
    mPublished = root.get("published", "true").asBool();
    mPointsPossible = root.get("points_possible", "0").asUInt();
    mAllowedAttempts = root.get("allowed_attempts", "-1").asInt();
    mQuestionCount = root.get("question_count", "0").asUInt();
    mTimeLimit = root.get("time_limit", "-1").asInt();
    mOQAAT = root.get("one_question_at_a_time", "false").asBool();
    mLocked = root.get("locked_for_user", "false").asBool();
    mShowCorrectAnswers = root.get("show_correct_answers", "true").asBool();

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
      else {
        // qq = new QuizQuestion(qqId, this);
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

    mUrl = mCourse->url() + "/quizzes/" + utility::stringify(mId);
  }

  Quiz::Questions const& Quiz::questions() const {
    return mQuestions;
  }
} // namespace cnvs

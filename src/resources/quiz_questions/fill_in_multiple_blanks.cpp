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

#include "canvas/resources/quiz_questions/fill_in_multiple_blanks.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include <sstream>

namespace Canvas {
namespace QuizQuestions {

  FillInMultipleBlanks::FillInMultipleBlanks()
  : QuizQuestion()
  {
  }

  FillInMultipleBlanks::FillInMultipleBlanks(ID id)
  : QuizQuestion(id)
  {
  }

  FillInMultipleBlanks::FillInMultipleBlanks(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz)
  {
  }

  FillInMultipleBlanks::~FillInMultipleBlanks() {
  }

  void FillInMultipleBlanks::deserialize(JSONValue &document) {
    QuizQuestion::deserialize(document);

    for (auto answerDocument : document["answers"]) {
      if (!answerDocument["blank_id"].isString()) {
        throw JSONError("Expected answer document to contain a blank_id string.",
          answerDocument);
      }

      const String blankId = answerDocument.get("blank_id", "").asString();

      if (!hasBlank(blankId)) {
        mBlanks.push_back(blankId);

        // make sure we get a default empty value
        fill(blankId, "");
      }
    }
  }

  void FillInMultipleBlanks::fill(String const& blank, String const& answer) {
    Answers::iterator locator;
    bool allAnswersEmpty;

    assertHasBlank(blank);

    locator = mAnswers.find(blank);

    if (locator != mAnswers.end()) {
      locator->second = answer;
    }
    else {
      mAnswers.insert(std::make_pair(blank, answer));
    }

    if (!answer.empty()) {
      flagAnswered();
    }
    else {
      // Check if all answers are empty, and flag accordingly
      allAnswersEmpty = true;

      for (auto pair : mAnswers) {
        if (!pair.second.empty()) {
          allAnswersEmpty = false;
          break;
        }
      }

      if (allAnswersEmpty) {
        flagUnanswered();
      }
    }
  }

  String const& FillInMultipleBlanks::filledAnswer(String const& blank) const {
    assertHasBlank(blank);

    return mAnswers.find(blank)->second;
  }

  void FillInMultipleBlanks::deserializeAnswer(JSONValue const &document) {
    QuizQuestion::deserializeAnswer(document);

    if (document["answer"].isObject()) {
      for (auto blankId : document["answer"].getMemberNames()) {
        fill(blankId, document["answer"][blankId].asString());
      }
    }
  }

  JSONValue FillInMultipleBlanks::serializeAnswer() const {
    Json::Value document;

    if (!mAnswers.empty()) {
      for (auto pair : mAnswers) {
        document["answer"][pair.first] = pair.second;
      }
    }

    return document;
  }

  bool FillInMultipleBlanks::hasBlank(String const& blankId) const {
    for (auto blank : mBlanks) {
      if (blank == blankId) {
        return true;
      }
    }

    return false;
  }

  void FillInMultipleBlanks::assertHasBlank(String const& blankId) const {
    if (!hasBlank(blankId)) {
      throw std::invalid_argument("No such blank with ID: " + blankId);
    }
  }

  FillInMultipleBlanks::Blanks const& FillInMultipleBlanks::blanks() const {
    return mBlanks;
  }

} // namespace QuizQuestions
} // namespace Canvas
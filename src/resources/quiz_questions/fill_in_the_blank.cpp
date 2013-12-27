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

#include "canvas/resources/quiz_questions/fill_in_the_blank.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include <sstream>

namespace Canvas {
namespace QuizQuestions {

  FillInTheBlank::FillInTheBlank()
  : QuizQuestion()
  {
  }

  FillInTheBlank::FillInTheBlank(ID id)
  : QuizQuestion(id)
  {
  }

  FillInTheBlank::FillInTheBlank(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz)
  {
  }

  FillInTheBlank::~FillInTheBlank() {
  }

  void FillInTheBlank::deserialize(JSONValue &root) {
    QuizQuestion::deserialize(root);
  }

  void FillInTheBlank::fill(String const& answer) {
    mAnswer = answer;

    if (!mAnswer.empty()) {
      flagAnswered();
    }
    else {
      flagUnanswered();
    }
  }

  String const& FillInTheBlank::filledAnswer() const {
    return mAnswer;
  }

  void FillInTheBlank::deserializeAnswer(JSONValue const &document) {
    QuizQuestion::deserializeAnswer(document);

    if (document["answer"].isString()) {
      fill(document["answer"].asString());
    }
  }

  JSONValue FillInTheBlank::serializeAnswer() const {
    Json::Value document;

    if (!mAnswer.empty()) {
      document["answer"] = mAnswer;
    }

    return document;
  }

} // namespace QuizQuestions
} // namespace Canvas
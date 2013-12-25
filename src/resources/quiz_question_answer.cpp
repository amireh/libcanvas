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

#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/quiz_question.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/utility.hpp"

namespace Canvas {
  QuizQuestionAnswer::QuizQuestionAnswer()
  : Resource(0),
    mQuestion(nullptr)
  {
    reset();
  }

  QuizQuestionAnswer::QuizQuestionAnswer(ID id)
  : Resource(id),
    mQuestion(nullptr)
  {
    reset();
  }

  QuizQuestionAnswer::QuizQuestionAnswer(ID id, QuizQuestion const* question)
  : Resource(id),
    mQuestion(question)
  {
    reset();
  }

  QuizQuestionAnswer::~QuizQuestionAnswer() {
    mQuestion = nullptr;
  }

  void QuizQuestionAnswer::reset() {
    mWeight = 0;
  }

  QuizQuestion const* QuizQuestionAnswer::question() const {
    return mQuestion;
  }

  String const& QuizQuestionAnswer::text() const {
    return mText;
  }

  String const& QuizQuestionAnswer::comments() const {
    return mComments;
  }

  int QuizQuestionAnswer::weight() const {
    return mWeight;
  }

  void QuizQuestionAnswer::deserialize(JSONValue& root) {
    mId = ResourceParser::parseId(root);
    mText = root.get("text", "").asString();
    mComments = root.get("comments", "").asString();
    mWeight = root.get("weight", 0).asUInt();
  }

  void QuizQuestionAnswer::setQuestion(QuizQuestion const *question) {
    mQuestion = question;
  }
}
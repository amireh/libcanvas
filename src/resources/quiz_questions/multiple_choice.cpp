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

#include "canvas/resources/quiz_questions/multiple_choice.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include <sstream>

namespace Canvas {
namespace QuizQuestions {

  MultipleChoice::MultipleChoice()
  : QuizQuestion(), mAnswer(nullptr)
  {
  }

  MultipleChoice::MultipleChoice(ID id)
  : QuizQuestion(id), mAnswer(nullptr)
  {
  }

  MultipleChoice::MultipleChoice(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz), mAnswer(nullptr)
  {
  }

  MultipleChoice::~MultipleChoice() {
    mAnswer = nullptr;
  }

  void MultipleChoice::deserialize(JSONValue &root) {
    QuizQuestion::deserialize(root);

    for (auto answerDocument : root["answers"]) {
      ID answerId = answerDocument["id"].asUInt();

      addAnswer(answerId, [&answerDocument](QuizQuestionAnswer *answer) {
        answer->deserialize(answerDocument);
      });
    }
  }

  void MultipleChoice::choose(QuizQuestionAnswer const *answer) {
    if (!answer) {
      throw std::invalid_argument("Answer must not be null!");
    }

    if (answer->question() != this) {
      std::ostringstream msg;

      msg
        << "Answer#" << answer->id() << " does not belong to Question#" << id();

      throw std::invalid_argument(msg.str());
    }

    mAnswer = answer;
  }

  void MultipleChoice::choose(ID answerId) {
    return choose( findAnswer(answerId) );
  }

  QuizQuestionAnswer const* MultipleChoice::chosenAnswer() const {
    return mAnswer;
  }

  void MultipleChoice::deserializeAnswer(JSONValue const &document) {
    QuizQuestion::deserializeAnswer(document);

    mAnswer = findAnswer(document["answer"].asUInt());
  }

  JSONValue MultipleChoice::serializeAnswer() const {
    Json::Value document;
    if (mAnswer) {
      document["answer"] = mAnswer->id();
    }
    return document;
  }

} // namespace QuizQuestions
} // namespace Canvas
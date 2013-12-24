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

#include "canvas/resources/quiz_questions/true_false.hpp"

namespace Canvas {
namespace QuizQuestions {

  TrueFalse::TrueFalse()
  : MultipleChoice()
  {
  }

  TrueFalse::TrueFalse(ID id)
  : MultipleChoice(id)
  {
  }

  TrueFalse::TrueFalse(ID id, Quiz const* quiz)
  : MultipleChoice(id, quiz)
  {
  }

  TrueFalse::~TrueFalse() {
  }

//  void TrueFalse::deserialize(JSONValue &root) {
//    QuizQuestion::deserialize(root);

//    for (auto answerDocument : root["answers"]) {
//      ID answerId = answerDocument["id"].asUInt();

//      addAnswer(answerId, [&answerDocument](QuizQuestionAnswer *answer) {
//        answer->deserialize(answerDocument);
//      });
//    }
//  }

//  // JSONValue TrueFalse::answer(ID answerId) {
//  //   // todo: validate answer
//  //   Json::Value root;
//  //   root["answer"] = answerId;
//  //   return root;
//  // }

//  void TrueFalse::choose(QuizQuestionAnswer const *answer) {
//    if (!answer) {
//      throw std::invalid_argument("Answer must not be null!");
//    }

//    if (answer->question() != this) {
//      std::ostringstream msg;

//      msg
//        << "Answer#" << answer->id() << " does not belong to Question#" << id();

//      throw std::invalid_argument(msg.str());
//    }

//    mAnswer = answer;
//  }

//  void TrueFalse::choose(ID answerId) {
//    return choose( findAnswer(answerId) );
//  }

//  QuizQuestionAnswer const* TrueFalse::chosenAnswer() const {
//    return mAnswer;
//  }

//  void TrueFalse::deserializeAnswer(JSONValue &document) {
//    mAnswer = findAnswer(document["answer"].asUInt());
//  }

//  JSONValue TrueFalse::serializeAnswer() const {
//    Json::Value document;
//    if (mAnswer) {
//      document["answer"] = mAnswer->id();
//    }
//    return document;
//  }

} // namespace QuizQuestions
} // namespace Canvas

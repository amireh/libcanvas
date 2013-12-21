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

namespace Canvas {
namespace QuizQuestions {

  MultipleChoice::MultipleChoice()
  : QuizQuestion()
  {
  }

  MultipleChoice::MultipleChoice(ID id)
  : QuizQuestion(id)
  {
  }

  MultipleChoice::MultipleChoice(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz)
  {
  }

  MultipleChoice::~MultipleChoice() {
  }

  void MultipleChoice::deserialize(JSONValue &root) {
    QuizQuestion::deserialize(root);

    for (auto answerDocument : root["answers"]) {
      // QuizQuestionAnswer* answer;
      ID answerId = answerDocument["id"].asUInt();

      addAnswer(answerId, [&answerDocument](QuizQuestionAnswer *answer) {
        answer->deserialize(answerDocument);
      });

      // answer = new QuizQuestionAnswer(answerId, this);
      // mAnswers.push_back(answer);
    }
  }

} // namespace QuizQuestions
} // namespace Canvas
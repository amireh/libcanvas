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

#include "canvas/resources/quiz_questions/multiple_answers.hpp"
#include "canvas/resource_parser.hpp"

namespace Canvas {
namespace QuizQuestions {

  MultipleAnswers::MultipleAnswers()
  : QuizQuestion()
  {
  }

  MultipleAnswers::MultipleAnswers(ID id)
  : QuizQuestion(id)
  {
  }

  MultipleAnswers::MultipleAnswers(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz)
  {
  }

  MultipleAnswers::~MultipleAnswers() {
    mSelection.clear();
  }

  void MultipleAnswers::deserialize(JSONValue &document) {
    QuizQuestion::deserialize(document);

    if (document.isMember("answers") && document["answers"].isArray()) {
      for (auto answerDocument : document["answers"]) {
        addAnswer(answerDocument);
      }
    }
  }

  void MultipleAnswers::deserializeAnswer(JSONValue const &document) {
    QuizQuestion::deserializeAnswer(document);

    if (document.isMember("answer") && document["answer"].isArray()) {
      for (auto rawAnswerId : document["answer"]) {
        ID answerId;

        try {
          answerId = ResourceParser::parseIdElement(rawAnswerId);
        } catch (JSONError &e) {
          continue;
        }

        if (answerId) {
          choose(answerId);
        }
      }
    }
  }

  JSONValue MultipleAnswers::serializeAnswer() const {
    Json::Value document;

    for (auto answer : mSelection) {
      document["answer"].append(answer->id());
    }

    return document;
  }

  void MultipleAnswers::choose(QuizQuestionAnswer const *answer) {
    if (!answer) {
      throw std::invalid_argument("Answer must not be null!");
    }

    if (answer->question() != this) {
      std::ostringstream msg;

      msg
        << "Answer#" << answer->id() << " does not belong to Question#" << id();

      throw std::invalid_argument(msg.str());
    }

    if (!isChosen(answer)) {
      mSelection.push_back(answer);

      flagAnswered();
    }
  }

  void MultipleAnswers::choose(ID answerId) {
    return choose( findAnswer(answerId) );
  }


  void MultipleAnswers::unchoose(QuizQuestionAnswer const *answer) {
    if (!answer) {
      throw std::invalid_argument("Answer must not be null!");
    }

    Selection::iterator locator =
      std::find(mSelection.begin(), mSelection.end(), answer);

    if (locator != mSelection.end()) {
      mSelection.erase(locator);
    }

    if (mSelection.empty()) {
      flagUnanswered();
    }
  }

  void MultipleAnswers::unchoose(ID answerId) {
    return unchoose( findAnswer(answerId) );
  }

  MultipleAnswers::Selection const& MultipleAnswers::chosenAnswers() const {
    return mSelection;
  }

  bool MultipleAnswers::isChosen(QuizQuestionAnswer const* inAnswer) const {
    for (auto answer : mSelection) {
      if (answer == inAnswer) {
        return true;
      }
    }

    return false;
  }

  bool MultipleAnswers::isChosen(ID answerId) const {
    return isChosen(findAnswer(answerId));
  }

} // namespace QuizQuestions
} // namespace Canvas
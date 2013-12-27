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

#include "canvas/resources/quiz_questions/multiple_dropdowns.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/utility.hpp"

namespace Canvas {
namespace QuizQuestions {
  typedef MultipleDropdowns::Answer Answer;

  MultipleDropdowns::MultipleDropdowns()
  : QuizQuestion()
  {
  }

  MultipleDropdowns::MultipleDropdowns(ID id)
  : QuizQuestion(id)
  {
  }

  MultipleDropdowns::MultipleDropdowns(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz)
  {
  }

  MultipleDropdowns::~MultipleDropdowns() {
  }

  void MultipleDropdowns::deserialize(JSONValue &document) {
    QuizQuestion::deserialize(document);

    if (document["answers"].isArray()) {
      for (auto answerDocument : document["answers"]) {
        const String blankId = answerDocument.get("blank_id", "").asString();

        Answer *answer = addAnswer(answerDocument);

        mAnswerBlanks.insert(std::make_pair(answer, blankId));

        if (!hasBlank(blankId) && blankId.size()) {
          mBlanks.push_back(blankId);
        }
      }
    }
  }

  void MultipleDropdowns::choose(String const& blank, ID answerId) {
    assertHasBlank(blank);

    Answer const* answer = findAnswer(answerId);

    if (!answer) {
      throw std::invalid_argument("Unknown answer: " + Utility::stringify(answerId));
    }

    ChosenAnswers::iterator locator = mChosenAnswers.find(blank);

    if (mChosenAnswers.find(blank) != mChosenAnswers.end()) {
      mChosenAnswers.erase(locator);
    }

    mChosenAnswers.insert(std::make_pair(blank, answer));
    flagAnswered();
  }

  Answer const* MultipleDropdowns::chosenAnswer(String const& blank) const {
    assertHasBlank(blank);

    ChosenAnswers::const_iterator locator = mChosenAnswers.find(blank);

    if (locator == mChosenAnswers.end()) {
      return nullptr;
    }

    return locator->second;
  }

  void MultipleDropdowns::deserializeAnswer(JSONValue const &document) {
    QuizQuestion::deserializeAnswer(document);

    if (document["answer"].isObject()) {
      for (auto blankId : document["answer"].getMemberNames()) {
        const ID answerId = ResourceParser::parseId(document["answer"], blankId);

        if (answerId) {
          choose(blankId, answerId);
        }
      }
    }
  }

  JSONValue MultipleDropdowns::serializeAnswer() const {
    Json::Value document;

    if (mAnswers.size()) {
      for (auto pair : mChosenAnswers) {
        if (pair.second) {
          document["answer"][pair.first] = pair.second->id();
        }
      }
    }

    return document;
  }

  bool MultipleDropdowns::hasBlank(String const& blankId) const {
    for (auto blank : mBlanks) {
      if (blank == blankId) {
        return true;
      }
    }

    return false;
  }

  void MultipleDropdowns::assertHasBlank(String const& blank) const {
    if (!hasBlank(blank)) {
      throw std::invalid_argument("No such blank with ID: " + blank);
    }
  }

  MultipleDropdowns::Blanks const& MultipleDropdowns::blanks() const {
    return mBlanks;
  }

  MultipleDropdowns::Answers MultipleDropdowns::answers(String const& blank) const {
    MultipleDropdowns::Answers answers;

    for (auto pair : mAnswerBlanks) {
      if (pair.second == blank) {
        answers.push_back(pair.first);
      }
    }

    return answers;
  }

} // namespace QuizQuestions
} // namespace Canvas
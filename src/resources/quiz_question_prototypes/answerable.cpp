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

#include "canvas/resources/quiz_question_prototypes/answerable.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/calculated_answer.hpp"
#include "canvas/resources/matching_answer.hpp"
#include "canvas/resources/quiz_question.hpp"
#include "canvas/resource_parser.hpp"

namespace Canvas {
namespace QuizQuestionPrototypes {

  template<typename T>
  Answerable<T>::Answerable() {
  }

  template<typename T>
  Answerable<T>::~Answerable() {
    std::for_each(mAnswers.begin(), mAnswers.end(), [](T* qqa) {
      delete qqa;
    });

    mAnswers.clear();
  }

  template<typename T> typename
  Answerable<T>::Answers const& Answerable<T>::answers() const {
    return mAnswers;
  }

  template<typename T>
  T const* Answerable<T>::findAnswer(ID answerId) const {
    for (auto answer : answers()) {
      if (answer->id() == answerId) {
        return answer;
      }
    }

    return nullptr;
  }

  template<typename T>
  T* Answerable<T>::addAnswer(ID answerId, std::function<void(T*)> callback) {
    if (answerId > 0) {
      T* answer = new T();
      answer->setQuestion(dynamic_cast<QuizQuestion const*>(this));
      mAnswers.push_back(answer);

      if (callback) {
        callback(answer);
      }

      return answer;
    }

    return nullptr;
  }

  template<typename T>
  T* Answerable<T>::addAnswer(JSONValue const& document) {
    const ID answerId = ResourceParser::parseId(document);

    if (answerId > 0) {
      T* answer = new T();

      answer->setQuestion(dynamic_cast<QuizQuestion const*>(this));
      answer->deserialize((JSONValue&)document);

      mAnswers.push_back(answer);

      return answer;
    }

    return nullptr;
  }

  template class Answerable<QuizQuestionAnswer>;
  template class Answerable<CalculatedAnswer>;
  template class Answerable<MatchingAnswer>;

} // namespace QuizQuestions
} // namespace Canvas
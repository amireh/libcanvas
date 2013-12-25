/*
 *  Copyright (c) 2013 Algol Labs <ahmad@algollabs.com>
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

#ifndef H_CANVAS_ANSWERABLE_QUIZ_QUESTION_PROTOTYPE_H
#define H_CANVAS_ANSWERABLE_QUIZ_QUESTION_PROTOTYPE_H

#include "canvas/canvas.hpp"
#include <vector>

namespace Json {
  class Value;
}

namespace Canvas {
  typedef Json::Value JSONValue;
}

namespace Canvas {
namespace QuizQuestionPrototypes {

  /**
   * @class Answerable
   * A prototype for quiz questions that provide pre-defined answers.
   */
  template<typename T>
  class Answerable {
  public:
    typedef std::vector<T*> Answers;

    Answerable();
    virtual ~Answerable();

    /**
     * Answers provided by this quiz question.
     */
    Answers const& answers() const;

    T const* findAnswer(ID) const;
  protected:
    Answers mAnswers;

    /**
     * Add a new answer to the list of possible answers this question provides.
     *
     * @param[in] answerId
     *   This must be the unique answer ID, if it is 0, this method will be a
     *   no-op.
     *
     * @param callback
     *   Post-processor for the newly-added answer. You can use this to customize
     *   the answer object, or deserialize it from a JSON document, etc.
     */
    T* addAnswer(ID answerId, std::function<void(T*)> callback = nullptr);

    /**
     * Add an answer to the list of possible answers from the given JSON document.
     * The answer ID is expected to reside in an "id" field.
     *
     * See QuizQuestionAnswer::deserialize()
     */
    T* addAnswer(JSONValue const&);
  };
}
}

#endif
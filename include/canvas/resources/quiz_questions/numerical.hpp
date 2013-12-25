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

#ifndef H_CANVAS_NUMERICAL_QUIZ_QUESTION_H
#define H_CANVAS_NUMERICAL_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"

namespace Canvas {
namespace QuizQuestions {

  /**
   * \addtogroup Resources
   * @{
   * @class Numerical
   * @brief
   * A question with a simple numerical answer.
   */
  class Numerical : public QuizQuestion {
  public:
    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;

    Numerical();
    Numerical(ID);
    Numerical(ID, Quiz const*);
    Numerical(const Numerical&) = delete;
    Numerical& operator=(const Numerical&) = delete;
    virtual ~Numerical();

    virtual void deserialize(JSONValue&);
    virtual void deserializeAnswer(JSONValue const&);

    /**
     * Save the selection of a single multiple-choice answer.
     *
     * @param[in] answer
     *   The multiple-choice answer to choose.
     *
     * @throw runtime_error if the answer does not belong to the question this
     * submission entry answer represents
     */
    virtual void setAnswer(double);

    /**
     * The chosen answer. May be nullptr.
     */
    virtual double answer() const;

    /**
     * Output looks like this:
     *
     *   { "answer": 42.0 }
     */
    virtual JSONValue serializeAnswer() const;

  protected:
    double mAnswer;
  };
  /** @} */
}
}

#endif

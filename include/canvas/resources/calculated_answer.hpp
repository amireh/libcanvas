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

#ifndef H_CANVAS_CALCULATED_ANSWER_H
#define H_CANVAS_CALCULATED_ANSWER_H

#include "canvas/canvas.hpp"
#include "canvas/resources/quiz_question_answer.hpp"

#include <vector>

namespace Canvas {
  class Quiz;
  class QuizSubmission;
}

namespace Canvas {

  /**
   * \addtogroup Resources
   * @{
   * @class Calculated
   * @brief
   * A single possible answer for a Calculated quiz question. The answer maps
   * a single value to each variable defined in the question.
   *
   */
  class CalculatedAnswer : public QuizQuestionAnswer {
  public:
    using QuizQuestionAnswer::deserialize;

    CalculatedAnswer();
    CalculatedAnswer(ID);
    CalculatedAnswer(ID, QuizQuestion const*);
    CalculatedAnswer(const CalculatedAnswer&) = delete;
    CalculatedAnswer& operator=(CalculatedAnswer const&) = delete;
    virtual ~CalculatedAnswer();

    /**
     * Convenience for accessing the value of the given variable in this answer.
     */
    virtual double variableValue(String const&) const;

    /**
     * The value that the student has to supply to get a correct-answer score
     * for this answer is CalculatedAnswer::answer().
     */
    virtual double correctValue() const;

    virtual void deserialize(JSONValue&);

  protected:
    typedef struct {
      String name;
      double value;
    } Variable;

    typedef std::vector<Variable> Variables;

    Variables mVariables;
    double mValue;

    virtual Variables const& variables() const;
    virtual Variable const& variable(String const&) const;
  };
  /** @} */
}

#endif
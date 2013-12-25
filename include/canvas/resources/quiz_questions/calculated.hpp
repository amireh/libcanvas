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

#ifndef H_CANVAS_CALCULATED_QUIZ_QUESTION_H
#define H_CANVAS_CALCULATED_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/calculated_answer.hpp"
#include "canvas/resources/quiz_question_prototypes/answerable.hpp"

namespace Canvas {
  class QuizSubmission;
}

namespace Canvas {
namespace QuizQuestions {
  using QuizQuestionPrototypes::Answerable;

  /**
   * \addtogroup Resources
   * @{
   * @class Calculated
   * @brief
   * A calculated, or Formula, type of question.
   */
  class Calculated : public QuizQuestion, public Answerable<CalculatedAnswer> {
  public:
    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;

    struct Variable {
      Variable();

      String name;
      double min;
      double max;
      int precision;
    };

    typedef std::vector<Variable> Variables;

    Calculated();
    Calculated(ID);
    Calculated(ID, Quiz const*);
    Calculated(const Calculated&) = delete;
    Calculated& operator=(const Calculated&) = delete;
    virtual ~Calculated();

    virtual void deserialize(JSONValue&);
    virtual void deserializeAnswer(JSONValue const&);

    /**
     * Supply a number as the answer.
     */
    virtual void setAnswer(double);

    /**
     * The supplied answer.
     */
    virtual double answer() const;

    /**
     * Output looks like this:
     *
     *   { "answer": 10.5 }
     */
    virtual JSONValue serializeAnswer() const;

    /**
     * The value to display for a given variable that is unique for the student's
     * quiz attempt (as in, it will be consistent with further calls until the
     * quiz is turned in.).
     */
    virtual double variableValue(QuizSubmission const&, Variable const&) const;

    /**
     * All possible correct value for the given variable.
     */
    virtual std::vector<double> variableValues(Variable const&) const;

    Variables const& variables() const;
    Variable const& variable(String const&) const;
  protected:
    Variables mVariables;
    double mAnswer;
  };
  /** @} */
}
}

#endif

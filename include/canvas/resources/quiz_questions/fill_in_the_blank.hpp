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

#ifndef H_CANVAS_FILL_IN_THE_BLANK_QUIZ_QUESTION_H
#define H_CANVAS_FILL_IN_THE_BLANK_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/quiz_question_prototypes/answerable.hpp"

namespace Canvas {
namespace QuizQuestions {
  using QuizQuestionPrototypes::Answerable;

  /**
   * \addtogroup Resources
   * @{
   * @class FillInTheBlank
   * @brief
   * A fill in the blank type of question.
   */
  class FillInTheBlank : public QuizQuestion {
  public:
    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;

    FillInTheBlank();
    FillInTheBlank(ID);
    FillInTheBlank(ID, Quiz const*);
    FillInTheBlank(const FillInTheBlank&) = delete;
    FillInTheBlank& operator=(const FillInTheBlank&) = delete;
    virtual ~FillInTheBlank();

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
    virtual void fill(String const&);

    /**
     * The chosen answer. May be nullptr.
     */
    virtual String const& filledAnswer() const;

    /**
     * Output looks like this:
     *
     *   { "answer": "your answer" }
     */
    virtual JSONValue serializeAnswer() const;

  protected:
    String mAnswer;
  };
  /** @} */
}
}

#endif

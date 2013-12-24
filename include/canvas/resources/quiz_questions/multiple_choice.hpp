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

#ifndef H_CANVAS_MULTIPLE_CHOICE_QUIZ_QUESTION_H
#define H_CANVAS_MULTIPLE_CHOICE_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/quiz_question_prototypes/answerable.hpp"

namespace Canvas {
namespace QuizQuestions {
  using QuizQuestionPrototypes::Answerable;

  /**
   * \addtogroup Resources
   * @{
   * @class MultipleChoice
   * @brief
   * A multiple-choice type of question.
   */
  class MultipleChoice : public QuizQuestion, public Answerable<QuizQuestionAnswer> {
  public:
    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;

    MultipleChoice();
    MultipleChoice(ID);
    MultipleChoice(ID, Quiz const*);
    MultipleChoice(const MultipleChoice&) = delete;
    MultipleChoice& operator=(const MultipleChoice&) = delete;
    virtual ~MultipleChoice();

    virtual void deserialize(JSONValue&);
    virtual void deserializeAnswer(JSONValue&);

    /**
     * Save the selection of a single multiple-choice answer.
     *
     * @param[in] answer
     *   The multiple-choice answer to choose.
     *
     * @throw runtime_error if the answer does not belong to the question this
     * submission entry answer represents
     */
    virtual void choose(QuizQuestionAnswer const*);
    virtual void choose(ID);

    /**
     * The chosen answer. May be nullptr.
     */
    virtual QuizQuestionAnswer const* chosenAnswer() const;

    /**
     * Output looks like this:
     *
     *   { "answer": answer_id }
     */
    virtual JSONValue serializeAnswer() const;

  protected:
    QuizQuestionAnswer const *mAnswer;
  };
  /** @} */
}
}

#endif

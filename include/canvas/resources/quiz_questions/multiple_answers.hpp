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

#ifndef H_CANVAS_MULTIPLE_ANSWERS_QUIZ_QUESTION_H
#define H_CANVAS_MULTIPLE_ANSWERS_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/quiz_question_prototypes/answerable.hpp"

namespace Canvas {
namespace QuizQuestions {
  using QuizQuestionPrototypes::Answerable;

  /**
   * \addtogroup Resources
   * @{
   * @class MultipleAnswers
   * @brief
   * A question that provides several answers, of which the student has to select
   * one or more.
   */
  class MultipleAnswers : public QuizQuestion, public Answerable<QuizQuestionAnswer> {
  public:
    typedef std::vector<QuizQuestionAnswer const*> Selection;

    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;

    MultipleAnswers();
    MultipleAnswers(ID);
    MultipleAnswers(ID, Quiz const*);
    MultipleAnswers(const MultipleAnswers&) = delete;
    MultipleAnswers& operator=(const MultipleAnswers&) = delete;
    virtual ~MultipleAnswers();

    virtual void deserialize(JSONValue&);
    virtual void deserializeAnswer(JSONValue const&);

    /**
     * Choose an answer to add to the selection of answers.
     *
     * @param[in] answer
     *   The answer to add to the selection.
     *
     * @throw std::invalid_argument if the answer is null
     * @throw std::invalid_argument if the answer does not belong to the question
     */
    void choose(QuizQuestionAnswer const*);
    void choose(ID);

    /**
     * Choose an answer to remove from the selection of answers.
     *
     * @param[in] answer
     *   The answer to remove from the selection.
     *
     * @note
     *   This is a no-op if the answer had not been selected.
     */
    void unchoose(QuizQuestionAnswer const*);
    void unchoose(ID);

    /**
     * The selection of chosen answers.
     */
    Selection const& chosenAnswers() const;

    bool isChosen(QuizQuestionAnswer const*) const;
    bool isChosen(ID) const;

    /**
     * Output looks like this:
     *
     *   { "answer": [ answer_id, answer_id ] }
     */
    virtual JSONValue serializeAnswer() const;

  protected:
    Selection mSelection;
  };
  /** @} */
}
}

#endif

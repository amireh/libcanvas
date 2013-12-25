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

#ifndef H_CANVAS_MULTIPLE_DROPDOWNS_QUIZ_QUESTION_H
#define H_CANVAS_MULTIPLE_DROPDOWNS_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/quiz_question_prototypes/answerable.hpp"

namespace Canvas {
namespace QuizQuestions {
  using QuizQuestionPrototypes::Answerable;

  /**
   * \addtogroup Resources
   * @{
   * @class MultipleDropdowns
   * @brief
   * A question with multiple pre-defined sets of blank answers, similar to
   * fill in multiple blanks questions, but the student doesn't get to enter
   * the answers directly, only choose them.
   */
  class MultipleDropdowns : public QuizQuestion, public Answerable<QuizQuestionAnswer> {
  public:
    typedef std::vector<String> Blanks;
    typedef QuizQuestionAnswer  Answer;

    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;
    using Answerable::answers;

    MultipleDropdowns();
    MultipleDropdowns(ID);
    MultipleDropdowns(ID, Quiz const*);
    MultipleDropdowns(const MultipleDropdowns&) = delete;
    MultipleDropdowns& operator=(const MultipleDropdowns&) = delete;
    virtual ~MultipleDropdowns();

    virtual void deserialize(JSONValue&);
    virtual void deserializeAnswer(JSONValue const&);

    /**
     * Choose an answer for a single blank.
     *
     * @param[in] blank
     *   Name of the "blank", or the variable, the answer is for.
     *
     * @param[in] answerId
     *   ID of the answer for the specified blank.
     */
    virtual void choose(String const& blank, ID);

    /**
     * The text filled in for the given blank.
     *
     * @param[in] blank
     *   Name of the blank the answer is expected for.
     */
    Answer const* chosenAnswer(String const&) const;

    /**
     * Output looks like this:
     *
     *   {
     *     "answer": {
     *       "blank_1": 123,
     *       "blank_x": 000
     *     }
     *   }
     */
    virtual JSONValue serializeAnswer() const;

    /**
     * All defined blanks.
     */
    Blanks const& blanks() const;

    /**
     * Available answers for a given blank.
     */
    Answers answers(String const&) const;

  protected:
    typedef std::map<String, Answer const*> ChosenAnswers;
    typedef std::map<Answer*, String> AnswerBlanks;

    ChosenAnswers mChosenAnswers;
    AnswerBlanks mAnswerBlanks;
    Blanks mBlanks;

    bool hasBlank(String const&) const;
    void assertHasBlank(String const&) const;
  };
  /** @} */
}
}

#endif

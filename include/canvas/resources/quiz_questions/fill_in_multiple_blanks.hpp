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

#ifndef H_CANVAS_FILL_IN_MULTIPLE_BLANKS_QUIZ_QUESTION_H
#define H_CANVAS_FILL_IN_MULTIPLE_BLANKS_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_question_answer.hpp"
#include "canvas/resources/quiz_question_prototypes/answerable.hpp"

namespace Canvas {
namespace QuizQuestions {
  using QuizQuestionPrototypes::Answerable;

  /**
   * \addtogroup Resources
   * @{
   * @class FillInMultipleBlanks
   * @brief
   * A fill in the blank type of question.
   */
  class FillInMultipleBlanks : public QuizQuestion {
  public:
    typedef std::vector<String> Blanks;

    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;

    FillInMultipleBlanks();
    FillInMultipleBlanks(ID);
    FillInMultipleBlanks(ID, Quiz const*);
    FillInMultipleBlanks(const FillInMultipleBlanks&) = delete;
    FillInMultipleBlanks& operator=(const FillInMultipleBlanks&) = delete;
    virtual ~FillInMultipleBlanks();

    /**
     *
     * @throw JSONError if blank_id is missing, or isn't a string in one of the
     * answer documents
     */
    virtual void deserialize(JSONValue&);
    virtual void deserializeAnswer(JSONValue const&);

    /**
     * Save the selection of a single multiple-choice answer.
     *
     * @param[in] answer
     *   The multiple-choice answer to choose.
     *
     * @throw std::invalid_argument if the given blank is invalid
     */
    virtual void fill(String const& blank, String const&);

    /**
     * The text filled in for the given blank.
     */
    virtual String const& filledAnswer(String const&) const;

    /**
     * Output looks like this:
     *
     *   { "answer": "your answer" }
     */
    virtual JSONValue serializeAnswer() const;

    Blanks const& blanks() const;

  protected:
    typedef std::map<String, String> Answers;

    Answers mAnswers;
    Blanks mBlanks;

    bool hasBlank(String const&) const;
    void assertHasBlank(String const&) const;
  };
  /** @} */
}
}

#endif

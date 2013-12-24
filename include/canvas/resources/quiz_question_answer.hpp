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

#ifndef H_CANVAS_QUIZ_QUESTION_ANSWER_H
#define H_CANVAS_QUIZ_QUESTION_ANSWER_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"

namespace Canvas {

  class QuizQuestion;

  /**
   * \addtogroup Resources
   * @{
   * @class QuizQuestionAnswer
   * @brief
   * A base answer type for quiz questions.
   *
   * Most quiz questions will provide a set of possible answers a student might
   * choose, except in the case of textual questions where the answer is left
   * completely for the student to supply - and automatic grading is not
   * applicable.
   *
   * The QuizQuestionAnswer is a prototype of those answer constructs, which
   * may contain a mix of the following data items:
   *
   *   - a unique answer id (see #id())
   *   - a piece of text that describes the answer to the student (see #text())
   *   - a scoring weight that is invisible to the student (see #weight())
   *
   * Further data items may be exposed by concrete answer subjects.
   */
  class QuizQuestionAnswer : public Resource {
  public:
    using Resource::deserialize;

    QuizQuestionAnswer();
    QuizQuestionAnswer(ID);
    QuizQuestionAnswer(ID, QuizQuestion const*);
    QuizQuestionAnswer(const QuizQuestionAnswer&) = delete;
    QuizQuestionAnswer& operator=(QuizQuestionAnswer const&) = delete;
    virtual ~QuizQuestionAnswer();

    /**
     * The question this answer is for.
     */
    virtual QuizQuestion const* question() const;

    /**
     * A piece of text to display as the primary indicator for this answer.
     */
    virtual String const& text() const;

    /**
     * Any comments specified by the teacher to guide students with this answer.
     */
    virtual String const& comments() const;

    /**
     * Scoring weight, the heavier an answer's weight, the more points it scores.
     */
    virtual int weight() const;

    virtual void setQuestion(QuizQuestion const*);

    virtual void deserialize(JSONValue&);

  protected:
    void reset();

    QuizQuestion const* mQuestion;
    int mWeight;
    String mText;
    String mComments;
  };
  /** @} */
}

#endif
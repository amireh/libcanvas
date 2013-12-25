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

#ifndef H_CANVAS_MATCHING_ANSWER_H
#define H_CANVAS_MATCHING_ANSWER_H

#include "canvas/canvas.hpp"
#include "canvas/resources/quiz_question_answer.hpp"

namespace Canvas {

  /**
   * \addtogroup Resources
   * @{
   * @class Matching
   * @brief
   * A single answer for a Matching quiz question. Matching answers contain
   * a pair of text, to the "left" and "right", which should be matched by the
   * student.
   */
  class MatchingAnswer : public QuizQuestionAnswer {
  public:
    using QuizQuestionAnswer::deserialize;

    MatchingAnswer();
    MatchingAnswer(ID);
    MatchingAnswer(ID, QuizQuestion const*);
    MatchingAnswer(const MatchingAnswer&) = delete;
    MatchingAnswer& operator=(MatchingAnswer const&) = delete;
    virtual ~MatchingAnswer();

    String const& left() const;
    String const& right() const;
    ID matchId() const;

    virtual void deserialize(JSONValue&);

  protected:
    String mLeft;
    String mRight;
    ID mMatchId;
  };
  /** @} */
}

#endif
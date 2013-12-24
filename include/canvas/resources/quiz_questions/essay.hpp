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

#ifndef H_CANVAS_ESSAY_QUIZ_QUESTION_H
#define H_CANVAS_ESSAY_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/quiz_questions/fill_in_the_blank.hpp"

namespace Canvas {
namespace QuizQuestions {

  /**
   * \addtogroup Resources
   * @{
   * @class Essay
   * @brief
   * An essay question where the student gets to write out their hearts contents.
   */
  class Essay : public FillInTheBlank {
  public:
    Essay();
    Essay(ID);
    Essay(ID, Quiz const*);
    Essay(const Essay&) = delete;
    Essay& operator=(const Essay&) = delete;
    virtual ~Essay();
  };
  /** @} */
}
}

#endif
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

#ifndef H_CANVAS_QUIZ_SUBMISSION_H
#define H_CANVAS_QUIZ_SUBMISSION_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"

namespace cnvs {

  class quiz;
  /**
   * @class quiz_submission
   * @brief
   * A course quiz_submission.
   */
  class quiz_submission : public resource {
  public:
    quiz_submission(id_t, quiz*);
    virtual ~quiz_submission();

    /**
     * The Quiz this QS acts on.
     */
    virtual quiz const* get_quiz() const;

    /**
     * Timestamp denoting when the latest quiz attempt has been started.
     */
    virtual string_t const& started_at() const;

    /**
     * Timestamp denoting when the latest quiz attempt was submitted.
     */
    virtual string_t const& finished_at() const;

    /**
     * Timestamp denoting when the QS will become overdue.
     */
    virtual string_t const& end_at() const;

    /**
     * Access token required for manipulating the QS.
     *
     * This token is generated when the QS is created and does not change.
     *
     * @note
     * Keep it secret!
     */
    virtual string_t const& validation_token() const;

    /**
     * The score of the latest QS attempt.
     */
    virtual double score() const;

    /**
     * The latest, or highest, or original score - depending on the Quiz
     * settings.
     */
    virtual double kept_score() const;

    /**
     * ID of the generic submission this QS represents.
     */
    virtual id_t submission_id() const;

    /**
     * ID of the quiz participant.
     */
    virtual id_t user_id() const;

    /**
     * The current attempt index the quiz participant is at for this Quiz.
     */
    virtual int attempt() const;

    /**
     * Was this QS turned in?
     */
    virtual bool is_complete() const;

    /**
     * Can the quiz be taken?
     */
    virtual bool is_takeable() const;

    /**
     * Is the QS complete and pending review by a teacher or grader?
     */
    virtual bool is_pending_review() const;

    /**
     * Populate QuizSubmission from a JSON document.
     */
    virtual void deserialize(string_t const& json);

  protected:
    quiz* quiz_;
    id_t submission_id_;
    id_t user_id_;
    string_t started_at_;
    string_t end_at_;
    string_t finished_at_;
    string_t validation_token_;
    string_t workflow_state_;
    uint8_t attempt_;
    double score_;
    double kept_score_;
  };
}

#endif
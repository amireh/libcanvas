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

namespace Canvas {

  class Session;
  class Quiz;
  class QuizQuestion;
  /**
   * @class quiz_submission
   * @brief
   * A course quiz_submission.
   */
  class QuizSubmission : public Resource {
  public:
    using Resource::deserialize;

    QuizSubmission();
    QuizSubmission(ID);
    QuizSubmission(ID, Quiz const*);
    QuizSubmission(const QuizSubmission&) = delete;
    QuizSubmission& operator=(QuizSubmission const&) = delete;
    virtual ~QuizSubmission();

    /**
     * The Quiz this QS acts on.
     */
    virtual Quiz const* quiz() const;

    /**
     * Timestamp denoting when the latest quiz attempt has been started.
     */
    virtual String const& startedAt() const;

    /**
     * Timestamp denoting when the latest quiz attempt was submitted.
     */
    virtual String const& finishedAt() const;

    /**
     * Timestamp denoting when the QS will become overdue.
     */
    virtual String const& endAt() const;

    /**
     * Access token required for manipulating the QS.
     *
     * This token is generated when the QS is created and does not change.
     *
     * @note
     * Keep it secret!
     */
    virtual String const& validationToken() const;

    /**
     * The score of the latest QS attempt.
     */
    virtual double score() const;

    /**
     * The latest, or highest, or original score - depending on the Quiz
     * settings.
     */
    virtual double keptScore() const;

    /**
     * ID of the generic submission this QS represents.
     */
    virtual ID submissionId() const;

    /**
     * ID of the quiz participant.
     */
    virtual ID userId() const;

    /**
     * The current attempt index the quiz participant is at for this Quiz.
     */
    virtual int attempt() const;

    /**
     * Was this QS turned in?
     */
    virtual bool isComplete() const;

    /**
     * Can the quiz be taken?
     */
    virtual bool isTakeable() const;

    /**
     * Is the QS complete and pending review by a teacher or grader?
     */
    virtual bool isPendingReview() const;

    /**
     * Populate QuizSubmission from a JSON document.
     */
    virtual void deserialize(JSONValue&);

    virtual void setQuiz(Quiz const*);

    virtual void saveAnswer(QuizQuestion const*, JSONValue&, Session&, AsyncCallback = nullptr) const;
    virtual void complete(Session&, AsyncCallback = nullptr);
  protected:
    void reset();
    void buildUrl();

    Quiz const* mQuiz;
    ID mSubmissionId;
    ID mUserId;
    String mStartedAt;
    String mEndAt;
    String mFinishedAt;
    String mValidationToken;
    String mWorkflowState;
    uint8_t mAttempt;
    double mScore;
    double mKeptScore;
  };
}

#endif

/*
 *  Copyright (C) 2013 Algol Labs <ahmad@algollabs.com>
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

#include "canvas/resources/quiz_submission.hpp"
#include "canvas/session.hpp"
#include "canvas/utility.hpp"
#include <cstdio>
#include <cstring>

namespace Canvas {
  QuizSubmission::QuizSubmission(ID id, Quiz* quiz)
  : Resource(id),
    mQuiz(quiz),
    mSubmissionId(0),
    mUserId(0),
    mAttempt(0),
    mScore(0),
    mKeptScore(0) {
  }

  QuizSubmission::~QuizSubmission() {
  }

  void QuizSubmission::deserialize(String const& json) {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    mId = root.get("id", 0).asUInt();
    mSubmissionId = root.get("submission_id", 0).asUInt();
    mUserId = root.get("user_id", 0).asUInt();
    mAttempt = root.get("attempt", 0).asUInt();
    mStartedAt = root.get("started_at", "").asString();
    mFinishedAt = root.get("finished_at", "").asString();
    mEndAt = root.get("end_at", "").asString();
    mValidationToken = root.get("validation_token", "").asString();
    mWorkflowState = root.get("workflow_state", "").asString();
    mScore = root.get("score", "").asDouble();
    mKeptScore = root.get("kept_score", "").asDouble();
  }

  Quiz const* QuizSubmission::quiz() const {
    return mQuiz;
  }
  String const& QuizSubmission::startedAt() const {
    return mStartedAt;
  }
  String const& QuizSubmission::finishedAt() const {
    return mFinishedAt;
  }
  String const& QuizSubmission::endAt() const {
    return mEndAt;
  }
  String const& QuizSubmission::validationToken() const {
    return mValidationToken;
  }
  double QuizSubmission::score() const {
    return mScore;
  }
  double QuizSubmission::keptScore() const {
    return mKeptScore;
  }
  ID QuizSubmission::submissionId() const {
    return mSubmissionId;
  }
  ID QuizSubmission::userId() const {
    return mUserId;
  }
  int QuizSubmission::attempt() const {
    return mAttempt;
  }
  bool QuizSubmission::isComplete() const {
    return mWorkflowState == "complete";
  }
  bool QuizSubmission::isTakeable() const {
    return mWorkflowState == "untaken";
  }
  bool QuizSubmission::isPendingReview() const {
    return mWorkflowState == "pending_review";
  }

} // namespace cnvs

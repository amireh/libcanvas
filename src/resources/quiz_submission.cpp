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

namespace cnvs {
  quiz_submission::quiz_submission(id_t id, quiz* quiz)
  : resource(id),
    quiz_(quiz),
    submission_id_(0),
    user_id_(0),
    attempt_(0),
    score_(0),
    kept_score_(0) {
  }

  quiz_submission::~quiz_submission() {
  }

  void quiz_submission::deserialize(string_t const& json) {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    if (!reader.parse( json, root )) {
      throw json_parser_error(reader.getFormattedErrorMessages());
    }

    id_ = root.get("id", 0).asUInt();
    submission_id_ = root.get("submission_id", 0).asUInt();
    user_id_ = root.get("user_id", 0).asUInt();
    attempt_ = root.get("attempt", 0).asUInt();
    started_at_ = root.get("started_at", "").asString();
    finished_at_ = root.get("finished_at", "").asString();
    end_at_ = root.get("end_at", "").asString();
    validation_token_ = root.get("validation_token", "").asString();
    workflow_state_ = root.get("workflow_state", "").asString();
    score_ = root.get("score", "").asDouble();
    kept_score_ = root.get("kept_score", "").asDouble();
  }

  quiz const* quiz_submission::get_quiz() const {
    return quiz_;
  }
  string_t const& quiz_submission::started_at() const {
    return started_at_;
  }
  string_t const& quiz_submission::finished_at() const {
    return finished_at_;
  }
  string_t const& quiz_submission::end_at() const {
    return end_at_;
  }
  string_t const& quiz_submission::validation_token() const {
    return validation_token_;
  }
  double quiz_submission::score() const {
    return score_;
  }
  double quiz_submission::kept_score() const {
    return kept_score_;
  }
  id_t quiz_submission::submission_id() const {
    return submission_id_;
  }
  id_t quiz_submission::user_id() const {
    return user_id_;
  }
  int quiz_submission::attempt() const {
    return attempt_;
  }
  bool quiz_submission::is_complete() const {
    return workflow_state_ == "complete";
  }
  bool quiz_submission::is_takeable() const {
    return workflow_state_ == "untaken";
  }
  bool quiz_submission::is_pending_review() const {
    return workflow_state_ == "pending_review";
  }

} // namespace cnvs
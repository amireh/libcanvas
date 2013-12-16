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

#include "canvas/resources/course.hpp"
#include "canvas/utility.hpp"
#include "canvas/parsers/quiz_parser.hpp"
#include "canvas/session.hpp"
#include <cstdio>
#include <cstring>

namespace cnvs {
  course::course(id_t id)
  : resource(id) {
    url_ = "/courses/" + utility::stringify(id);
  }
  course::~course() {
    while (!quizzes_.empty()) {
      delete quizzes_.back();
      quizzes_.pop_back();
    }
  }

  void course::set_name(string_t const& name) {
    name_ = name;
  }
  void course::set_code(string_t const& code) {
    code_ = code;
  }
  void course::set_workflow_state(string_t const& workflow_state) {
    workflow_state_ = workflow_state;
  }

  string_t const& course::get_name() const {
    return name_;
  }
  string_t const& course::get_code() const {
    return code_;
  }
  string_t const& course::get_workflow_state() const {
    return workflow_state_;
  }
  course::quizzes_t const& course::get_quizzes() const {
    return quizzes_;
  }

  void course::load_quizzes(session& in_session, async_callback_t callback) {
    in_session.get(get_url() + "/quizzes",
      [&](bool success, http::response const &response) -> void {
        quiz_parser lparser;

        if (!success) {
          callback(false);
          return;
        }

        parser::json_documents_t quiz_documents =
          lparser.json_documents(response.body);

        for (auto quiz_document : quiz_documents) {
          quizzes_.push_back(lparser.from_json(quiz_document));
        }

        callback(true);
      });
  }
} // namespace cnvs
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
#include "canvas/resources/quiz.hpp"
#include "canvas/utility.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"

namespace cnvs {
  course::course()
  : resource() {
  }

  course::course(id_t id)
  : resource(id) {
    build_url();
  }

  course::~course() {
    std::for_each(quizzes_.begin(), quizzes_.end(), [](quiz* quiz) {
      delete quiz;
    });

    quizzes_.clear();
  }

  void course::build_url() {
    url_ = "/courses/" + utility::stringify(id_);
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
        resource_parser parser;

        if (!success) {
          callback(false);
          return;
        }

        quizzes_ = parser.parse_resources<quiz>(response.body, [&](quiz* quiz) {
          quiz->set_course(this);
        });


        callback(true);
      });
  }

  void course::deserialize(string_t const& json) {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    if (!reader.parse( json, root )) {
      throw json_parser_error(reader.getFormattedErrorMessages());
    }

    id_ = root.get("id", 0).asUInt();
    name_ = root.get("name", "Course").asString();
    code_ = root.get("course_code", "course").asString();
    workflow_state_ = root.get("workflow_state", "available").asString();

    build_url();
  }
} // namespace cnvs
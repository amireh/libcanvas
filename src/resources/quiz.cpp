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

#include "canvas/resources/quiz.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/session.hpp"
#include "canvas/utility.hpp"
#include <cstdio>
#include <cstring>

namespace cnvs {
  quiz::quiz()
  : resource(),
    course_(nullptr) {
  }

  quiz::quiz(id_t id, course* course)
  : resource(id),
    course_(course) {
  }

  quiz::~quiz() {
  }

  void quiz::set_course(course* course) {
    course_ = course;
    url_ = course->get_url() + "/quizzes/" + utility::stringify(id_);
  }
  void quiz::set_title(string_t const& title) {
    title_ = title;
  }
  void quiz::set_published(bool flag) {
    published_ = flag;
  }
  void quiz::set_access_code(string_t const& access_code) {
    access_code_ = access_code;
  }

  course const* quiz::get_course() const {
    return course_;
  }
  string_t const& quiz::get_title() const {
    return title_;
  }
  bool quiz::is_published() const {
    return published_;
  }
  string_t const& quiz::get_access_code() const {
    return access_code_;
  }

  bool quiz::take(session &in_session, async_callback_t &callback) {
    in_session.post(get_url() + "/", [&](bool success, http::response response) -> void {
    });

    return true;
  }

  void quiz::deserialize(string_t const& json) {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    if (!reader.parse( json, root )) {
      throw json_parser_error(reader.getFormattedErrorMessages());
    }

    id_ = root.get("id", 0).asUInt();
    title_ = root.get("title", "Unnamed Quiz").asString();
  }
} // namespace cnvs
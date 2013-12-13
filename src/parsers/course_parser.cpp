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

#include "canvas/parsers/course_parser.hpp"
#include <cstdio>
#include <cstring>

namespace cnvs {
  course_parser::course_parser() :
  logger("course_parser") {
  }

  course_parser::~course_parser() {
  }

  course* course_parser::from_json(string_t const& raw_json) const {
    course* new_course;
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( raw_json, root );

    if ( !parsingSuccessful ) {
      // report to the user the failure and their locations in the document.
      this->error()
        << "Failed to parse configuration\n"
        << reader.getFormattedErrorMessages();
      return nullptr;
    }

    if (root.isArray()) {
      return this->from_json(root[0].toStyledString());
    }

    new_course = new course( root.get("id", 0).asUInt() );
    new_course->set_name(root.get("name", "Course").asString());
    new_course->set_code(root.get("course_code", "course").asString());
    new_course->set_workflow_state(root.get("workflow_state", "available").asString());

    return new_course;
  }
} // namespace cnvs
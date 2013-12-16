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

#include "canvas/parsers/quiz_parser.hpp"
#include <cstdio>
#include <cstring>

namespace cnvs {
  quiz_parser::quiz_parser()
  : logger("quiz_parser") {
  }

  quiz_parser::~quiz_parser() {
  }

  quiz* quiz_parser::from_json(string_t const& raw_json) const {
    quiz* new_quiz;
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    parser_success = reader.parse( raw_json, root );

    if (!parser_success) {
      throw json_parser_error(reader.getFormattedErrorMessages());
    }

    if (root.isArray()) {
      return this->from_json(root[0].toStyledString());
    }

    new_quiz = new quiz( root.get("id", 0).asUInt(), nullptr );
    new_quiz->set_title(root.get("title", "Course").asString());

    return new_quiz;
  }
} // namespace cnvs
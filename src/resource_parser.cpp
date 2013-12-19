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

#include "canvas/resource_parser.hpp"
#include <iostream>

namespace cnvs {
  resource_parser::resource_parser() {
  }

  resource_parser::~resource_parser() {
  }

  resource_parser::json_documents_t
  resource_parser::json_documents(string_t const& root_json) const {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse( root_json, root )) {
      throw json_parser_error(reader.getFormattedErrorMessages());
    }

    return json_documents(root);
  }

  resource_parser::json_documents_t
  resource_parser::json_documents(Json::Value& root) const {
    json_documents_t documents;

    if (root.isArray()) {
      for (auto element : root) {
        documents.push_back(element.toStyledString());
      }
    }

    return documents;
  }
} // namespace cnvs
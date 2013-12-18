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

#include "canvas/parser.hpp"
#include <iostream>

namespace cnvs {
  typedef parser::json_documents_t json_documents_t;

  parser::parser() {
  }

  parser::~parser() {
  }

  json_documents_t parser::json_documents(string_t const& root_json) const {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    parser_success = reader.parse( root_json, root );

    if (!parser_success) {
      throw json_parser_error(reader.getFormattedErrorMessages());
    }

    return json_documents(root);
  }

  json_documents_t parser::json_documents(Json::Value& root) const {
    json_documents_t documents;

    if (root.isArray()) {
      for (auto element : root) {
        documents.push_back(element.toStyledString());
      }
    }

    return documents;
  }

  // template<typename T>
  // std::vector<T*> parser::parse_resources(string_t const& json) const {
  //   std::vector<T*> resources;
  //   json_documents_t documents(json_documents(json));

  //   for (auto document : documents) {
  //     resources.push_back(from_json(document));
  //   }

  //   return resources;
  // }
} // namespace cnvs
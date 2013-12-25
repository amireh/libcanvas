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
#include "canvas/utility.hpp"
#include <iostream>

namespace Canvas {
  ResourceParser::ResourceParser() {
  }

  ResourceParser::~ResourceParser() {
  }

  ResourceParser::JSONDocuments
  ResourceParser::jsonDocuments(String const& root_json, String const& ns) const {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse( root_json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    return jsonDocuments(root, ns);
  }

  ResourceParser::JSONDocuments
  ResourceParser::jsonDocuments(Json::Value& root, String const& ns) const {
    JSONDocuments documents;

    if (!ns.empty()) {
      root = root[ns];
    }

    if (root.isArray()) {
      for (auto element : root) {
        documents.push_back(element.toStyledString());
      }
    }

    return documents;
  }

  ID ResourceParser::parseId(JSONValue const& document, String const& key) {
    if (!document.isMember(key)) {
      throw JSONError("Expected document to contain an ID field called '" + key + "'",
        document);
    }
    else if (!document[key].isInt()) {
      // try to convert it
      try {
        const String value = document.get(key, "0").asString();

        if (value.size() == 0) {
          return 0;
        }

        return utility::convertTo<int>(value);
      } catch(BadConversion &e) {
        throw JSONError("Expected field '" + key + "' to be numeric.", document);
      }
    }
    else {
      return document[key].asInt();
    }
  }

  ID ResourceParser::parseIdElement(JSONValue const& value) {
    if (!value.isInt()) {
      // try to convert it
      try {
        const String stringValue = value.asString();

        if (value.size() == 0) {
          return 0;
        }

        return utility::convertTo<int>(stringValue);
      } catch(BadConversion &e) {
        throw JSONError("Expected value to be a numeric ID.", value);
      }
    }
    else {
      return value.asInt();
    }
  }

  bool ResourceParser::parseBool(JSONValue const& value) {
    if (value.isBool()) {
      return value.asBool();
    }
    else if (value.isString()) {
      return value.asString() == "true";
    }
    else {
      throw JSONError("Expected value to be a boolean.", value);
    }

    return false;
  }
} // namespace cnvs

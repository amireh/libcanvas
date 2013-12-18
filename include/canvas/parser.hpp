/*
 *  Copyright (c) 2013 Algol Labs <ahmad@algollabs.com>
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

#ifndef H_CANVAS_PARSER_H
#define H_CANVAS_PARSER_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"
#include <json/json.h>
#include <list>

namespace cnvs {

  /**
   * @class course
   * @brief
   * Courses have student enrollments and quizzes.
   */
  class parser {
  public:
    typedef std::list<string_t> json_documents_t;

    parser();
    virtual ~parser();

    virtual resource* from_json(const string_t& json) const = 0;
    virtual json_documents_t json_documents(string_t const& root) const;
    virtual json_documents_t json_documents(Json::Value& root) const;

    /**
     * Bulk parse of resources from a JSON collection.
     */
    template<typename T>
    std::vector<T*> parse_resources(
      const string_t& json,
      std::function<void(T*)> callback = nullptr) const {
      T* resource;
      std::vector<T*> resources;
      json_documents_t documents(json_documents(json));

      for (auto document : documents) {
        resource = (T*)from_json(document);
        resources.push_back(resource);

        if (callback) {
          callback(resource);
        }
      }

      return resources;
    }
  };
}

#endif
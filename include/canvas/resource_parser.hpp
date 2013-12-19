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

#ifndef H_CANVAS_RESOURCE_PARSER_H
#define H_CANVAS_RESOURCE_PARSER_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"
#include <json/json.h>
#include <list>

namespace cnvs {

  /**
   * @class resource_parser
   * @brief
   * Builds resources from JSON documents.
   */
  class resource_parser {
  public:
    resource_parser();
    virtual ~resource_parser();

    /**
     * Build a single resource from a JSON document.
     *
     * @see resource::serialize()
     * @return nullptr if the resource fails to deserialize.
     */
    template<typename T>
    T* parse_resource(const string_t& document) {
      T* resource = new T();

      try {
        resource->deserialize(document);
      }
      catch (...) {
        delete resource;
        return nullptr;
      }

      return resource;
    }

    /**
     * Create multiple resources from a JSON collection.
     *
     * @param[in] json
     *   A valid, conformant JSON collection of documents.
     * @param[in] callback
     *   A handler that will be called everytime a resource has been created so
     *   you can do any post-processing on the resource, if needed.
     *
     * @see resource::deserialize()
     */
    template<typename T>
    std::vector<T*> parse_resources(
      const string_t& json,
      std::function<void(T*)> callback = nullptr) const {
      T* resource;
      std::vector<T*> resources;
      json_documents_t documents(json_documents(json));

      for (auto document : documents) {
        resource = new T();

        try {
          resource->deserialize(document);
        } catch(...) {
          delete resource;
          continue;
        }

        resources.push_back(resource);

        if (callback) {
          callback(resource);
        }
      }

      return resources;
    }

  protected:
    typedef std::list<string_t> json_documents_t;

    virtual json_documents_t json_documents(string_t const& root) const;
    virtual json_documents_t json_documents(Json::Value& root) const;
  };
}

#endif
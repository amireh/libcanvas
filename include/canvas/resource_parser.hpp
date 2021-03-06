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
#include "canvas/logger.hpp"
#include <json/json.h>
#include <list>

namespace Canvas {

  #define abort_resource_parsing(resource) \
    delete resource; \
    continue;

  /**
   * @class resource_parser
   * @brief
   * Builds resources from JSON documents.
   */
  class ResourceParser {
  public:
    ResourceParser();
    virtual ~ResourceParser();

    /**
     * Build a single resource from a JSON document.
     *
     * @see resource::serialize()
     * @return nullptr if the resource fails to deserialize.
     */
    template<typename T>
    T* parseResource(const String& document) {
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
    std::vector<T*> parseResources(
      String const& json,
      std::function<void(T*)> callback = nullptr,
      String ns = "") const {
      T* resource;
      std::vector<T*> resources;
      JSONDocuments documents(jsonDocuments(json, ns));
      Json::Reader reader;
      Json::Value documentRoot;

      for (auto document : documents) {
        resource = new T();

        if (!reader.parse( document, documentRoot )) {
          throw JSONParserError(reader.getFormattedErrorMessages());
        }

        try {
          resource->setDocument(documentRoot);
          resource->deserialize(documentRoot);
        } catch(std::exception &e) {
          Logger::defaultLogger().error()
            << "Resource deserialization failed: "
            << e.what()
            << "\nErratic document:\n"
            << document;

          abort_resource_parsing(resource);
        } catch(...) {
          Logger::defaultLogger().error()
            << "An unknown exception was raised deserializing object. "
            << "Erratic JSON document:\n"
            << document;

          abort_resource_parsing(resource);
        }

        resources.push_back(resource);

        if (callback) {
          callback(resource);
        }
      }

      return resources;
    }

    /**
     * Attempt to parse a numeric field, particularly useful for ID fields.
     *
     * Can handle the following formats:
     *
     *  - 123   => 123 [Integer]
     *  - "123" => 123 [String]
     *  - ""    => 0   [String]
     *
     * @throw MissingFieldError if the field is missing in the document
     * @throw JSONError if the value could not be parsed
     */
    static ID parseId(JSONValue const&, String const& key = "id");
    static ID parseIdElement(JSONValue const&);

    /**
     * Attempt to parse a boolean field in one of the following formats:
     *
     * @throw JSONError if the value could not be parsed
     *
     * @return true if the value is a boolean and is true
     * @return false if the value is a boolean and is false
     * @return true if the value is the string "true"
     */
    static bool parseBool(JSONValue const&);

  protected:
    typedef std::list<String> JSONDocuments;

    virtual JSONDocuments jsonDocuments(String const& root, String const& ns) const;
    virtual JSONDocuments jsonDocuments(Json::Value& root, String const& ns) const;
  };
}

#endif

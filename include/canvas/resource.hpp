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

#ifndef H_CANVAS_RESOURCE_H
#define H_CANVAS_RESOURCE_H

#include "canvas/canvas.hpp"
#include <json/json.h>

namespace Canvas {

  class ResourceParser;

  /**
   * @class Resource
   * @brief
   * Base resource.
   */
  class Resource {
  public:
    inline
    Resource() : mId(0) {
    }

    inline
    Resource(ID id)
    : mId(id) {
    }

    inline
    virtual ~Resource() {};

    inline
    virtual ID id() const {
      return mId;
    }

    inline
    virtual String const& url() const {
      return mUrl;
    }

    /**
     * Populate the resource from a JSON document.
     */
    virtual void deserialize(String const&) = 0;

  protected:
    friend class ResourceParser;

    inline
    virtual void setDocument(Json::Value& document) {
      mDocument = document;
    }

    ID mId;
    String mUrl;
    Json::Value mDocument;
  };
}

#endif

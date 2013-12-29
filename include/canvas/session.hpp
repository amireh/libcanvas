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

#ifndef H_CANVAS_SESSION_H
#define H_CANVAS_SESSION_H

#include "canvas/canvas.hpp"
#include "canvas/logger.hpp"
#include "canvas/http/response.hpp"
#include "canvas/http/download.hpp"
#include <curl/curl.h>

namespace Canvas {

  class Student;
  class Resource;
  /**
   * @class session
   * @brief
   * API communicator module capable of retrieving and submitting JSON data.
   */
  class Session : public Logger {
  public:
    typedef std::function<void(bool success, HTTP::Response const&)> RC_GET;
    typedef std::function<void(bool success, HTTP::Response const&)> RC_POST;

    Session();
    virtual ~Session();

    /**
     * Impersonate a given student. Further API calls will be made on behalf of
     * the given Student.
     *
     * @note
     * The student's API Token must be set, see Student::apiToken().
     */
    virtual void authenticate(Student const&);

    /**
     * Bind this session to the given API Token.
     */
    virtual void authenticate(String const&);

    /**
     * Perform a GET API call to retrieve a document, or a set of documents.
     */
    virtual bool get(URI const&, RC_GET);

    /**
     * Perform a POST API call to create resources, or upload data.
     */
    virtual bool post(URI const&, String const& data, RC_GET);

    /**
     * Perform a PUT API call to update a resource.
     */
    virtual bool put(URI const&, String const& data, RC_GET);

  protected:
    /**
     * Generate the fully-qualified URI for an API endpoint.
     */
    virtual URI apiEndpoint(URI const&) const;

    struct curl_slist* addJsonHeaders(struct curl_slist* = nullptr);
    void free_headers();
    virtual bool performRequest(String const&, RC_GET);

    CURL *mCurl;
    struct curl_slist *mHeaders;
  };


} // namespace cnvs

#endif

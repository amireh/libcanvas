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

    virtual void authenticate(String const& username, String const& password);
    virtual void authenticate(String const& token);

    virtual bool get(URI const&, RC_GET);
    virtual bool post(URI const&, RC_POST);

  protected:
    /**
     * Update the Authorization headers with the current identity.
     */
    virtual void stampIdentity();

    /**
     * Generate the fully-qualified URI for an API endpoint.
     */
    virtual URI apiEndpoint(URI const&) const;

    struct curl_slist* addJsonHeaders(struct curl_slist* = nullptr);
    void free_headers();

    struct identity_t {
      String username;
      String password;
      String token;
    } identity_;

    CURL *mCurl;
    struct curl_slist *mHeaders;
  };


} // namespace cnvs

#endif

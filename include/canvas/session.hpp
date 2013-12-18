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
#include <curl/curl.h>

namespace cnvs {

  /**
   * @class session
   * @brief
   * API communicator module capable of retrieving and submitting JSON data.
   */
  class session : public logger {
  public:
    typedef std::function<void(bool success, http::response const&)> RC_GET;
    typedef std::function<void(bool success, http::response const&)> RC_POST;

    session();
    virtual ~session();

    virtual void authenticate(string_t const& username, string_t const& password);
    virtual void authenticate(string_t const& token);

    virtual bool get(uri_t const&, RC_GET);
    virtual bool post(uri_t const&, RC_POST);

  protected:
    /**
     * Update the Authorization headers with the current identity.
     */
    virtual void stamp_identity();

    /**
     * Generate the fully-qualified URI for an API endpoint.
     */
    virtual uri_t api_endpoint(uri_t const&) const;

    struct identity_t {
      string_t username;
      string_t password;
      string_t token;
    } identity_;

    struct curl_slist *json_headers_;
  };

  /** Used internally by the resource_manager to manage downloads */
  struct download_t {
    inline
    download_t(std::ostream& s)
    : status(false),
      size(0),
      retry_no(0),
      stream(s) {
    }

    string_t      uri;
    bool          status;
    uint64_t      size;
    int           retry_no;
    std::ostream  &stream;
  };

} // namespace cnvs

#endif

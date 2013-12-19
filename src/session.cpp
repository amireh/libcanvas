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

#include "canvas/session.hpp"
#include "canvas/settings.hpp"

namespace cnvs {
  static size_t on_curl_data(char *buffer, size_t size, size_t nmemb, void *userdata)
  {
    download_t  *download;
    size_t      realsize;
    string_t    buffer_str;

    download = (download_t*)userdata;
    realsize = size * nmemb;
    download->size += realsize;
    buffer_str = string_t(buffer, realsize);

    if (settings::is_enabled("-v")) {
      logger l("cURL");
      l.debug() << "received " << realsize << " bytes";
      l.debug() << buffer_str;
    }

    download->stream << buffer_str;

    return realsize;
  }

  session::session() :
  logger("session"),
  headers_(nullptr),
  curl_(nullptr) {
    curl_ = curl_easy_init();
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &on_curl_data);
  }

  session::~session() {
    free_headers();
    curl_easy_cleanup(curl_);
    curl_ = nullptr;
  }

  void session::free_headers() {
    if (headers_) {
      curl_slist_free_all(headers_);
      headers_ = nullptr;
    }
  }

  struct curl_slist* session::add_json_headers(struct curl_slist* headers) {
    headers = curl_slist_append(headers, "Content-Type: application/json;charset=UTF-8");
    headers = curl_slist_append(headers, "Accept: application/json;charset=UTF-8");

    return headers;
  }

  void session::authenticate(string_t const& username, string_t const& password) {
    throw "BASIC AUTH not implemented yet";

    identity_.username = username;
    identity_.password = password;

    stamp_identity();
  }

  void session::authenticate(string_t const& token) {
    identity_.token = token;

    stamp_identity();
  }

  void session::stamp_identity() {
    free_headers();

    headers_ = add_json_headers();
    headers_ = curl_slist_append(headers_,
      ("Authorization: Bearer " + identity_.token).c_str());

    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers_);
  }

  bool session::get(uri_t const& endpoint, session::RC_GET callback) {
    CURL* curl;
    CURLcode curlrc;
    char curlerr[CURL_ERROR_SIZE];
    http::response response;
    uint8_t http_rc = 0;
    download_t dl;

    dl.uri = api_endpoint(endpoint);

    info() << "Downloading " << dl.uri;

    curl_easy_setopt(curl_, CURLOPT_ERRORBUFFER, curlerr);
    curl_easy_setopt(curl_, CURLOPT_URL, dl.uri.c_str());
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &dl);

    curlrc = curl_easy_perform(curl_);

    if (curlrc != 0) {
      error() << "a CURL error was encountered; " << curlrc << " => " << curlerr;
      callback(false, response);

      return false;
    }

    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &http_rc);

    if (http_rc != 200) {
      error() << "remote server error, HTTP code: " << http_rc << ", download failed";
      callback(false, response);

      return false;
    }

    response.body = static_cast<std::ostringstream*>(&dl.stream)->str();

    callback(true, response);

    return true;
  }

  bool session::post(uri_t const& endpoint, session::RC_POST callback) {
    return true;
  }

  uri_t session::api_endpoint(uri_t const& endpoint) const {
    return string_t(settings::get("canvas_host")
      + ":"
      + settings::get("canvas_port")
      + settings::get("canvas_api_prefix")
      + endpoint);
  }

} // namespace cnvs
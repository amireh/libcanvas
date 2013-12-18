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
  session::session() :
  logger("session"),
  json_headers_(NULL) {
    json_headers_ = curl_slist_append(json_headers_, "Content-Type: application/json;charset=UTF-8");
    json_headers_ = curl_slist_append(json_headers_, "Accept: application/json;charset=UTF-8");
  }

  session::~session() {
    if (json_headers_) {
      curl_slist_free_all(json_headers_);
    }

    json_headers_ = nullptr;
  }

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
    json_headers_ = curl_slist_append(json_headers_, "Authorization:");
    json_headers_ = curl_slist_append(json_headers_,
      ("Authorization: Bearer " + identity_.token).c_str());
  }

  bool session::get(uri_t const& endpoint, session::RC_GET callback) {
    download_t* dl;
    CURL* curl;
    CURLcode curlrc;
    char curlerr[CURL_ERROR_SIZE];
    uint8_t http_rc;
    std::ostringstream outbuf;
    http::response resp;

    curl = curl_easy_init();

    if (!curl) {
      this->error() << "unable to resolve URL " << dl->uri << ", aborting remote download request";

      return false;
    }

    dl = new download_t(outbuf);
    dl->uri = api_endpoint(endpoint);

    info() << "Downloading " << dl->uri;

    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlerr);
    curl_easy_setopt(curl, CURLOPT_URL, dl->uri.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, json_headers_);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &on_curl_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, dl);

    curlrc = curl_easy_perform(curl);

    if (curlrc != 0) {
      error() << "a CURL error was encountered; " << curlrc << " => " << curlerr;

      delete dl;

      curl_easy_cleanup(curl);

      callback(false, resp);

      return false;
    }

    http_rc = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_rc);

    if (http_rc != 200) {
      error() << "remote server error, HTTP code: " << http_rc << ", download failed";

      delete dl;

      callback(false, resp);
      curl_easy_cleanup(curl);

      return false;
    }

    curl_easy_cleanup(curl);

    resp.body = static_cast<std::ostringstream*>(&dl->stream)->str();
    delete dl;

    callback(true, resp);

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
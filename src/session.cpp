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

namespace Canvas {
  using HTTP::Download;

  static size_t on_curl_data(char *buffer, size_t size, size_t nmemb, void *userdata)
  {
    Download  *download;
    size_t      realsize;
    String    buffer_str;

    download = (Download*)userdata;
    realsize = size * nmemb;
    download->size += realsize;
    buffer_str = String(buffer, realsize);

    if (settings::isEnabled("-v")) {
      Logger l("cURL");
      l.debug() << "received " << realsize << " bytes";
      l.debug() << buffer_str;
    }

    download->stream << buffer_str;

    return realsize;
  }

  Session::Session() :
  Logger("session"),
  mHeaders(nullptr),
  mCurl(nullptr) {
    mCurl = curl_easy_init();
    curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, &on_curl_data);
  }

  Session::~Session() {
    free_headers();
    curl_easy_cleanup(mCurl);
    mCurl = nullptr;
  }

  void Session::free_headers() {
    if (mHeaders) {
      curl_slist_free_all(mHeaders);
      mHeaders = nullptr;
    }
  }

  struct curl_slist* Session::addJsonHeaders(struct curl_slist* headers) {
    headers = curl_slist_append(headers, "Content-Type: application/json;charset=UTF-8");
    headers = curl_slist_append(headers, "Accept: application/json;charset=UTF-8");

    return headers;
  }

  void Session::authenticate(String const& username, String const& password) {
    throw "BASIC AUTH not implemented yet";

    identity_.username = username;
    identity_.password = password;

    stampIdentity();
  }

  void Session::authenticate(String const& token) {
    identity_.token = token;

    stampIdentity();
  }

  void Session::stampIdentity() {
    free_headers();

    mHeaders = addJsonHeaders();
    mHeaders = curl_slist_append(mHeaders,
      ("Authorization: Bearer " + identity_.token).c_str());

    curl_easy_setopt(mCurl, CURLOPT_HTTPHEADER, mHeaders);
  }

  bool Session::get(URI const& endpoint, Session::RC_GET callback) {
    CURLcode curlrc;
    char curlerr[CURL_ERROR_SIZE];
    HTTP::Response response;
    uint8_t http_rc = 0;
    Download dl;

    dl.uri = apiEndpoint(endpoint);

    info() << "Downloading " << dl.uri;

    curl_easy_setopt(mCurl, CURLOPT_ERRORBUFFER, curlerr);
    curl_easy_setopt(mCurl, CURLOPT_URL, dl.uri.c_str());
    curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &dl);

    curlrc = curl_easy_perform(mCurl);

    if (curlrc != 0) {
      error() << "a CURL error was encountered; " << curlrc << " => " << curlerr;
      callback(false, response);

      return false;
    }

    curl_easy_getinfo(mCurl, CURLINFO_RESPONSE_CODE, &http_rc);

    if (http_rc != 200) {
      error() << "remote server error, HTTP code: " << http_rc << ", download failed";
      callback(false, response);

      return false;
    }

    response.body = static_cast<std::ostringstream*>(&dl.stream)->str();

    callback(true, response);

    return true;
  }

  bool Session::post(URI const& endpoint, Session::RC_POST callback) {
    return true;
  }

  URI Session::apiEndpoint(URI const& endpoint) const {
    return String(settings::get("canvas_host")
      + ":"
      + settings::get("canvas_port")
      + settings::get("canvas_api_prefix")
      + endpoint);
  }

} // namespace cnvs

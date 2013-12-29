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
#include "canvas/resources/student.hpp"

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

    if (Settings::isEnabled("-v")) {
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

  void Session::authenticate(Student const& student) {
    free_headers();

    mHeaders = addJsonHeaders();
    mHeaders = curl_slist_append(mHeaders,
      ("Authorization: Bearer " + student.apiToken()).c_str());

    curl_easy_setopt(mCurl, CURLOPT_HTTPHEADER, mHeaders);
  }

  void Session::authenticate(String const& apiToken) {
    Student student;
    student.setApiToken(apiToken);

    authenticate(student);
  }

  bool Session::get(URI const& endpoint, Session::RC_GET callback) {
    curl_easy_setopt(mCurl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, NULL);

    return performRequest(endpoint, callback);
  }

  bool Session::post(URI const& endpoint, String const& data, RC_GET callback) {
    curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, (void*)data.c_str());

    return performRequest(endpoint, callback);
  }

  bool Session::put(URI const& endpoint, String const& data, RC_GET callback) {
    curl_easy_setopt(mCurl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(mCurl, CURLOPT_POSTFIELDS, (void*)data.c_str());

    return performRequest(endpoint, callback);
  }

  URI Session::apiEndpoint(URI const& endpoint) const {
    return String(Settings::get("canvas_host")
      + ":"
      + Settings::get("canvas_port")
      + Settings::get("canvas_api_prefix")
      + endpoint);
  }

  bool Session::performRequest(String const& endpoint, RC_GET callback) {
    HTTP::Response response;
    HTTP::Download dl;
    CURLcode curlrc;
    char curlerr[CURL_ERROR_SIZE];

    dl.uri = apiEndpoint(endpoint);

    curl_easy_setopt(mCurl, CURLOPT_ERRORBUFFER, curlerr);
    curl_easy_setopt(mCurl, CURLOPT_URL, dl.uri.c_str());
    curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &dl);

    curlrc = curl_easy_perform(mCurl);

    if (curlrc != 0) {
      error() << "a CURL error was encountered; " << curlrc << " => " << curlerr;
      response.body = curlerr;
      callback(false, response);

      return false;
    }

    curl_easy_getinfo(mCurl, CURLINFO_RESPONSE_CODE, &response.status);

    if (response.status != 200) {
      error()
        << "API error: "
        << "[" << response.status << "]"
        << " " << response.body;

      callback(false, response);

      return false;
    }

    response.body = static_cast<std::ostringstream*>(&dl.stream)->str();

    callback(true, response);

    return true;
  }

} // namespace cnvs

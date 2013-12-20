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

#include "canvas/resources/student.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/utility.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"

namespace Canvas {
  Student::Student()
  : Resource() {
  }

  Student::Student(ID id)
  : Resource(id) {
    buildUrl();
  }

  Student::~Student() {
    std::for_each(mCourses.begin(), mCourses.end(), [](Course* course) {
      delete course;
    });

    mCourses.clear();
  }

  void Student::buildUrl() {
    mUrl = "/users/" + utility::stringify(mId);
  }

  String const& Student::apiToken() const {
    return mApiToken;
  }
  String const& Student::username() const {
    return mUsername;
  }
  String const& Student::password() const {
    return mPassword;
  }
  Student::Courses const& Student::courses() const {
    return mCourses;
  }

  void Student::loadIdentity(Session& session, AsyncCallback callback) {
    session.get("/users/self/logins",
      [&](bool success, HTTP::Response const &response) -> void {
        ResourceParser parser;
        std::vector<Student::Login*> logins;
        Student::Login* login;

        if (!success) {
          callback(false);
          return;
        }

        logins = parser.parseResources<Student::Login>(response.body);
        login = logins.front();

        if (login) {
          mId = login->userId();
        }

        std::for_each(logins.begin(), logins.end(), [](Student::Login* login) {
          delete login;
        });

        logins.clear();

        buildUrl();

        callback(true);
      });
  }

  void Student::loadCourses(Session& session, AsyncCallback callback) {
    session.get(url() + "/courses",
      [&](bool success, HTTP::Response const &response) -> void {
        ResourceParser parser;

        if (!success) {
          callback(false);
          return;
        }

        mCourses = parser.parseResources<Course>(response.body, [&](Course* course) {
        });

        callback(true);
      });
  }

  void Student::deserialize(String const&) {
  }

  void Student::setApiToken(String const& apiToken) {
    mApiToken = apiToken;
  }

  Student::Login::Login()
  : Resource(0) {}

  Student::Login::Login(ID id)
  : Resource(id) {}

  Student::Login::~Login() {}

  void Student::Login::deserialize(String const& json) {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    mUserId = root.get("user_id", 0).asUInt();
  }

  ID Student::Login::userId() const {
    return mUserId;
  }
} // namespace cnvs
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

#include "canvas/resources/quiz.hpp"
#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz_question.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"
#include "canvas/utility.hpp"
#include <cstdio>
#include <cstring>

namespace Canvas {
  Quiz::Quiz()
  : Resource(),
    mCourse(nullptr) {
  }

  Quiz::Quiz(ID id, Course* course)
  : Resource(id),
    mCourse(course) {

    buildUrl();
  }

  Quiz::~Quiz() {
    std::for_each(mQuestions.begin(), mQuestions.end(), [](QuizQuestion* qq) {
      delete qq;
    });

    mQuestions.clear();
  }

  void Quiz::setCourse(Course* course) {
    mCourse = course;
    buildUrl();
  }
  void Quiz::setTitle(String const& title) {
    mTitle = title;
  }
  void Quiz::setPublished(bool flag) {
    mPublished = flag;
  }
  void Quiz::setAccessCode(String const& access_code) {
    mAccessCode = access_code;
  }

  Course const* Quiz::course() const {
    return mCourse;
  }
  String const& Quiz::title() const {
    return mTitle;
  }
  bool Quiz::isPublished() const {
    return mPublished;
  }
  String const& Quiz::accessCode() const {
    return mAccessCode;
  }

  void Quiz::deserialize(String const& json) {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    mId = root.get("id", 0).asUInt();
    mTitle = root.get("title", "Unnamed Quiz").asString();

    buildUrl();
  }

  void Quiz::loadQuestions(Session &session, AsyncCallback callback) {
    session.get(url() + "/questions",
      [&](bool success, HTTP::Response response) -> void {
        if (success) {
          loadQuestions(response.body);
        }

        callback(success);
    });
  }

  void Quiz::loadQuestions(String const& documents) {
    ResourceParser parser;
    parser.parseResources<QuizQuestion>(documents, [&](QuizQuestion* qq) {
      qq->setQuiz(this);
      mQuestions.push_back(qq);
    });
  }

  void Quiz::buildUrl()
  {
    if (!mCourse) {
      return;
    }

    mUrl = mCourse->url() + "/quizzes/" + utility::stringify(mId);
  }

  Quiz::Questions const& Quiz::questions() const {
    return mQuestions;
  }
} // namespace cnvs

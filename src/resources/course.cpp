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

#include "canvas/resources/course.hpp"
#include "canvas/resources/quiz.hpp"
#include "canvas/utility.hpp"
#include "canvas/resource_parser.hpp"
#include "canvas/session.hpp"

namespace Canvas {
  Course::Course()
  : Resource() {
  }

  Course::Course(ID id)
  : Resource(id) {
    buildUrl();
  }

  Course::~Course() {
    std::for_each(mQuizzes.begin(), mQuizzes.end(), [](Quiz* Quiz) {
      delete Quiz;
    });

    mQuizzes.clear();
  }

  void Course::buildUrl() {
    mUrl = "/courses/" + utility::stringify(mId);
  }

  void Course::setName(String const& name) {
    mName = name;
  }
  void Course::setCode(String const& code) {
    mCode = code;
  }
  void Course::setWorkflowState(String const& workflow_state) {
    mWorkflowState = workflow_state;
  }

  String const& Course::name() const {
    return mName;
  }
  String const& Course::code() const {
    return mCode;
  }
  String const& Course::workflowState() const {
    return mWorkflowState;
  }
  Course::Quizzes const& Course::quizzes() const {
    return mQuizzes;
  }

  void Course::loadQuizzes(Session& in_session, AsyncCallback callback) {
    in_session.get(url() + "/quizzes",
      [&](bool success, HTTP::Response const &response) -> void {
        ResourceParser parser;

        if (!success) {
          callback(false);
          return;
        }

        mQuizzes = parser.parseResources<Quiz>(response.body, [&](Quiz* quiz) {
          quiz->setCourse(this);
        });


        callback(true);
      });
  }

  void Course::deserialize(String const& json) {
    Json::Value root;
    Json::Reader reader;
    bool parser_success;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    mId = root.get("id", 0).asUInt();
    mName = root.get("name", "Course").asString();
    mCode = root.get("course_code", "course").asString();
    mWorkflowState = root.get("workflow_state", "available").asString();

    buildUrl();
  }
} // namespace cnvs

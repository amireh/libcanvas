/*
 *  Copyright (c) 2013 Algol Labs <ahmad@algollabs.com>
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

#ifndef H_CANVAS_QUIZ_H
#define H_CANVAS_QUIZ_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"

namespace Canvas {

  class Course;
  class Session;
  /**
   * @class quiz
   * @brief
   * A course quiz.
   */
  class Quiz : public Resource {
  public:
    Quiz();
    Quiz(ID id, Course*);
    virtual ~Quiz();

    virtual void setCourse(Course*);
    virtual void setTitle(String const&);
    virtual void setAccessCode(String const&);
    virtual void setPublished(bool);

    virtual Course const* course() const;
    virtual String const& title() const;
    virtual String const& accessCode() const;

    virtual bool isPublished() const;

    virtual bool take(Session&, AsyncCallback&);

    /**
     * Populate the Quiz from a JSON document.
     */
    virtual void deserialize(String const&);

  protected:
    Course* mCourse;
    String mTitle;
    String mAccessCode;
    bool mPublished;

    void buildUrl();
  };
}

#endif

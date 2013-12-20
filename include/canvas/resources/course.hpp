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

#ifndef H_CANVAS_COURSE_H
#define H_CANVAS_COURSE_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"
#include <vector>

namespace Canvas {

  class Quiz;
  class Session;

  /**
   * \addtogroup Resources
   * @{
   * @class course
   * Courses have student enrollments and quizzes.
   */
  class Course : public Resource {
  public:
    typedef std::vector<Quiz*> Quizzes;

    Course();
    Course(ID id);
    virtual ~Course();

    virtual void setName(String const&);
    virtual void setCode(String const&);
    virtual void setWorkflowState(String const&);

    virtual String const& name() const;
    virtual String const& code() const;
    virtual String const& workflowState() const;
    virtual Quizzes const& quizzes() const;

    virtual void loadQuizzes(Session&, AsyncCallback = nullptr);

    /**
     * Populate the Course from a JSON document.
     */
    virtual void deserialize(String const&);

  protected:
    String mName;
    String mCode;
    String mWorkflowState;
    Quizzes mQuizzes;

    void buildUrl();
  };
  /** @} */
}

#endif

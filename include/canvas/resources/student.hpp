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

#ifndef H_CANVAS_STUDENT_H
#define H_CANVAS_STUDENT_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"
#include <vector>

namespace Canvas {

  class Course;
  class Session;
  class Quiz;

  /**
   * \addtogroup Resources
   * @{
   * @class Student
   * A student can be enrolled in many courses and participate in course quizzes.
   */
  class Student : public Resource {
  public:
    typedef std::vector<Course*> Courses;

    Student();
    Student(ID id);
    virtual ~Student();

    virtual String const& apiToken() const;
    virtual String const& username() const;
    virtual String const& password() const;

    /**
     * Courses this student is enrolled in.
     *
     * See #loadCourses() for loading the courses.
     */
    virtual Courses const& courses() const;

    /**
     * Fetch the student's id.
     *
     * Student#id() should be available if the identity has been successfully
     * loaded.
     */
    virtual void loadIdentity(Session&, AsyncCallback = nullptr);

    /**
     * Fetch all the courses this student is enrolled in.
     */
    virtual void loadCourses(Session&, AsyncCallback = nullptr);

    /**
     * Populate the Student from a JSON document.
     *
     * @warning
     * This is currently no-op as user records can not be fetched from the
     * Canvas API yet.
     */
    virtual void deserialize(String const&);

    virtual void setApiToken(String const&);

  protected:
    String mApiToken;
    String mUsername;
    String mPassword;

    Courses mCourses;

    void buildUrl();

    /**
     * @class Login
     * A student's "identity", or a login, that can be used to authenticate
     * with Canvas.
     *
     * This is currently the only means to actually get the Student's id.
     */
    class Login : public Resource {
    public:
      Login();
      Login(ID);
      virtual ~Login();

      virtual void deserialize(String const&);
      ID userId() const;
    protected:
      ID mUserId;
    };
  };
  /** @} */
}

#endif

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

namespace cnvs {

  class quiz;
  class session;

  /**
   * \addtogroup Resources
   * @{
   * @class course
   * Courses have student enrollments and quizzes.
   */
  class course : public resource {
  public:
    typedef std::vector<quiz*> quizzes_t;

    course();
    course(id_t id);
    virtual ~course();

    virtual void set_name(string_t const&);
    virtual void set_code(string_t const&);
    virtual void set_workflow_state(string_t const&);

    virtual string_t const& get_name() const;
    virtual string_t const& get_code() const;
    virtual string_t const& get_workflow_state() const;
    virtual quizzes_t const& get_quizzes() const;

    virtual void load_quizzes(session&, async_callback_t = nullptr);

    /**
     * Populate the Course from a JSON document.
     */
    virtual void deserialize(string_t const&);

  protected:
    string_t name_;
    string_t code_;
    string_t workflow_state_;
    quizzes_t quizzes_;

    void build_url();
  };
  /** @} */
}

#endif
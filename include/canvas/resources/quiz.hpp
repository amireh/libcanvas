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

namespace cnvs {

  class course;
  class session;
  /**
   * @class quiz
   * @brief
   * A course quiz.
   */
  class quiz : public resource {
  public:
    quiz(id_t id, course*);
    virtual ~quiz();

    virtual void set_course(course*);
    virtual void set_title(string_t const&);
    virtual void set_access_code(string_t const&);
    virtual void set_published(bool);

    virtual course const* get_course() const;
    virtual string_t const& get_title() const;
    virtual string_t const& get_access_code() const;

    virtual bool is_published() const;

    virtual bool take(session&, async_callback_t&);

  protected:
    course* course_;
    string_t title_;
    string_t access_code_;
    bool published_;
  };
}

#endif
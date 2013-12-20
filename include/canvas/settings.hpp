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

#ifndef H_CANVAS_SETTINGS_H
#define H_CANVAS_SETTINGS_H

#include "canvas/canvas.hpp"
#include <map>

namespace Canvas {

  /**
   * @class settings
   * @brief
   * A temporary hack to store some library-wide settings
   */
  class settings {
  public:
    inline settings() {}
    inline ~settings() {}

    static void setDefaults();

    static void enable(String const& id);
    static void disable(String const& id);
    static void set(String const& id, String const& value);
    static bool isEnabled(String const& id);
    static String const& get(String const& id);

  protected:
    typedef std::map<String, bool>    FlagSettings;
    typedef std::map<String, String>  LiteralSettings;

    static FlagSettings mFlagSettings;
    static LiteralSettings mLiteralSettings;
  };
}

#endif

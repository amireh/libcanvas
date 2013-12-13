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
 */

#include "canvas/file_manager.hpp"
#include "canvas/utility.hpp"

#include <map>

namespace cnvs {
  file_manager* file_manager::__instance = 0;

  file_manager::file_manager()
  : logger("file manager") {
  }

  file_manager::~file_manager() {
  }

  file_manager& file_manager::singleton() {
    if (!__instance)
      __instance = new file_manager();

    return *__instance;
  }

  bool file_manager::load_file(std::ifstream &fs, string_t& out_buf)
  {
    if (!fs.is_open() || !fs.good()) {
      return false;
    }

    while (fs.good()) {
      out_buf.push_back(fs.get());
    }

    out_buf.erase(out_buf.size()-1,1);

    return true;
  }

  bool file_manager::load_file(string_t const& path, string_t& out_buf)
  {
    bool rc;
    std::ifstream stream(path);

    rc = load_file(stream, out_buf);

    stream.close();

    return rc;
  }
}
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

#include "canvas/settings.hpp"

namespace cnvs {
  settings::flag_settings_t     settings::flag_settings_;
  settings::literal_settings_t  settings::literal_settings_;

  const static string_t nil_setting("");

  void settings::enable(string_t const& id) {
    flag_settings_.insert(std::make_pair(id, true));
  }

  void settings::disable(string_t const& id) {
    flag_settings_.erase(id);
  }

  bool settings::is_enabled(string_t const& id) {
    return flag_settings_.find(id) != flag_settings_.end();
  }

  void settings::set(string_t const& k, string_t const& v) {
    if (literal_settings_.find(k) != literal_settings_.end()) {
      literal_settings_[k] = v;
      return;
    }

    literal_settings_.insert(std::make_pair(k,v));
  }

  string_t const& settings::get(string_t const& k) {
    if (literal_settings_.find(k) == literal_settings_.end())
      return nil_setting;

    return literal_settings_.find(k)->second;
  }

  void settings::set_defaults() {
    set("canvas_host", "http://localhost");
    set("canvas_port", "3000");
    set("canvas_api_prefix", "/api/v1");
  }
}
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

namespace Canvas {
  settings::FlagSettings     settings::mFlagSettings;
  settings::LiteralSettings  settings::mLiteralSettings;

  const static String nil_setting("");

  void settings::enable(String const& id) {
    mFlagSettings.insert(std::make_pair(id, true));
  }

  void settings::disable(String const& id) {
    mFlagSettings.erase(id);
  }

  bool settings::isEnabled(String const& id) {
    return mFlagSettings.find(id) != mFlagSettings.end();
  }

  void settings::set(String const& k, String const& v) {
    if (mLiteralSettings.find(k) != mLiteralSettings.end()) {
      mLiteralSettings[k] = v;
      return;
    }

    mLiteralSettings.insert(std::make_pair(k,v));
  }

  String const& settings::get(String const& k) {
    if (mLiteralSettings.find(k) == mLiteralSettings.end())
      return nil_setting;

    return mLiteralSettings.find(k)->second;
  }

  void settings::setDefaults() {
    set("canvas_host", "http://localhost");
    set("canvas_port", "3000");
    set("canvas_api_prefix", "/api/v1");
  }
}
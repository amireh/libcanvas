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

#ifndef H_CANVAS_UTILITY_H
#define H_CANVAS_UTILITY_H

#include "canvas/canvas.hpp"
#include "canvas/exception.hpp"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

namespace Canvas {
namespace utility {

  inline static String stringify(bool x)
  {
    return x ? "true" : "false";
  }

  template<typename T>
  inline static String stringify(const T& x)
  {
    std::ostringstream o;
    if (!(o << x))
      throw BadConversion(String("stringify(")
                + typeid(x).name() + ")");
    return o.str();
  }

  // helper; converts an integer-based type to a string
  template<typename T>
  inline static void convert(String const& s, T& inValue,
            bool fail_if_leftovers = true)
  {
    std::istringstream _buffer(s);
    char c;
    if (!(_buffer >> inValue) || (fail_if_leftovers && _buffer.get(c)))
      throw BadConversion(s);
  }

  template<typename T>
  inline static T convertTo(const std::string& s, bool fail_if_leftovers = true)
  {
    T _value;
    convert(s, _value, fail_if_leftovers);
    return _value;
  }

  inline static uint64_t toNumber(String const& s) {
    return convertTo<uint64_t>(s);
  }

  /* splits a string s using the delimiter delim */
  typedef std::vector<String> partitioned_string_t;
  inline static
  partitioned_string_t split(const String &s, char delim = '\n') {
    partitioned_string_t elems;
    std::stringstream ss(s);
    String item;
    while(std::getline(ss, item, delim)) {
      elems.push_back(item);
    }
    return elems;
  }

  inline static
  String sanitize(String const& s) {
    String out(s);
    std::transform(out.begin(), out.end(), out.begin(), ::tolower);
    std::replace(out.begin(),   out.end(), ' ', '_');
    return out;
  }

  inline static
  void ijoin(const std::vector<String>& tokens, String &out, char delim) {
    for (std::vector<String>::const_iterator token = tokens.begin();
    token != tokens.end();
    ++token)
    {
      out += *token;
      out.push_back(delim);
    }
  }

  inline static
  String join(const std::vector<String>& tokens, char delim) {
    String out;
    ijoin(tokens, out, delim);
    return out;
  }
} // namespace utility
} // namespace cnvs

#endif

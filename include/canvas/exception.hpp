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

#ifndef H_CANVAS_EXCEPTION_H
#define H_CANVAS_EXCEPTION_H

#include <exception>
#include <string>
#include <stdexcept>
#include <json/json.h>

namespace Canvas {

  /**
   * \addtogroup Errors
   * @{
   */

  /**
   * Thrown when an argument passed to Utility::convertTo<> is not a number
   * and thus can not be converted.
   */
  class BadConversion : public std::runtime_error {
  public:
    inline BadConversion(const std::string& s)
    : std::runtime_error(s)
    { }
  };

  class JSONParserError : public std::runtime_error {
  public:
    inline JSONParserError(const std::string& s)
    : std::runtime_error(s)
    { }
  };

  class JSONError : public std::runtime_error {
  public:
    inline JSONError(const std::string& s, Json::Value const &d)
    : std::runtime_error(s + "\nErratic JSON document: " + d.toStyledString())
    {
    }
  };

  class MissingFieldError : public JSONError {
  public:
    inline MissingFieldError(const std::string &field, Json::Value const &d)
    : JSONError("Missing field '" + field + "'.", d)
    {
    }
  };

  /**
   * Indicates a resource was being accessed before being fully loaded.
   */
  class UninitializedError : public std::runtime_error {
  public:
    inline UninitializedError(const std::string& s)
    : std::runtime_error(s)
    { }
  };

  /** @} */

} // end of namespace cnvs

#endif

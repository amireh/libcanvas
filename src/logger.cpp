/*
 *  Copyright (C) 2013 Algol Labs <ahmad@algollabs.com>
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

#include "canvas/logger.hpp"
#include <iomanip>

namespace Canvas {

  static char levels[] = { 'D','I','N','W','E','A','C' };
  static char threshold = 'D';

  ostringstream Logger::gSink;
  ostream*      Logger::gOut = &std::cout;
  bool          Logger::gWithTimestamps = true;
  String      Logger::gAppName = "";
  int           Logger::gIndentLevel = 0;
  bool          Logger::gSilenced = false;
  Logger        Logger::gDefaultLogger("canvas");

  Logger const& Logger::defaultLogger() {
    return gDefaultLogger;
  }

  void Logger::mute() {
    gSilenced = true;
  }
  void Logger::unmute() {
    gSilenced = false;
  }

  void Logger::setThreshold(char level) {
    threshold = level;
  }

  void Logger::setStream(std::ostream* s) {
    gOut = s;
  }

  void Logger::enableTimestamps(bool f) {
    gWithTimestamps = f;
  }

  void Logger::setAppName(String const& in_app_name) {
    gAppName = in_app_name;
  }

  void Logger::indent() {
    ++gIndentLevel;
  }

  void Logger::deindent() {
    --gIndentLevel;
  }

  Logger::Logger(String context)
  : mContext(context)
  {
  }

  Logger::~Logger()
  {
  }

  ostream& Logger::log(char lvl) const {
    if (gSilenced)
      return gSink;

    bool enabled = false;
    for (int i = 0; i < 7; ++i)
      if (levels[i] == threshold) { enabled = true; break; }
      else if (levels[i] == lvl) break;

    if (!enabled)
      return gSink;

    if (gWithTimestamps) {
      struct tm *pTime;
      time_t ctTime; time(&ctTime);
      pTime = localtime( &ctTime );
      std::ostringstream timestamp;
      timestamp
        << std::setw(2) << std::setfill('0') << pTime->tm_mon
        << '-' << std::setw(2) << std::setfill('0') << pTime->tm_mday
        << '-' << std::setw(4) << std::setfill('0') << pTime->tm_year + 1900
        << ' ' << std::setw(2) << std::setfill('0') << pTime->tm_hour
        << ":" << std::setw(2) << std::setfill('0') << pTime->tm_min
        << ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec
        << " ";
      (*gOut) << timestamp.str();
    }

    if (!gAppName.empty()) {
      (*gOut) << gAppName << " ";
    }

    for (int i = 0; i < gIndentLevel; ++i)
      (*gOut) << "  ";

    (*gOut) << "[" << lvl << "]" << mUuidPrefix << " "
      << (mContext.empty() ? "" : mContext + ": ");

    return *gOut;
  }

  void Logger::setUuidPrefix(String const& uuid) {
    mUuidPrefix = " {" + uuid + "}";
  }
  String const& Logger::uuidPrefix() const {
    return mUuidPrefix;
  }

  LogStream Logger::debug()  const { return LogStream(log('D')); }
  LogStream Logger::info()   const { return LogStream(log('I')); }
  LogStream Logger::notice() const { return LogStream(log('N')); }
  LogStream Logger::warn()   const { return LogStream(log('W')); }
  LogStream Logger::error()  const { return LogStream(log('E')); }
  LogStream Logger::alert()  const { return LogStream(log('A')); }
  LogStream Logger::crit()   const { return LogStream(log('C')); }
  LogStream Logger::plain()  const { return LogStream(*gOut); }

  LogStream::LogStream(std::ostream& in_s)
  : s(in_s) {}

  LogStream::~LogStream() {
    s << std::endl;
  }

  void Logger::renameContext(String const& new_ctx) {
    mContext = new_ctx;
  }
}

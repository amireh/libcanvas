/*
 *  Copyright (c) 2011-2012 Ahmad Amireh <kandie@mxvt.net>
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

#ifndef H_CANVAS_LOGGER_H
#define H_CANVAS_LOGGER_H

#include "canvas/canvas.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

namespace Canvas {

  using std::ostream;
  using std::ostringstream;

  struct LogStream;
  class Logger {
  public:

    /**
     * Creates a new logger instance that can be used to spit out
     * messages using a stream interface.
     *
     * Loggers can either be manually instantiated or derived from.
     *
     * The context identifies the module that this logger instance
     * represents, ie: GameManager, db_adapter, UIEngine, etc.
     */
    Logger(String context);
    virtual ~Logger();

    /**
     * A generic, global logger instance that can be used by modules that want
     * to log once or twice, but don't necessarily want to become Logger objects
     * themselves.
     */
    static Logger const& defaultLogger();

    /**
     * Assigns the threshold to use for filtering messages.
     * Messages logged with a level "below" the assigned threshold
     * will not be logged.
     *
     * Available level thresholds (ordered):
     * => D, I, N, W, E, A, C
     */
    static void setThreshold(char level);

    /**
     * Override the stream to append the messages to (defaults to std::cout)
     */
    static void setStream(std::ostream*);

    /**
     * Messages will be prefixed with a timestamp of the following format:
     * => dd-mm-yyyy hh:mm::ss
     */
    static void enableTimestamps(bool on_or_off);

    /** All messages will be prefixed by the specified application name */
    static void setAppName(String const& gAppName);

    static void indent();
    static void deindent();

    static void mute();
    static void unmute();

    /** Message will be prefixed with [D] */
    LogStream debug() const;
    /** Message will be prefixed with [I] */
    LogStream info() const;
    /** Message will be prefixed with [N] */
    LogStream notice() const;
    /** Message will be prefixed with [W] */
    LogStream warn() const;
    /** Message will be prefixed with [E] */
    LogStream error() const;
    /** Message will be prefixed with [A] */
    LogStream alert() const;
    /** Message will be prefixed with [C] */
    LogStream crit() const;

    LogStream plain() const;

    /**
     * Subsequent messages will be prefixed with {IN_UUID}
     * positioned right after the [LEVEL] part.
     */
    void setUuidPrefix(String const&);

    /** The assigned UUID prefix, if any */
    String const& uuidPrefix() const;

  protected:
    void renameContext(String const&);

  private:
    ostream& log(char lvl) const;
    String mContext;

    static ostringstream  gSink;
    static ostream*       gOut;
    static bool           gWithTimestamps;
    static bool           gWithAppName;
    static bool           gSilenced;
    static String         gAppName;
    static int            gIndentLevel;
    static Logger         gDefaultLogger;

    String mUuidPrefix;
  }; // end of logger class

  struct LogStream {
    LogStream(std::ostream&);
    ~LogStream();

    std::ostream &s;

    template<typename T>
    inline LogStream& operator<<(T const& data) {
      s << data;
      return *this;
    }
  };

} // namespace cnvs

#endif

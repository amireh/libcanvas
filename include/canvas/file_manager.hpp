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

#ifndef H_CANVAS_FILE_MANAGER_H
#define H_CANVAS_FILE_MANAGER_H

#include "canvas/canvas.hpp"
#include "canvas/logger.hpp"

#include <sstream>
#include <fstream>

namespace Canvas {

  /**
   * \addtogroup Core
   * @{
   * @class file_manager
   *
   *
   */
  class FileManager : public Logger {
  public:

    static FileManager& singleton();

    virtual ~FileManager();
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    /**
     * note: the stream must be open and this method will NOT close it
     */
    bool load_file(std::ifstream &file, String& out);
    bool load_file(String const& path, String& out);

  private:
    explicit FileManager();
    static FileManager* __instance;
  };
  /** @} */

} // namespace cnvs

#endif

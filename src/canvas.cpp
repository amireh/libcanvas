#include "canvas/canvas.hpp"
#include "canvas/file_manager.hpp"

namespace Canvas {
  int init(int argc, char** argv) {
    FileManager::singleton();
    return 0;
  }

  void free() {
    delete &FileManager::singleton();
  }
}

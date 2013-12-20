#include "canvas/canvas.hpp"
#include "canvas/file_manager.hpp"
#include "canvas/settings.hpp"

namespace Canvas {
  int init(int argc, char** argv) {
    FileManager::singleton();
    Settings::setDefaults();
    return 0;
  }

  void free() {
    delete &FileManager::singleton();
  }
}

#include "canvas/canvas.hpp"
#include "canvas/file_manager.hpp"

namespace cnvs {
  int canvas_init(int argc, char** argv) {
    file_manager::singleton();
    return 0;
  }

  void canvas_free() {
    delete &file_manager::singleton();
  }
}
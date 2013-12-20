#include "canvas/canvas.hpp"
#include "canvas/file_manager.hpp"
#include "canvas/settings.hpp"
#include "canvas/logger.hpp"

namespace Canvas {
  int init(int argc, char** argv) {
    FileManager::singleton();
    Settings::setDefaults();

    for (int i = 0; i < argc; ++i) {
      String arg(argv[i]);

      if (arg == "-v" || arg == "--verbose") {
        Settings::enable("verbose");
      }
    }

    if (!Settings::isEnabled("verbose")) {
      Logger::mute();
    }

    return 0;
  }

  void free() {
    delete &FileManager::singleton();
  }
}

#include "canvas/canvas.hpp"
#include "canvas/settings.hpp"
#include "canvas/logger.hpp"
#include <curl/curl.h>

namespace Canvas {
  int init(int argc, char** argv) {
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
    curl_global_cleanup();
  }
}

#include "canvas/canvas.hpp"
#include "canvas/logger.hpp"
#include "canvas/settings.hpp"
#include "test_helper.hpp"
#include <gtest/gtest.h>

namespace Canvas {
  class unit_test_env : public ::testing::Environment {
  public:
    unit_test_env(int argc, char** argv) {
      init(argc, argv);
    }

    virtual ~unit_test_env() {
      free();
    }

    virtual void SetUp() {

      Logger::mute();
      settings::setDefaults();
      settings::enable("-v");
    }

    virtual void TearDown() {
    }
  };
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new Canvas::unit_test_env(argc, argv));
  return RUN_ALL_TESTS();
}
#include "canvas/canvas.hpp"
#include "canvas/logger.hpp"
#include "canvas/settings.hpp"
#include "test_helper.hpp"
#include <gtest/gtest.h>

namespace Canvas {
  class unit_test_env : public ::testing::Environment {
  public:
    unit_test_env(int argc, char** argv) {
      Canvas::init(argc, argv);
    }

    virtual ~unit_test_env() {
      Canvas::free();
    }

    virtual void SetUp() {
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

#include "canvas/canvas.hpp"
#include "canvas/logger.hpp"
#include "canvas/settings.hpp"
#include "test_helper.hpp"
#include <gtest/gtest.h>

namespace cnvs {
  class unit_test_env : public ::testing::Environment {
  public:
    unit_test_env(int argc, char** argv) {
    }

    virtual ~unit_test_env() {}

    virtual void SetUp() {
      // logger::mute();
      settings::set_defaults();
      settings::enable("-v");
    }

    virtual void TearDown() {
    }
  };
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::AddGlobalTestEnvironment(new cnvs::unit_test_env(argc, argv));
  return RUN_ALL_TESTS();
}
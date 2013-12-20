#include <gtest/gtest.h>
#include "canvas/settings.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class settings_test : public ::testing::Test {
  };

  TEST_F(settings_test, set) {
    Settings::set("spec_option", "yes");
    ASSERT_TRUE(Settings::get("spec_option") == "yes");
  }
} // namespace cnvs
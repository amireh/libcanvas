#include <gtest/gtest.h>
#include "canvas/settings.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class settings_test : public ::testing::Test {
  protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }
  };

  TEST_F(settings_test, set) {
    settings::set("spec_option", "yes");
    ASSERT_TRUE(settings::get("spec_option") == "yes");
  }
} // namespace cnvs
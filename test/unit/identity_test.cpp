#include <gtest/gtest.h>
#include "canvas/identity.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class identity_test : public ::testing::Test {
  protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    identity identity_;
  };

  TEST_F(identity_test, signature_generation) {
    ASSERT_TRUE(true) << "test failed";
  }
} // namespace cnvs
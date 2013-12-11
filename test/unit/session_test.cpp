#include <gtest/gtest.h>
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class session_test : public ::testing::Test {
  protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    session session_;
  };

  TEST_F(session_test, get_courses) {
    session_.authenticate(CANVAS_SPEC_API_TOKEN);

    bool rc = session_.get("/courses", [&](bool success, http::response const& resp) -> void {
      ASSERT_TRUE(success);
      ASSERT_TRUE(resp.body.length() > 0);
    });

    ASSERT_TRUE(rc);
  }
} // namespace cnvs
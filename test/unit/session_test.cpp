#include <gtest/gtest.h>
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class session_test : public ::testing::Test {
  protected:
    Session mSession;
  };

  TEST_F(session_test, get_courses) {
    bool rc;

    mSession.authenticate(CANVAS_SPEC_API_TOKEN);

    rc = mSession.get("/courses",
      [&](bool success, HTTP::Response const& resp) -> void {
        ASSERT_TRUE(success);
        ASSERT_TRUE(resp.body.length() > 0);
      });

    ASSERT_TRUE(rc);
  }
} // namespace cnvs
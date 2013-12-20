#include <gtest/gtest.h>
#include "canvas/session.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class session_test : public ::testing::Test {
  public:
    session_test() {
      mSession.authenticate(CANVAS_SPEC_API_TOKEN);
    }
  protected:
    Session mSession;
  };

  TEST_F(session_test, get) {
    bool rc = mSession.get("/courses",
      [&](bool success, HTTP::Response const& resp) -> void {
        ASSERT_TRUE(success);
        ASSERT_NE(resp.body.length(), 0);
      });

    ASSERT_TRUE(rc);
  }
} // namespace cnvs
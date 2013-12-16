#include <gtest/gtest.h>
#include "canvas/session.hpp"
#include "canvas/file_manager.hpp"
#include "canvas/parsers/quiz_parser.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class quiz_parser_test : public ::testing::Test {
  protected:
    session session_;
    quiz_parser parser_;
    quiz* quiz_;
  };

  TEST_F(quiz_parser_test, from_json) {
    string_t json = load_fixture("quiz.json");

    ASSERT_NO_THROW(quiz_ = parser_.from_json(json););
    ASSERT_TRUE(quiz_);
    ASSERT_TRUE(quiz_->id() == 1);
    ASSERT_TRUE(quiz_->get_title() == "CNVS-9750");

    delete quiz_;
  }
} // namespace cnvs
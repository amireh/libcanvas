#include <gtest/gtest.h>
#include "canvas/parser.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class spec_parser : public parser {
  public:
    inline spec_parser() {
    }
    inline virtual ~spec_parser() {
    }
    inline virtual resource* from_json(const string_t&) const {
      return nullptr;
    }
  };

  class parser_test : public ::testing::Test {
  protected:
    spec_parser parser_;
  };

  TEST_F(parser_test, json_documents) {
    string_t json("[ {}, {} ]");
    parser::json_documents_t json_documents;

    ASSERT_NO_THROW({
      json_documents = parser_.json_documents(json);
    });

    ASSERT_EQ(json_documents.size(), 2);
  }
} // namespace cnvs
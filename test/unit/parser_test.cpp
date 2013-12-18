#include <gtest/gtest.h>
#include "canvas/parser.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class spec_resource : public resource {
  public:
    inline spec_resource(int id) : resource(id) {}
    inline virtual ~spec_resource() {}
  };
  class spec_parser : public parser {
  public:
    inline spec_parser() {
    }

    inline virtual ~spec_parser() {
    }

    inline virtual resource* from_json(const string_t& json) const {
      spec_resource* resource;
      Json::Value root;
      Json::Reader reader;
      bool parsingSuccessful = reader.parse( json, root );

      if ( !parsingSuccessful ) {
        throw reader.getFormattedErrorMessages();
      }

      resource = new spec_resource(root.get("id", 0).asUInt());

      return resource;
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
    ASSERT_EQ(json_documents.front(), "{}\n");
  }

  TEST_F(parser_test, parse_resources) {
    string_t json = load_fixture("random_documents.json");
    std::vector<spec_resource*> resources;

    ASSERT_NO_THROW({
      resources = parser_.parse_resources<spec_resource>(json);
    });

    ASSERT_EQ(resources.size(), 2);
    ASSERT_EQ(resources.at(0)->id(), 1);
    ASSERT_EQ(resources.at(1)->id(), 2);

    std::for_each(resources.begin(), resources.end(), [](resource* r) {
      delete r;
    });

    resources.clear();
  }
} // namespace cnvs
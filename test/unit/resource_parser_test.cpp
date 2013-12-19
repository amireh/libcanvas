#include <gtest/gtest.h>
#include "canvas/resource_parser.hpp"
#include "test_helper.hpp"

namespace cnvs {

  class spec_resource : public resource {
  public:
    inline spec_resource() : resource() {}
    inline spec_resource(int id) : resource(id) {}
    inline virtual ~spec_resource() {}

    inline virtual void deserialize(const string_t& json) {
      spec_resource* resource;
      Json::Value root;
      Json::Reader reader;
      bool parsingSuccessful = reader.parse( json, root );

      if ( !parsingSuccessful ) {
        throw reader.getFormattedErrorMessages();
      }

      id_ = root.get("id", 0).asUInt();
    }
  };

  class spec_parser : public resource_parser {
  public:
    typedef json_documents_t json_documents_t;

    inline spec_parser() : resource_parser() {}
    inline virtual ~spec_parser() {}

    /**
     * Expose this to the spec, since it's protected in the base class.
     */
    virtual json_documents_t json_documents(string_t const& root) const {
      return resource_parser::json_documents(root);
    }
  };

  class resource_parser_test : public ::testing::Test {
  protected:
    spec_parser parser_;
  };

  TEST_F(resource_parser_test, json_documents) {
    string_t json("[ {}, {} ]");
    spec_parser::json_documents_t json_documents;

    ASSERT_NO_THROW({
      json_documents = parser_.json_documents(json);
    });

    ASSERT_EQ(json_documents.size(), 2);
    ASSERT_EQ(json_documents.front(), "{}\n");
  }

  TEST_F(resource_parser_test, parse_resource) {
    string_t json = load_fixture("random_document.json");
    spec_resource* resource;

    ASSERT_NO_THROW({
      resource = parser_.parse_resource<spec_resource>(json);
    });

    ASSERT_EQ(resource->id(), 5);

    delete resource;
  }

  TEST_F(resource_parser_test, parse_resources) {
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
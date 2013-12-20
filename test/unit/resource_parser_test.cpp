#include <gtest/gtest.h>
#include "canvas/resource_parser.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class spec_resource : public Resource {
  public:
    inline spec_resource() : Resource() {}
    inline spec_resource(int id) : Resource(id) {}
    inline virtual ~spec_resource() {}

    inline virtual void deserialize(const String& json) {
      spec_resource* resource;
      Json::Value root;
      Json::Reader reader;
      bool parsingSuccessful = reader.parse( json, root );

      if ( !parsingSuccessful ) {
        throw reader.getFormattedErrorMessages();
      }

      mId = root.get("id", 0).asUInt();
    }
  };

  class spec_parser : public ResourceParser {
  public:
    typedef JSONDocuments JSONDocuments;

    inline spec_parser() : ResourceParser() {}
    inline virtual ~spec_parser() {}

    /**
     * Expose this to the spec, since it's protected in the base class.
     */
    virtual JSONDocuments jsonDocuments(String const& root) const {
      return ResourceParser::jsonDocuments(root);
    }
  };

  class resource_parser_test : public ::testing::Test {
  protected:
    spec_parser parser_;
  };

  TEST_F(resource_parser_test, jsonDocuments) {
    String json("[ {}, {} ]");
    spec_parser::JSONDocuments jsonDocuments;

    ASSERT_NO_THROW({
      jsonDocuments = parser_.jsonDocuments(json);
    });

    ASSERT_EQ(jsonDocuments.size(), 2);
    ASSERT_EQ(jsonDocuments.front(), "{}\n");
  }

  TEST_F(resource_parser_test, parseResource) {
    String json = load_fixture("random_document.json");
    spec_resource* resource;

    ASSERT_NO_THROW({
      resource = parser_.parseResource<spec_resource>(json);
    });

    ASSERT_EQ(resource->id(), 5);

    delete resource;
  }

  TEST_F(resource_parser_test, parseResources) {
    String json = load_fixture("random_documents.json");
    std::vector<spec_resource*> resources;

    ASSERT_NO_THROW({
      resources = parser_.parseResources<spec_resource>(json);
    });

    ASSERT_EQ(resources.size(), 2);
    ASSERT_EQ(resources.at(0)->id(), 1);
    ASSERT_EQ(resources.at(1)->id(), 2);

    std::for_each(resources.begin(), resources.end(), [](Resource* r) {
      delete r;
    });

    resources.clear();
  }
} // namespace cnvs

#include <gtest/gtest.h>
#include "canvas/resource_parser.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class SpecResource : public Resource {
  public:
    inline SpecResource() : Resource() {}
    inline SpecResource(int id) : Resource(id) {}
    inline virtual ~SpecResource() {}

    inline virtual void deserialize(const String& json) {
      SpecResource* resource;
      Json::Value root;
      Json::Reader reader;
      bool parsingSuccessful = reader.parse( json, root );

      if ( !parsingSuccessful ) {
        throw reader.getFormattedErrorMessages();
      }

      mId = root.get("id", 0).asUInt();
    }
  };

  class SpecParser : public ResourceParser {
  public:
    typedef JSONDocuments JSONDocuments;

    inline SpecParser() : ResourceParser() {}
    inline virtual ~SpecParser() {}

    /**
     * Expose this to the spec, since it's protected in the base class.
     */
    virtual JSONDocuments jsonDocuments(String const& root, String const& ns) const {
      return ResourceParser::jsonDocuments(root, ns);
    }
  };

  class ResourceParserTest : public ::testing::Test {
  protected:
    SpecParser parser_;
  };

  TEST_F(ResourceParserTest, jsonDocuments) {
    String json("[ {}, {} ]");
    SpecParser::JSONDocuments jsonDocuments;

    ASSERT_NO_THROW({
      jsonDocuments = parser_.jsonDocuments(json, "");
    });

    ASSERT_EQ(jsonDocuments.size(), 2);
    ASSERT_EQ(jsonDocuments.front(), "{}\n");
  }

  TEST_F(ResourceParserTest, jsonDocumentsWithNamespace) {
    String json("{ \"items\": [ {}, {} ] }");
    SpecParser::JSONDocuments jsonDocuments;

    ASSERT_NO_THROW({
      jsonDocuments = parser_.jsonDocuments(json, "items");
    });

    ASSERT_EQ(jsonDocuments.size(), 2);
    ASSERT_EQ(jsonDocuments.front(), "{}\n");
  }

  TEST_F(ResourceParserTest, parseResource) {
    String json = loadFixture("random_document.json");
    SpecResource* resource;

    ASSERT_NO_THROW({
      resource = parser_.parseResource<SpecResource>(json);
    });

    ASSERT_TRUE(resource);
    ASSERT_EQ(resource->id(), 5);

    delete resource;
  }

  TEST_F(ResourceParserTest, parseResources) {
    String json = loadFixture("random_documents.json");
    std::vector<SpecResource*> resources;

    ASSERT_NO_THROW({
      resources = parser_.parseResources<SpecResource>(json);
    });

    ASSERT_EQ(resources.size(), 2);
    ASSERT_EQ(resources.at(0)->id(), 1);
    ASSERT_EQ(resources.at(1)->id(), 2);

    std::for_each(resources.begin(), resources.end(), [](Resource* r) {
      delete r;
    });

    resources.clear();
  }

  TEST_F(ResourceParserTest, parseResourcesWithCallback) {
    String json = loadFixture("random_documents.json");
    std::vector<SpecResource*> resources;
    int nrCalls = 0;

    resources = parser_.parseResources<SpecResource>(json,
      [&nrCalls](SpecResource* resource) {
        ++nrCalls;
      });

    ASSERT_EQ(nrCalls, 2);

    std::for_each(resources.begin(), resources.end(), [](Resource* r) {
      delete r;
    });

    resources.clear();
  }
} // namespace cnvs

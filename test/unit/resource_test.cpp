#include <gtest/gtest.h>
#include "canvas/resource_parser.hpp"
#include "test_helper.hpp"

namespace Canvas {

  class SpecResource : public Resource {
  public:
    inline SpecResource() : Resource() {}
    inline SpecResource(int id) : Resource(id) {}
    inline virtual ~SpecResource() {}

    virtual void deserialize(const String& document) {
      Resource::deserialize(document);
    }
    inline virtual void deserialize(JSONValue& root) {
      mId = root.get("id", 0).asUInt();
    }
  };

  TEST(ResourceTest, setUserData) {
    SpecResource resource;

    resource.setUserData<SpecResource>("Resource", &resource);

    ASSERT_NE(resource.userData<SpecResource>("Resource"), nullptr);
    ASSERT_EQ(resource.userData<SpecResource>("Resource"), &resource);
  }

} // namespace cnvs

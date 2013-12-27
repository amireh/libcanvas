#include "canvas/resource.hpp"

namespace Canvas {

  Resource::~Resource() {
    mUserData.clear();
  }

  void Resource::deserialize(const String& json) {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    setDocument(root);
    deserialize(root);
  }

  JSONValue const& Resource::document() const {
    return mDocument;
  }
}
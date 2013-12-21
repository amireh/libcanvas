#include "canvas/resource.hpp"

namespace Canvas {

  void Resource::deserialize(const String& json) {
    Json::Value root;
    Json::Reader reader;

    if (!reader.parse( json, root )) {
      throw JSONParserError(reader.getFormattedErrorMessages());
    }

    setDocument(root);
    deserialize(root);
  }

  void Resource::deserialize(JSONValue&) {
  }
}
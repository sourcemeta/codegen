#include <gtest/gtest.h>

#include <sourcemeta/codegen/ir_group.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#define EXPECT_GROUP(instance_location, expected_size)                         \
  {                                                                            \
    const sourcemeta::core::PointerTemplate key{                               \
        sourcemeta::core::to_pointer((instance_location))};                    \
    EXPECT_TRUE(result.contains(key));                                         \
    EXPECT_EQ(result.at(key).locations.size(), (expected_size));               \
  }

#define EXPECT_GROUP_ENTRY(instance_location, index, schema_location)          \
  {                                                                            \
    const sourcemeta::core::PointerTemplate key{                               \
        sourcemeta::core::to_pointer((instance_location))};                    \
    const auto expected_pointer{                                               \
        sourcemeta::core::to_pointer((schema_location))};                      \
    EXPECT_EQ(result.at(key).locations.at((index)).location.get().pointer,     \
              expected_pointer);                                               \
  }

TEST(IRGroup, simple_string_schema) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Instances};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  const auto result{sourcemeta::codegen::group(frame)};

  EXPECT_EQ(result.size(), 1);

  EXPECT_GROUP("", 1);
  EXPECT_GROUP_ENTRY("", 0, "");
}

TEST(IRGroup, object_with_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Instances};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  const auto result{sourcemeta::codegen::group(frame)};

  EXPECT_EQ(result.size(), 2);

  EXPECT_GROUP("", 1);
  EXPECT_GROUP("/foo", 1);

  EXPECT_GROUP_ENTRY("", 0, "");
  EXPECT_GROUP_ENTRY("/foo", 0, "/properties/foo");
}

TEST(IRGroup, object_with_multiple_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" },
      "age": { "type": "integer" }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Instances};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  const auto result{sourcemeta::codegen::group(frame)};

  EXPECT_EQ(result.size(), 3);

  EXPECT_GROUP("", 1);
  EXPECT_GROUP("/name", 1);
  EXPECT_GROUP("/age", 1);

  EXPECT_GROUP_ENTRY("", 0, "");
  EXPECT_GROUP_ENTRY("/name", 0, "/properties/name");
  EXPECT_GROUP_ENTRY("/age", 0, "/properties/age");
}

TEST(IRGroup, nested_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "address": {
        "type": "object",
        "properties": {
          "city": { "type": "string" }
        }
      }
    }
  })JSON")};

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Instances};
  frame.analyse(schema, sourcemeta::core::schema_walker,
                sourcemeta::core::schema_resolver);

  const auto result{sourcemeta::codegen::group(frame)};

  EXPECT_EQ(result.size(), 3);

  EXPECT_GROUP("", 1);
  EXPECT_GROUP("/address", 1);
  EXPECT_GROUP("/address/city", 1);

  EXPECT_GROUP_ENTRY("", 0, "");
  EXPECT_GROUP_ENTRY("/address", 0, "/properties/address");
  EXPECT_GROUP_ENTRY("/address/city", 0, "/properties/address/properties/city");
}

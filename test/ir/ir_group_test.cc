#include <gtest/gtest.h>

#include <sourcemeta/codegen/ir_group.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

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
  EXPECT_TRUE(result.contains(sourcemeta::core::PointerTemplate{}));

  const auto &entries{result.at(sourcemeta::core::PointerTemplate{})};
  EXPECT_EQ(entries.size(), 1);
  EXPECT_TRUE(entries.at(0).instance_location.get().empty());
  EXPECT_TRUE(entries.at(0).location.get().pointer.empty());
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

  const sourcemeta::core::PointerTemplate foo_template{
      sourcemeta::core::Pointer{"foo"}};
  EXPECT_TRUE(result.contains(sourcemeta::core::PointerTemplate{}));
  EXPECT_TRUE(result.contains(foo_template));

  const auto &root_entries{result.at(sourcemeta::core::PointerTemplate{})};
  EXPECT_EQ(root_entries.size(), 1);
  EXPECT_TRUE(root_entries.at(0).location.get().pointer.empty());

  const auto &foo_entries{result.at(foo_template)};
  EXPECT_EQ(foo_entries.size(), 1);
  const sourcemeta::core::Pointer expected_foo_pointer{"properties", "foo"};
  EXPECT_EQ(foo_entries.at(0).location.get().pointer, expected_foo_pointer);
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

  const sourcemeta::core::PointerTemplate name_template{
      sourcemeta::core::Pointer{"name"}};
  const sourcemeta::core::PointerTemplate age_template{
      sourcemeta::core::Pointer{"age"}};
  EXPECT_TRUE(result.contains(sourcemeta::core::PointerTemplate{}));
  EXPECT_TRUE(result.contains(name_template));
  EXPECT_TRUE(result.contains(age_template));

  const auto &root_entries{result.at(sourcemeta::core::PointerTemplate{})};
  EXPECT_EQ(root_entries.size(), 1);
  EXPECT_TRUE(root_entries.at(0).location.get().pointer.empty());

  const auto &name_entries{result.at(name_template)};
  EXPECT_EQ(name_entries.size(), 1);
  const sourcemeta::core::Pointer expected_name_pointer{"properties", "name"};
  EXPECT_EQ(name_entries.at(0).location.get().pointer, expected_name_pointer);

  const auto &age_entries{result.at(age_template)};
  EXPECT_EQ(age_entries.size(), 1);
  const sourcemeta::core::Pointer expected_age_pointer{"properties", "age"};
  EXPECT_EQ(age_entries.at(0).location.get().pointer, expected_age_pointer);
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

  const sourcemeta::core::PointerTemplate address_template{
      sourcemeta::core::Pointer{"address"}};
  const sourcemeta::core::PointerTemplate city_template{
      sourcemeta::core::Pointer{"address", "city"}};
  EXPECT_TRUE(result.contains(sourcemeta::core::PointerTemplate{}));
  EXPECT_TRUE(result.contains(address_template));
  EXPECT_TRUE(result.contains(city_template));

  const auto &root_entries{result.at(sourcemeta::core::PointerTemplate{})};
  EXPECT_EQ(root_entries.size(), 1);
  EXPECT_TRUE(root_entries.at(0).location.get().pointer.empty());

  const auto &address_entries{result.at(address_template)};
  EXPECT_EQ(address_entries.size(), 1);
  const sourcemeta::core::Pointer expected_address_pointer{"properties",
                                                           "address"};
  EXPECT_EQ(address_entries.at(0).location.get().pointer,
            expected_address_pointer);

  const auto &city_entries{result.at(city_template)};
  EXPECT_EQ(city_entries.size(), 1);
  const sourcemeta::core::Pointer expected_city_pointer{"properties", "address",
                                                        "properties", "city"};
  EXPECT_EQ(city_entries.at(0).location.get().pointer, expected_city_pointer);
}

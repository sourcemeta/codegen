#include <gtest/gtest.h>

#include <sourcemeta/codegen/ir.h>

#include "ir_test_utils.h"

TEST(IR_2020_12, test_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, String, "");
}

TEST(IR_2020_12, test_2) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": {
        "type": "string"
      }
    }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.at(0).first, "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).additional.has_value());
}

TEST(IR_2020_12, test_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Integer, "");
}

TEST(IR_2020_12, test_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Number, "");
}

TEST(IR_2020_12, test_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "maximum": 100,
    "multipleOf": 5
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Integer, "");
}

TEST(IR_2020_12, test_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMinimum": 0,
    "exclusiveMaximum": 1.5,
    "multipleOf": 0.1
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Number, "");
}

TEST(IR_2020_12, enum_null) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Null, "");
}

TEST(IR_2020_12, enum_boolean_true_false) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Boolean, "");
}

TEST(IR_2020_12, enum_boolean_false_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Boolean, "");
}

TEST(IR_2020_12, enum_string_values) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar", "baz" ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 3);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_string(),
            "foo");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(1).to_string(),
            "bar");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(2).to_string(),
            "baz");
}

TEST(IR_2020_12, const_null) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": null
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Null, "");
}

TEST(IR_2020_12, const_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "hello"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_string(),
            "hello");
}

TEST(IR_2020_12, const_integer) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 42
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_integer(),
            42);
}

TEST(IR_2020_12, const_boolean_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": true
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_TRUE(std::get<IREnumeration>(result.at(0)).values.at(0).to_boolean());
}

TEST(IR_2020_12, object_type_only) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).pointer, "");
  EXPECT_TRUE(std::get<IRObject>(result.at(0)).members.empty());
  EXPECT_FALSE(std::get<IRObject>(result.at(0)).additional.has_value());
}

TEST(IR_2020_12, object_empty_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {}
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).pointer, "");
  EXPECT_TRUE(std::get<IRObject>(result.at(0)).members.empty());
  EXPECT_FALSE(std::get<IRObject>(result.at(0)).additional.has_value());
}

TEST(IR_2020_12, object_with_additional_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    },
    "additionalProperties": { "type": "integer" }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo");
  EXPECT_IR_SCALAR(result, 1, Integer, "/additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.at(0).first == "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at(0).second.pointer,
      "/properties/foo");

  EXPECT_TRUE(std::get<IRObject>(result.at(2)).additional.has_value());
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).additional->pointer,
                   "/additionalProperties");
}

TEST(IR_2020_12, object_with_impossible_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": false
    }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_IMPOSSIBLE(result, 0, "/properties/foo");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).first == "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).additional.has_value());
}

TEST(IR_2020_12, object_with_impossible_additional_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": { "type": "string" }
    },
    "additionalProperties": false
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo");

  EXPECT_IR_IMPOSSIBLE(result, 1, "/additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.at(0).first == "foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at(0).second.pointer,
      "/properties/foo");

  EXPECT_TRUE(std::get<IRObject>(result.at(2)).additional.has_value());
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).additional->pointer,
                   "/additionalProperties");
}

TEST(IR_2020_12, array_with_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, String, "/items");

  EXPECT_IR_ARRAY(result, 1, "", "/items");
}

TEST(IR_2020_12, array_nested_in_object) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "tags": {
        "type": "array",
        "items": { "type": "string" }
      }
    }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/tags/items");

  EXPECT_IR_ARRAY(result, 1, "/properties/tags", "/properties/tags/items");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
}

TEST(IR_2020_12, tuple_with_prefix_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, Integer, "/prefixItems/1");
  EXPECT_IR_SCALAR(result, 1, String, "/prefixItems/0");

  EXPECT_TRUE(std::holds_alternative<IRTuple>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).pointer, "");
  EXPECT_EQ(std::get<IRTuple>(result.at(2)).items.size(), 2);
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).items.at(0).pointer,
                   "/prefixItems/0");
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).items.at(1).pointer,
                   "/prefixItems/1");
  EXPECT_FALSE(std::get<IRTuple>(result.at(2)).additional.has_value());
}

TEST(IR_2020_12, tuple_with_prefix_items_and_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "prefixItems": [
      { "type": "string" }
    ],
    "items": { "type": "boolean" }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/prefixItems/0");
  EXPECT_IR_SCALAR(result, 1, Boolean, "/items");

  EXPECT_TRUE(std::holds_alternative<IRTuple>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).pointer, "");
  EXPECT_EQ(std::get<IRTuple>(result.at(2)).items.size(), 1);
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).items.at(0).pointer,
                   "/prefixItems/0");
  EXPECT_TRUE(std::get<IRTuple>(result.at(2)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).additional->pointer,
                   "/items");
}

TEST(IR_2020_12, anyof_two_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, Integer, "/anyOf/1");
  EXPECT_IR_SCALAR(result, 1, String, "/anyOf/0");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).pointer, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(2)).values.size(), 2);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(1).pointer,
                   "/anyOf/1");
}

TEST(IR_2020_12, anyof_three_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" },
      { "type": "boolean" }
    ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 4);

  EXPECT_IR_SCALAR(result, 0, Boolean, "/anyOf/2");
  EXPECT_IR_SCALAR(result, 1, Integer, "/anyOf/1");
  EXPECT_IR_SCALAR(result, 2, String, "/anyOf/0");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(3)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).pointer, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(3)).values.size(), 3);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(1).pointer,
                   "/anyOf/1");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(2).pointer,
                   "/anyOf/2");
}

TEST(IR_2020_12, ref_recursive_to_root) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "child": { "$ref": "#" }
    }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_REFERENCE(result, 0, "/properties/child", "");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).first == "child");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/child");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).additional.has_value());
}

TEST(IR_2020_12, nested_object_with_required_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "nested": {
        "type": "object",
        "properties": {
          "name": { "type": "string" }
        },
        "required": [ "name" ]
      }
    }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/nested/properties/name");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer,
                   "/properties/nested");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).first == "name");
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at(0).second.pointer,
      "/properties/nested/properties/name");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).additional.has_value());

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.at(0).first == "nested");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at(0).second.pointer,
      "/properties/nested");
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional.has_value());
}

TEST(IR_2020_12, array_without_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "minItems": 0
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRArray>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRArray>(result.at(0)).pointer, "");
  EXPECT_FALSE(std::get<IRArray>(result.at(0)).items.has_value());
}

TEST(IR_2020_12, object_with_additional_properties_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "name": { "type": "string" }
    },
    "additionalProperties": true
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 9);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/name");
  EXPECT_IR_SCALAR(result, 1, Number, "/additionalProperties/anyOf/5");
  EXPECT_IR_SCALAR(result, 2, String, "/additionalProperties/anyOf/4");

  EXPECT_TRUE(std::holds_alternative<IRArray>(result.at(3)));
  EXPECT_AS_STRING(std::get<IRArray>(result.at(3)).pointer,
                   "/additionalProperties/anyOf/3");
  EXPECT_FALSE(std::get<IRArray>(result.at(3)).items.has_value());

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(4)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(4)).pointer,
                   "/additionalProperties/anyOf/2");
  EXPECT_EQ(std::get<IRObject>(result.at(4)).members.size(), 0);
  EXPECT_FALSE(std::get<IRObject>(result.at(4)).additional.has_value());

  EXPECT_IR_SCALAR(result, 5, Boolean, "/additionalProperties/anyOf/1");
  EXPECT_IR_SCALAR(result, 6, Null, "/additionalProperties/anyOf/0");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(7)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(7)).pointer,
                   "/additionalProperties");
  EXPECT_EQ(std::get<IRUnion>(result.at(7)).values.size(), 6);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(7)).values.at(0).pointer,
                   "/additionalProperties/anyOf/0");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(7)).values.at(1).pointer,
                   "/additionalProperties/anyOf/1");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(7)).values.at(2).pointer,
                   "/additionalProperties/anyOf/2");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(7)).values.at(3).pointer,
                   "/additionalProperties/anyOf/3");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(7)).values.at(4).pointer,
                   "/additionalProperties/anyOf/4");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(7)).values.at(5).pointer,
                   "/additionalProperties/anyOf/5");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(8)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(8)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(8)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(8)).members.at(0).first == "name");
  EXPECT_FALSE(std::get<IRObject>(result.at(8)).members.at(0).second.required);
  EXPECT_FALSE(std::get<IRObject>(result.at(8)).members.at(0).second.immutable);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(8)).members.at(0).second.pointer,
      "/properties/name");
  EXPECT_TRUE(std::get<IRObject>(result.at(8)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRObject>(result.at(8)).additional->pointer,
                   "/additionalProperties");
}

TEST(IR_2020_12, object_only_additional_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "additionalProperties": { "type": "boolean" }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, Boolean, "/additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 0);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).additional->pointer,
                   "/additionalProperties");
}

TEST(IR_2020_12, embedded_resource_with_nested_id_no_duplicates) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "$id": "https://example.com/main",
    "type": "object",
    "required": [ "item" ],
    "properties": {
      "item": { "$ref": "https://example.com/item" }
    },
    "additionalProperties": false,
    "$defs": {
      "Item": {
        "$id": "https://example.com/item",
        "type": "object",
        "required": [ "name" ],
        "properties": {
          "name": { "type": "string" }
        },
        "additionalProperties": false
      }
    }
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 6);

  EXPECT_IR_REFERENCE(result, 0, "/properties/item", "/$defs/Item");

  EXPECT_IR_IMPOSSIBLE(result, 1, "/additionalProperties");

  EXPECT_IR_SCALAR(result, 2, String, "/$defs/Item/properties/name");

  EXPECT_IR_IMPOSSIBLE(result, 3, "/$defs/Item/additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(4)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(4)).pointer, "/$defs/Item");
  EXPECT_EQ(std::get<IRObject>(result.at(4)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(4)).members.at(0).first, "name");
  EXPECT_TRUE(std::get<IRObject>(result.at(4)).members.at(0).second.required);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(4)).members.at(0).second.pointer,
      "/$defs/Item/properties/name");
  EXPECT_TRUE(std::get<IRObject>(result.at(4)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRObject>(result.at(4)).additional->pointer,
                   "/$defs/Item/additionalProperties");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(5)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(5)).pointer, "");
  EXPECT_EQ(std::get<IRObject>(result.at(5)).members.size(), 1);
  EXPECT_EQ(std::get<IRObject>(result.at(5)).members.at(0).first, "item");
  EXPECT_TRUE(std::get<IRObject>(result.at(5)).members.at(0).second.required);
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(5)).members.at(0).second.pointer,
      "/properties/item");
  EXPECT_TRUE(std::get<IRObject>(result.at(5)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRObject>(result.at(5)).additional->pointer,
                   "/additionalProperties");
}

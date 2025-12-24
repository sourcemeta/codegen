#include <gtest/gtest.h>

#include <sourcemeta/codegen/ir.h>

#include "ir_test_utils.h"

TEST(IR_2020_12, test_1) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string"
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, String, "", "");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo", "/foo");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).instance_location, "");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.contains("foo"));
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).members.at("foo").pointer,
                   "/properties/foo");
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at("foo").instance_location,
      "/foo");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).additional.has_value());
}

TEST(IR_2020_12, test_3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer"
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Integer, "", "");
}

TEST(IR_2020_12, test_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Number, "", "");
}

TEST(IR_2020_12, test_5) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "integer",
    "minimum": 0,
    "maximum": 100,
    "multipleOf": 5
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Integer, "", "");
}

TEST(IR_2020_12, test_6) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number",
    "exclusiveMinimum": 0,
    "exclusiveMaximum": 1.5,
    "multipleOf": 0.1
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Number, "", "");
}

TEST(IR_2020_12, enum_null) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Null, "", "");
}

TEST(IR_2020_12, enum_boolean_true_false) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ]
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Boolean, "", "");
}

TEST(IR_2020_12, enum_boolean_false_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Boolean, "", "");
}

TEST(IR_2020_12, enum_string_values) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar", "baz" ]
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).instance_location, "");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_IR_SCALAR(result, 0, Null, "", "");
}

TEST(IR_2020_12, const_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "hello"
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_string(),
            "hello");
}

TEST(IR_2020_12, const_integer) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 42
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.at(0).to_integer(),
            42);
}

TEST(IR_2020_12, const_boolean_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": true
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IREnumeration>(result.at(0)));
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IREnumeration>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IREnumeration>(result.at(0)).values.size(), 1);
  EXPECT_TRUE(std::get<IREnumeration>(result.at(0)).values.at(0).to_boolean());
}

TEST(IR_2020_12, object_type_only) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).instance_location, "");
  EXPECT_TRUE(std::get<IRObject>(result.at(0)).members.empty());
  EXPECT_FALSE(std::get<IRObject>(result.at(0)).additional.has_value());
}

TEST(IR_2020_12, object_empty_properties) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {}
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(0)).instance_location, "");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo", "/foo");
  EXPECT_IR_SCALAR(result, 1, Integer, "/additionalProperties",
                   "/~?additionalProperties~/~P~");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).instance_location, "");
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.contains("foo"));
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at("foo").required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at("foo").immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).members.at("foo").pointer,
                   "/properties/foo");
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at("foo").instance_location,
      "/foo");

  EXPECT_TRUE(std::get<IRObject>(result.at(2)).additional.has_value());
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).additional->pointer,
                   "/additionalProperties");
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).additional->instance_location,
      "/~?additionalProperties~/~P~");
}

TEST(IR_2020_12, object_with_impossible_property) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "foo": false
    }
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_IMPOSSIBLE(result, 0, "/properties/foo", "/foo");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).instance_location, "");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.contains("foo"));
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).members.at("foo").pointer,
                   "/properties/foo");
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at("foo").instance_location,
      "/foo");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/foo", "/foo");

  EXPECT_IR_IMPOSSIBLE(result, 1, "/additionalProperties",
                       "/~?additionalProperties~/~P~");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).instance_location, "");
  EXPECT_EQ(std::get<IRObject>(result.at(2)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(2)).members.contains("foo"));
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at("foo").required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).members.at("foo").immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).members.at("foo").pointer,
                   "/properties/foo");
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).members.at("foo").instance_location,
      "/foo");

  EXPECT_TRUE(std::get<IRObject>(result.at(2)).additional.has_value());
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->required);
  EXPECT_FALSE(std::get<IRObject>(result.at(2)).additional->immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).additional->pointer,
                   "/additionalProperties");
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(2)).additional->instance_location,
      "/~?additionalProperties~/~P~");
}

TEST(IR_2020_12, array_with_items) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "array",
    "items": { "type": "string" }
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_SCALAR(result, 0, String, "/items", "/~?items~/~I~");

  EXPECT_IR_ARRAY(result, 1, "", "", "/items", "/~?items~/~I~");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/properties/tags/items",
                   "/tags/~?items~/~I~");

  EXPECT_IR_ARRAY(result, 1, "/properties/tags", "/tags",
                  "/properties/tags/items", "/tags/~?items~/~I~");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(2)).instance_location, "");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, Integer, "/prefixItems/1", "/1");
  EXPECT_IR_SCALAR(result, 1, String, "/prefixItems/0", "/0");

  EXPECT_TRUE(std::holds_alternative<IRTuple>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).pointer, "");
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).instance_location, "");
  EXPECT_EQ(std::get<IRTuple>(result.at(2)).items.size(), 2);
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).items.at(0).pointer,
                   "/prefixItems/0");
  EXPECT_AS_STRING(
      std::get<IRTuple>(result.at(2)).items.at(0).instance_location,
      "/~?prefixItems~/0");
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).items.at(1).pointer,
                   "/prefixItems/1");
  EXPECT_AS_STRING(
      std::get<IRTuple>(result.at(2)).items.at(1).instance_location,
      "/~?prefixItems~/1");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/prefixItems/0", "/0");
  EXPECT_IR_SCALAR(result, 1, Boolean, "/items", "/~?items~/~I~");

  EXPECT_TRUE(std::holds_alternative<IRTuple>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).pointer, "");
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).instance_location, "");
  EXPECT_EQ(std::get<IRTuple>(result.at(2)).items.size(), 1);
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).items.at(0).pointer,
                   "/prefixItems/0");
  EXPECT_AS_STRING(
      std::get<IRTuple>(result.at(2)).items.at(0).instance_location,
      "/~?prefixItems~/0");
  EXPECT_TRUE(std::get<IRTuple>(result.at(2)).additional.has_value());
  EXPECT_AS_STRING(std::get<IRTuple>(result.at(2)).additional->pointer,
                   "/items");
  EXPECT_AS_STRING(
      std::get<IRTuple>(result.at(2)).additional->instance_location,
      "/~?items~/~I~");
}

TEST(IR_2020_12, anyof_two_branches) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "anyOf": [
      { "type": "string" },
      { "type": "integer" }
    ]
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_IR_SCALAR(result, 0, String, "/anyOf/0", "/~?anyOf~/~?0~");
  EXPECT_IR_SCALAR(result, 1, Integer, "/anyOf/1", "/~?anyOf~/~?1~");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(2)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).pointer, "");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).instance_location, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(2)).values.size(), 2);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_AS_STRING(
      std::get<IRUnion>(result.at(2)).values.at(0).instance_location,
      "/~?anyOf~/~?0~");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(2)).values.at(1).pointer,
                   "/anyOf/1");
  EXPECT_AS_STRING(
      std::get<IRUnion>(result.at(2)).values.at(1).instance_location,
      "/~?anyOf~/~?1~");
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

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 4);

  EXPECT_IR_SCALAR(result, 0, String, "/anyOf/0", "/~?anyOf~/~?0~");
  EXPECT_IR_SCALAR(result, 1, Integer, "/anyOf/1", "/~?anyOf~/~?1~");
  EXPECT_IR_SCALAR(result, 2, Boolean, "/anyOf/2", "/~?anyOf~/~?2~");

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(3)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).pointer, "");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).instance_location, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(3)).values.size(), 3);
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(0).pointer,
                   "/anyOf/0");
  EXPECT_AS_STRING(
      std::get<IRUnion>(result.at(3)).values.at(0).instance_location,
      "/~?anyOf~/~?0~");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(1).pointer,
                   "/anyOf/1");
  EXPECT_AS_STRING(
      std::get<IRUnion>(result.at(3)).values.at(1).instance_location,
      "/~?anyOf~/~?1~");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(3)).values.at(2).pointer,
                   "/anyOf/2");
  EXPECT_AS_STRING(
      std::get<IRUnion>(result.at(3)).values.at(2).instance_location,
      "/~?anyOf~/~?2~");
}

TEST(IR_2020_12, ref_recursive_to_root) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "child": { "$ref": "#" }
    }
  })JSON")};

  const auto result{sourcemeta::codegen::compile(
      schema, sourcemeta::core::schema_walker,
      sourcemeta::core::schema_resolver, sourcemeta::codegen::default_compiler,
      [](const auto &, const auto, const auto, const auto &) {})};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_IR_REFERENCE(result, 0, "/properties/child", "/child", "", "");

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).pointer, "");
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).instance_location, "");
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.contains("child"));
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("child").required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("child").immutable);
  EXPECT_AS_STRING(std::get<IRObject>(result.at(1)).members.at("child").pointer,
                   "/properties/child");
  EXPECT_AS_STRING(
      std::get<IRObject>(result.at(1)).members.at("child").instance_location,
      "/child");
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).additional.has_value());
}

TEST(IR_2020_12, invalid_property_name) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object",
    "properties": {
      "$!@": { "type": "string" }
    }
  })JSON")};

  struct CallbackEntry {
    sourcemeta::core::Pointer pointer;
    std::string rule_name;
    std::string message;
    bool applies;
    std::vector<sourcemeta::core::Pointer> locations;
    std::optional<std::string> description;
  };

  std::vector<CallbackEntry> callback_entries;

  EXPECT_THROW(
      {
        sourcemeta::codegen::compile(
            schema, sourcemeta::core::schema_walker,
            sourcemeta::core::schema_resolver,
            sourcemeta::codegen::default_compiler,
            [&callback_entries](const sourcemeta::core::Pointer &pointer,
                                const std::string_view rule_name,
                                const std::string_view message,
                                const auto &result) {
              CallbackEntry entry;
              entry.pointer = pointer;
              entry.rule_name = std::string{rule_name};
              entry.message = std::string{message};
              entry.applies = result.applies;
              entry.locations = result.locations;
              entry.description = result.description;
              callback_entries.push_back(std::move(entry));
            });
      },
      sourcemeta::codegen::NonCanonicalizableError);

  EXPECT_EQ(callback_entries.size(), 3);

  // TODO: Why is this emitted 3 times?

  EXPECT_AS_STRING(callback_entries.at(0).pointer, "");
  EXPECT_EQ(callback_entries.at(0).rule_name, "simple_properties_identifiers");
  EXPECT_EQ(callback_entries.at(0).message,
            "Set `properties` to identifier names that can be easily mapped to "
            "programming languages (matching [A-Za-z_][A-Za-z0-9_]*)");
  EXPECT_TRUE(callback_entries.at(0).applies);
  EXPECT_EQ(callback_entries.at(0).locations.size(), 1);
  EXPECT_AS_STRING(callback_entries.at(0).locations.at(0), "/properties/$!@");
  EXPECT_FALSE(callback_entries.at(0).description.has_value());

  EXPECT_AS_STRING(callback_entries.at(1).pointer, "");
  EXPECT_EQ(callback_entries.at(1).rule_name, "simple_properties_identifiers");
  EXPECT_EQ(callback_entries.at(1).message,
            "Set `properties` to identifier names that can be easily mapped to "
            "programming languages (matching [A-Za-z_][A-Za-z0-9_]*)");
  EXPECT_TRUE(callback_entries.at(1).applies);
  EXPECT_EQ(callback_entries.at(1).locations.size(), 1);
  EXPECT_AS_STRING(callback_entries.at(1).locations.at(0), "/properties/$!@");
  EXPECT_FALSE(callback_entries.at(1).description.has_value());

  EXPECT_AS_STRING(callback_entries.at(2).pointer, "");
  EXPECT_EQ(callback_entries.at(2).rule_name, "simple_properties_identifiers");
  EXPECT_EQ(callback_entries.at(2).message,
            "Set `properties` to identifier names that can be easily mapped to "
            "programming languages (matching [A-Za-z_][A-Za-z0-9_]*)");
  EXPECT_TRUE(callback_entries.at(2).applies);
  EXPECT_EQ(callback_entries.at(2).locations.size(), 1);
  EXPECT_AS_STRING(callback_entries.at(2).locations.at(0), "/properties/$!@");
  EXPECT_FALSE(callback_entries.at(2).description.has_value());
}

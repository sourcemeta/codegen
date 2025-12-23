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
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::String);
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
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "/properties/foo");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "/foo");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::String);

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

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Integer);
}

TEST(IR_2020_12, test_4) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "number"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Number);
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
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Integer);
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
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Number);
}

TEST(IR_2020_12, enum_null) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ null ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Null);
}

TEST(IR_2020_12, enum_boolean_true_false) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ true, false ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Boolean);
}

TEST(IR_2020_12, enum_boolean_false_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ false, true ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Boolean);
}

TEST(IR_2020_12, enum_string_values) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "enum": [ "foo", "bar", "baz" ]
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 3);
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(0).to_string(), "foo");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(1).to_string(), "bar");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(2).to_string(), "baz");
}

TEST(IR_2020_12, const_null) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": null
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Null);
}

TEST(IR_2020_12, const_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": "hello"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(0).to_string(), "hello");
}

TEST(IR_2020_12, const_integer) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": 42
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(0).to_integer(), 42);
}

TEST(IR_2020_12, const_boolean_true) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "const": true
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 1);

  EXPECT_TRUE(std::holds_alternative<IRUnion>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).pointer, "");
  EXPECT_AS_STRING(std::get<IRUnion>(result.at(0)).instance_location, "");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 1);
  EXPECT_TRUE(std::get<IRUnion>(result.at(0)).values.at(0).to_boolean());
}

TEST(IR_2020_12, object_type_only) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "object"
  })JSON")};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

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

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

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

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "/properties/foo");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "/foo");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::String);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(1)).pointer,
                   "/additionalProperties");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(1)).instance_location,
                   "/~?additionalProperties~/~P~");
  EXPECT_EQ(std::get<IRScalar>(result.at(1)).value, IRScalarType::Integer);

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

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 2);

  EXPECT_TRUE(std::holds_alternative<IRImpossible>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRImpossible>(result.at(0)).pointer,
                   "/properties/foo");
  EXPECT_AS_STRING(std::get<IRImpossible>(result.at(0)).instance_location,
                   "/foo");

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

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver)};

  using namespace sourcemeta::codegen;

  EXPECT_EQ(result.size(), 3);

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).pointer, "/properties/foo");
  EXPECT_AS_STRING(std::get<IRScalar>(result.at(0)).instance_location, "/foo");
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::String);

  EXPECT_TRUE(std::holds_alternative<IRImpossible>(result.at(1)));
  EXPECT_AS_STRING(std::get<IRImpossible>(result.at(1)).pointer,
                   "/additionalProperties");
  EXPECT_AS_STRING(std::get<IRImpossible>(result.at(1)).instance_location,
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

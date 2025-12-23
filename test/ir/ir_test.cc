#include <gtest/gtest.h>

#include <sourcemeta/codegen/ir.h>

TEST(IR, test_1) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::String);
}

TEST(IR, test_2) {
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

  const sourcemeta::core::PointerTemplate foo_pointer{
      sourcemeta::core::to_pointer("/foo")};

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).instance_location, foo_pointer);
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::String);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).instance_location.empty());
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.contains("foo"));
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").immutable);
  EXPECT_EQ(
      std::get<IRObject>(result.at(1)).members.at("foo").instance_location,
      foo_pointer);
}

TEST(IR, test_3) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Integer);
}

TEST(IR, test_4) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Number);
}

TEST(IR, test_5) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Integer);
}

TEST(IR, test_6) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Number);
}

TEST(IR, enum_null) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Null);
}

TEST(IR, enum_boolean_true_false) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Boolean);
}

TEST(IR, enum_boolean_false_true) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Boolean);
}

TEST(IR, enum_string_values) {
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
  EXPECT_TRUE(std::get<IRUnion>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 3);
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(0).to_string(), "foo");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(1).to_string(), "bar");
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(2).to_string(), "baz");
}

TEST(IR, const_null) {
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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::Null);
}

TEST(IR, const_string) {
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
  EXPECT_TRUE(std::get<IRUnion>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(0).to_string(), "hello");
}

TEST(IR, const_integer) {
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
  EXPECT_TRUE(std::get<IRUnion>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 1);
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.at(0).to_integer(), 42);
}

TEST(IR, const_boolean_true) {
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
  EXPECT_TRUE(std::get<IRUnion>(result.at(0)).instance_location.empty());
  EXPECT_EQ(std::get<IRUnion>(result.at(0)).values.size(), 1);
  EXPECT_TRUE(std::get<IRUnion>(result.at(0)).values.at(0).to_boolean());
}

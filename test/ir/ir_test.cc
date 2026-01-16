#include <gtest/gtest.h>

#include <sourcemeta/codegen/ir.h>
#include <sourcemeta/core/jsonschema.h>

TEST(IR, unsupported_dialect_draft3) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "http://json-schema.org/draft-03/schema#",
    "type": "string"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler),
      sourcemeta::core::SchemaVocabularyError);
}

TEST(IR, unsupported_keyword_error) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "string",
    "if": { "minLength": 5 },
    "then": { "maxLength": 10 }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler),
      sourcemeta::codegen::UnsupportedKeywordError);
}

TEST(IR, unsupported_keyword_value_error_type_not_string) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": 123
  })JSON")};

  EXPECT_THROW(
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler),
      sourcemeta::codegen::UnsupportedKeywordValueError);
}

TEST(IR, unsupported_keyword_value_error_unknown_type) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "type": "foo"
  })JSON")};

  EXPECT_THROW(
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler),
      sourcemeta::codegen::UnsupportedKeywordValueError);
}

TEST(IR, unexpected_schema_error_unsupported_shape) {
  const sourcemeta::core::JSON schema{sourcemeta::core::parse_json(R"JSON({
    "$schema": "https://json-schema.org/draft/2020-12/schema",
    "not": { "type": "string" }
  })JSON")};

  EXPECT_THROW(
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler),
      sourcemeta::codegen::UnexpectedSchemaError);
}

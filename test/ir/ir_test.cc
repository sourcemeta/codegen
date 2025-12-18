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
  EXPECT_TRUE(std::get<IRScalar>(result.at(0)).pointer.empty());
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

  EXPECT_TRUE(std::holds_alternative<IRScalar>(result.at(0)));
  EXPECT_EQ(
      std::get<IRScalar>(result.at(0)).pointer,
      sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"foo"}});
  EXPECT_EQ(std::get<IRScalar>(result.at(0)).value, IRScalarType::String);

  EXPECT_TRUE(std::holds_alternative<IRObject>(result.at(1)));
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).pointer.empty());
  EXPECT_EQ(std::get<IRObject>(result.at(1)).members.size(), 1);
  EXPECT_TRUE(std::get<IRObject>(result.at(1)).members.contains("foo"));
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").required);
  EXPECT_FALSE(std::get<IRObject>(result.at(1)).members.at("foo").immutable);
  EXPECT_EQ(
      std::get<IRObject>(result.at(1)).members.at("foo").pointer,
      sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"foo"}});
}

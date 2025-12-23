#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>

#include <sstream> // std::ostringstream

TEST(TypeScript, test_1) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(
      IRScalar{.instance_location = {}, .value = IRScalarType::String});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = string;\n");
}

TEST(TypeScript, test_2) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      .instance_location =
          sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"foo"}},
      .value = IRScalarType::String});

  IRObject object;
  object.instance_location = {};
  object.members.emplace(
      "foo",
      IRObjectValue{.required = false,
                    .immutable = false,
                    .instance_location = sourcemeta::core::PointerTemplate{
                        sourcemeta::core::Pointer{"foo"}}});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  typescript(output, result, "MyObject");

  const auto expected{R"TS(export type foo = string;

export interface MyObject {
  foo?: foo;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

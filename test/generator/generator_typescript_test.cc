#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>

#include <sstream> // std::ostringstream

TEST(Generator_typescript, scalar_string) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::String});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = string;\n");
}

TEST(Generator_typescript, scalar_number) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Number});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = number;\n");
}

TEST(Generator_typescript, scalar_integer) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Integer});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = number;\n");
}

TEST(Generator_typescript, scalar_boolean) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Boolean});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = boolean;\n");
}

TEST(Generator_typescript, scalar_null) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Null});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = null;\n");
}

TEST(Generator_typescript, object_with_optional_string_property) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {{}, sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"foo"}}},
      IRScalarType::String});

  IRObject object;
  object.instance_location = {};
  object.members.emplace("foo",
                         IRObjectValue{{{},
                                        sourcemeta::core::PointerTemplate{
                                            sourcemeta::core::Pointer{"foo"}}},
                                       false,
                                       false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  typescript(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Foo = string;

export interface MyObject {
  foo?: MyObject_Foo;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, impossible_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{{}});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = never;\n");
}

TEST(Generator_typescript, impossible_nested) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{
      {sourcemeta::core::Pointer{"foo"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"foo"}}}});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType_Foo = never;\n");
}

TEST(Generator_typescript, array_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"items"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}}},
      IRScalarType::String});

  IRArray array;
  array.pointer = {};
  array.instance_location = {};
  array.items.pointer = sourcemeta::core::Pointer{"items"};
  array.items.instance_location =
      sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}};
  result.emplace_back(std::move(array));

  std::ostringstream output;
  typescript(output, result, "MyArray");

  const auto expected{R"TS(export type MyArray_0 = string;

export type MyArray = MyArray_0[];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, array_nested_in_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "tags", "items"},
                sourcemeta::core::PointerTemplate{
                    sourcemeta::core::Pointer{"tags", "0"}}},
               IRScalarType::String});

  IRArray array;
  array.pointer = sourcemeta::core::Pointer{"properties", "tags"};
  array.instance_location =
      sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"tags"}};
  array.items.pointer =
      sourcemeta::core::Pointer{"properties", "tags", "items"};
  array.items.instance_location =
      sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"tags", "0"}};
  result.emplace_back(std::move(array));

  IRObject object;
  object.instance_location = {};
  object.members.emplace(
      "tags", IRObjectValue{{sourcemeta::core::Pointer{"properties", "tags"},
                             sourcemeta::core::PointerTemplate{
                                 sourcemeta::core::Pointer{"tags"}}},
                            false,
                            false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  typescript(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Tags_0 = string;

export type MyObject_Tags = MyObject_Tags_0[];

export interface MyObject {
  tags?: MyObject_Tags;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, tuple_without_additional) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"prefixItems", "0"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}}},
      IRScalarType::String});

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"prefixItems", "1"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"1"}}},
      IRScalarType::String});

  IRTuple tuple;
  tuple.pointer = {};
  tuple.instance_location = {};
  tuple.items.push_back(
      {sourcemeta::core::Pointer{"prefixItems", "0"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}}});
  tuple.items.push_back(
      {sourcemeta::core::Pointer{"prefixItems", "1"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"1"}}});
  result.emplace_back(std::move(tuple));

  std::ostringstream output;
  typescript(output, result, "MyTuple");

  const auto expected{R"TS(export type MyTuple_0 = string;

export type MyTuple_1 = string;

export type MyTuple = [MyTuple_0, MyTuple_1];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, tuple_with_additional) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"prefixItems", "0"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}}},
      IRScalarType::String});

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"items"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"1"}}},
      IRScalarType::String});

  IRTuple tuple;
  tuple.pointer = {};
  tuple.instance_location = {};
  tuple.items.push_back(
      {sourcemeta::core::Pointer{"prefixItems", "0"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}}});
  tuple.additional =
      IRType{sourcemeta::core::Pointer{"items"},
             sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"1"}}};
  result.emplace_back(std::move(tuple));

  std::ostringstream output;
  typescript(output, result, "MyTuple");

  const auto expected{R"TS(export type MyTuple_0 = string;

export type MyTuple_1 = string;

export type MyTuple = [MyTuple_0, ...MyTuple_1[]];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, reference_property_to_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRReference{
      {sourcemeta::core::Pointer{"properties", "child", "$ref"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"child"}}},
      {{}, sourcemeta::core::PointerTemplate{}}});

  IRObject object;
  object.pointer = {};
  object.instance_location = {};
  object.members.emplace(
      "child",
      IRObjectValue{{sourcemeta::core::Pointer{"properties", "child", "$ref"},
                     sourcemeta::core::PointerTemplate{
                         sourcemeta::core::Pointer{"child"}}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  typescript(output, result, "Node");

  const auto expected{R"TS(export type Node_Child = Node;

export interface Node {
  child?: Node_Child;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, enumeration_strings) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IREnumeration enumeration;
  enumeration.pointer = {};
  enumeration.instance_location = {};
  enumeration.values.push_back(sourcemeta::core::JSON{"foo"});
  enumeration.values.push_back(sourcemeta::core::JSON{"bar"});
  enumeration.values.push_back(sourcemeta::core::JSON{"baz"});
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  typescript(output, result, "Status");

  EXPECT_EQ(output.str(),
            "export type Status = \"foo\" | \"bar\" | \"baz\";\n");
}

TEST(Generator_typescript, enumeration_mixed_primitives) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IREnumeration enumeration;
  enumeration.pointer = {};
  enumeration.instance_location = {};
  enumeration.values.push_back(sourcemeta::core::JSON{"active"});
  enumeration.values.push_back(sourcemeta::core::JSON{42});
  enumeration.values.push_back(sourcemeta::core::JSON{true});
  enumeration.values.push_back(sourcemeta::core::JSON{nullptr});
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  typescript(output, result, "Value");

  EXPECT_EQ(output.str(),
            "export type Value = \"active\" | 42 | true | null;\n");
}

TEST(Generator_typescript, enumeration_with_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IREnumeration enumeration;
  enumeration.pointer = {};
  enumeration.instance_location = {};
  enumeration.values.push_back(sourcemeta::core::JSON{"simple"});
  enumeration.values.push_back(
      sourcemeta::core::parse_json("{\"type\":\"complex\"}"));
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  typescript(output, result, "Config");

  const auto expected{R"TS(export type Config = "simple" | {
  "type": "complex"
};
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, enumeration_with_array) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IREnumeration enumeration;
  enumeration.pointer = {};
  enumeration.instance_location = {};
  enumeration.values.push_back(sourcemeta::core::JSON{1});
  enumeration.values.push_back(sourcemeta::core::parse_json("[1,2,3]"));
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  typescript(output, result, "Data");

  EXPECT_EQ(output.str(), "export type Data = 1 | [ 1, 2, 3 ];\n");
}

TEST(Generator_typescript, union_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"anyOf", "0"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}}},
      IRScalarType::String});

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"anyOf", "1"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"1"}}},
      IRScalarType::String});

  IRUnion my_union;
  my_union.pointer = {};
  my_union.instance_location = {};
  my_union.values.push_back(
      {sourcemeta::core::Pointer{"anyOf", "0"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"0"}}});
  my_union.values.push_back(
      {sourcemeta::core::Pointer{"anyOf", "1"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"1"}}});
  result.emplace_back(std::move(my_union));

  std::ostringstream output;
  typescript(output, result, "MyUnion");

  const auto expected{R"TS(export type MyUnion_0 = string;

export type MyUnion_1 = string;

export type MyUnion = MyUnion_0 | MyUnion_1;
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, union_nested_in_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "value", "anyOf", "0"},
                sourcemeta::core::PointerTemplate{
                    sourcemeta::core::Pointer{"value", "0"}}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "value", "anyOf", "1"},
                sourcemeta::core::PointerTemplate{
                    sourcemeta::core::Pointer{"value", "1"}}},
               IRScalarType::String});

  IRUnion my_union;
  my_union.pointer = sourcemeta::core::Pointer{"properties", "value"};
  my_union.instance_location =
      sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"value"}};
  my_union.values.push_back(
      {sourcemeta::core::Pointer{"properties", "value", "anyOf", "0"},
       sourcemeta::core::PointerTemplate{
           sourcemeta::core::Pointer{"value", "0"}}});
  my_union.values.push_back(
      {sourcemeta::core::Pointer{"properties", "value", "anyOf", "1"},
       sourcemeta::core::PointerTemplate{
           sourcemeta::core::Pointer{"value", "1"}}});
  result.emplace_back(std::move(my_union));

  IRObject object;
  object.pointer = {};
  object.instance_location = {};
  object.members.emplace(
      "value", IRObjectValue{{sourcemeta::core::Pointer{"properties", "value"},
                              sourcemeta::core::PointerTemplate{
                                  sourcemeta::core::Pointer{"value"}}},
                             false,
                             false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  typescript(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Value_0 = string;

export type MyObject_Value_1 = string;

export type MyObject_Value = MyObject_Value_0 | MyObject_Value_1;

export interface MyObject {
  value?: MyObject_Value;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

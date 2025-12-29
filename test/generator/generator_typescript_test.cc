#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>

#include <sstream> // std::ostringstream

TEST(Generator_typescript, scalar_string) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::String});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = string;\n");
}

TEST(Generator_typescript, scalar_number) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Number});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = number;\n");
}

TEST(Generator_typescript, scalar_integer) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Integer});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = number;\n");
}

TEST(Generator_typescript, scalar_boolean) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Boolean});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = boolean;\n");
}

TEST(Generator_typescript, scalar_null) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::Null});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = null;\n");
}

TEST(Generator_typescript, object_with_optional_string_property) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{{sourcemeta::core::Pointer{"properties", "foo"}},
                               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "foo", IRObjectValue{{sourcemeta::core::Pointer{"properties", "foo"}},
                           false,
                           false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Properties_Foo = string;

export interface MyObject {
  "foo"?: MyObject_Properties_Foo;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_quotes) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "say \"hello\""}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "say \"hello\"",
      IRObjectValue{{sourcemeta::core::Pointer{"properties", "say \"hello\""}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObject_Properties_SayX20X22HelloX22 = string;

export interface MyObject {
  "say \"hello\""?: MyObject_Properties_SayX20X22HelloX22;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_backslash) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "path\\to\\file"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "path\\to\\file",
      IRObjectValue{{sourcemeta::core::Pointer{"properties", "path\\to\\file"}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObject_Properties_PathX5CToX5CFile = string;

export interface MyObject {
  "path\\to\\file"?: MyObject_Properties_PathX5CToX5CFile;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_newline) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "line1\nline2"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "line1\nline2",
      IRObjectValue{{sourcemeta::core::Pointer{"properties", "line1\nline2"}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(output.str(),
            "export type MyObject_Properties_Line1X0ALine2 = string;\n\n"
            "export interface MyObject {\n"
            "  \"line1\\nline2\"?: MyObject_Properties_Line1X0ALine2;\n"
            "}\n");
}

TEST(Generator_typescript, object_property_with_tab) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "col1\tcol2"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "col1\tcol2",
      IRObjectValue{{sourcemeta::core::Pointer{"properties", "col1\tcol2"}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(output.str(),
            "export type MyObject_Properties_Col1X09Col2 = string;\n\n"
            "export interface MyObject {\n"
            "  \"col1\\tcol2\"?: MyObject_Properties_Col1X09Col2;\n"
            "}\n");
}

TEST(Generator_typescript, object_property_with_carriage_return) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "line1\rline2"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "line1\rline2",
      IRObjectValue{{sourcemeta::core::Pointer{"properties", "line1\rline2"}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(output.str(),
            "export type MyObject_Properties_Line1X0DLine2 = string;\n\n"
            "export interface MyObject {\n"
            "  \"line1\\rline2\"?: MyObject_Properties_Line1X0DLine2;\n"
            "}\n");
}

TEST(Generator_typescript, object_property_with_special_characters) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "$foo@bar"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "$foo@bar",
      IRObjectValue{
          {sourcemeta::core::Pointer{"properties", "$foo@bar"}}, false, false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObject_Properties_X24FooX40Bar = string;

export interface MyObject {
  "$foo@bar"?: MyObject_Properties_X24FooX40Bar;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_spaces) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "my property name"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace("my property name",
                         IRObjectValue{{sourcemeta::core::Pointer{
                                           "properties", "my property name"}},
                                       false,
                                       false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObject_Properties_MyX20PropertyX20Name = string;

export interface MyObject {
  "my property name"?: MyObject_Properties_MyX20PropertyX20Name;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_starting_with_number) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "123abc"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "123abc",
      IRObjectValue{
          {sourcemeta::core::Pointer{"properties", "123abc"}}, false, false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Properties_123abc = string;

export interface MyObject {
  "123abc"?: MyObject_Properties_123abc;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_reserved_word) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "class"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "class", IRObjectValue{{sourcemeta::core::Pointer{"properties", "class"}},
                             false,
                             false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Properties_Class = string;

export interface MyObject {
  "class"?: MyObject_Properties_Class;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_mixed_escapes) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {sourcemeta::core::Pointer{"properties", "path\\to\\\"file\"\n"}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "path\\to\\\"file\"\n",
      IRObjectValue{
          {sourcemeta::core::Pointer{"properties", "path\\to\\\"file\"\n"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(
      output.str(),
      "export type MyObject_Properties_PathX5CToX5CX22FileX22X0A = string;\n\n"
      "export interface MyObject {\n"
      "  \"path\\\\to\\\\\\\"file\\\"\\n\"?: "
      "MyObject_Properties_PathX5CToX5CX22FileX22X0A;\n"
      "}\n");
}

TEST(Generator_typescript, object_property_empty_string) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{{sourcemeta::core::Pointer{"properties", ""}},
                               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "", IRObjectValue{
              {sourcemeta::core::Pointer{"properties", ""}}, false, false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Properties_ZEmpty = string;

export interface MyObject {
  ""?: MyObject_Properties_ZEmpty;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, impossible_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{{}});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = never;\n");
}

TEST(Generator_typescript, impossible_nested) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{{sourcemeta::core::Pointer{"foo"}}});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType_Foo = never;\n");
}

TEST(Generator_typescript, array_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"items"}}, IRScalarType::String});

  IRArray array;
  array.pointer = {};
  array.items.pointer = sourcemeta::core::Pointer{"items"};
  result.emplace_back(std::move(array));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyArray");

  const auto expected{R"TS(export type MyArray_Items = string;

export type MyArray = MyArray_Items[];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, array_nested_in_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "tags", "items"}},
               IRScalarType::String});

  IRArray array;
  array.pointer = sourcemeta::core::Pointer{"properties", "tags"};
  array.items.pointer =
      sourcemeta::core::Pointer{"properties", "tags", "items"};
  result.emplace_back(std::move(array));

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "tags", IRObjectValue{{sourcemeta::core::Pointer{"properties", "tags"}},
                            false,
                            false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Properties_Tags_Items = string;

export type MyObject_Properties_Tags = MyObject_Properties_Tags_Items[];

export interface MyObject {
  "tags"?: MyObject_Properties_Tags;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, tuple_without_additional) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{{sourcemeta::core::Pointer{"prefixItems", "0"}},
                               IRScalarType::String});

  result.emplace_back(IRScalar{{sourcemeta::core::Pointer{"prefixItems", "1"}},
                               IRScalarType::String});

  IRTuple tuple;
  tuple.pointer = {};
  tuple.items.push_back({sourcemeta::core::Pointer{"prefixItems", "0"}});
  tuple.items.push_back({sourcemeta::core::Pointer{"prefixItems", "1"}});
  result.emplace_back(std::move(tuple));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyTuple");

  const auto expected{R"TS(export type MyTuple_PrefixItems_0 = string;

export type MyTuple_PrefixItems_1 = string;

export type MyTuple = [MyTuple_PrefixItems_0, MyTuple_PrefixItems_1];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, tuple_with_additional) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{{sourcemeta::core::Pointer{"prefixItems", "0"}},
                               IRScalarType::String});

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"items"}}, IRScalarType::String});

  IRTuple tuple;
  tuple.pointer = {};
  tuple.items.push_back({sourcemeta::core::Pointer{"prefixItems", "0"}});
  tuple.additional = IRType{sourcemeta::core::Pointer{"items"}};
  result.emplace_back(std::move(tuple));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyTuple");

  const auto expected{R"TS(export type MyTuple_PrefixItems_0 = string;

export type MyTuple_Items = string;

export type MyTuple = [MyTuple_PrefixItems_0, ...MyTuple_Items[]];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, reference_property_to_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRReference{{sourcemeta::core::Pointer{"properties", "child"}}, {{}}});

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "child", IRObjectValue{{sourcemeta::core::Pointer{"properties", "child"}},
                             false,
                             false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Node");

  const auto expected{R"TS(export type Node_Properties_Child = Node;

export interface Node {
  "child"?: Node_Properties_Child;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, enumeration_strings) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IREnumeration enumeration;
  enumeration.pointer = {};
  enumeration.values.push_back(sourcemeta::core::JSON{"foo"});
  enumeration.values.push_back(sourcemeta::core::JSON{"bar"});
  enumeration.values.push_back(sourcemeta::core::JSON{"baz"});
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Status");

  EXPECT_EQ(output.str(),
            "export type Status = \"foo\" | \"bar\" | \"baz\";\n");
}

TEST(Generator_typescript, enumeration_mixed_primitives) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IREnumeration enumeration;
  enumeration.pointer = {};
  enumeration.values.push_back(sourcemeta::core::JSON{"active"});
  enumeration.values.push_back(sourcemeta::core::JSON{42});
  enumeration.values.push_back(sourcemeta::core::JSON{true});
  enumeration.values.push_back(sourcemeta::core::JSON{nullptr});
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Value");

  EXPECT_EQ(output.str(),
            "export type Value = \"active\" | 42 | true | null;\n");
}

TEST(Generator_typescript, enumeration_with_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IREnumeration enumeration;
  enumeration.pointer = {};
  enumeration.values.push_back(sourcemeta::core::JSON{"simple"});
  enumeration.values.push_back(
      sourcemeta::core::parse_json("{\"type\":\"complex\"}"));
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Config");

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
  enumeration.values.push_back(sourcemeta::core::JSON{1});
  enumeration.values.push_back(sourcemeta::core::parse_json("[1,2,3]"));
  result.emplace_back(std::move(enumeration));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Data");

  EXPECT_EQ(output.str(), "export type Data = 1 | [ 1, 2, 3 ];\n");
}

TEST(Generator_typescript, union_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{{sourcemeta::core::Pointer{"anyOf", "0"}},
                               IRScalarType::String});

  result.emplace_back(IRScalar{{sourcemeta::core::Pointer{"anyOf", "1"}},
                               IRScalarType::String});

  IRUnion my_union;
  my_union.pointer = {};
  my_union.values.push_back({sourcemeta::core::Pointer{"anyOf", "0"}});
  my_union.values.push_back({sourcemeta::core::Pointer{"anyOf", "1"}});
  result.emplace_back(std::move(my_union));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyUnion");

  const auto expected{R"TS(export type MyUnion_AnyOf_0 = string;

export type MyUnion_AnyOf_1 = string;

export type MyUnion = MyUnion_AnyOf_0 | MyUnion_AnyOf_1;
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, union_nested_in_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "value", "anyOf", "0"}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{sourcemeta::core::Pointer{"properties", "value", "anyOf", "1"}},
               IRScalarType::String});

  IRUnion my_union;
  my_union.pointer = sourcemeta::core::Pointer{"properties", "value"};
  my_union.values.push_back(
      {sourcemeta::core::Pointer{"properties", "value", "anyOf", "0"}});
  my_union.values.push_back(
      {sourcemeta::core::Pointer{"properties", "value", "anyOf", "1"}});
  result.emplace_back(std::move(my_union));

  IRObject object;
  object.pointer = {};
  object.members.emplace(
      "value", IRObjectValue{{sourcemeta::core::Pointer{"properties", "value"}},
                             false,
                             false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObject_Properties_Value_AnyOf_0 = string;

export type MyObject_Properties_Value_AnyOf_1 = string;

export type MyObject_Properties_Value = MyObject_Properties_Value_AnyOf_0 | MyObject_Properties_Value_AnyOf_1;

export interface MyObject {
  "value"?: MyObject_Properties_Value;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

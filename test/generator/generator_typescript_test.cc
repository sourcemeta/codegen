#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>

#include <sstream> // std::ostringstream

TEST(Generator_typescript, scalar_string) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(
      IRScalar{{.pointer = {}, .symbol = {}}, IRScalarType::String});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = string;\n");
}

TEST(Generator_typescript, scalar_number) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(
      IRScalar{{.pointer = {}, .symbol = {}}, IRScalarType::Number});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = number;\n");
}

TEST(Generator_typescript, scalar_integer) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(
      IRScalar{{.pointer = {}, .symbol = {}}, IRScalarType::Integer});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = number;\n");
}

TEST(Generator_typescript, scalar_boolean) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(
      IRScalar{{.pointer = {}, .symbol = {}}, IRScalarType::Boolean});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = boolean;\n");
}

TEST(Generator_typescript, scalar_null) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(
      IRScalar{{.pointer = {}, .symbol = {}}, IRScalarType::Null});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = null;\n");
}

TEST(Generator_typescript, object_with_optional_string_property) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "foo"},
                .symbol = {"foo"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "foo",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", "foo"},
                     .symbol = {"foo"}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObjectFoo = string;

export interface MyObject {
  "foo"?: MyObjectFoo;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_quotes) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", "say \"hello\""},
       .symbol = {"say \"hello\""}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "say \"hello\"",
      IRObjectValue{
          {.pointer = sourcemeta::core::Pointer{"properties", "say \"hello\""},
           .symbol = {"say \"hello\""}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObjectSayhello = string;

export interface MyObject {
  "say \"hello\""?: MyObjectSayhello;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_backslash) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", "path\\to\\file"},
       .symbol = {"path\\to\\file"}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "path\\to\\file",
      IRObjectValue{
          {.pointer = sourcemeta::core::Pointer{"properties", "path\\to\\file"},
           .symbol = {"path\\to\\file"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObjectPathtofile = string;

export interface MyObject {
  "path\\to\\file"?: MyObjectPathtofile;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_newline) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", "line1\nline2"},
       .symbol = {"line1\nline2"}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "line1\nline2",
      IRObjectValue{
          {.pointer = sourcemeta::core::Pointer{"properties", "line1\nline2"},
           .symbol = {"line1\nline2"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(output.str(), "export type MyObjectLine1line2 = string;\n\n"
                          "export interface MyObject {\n"
                          "  \"line1\\nline2\"?: MyObjectLine1line2;\n"
                          "}\n");
}

TEST(Generator_typescript, object_property_with_tab) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", "col1\tcol2"},
       .symbol = {"col1\tcol2"}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "col1\tcol2",
      IRObjectValue{
          {.pointer = sourcemeta::core::Pointer{"properties", "col1\tcol2"},
           .symbol = {"col1\tcol2"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(output.str(), "export type MyObjectCol1col2 = string;\n\n"
                          "export interface MyObject {\n"
                          "  \"col1\\tcol2\"?: MyObjectCol1col2;\n"
                          "}\n");
}

TEST(Generator_typescript, object_property_with_carriage_return) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", "line1\rline2"},
       .symbol = {"line1\rline2"}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "line1\rline2",
      IRObjectValue{
          {.pointer = sourcemeta::core::Pointer{"properties", "line1\rline2"},
           .symbol = {"line1\rline2"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(output.str(), "export type MyObjectLine1line2 = string;\n\n"
                          "export interface MyObject {\n"
                          "  \"line1\\rline2\"?: MyObjectLine1line2;\n"
                          "}\n");
}

TEST(Generator_typescript, object_property_with_special_characters) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "$foo@bar"},
                .symbol = {"$foo@bar"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "$foo@bar",
      IRObjectValue{
          {.pointer = sourcemeta::core::Pointer{"properties", "$foo@bar"},
           .symbol = {"$foo@bar"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObject$foobar = string;

export interface MyObject {
  "$foo@bar"?: MyObject$foobar;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_with_spaces) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", "my property name"},
       .symbol = {"my property name"}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "my property name",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties",
                                                          "my property name"},
                     .symbol = {"my property name"}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObjectMypropertyname = string;

export interface MyObject {
  "my property name"?: MyObjectMypropertyname;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_starting_with_number) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "123abc"},
                .symbol = {"123abc"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "123abc",
      IRObjectValue{
          {.pointer = sourcemeta::core::Pointer{"properties", "123abc"},
           .symbol = {"123abc"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_123abc = string;

export interface MyObject {
  "123abc"?: MyObject_123abc;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_reserved_word) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "class"},
                .symbol = {"class"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "class", IRObjectValue{
                   {.pointer = sourcemeta::core::Pointer{"properties", "class"},
                    .symbol = {"class"}},
                   false,
                   false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObjectClass = string;

export interface MyObject {
  "class"?: MyObjectClass;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_property_mixed_escapes) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties",
                                                     "path\\to\\\"file\"\n"},
                .symbol = {"path\\to\\\"file\"\n"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "path\\to\\\"file\"\n",
      IRObjectValue{
          {.pointer =
               sourcemeta::core::Pointer{"properties", "path\\to\\\"file\"\n"},
           .symbol = {"path\\to\\\"file\"\n"}},
          false,
          false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  EXPECT_EQ(output.str(), "export type MyObjectPathtofile = string;\n\n"
                          "export interface MyObject {\n"
                          "  \"path\\\\to\\\\\\\"file\\\"\\n\"?: "
                          "MyObjectPathtofile;\n"
                          "}\n");
}

TEST(Generator_typescript, object_property_empty_string) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", ""}, .symbol = {""}},
      IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "", IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", ""},
                         .symbol = {""}},
                        false,
                        false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject = string;

export interface _MyObject {
  ""?: MyObject;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, impossible_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{{.pointer = {}, .symbol = {}}});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = never;\n");
}

TEST(Generator_typescript, impossible_nested) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{
      {.pointer = sourcemeta::core::Pointer{"foo"}, .symbol = {"foo"}}});

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyTypeFoo = never;\n");
}

TEST(Generator_typescript, array_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"items"}, .symbol = {"items"}},
      IRScalarType::String});

  IRArray array;
  array.pointer = {};
  array.items = IRType{.pointer = sourcemeta::core::Pointer{"items"},
                       .symbol = {"items"}};
  result.emplace_back(std::move(array));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyArray");

  const auto expected{R"TS(export type MyArrayItems = string;

export type MyArray = MyArrayItems[];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, array_nested_in_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"properties", "tags", "items"},
       .symbol = {"tags", "items"}},
      IRScalarType::String});

  IRArray array;
  array.pointer = sourcemeta::core::Pointer{"properties", "tags"};
  array.symbol = {"tags"};
  array.items = IRType{
      .pointer = sourcemeta::core::Pointer{"properties", "tags", "items"},
      .symbol = {"tags", "items"}};
  result.emplace_back(std::move(array));

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "tags",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", "tags"},
                     .symbol = {"tags"}},
                    false,
                    false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObjectTagsItems = string;

export type MyObjectTags = MyObjectTagsItems[];

export interface MyObject {
  "tags"?: MyObjectTags;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, tuple_without_additional) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"prefixItems", "0"},
                .symbol = {"0"}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"prefixItems", "1"},
                .symbol = {"1"}},
               IRScalarType::String});

  IRTuple tuple;
  tuple.pointer = {};
  tuple.items.push_back(
      {.pointer = sourcemeta::core::Pointer{"prefixItems", "0"},
       .symbol = {"0"}});
  tuple.items.push_back(
      {.pointer = sourcemeta::core::Pointer{"prefixItems", "1"},
       .symbol = {"1"}});
  result.emplace_back(std::move(tuple));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyTuple");

  const auto expected{R"TS(export type MyTuple_0 = string;

export type MyTuple_1 = string;

export type MyTuple = [MyTuple_0, MyTuple_1];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, tuple_with_additional) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"prefixItems", "0"},
                .symbol = {"0"}},
               IRScalarType::String});

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"items"}, .symbol = {"items"}},
      IRScalarType::String});

  IRTuple tuple;
  tuple.pointer = {};
  tuple.items.push_back(
      {.pointer = sourcemeta::core::Pointer{"prefixItems", "0"},
       .symbol = {"0"}});
  tuple.additional = IRType{.pointer = sourcemeta::core::Pointer{"items"},
                            .symbol = {"items"}};
  result.emplace_back(std::move(tuple));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyTuple");

  const auto expected{R"TS(export type MyTuple_0 = string;

export type MyTupleItems = string;

export type MyTuple = [MyTuple_0, ...MyTupleItems[]];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, reference_property_to_root) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRReference{{.pointer = sourcemeta::core::Pointer{"properties", "child"},
                   .symbol = {"child"}},
                  {.pointer = {}, .symbol = {}}});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "child", IRObjectValue{
                   {.pointer = sourcemeta::core::Pointer{"properties", "child"},
                    .symbol = {"child"}},
                   false,
                   false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Node");

  const auto expected{R"TS(export type NodeChild = Node;

export interface Node {
  "child"?: NodeChild;
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

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"anyOf", "0"}, .symbol = {"0"}},
      IRScalarType::String});

  result.emplace_back(IRScalar{
      {.pointer = sourcemeta::core::Pointer{"anyOf", "1"}, .symbol = {"1"}},
      IRScalarType::String});

  IRUnion my_union;
  my_union.pointer = {};
  my_union.values.push_back(
      {.pointer = sourcemeta::core::Pointer{"anyOf", "0"}, .symbol = {"0"}});
  my_union.values.push_back(
      {.pointer = sourcemeta::core::Pointer{"anyOf", "1"}, .symbol = {"1"}});
  result.emplace_back(std::move(my_union));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyUnion");

  const auto expected{R"TS(export type MyUnion_0 = string;

export type MyUnion_1 = string;

export type MyUnion =
  MyUnion_0 |
  MyUnion_1;
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, union_nested_in_object) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "value",
                                                     "anyOf", "0"},
                .symbol = {"value", "0"}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "value",
                                                     "anyOf", "1"},
                .symbol = {"value", "1"}},
               IRScalarType::String});

  IRUnion my_union;
  my_union.pointer = sourcemeta::core::Pointer{"properties", "value"};
  my_union.symbol = {"value"};
  my_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"properties", "value", "anyOf", "0"},
       .symbol = {"value", "0"}});
  my_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"properties", "value", "anyOf", "1"},
       .symbol = {"value", "1"}});
  result.emplace_back(std::move(my_union));

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "value", IRObjectValue{
                   {.pointer = sourcemeta::core::Pointer{"properties", "value"},
                    .symbol = {"value"}},
                   false,
                   false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{
      R"TS(export type MyObjectValue_0 = string;

export type MyObjectValue_1 = string;

export type MyObjectValue =
  MyObjectValue_0 |
  MyObjectValue_1;

export interface MyObject {
  "value"?: MyObjectValue;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_with_additional_properties_typed) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "name"},
                .symbol = {"name"}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "age"},
                .symbol = {"age"}},
               IRScalarType::Integer});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
                .symbol = {"additionalProperties"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "name",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", "name"},
                     .symbol = {"name"}},
                    true,
                    false});
  object.members.emplace_back(
      "age",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", "age"},
                     .symbol = {"age"}},
                    false,
                    false});
  object.additional =
      IRType{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
             .symbol = {"additionalProperties"}};
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Person");

  const auto expected{R"TS(export type PersonName = string;

export type PersonAge = number;

export type PersonAdditionalProperties = string;

export interface Person {
  "name": PersonName;
  "age"?: PersonAge;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    PersonName |
    PersonAge |
    PersonAdditionalProperties |
    undefined;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript,
     object_with_single_property_and_additional_properties) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "id"},
                .symbol = {"id"}},
               IRScalarType::Integer});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
                .symbol = {"additionalProperties"}},
               IRScalarType::String});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "id",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", "id"},
                     .symbol = {"id"}},
                    true,
                    false});
  object.additional =
      IRType{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
             .symbol = {"additionalProperties"}};
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Item");

  const auto expected{R"TS(export type ItemId = number;

export type ItemAdditionalProperties = string;

export interface Item {
  "id": ItemId;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    ItemId |
    ItemAdditionalProperties |
    undefined;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, array_without_items) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IRArray array;
  array.pointer = {};
  array.items = std::nullopt;
  result.emplace_back(std::move(array));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyArray");

  const auto expected{R"TS(export type MyArray = unknown[];
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_with_additional_properties_false) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "foo"},
                .symbol = {"foo"}},
               IRScalarType::String});

  result.emplace_back(IRImpossible{
      {.pointer = sourcemeta::core::Pointer{"additionalProperties"},
       .symbol = {"additionalProperties"}}});

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "foo",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", "foo"},
                     .symbol = {"foo"}},
                    false,
                    false});
  object.additional =
      IRType{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
             .symbol = {"additionalProperties"}};
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "MyObject");

  const auto expected{R"TS(export type MyObjectFoo = string;

export type MyObjectAdditionalProperties = never;

export interface MyObject {
  "foo"?: MyObjectFoo;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    MyObjectFoo |
    MyObjectAdditionalProperties |
    undefined;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_with_additional_properties_any) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"properties", "name"},
                .symbol = {"name"}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "0"},
                .symbol = {"additionalProperties", "0"}},
               IRScalarType::Null});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "1"},
                .symbol = {"additionalProperties", "1"}},
               IRScalarType::Boolean});

  IRArray any_array;
  any_array.pointer =
      sourcemeta::core::Pointer{"additionalProperties", "anyOf", "2"};
  any_array.symbol = {"additionalProperties", "2"};
  any_array.items = std::nullopt;
  result.emplace_back(std::move(any_array));

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "3"},
                .symbol = {"additionalProperties", "3"}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "4"},
                .symbol = {"additionalProperties", "4"}},
               IRScalarType::Number});

  IRUnion any_union;
  any_union.pointer = sourcemeta::core::Pointer{"additionalProperties"};
  any_union.symbol = {"additionalProperties"};
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "0"},
       .symbol = {"additionalProperties", "0"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "1"},
       .symbol = {"additionalProperties", "1"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "2"},
       .symbol = {"additionalProperties", "2"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "3"},
       .symbol = {"additionalProperties", "3"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "4"},
       .symbol = {"additionalProperties", "4"}});
  result.emplace_back(std::move(any_union));

  IRObject object;
  object.pointer = {};
  object.members.emplace_back(
      "name",
      IRObjectValue{{.pointer = sourcemeta::core::Pointer{"properties", "name"},
                     .symbol = {"name"}},
                    false,
                    false});
  object.additional =
      IRType{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
             .symbol = {"additionalProperties"}};
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Test");

  const auto expected{R"TS(export type TestName = string;

export type TestAdditionalProperties_0 = null;

export type TestAdditionalProperties_1 = boolean;

export type TestAdditionalProperties_2 = unknown[];

export type TestAdditionalProperties_3 = string;

export type TestAdditionalProperties_4 = number;

export type TestAdditionalProperties =
  TestAdditionalProperties_0 |
  TestAdditionalProperties_1 |
  TestAdditionalProperties_2 |
  TestAdditionalProperties_3 |
  TestAdditionalProperties_4;

export interface Test {
  "name"?: TestName;
  [key: string]:
    // As a notable limitation, TypeScript requires index signatures
    // to also include the types of all of its properties, so we must
    // match a superset of what JSON Schema allows
    TestName |
    TestAdditionalProperties |
    undefined;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_only_additional_properties) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
                .symbol = {"additionalProperties"}},
               IRScalarType::Boolean});

  IRObject object;
  object.pointer = {};
  object.additional =
      IRType{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
             .symbol = {"additionalProperties"}};
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Test");

  const auto expected{R"TS(export type TestAdditionalProperties = boolean;

export type Test = Record<string, TestAdditionalProperties>;
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_only_additional_properties_false) {
  using namespace sourcemeta::codegen;

  IRResult result;

  IRObject object;
  object.pointer = {};
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Test");

  const auto expected{R"TS(export interface Test {
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, object_only_additional_properties_true) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "0"},
                .symbol = {"additionalProperties", "0"}},
               IRScalarType::Null});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "1"},
                .symbol = {"additionalProperties", "1"}},
               IRScalarType::Boolean});

  IRArray any_array;
  any_array.pointer =
      sourcemeta::core::Pointer{"additionalProperties", "anyOf", "2"};
  any_array.symbol = {"additionalProperties", "2"};
  any_array.items = std::nullopt;
  result.emplace_back(std::move(any_array));

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "3"},
                .symbol = {"additionalProperties", "3"}},
               IRScalarType::String});

  result.emplace_back(
      IRScalar{{.pointer = sourcemeta::core::Pointer{"additionalProperties",
                                                     "anyOf", "4"},
                .symbol = {"additionalProperties", "4"}},
               IRScalarType::Number});

  IRUnion any_union;
  any_union.pointer = sourcemeta::core::Pointer{"additionalProperties"};
  any_union.symbol = {"additionalProperties"};
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "0"},
       .symbol = {"additionalProperties", "0"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "1"},
       .symbol = {"additionalProperties", "1"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "2"},
       .symbol = {"additionalProperties", "2"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "3"},
       .symbol = {"additionalProperties", "3"}});
  any_union.values.push_back(
      {.pointer =
           sourcemeta::core::Pointer{"additionalProperties", "anyOf", "4"},
       .symbol = {"additionalProperties", "4"}});
  result.emplace_back(std::move(any_union));

  IRObject object;
  object.pointer = {};
  object.additional =
      IRType{.pointer = sourcemeta::core::Pointer{"additionalProperties"},
             .symbol = {"additionalProperties"}};
  result.emplace_back(std::move(object));

  std::ostringstream output;
  generate<TypeScript>(output, result, "Test");

  const auto expected{R"TS(export type TestAdditionalProperties_0 = null;

export type TestAdditionalProperties_1 = boolean;

export type TestAdditionalProperties_2 = unknown[];

export type TestAdditionalProperties_3 = string;

export type TestAdditionalProperties_4 = number;

export type TestAdditionalProperties =
  TestAdditionalProperties_0 |
  TestAdditionalProperties_1 |
  TestAdditionalProperties_2 |
  TestAdditionalProperties_3 |
  TestAdditionalProperties_4;

export type Test = Record<string, TestAdditionalProperties>;
)TS"};

  EXPECT_EQ(output.str(), expected);
}

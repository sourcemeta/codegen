#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>
#include <sourcemeta/core/jsonpointer.h>

TEST(Generator_to_pascal_case,
     empty_instance_location_returns_default_namespace) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location;
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "Schema");
}

TEST(Generator_to_pascal_case, empty_instance_location_with_custom_namespace) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location;
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "MyNamespace")};
  EXPECT_EQ(result, "MyNamespace");
}

TEST(Generator_to_pascal_case, single_property_token) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFoo");
}

TEST(Generator_to_pascal_case, multiple_property_tokens) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooBar");
}

TEST(Generator_to_pascal_case, three_property_tokens) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "bar", "baz"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooBarBaz");
}

TEST(Generator_to_pascal_case, property_with_hyphen) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo-bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooX2DBar");
}

TEST(Generator_to_pascal_case, property_starting_with_number) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"123foo"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "Schema_123Foo");
}

TEST(Generator_to_pascal_case, property_that_is_only_numbers) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"123"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "Schema_123");
}

TEST(Generator_to_pascal_case, property_with_underscore) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo_bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooX5FBar");
}

TEST(Generator_to_pascal_case, property_with_spaces) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooX20Bar");
}

TEST(Generator_to_pascal_case, property_with_special_characters) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo@bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooX40Bar");
}

TEST(Generator_to_pascal_case, empty_property_name) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{""}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "Schema");
}

TEST(Generator_to_pascal_case, deeply_nested_path) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"a", "b", "c", "d", "e"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaABCDE");
}

TEST(Generator_to_pascal_case, single_camel_case_token) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"fooBar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooBar");
}

TEST(Generator_to_pascal_case, two_tokens_foo_bar) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooBar");
}

TEST(Generator_to_pascal_case, preserves_case_after_first_letter) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"fooBAR"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooBAR");
}

TEST(Generator_to_pascal_case, multiple_special_chars_in_sequence) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo--bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooX2DX2DBar");
}

TEST(Generator_to_pascal_case, leading_special_characters) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"--foo"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaX2DX2DFoo");
}

TEST(Generator_to_pascal_case, trailing_special_characters) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo--"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaFooX2DX2D");
}

TEST(Generator_to_pascal_case, only_special_characters) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"@#$%"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "SchemaX40X23X24X25");
}

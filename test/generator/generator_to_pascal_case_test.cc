#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>
#include <sourcemeta/core/jsonpointer.h>

TEST(Generator_to_pascal_case, empty_instance_location_lowercase_namespace) {
  const sourcemeta::core::PointerTemplate instance_location;
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema");
}

TEST(Generator_to_pascal_case, empty_instance_location_uppercase_namespace) {
  const sourcemeta::core::PointerTemplate instance_location;
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "Schema")};
  EXPECT_EQ(result, "Schema");
}

TEST(Generator_to_pascal_case, empty_instance_location_custom_namespace) {
  const sourcemeta::core::PointerTemplate instance_location;
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "myNamespace")};
  EXPECT_EQ(result, "MyNamespace");
}

TEST(Generator_to_pascal_case, single_lowercase_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo");
}

TEST(Generator_to_pascal_case, single_lowercase_token_long) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foobar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foobar");
}

TEST(Generator_to_pascal_case, single_uppercase_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"Foo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_UFoo");
}

TEST(Generator_to_pascal_case, single_all_uppercase_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"FOO"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_UFOO");
}

TEST(Generator_to_pascal_case, lowercase_x_at_start) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"xoo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X78oo");
}

TEST(Generator_to_pascal_case, uppercase_X_at_start) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"Xoo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X58oo");
}

TEST(Generator_to_pascal_case, lowercase_u_at_start) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"uoo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X75oo");
}

TEST(Generator_to_pascal_case, uppercase_U_at_start) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"Uoo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X55oo");
}

TEST(Generator_to_pascal_case, uppercase_X_in_middle) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foXbar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FoX58bar");
}

TEST(Generator_to_pascal_case, uppercase_U_in_middle) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foUbar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FoX55bar");
}

TEST(Generator_to_pascal_case, lowercase_x_in_middle) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foxbar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foxbar");
}

TEST(Generator_to_pascal_case, lowercase_u_in_middle) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foubar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foubar");
}

TEST(Generator_to_pascal_case, hyphen_in_middle) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo-bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FooX2DBar");
}

TEST(Generator_to_pascal_case, underscore_in_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo_bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FooX5FBar");
}

TEST(Generator_to_pascal_case, space_in_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FooX20Bar");
}

TEST(Generator_to_pascal_case, at_sign_in_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo@bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FooX40Bar");
}

TEST(Generator_to_pascal_case, special_char_at_start) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"@foo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X40Foo");
}

TEST(Generator_to_pascal_case, only_special_characters) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"@#$%"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X40X23X24X25");
}

TEST(Generator_to_pascal_case, multiple_hyphens) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo--bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FooX2DX2DBar");
}

TEST(Generator_to_pascal_case, digit_at_start) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"123foo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_123foo");
}

TEST(Generator_to_pascal_case, only_digits) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"123"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_123");
}

TEST(Generator_to_pascal_case, digits_in_middle) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo123bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo123bar");
}

TEST(Generator_to_pascal_case, digits_at_end) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo123"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo123");
}

TEST(Generator_to_pascal_case, two_lowercase_tokens) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo_Bar");
}

TEST(Generator_to_pascal_case, three_lowercase_tokens) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "bar", "baz"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo_Bar_Baz");
}

TEST(Generator_to_pascal_case, camelcase_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"fooBar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FooBar");
}

TEST(Generator_to_pascal_case, mixed_case_multi_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "Bar"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo_UBar");
}

TEST(Generator_to_pascal_case, lowercase_x_followed_by_digits) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"x40"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X7840");
}

TEST(Generator_to_pascal_case, uppercase_X_followed_by_digits) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"X40"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X5840");
}

TEST(Generator_to_pascal_case, lowercase_u_followed_by_uppercase) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"uFoo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X75Foo");
}

TEST(Generator_to_pascal_case, uppercase_U_followed_by_uppercase) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"UFoo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_X55Foo");
}

TEST(Generator_to_pascal_case, empty_token) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{""}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema");
}

TEST(Generator_to_pascal_case, deeply_nested_path) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"a", "b", "c", "d", "e"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_A_B_C_D_E");
}

TEST(Generator_to_pascal_case, preserves_case_after_first_letter) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"fooBAR"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_FooBAR");
}

TEST(Generator_to_pascal_case, wildcard_property) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::PointerTemplate::Wildcard::Property};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_AnyProperty");
}

TEST(Generator_to_pascal_case, wildcard_item) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::PointerTemplate::Wildcard::Item};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_AnyItem");
}

TEST(Generator_to_pascal_case, wildcard_key) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::PointerTemplate::Wildcard::Key};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_AnyKey");
}

TEST(Generator_to_pascal_case, condition_without_suffix) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::PointerTemplate::Condition{}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Maybe");
}

TEST(Generator_to_pascal_case, condition_with_suffix) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::PointerTemplate::Condition{"then"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_MaybeThen");
}

TEST(Generator_to_pascal_case, condition_with_uppercase_suffix) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::PointerTemplate::Condition{"Then"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_MaybeUThen");
}

TEST(Generator_to_pascal_case, negation) {
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::PointerTemplate::Negation{}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Not");
}

TEST(Generator_to_pascal_case, regex_simple) {
  const sourcemeta::core::PointerTemplate instance_location{std::string{"foo"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_RegexFoo");
}

TEST(Generator_to_pascal_case, regex_with_special_chars) {
  const sourcemeta::core::PointerTemplate instance_location{
      std::string{"^foo.*"}};
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_RegexX5EFooX2EX2A");
}

TEST(Generator_to_pascal_case, property_then_wildcard) {
  sourcemeta::core::PointerTemplate instance_location;
  instance_location.emplace_back(sourcemeta::core::Pointer::Token{"foo"});
  instance_location.emplace_back(
      sourcemeta::core::PointerTemplate::Wildcard::Property);
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo_AnyProperty");
}

TEST(Generator_to_pascal_case, wildcard_then_property) {
  sourcemeta::core::PointerTemplate instance_location;
  instance_location.emplace_back(
      sourcemeta::core::PointerTemplate::Wildcard::Property);
  instance_location.emplace_back(sourcemeta::core::Pointer::Token{"foo"});
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_AnyProperty_Foo");
}

TEST(Generator_to_pascal_case, property_wildcard_property) {
  sourcemeta::core::PointerTemplate instance_location;
  instance_location.emplace_back(sourcemeta::core::Pointer::Token{"foo"});
  instance_location.emplace_back(
      sourcemeta::core::PointerTemplate::Wildcard::Property);
  instance_location.emplace_back(sourcemeta::core::Pointer::Token{"bar"});
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Foo_AnyProperty_Bar");
}

TEST(Generator_to_pascal_case, condition_then_property) {
  sourcemeta::core::PointerTemplate instance_location;
  instance_location.emplace_back(
      sourcemeta::core::PointerTemplate::Condition{"if"});
  instance_location.emplace_back(sourcemeta::core::Pointer::Token{"foo"});
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_MaybeIf_Foo");
}

TEST(Generator_to_pascal_case, negation_then_property) {
  sourcemeta::core::PointerTemplate instance_location;
  instance_location.emplace_back(sourcemeta::core::PointerTemplate::Negation{});
  instance_location.emplace_back(sourcemeta::core::Pointer::Token{"foo"});
  const auto result{
      sourcemeta::codegen::to_pascal_case(instance_location, "schema")};
  EXPECT_EQ(result, "Schema_Not_Foo");
}

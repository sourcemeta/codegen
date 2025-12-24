#ifndef SOURCEMETA_CODEGEN_IR_DEFAULT_COMPILER_H_
#define SOURCEMETA_CODEGEN_IR_DEFAULT_COMPILER_H_

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/jsonschema.h>

#include <cassert>       // assert
#include <string_view>   // std::string_view
#include <unordered_set> // std::unordered_set

// We do not check vocabularies here because the canonicaliser ensures
// we never get an official keyword when its vocabulary is not present
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define ONLY_WHITELIST_KEYWORDS(schema, subschema, pointer, ...)               \
  {                                                                            \
    static const std::unordered_set<std::string_view> allowed{__VA_ARGS__};    \
    for (const auto &entry : (subschema).as_object()) {                        \
      if (!allowed.contains(entry.first)) {                                    \
        throw sourcemeta::codegen::UnsupportedKeyword(                         \
            (schema), (pointer), entry.first,                                  \
            "Unexpected keyword in subschema");                                \
      }                                                                        \
    }                                                                          \
  }

namespace sourcemeta::codegen {

auto handle_impossible(
    const sourcemeta::core::JSON &, const sourcemeta::core::SchemaFrame &,
    const sourcemeta::core::SchemaFrame::Location &location,
    const sourcemeta::core::Vocabularies &,
    const sourcemeta::core::SchemaResolver &, const sourcemeta::core::JSON &,
    const sourcemeta::core::PointerTemplate &instance_location)
    -> IRImpossible {
  return IRImpossible{
      {.pointer = location.pointer, .instance_location = instance_location}};
}

auto handle_string(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::SchemaFrame &,
                   const sourcemeta::core::SchemaFrame::Location &location,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::SchemaResolver &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  ONLY_WHITELIST_KEYWORDS(
      schema, subschema, location.pointer,
      {"$schema", "$id", "type", "minLength", "maxLength", "pattern"});
  return IRScalar{
      {.pointer = location.pointer, .instance_location = instance_location},
      IRScalarType::String};
}

auto handle_object(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::SchemaFrame &,
                   const sourcemeta::core::SchemaFrame::Location &location,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::SchemaResolver &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRObject {
  ONLY_WHITELIST_KEYWORDS(
      schema, subschema, location.pointer,
      {"$schema", "$id", "type", "properties", "required",
       // Note that most programming languages CANNOT represent the idea
       // of additional properties, mainly if they differ from the types of the
       // other properties. Therefore, we whitelist this, but we consider it to
       // be the responsability of the validator
       "additionalProperties", "minProperties", "maxProperties",
       "propertyNames"});

  std::unordered_map<sourcemeta::core::JSON::String, IRObjectValue> members;

  // Guaranteed by canonicalisation
  assert(subschema.defines("properties"));

  const auto &properties{subschema.at("properties")};

  std::unordered_set<std::string_view> required_set;
  if (subschema.defines("required")) {
    const auto &required{schema.at("required")};
    for (const auto &item : required.as_array()) {
      // Guaranteed by canonicalisation
      assert(properties.defines(item.to_string()));
      required_set.insert(item.to_string());
    }
  }

  for (const auto &entry : properties.as_object()) {
    auto property_pointer{location.pointer};
    property_pointer.push_back("properties");
    property_pointer.push_back(entry.first);

    auto property_instance_location{instance_location};
    property_instance_location.emplace_back(
        sourcemeta::core::Pointer::Token{entry.first});

    IRObjectValue member_value{
        {.pointer = property_pointer,
         .instance_location = property_instance_location},
        required_set.contains(entry.first),
        false};

    members.emplace(entry.first, std::move(member_value));
  }

  std::optional<IRObjectValue> additional{std::nullopt};
  if (subschema.defines("additionalProperties")) {
    auto additional_pointer{location.pointer};
    additional_pointer.push_back("additionalProperties");

    auto additional_instance_location{instance_location};
    additional_instance_location.emplace_back(
        sourcemeta::core::PointerTemplate::Condition{
            .suffix = "additionalProperties"});
    additional_instance_location.emplace_back(
        sourcemeta::core::PointerTemplate::Wildcard::Property);

    additional =
        IRObjectValue{{.pointer = additional_pointer,
                       .instance_location = additional_instance_location},
                      false,
                      false};
  }

  return IRObject{
      {.pointer = location.pointer, .instance_location = instance_location},
      std::move(members),
      std::move(additional)};
}

auto handle_integer(const sourcemeta::core::JSON &schema,
                    const sourcemeta::core::SchemaFrame &,
                    const sourcemeta::core::SchemaFrame::Location &location,
                    const sourcemeta::core::Vocabularies &,
                    const sourcemeta::core::SchemaResolver &,
                    const sourcemeta::core::JSON &subschema,
                    const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, location.pointer,
                          {"$schema", "$id", "type", "minimum", "maximum",
                           "exclusiveMinimum", "exclusiveMaximum",
                           "multipleOf"});
  return IRScalar{
      {.pointer = location.pointer, .instance_location = instance_location},
      IRScalarType::Integer};
}

auto handle_number(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::SchemaFrame &,
                   const sourcemeta::core::SchemaFrame::Location &location,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::SchemaResolver &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, location.pointer,
                          {"$schema", "$id", "type", "minimum", "maximum",
                           "exclusiveMinimum", "exclusiveMaximum",
                           "multipleOf"});
  return IRScalar{
      {.pointer = location.pointer, .instance_location = instance_location},
      IRScalarType::Number};
}

auto handle_array(const sourcemeta::core::JSON &schema,
                  const sourcemeta::core::SchemaFrame &,
                  const sourcemeta::core::SchemaFrame::Location &location,
                  const sourcemeta::core::Vocabularies &vocabularies,
                  const sourcemeta::core::SchemaResolver &,
                  const sourcemeta::core::JSON &subschema,
                  const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, location.pointer,
                          {"$schema", "$id", "type", "items", "minItems",
                           "maxItems", "uniqueItems", "contains", "minContains",
                           "maxContains", "additionalItems", "prefixItems"});

  using Vocabularies = sourcemeta::core::Vocabularies;

  if (vocabularies.contains(
          Vocabularies::Known::JSON_Schema_2020_12_Applicator) &&
      subschema.defines("prefixItems")) {
    const auto &prefix_items{subschema.at("prefixItems")};
    assert(prefix_items.is_array());

    std::vector<IRType> tuple_items;
    for (std::size_t index = 0; index < prefix_items.size(); ++index) {
      auto item_pointer{location.pointer};
      item_pointer.push_back("prefixItems");
      item_pointer.push_back(index);

      auto item_instance_location{instance_location};
      item_instance_location.emplace_back(
          sourcemeta::core::PointerTemplate::Condition{.suffix =
                                                           "prefixItems"});
      item_instance_location.emplace_back(index);

      tuple_items.push_back({.pointer = item_pointer,
                             .instance_location = item_instance_location});
    }

    std::optional<IRType> additional{std::nullopt};
    if (subschema.defines("items")) {
      auto additional_pointer{location.pointer};
      additional_pointer.push_back("items");

      auto additional_instance_location{instance_location};
      additional_instance_location.emplace_back(
          sourcemeta::core::PointerTemplate::Condition{.suffix = "items"});
      additional_instance_location.emplace_back(
          sourcemeta::core::PointerTemplate::Wildcard::Item);

      additional = IRType{.pointer = additional_pointer,
                          .instance_location = additional_instance_location};
    }

    return IRTuple{
        {.pointer = location.pointer, .instance_location = instance_location},
        std::move(tuple_items),
        std::move(additional)};
  }

  if (vocabularies.contains_any(
          {Vocabularies::Known::JSON_Schema_2019_09_Applicator,
           Vocabularies::Known::JSON_Schema_Draft_7,
           Vocabularies::Known::JSON_Schema_Draft_6,
           Vocabularies::Known::JSON_Schema_Draft_4,
           Vocabularies::Known::JSON_Schema_Draft_3}) &&
      subschema.defines("items") && subschema.at("items").is_array()) {
    const auto &items_array{subschema.at("items")};

    std::vector<IRType> tuple_items;
    for (std::size_t index = 0; index < items_array.size(); ++index) {
      auto item_pointer{location.pointer};
      item_pointer.push_back("items");
      item_pointer.push_back(index);

      auto item_instance_location{instance_location};
      item_instance_location.emplace_back(
          sourcemeta::core::PointerTemplate::Condition{.suffix = "items"});
      item_instance_location.emplace_back(index);

      tuple_items.push_back({.pointer = item_pointer,
                             .instance_location = item_instance_location});
    }

    std::optional<IRType> additional{std::nullopt};
    if (subschema.defines("additionalItems")) {
      auto additional_pointer{location.pointer};
      additional_pointer.push_back("additionalItems");

      auto additional_instance_location{instance_location};
      additional_instance_location.emplace_back(
          sourcemeta::core::PointerTemplate::Condition{.suffix =
                                                           "additionalItems"});
      additional_instance_location.emplace_back(
          sourcemeta::core::PointerTemplate::Wildcard::Item);

      additional = IRType{.pointer = additional_pointer,
                          .instance_location = additional_instance_location};
    }

    return IRTuple{
        {.pointer = location.pointer, .instance_location = instance_location},
        std::move(tuple_items),
        std::move(additional)};
  }

  assert(subschema.defines("items"));
  auto items_pointer{location.pointer};
  items_pointer.push_back("items");
  auto items_instance_location{instance_location};
  items_instance_location.emplace_back(
      sourcemeta::core::PointerTemplate::Condition{.suffix = "items"});
  items_instance_location.emplace_back(
      sourcemeta::core::PointerTemplate::Wildcard::Item);

  return IRArray{
      {.pointer = location.pointer, .instance_location = instance_location},
      {.pointer = items_pointer, .instance_location = items_instance_location}};
}

auto handle_enum(const sourcemeta::core::JSON &schema,
                 const sourcemeta::core::SchemaFrame &,
                 const sourcemeta::core::SchemaFrame::Location &location,
                 const sourcemeta::core::Vocabularies &,
                 const sourcemeta::core::SchemaResolver &,
                 const sourcemeta::core::JSON &subschema,
                 const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, location.pointer,
                          {"$schema", "$id", "enum"});
  const auto &enum_json{subschema.at("enum")};

  // Boolean and null special cases
  if (enum_json.size() == 1 && enum_json.at(0).is_null()) {
    return IRScalar{
        {.pointer = location.pointer, .instance_location = instance_location},
        IRScalarType::Null};
  } else if (enum_json.size() == 2) {
    const auto &first{enum_json.at(0)};
    const auto &second{enum_json.at(1)};
    if ((first.is_boolean() && second.is_boolean()) &&
        (first.to_boolean() != second.to_boolean())) {
      return IRScalar{
          {.pointer = location.pointer, .instance_location = instance_location},
          IRScalarType::Boolean};
    }
  }

  std::vector<sourcemeta::core::JSON> values{enum_json.as_array().cbegin(),
                                             enum_json.as_array().cend()};
  return IREnumeration{
      {.pointer = location.pointer, .instance_location = instance_location},
      std::move(values)};
}

auto handle_anyof(const sourcemeta::core::JSON &schema,
                  const sourcemeta::core::SchemaFrame &,
                  const sourcemeta::core::SchemaFrame::Location &location,
                  const sourcemeta::core::Vocabularies &,
                  const sourcemeta::core::SchemaResolver &,
                  const sourcemeta::core::JSON &subschema,
                  const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, location.pointer,
                          {"$schema", "$id", "anyOf"});

  const auto &any_of{subschema.at("anyOf")};
  assert(any_of.is_array());
  assert(any_of.size() >= 2);

  std::vector<IRType> branches;
  for (std::size_t index = 0; index < any_of.size(); ++index) {
    auto branch_pointer{location.pointer};
    branch_pointer.push_back("anyOf");
    branch_pointer.push_back(index);

    auto branch_instance_location{instance_location};
    branch_instance_location.emplace_back(
        sourcemeta::core::PointerTemplate::Condition{.suffix = "anyOf"});
    branch_instance_location.emplace_back(
        sourcemeta::core::PointerTemplate::Condition{
            .suffix = std::to_string(index)});

    branches.push_back({.pointer = branch_pointer,
                        .instance_location = branch_instance_location});
  }

  return IRUnion{
      {.pointer = location.pointer, .instance_location = instance_location},
      std::move(branches)};
}

auto handle_ref(const sourcemeta::core::JSON &schema,
                const sourcemeta::core::SchemaFrame &,
                const sourcemeta::core::SchemaFrame::Location &location,
                const sourcemeta::core::Vocabularies &,
                const sourcemeta::core::SchemaResolver &,
                const sourcemeta::core::JSON &,
                const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw UnexpectedSchema(schema, location.pointer,
                         "We do not support this type of subschema yet");
}

auto default_compiler(
    const sourcemeta::core::JSON &schema,
    const sourcemeta::core::SchemaFrame &frame,
    const sourcemeta::core::SchemaFrame::Location &location,
    const sourcemeta::core::SchemaResolver &resolver,
    const sourcemeta::core::JSON &subschema,
    const sourcemeta::core::PointerTemplate &instance_location) -> IREntity {
  const auto vocabularies{frame.vocabularies(location, resolver)};
  assert(!vocabularies.empty());

  // Be strict with vocabulary support
  using Vocabularies = sourcemeta::core::Vocabularies;
  static const std::unordered_set<Vocabularies::URI> supported{
      Vocabularies::Known::JSON_Schema_2020_12_Core,
      Vocabularies::Known::JSON_Schema_2020_12_Applicator,
      Vocabularies::Known::JSON_Schema_2020_12_Validation,
      Vocabularies::Known::JSON_Schema_2020_12_Unevaluated,
      Vocabularies::Known::JSON_Schema_2020_12_Content,
      Vocabularies::Known::JSON_Schema_2020_12_Meta_Data,
      Vocabularies::Known::JSON_Schema_2020_12_Format_Annotation,
      Vocabularies::Known::JSON_Schema_2019_09_Core,
      Vocabularies::Known::JSON_Schema_2019_09_Applicator,
      Vocabularies::Known::JSON_Schema_2019_09_Validation,
      Vocabularies::Known::JSON_Schema_2019_09_Content,
      Vocabularies::Known::JSON_Schema_2019_09_Meta_Data,
      Vocabularies::Known::JSON_Schema_2019_09_Format,
      Vocabularies::Known::JSON_Schema_Draft_7,
      Vocabularies::Known::JSON_Schema_Draft_6,
      Vocabularies::Known::JSON_Schema_Draft_4};
  vocabularies.throw_if_any_unsupported(supported,
                                        "Unsupported required vocabulary");

  // The canonicaliser ensures that every subschema schema is only in one of the
  // following shapes

  if (subschema.is_boolean()) {
    assert(!subschema.to_boolean());
    return handle_impossible(schema, frame, location, vocabularies, resolver,
                             subschema, instance_location);
  } else if (subschema.defines("type")) {
    const auto &type_value{subschema.at("type")};
    if (!type_value.is_string()) {
      throw UnsupportedKeywordValue(schema, location.pointer, "type",
                                    "Expected a string value");
    }

    const auto &type_string{type_value.to_string()};

    // The canonicaliser transforms any other type
    if (type_string == "string") {
      return handle_string(schema, frame, location, vocabularies, resolver,
                           subschema, instance_location);
    } else if (type_string == "object") {
      return handle_object(schema, frame, location, vocabularies, resolver,
                           subschema, instance_location);
    } else if (type_string == "integer") {
      return handle_integer(schema, frame, location, vocabularies, resolver,
                            subschema, instance_location);
    } else if (type_string == "number") {
      return handle_number(schema, frame, location, vocabularies, resolver,
                           subschema, instance_location);
    } else if (type_string == "array") {
      return handle_array(schema, frame, location, vocabularies, resolver,
                          subschema, instance_location);
    } else {
      throw UnsupportedKeywordValue(schema, location.pointer, "type",
                                    "Unsupported type value");
    }
  } else if (subschema.defines("enum")) {
    return handle_enum(schema, frame, location, vocabularies, resolver,
                       subschema, instance_location);
  } else if (subschema.defines("anyOf")) {
    return handle_anyof(schema, frame, location, vocabularies, resolver,
                        subschema, instance_location);
    // Only the recursive case
  } else if (subschema.defines("$ref")) {
    return handle_ref(schema, frame, location, vocabularies, resolver,
                      subschema, instance_location);
  } else {
    throw UnexpectedSchema(schema, location.pointer, "Unsupported subschema");
  }
}

} // namespace sourcemeta::codegen

#endif

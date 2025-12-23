#ifndef SOURCEMETA_CODEGEN_IR_HANDLERS_H_
#define SOURCEMETA_CODEGEN_IR_HANDLERS_H_

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/jsonschema.h>

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

auto handle_string(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::Pointer &pointer,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  ONLY_WHITELIST_KEYWORDS(
      schema, subschema, pointer,
      {"$schema", "$id", "type", "minLength", "maxLength", "pattern"});
  return IRScalar{.pointer = pointer,
                  .instance_location = instance_location,
                  .value = IRScalarType::String};
}

auto handle_object(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::Pointer &pointer,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRObject {
  ONLY_WHITELIST_KEYWORDS(
      schema, subschema, pointer,
      {"$schema", "$id", "type", "properties", "required",
       // Note that most programming languages CANNOT represent the idea
       // of additional properties, mainly if they differ from the types of the
       // other properties. Therefore, we whitelist this, but we consider it to
       // be the responsability of the validator
       "patternProperties", "additionalProperties", "minProperties",
       "maxProperties", "propertyNames"});

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

  for (const auto &[property_name, property_schema, property_hash] :
       properties.as_object()) {
    static_cast<void>(property_hash);
    auto property_pointer{pointer};
    property_pointer.push_back("properties");
    property_pointer.push_back(property_name);

    auto property_instance_location{instance_location};
    property_instance_location.emplace_back(
        sourcemeta::core::Pointer::Token{property_name});

    IRObjectValue member_value{.required = required_set.contains(property_name),
                               .immutable = false,
                               .pointer = property_pointer,
                               .instance_location = property_instance_location};

    members.emplace(property_name, std::move(member_value));
  }

  return IRObject{.pointer = pointer,
                  .instance_location = instance_location,
                  .members = std::move(members)};
}

auto handle_integer(const sourcemeta::core::JSON &schema,
                    const sourcemeta::core::Vocabularies &,
                    const sourcemeta::core::JSON &subschema,
                    const sourcemeta::core::Pointer &pointer,
                    const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, pointer,
                          {"$schema", "$id", "type", "minimum", "maximum",
                           "exclusiveMinimum", "exclusiveMaximum",
                           "multipleOf"});
  return IRScalar{.pointer = pointer,
                  .instance_location = instance_location,
                  .value = IRScalarType::Integer};
}

auto handle_number(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::Pointer &pointer,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, pointer,
                          {"$schema", "$id", "type", "minimum", "maximum",
                           "exclusiveMinimum", "exclusiveMaximum",
                           "multipleOf"});
  return IRScalar{.pointer = pointer,
                  .instance_location = instance_location,
                  .value = IRScalarType::Number};
}

auto handle_array(const sourcemeta::core::JSON &schema,
                  const sourcemeta::core::Vocabularies &,
                  const sourcemeta::core::JSON &,
                  const sourcemeta::core::Pointer &pointer,
                  const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw UnexpectedSchema(schema, pointer,
                         "We do not support this type of subschema yet");
}

auto handle_enum(const sourcemeta::core::JSON &schema,
                 const sourcemeta::core::Vocabularies &,
                 const sourcemeta::core::JSON &subschema,
                 const sourcemeta::core::Pointer &pointer,
                 const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  ONLY_WHITELIST_KEYWORDS(schema, subschema, pointer,
                          {"$schema", "$id", "enum"});
  const auto &enum_json{subschema.at("enum")};

  // Boolean and null special cases
  if (enum_json.size() == 1 && enum_json.at(0).is_null()) {
    return IRScalar{.pointer = pointer,
                    .instance_location = instance_location,
                    .value = IRScalarType::Null};
  } else if (enum_json.size() == 2) {
    const auto &first{enum_json.at(0)};
    const auto &second{enum_json.at(1)};
    if ((first.is_boolean() && second.is_boolean()) &&
        (first.to_boolean() != second.to_boolean())) {
      return IRScalar{.pointer = pointer,
                      .instance_location = instance_location,
                      .value = IRScalarType::Boolean};
    }
  }

  std::vector<sourcemeta::core::JSON> values{enum_json.as_array().cbegin(),
                                             enum_json.as_array().cend()};
  return IRUnion{.pointer = pointer,
                 .instance_location = instance_location,
                 .values = std::move(values)};
}

auto handle_anyof(const sourcemeta::core::JSON &schema,
                  const sourcemeta::core::Vocabularies &,
                  const sourcemeta::core::JSON &,
                  const sourcemeta::core::Pointer &pointer,
                  const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw UnexpectedSchema(schema, pointer,
                         "We do not support this type of subschema yet");
}

auto handle_ref(const sourcemeta::core::JSON &schema,
                const sourcemeta::core::Vocabularies &,
                const sourcemeta::core::JSON &,
                const sourcemeta::core::Pointer &pointer,
                const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw UnexpectedSchema(schema, pointer,
                         "We do not support this type of subschema yet");
}

} // namespace sourcemeta::codegen

#endif

#ifndef SOURCEMETA_CODEGEN_IR_HANDLERS_H_
#define SOURCEMETA_CODEGEN_IR_HANDLERS_H_

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/jsonschema.h>

#include <set>       // std::set
#include <stdexcept> // std::runtime_error

namespace sourcemeta::codegen {

inline auto ONLY_CONTINUE_IF(const bool condition, const char *message)
    -> void {
  if (!condition) {
    throw std::runtime_error(message);
  }
}

auto handle_string(const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  return IRScalar{.instance_location = instance_location,
                  .value = IRScalarType::String};
}

auto handle_object(const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRObject {
  std::unordered_map<sourcemeta::core::JSON::String, IRObjectValue> members;

  if (subschema.defines("properties")) {
    const auto &properties{subschema.at("properties")};

    std::set<std::string> required_set;
    if (subschema.defines("required")) {
      for (const auto &item : subschema.at("required").as_array()) {
        required_set.insert(item.to_string());
      }
    }

    for (const auto &[property_name, property_schema, property_hash] :
         properties.as_object()) {
      static_cast<void>(property_hash);
      auto property_instance_location{instance_location};
      property_instance_location.emplace_back(
          sourcemeta::core::Pointer::Token{property_name});

      IRObjectValue member_value{
          .required = required_set.contains(property_name),
          .immutable = false,
          .instance_location = property_instance_location};

      members.emplace(property_name, std::move(member_value));
    }
  }

  return IRObject{.instance_location = instance_location,
                  .members = std::move(members)};
}

auto handle_schema(const sourcemeta::core::Vocabularies &vocabularies,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  ONLY_CONTINUE_IF(subschema.is_object() && subschema.defines("type"),
                   "Cannot handle subschema without type");

  const auto &type_value{subschema.at("type")};
  ONLY_CONTINUE_IF(type_value.is_string(), "Cannot handle non-string type");

  const auto type_string{type_value.to_string()};

  if (type_string == "string") {
    return handle_string(vocabularies, instance_location);
  }

  if (type_string == "object") {
    return handle_object(vocabularies, subschema, instance_location);
  }

  ONLY_CONTINUE_IF(false, "Unknown type");
  return handle_string(vocabularies, instance_location);
}

} // namespace sourcemeta::codegen

#endif

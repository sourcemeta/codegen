#ifndef SOURCEMETA_CODEGEN_IR_HANDLERS_H_
#define SOURCEMETA_CODEGEN_IR_HANDLERS_H_

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/jsonschema.h>

#include <set> // std::set

namespace sourcemeta::codegen {

auto handle_string(const sourcemeta::core::JSON &,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &,
                   const sourcemeta::core::Pointer &,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  return IRScalar{.instance_location = instance_location,
                  .value = IRScalarType::String};
}

auto handle_object(const sourcemeta::core::JSON &,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::Pointer &,
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

auto handle_integer(const sourcemeta::core::JSON &,
                    const sourcemeta::core::Vocabularies &,
                    const sourcemeta::core::JSON &,
                    const sourcemeta::core::Pointer &,
                    const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  return IRScalar{.instance_location = instance_location,
                  .value = IRScalarType::Integer};
}

auto handle_number(const sourcemeta::core::JSON &,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &,
                   const sourcemeta::core::Pointer &,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IRScalar {
  return IRScalar{.instance_location = instance_location,
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

auto handle_enum(const sourcemeta::core::JSON &,
                 const sourcemeta::core::Vocabularies &,
                 const sourcemeta::core::JSON &subschema,
                 const sourcemeta::core::Pointer &,
                 const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  const auto &enum_json{subschema.at("enum")};

  // Boolean and null special cases
  if (enum_json.size() == 1 && enum_json.at(0).is_null()) {
    return IRScalar{.instance_location = instance_location,
                    .value = IRScalarType::Null};
  } else if (enum_json.size() == 2) {
    const auto &first{enum_json.at(0)};
    const auto &second{enum_json.at(1)};
    if ((first.is_boolean() && second.is_boolean()) &&
        (first.to_boolean() != second.to_boolean())) {
      return IRScalar{.instance_location = instance_location,
                      .value = IRScalarType::Boolean};
    }
  }

  std::vector<sourcemeta::core::JSON> values{enum_json.as_array().cbegin(),
                                             enum_json.as_array().cend()};
  return IRUnion{.instance_location = instance_location,
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

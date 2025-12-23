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

auto handle_string(const sourcemeta::core::JSON &,
                   const sourcemeta::core::Vocabularies &,
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
                    const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw std::runtime_error("TODO: handle_integer");
}

auto handle_number(const sourcemeta::core::JSON &,
                   const sourcemeta::core::Vocabularies &,
                   const sourcemeta::core::JSON &,
                   const sourcemeta::core::Pointer &,
                   const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw std::runtime_error("TODO: handle_number");
}

auto handle_array(const sourcemeta::core::JSON &,
                  const sourcemeta::core::Vocabularies &,
                  const sourcemeta::core::JSON &,
                  const sourcemeta::core::Pointer &,
                  const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw std::runtime_error("TODO: handle_array");
}

auto handle_enum(const sourcemeta::core::JSON &,
                 const sourcemeta::core::Vocabularies &,
                 const sourcemeta::core::JSON &,
                 const sourcemeta::core::Pointer &,
                 const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw std::runtime_error("TODO: handle_enum");
}

auto handle_anyof(const sourcemeta::core::JSON &,
                  const sourcemeta::core::Vocabularies &,
                  const sourcemeta::core::JSON &,
                  const sourcemeta::core::Pointer &,
                  const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw std::runtime_error("TODO: handle_anyof");
}

auto handle_ref(const sourcemeta::core::JSON &,
                const sourcemeta::core::Vocabularies &,
                const sourcemeta::core::JSON &,
                const sourcemeta::core::Pointer &,
                const sourcemeta::core::PointerTemplate &) -> IREntity {
  throw std::runtime_error("TODO: handle_ref");
}

auto handle_schema(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::Vocabularies &vocabularies,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::Pointer &pointer,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  // The canonicaliser ensures that every subschema schema is only in one of the
  // following shapes

  if (subschema.defines("type")) {
    const auto &type_value{subschema.at("type")};
    if (!type_value.is_string()) {
      throw UnexpectedKeywordValue(schema, pointer, "type",
                                   "Expected a string value");
    }

    const auto &type_string{type_value.to_string()};

    // The canonicaliser transforms any other type
    if (type_string == "string") {
      return handle_string(schema, vocabularies, pointer, instance_location);
    } else if (type_string == "object") {
      return handle_object(schema, vocabularies, subschema, pointer,
                           instance_location);
    } else if (type_string == "integer") {
      return handle_integer(schema, vocabularies, subschema, pointer,
                            instance_location);
    } else if (type_string == "number") {
      return handle_number(schema, vocabularies, subschema, pointer,
                           instance_location);
    } else if (type_string == "array") {
      return handle_array(schema, vocabularies, subschema, pointer,
                          instance_location);
    } else {
      throw UnexpectedKeywordValue(schema, pointer, "type",
                                   "Unexpeced type value");
    }
  } else if (subschema.defines("enum")) {
    return handle_enum(schema, vocabularies, subschema, pointer,
                       instance_location);
  } else if (subschema.defines("anyOf")) {
    return handle_anyof(schema, vocabularies, subschema, pointer,
                        instance_location);
    // Only the recursive case
  } else if (subschema.defines("$ref")) {
    return handle_ref(schema, vocabularies, subschema, pointer,
                      instance_location);
  } else {
    throw std::runtime_error("TODO: unknown subschema shape");
  }
}

} // namespace sourcemeta::codegen

#endif

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/alterschema.h>

#include <algorithm> // std::ranges::sort
#include <cassert>   // assert
#include <set>       // std::set
#include <stdexcept> // std::runtime_error

namespace sourcemeta::codegen {

static auto
schema_to_ir(const sourcemeta::core::JSON &subschema,
             const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  if (!subschema.is_object() || !subschema.defines("type")) {
    throw std::runtime_error("Cannot handle subschema without type");
  }

  const auto &type_value{subschema.at("type")};
  if (!type_value.is_string()) {
    throw std::runtime_error("Cannot handle non-string type");
  }

  const auto type_string{type_value.to_string()};

  if (type_string == "string") {
    return IRScalar{.pointer = instance_location,
                    .value = IRScalarType::String};
  }

  if (type_string == "object") {
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

        IRObjectValue member_value{.required =
                                       required_set.contains(property_name),
                                   .immutable = false,
                                   .pointer = property_instance_location};

        members.emplace(property_name, std::move(member_value));
      }
    }

    return IRObject{.pointer = instance_location,
                    .members = std::move(members)};
  }

  throw std::runtime_error("Unknown type: " + type_string);
}

auto compile(
    const sourcemeta::core::JSON &input,
    const sourcemeta::core::SchemaWalker &walker,
    const sourcemeta::core::SchemaResolver &resolver,
    const std::optional<sourcemeta::core::JSON::String> &default_dialect,
    const std::optional<sourcemeta::core::JSON::String> &default_id)
    -> IRResult {
  // --------------------------------------------------------------------------
  // (1) Bundle the schema to resolve external references
  // --------------------------------------------------------------------------

  auto schema{sourcemeta::core::bundle(input, walker, resolver, default_dialect,
                                       default_id)};

  // --------------------------------------------------------------------------
  // (2) Canonicalize the schema for easier analysis
  // --------------------------------------------------------------------------

  sourcemeta::core::SchemaTransformer canonicalizer;
  sourcemeta::core::add(canonicalizer,
                        sourcemeta::core::AlterSchemaMode::Canonicalizer);
  const auto canonicalized{canonicalizer.apply(
      schema, walker, resolver,
      [](const auto &, const auto, const auto, const auto &) {})};
  assert(canonicalized.first);

  // --------------------------------------------------------------------------
  // (3) Frame the resulting schema with instance location information
  // --------------------------------------------------------------------------

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Instances};
  frame.analyse(schema, walker, resolver);

  // --------------------------------------------------------------------------
  // (4) Convert every subschema into a code generation object
  // --------------------------------------------------------------------------

  IRResult result;
  for (const auto &[key, location] : frame.locations()) {
    if (location.type !=
            sourcemeta::core::SchemaFrame::LocationType::Resource &&
        location.type !=
            sourcemeta::core::SchemaFrame::LocationType::Subschema) {
      continue;
    }

    const auto &subschema{sourcemeta::core::get(schema, location.pointer)};
    const auto &instance_locations{frame.instance_locations(location)};
    assert(!instance_locations.empty());
    result.push_back(schema_to_ir(subschema, instance_locations.front()));
  }

  // --------------------------------------------------------------------------
  // (6) Sort entries so that dependencies come before dependents
  // --------------------------------------------------------------------------

  std::ranges::sort(
      result, [](const IREntity &left, const IREntity &right) -> bool {
        return std::visit([](const auto &entry) { return entry.pointer; },
                          right) <
               std::visit([](const auto &entry) { return entry.pointer; },
                          left);
      });

  return result;
}

} // namespace sourcemeta::codegen

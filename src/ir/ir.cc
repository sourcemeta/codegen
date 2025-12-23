#include <sourcemeta/codegen/ir.h>
#include <sourcemeta/codegen/ir_group.h>

#include <sourcemeta/core/alterschema.h>

#include <algorithm> // std::ranges::sort
#include <cassert>   // assert

namespace sourcemeta::codegen {

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
  // (4) Re-group all entries based on their instance locations
  // --------------------------------------------------------------------------

  const auto instance_to_locations{group(frame)};

  // ----- TODO

  IRResult result;

  // Process each instance location group
  for (const auto &[instance_location, entry] : instance_to_locations) {
    for (const auto &group_location : entry.locations) {
      const auto &subschema{
          sourcemeta::core::get(schema, group_location.location.get().pointer)};
      if (!subschema.is_object()) {
        continue;
      }

      const auto vocabularies{
          frame.vocabularies(group_location.location.get(), resolver)};

      if (subschema.defines("type")) {
        const auto &type_result{walker("type", vocabularies)};
        if (type_result.type !=
            sourcemeta::core::SchemaKeywordType::Assertion) {
          continue;
        }

        const auto &type_value{subschema.at("type")};
        if (!type_value.is_string()) {
          continue;
        }

        const auto &type_string{type_value.to_string()};

        if (type_string == "string") {
          result.emplace_back(IRScalar{.pointer = instance_location,
                                       .value = IRScalarType::String});
        } else if (type_string == "object") {
          IRObject object;
          object.pointer = instance_location;

          // Find child instance locations (one property token deeper)
          for (const auto &[child_instance, child_entry] :
               instance_to_locations) {
            if (!child_instance.trivial() || child_instance.empty()) {
              continue;
            }

            // Check if child is exactly one property token deeper
            auto child_size{
                std::distance(child_instance.begin(), child_instance.end())};
            auto parent_size{std::distance(instance_location.begin(),
                                           instance_location.end())};
            if (child_size != parent_size + 1) {
              continue;
            }

            // Verify parent prefix matches
            auto matches{true};
            auto child_iter{child_instance.begin()};
            for (const auto &parent_token : instance_location) {
              if (*child_iter != parent_token) {
                matches = false;
                break;
              }
              ++child_iter;
            }

            if (!matches) {
              continue;
            }

            // Get the property name from the last token
            const auto &last_token{*child_instance.rbegin()};
            if (!std::holds_alternative<sourcemeta::core::Pointer::Token>(
                    last_token)) {
              continue;
            }

            const auto &property_token{
                std::get<sourcemeta::core::Pointer::Token>(last_token)};
            if (!property_token.is_property()) {
              continue;
            }

            object.members.emplace(property_token.to_property(),
                                   IRObjectValue{.required = false,
                                                 .immutable = false,
                                                 .pointer = child_instance});
          }

          result.emplace_back(std::move(object));
        }
      }
    }
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

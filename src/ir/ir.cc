#include <sourcemeta/codegen/ir.h>
#include <sourcemeta/core/alterschema.h>

#include <algorithm> // std::ranges::sort
#include <cassert>   // assert

#include "ir_handlers.h"

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
  // Canonicalization should only consists of transformable rules, so this would
  // never be false and the callback would never be called
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

    // Canonicalisation ensures subschemas are objects or the `false` subschema,
    // in the latter case, we will deal with it in the corresponding containers
    if (!subschema.is_object()) {
      assert(subschema.is_boolean());
      assert(!subschema.to_boolean());
      continue;
    }

    const auto &instance_locations{frame.instance_locations(location)};
    // Canonicalisation is expected to take care of this
    assert(!instance_locations.empty());
    const auto vocabularies{frame.vocabularies(location, resolver)};
    assert(!vocabularies.empty());
    result.push_back(
        handle_schema(vocabularies, subschema, instance_locations.front()));
  }

  // --------------------------------------------------------------------------
  // (6) Sort entries so that dependencies come before dependents
  // --------------------------------------------------------------------------

  std::ranges::sort(
      result, [](const IREntity &left, const IREntity &right) -> bool {
        return std::visit(
                   [](const auto &entry) { return entry.instance_location; },
                   right) <
               std::visit(
                   [](const auto &entry) { return entry.instance_location; },
                   left);
      });

  return result;
}

} // namespace sourcemeta::codegen

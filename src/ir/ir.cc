#include <sourcemeta/codegen/ir.h>
#include <sourcemeta/core/alterschema.h>

#include <algorithm>     // std::ranges::sort
#include <unordered_set> // std::unordered_set

#include "ir_default_compiler.h"

namespace sourcemeta::codegen {

auto compile(
    const sourcemeta::core::JSON &input,
    const sourcemeta::core::SchemaWalker &walker,
    const sourcemeta::core::SchemaResolver &resolver, const Compiler &compiler,
    const sourcemeta::core::SchemaTransformer::Callback &callback,
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
  const auto canonicalized{
      canonicalizer.apply(schema, walker, resolver, callback)};
  if (!canonicalized.first) {
    throw NonCanonicalizableError{};
  }

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
    // Canonicalisation is expected to take care of this
    assert(!instance_locations.empty());

    result.push_back(compiler(schema, frame, location, resolver, subschema,
                              instance_locations.front()));
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

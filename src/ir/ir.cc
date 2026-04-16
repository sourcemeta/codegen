#include <sourcemeta/blaze/alterschema.h>
#include <sourcemeta/codegen/ir.h>

#include <algorithm>     // std::ranges::sort
#include <cassert>       // assert
#include <unordered_set> // std::unordered_set

#include "ir_default_compiler.h"

namespace sourcemeta::codegen {

static auto
is_validation_only_location(const sourcemeta::core::WeakPointer &pointer)
    -> bool {
  static const std::unordered_set<std::string_view> validation_only_keywords{
      "propertyNames", "contains"};
  static const std::unordered_set<std::string_view> container_keywords{
      "properties", "patternProperties", "$defs", "definitions"};
  for (std::size_t index = 0; index < pointer.size(); ++index) {
    const auto &token{pointer.at(index)};
    if (!token.is_property() ||
        !validation_only_keywords.contains(token.to_property())) {
      continue;
    }

    if (index == 0 || !pointer.at(index - 1).is_property() ||
        !container_keywords.contains(pointer.at(index - 1).to_property())) {
      return true;
    }
  }

  return false;
}

auto compile(const sourcemeta::core::JSON &input,
             const sourcemeta::core::SchemaWalker &walker,
             const sourcemeta::core::SchemaResolver &resolver,
             const Compiler &compiler, const std::string_view default_dialect,
             const std::string_view default_id) -> IRResult {
  // --------------------------------------------------------------------------
  // (1) Bundle the schema to resolve external references
  // --------------------------------------------------------------------------

  auto schema{sourcemeta::core::bundle(input, walker, resolver, default_dialect,
                                       default_id)};

  // --------------------------------------------------------------------------
  // (2) Canonicalize the schema for easier analysis
  // --------------------------------------------------------------------------

  sourcemeta::blaze::SchemaTransformer canonicalizer;
  sourcemeta::blaze::add(canonicalizer,
                         sourcemeta::blaze::AlterSchemaMode::Canonicalizer);
  [[maybe_unused]] const auto canonicalized{canonicalizer.apply(
      schema, walker, resolver,
      [](const auto &, const auto, const auto, const auto &,
         [[maybe_unused]] const auto applied) { assert(applied); },
      default_dialect, default_id)};
  assert(canonicalized.first);

  // --------------------------------------------------------------------------
  // (3) Frame the resulting schema with instance location information
  // --------------------------------------------------------------------------

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::References};
  frame.analyse(schema, walker, resolver, default_dialect, default_id);

  // --------------------------------------------------------------------------
  // (4) Convert every subschema into a code generation object
  // --------------------------------------------------------------------------

  std::unordered_set<sourcemeta::core::WeakPointer,
                     sourcemeta::core::WeakPointer::Hasher,
                     sourcemeta::core::WeakPointer::Comparator>
      visited;
  IRResult result;
  for (const auto &[key, location] : frame.locations()) {
    if (location.type !=
            sourcemeta::core::SchemaFrame::LocationType::Resource &&
        location.type !=
            sourcemeta::core::SchemaFrame::LocationType::Subschema) {
      continue;
    }

    // Framing may report resource twice or more given default identifiers and
    // nested resources
    const auto [visited_iterator, inserted] = visited.insert(location.pointer);
    if (!inserted) {
      continue;
    }

    // Skip subschemas under validation-only keywords that do not contribute
    // to the type structure
    if (is_validation_only_location(location.pointer)) {
      continue;
    }

    const auto &subschema{sourcemeta::core::get(schema, location.pointer)};
    result.push_back(compiler(schema, frame, location, resolver, subschema));
  }

  // --------------------------------------------------------------------------
  // (5) Sort entries so that dependencies come before dependents
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

#ifndef SOURCEMETA_CODEGEN_IR_H_
#define SOURCEMETA_CODEGEN_IR_H_

#ifndef SOURCEMETA_CODEGEN_IR_EXPORT
#include <sourcemeta/codegen/ir_export.h>
#endif

// NOLINTBEGIN(misc-include-cleaner)
#include <sourcemeta/codegen/ir_error.h>
// NOLINTEND(misc-include-cleaner)

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <cstdint>       // std::uint8_t
#include <functional>    // std::function
#include <optional>      // std::optional, std::nullopt
#include <unordered_map> // std::unordered_map
#include <variant>       // std::variant
#include <vector>        // std::vector

/// @defgroup ir IR
/// @brief The codegen JSON Schema intermediary format

namespace sourcemeta::codegen {

/// @ingroup ir
enum class IRScalarType : std::uint8_t {
  String,
  Number,
  Integer,
  Boolean,
  Null
};

/// @ingroup ir
struct IRScalar {
  sourcemeta::core::Pointer pointer;
  sourcemeta::core::PointerTemplate instance_location;
  IRScalarType value;
};

/// @ingroup ir
struct IRUnion {
  sourcemeta::core::Pointer pointer;
  sourcemeta::core::PointerTemplate instance_location;
  std::vector<sourcemeta::core::JSON> values;
};

/// @ingroup ir
struct IRObjectValue {
  bool required;
  bool immutable;
  sourcemeta::core::Pointer pointer;
  sourcemeta::core::PointerTemplate instance_location;
};

/// @ingroup ir
struct IRObject {
  sourcemeta::core::Pointer pointer;
  sourcemeta::core::PointerTemplate instance_location;
  std::unordered_map<sourcemeta::core::JSON::String, IRObjectValue> members;
  std::optional<IRObjectValue> additional;
};

/// @ingroup ir
struct IRImpossible {
  sourcemeta::core::Pointer pointer;
  sourcemeta::core::PointerTemplate instance_location;
};

/// @ingroup ir
using IREntity = std::variant<IRObject, IRScalar, IRUnion, IRImpossible>;

/// @ingroup ir
using IRResult = std::vector<IREntity>;

/// @ingroup ir
using Compiler = std::function<IREntity(
    const sourcemeta::core::JSON &, const sourcemeta::core::Vocabularies &,
    const sourcemeta::core::JSON &, const sourcemeta::core::Pointer &,
    const sourcemeta::core::PointerTemplate &)>;

/// @ingroup ir
SOURCEMETA_CODEGEN_IR_EXPORT
auto default_compiler(
    const sourcemeta::core::JSON &schema,
    const sourcemeta::core::Vocabularies &vocabularies,
    const sourcemeta::core::JSON &subschema,
    const sourcemeta::core::Pointer &pointer,
    const sourcemeta::core::PointerTemplate &instance_location) -> IREntity;

/// @ingroup ir
SOURCEMETA_CODEGEN_IR_EXPORT
auto compile(const sourcemeta::core::JSON &schema,
             const sourcemeta::core::SchemaWalker &walker,
             const sourcemeta::core::SchemaResolver &resolver,
             const Compiler &compiler,
             const std::optional<sourcemeta::core::JSON::String>
                 &default_dialect = std::nullopt,
             const std::optional<sourcemeta::core::JSON::String> &default_id =
                 std::nullopt) -> IRResult;

} // namespace sourcemeta::codegen

#endif

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
  sourcemeta::core::PointerTemplate instance_location;
  IRScalarType value;
};

/// @ingroup ir
struct IRUnion {
  sourcemeta::core::PointerTemplate instance_location;
  std::vector<sourcemeta::core::JSON> values;
};

/// @ingroup ir
struct IRObjectValue {
  bool required;
  bool immutable;
  sourcemeta::core::PointerTemplate instance_location;
};

/// @ingroup ir
struct IRObject {
  sourcemeta::core::PointerTemplate instance_location;
  std::unordered_map<sourcemeta::core::JSON::String, IRObjectValue> members;
};

/// @ingroup ir
using IREntity = std::variant<IRObject, IRScalar, IRUnion>;

/// @ingroup ir
using IRResult = std::vector<IREntity>;

/// @ingroup ir
SOURCEMETA_CODEGEN_IR_EXPORT
auto compile(const sourcemeta::core::JSON &schema,
             const sourcemeta::core::SchemaWalker &walker,
             const sourcemeta::core::SchemaResolver &resolver,
             const std::optional<sourcemeta::core::JSON::String>
                 &default_dialect = std::nullopt,
             const std::optional<sourcemeta::core::JSON::String> &default_id =
                 std::nullopt) -> IRResult;

} // namespace sourcemeta::codegen

#endif

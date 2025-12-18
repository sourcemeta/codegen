#ifndef SOURCEMETA_CODEGEN_IR_H_
#define SOURCEMETA_CODEGEN_IR_H_

#ifndef SOURCEMETA_CODEGEN_IR_EXPORT
#include <sourcemeta/codegen/ir_export.h>
#endif

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
enum class IRScalarType : std::uint8_t { String };

/// @ingroup ir
struct IRObjectValue {
  bool required;
  bool immutable;
  sourcemeta::core::PointerTemplate pointer;
};

/// @ingroup ir
struct IRScalar {
  sourcemeta::core::PointerTemplate pointer;
  IRScalarType value;
};

/// @ingroup ir
struct IRObject {
  sourcemeta::core::PointerTemplate pointer;
  std::unordered_map<sourcemeta::core::JSON::String, IRObjectValue> members;
};

/// @ingroup ir
using IREntity = std::variant<IRObject, IRScalar>;

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

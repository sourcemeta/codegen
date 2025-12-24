#ifndef SOURCEMETA_CODEGEN_GENERATOR_H_
#define SOURCEMETA_CODEGEN_GENERATOR_H_

#ifndef SOURCEMETA_CODEGEN_GENERATOR_EXPORT
#include <sourcemeta/codegen/generator_export.h>
#endif

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/jsonpointer.h>

#include <optional> // std::optional, std::nullopt
#include <ostream>  // std::ostream
#include <string>   // std::string

/// @defgroup generator Generator
/// @brief The codegen JSON Schema code generation package

namespace sourcemeta::codegen {

/// @ingroup generator
SOURCEMETA_CODEGEN_GENERATOR_EXPORT
auto to_pascal_case(const sourcemeta::core::PointerTemplate &instance_location,
                    const std::string &prefix) -> std::string;

/// @ingroup generator
SOURCEMETA_CODEGEN_GENERATOR_EXPORT
auto typescript(std::ostream &output, const IRResult &result,
                const std::optional<std::string> &default_prefix = std::nullopt)
    -> void;

} // namespace sourcemeta::codegen

#endif

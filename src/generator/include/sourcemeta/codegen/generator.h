#ifndef SOURCEMETA_CODEGEN_GENERATOR_H_
#define SOURCEMETA_CODEGEN_GENERATOR_H_

#ifndef SOURCEMETA_CODEGEN_GENERATOR_EXPORT
#include <sourcemeta/codegen/generator_export.h>
#endif

// NOLINTBEGIN(misc-include-cleaner)
#include <sourcemeta/codegen/generator_typescript.h>
// NOLINTEND(misc-include-cleaner)

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/jsonpointer.h>

#include <ostream> // std::ostream
#include <string>  // std::string
#include <variant> // std::visit

/// @defgroup generator Generator
/// @brief The codegen JSON Schema code generation package

namespace sourcemeta::codegen {

/// @ingroup generator
template <typename T>
auto generate(std::ostream &output, const IRResult &result,
              const std::string &prefix = "Schema") -> void {
  const T visitor{output, prefix};
  const char *separator{""};
  for (const auto &entity : result) {
    output << separator;
    separator = "\n";
    std::visit(visitor, entity);
  }
}

} // namespace sourcemeta::codegen

#endif

#ifndef SOURCEMETA_CODEGEN_GENERATOR_H_
#define SOURCEMETA_CODEGEN_GENERATOR_H_

#ifndef SOURCEMETA_CODEGEN_GENERATOR_EXPORT
#include <sourcemeta/codegen/generator_export.h>
#endif

#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/jsonpointer.h>

#include <ostream> // std::ostream
#include <string>  // std::string
#include <variant> // std::visit

/// @defgroup generator Generator
/// @brief The codegen JSON Schema code generation package

namespace sourcemeta::codegen {

/// @ingroup generator
SOURCEMETA_CODEGEN_GENERATOR_EXPORT
auto to_pascal_case(const sourcemeta::core::PointerTemplate &instance_location,
                    const std::string &prefix) -> std::string;

/// @ingroup generator
template <typename T>
auto generate(std::ostream &output, const IRResult &result,
              const std::string &prefix) -> void {
  const T visitor{output, prefix};
  const char *separator{""};
  for (const auto &entity : result) {
    output << separator;
    separator = "\n";
    std::visit(visitor, entity);
  }
}

/// @ingroup generator
class SOURCEMETA_CODEGEN_GENERATOR_EXPORT TypeScript {
public:
  TypeScript(std::ostream &stream, const std::string &type_prefix);
  auto operator()(const IRScalar &entry) const -> void;
  auto operator()(const IREnumeration &entry) const -> void;
  auto operator()(const IRObject &entry) const -> void;
  auto operator()(const IRImpossible &entry) const -> void;
  auto operator()(const IRArray &entry) const -> void;
  auto operator()(const IRReference &entry) const -> void;
  auto operator()(const IRTuple &entry) const -> void;
  auto operator()(const IRUnion &entry) const -> void;

private:
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  std::ostream &output;
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  const std::string &prefix;
};

} // namespace sourcemeta::codegen

#endif

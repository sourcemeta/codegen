#ifndef SOURCEMETA_CODEGEN_GENERATOR_TYPESCRIPT_H_
#define SOURCEMETA_CODEGEN_GENERATOR_TYPESCRIPT_H_

#ifndef SOURCEMETA_CODEGEN_GENERATOR_EXPORT
#include <sourcemeta/codegen/generator_export.h>
#endif

#include <sourcemeta/codegen/ir.h>

#include <ostream> // std::ostream
#include <string>  // std::string

namespace sourcemeta::codegen {

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

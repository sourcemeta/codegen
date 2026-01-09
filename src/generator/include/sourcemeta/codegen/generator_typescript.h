#ifndef SOURCEMETA_CODEGEN_GENERATOR_TYPESCRIPT_H_
#define SOURCEMETA_CODEGEN_GENERATOR_TYPESCRIPT_H_

#ifndef SOURCEMETA_CODEGEN_GENERATOR_EXPORT
#include <sourcemeta/codegen/generator_export.h>
#endif

#include <sourcemeta/codegen/ir.h>

#include <ostream>     // std::ostream
#include <string_view> // std::string_view

namespace sourcemeta::codegen {

/// @ingroup generator
class SOURCEMETA_CODEGEN_GENERATOR_EXPORT TypeScript {
public:
  TypeScript(std::ostream &stream, std::string_view type_prefix);
  auto operator()(const IRScalar &entry) const -> void;
  auto operator()(const IREnumeration &entry) const -> void;
  auto operator()(const IRObject &entry) const -> void;
  auto operator()(const IRImpossible &entry) const -> void;
  auto operator()(const IRArray &entry) const -> void;
  auto operator()(const IRReference &entry) const -> void;
  auto operator()(const IRTuple &entry) const -> void;
  auto operator()(const IRUnion &entry) const -> void;

private:
// Exporting symbols that depends on the standard C++ library is considered
// safe.
// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275?view=msvc-170&redirectedfrom=MSDN
#if defined(_MSC_VER)
#pragma warning(disable : 4251)
#endif
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  std::ostream &output;
  std::string_view prefix;
#if defined(_MSC_VER)
#pragma warning(default : 4251)
#endif
};

} // namespace sourcemeta::codegen

#endif

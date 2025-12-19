#ifndef SOURCEMETA_CODEGEN_IR_GROUP_H_
#define SOURCEMETA_CODEGEN_IR_GROUP_H_

#ifndef SOURCEMETA_CODEGEN_IR_EXPORT
#include <sourcemeta/codegen/ir_export.h>
#endif

#include <sourcemeta/core/jsonpointer.h>
#include <sourcemeta/core/jsonschema.h>

#include <functional> // std::reference_wrapper
#include <map>        // std::map
#include <vector>     // std::vector

namespace sourcemeta::codegen {

/// @ingroup ir
struct IRGroupLocation {
  std::reference_wrapper<const sourcemeta::core::PointerTemplate>
      instance_location;
  std::reference_wrapper<const sourcemeta::core::SchemaFrame::Location>
      location;
};

/// @ingroup ir
struct IRGroupEntry {
  std::vector<IRGroupLocation> locations;
};

/// @ingroup ir
using IRGroup = std::map<sourcemeta::core::PointerTemplate, IRGroupEntry>;

/// @ingroup ir
SOURCEMETA_CODEGEN_IR_EXPORT
auto group(const sourcemeta::core::SchemaFrame &frame) -> IRGroup;

} // namespace sourcemeta::codegen

#endif

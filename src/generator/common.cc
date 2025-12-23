#include <sourcemeta/codegen/generator.h>

namespace sourcemeta::codegen {

auto to_pascal_case(const sourcemeta::core::Pointer &,
                    const sourcemeta::core::PointerTemplate &instance_location,
                    const std::string &default_namespace) -> std::string {
  if (instance_location.empty()) {
    return default_namespace;
  }

  std::string result;
  for (const auto &token : instance_location) {
    if (!result.empty()) {
      result += "_";
    }
    const auto &property_token{
        std::get<sourcemeta::core::Pointer::Token>(token)};
    result += property_token.to_property();
  }
  return result;
}

} // namespace sourcemeta::codegen

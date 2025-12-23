#include <sourcemeta/codegen/generator.h>

#include <stdexcept> // std::runtime_error

namespace sourcemeta::codegen {

auto safe_name(const sourcemeta::core::Pointer &,
               const sourcemeta::core::PointerTemplate &instance_location,
               const std::optional<std::string> &default_namespace)
    -> std::string {
  if (instance_location.empty()) {
    if (!default_namespace.has_value()) {
      throw std::runtime_error(
          "Empty pointer without default namespace provided");
    }
    return default_namespace.value();
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

#include <sourcemeta/codegen/generator.h>

#include <cctype>  // std::isalpha, std::isdigit, std::toupper
#include <iomanip> // std::setfill, std::setw
#include <sstream> // std::ostringstream

namespace sourcemeta::codegen {

// Helper to convert a string to PascalCase with hex-escaped special characters
static auto string_to_pascal_case(const std::string &input) -> std::string {
  std::ostringstream result;
  bool capitalize_next{true};
  for (const char character : input) {
    if (std::isalpha(static_cast<unsigned char>(character)) != 0) {
      if (capitalize_next) {
        result << static_cast<char>(
            std::toupper(static_cast<unsigned char>(character)));
        capitalize_next = false;
      } else {
        result << character;
      }
    } else if (std::isdigit(static_cast<unsigned char>(character)) != 0) {
      result << character;
    } else {
      result << 'X' << std::uppercase << std::hex << std::setfill('0')
             << std::setw(2)
             << static_cast<unsigned int>(
                    static_cast<unsigned char>(character));
      capitalize_next = true;
    }
  }
  return result.str();
}

auto to_pascal_case(const sourcemeta::core::Pointer &,
                    const sourcemeta::core::PointerTemplate &instance_location,
                    const std::string &default_namespace) -> std::string {
  // Convert namespace to PascalCase
  std::string result{string_to_pascal_case(default_namespace)};

  if (instance_location.empty()) {
    return result;
  }

  for (const auto &token : instance_location) {
    const auto &property_token{
        std::get<sourcemeta::core::Pointer::Token>(token)};
    const auto &property{property_token.to_property()};

    // Convert token to PascalCase
    std::string token_pascal{string_to_pascal_case(property)};

    // Skip empty tokens
    if (token_pascal.empty()) {
      continue;
    }

    // If token starts with digit, prepend underscore for valid identifier
    if (std::isdigit(static_cast<unsigned char>(token_pascal[0])) != 0) {
      result += '_';
    }

    result += token_pascal;
  }

  return result;
}

} // namespace sourcemeta::codegen

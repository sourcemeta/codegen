#include <sourcemeta/codegen/generator.h>

#include <cassert> // assert
#include <cctype> // std::isalpha, std::isdigit, std::islower, std::isupper, std::toupper
#include <iomanip> // std::setfill, std::setw
#include <sstream> // std::ostringstream

namespace sourcemeta::codegen {

static auto hex_escape(std::ostringstream &output, char character) -> void {
  output << 'X' << std::uppercase << std::hex << std::setfill('0')
         << std::setw(2)
         << static_cast<unsigned int>(static_cast<unsigned char>(character));
}

// Encode a string to a collision-free PascalCase identifier
// Rules:
// - Lowercase at segment start: capitalize (no marker) - common case
// - Uppercase at segment start (except X, U): U + letter
// - Uppercase X at segment start: X58 (hex escape)
// - Uppercase U at segment start: X55 (hex escape)
// - Non-segment-start lowercase: as-is
// - Non-segment-start uppercase (except X, U): as-is
// - Non-segment-start X: X58, Non-segment-start U: X55
// - Digits: as-is
// - Non-alphanumeric: hex escape, starts new segment
static auto encode_string(const std::string &input) -> std::string {
  std::ostringstream result;
  bool segment_start{true};

  for (const char character : input) {
    const auto unsigned_char{static_cast<unsigned char>(character)};

    if (std::isalpha(unsigned_char) != 0) {
      if (segment_start) {
        if (character == 'X' || character == 'U' || character == 'x' ||
            character == 'u') {
          hex_escape(result, character);
        } else if (std::islower(unsigned_char) != 0) {
          result << static_cast<char>(std::toupper(unsigned_char));
        } else {
          result << 'U' << character;
        }
      } else {
        if (character == 'X' || character == 'U') {
          hex_escape(result, character);
        } else {
          result << character;
        }
      }
      segment_start = false;
    } else if (std::isdigit(unsigned_char) != 0) {
      result << character;
      segment_start = false;
    } else {
      hex_escape(result, character);
      segment_start = true;
    }
  }

  return result.str();
}

auto to_pascal_case(const sourcemeta::core::PointerTemplate &instance_location,
                    const std::string &default_namespace) -> std::string {
  assert(!default_namespace.empty());
  std::string result{default_namespace};
  const auto first_char{static_cast<unsigned char>(result[0])};
  if (std::islower(first_char) != 0) {
    result[0] = static_cast<char>(std::toupper(first_char));
  }

  if (instance_location.empty()) {
    return result;
  }

  for (const auto &token : instance_location) {
    if (const auto *property_token =
            std::get_if<sourcemeta::core::Pointer::Token>(&token)) {
      const auto &property{property_token->to_property()};
      std::string encoded{encode_string(property)};
      if (!encoded.empty()) {
        result += '_';
        result += encoded;
      }
    } else if (const auto *wildcard =
                   std::get_if<sourcemeta::core::PointerTemplate::Wildcard>(
                       &token)) {
      result += '_';
      switch (*wildcard) {
        case sourcemeta::core::PointerTemplate::Wildcard::Property:
          result += "AnyProperty";
          break;
        case sourcemeta::core::PointerTemplate::Wildcard::Item:
          result += "AnyItem";
          break;
        case sourcemeta::core::PointerTemplate::Wildcard::Key:
          result += "AnyKey";
          break;
      }
    } else if (const auto *condition =
                   std::get_if<sourcemeta::core::PointerTemplate::Condition>(
                       &token)) {
      result += "_Maybe";
      if (condition->suffix.has_value()) {
        result += encode_string(condition->suffix.value());
      }
    } else if (std::holds_alternative<
                   sourcemeta::core::PointerTemplate::Negation>(token)) {
      result += "_Not";
    } else if (const auto *regex =
                   std::get_if<sourcemeta::core::PointerTemplate::Regex>(
                       &token)) {
      result += "_Regex";
      result += encode_string(*regex);
    }
  }

  return result;
}

} // namespace sourcemeta::codegen

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
// - Lowercase at segment start (except x, u, z): capitalize (no marker)
// - Lowercase x, u, z at segment start: hex escape (reserved characters)
// - Uppercase at segment start (except X, U, Z): U + letter
// - Uppercase X, U, Z at segment start: hex escape (reserved characters)
// - Non-segment-start lowercase: as-is
// - Non-segment-start uppercase (except X, U): as-is
// - Non-segment-start X: X58, Non-segment-start U: X55
// - Digits: as-is
// - Non-alphanumeric: hex escape, starts new segment
// Note: Z/z reserved for special token prefixes (ZNot, ZMaybe, ZAnyProperty,
// etc.)
static auto encode_string(const std::string &input) -> std::string {
  std::ostringstream result;
  bool segment_start{true};

  for (const char character : input) {
    const auto unsigned_char{static_cast<unsigned char>(character)};

    if (std::isalpha(unsigned_char) != 0) {
      if (segment_start) {
        if (character == 'X' || character == 'U' || character == 'x' ||
            character == 'u' || character == 'Z' || character == 'z') {
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
      // Non-ASCII bytes (>= 0x80) don't start new segments (UTF-8 continuation)
      // ASCII special characters (< 0x80) do start new segments
      segment_start = (unsigned_char < 0x80);
    }
  }

  return result.str();
}

auto to_pascal_case(const sourcemeta::core::PointerTemplate &instance_location,
                    const std::string &prefix) -> std::string {
  assert(!prefix.empty());
  std::string result{prefix};
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
      result += '_';
      if (property.empty()) {
        result += "ZEmpty";
      } else {
        result += encode_string(property);
      }
    } else if (const auto *wildcard =
                   std::get_if<sourcemeta::core::PointerTemplate::Wildcard>(
                       &token)) {
      result += '_';
      switch (*wildcard) {
        case sourcemeta::core::PointerTemplate::Wildcard::Property:
          result += "ZAnyProperty";
          break;
        case sourcemeta::core::PointerTemplate::Wildcard::Item:
          result += "ZAnyItem";
          break;
        case sourcemeta::core::PointerTemplate::Wildcard::Key:
          result += "ZAnyKey";
          break;
      }
    } else if (const auto *condition =
                   std::get_if<sourcemeta::core::PointerTemplate::Condition>(
                       &token)) {
      result += "_ZMaybe";
      if (condition->suffix.has_value()) {
        const auto &suffix_value{condition->suffix.value()};
        if (suffix_value.empty()) {
          result += "ZEmpty";
        } else {
          result += encode_string(suffix_value);
        }
      }
    } else if (std::holds_alternative<
                   sourcemeta::core::PointerTemplate::Negation>(token)) {
      result += "_ZNot";
    } else if (const auto *regex =
                   std::get_if<sourcemeta::core::PointerTemplate::Regex>(
                       &token)) {
      result += "_ZRegex";
      if (regex->empty()) {
        result += "ZEmpty";
      } else {
        result += encode_string(*regex);
      }
    }
  }

  return result;
}

} // namespace sourcemeta::codegen

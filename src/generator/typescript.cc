#include <sourcemeta/codegen/generator.h>

#include <sstream> // std::ostringstream

namespace {

// TODO: Move to Core
auto escape_string(const std::string &input) -> std::string {
  std::ostringstream result;
  for (const auto character : input) {
    switch (character) {
      case '\\':
        result << "\\\\";
        break;
      case '"':
        result << "\\\"";
        break;
      case '\n':
        result << "\\n";
        break;
      case '\r':
        result << "\\r";
        break;
      case '\t':
        result << "\\t";
        break;
      default:
        result << character;
        break;
    }
  }

  return result.str();
}

} // namespace

namespace sourcemeta::codegen {

TypeScript::TypeScript(std::ostream &stream, const std::string_view type_prefix)
    : output{stream}, prefix{type_prefix} {}

auto TypeScript::operator()(const IRScalar &entry) const -> void {
  this->output << "export type "
               << sourcemeta::core::mangle(entry.pointer, this->prefix)
               << " = ";

  switch (entry.value) {
    case IRScalarType::String:
      this->output << "string";
      break;
    case IRScalarType::Number:
    case IRScalarType::Integer:
      this->output << "number";
      break;
    case IRScalarType::Boolean:
      this->output << "boolean";
      break;
    case IRScalarType::Null:
      this->output << "null";
      break;
  }

  this->output << ";\n";
}

auto TypeScript::operator()(const IREnumeration &entry) const -> void {
  this->output << "export type "
               << sourcemeta::core::mangle(entry.pointer, this->prefix)
               << " = ";

  const char *separator{""};
  for (const auto &value : entry.values) {
    this->output << separator;
    sourcemeta::core::prettify(value, this->output);
    separator = " | ";
  }

  this->output << ";\n";
}

auto TypeScript::operator()(const IRObject &entry) const -> void {
  const auto type_name{sourcemeta::core::mangle(entry.pointer, this->prefix)};
  const auto has_additional{entry.additional.has_value()};

  if (has_additional && entry.members.empty()) {
    this->output << "export type " << type_name << " = Record<string, "
                 << sourcemeta::core::mangle(entry.additional->pointer,
                                             this->prefix)
                 << ">;\n";
    return;
  }

  this->output << "export interface " << type_name << " {\n";

  // We always quote property names for safety. JSON Schema allows any string
  // as a property name, but unquoted TypeScript/ECMAScript property names
  // must be valid IdentifierName productions (see ECMA-262 section 12.7).
  // Quoting allows any string to be used as a property name.
  // See: https://tc39.es/ecma262/#sec-names-and-keywords
  // See: https://mathiasbynens.be/notes/javascript-properties
  for (const auto &[member_name, member_value] : entry.members) {
    const auto optional_marker{member_value.required ? "" : "?"};
    const auto readonly_marker{member_value.immutable ? "readonly " : ""};

    this->output << "  " << readonly_marker << "\""
                 << escape_string(member_name) << "\"" << optional_marker
                 << ": "
                 << sourcemeta::core::mangle(member_value.pointer, this->prefix)
                 << ";\n";
  }

  if (has_additional) {
    // TypeScript index signatures must be a supertype of all property value
    // types. We use a union of all member types plus the additional properties
    // type plus undefined (for optional properties).
    this->output << "  [key: string]:\n";
    for (const auto &[member_name, member_value] : entry.members) {
      this->output << "    "
                   << sourcemeta::core::mangle(member_value.pointer,
                                               this->prefix)
                   << " |\n";
    }
    this->output << "    "
                 << sourcemeta::core::mangle(entry.additional->pointer,
                                             this->prefix)
                 << " |\n";
    this->output << "    undefined;\n";
  }

  this->output << "}\n";
}

auto TypeScript::operator()(const IRImpossible &entry) const -> void {
  this->output << "export type "
               << sourcemeta::core::mangle(entry.pointer, this->prefix)
               << " = never;\n";
}

auto TypeScript::operator()(const IRArray &entry) const -> void {
  this->output << "export type "
               << sourcemeta::core::mangle(entry.pointer, this->prefix)
               << " = ";

  if (entry.items.has_value()) {
    this->output << sourcemeta::core::mangle(entry.items->pointer, this->prefix)
                 << "[]";
  } else {
    this->output << "unknown[]";
  }

  this->output << ";\n";
}

auto TypeScript::operator()(const IRReference &entry) const -> void {
  this->output << "export type "
               << sourcemeta::core::mangle(entry.pointer, this->prefix) << " = "
               << sourcemeta::core::mangle(entry.target.pointer, this->prefix)
               << ";\n";
}

auto TypeScript::operator()(const IRTuple &entry) const -> void {
  this->output << "export type "
               << sourcemeta::core::mangle(entry.pointer, this->prefix)
               << " = [";

  const char *separator{""};
  for (const auto &item : entry.items) {
    this->output << separator
                 << sourcemeta::core::mangle(item.pointer, this->prefix);
    separator = ", ";
  }

  if (entry.additional.has_value()) {
    this->output << separator << "..."
                 << sourcemeta::core::mangle(entry.additional->pointer,
                                             this->prefix)
                 << "[]";
  }

  this->output << "];\n";
}

auto TypeScript::operator()(const IRUnion &entry) const -> void {
  this->output << "export type "
               << sourcemeta::core::mangle(entry.pointer, this->prefix)
               << " =\n";

  const char *separator{""};
  for (const auto &value : entry.values) {
    this->output << separator << "  "
                 << sourcemeta::core::mangle(value.pointer, this->prefix);
    separator = " |\n";
  }

  this->output << ";\n";
}

} // namespace sourcemeta::codegen

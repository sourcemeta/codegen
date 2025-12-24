#include <sourcemeta/codegen/generator.h>

#include <variant> // std::visit

namespace sourcemeta::codegen {

static auto scalar_type_to_typescript(IRScalarType type) -> std::string {
  switch (type) {
    case IRScalarType::String:
      return "string";
    default:
      return "unknown";
  }
}

class TypeScriptGenerator {
public:
  TypeScriptGenerator(std::ostream &stream, const std::string &type_prefix)
      : output{stream}, prefix{type_prefix} {}

  auto operator()(const IRScalar &entry) const -> void {
    this->output << "export type "
                 << to_pascal_case(entry.instance_location, this->prefix)
                 << " = " << scalar_type_to_typescript(entry.value) << ";\n";
  }

  auto operator()(const IREnumeration &entry) const -> void {
    this->output << "export type "
                 << to_pascal_case(entry.instance_location, this->prefix)
                 << " = ";

    const char *separator{""};
    for (const auto &value : entry.values) {
      this->output << separator;
      sourcemeta::core::prettify(value, this->output);
      separator = " | ";
    }

    this->output << ";\n";
  }

  auto operator()(const IRObject &entry) const -> void {
    this->output << "export interface "
                 << to_pascal_case(entry.instance_location, this->prefix)
                 << " {\n";
    for (const auto &[member_name, member_value] : entry.members) {
      const auto optional_marker{member_value.required ? "" : "?"};
      const auto readonly_marker{member_value.immutable ? "readonly " : ""};
      // TODO: Throw an error if this member name cannot be represented
      this->output << "  " << readonly_marker << member_name << optional_marker
                   << ": "
                   << to_pascal_case(member_value.instance_location,
                                     this->prefix)
                   << ";\n";
    }

    this->output << "}\n";
  }

  auto operator()(const IRImpossible &entry) const -> void {
    this->output << "export type "
                 << to_pascal_case(entry.instance_location, this->prefix)
                 << " = never;\n";
  }

  auto operator()(const IRArray &entry) const -> void {
    this->output << "export type "
                 << to_pascal_case(entry.instance_location, this->prefix)
                 << " = "
                 << to_pascal_case(entry.items.instance_location, this->prefix)
                 << "[];\n";
  }

  auto operator()(const IRReference &entry) const -> void {
    this->output << "export type "
                 << to_pascal_case(entry.instance_location, this->prefix)
                 << " = "
                 << to_pascal_case(entry.target.instance_location, this->prefix)
                 << ";\n";
  }

  auto operator()(const IRTuple &entry) const -> void {
    this->output << "export type "
                 << to_pascal_case(entry.instance_location, this->prefix)
                 << " = [";

    const char *separator{""};
    for (const auto &item : entry.items) {
      this->output << separator
                   << to_pascal_case(item.instance_location, this->prefix);
      separator = ", ";
    }

    if (entry.additional.has_value()) {
      this->output << separator << "..."
                   << to_pascal_case(entry.additional->instance_location,
                                     this->prefix)
                   << "[]";
    }

    this->output << "];\n";
  }

  auto operator()(const IRUnion &) const -> void {
    // TODO: Implement IRUnion support
  }

private:
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  std::ostream &output;
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
  const std::string &prefix;
};

auto typescript(std::ostream &output, const IRResult &result,
                const std::optional<std::string> &default_prefix) -> void {
  const std::string prefix{default_prefix.value_or("Schema")};
  const TypeScriptGenerator visitor{output, prefix};
  const char *separator{""};
  for (const auto &entity : result) {
    output << separator;
    separator = "\n";
    std::visit(visitor, entity);
  }
}

} // namespace sourcemeta::codegen

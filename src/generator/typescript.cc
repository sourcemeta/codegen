#include <sourcemeta/codegen/generator.h>

namespace sourcemeta::codegen {

static auto scalar_type_to_typescript(IRScalarType type) -> std::string {
  switch (type) {
    case IRScalarType::String:
      return "string";
    default:
      return "unknown";
  }
}

static auto handle_ir_scalar(std::ostream &output, const IRScalar &entry,
                             const std::string &default_namespace) -> void {
  output << "export type "
         << to_pascal_case(entry.instance_location, default_namespace) << " = "
         << scalar_type_to_typescript(entry.value) << ";\n";
}

static auto handle_ir_enumeration(std::ostream &output,
                                  const IREnumeration &entry,
                                  const std::string &default_namespace)
    -> void {
  output << "export type "
         << to_pascal_case(entry.instance_location, default_namespace) << " = ";

  const char *separator{""};
  for (const auto &value : entry.values) {
    output << separator;
    sourcemeta::core::stringify(value, output);
    separator = " | ";
  }

  output << ";\n";
}

static auto handle_ir_object(std::ostream &output, const IRObject &entry,
                             const std::string &default_namespace) -> void {
  output << "export interface "
         << to_pascal_case(entry.instance_location, default_namespace)
         << " {\n";
  for (const auto &[member_name, member_value] : entry.members) {
    const auto optional_marker{member_value.required ? "" : "?"};
    const auto readonly_marker{member_value.immutable ? "readonly " : ""};
    output << "  "
           << readonly_marker
           // TODO: Throw an error if this member name cannot be represented
           << member_name << optional_marker << ": "
           << to_pascal_case(member_value.instance_location, default_namespace)
           << ";\n";
  }

  output << "}\n";
}

static auto handle_ir_impossible(std::ostream &output,
                                 const IRImpossible &entry,
                                 const std::string &default_namespace) -> void {
  output << "export type "
         << to_pascal_case(entry.instance_location, default_namespace)
         << " = never;\n";
}

static auto handle_ir_array(std::ostream &output, const IRArray &entry,
                            const std::string &default_namespace) -> void {
  output << "export type "
         << to_pascal_case(entry.instance_location, default_namespace) << " = "
         << to_pascal_case(entry.items.instance_location, default_namespace)
         << "[];\n";
}

static auto handle_ir_reference(std::ostream &output, const IRReference &entry,
                                const std::string &default_namespace) -> void {
  output << "export type "
         << to_pascal_case(entry.instance_location, default_namespace) << " = "
         << to_pascal_case(entry.target.instance_location, default_namespace)
         << ";\n";
}

static auto handle_ir_tuple(std::ostream &output, const IRTuple &entry,
                            const std::string &default_namespace) -> void {
  output << "export type "
         << to_pascal_case(entry.instance_location, default_namespace)
         << " = [";

  const char *separator{""};
  for (const auto &item : entry.items) {
    output << separator
           << to_pascal_case(item.instance_location, default_namespace);
    separator = ", ";
  }

  if (entry.additional.has_value()) {
    output << separator << "..."
           << to_pascal_case(entry.additional->instance_location,
                             default_namespace)
           << "[]";
  }

  output << "];\n";
}

auto typescript(std::ostream &output, const IRResult &result,
                const std::optional<std::string> &default_namespace) -> void {
  const std::string ns{default_namespace.value_or("Schema")};
  const char *separator{""};
  for (const auto &entity : result) {
    output << separator;
    separator = "\n";
    if (const auto *scalar = std::get_if<IRScalar>(&entity)) {
      handle_ir_scalar(output, *scalar, ns);
    } else if (const auto *enumeration = std::get_if<IREnumeration>(&entity)) {
      handle_ir_enumeration(output, *enumeration, ns);
    } else if (const auto *object = std::get_if<IRObject>(&entity)) {
      handle_ir_object(output, *object, ns);
    } else if (const auto *impossible = std::get_if<IRImpossible>(&entity)) {
      handle_ir_impossible(output, *impossible, ns);
    } else if (const auto *array = std::get_if<IRArray>(&entity)) {
      handle_ir_array(output, *array, ns);
    } else if (const auto *tuple = std::get_if<IRTuple>(&entity)) {
      handle_ir_tuple(output, *tuple, ns);
    } else if (const auto *reference = std::get_if<IRReference>(&entity)) {
      handle_ir_reference(output, *reference, ns);
    }
  }
}

} // namespace sourcemeta::codegen

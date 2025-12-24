#include <sourcemeta/codegen/generator.h>

#include <stdexcept> // std::runtime_error

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

static auto handle_ir_enumeration(std::ostream &, const IREnumeration &,
                                  const std::string &) -> void {
  throw std::runtime_error("IREnumeration is not supported yet");
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
    }
  }
}

} // namespace sourcemeta::codegen

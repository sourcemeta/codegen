#include <sourcemeta/codegen/generator.h>

#include <stdexcept> // std::runtime_error

namespace sourcemeta::codegen {

static auto pointer_to_name(const sourcemeta::core::PointerTemplate &pointer,
                            const std::optional<std::string> &default_namespace)
    -> std::string {
  if (pointer.empty()) {
    if (!default_namespace.has_value()) {
      throw std::runtime_error(
          "Empty pointer without default namespace provided");
    }
    return default_namespace.value();
  }

  std::string result;
  for (const auto &token : pointer) {
    if (!result.empty()) {
      result += "_";
    }
    const auto &property_token{
        std::get<sourcemeta::core::Pointer::Token>(token)};
    result += property_token.to_property();
  }
  return result;
}

static auto scalar_type_to_typescript(IRScalarType type) -> std::string {
  switch (type) {
    case IRScalarType::String:
      return "string";
    default:
      return "unknown";
  }
}

static auto
handle_ir_scalar(std::ostream &output, const IRScalar &entry,
                 const std::optional<std::string> &default_namespace) -> void {
  const auto name{pointer_to_name(entry.instance_location, default_namespace)};
  output << "export type " << name << " = "
         << scalar_type_to_typescript(entry.value) << ";\n";
}

static auto handle_ir_union(std::ostream &, const IRUnion &,
                            const std::optional<std::string> &) -> void {
  throw std::runtime_error("IRUnion is not supported yet");
}

static auto
handle_ir_object(std::ostream &output, const IRObject &entry,
                 const std::optional<std::string> &default_namespace) -> void {
  const auto name{pointer_to_name(entry.instance_location, default_namespace)};
  output << "export interface " << name << " {\n";
  for (const auto &[member_name, member_value] : entry.members) {
    const auto optional_marker{member_value.required ? "" : "?"};
    const auto readonly_marker{member_value.immutable ? "readonly " : ""};
    const auto member_type_name{
        pointer_to_name(member_value.instance_location, default_namespace)};
    output << "  " << readonly_marker << member_name << optional_marker << ": "
           << member_type_name << ";\n";
  }
  output << "}\n";
}

static auto handle_ir_impossible(std::ostream &, const IRImpossible &,
                                 const std::optional<std::string> &) -> void {
  throw std::runtime_error("IRImpossible is not supported yet");
}

auto typescript(std::ostream &output, const IRResult &result,
                const std::optional<std::string> &default_namespace) -> void {
  bool first{true};
  for (const auto &entity : result) {
    if (!first) {
      output << "\n";
    }
    first = false;

    if (const auto *scalar = std::get_if<IRScalar>(&entity)) {
      handle_ir_scalar(output, *scalar, default_namespace);
    } else if (const auto *union_entry = std::get_if<IRUnion>(&entity)) {
      handle_ir_union(output, *union_entry, default_namespace);
    } else if (const auto *object = std::get_if<IRObject>(&entity)) {
      handle_ir_object(output, *object, default_namespace);
    } else if (const auto *impossible = std::get_if<IRImpossible>(&entity)) {
      handle_ir_impossible(output, *impossible, default_namespace);
    }
  }
}

} // namespace sourcemeta::codegen

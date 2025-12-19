#include <sourcemeta/codegen/ir_group.h>

namespace sourcemeta::codegen {

auto group(const sourcemeta::core::SchemaFrame &frame) -> IRGroup {
  IRGroup trivial;
  IRGroup non_trivial;

  for (const auto &[key, location] : frame.locations()) {
    if (location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Resource ||
        location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Subschema) {
      for (const auto &instance_location : frame.instance_locations(location)) {
        auto &target{instance_location.trivial() ? trivial : non_trivial};
        target[instance_location].locations.emplace_back(IRGroupLocation{
            .instance_location = instance_location, .location = location});
      }
    }
  }

  for (const auto &[non_trivial_location, entry] : non_trivial) {
    auto matched{false};
    for (auto &[trivial_location, trivial_entry] : trivial) {
      if (non_trivial_location.matches(trivial_location)) {
        for (const auto &location : entry.locations) {
          trivial_entry.locations.emplace_back(location);
        }

        matched = true;
      }
    }

    if (!matched) {
      trivial[non_trivial_location] = entry;
    }
  }

  return trivial;
}

} // namespace sourcemeta::codegen

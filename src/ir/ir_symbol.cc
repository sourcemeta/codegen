#include <sourcemeta/codegen/ir.h>

#include <algorithm> // std::ranges::reverse
#include <cassert>   // assert
#include <string>    // std::string
#include <vector>    // std::vector

namespace sourcemeta::codegen {

auto symbol(const sourcemeta::core::SchemaFrame &frame,
            const sourcemeta::core::SchemaFrame::Location &location)
    -> std::vector<std::string> {
  std::vector<std::string> result;

  auto current_pointer{location.pointer};

  while (true) {
    const auto current_location{frame.traverse(current_pointer)};
    assert(current_location.has_value());

    if (!current_location->get().parent.has_value()) {
      break;
    }

    const auto &parent_pointer{current_location->get().parent.value()};
    const auto segments_skipped{current_pointer.size() - parent_pointer.size()};
    assert(segments_skipped >= 1);

    if (segments_skipped >= 2) {
      const auto &last_token{current_pointer.back()};
      if (last_token.is_property()) {
        result.emplace_back(last_token.to_property());
      } else {
        result.emplace_back(std::to_string(last_token.to_index()));
      }
    } else {
      const auto &token{current_pointer.back()};
      if (token.is_property()) {
        result.emplace_back(token.to_property());
      } else {
        result.emplace_back(std::to_string(token.to_index()));
      }
    }

    current_pointer = parent_pointer;
  }

  std::ranges::reverse(result);
  return result;
}

} // namespace sourcemeta::codegen

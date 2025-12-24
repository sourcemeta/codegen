#include <sourcemeta/codegen/generator.h>
#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem> // std::filesystem::path
#include <iostream>   // std::cout, std::cerr
#include <optional>   // std::optional, std::nullopt
#include <string>     // std::string

auto main(int argc, char *argv[]) -> int {
  sourcemeta::core::Options options;
  options.option("default-prefix", {"p"});
  options.parse(argc, argv);

  const auto &positional_arguments{options.positional()};
  if (positional_arguments.empty()) {
    std::cerr << "error: missing schema path\n";
    return EXIT_FAILURE;
  }

  const std::filesystem::path schema_path{positional_arguments.front()};
  const auto schema{sourcemeta::core::read_json(schema_path)};

  const auto result{
      sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                   sourcemeta::core::schema_resolver,
                                   sourcemeta::codegen::default_compiler)};

  std::optional<std::string> default_prefix{std::nullopt};
  if (options.contains("default-prefix")) {
    default_prefix = std::string{options.at("default-prefix").front()};
  }

  sourcemeta::codegen::typescript(std::cout, result, default_prefix);
  return EXIT_SUCCESS;
}

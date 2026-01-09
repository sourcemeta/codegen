#include <sourcemeta/codegen/generator.h>
#include <sourcemeta/codegen/ir.h>
#include <sourcemeta/codegen/ir_error.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>
#include <sourcemeta/core/options.h>

#include <cstdlib>    // EXIT_SUCCESS, EXIT_FAILURE
#include <filesystem> // std::filesystem::path
#include <iostream>   // std::cout, std::cerr
#include <sstream>    // std::ostringstream
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

  try {
    const auto schema{sourcemeta::core::read_json(schema_path)};

    const auto result{
        sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                     sourcemeta::core::schema_resolver,
                                     sourcemeta::codegen::default_compiler)};

    const std::string prefix{
        options.contains("default-prefix")
            ? std::string{options.at("default-prefix").front()}
            : "Schema"};

    sourcemeta::codegen::generate<sourcemeta::codegen::TypeScript>(
        std::cout, result, prefix);
  } catch (const sourcemeta::codegen::UnsupportedKeywordError &error) {
    std::ostringstream pointer;
    sourcemeta::core::stringify(error.pointer(), pointer);
    std::cerr << "error: " << error.what() << "\n";
    std::cerr << "  keyword: " << error.keyword() << "\n";
    std::cerr << "  location: " << pointer.str() << "\n";
    std::cerr << "  schema: ";
    sourcemeta::core::prettify(error.json(), std::cerr);
    std::cerr << "\n";
    return EXIT_FAILURE;
  } catch (const sourcemeta::codegen::UnsupportedKeywordValueError &error) {
    std::ostringstream pointer;
    sourcemeta::core::stringify(error.pointer(), pointer);
    std::cerr << "error: " << error.what() << "\n";
    std::cerr << "  keyword: " << error.keyword() << "\n";
    std::cerr << "  location: " << pointer.str() << "\n";
    std::cerr << "  schema: ";
    sourcemeta::core::prettify(error.json(), std::cerr);
    std::cerr << "\n";
    return EXIT_FAILURE;
  } catch (const sourcemeta::codegen::UnexpectedSchemaError &error) {
    std::ostringstream pointer;
    sourcemeta::core::stringify(error.pointer(), pointer);
    std::cerr << "error: " << error.what() << "\n";
    std::cerr << "  location: " << pointer.str() << "\n";
    std::cerr << "  schema: ";
    sourcemeta::core::prettify(error.json(), std::cerr);
    std::cerr << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

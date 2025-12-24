sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME generator
  FOLDER "Codegen/Generator"
  SOURCES generator_typescript_test.cc)

target_link_libraries(sourcemeta_codegen_generator_unit
  PRIVATE sourcemeta::codegen::generator)

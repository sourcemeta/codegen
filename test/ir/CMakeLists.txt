sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME ir
  FOLDER "Codegen/IR"
  SOURCES ir_2020_12_test.cc ir_symbol_test.cc ir_test_utils.h)

target_link_libraries(sourcemeta_codegen_ir_unit
  PRIVATE sourcemeta::codegen::ir)

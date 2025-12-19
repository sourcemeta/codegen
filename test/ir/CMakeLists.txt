sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME ir
  FOLDER "Codegen/IR"
  SOURCES ir_test.cc ir_group_test.cc)

target_link_libraries(sourcemeta_codegen_ir_unit
  PRIVATE sourcemeta::codegen::ir)

sourcemeta_library(NAMESPACE sourcemeta PROJECT codegen NAME generator
  FOLDER "Codegen/Generator"
  SOURCES typescript.cc)

if(CODEGEN_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT codegen NAME generator)
endif()

target_link_libraries(sourcemeta_codegen_generator PUBLIC sourcemeta::codegen::ir)

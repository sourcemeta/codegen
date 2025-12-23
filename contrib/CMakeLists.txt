if(CODEGEN_IR AND CODEGEN_GENERATOR)
  sourcemeta_executable(NAMESPACE sourcemeta PROJECT codegen NAME contrib_typescript
    FOLDER "Codegen/Contrib" SOURCES typescript.cc)
  target_link_libraries(sourcemeta_codegen_contrib_typescript
    PRIVATE sourcemeta::codegen::ir)
  target_link_libraries(sourcemeta_codegen_contrib_typescript
    PRIVATE sourcemeta::codegen::generator)
endif()

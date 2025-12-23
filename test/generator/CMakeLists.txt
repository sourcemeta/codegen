sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME generator
  FOLDER "Codegen/Generator"
  SOURCES generator_test.cc)

target_link_libraries(sourcemeta_codegen_generator_unit
  PRIVATE sourcemeta::codegen::generator)

sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME generator_e2e
  FOLDER "Codegen/Generator"
  SOURCES e2e.cc)

target_link_libraries(sourcemeta_codegen_generator_e2e_unit
  PRIVATE sourcemeta::codegen::ir)
target_link_libraries(sourcemeta_codegen_generator_e2e_unit
  PRIVATE sourcemeta::codegen::generator)
target_compile_definitions(sourcemeta_codegen_generator_e2e_unit
  PRIVATE TYPESCRIPT_E2E_PATH="${CMAKE_CURRENT_SOURCE_DIR}/e2e")

file(GLOB TYPESCRIPT_DIALECT_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/e2e/*")
foreach(DIALECT_DIRECTORY ${TYPESCRIPT_DIALECT_DIRECTORIES})
  if(IS_DIRECTORY ${DIALECT_DIRECTORY})
    get_filename_component(DIALECT_NAME ${DIALECT_DIRECTORY} NAME)
    file(GLOB TYPESCRIPT_CASE_DIRECTORIES "${DIALECT_DIRECTORY}/*")
    foreach(CASE_DIRECTORY ${TYPESCRIPT_CASE_DIRECTORIES})
      if(IS_DIRECTORY ${CASE_DIRECTORY})
        get_filename_component(CASE_NAME ${CASE_DIRECTORY} NAME)
        add_test(NAME "tsc.${DIALECT_NAME}.${CASE_NAME}/expected.d.ts"
          COMMAND "${PROJECT_SOURCE_DIR}/node_modules/.bin/tsc" --noEmit
            "${CASE_DIRECTORY}/expected.d.ts")
      endif()
    endforeach()
  endif()
endforeach()

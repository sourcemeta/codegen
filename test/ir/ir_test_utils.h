#ifndef SOURCEMETA_CODEGEN_IR_TEST_UTILS_H_
#define SOURCEMETA_CODEGEN_IR_TEST_UTILS_H_

// TODO: Have macros for objects and enumerations

#define EXPECT_AS_STRING(actual, expected)                                     \
  EXPECT_EQ(sourcemeta::core::to_string(actual), expected)

#define EXPECT_SYMBOL(actual, ...)                                             \
  EXPECT_EQ(actual, (std::vector<std::string>{__VA_ARGS__}))

#define EXPECT_IR_SCALAR(result, index, scalar_type, expected_pointer)         \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::codegen::IRScalar>(result.at(index))) \
      << "Expected IRScalar at index " << index;                               \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::codegen::IRScalar>(result.at(index)).pointer,       \
      expected_pointer);                                                       \
  EXPECT_EQ(std::get<sourcemeta::codegen::IRScalar>(result.at(index)).value,   \
            sourcemeta::codegen::IRScalarType::scalar_type)

#define EXPECT_IR_IMPOSSIBLE(result, index, expected_pointer)                  \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::codegen::IRImpossible>(       \
      result.at(index)))                                                       \
      << "Expected IRImpossible at index " << index;                           \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::codegen::IRImpossible>(result.at(index)).pointer,   \
      expected_pointer)

#define EXPECT_IR_ARRAY(result, index, expected_pointer,                       \
                        expected_items_pointer)                                \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::codegen::IRArray>(result.at(index)))  \
      << "Expected IRArray at index " << index;                                \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::codegen::IRArray>(result.at(index)).pointer,        \
      expected_pointer);                                                       \
  EXPECT_TRUE(std::get<sourcemeta::codegen::IRArray>(result.at(index))         \
                  .items.has_value())                                          \
      << "Expected IRArray items to have a value";                             \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::codegen::IRArray>(result.at(index)).items->pointer, \
      expected_items_pointer)

#define EXPECT_IR_REFERENCE(result, index, expected_pointer,                   \
                            expected_target_pointer)                           \
  EXPECT_TRUE(std::holds_alternative<sourcemeta::codegen::IRReference>(        \
      result.at(index)))                                                       \
      << "Expected IRReference at index " << index;                            \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::codegen::IRReference>(result.at(index)).pointer,    \
      expected_pointer);                                                       \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::codegen::IRReference>(result.at(index))             \
          .target.pointer,                                                     \
      expected_target_pointer)

#endif

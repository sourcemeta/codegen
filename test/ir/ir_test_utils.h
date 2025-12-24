#ifndef SOURCEMETA_CODEGEN_IR_TEST_UTILS_H_
#define SOURCEMETA_CODEGEN_IR_TEST_UTILS_H_

#define EXPECT_AS_STRING(actual, expected)                                     \
  EXPECT_EQ(sourcemeta::core::to_string(actual), expected)

#define EXPECT_IR_SCALAR(result, index, scalar_type, expected_pointer,         \
                         expected_instance_location)                           \
  EXPECT_TRUE(                                                                 \
      std::holds_alternative<sourcemeta::codegen::IRScalar>(result.at(index))) \
      << "Expected IRScalar at index " << index;                               \
  EXPECT_AS_STRING(                                                            \
      std::get<sourcemeta::codegen::IRScalar>(result.at(index)).pointer,       \
      expected_pointer);                                                       \
  EXPECT_AS_STRING(std::get<sourcemeta::codegen::IRScalar>(result.at(index))   \
                       .instance_location,                                     \
                   expected_instance_location);                                \
  EXPECT_EQ(std::get<sourcemeta::codegen::IRScalar>(result.at(index)).value,   \
            sourcemeta::codegen::IRScalarType::scalar_type)

#endif

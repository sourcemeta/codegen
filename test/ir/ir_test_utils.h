#ifndef SOURCEMETA_CODEGEN_IR_TEST_UTILS_H_
#define SOURCEMETA_CODEGEN_IR_TEST_UTILS_H_

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define EXPECT_AS_STRING(actual, expected)                                     \
  EXPECT_EQ(sourcemeta::core::to_string(actual), expected)
// NOLINTEND(cppcoreguidelines-macro-usage)

#endif

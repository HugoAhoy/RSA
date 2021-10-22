#include"Int.hpp"
#include "gtest/gtest.h"

TEST(IntTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_EQ("1233", Int("1233").val());
}

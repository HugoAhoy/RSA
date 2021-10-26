#include "Int.hpp"
#include "string"
#include "gtest/gtest.h"

TEST(IntTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_EQ("1233", Int("1233").val());
  EXPECT_EQ("2531564864864185005455884", Int("2531564864864185005455884").val());
  EXPECT_EQ("-1864868", Int("-1864868").val());
  EXPECT_EQ(std::to_string(519854864), Int(519854864).val());
  EXPECT_EQ(std::to_string(-346846), Int(-346846).val());
  EXPECT_EQ(std::to_string(78541274693145ll), Int(78541274693145ll).val());
  EXPECT_EQ(std::to_string(-21542365237ll), Int(-21542365237ll).val());
}

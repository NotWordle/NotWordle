#include <gtest/gtest.h>

#include "game/Color.h"

using game::color::Code;

class ColorTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Code c1_{Code::FG_RED};
};

TEST_F(ColorTest, TestWrap) {
  // gcc compiles this color code escape as hex \033 == \x1B
  auto exp_str = "\x1B[31mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c1_), exp_str);
}
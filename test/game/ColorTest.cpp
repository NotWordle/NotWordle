#include <gtest/gtest.h>

#include "game/Color.h"

using game::color::Code;

class ColorTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Code c1_{Code::FG_RED};
  Code c2_{Code::FG_GREEN};
  Code c3_{Code::FG_BLUE};
  Code c4_{Code::FG_DEFAULT};
  Code c5_{Code::BG_RED};
  Code c6_{Code::BG_GREEN};
  Code c7_{Code::BG_BLUE};
  Code c8_{Code::BG_DEFAULT};
};

TEST_F(ColorTest, TestWrap) {
  // gcc compiles this color code escape as hex \033 == \x1B
  auto exp_str = "\x1B[31mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c1_), exp_str);

  exp_str = "\x1B[32mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c2_), exp_str);

  exp_str = "\x1B[34mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c3_), exp_str);

  exp_str = "\x1B[39mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c4_), exp_str);

  exp_str = "\x1B[41mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c5_), exp_str);

  exp_str = "\x1B[42mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c6_), exp_str);

  exp_str = "\x1B[44mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c7_), exp_str);

  exp_str = "\x1B[49mtest_str\x1B[0m";
  EXPECT_EQ(game::color::wrap("test_str", c8_), exp_str);
}

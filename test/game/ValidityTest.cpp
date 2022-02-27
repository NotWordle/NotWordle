#include <gtest/gtest.h>

#include "game/Validity.h"

using game::Validity;

class ValidityTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Validity v1_{Validity::EMPTY};
  Validity v2_{Validity::INVALID};
  Validity v3_{Validity::CLOSE};
  Validity v4_{Validity::CORRECT};
};

TEST_F(ValidityTest, TestValue) {
  EXPECT_EQ(static_cast<int>(v1_), 0);
  EXPECT_EQ(static_cast<int>(v2_), 1);
  EXPECT_EQ(static_cast<int>(v3_), 2);
  EXPECT_EQ(static_cast<int>(v4_), 3);
}

TEST_F(ValidityTest, TestToString) {
  EXPECT_EQ(game::to_string(v1_), "EMPTY");
  EXPECT_EQ(game::to_string(v2_), "INVALID");
  EXPECT_EQ(game::to_string(v3_), "CLOSE");
  EXPECT_EQ(game::to_string(v4_), "CORRECT");

  EXPECT_THROW(game::to_string(static_cast<Validity>(4)), std::invalid_argument);
}

TEST_F(ValidityTest, TestFromString) {
  EXPECT_EQ(game::from_string("EMPTY"), Validity::EMPTY);
  EXPECT_EQ(game::from_string("INVALID"), Validity::INVALID);
  EXPECT_EQ(game::from_string("CLOSE"), Validity::CLOSE);
  EXPECT_EQ(game::from_string("CORRECT"), Validity::CORRECT);

  EXPECT_THROW(game::from_string("GARBAGE"), std::invalid_argument);
}

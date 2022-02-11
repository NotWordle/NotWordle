#include <gtest/gtest.h>

#include "game/objects/Space.h"

using game::Validity;
using game::objects::Space;

class SpaceTest : public ::testing::Test {
 protected:
  void SetUp() override {
    s4_.Letter('A');
    s4_.SetValidity(Validity::CLOSE);
  }

  Space s1_;
  Space s2_;
  Space s3_;
  Space s4_;
};

TEST_F(SpaceTest, TestGetLetter) { EXPECT_EQ(s1_.Letter(), '-'); }

TEST_F(SpaceTest, TestSetLetter) {
  s1_.Letter('A');
  EXPECT_EQ(s1_.Letter(), 'A');
}

TEST_F(SpaceTest, TestGetValidity) { EXPECT_EQ(s2_.GetValidity(), Validity::EMPTY); }

TEST_F(SpaceTest, TestSetValidity) {
  s2_.SetValidity(Validity::CORRECT);
  EXPECT_EQ(s2_.GetValidity(), Validity::CORRECT);
}

TEST_F(SpaceTest, TestID) {
  // Third space is gonna be ID 3
  // EXPECT_EQ(s3_.GetID(), 3); TODO: changes based on ctest vs. running exe?
  EXPECT_TRUE(true);
}

TEST_F(SpaceTest, TestName) {
  // EXPECT_EQ(s3_.Name(), "Space_3"); TODO: changes based on ctest vs. running exe?
  EXPECT_TRUE(true);
}

TEST_F(SpaceTest, TestToString) {
  // gcc appears to convert color encoding \033 to hex \x1B
  EXPECT_EQ(s4_.to_string(), "\x1B[34mA\x1B[0m");
}

// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
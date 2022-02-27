#include <gtest/gtest.h>

#include "game/objects/Grid.h"

using game::objects::Grid;

class GridTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Grid g1_{5};
  Grid g2_{5};
  Grid g3_{5};
  Grid g4_{5};
  Grid g5_{5};
};

TEST_F(GridTest, TestConstructor) {
  auto dim = g1_.GetGridDimensions();

  EXPECT_EQ(dim.first, 6);
  EXPECT_EQ(dim.second, 5);
}

TEST_F(GridTest, TestIndex) {
  const int kRow = 5, kCol = 2;

  auto dim = g1_.GetGridDimensions();
  auto exp_idx = kRow + dim.first * kCol;

  EXPECT_EQ(g1_.Index(kRow, kCol), exp_idx);
}

TEST_F(GridTest, TestSpaceMutation) {
  const int kRow = 5, kCol = 2;
  const char c = 'G';

  auto sp = g2_.GetSpace(kRow, kCol);
  ASSERT_EQ(sp.Letter(), '-');

  g2_.UpdateSpace(kRow, kCol, c);

  auto sp2 = g2_.GetSpace(kRow, kCol);
  EXPECT_EQ(sp2.Letter(), c);
}

TEST_F(GridTest, TestLineMutation) {
  auto dim = g3_.GetGridDimensions();

  const std::string word = "TRUNK";
  g3_.UpdateLine(word);

  std::string res;
  for (int i = 0; i < dim.second; ++i) {
    res += g3_.GetSpace(0, i).Letter();
  }

  EXPECT_EQ(res, word);

  g3_.ClearLine();

  res.clear();
  for (int i = 0; i < dim.second; ++i) {
    res += g3_.GetSpace(0, i).Letter();
  }

  EXPECT_EQ(res, std::string(dim.second, '-'));
}

TEST_F(GridTest, TestCheckGuess) {
  auto dim = g4_.GetGridDimensions();

  const std::string word = "TRUNK";
  g4_.UpdateLine(word);

  ASSERT_EQ(g4_.GetCurrentGuess(), word);

  // check correct word
  EXPECT_TRUE(g4_.CheckGuess(word));

  // check close word
  EXPECT_FALSE(g4_.CheckGuess("TRACE"));

  // check completely wrong word
  EXPECT_FALSE(g4_.CheckGuess("APPLE"));
}

TEST_F(GridTest, TestIncrementGuess) {
  auto dim = g4_.GetGridDimensions();

  for (int i = 0; i < dim.first - 1; ++i) {
    EXPECT_TRUE(g4_.IncrementGuess());
  }

  // only last guess returns false
  EXPECT_FALSE(g4_.IncrementGuess());
}

TEST_F(GridTest, TestMarkLettersUsed) {
  using game::Validity;

  std::array<Validity, 26> alphabet;
  for (auto& l : alphabet) {
    l = Validity::EMPTY;
  }

  g5_.UpdateLine("APPLE");
  g5_.CheckGuess("PAILS");

  g5_.MarkLettersUsed(&alphabet);

  EXPECT_EQ(alphabet['A' - 65], Validity::CLOSE);
  EXPECT_EQ(alphabet['P' - 65], Validity::CLOSE);
  EXPECT_EQ(alphabet['L' - 65], Validity::CORRECT);
  EXPECT_EQ(alphabet['E' - 65], Validity::INVALID);
}

TEST_F(GridTest, TestGetID) {
  g1_.GetID();  // TODO(merritt): ID counter issue
  EXPECT_TRUE(true);
}

TEST_F(GridTest, TestName) {
  g1_.Name();  // TODO(merritt): ID counter issue
  EXPECT_TRUE(true);
}

TEST_F(GridTest, TestToString) {
  auto dim = g5_.GetGridDimensions();

  g5_.UpdateLine("APPLE");
  g5_.IncrementGuess();
  g5_.UpdateLine("TRUNK");

  auto res = g5_.to_string();

  std::string exp =
      "\x1B[39mA\x1B[0m \x1B[39mP\x1B[0m \x1B[39mP\x1B[0m \x1B[39mL\x1B[0m \x1B[39mE\x1B[0m \n"
      "\x1B[39mT\x1B[0m \x1B[39mR\x1B[0m \x1B[39mU\x1B[0m \x1B[39mN\x1B[0m \x1B[39mK\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n\n";

  EXPECT_EQ(res, exp);
}

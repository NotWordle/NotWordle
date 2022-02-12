#include <gtest/gtest.h>

#include "game/Game.h"

using game::Game;

class GameTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Game g1_;
  Game g2_;
};

TEST_F(GameTest, TestConstructor) {
  auto letters = g1_.AvailableLetters();

  for (auto c : letters) {
    EXPECT_EQ(c, game::Validity::EMPTY);
  }
}

TEST_F(GameTest, TestIsValidWord) {
  g1_.GetDictionary().LoadWords(5);

  EXPECT_TRUE(g1_.IsValidWord("trunk"));
  EXPECT_FALSE(g1_.IsValidWord("abcde"));
}

TEST_F(GameTest, TestPrintGrid) {
  std::string exp =
      "\n\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n"
      "\x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \x1B[39m-\x1B[0m \n\n\n";

  std::stringstream output;
  g2_.InitializeGrid(5);
  g2_.PrintGrid(output);

  auto res = output.str();

  EXPECT_EQ(exp, res);
}

TEST_F(GameTest, TestShowAvailableLetters) {
  // test inital print

  // test print with close letter, wrong letter, and correct letter
}
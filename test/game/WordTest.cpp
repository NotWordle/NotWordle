#include <gtest/gtest.h>

#include "game/Word.h"

using game::Word;

class WordTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Word w1_;
  Word w2_{"alpha"};
  Word w3_{"apple"};
  Word w4_{"tests"};
};

TEST_F(WordTest, TestConstructor) {
  // default constructor
  ASSERT_TRUE(w1_.ToString().empty());

  // string constructor
  ASSERT_EQ(w2_.ToString(), "alpha");
}

TEST_F(WordTest, TestGetLetterCount) {
  // check letters present in word
  EXPECT_EQ(w2_.GetLetterCount('a'), 2);
  EXPECT_EQ(w2_.GetLetterCount('l'), 1);
  EXPECT_EQ(w2_.GetLetterCount('p'), 1);
  EXPECT_EQ(w2_.GetLetterCount('h'), 1);

  // check letter not in word
  EXPECT_EQ(w2_.GetLetterCount('z'), 0);
}

TEST_F(WordTest, TestDecrementLetterCount) {
  // decrement letter twice
  ASSERT_EQ(w3_.GetLetterCount('p'), 2);
  EXPECT_EQ(w3_.DecrementLetterCount('p'), 1);
  EXPECT_EQ(w3_.DecrementLetterCount('p'), 0);

  // ensure Word does not decrement past 0
  EXPECT_EQ(w3_.DecrementLetterCount('p'), 0);

  // check letter not in word
  EXPECT_EQ(w3_.DecrementLetterCount('z'), 0);
}

TEST_F(WordTest, TestCompare) {
  using game::Validity;

  const std::string s1 = "apple";
  const std::string s2 = "zests";
  const std::string s3 = "beets";
  const std::string ans = "tests";

  Validity res[5]{Validity::EMPTY};

  w4_.Compare(s1, res);
  EXPECT_EQ(res[0], Validity::INVALID);
  EXPECT_EQ(res[1], Validity::INVALID);
  EXPECT_EQ(res[2], Validity::INVALID);
  EXPECT_EQ(res[3], Validity::INVALID);
  EXPECT_EQ(res[4], Validity::CLOSE);

  w4_.Compare(s2, res);
  EXPECT_EQ(res[0], Validity::INVALID);
  EXPECT_EQ(res[1], Validity::CORRECT);
  EXPECT_EQ(res[2], Validity::CORRECT);
  EXPECT_EQ(res[3], Validity::CORRECT);
  EXPECT_EQ(res[4], Validity::CORRECT);

  // check case when letters were previously guessed in correct position
  // but are in different position now. If there are duplicate letters, then
  // they will be marked as "close" or "correct" as needed.
  w4_.Compare(s3, res);
  EXPECT_EQ(res[0], Validity::INVALID);
  EXPECT_EQ(res[1], Validity::CORRECT);
  EXPECT_EQ(res[2], Validity::INVALID);  // already guessed correctly, now invalid instead of close
  EXPECT_EQ(res[3], Validity::CORRECT);
  EXPECT_EQ(res[4], Validity::CORRECT);

  w4_.Compare(ans, res);
  EXPECT_EQ(res[0], Validity::CORRECT);
  EXPECT_EQ(res[1], Validity::CORRECT);
  EXPECT_EQ(res[2], Validity::CORRECT);
  EXPECT_EQ(res[3], Validity::CORRECT);
  EXPECT_EQ(res[4], Validity::CORRECT);
}

TEST_F(WordTest, TestToString) { ASSERT_EQ(w2_.ToString(), "alpha"); }

TEST_F(WordTest, TestSize) {
  ASSERT_EQ(w1_.Size(), 0);
  ASSERT_EQ(w2_.Size(), 5);
}

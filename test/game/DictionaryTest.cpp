#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
#include <set>

#include "game/Dictionary.h"

using game::Dictionary;

class DictionaryTest : public ::testing::Test {
 protected:
  void SetUp() override {}

  Dictionary dict_;
  Dictionary dict2_;
};

TEST_F(DictionaryTest, TestConstructor) {
  std::set<std::string> exp_words;
  std::ifstream input("/usr/share/dict/words");
  for (std::string line; getline(input, line);) {
    // filter out words that have non alpha characters
    auto lambda = [](char c) -> bool { return !std::isalpha(c) || std::isupper(c); };
    if (std::find_if(line.begin(), line.end(), lambda) != line.end()) continue;

    exp_words.insert(line);
  }

  EXPECT_EQ(exp_words, dict_.GetAllWords());
}

TEST_F(DictionaryTest, TestLoadWordsParam) {
  const int kSIZE = 8;
  std::set<std::string> exp_words;
  std::ifstream input("/usr/share/dict/words");
  for (std::string line; getline(input, line);) {
    // filter out words that have different size or non alpha characters or proper nouns
    auto lambda = [](char c) -> bool { return !std::isalpha(c) || std::isupper(c); };
    if (line.size() != kSIZE || std::find_if(line.begin(), line.end(), lambda) != line.end()) continue;

    exp_words.insert(line);
  }
  dict2_.LoadWords(kSIZE);

  EXPECT_EQ(exp_words, dict2_.GetAllWords());
}

TEST_F(DictionaryTest, TestExists) {
  EXPECT_TRUE(dict_.Exists("apple"));
  EXPECT_FALSE(dict_.Exists("abcde"));
}

TEST_F(DictionaryTest, TestSelectRandomWord) {
  const int kSIZE = 5;
  auto word1 = dict_.SelectRandomWord(kSIZE);
  auto word2 = dict_.SelectRandomWord(kSIZE);

  // ensure words aren't the same
  EXPECT_NE(word1, word2);

  // ensure words are the right length
  EXPECT_TRUE(word1.size() == kSIZE);
  EXPECT_TRUE(word2.size() == kSIZE);

  // ensure words are all upper case
  for (auto i = 0; i < kSIZE; ++i) {
    EXPECT_TRUE(std::isupper(word1[i]));
    EXPECT_TRUE(std::isupper(word2[i]));
  }
}

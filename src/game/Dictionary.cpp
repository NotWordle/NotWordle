#include "game/Dictionary.h"

#include <algorithm>
#include <fstream>
#include <random>

namespace game {

Dictionary::Dictionary() { LoadWords(); }

std::set<std::string> Dictionary::GetAllWords() { return words_; }

void Dictionary::LoadWords() {
  std::ifstream input("/usr/share/dict/words");
  for (std::string line; getline(input, line);) {
    // filter out words that have non alpha characters
    auto lambda = [](char c) -> bool { return !std::isalpha(c) || std::isupper(c); };
    if (std::find_if(line.begin(), line.end(), lambda) != line.end()) continue;

    words_.insert(line);
  }
}

void Dictionary::LoadWords(const int size) {
  // clear words currently in list
  words_.clear();

  std::ifstream input("/usr/share/dict/words");
  for (std::string line; getline(input, line);) {
    // filter out words that have different size or non alpha characters or proper nouns
    auto lambda = [](char c) -> bool { return !std::isalpha(c) || std::isupper(c); };
    if (line.size() != size || std::find_if(line.begin(), line.end(), lambda) != line.end()) continue;

    words_.insert(line);
  }
}

bool Dictionary::Exists(const std::string& word) const { return words_.count(word); }

std::string Dictionary::SelectRandomWord(const int size) const {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, words_.size() - 1);

  std::set<std::string>::iterator it;
  do {
    it = words_.begin();
    std::advance(it, dis(gen));
  } while (it->size() != size);

  // make word all uppercase
  std::string ret = *it;
  std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);

  return ret;
}

}  // namespace game

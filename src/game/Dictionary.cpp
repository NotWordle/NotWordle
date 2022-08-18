#include "game/Dictionary.h"

#include <algorithm>
#include <fstream>
#include <random>

namespace game {

void Dictionary::SetDictionaryFile(const std::string& filename) { dictionary_file_ = filename; }

std::set<std::string> Dictionary::GetAllWords() { return words_; }

void Dictionary::LoadWords(const int size) {
  // clear words currently in list
  words_.clear();

  std::ifstream input(dictionary_file_);
  if (input) {
    for (std::string line; getline(input, line);) {
      // filter out words that have different size or non alpha characters or proper nouns
      auto lambda = [](char c) -> bool { return !std::isalpha(c) || std::isupper(c); };
      if (line.size() != size || std::find_if(line.begin(), line.end(), lambda) != line.end()) continue;

      words_.insert(line);
    }
    loaded_ = true;
  } else {
    throw std::runtime_error("Dictionary file invalid! Ensure that '" + dictionary_file_ +
                             "' exists and has correct permissions");
  }
}

bool Dictionary::Exists(const std::string& word) const {
  if (!loaded_) {
    throw std::runtime_error("Attempting to use Dictionary before it's loaded!");
  }

  return words_.count(word);
}

std::string Dictionary::SelectRandomWord(const int size) const {
  if (!loaded_) {
    throw std::runtime_error("Attempting to use Dictionary before it's loaded!");
  }

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

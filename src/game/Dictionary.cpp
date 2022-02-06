#include "game/Dictionary.h"

#include <fstream>

namespace game {

Dictionary::Dictionary() { LoadWords(); }

void Dictionary::LoadWords() {
  std::ifstream input("/usr/share/dict/words");
  for (std::string line; getline(input, line);) {
    words_.insert(line);
  }
}

bool Dictionary::Exists(const std::string& word) const { return words_.count(word); }

}  // namespace game
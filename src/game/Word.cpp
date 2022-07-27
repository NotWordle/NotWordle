#include "game/Word.h"

#include <algorithm>
namespace game {

Word::Word(const std::string& raw) : raw_word_(raw) {
  for (const auto& l : raw) {
    letter_counts_[l]++;
  }
}

uint16_t Word::GetLetterCount(const char& let) const { return letter_counts_.count(let) ? letter_counts_.at(let) : 0; }

uint16_t Word::DecrementLetterCount(const char& let) {
  if (!letter_counts_.count(let)) return 0;

  auto& count = letter_counts_.at(let);
  count = count - 1 >= 0 ? count - 1 : 0;
  return count;
}

void Word::Compare(const std::string& str, Validity results[]) {
  // reset results and find any matching letters first
  for (int i = 0; i < Size(); ++i) {
    if (raw_word_[i] == str[i]) {
      results[i] = Validity::CORRECT;
      DecrementLetterCount(str[i]);
    } else {
      results[i] = Validity::EMPTY;
    }
  }

  // check if any letters are in word, but in wrong index
  for (int i = 0; i < Size(); ++i) {
    if (results[i] == Validity::CORRECT) continue;

    if (std::find(raw_word_.begin(), raw_word_.end(), str[i]) != raw_word_.end() && GetLetterCount(str[i])) {
      results[i] = Validity::CLOSE;
    } else {
      results[i] = Validity::INVALID;
    }
  }
}

std::string Word::ToString() const { return raw_word_; }

size_t Word::Size() const { return raw_word_.size(); }

}  // namespace game

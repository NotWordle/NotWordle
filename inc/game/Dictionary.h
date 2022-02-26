#ifndef INC_GAME_DICTIONARY_H_
#define INC_GAME_DICTIONARY_H_

#include <set>
#include <string>

/// \file

namespace game {

/**
 * @brief Dictionary class for handling acceptable
 * words for the game. Loads words from system file
 */
class Dictionary {
 public:
  /**
   * @brief Construct a default Dictionary object. It will load
   * all the words in the system file regardless of size.
   */
  Dictionary();

  /**
   * @brief Goes into the /usr/share/dict/words system file
   * and loads them into a set. Words that are proper nouns
   * (i.e. that have first letter capitalized) and words that have
   * dashes or numbers in them are filtered out.
   */
  void LoadWords();

  /**
   * @brief Same as LoadWords but adds the additional filter
   * of word size.
   *
   * @param size expected size of all words being loaded
   */
  void LoadWords(const int size);

  /**
   * @brief Checks if the given word exists in the loaded dictionary
   *
   * @param word "word" whose existence is being questioned
   * @return bool true if word is found, false otherwise
   */
  bool Exists(const std::string& word) const;

  /**
   * @brief Randomly selects a word from the set of loaded words
   *
   * @param size size of the random word
   * @return std::string a random word from the set of loaded words
   */
  std::string SelectRandomWord(const int size) const;

  /**
   * @brief Get the set of words currently loaded
   *
   * @return std::set<std::string> containing loaded words
   */
  std::set<std::string> GetAllWords();

 private:
  /// immutable set of words loaded into this Dictionary
  std::set<std::string> words_;
};
}  // namespace game

#endif  // INC_GAME_DICTIONARY_H_

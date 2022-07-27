#ifndef INC_GAME_WORD_H_
#define INC_GAME_WORD_H_

#include <map>
#include <string>

#include "Validity.h"

namespace game {

/**
 * @brief Word class to assist with comparing words
 * within the game
 *
 */
class Word {
 public:
  /**
   * @brief Default constructor
   */
  Word() = default;

  /**
   * @brief Construct a new Word object with a raw std string. Assumes
   * that given string is a valid English word.
   *
   * @param raw std::string
   */
  explicit Word(const std::string& raw);

  /**
   * @brief Return the number of occurences of the given
   * letter within this Word
   *
   * @param let desired letter to find in Word
   * @return uint16_t number of letters in the word
   */
  uint16_t GetLetterCount(const char& let) const;

  /**
   * @brief Decrements the count of the letter in the letter map
   *
   * @param let letter count being decremented
   * @return uint16_t the new count of the letter
   */
  uint16_t DecrementLetterCount(const char& let);

  /**
   * @brief Compares Word with given string, saving results in the provided
   * Validity array of equal size. If a character in the given string is located
   * at the same index as the Word, the letter's count is decremented in the Word's
   * letter map.
   *
   * @param str string being compared to underlying string of Word
   * @param results updated based on how well letter's in each word match.
   */
  void Compare(const std::string& str, Validity results[]);

  /**
   * @brief To string function, returns the underlying word
   *
   * @return std::string
   */
  std::string ToString() const;

  /**
   * @brief Returns the size of the word
   *
   * @return size_t word length
   */
  size_t Size() const;

 private:
  std::string raw_word_;

  std::map<char, uint16_t> letter_counts_;
};

}  // namespace game

#endif  // INC_GAME_WORD_H_
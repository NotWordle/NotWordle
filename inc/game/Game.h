#ifndef INC_GAME_GAME_H_
#define INC_GAME_GAME_H_

#include <array>
#include <ostream>
#include <string>

#include "game/Dictionary.h"
#include "game/Validity.h"
#include "game/objects/Grid.h"

namespace game {

/**
 * @brief main class for running the actual game, handling most
 * of the user input and output.
 */
class Game {
 public:
  /**
   * @brief Construct a new Game object. Initializes the array of
   * available letters
   */
  Game();

  /**
   * @brief main runner function that contains the game code
   *
   * @param out output stream
   * @param in input stream
   * @param preselected for unit testing, sets the game word to this word
   * instead of randomly selected it
   */
  void Run(std::ostream& out, std::istream& in, const std::string& preselected = "");

  /**
   * @brief asks the user for a guess, including checks for invalid words
   *
   * @param out output stream
   * @param in input stream
   * @return std::string the final guess of the user (after error checking)
   */
  std::string QueryUserForGuess(std::ostream& out, std::istream& in);

  /**
   * @brief asks the user for the desired word size for the game, including error
   * checking for invalid answers. Size must be between 4 and 9
   *
   * @param out output stream
   * @param in input stream
   * @return uint16_t the final word size from the user (after error checking)
   */
  uint16_t QueryUserForWordSize(std::ostream& out, std::istream& in) const;

  /**
   * @brief checks the Dictionary if the given word is valid
   *
   * @param word word being checked
   * @return bool true if word is in Dictionary, false otherwise
   */
  bool IsValidWord(const std::string& word) const;

  /**
   * @brief prints the Grid Spaces in a format based on the word size.
   *
   * @param out output stream
   */
  void PrintGrid(std::ostream& out) const;

  /**
   * @brief prints out the list of letters based on their set Validity
   *
   * @param out output stream
   */
  void ShowAvailableLetters(std::ostream& out) const;

  /**
   * @brief checks the game_grid to mark which letters in the alphabet
   * have been used based on their validity
   */
  void MarkLettersUsed();

  /**
   * @brief getter for the validity list (index corresponds to letter
   * in alphabet)
   *
   * @return const std::array<Validity, 26>&
   */
  const std::array<Validity, 26>& AvailableLetters();

  /**
   * @brief sets the text file that the Dictionary will read from and
   * load into its list of valid words
   */
  void SetDictionaryFile(const std::string& filename);

  /**
   * @brief Get the Dictionary object
   *
   * @return Dictionary&
   */
  Dictionary& GetDictionary();

  /**
   * @brief Loads the Dictionary with words of the selected word size
   */
  void LoadDictionary();

  /**
   * @brief re-initializes the Grid object
   */
  void InitializeGrid();

  /**
   * @brief Returns the underlying Grid object
   *
   * @return game grid
   */
  const objects::Grid& GetGrid();

  /**
   * @brief updates the grid with the given word
   *
   * @param word word to be placed into the grid
   */
  void UpdateGrid(const std::string& word);

  /**
   * @brief checks if the latest guess in the Grid matches
   * the game word
   *
   * @return bool true if the words match, false otherwise
   */
  bool CheckGuess();

  /**
   * @brief returns the selected word of the game
   *
   * @return const std::string& game word
   */
  std::string SelectedWord() const;

  /**
   * @brief Sets the selected word of the game
   *
   * @throws std::invalid_argument if word is invalid
   *
   * @param word game word
   */
  void SelectedWord(const std::string& word);

  /**
   * @brief sets the game word to a random word from the dictionary
   */
  void RandomizeSelectedWord();

  /**
   * @brief returns the game word size
   *
   * @return const uint16_t
   */
  const uint16_t WordSize() const;

  /**
   * @brief sets the word size of the game
   *
   * @param size new word size
   */
  void WordSize(uint16_t size);

 private:
  /// game grid where words/letters will be entered into
  objects::Grid* game_grid_{nullptr};

  /// Dictionary for managing valid words of the game
  Dictionary dictionary_;

  /// list of Validity values to indicate if a guessed letter is in the game word or not
  /// index corresponds to letter in the alphabet (0 is 'A')
  std::array<Validity, 26> available_letters_;

  /// selected word of the game, the user is trying to match this
  Word selected_word_;

  /// chosen word size of the game/grid
  uint16_t word_size_{5};
};
}  // namespace game
#endif  // INC_GAME_GAME_H_
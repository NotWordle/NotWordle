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
  void Run(std::ostream& out, std::istream& in, std::string preselected = "");

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
  uint16_t QueryUserForWordSize(std::ostream& out, std::istream& in);

  /**
   * @brief checks the Dictionary if the given word is valid
   *
   * @param word word being checked
   * @return bool true if word is in Dictionary, false otherwise
   */
  bool IsValidWord(const std::string& word);

  /**
   * @brief prints the Grid Spaces in a format based on the word size.
   *
   * @param out output stream
   */
  void PrintGrid(std::ostream& out);

  /**
   * @brief prints out the list of letters based on their set Validity
   *
   * @param out output stream
   */
  void ShowAvailableLetters(std::ostream& out);

  /**
   * @brief getter for the validity list (index corresponds to letter
   * in alphabet)
   *
   * @return const std::array<Validity, 26>&
   */
  const std::array<Validity, 26>& AvailableLetters();

  /**
   * @brief Get the Dictionary object
   *
   * @return Dictionary&
   */
  Dictionary& GetDictionary();

  /**
   * @brief re-initializes the Grid object to the given size
   *
   * @param size size of the grid
   */
  void InitializeGrid(const int size);

  /**
   * @brief updates the grid with the given word
   *
   * @param word word to be placed into the grid
   */
  void UpdateGrid(const std::string& word);

  /**
   * @brief checks if the latest guess in the Grid matches
   * the given game word.
   *
   * @param game_word selected word for the game
   * @return bool true if the words match, false otherwise
   */
  bool CheckGuess(const std::string& game_word);

  /**
   * @brief returns the selected word of the game
   *
   * @return const std::string& game word
   */
  const std::string& SelectedWord();

 private:
  /// game grid where words/letters will be entered into
  objects::Grid* game_grid_{nullptr};

  /// Dictionary for managing valid words of the game
  Dictionary dictionary_;

  /// list of Validity values to indicate if a guessed letter is in the game word or not
  /// index corresponds to letter in the alphabet (0 is 'A')
  std::array<Validity, 26> available_letters_;

  /// selected word of the game, the user is trying to match this
  std::string selected_word_;

  /// chosen word size of the game/grid
  uint16_t word_size_{5};
};
}  // namespace game
#endif  // INC_GAME_GAME_H_

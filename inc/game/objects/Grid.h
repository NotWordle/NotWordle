#ifndef INC_GAME_OBJECTS_GRID_H_
#define INC_GAME_OBJECTS_GRID_H_

#include <array>
#include <string>
#include <utility>

#include "game/objects/GameObject.h"
#include "game/objects/Space.h"

namespace game::objects {
/**
 * @brief Grid class to contain 2D grid of Spaces
 * for showing the user's guesses as the game progresses
 */
class Grid : public GameObject {
 public:
  /// delete default constructor
  Grid() = delete;

  /**
   * @brief Construct a new Grid object with the given word size
   * Word size determines the number of columns, while the number
   * of rows is word_size + 1
   *
   * @param word_size word size of the grim (and number of columns)
   */
  explicit Grid(int word_size);

  /**
   * @brief Destroy the Grid object (free up Space memory)
   */
  ~Grid();

  /**
   * @brief Updates the space at row, col with the given character
   *
   * @param row row number
   * @param col column number
   * @param c new letter that Space will hold
   */
  void UpdateSpace(int row, int col, char c);

  /**
   * @brief Updates a row on the grid with the given word. Which
   * row being updated is determined by number of guesses
   *
   * @param word word being inserted into grid
   */
  void UpdateLine(const std::string& word);

  /**
   * @brief Clears a row on the grid, resetting each Space. Which
   * row being updated is determined by number of guesses
   *
   */
  void ClearLine();

  /**
   * @brief Checks if the current guess matches the given word. The current
   * guess is whatever word is in the last row (based on number of guesses)
   *
   * @param exp_word
   * @return true if words match, false otherwise
   */
  bool CheckGuess(const std::string& exp_word);

  /**
   * @brief increments the number of guesses field and checks if that field
   * is greater than the number of rows (i.e. game over)
   *
   * @return true if the number of guesses is less than number of rows, false otherwise
   */
  bool IncrementGuess();

  /**
   * @brief Helper function to get the row-major index for (row, col) in vectorized grid
   *
   * @param row desired row in 2D grid
   * @param col desired column in 2D grid
   * @return std::size_t the index that (row, col) would be in a row-major one-dimensional array
   */
  inline std::size_t Index(int row, int col) const { return row + kNumRows * col; }

  /**
   * @brief Gets the latest guess entered into the grid
   *
   * @return std::string latest guess
   */
  std::string GetCurrentGuess();

  /**
   * @brief Get the Space located at (row, col) in the grid
   *
   * @param row desired row
   * @param col desired column
   * @return reference to the desired Space object
   */
  Space& GetSpace(int row, int col);

  /**
   * @brief Checks the grid for which letters have been used; it will
   * examine the Validity at each Space and mark it accordingly in the
   * given Validity array.
   *
   * @param alphabet array of Validity enums that will be set based on how
   * the letter is used in the grid
   */
  void MarkLettersUsed(std::array<Validity, 26>* alphabet);

  /**
   * @brief Gets the Name of the object
   *
   * @return std::string object name
   */
  std::string Name() override;

  /**
   * @brief Converts the grid to a human-readable grid
   * of Spaces
   *
   * @return std::string game grid
   */
  std::string to_string() override;

  /**
   * @brief Getter for the dimensions of the grid
   *
   * @return std::pair<const int, const int> (num rows, num columns)
   */
  std::pair<const int, const int> GetGridDimensions() const;

 private:
  /**
   * @brief 2D array arranged in row-major form into a 1D array
   *
   */
  Space* grid_;

  /// word size of the Grid; this is also the number of columns
  const int kWordSize;

  /// number of rows in the grid
  const int kNumRows;

  /// the number of guesses made on the grid, this serves as the index for the latest guess
  int num_guess_{0};
};
}  // namespace game::objects

#endif  // INC_GAME_OBJECTS_GRID_H_

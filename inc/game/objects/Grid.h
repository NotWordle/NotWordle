#ifndef INC_GAME_OBJECTS_GRID_H_
#define INC_GAME_OBJECTS_GRID_H_

#include <array>

#include "game/objects/GameObject.h"
#include "game/objects/Space.h"

namespace game::objects {
class Grid : public GameObject {
 public:
  Grid() = delete;

  Grid(int word_size);
  ~Grid();

  void UpdateSpace(int row, int col, char c);
  void UpdateLine(const std::string& word);
  void ClearLine();
  bool CheckGuess(const std::string& exp_word);
  bool IncrementGuess();

  inline std::size_t Index(int row, int col) const { return row + kNumRows * col; }

  std::string GetCurrentGuess();

  Space GetSpace(int row, int col);

  void MarkLettersUsed(std::array<Validity, 26>* alphabet);

  std::string Name() override;
  std::string to_string() override;

  std::pair<const int, const int> GetGridDimensions() const;

 private:
  // rather than using a clunky 2D array, the grid will be a row-major array
  Space* grid_;
  const int kWordSize;
  const int kNumRows;
  int num_guess_{0};
};
}  // namespace game::objects

#endif  // INC_GAME_OBJECTS_GRID_H_
#ifndef INC_GAME_OBJECTS_GRID_H_
#define INC_GAME_OBJECTS_GRID_H_

#include "game/objects/GameObject.h"
#include "game/objects/Space.h"

namespace game::objects {
class Grid : public GameObject {
 public:
  Grid(int word_size);
  ~Grid();

  void UpdateSpace(int row, int col, char c);
  bool CheckGuess(const std::string& exp_word);

  inline std::size_t Index(int row, int col) const { return row + kWordSize * col; }

  std::string GetCurrentGuess();

  Space GetSpace(int row, int col);

  std::string Name() override;
  std::string to_string() override;

 private:
  // rather than using a clunky 2D array, the grid will be a row-major array
  Space* grid_;
  const int kWordSize;
  const int kNumRows;
  int num_guess_{0};
};
}  // namespace game::objects

#endif  // INC_GAME_OBJECTS_GRID_H_
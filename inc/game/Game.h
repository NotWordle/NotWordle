#ifndef INC_GAME_GAME_H_
#define INC_GAME_GAME_H_

#include "game/Dictionary.h"
#include "game/objects/Grid.h"

namespace game {

class Game {
 public:
  void Run();

  std::string QueryUserForGuess();

  inline bool IsValidWord(const std::string& word);
  inline void PrintGrid();

 private:
  objects::Grid* game_grid_;

  Dictionary dictionary_;
};
}  // namespace game
#endif  // INC_GAME_GAME_H_

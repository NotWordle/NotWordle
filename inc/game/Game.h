#ifndef INC_GAME_GAME_H_
#define INC_GAME_GAME_H_

#include <array>

#include "game/Dictionary.h"
#include "game/Validity.h"
#include "game/objects/Grid.h"

namespace game {

class Game {
 public:
  Game();

  void Run();

  std::string QueryUserForGuess();

  inline bool IsValidWord(const std::string& word);
  inline void PrintGrid();

  void MarkLettersUsed();
  void ShowAvailableLetters();

 private:
  objects::Grid* game_grid_;

  Dictionary dictionary_;

  std::array<Validity, 26> available_letters_;
};
}  // namespace game
#endif  // INC_GAME_GAME_H_

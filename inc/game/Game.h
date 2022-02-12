#ifndef INC_GAME_GAME_H_
#define INC_GAME_GAME_H_

#include <array>
#include <ostream>

#include "game/Dictionary.h"
#include "game/Validity.h"
#include "game/objects/Grid.h"

namespace game {

class Game {
 public:
  Game();

  void Run();

  std::string QueryUserForGuess();

  bool IsValidWord(const std::string& word);
  void PrintGrid(std::ostream& out);

  void ShowAvailableLetters(std::ostream& out);

  std::array<Validity, 26> AvailableLetters() const;
  Dictionary& GetDictionary();

  void InitializeGrid(const int size);

 private:
  objects::Grid* game_grid_;

  Dictionary dictionary_;

  std::array<Validity, 26> available_letters_;
};
}  // namespace game
#endif  // INC_GAME_GAME_H_

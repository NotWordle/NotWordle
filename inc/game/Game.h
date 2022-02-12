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

  void Run(std::ostream& out, std::istream& in, std::string preselected = "");

  std::string QueryUserForGuess(std::ostream& out, std::istream& in);

  bool IsValidWord(const std::string& word);
  void PrintGrid(std::ostream& out);

  void ShowAvailableLetters(std::ostream& out);

  std::array<Validity, 26> AvailableLetters() const;
  Dictionary& GetDictionary();

  void InitializeGrid(const int size);
  void UpdateGrid(const std::string& word);
  bool CheckGuess(const std::string& game_word);
  const std::string& SelectedWord();

 private:
  objects::Grid* game_grid_;

  Dictionary dictionary_;

  std::array<Validity, 26> available_letters_;

  std::string selected_word_;
};
}  // namespace game
#endif  // INC_GAME_GAME_H_

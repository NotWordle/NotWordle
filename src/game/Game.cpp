#include "game/Game.h"

#include <iostream>
#include <string>

namespace game {

const std::string CHOSEN_WORD = "COULD";  // TODO: randomize at start
const unsigned int WORD_SIZE = 5;         // TODO: make configurable

bool Game::IsValidWord(const std::string& word) { return dictionary_.Exists(word); }

std::string Game::QueryUserForGuess() {
  std::string ret;

  do {
    std::cout << "Enter a 5 letter word:\n";
    std::cin >> ret;
  } while (ret.size() != WORD_SIZE || !IsValidWord(ret));

  // capitalize word
  for (auto& c : ret) c = toupper(c);

  return ret;
}

void Game::PrintGrid() { std::cout << "\n" << game_grid_->to_string() << "\n"; }

void Game::Run() {
  game_grid_ = new objects::Grid(WORD_SIZE);

  bool redo = false;
  bool success = false;
  do {
    do {
      game_grid_->ClearLine();
      PrintGrid();

      auto guess = QueryUserForGuess();

      game_grid_->UpdateLine(guess);
      PrintGrid();

      std::string ans;
      do {
        std::cout << "are you sure? (y/n) ";
        std::cin >> ans;
      } while (ans != "n" && ans != "y");

      redo = ans == "n";
    } while (redo);

    if (game_grid_->CheckGuess(CHOSEN_WORD)) {
      std::cout << "you got it!\n";
      success = true;
      break;
    }
  } while (game_grid_->IncrementGuess());

  PrintGrid();
  if (success) {
    std::cout << "nice job!\n";
  } else {
    std::cout << "better luck next time!\n";
  }
}
}  // namespace game
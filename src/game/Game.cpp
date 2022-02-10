#include "game/Game.h"

#include <iostream>
#include <string>

#include "game/Color.h"

namespace game {

const unsigned int WORD_SIZE = 5;  // TODO: make configurable

Game::Game() {
  for (auto& l : available_letters_) {
    l = Validity::EMPTY;
  }
}

bool Game::IsValidWord(const std::string& word) { return dictionary_.Exists(word); }

std::string Game::QueryUserForGuess() {
  std::string ret;

  do {
    std::cout << "Enter a 5 letter word:\n";
    std::cin >> ret;
  } while (ret.size() != WORD_SIZE || !IsValidWord(ret));

  return ret;
}

void Game::PrintGrid() { std::cout << "\n" << game_grid_->to_string() << "\n"; }

void Game::ShowAvailableLetters() {
  game_grid_->MarkLettersUsed(&available_letters_);
  for (int i = 0; i < available_letters_.size(); ++i) {
    auto& v = available_letters_[i];
    auto l = std::string(1, static_cast<char>(i + 65));
    switch (v) {
      case Validity::EMPTY:
        std::cout << color::wrap(l, color::Code::FG_DEFAULT);
        break;
      case Validity::INVALID:
        std::cout << color::wrap(l, color::Code::FG_RED);
        break;
      case Validity::CLOSE:
        std::cout << color::wrap(l, color::Code::FG_BLUE);
        break;
      case Validity::CORRECT:
        std::cout << color::wrap(l, color::Code::FG_GREEN);
        break;
    }
    if ((i + 1) % 7 == 0 || i == available_letters_.size() - 1) {
      std::cout << "\n";
    } else {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}

void Game::Run() {
  // TODO: query user for word_size before starting game

  dictionary_.LoadWords(WORD_SIZE);

  game_grid_ = new objects::Grid(WORD_SIZE);

  const auto exp_word = dictionary_.SelectGameWord(WORD_SIZE);
  bool redo = false;
  bool success = false;
  do {
    do {
      game_grid_->ClearLine();
      PrintGrid();
      ShowAvailableLetters();

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

    if (game_grid_->CheckGuess(exp_word)) {
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
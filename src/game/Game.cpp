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

std::array<Validity, 26> Game::AvailableLetters() const { return available_letters_; }

Dictionary& Game::GetDictionary() { return dictionary_; }

void Game::InitializeGrid(const int size) {
  if (game_grid_ != nullptr) delete game_grid_;
  game_grid_ = new objects::Grid(size);
}

bool Game::IsValidWord(const std::string& word) { return dictionary_.Exists(word); }

std::string Game::QueryUserForGuess(std::ostream& out, std::istream& in) {
  std::string ret;

  do {
    out << "Enter a 5 letter word:\n";  // TODO: change 5 to configurable word size
    in >> std::skipws >> ret;
  } while (ret.size() != WORD_SIZE || !IsValidWord(ret));

  return ret;
}

void Game::PrintGrid(std::ostream& out) { out << "\n" << game_grid_->to_string() << "\n"; }

void Game::ShowAvailableLetters(std::ostream& out) {
  game_grid_->MarkLettersUsed(&available_letters_);
  for (int i = 0; i < available_letters_.size(); ++i) {
    auto& v = available_letters_[i];
    auto l = std::string(1, static_cast<char>(i + 65));
    switch (v) {
      case Validity::EMPTY:
        out << color::wrap(l, color::Code::FG_DEFAULT);
        break;
      case Validity::INVALID:
        out << color::wrap(l, color::Code::FG_RED);
        break;
      case Validity::CLOSE:
        out << color::wrap(l, color::Code::FG_BLUE);
        break;
      case Validity::CORRECT:
        out << color::wrap(l, color::Code::FG_GREEN);
        break;
    }
    if ((i + 1) % 7 == 0 || i == available_letters_.size() - 1) {
      out << "\n";
    } else {
      out << " ";
    }
  }
  out << "\n";
}

void Game::UpdateGrid(const std::string& word) { game_grid_->UpdateLine(word); }

bool Game::CheckGuess(const std::string& game_word) { return game_grid_->CheckGuess(game_word); }

const std::string& Game::SelectedWord() { return selected_word_; }

void Game::Run(std::ostream& out, std::istream& in, std::string preselected) {
  // TODO: query user for word_size before starting game

  dictionary_.LoadWords(WORD_SIZE);

  InitializeGrid(WORD_SIZE);
  if (preselected.empty()) {
    selected_word_ = dictionary_.SelectGameWord(WORD_SIZE);
  } else {
    selected_word_ = preselected;
  }
  bool redo = false;
  bool success = false;
  do {
    do {
      game_grid_->ClearLine();
      PrintGrid(out);
      ShowAvailableLetters(out);

      auto guess = QueryUserForGuess(out, in);

      UpdateGrid(guess);
      PrintGrid(out);

      std::string ans;
      do {
        out << "are you sure? (y/n) ";
        in >> ans;
      } while (ans != "n" && ans != "y");

      redo = ans == "n";
    } while (redo);

    if (CheckGuess(selected_word_)) {
      out << "you got it!\n";
      success = true;
      break;
    }
  } while (game_grid_->IncrementGuess());

  PrintGrid(out);
  if (success) {
    out << "nice job!\n";
  } else {
    out << "better luck next time! Word was: " << selected_word_ << "\n";
  }
}
}  // namespace game
#include "game/Game.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "game/Color.h"

namespace game {

Game::Game() {
  for (auto& l : available_letters_) {
    l = Validity::EMPTY;
  }
}

const std::array<Validity, 26>& Game::AvailableLetters() { return available_letters_; }

Dictionary& Game::GetDictionary() { return dictionary_; }

void Game::LoadDictionary() { dictionary_.LoadWords(word_size_); }

void Game::SetDictionaryFile(const std::string& filename) { dictionary_.SetDictionaryFile(filename); }

void Game::InitializeGrid() {
  delete game_grid_;
  game_grid_ = new objects::Grid(word_size_);
}

const objects::Grid& Game::GetGrid() {
  if (!game_grid_) {
    throw std::runtime_error("Attempting to get Grid when it's not initialized!");
  }
  return *game_grid_;
}

bool Game::IsValidWord(const std::string& word) const { return dictionary_.Exists(word); }

std::string Game::QueryUserForGuess(std::ostream& out, std::istream& in) {
  std::string ret;

  do {
    out << "Enter a " << word_size_ << " letter word:\n";
    in >> std::skipws >> ret;
  } while (ret.size() != word_size_ || !IsValidWord(ret));

  return ret;
}

uint16_t Game::QueryUserForWordSize(std::ostream& out, std::istream& in) const {
  uint16_t ret{0};

  do {
    std::string raw;
    out << "Enter game word size [4-9] (default is 5):";
    getline(in, raw);

    if (raw.empty()) {
      ret = word_size_;
      break;
    }

    std::stringstream ss(raw);
    ss >> ret;
  } while (ret < 4 || ret > 9);

  return ret;
}

void Game::PrintGrid(std::ostream& out) const {
  if (!game_grid_) return;
  out << "\n" << game_grid_->to_string() << "\n";
}

void Game::ShowAvailableLetters(std::ostream& out) const {
  if (!game_grid_) return;

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

void Game::MarkLettersUsed() { game_grid_->MarkLettersUsed(&available_letters_); }

void Game::UpdateGrid(const std::string& word) {
  if (!game_grid_) return;
  game_grid_->UpdateLine(word);
}

bool Game::CheckGuess() {
  if (!game_grid_) return false;

  return game_grid_->CheckGuess(selected_word_);
}

std::string Game::SelectedWord() const { return selected_word_.ToString(); }

void Game::SelectedWord(const std::string& word) {
  if (IsValidWord(word)) {
    // make word all uppercase
    std::string tmp(word);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
    selected_word_ = Word(tmp);
  } else {
    throw std::invalid_argument(
        "Selected word was invalid! Make sure the word is the right size and exists in the dictionary");
  }
}

const uint16_t Game::WordSize() const { return word_size_; }

void Game::WordSize(uint16_t size) { word_size_ = size; }

void Game::RandomizeSelectedWord() { selected_word_ = Word(dictionary_.SelectRandomWord(word_size_)); }

void Game::Run(std::ostream& out, std::istream& in, const std::string& preselected) {
  if (!preselected.empty()) {
    selected_word_ = Word(preselected);
    word_size_ = selected_word_.Size();
    LoadDictionary();
  } else {
    word_size_ = QueryUserForWordSize(out, in);
    LoadDictionary();
    RandomizeSelectedWord();
  }

  InitializeGrid();

  bool redo = false;
  bool success = false;
  do {
    do {
      game_grid_->ClearLine();
      PrintGrid(out);
      MarkLettersUsed();
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

    if (CheckGuess()) {
      out << "you got it!\n";
      success = true;
      break;
    }
  } while (game_grid_->IncrementGuess());

  PrintGrid(out);
  MarkLettersUsed();
  ShowAvailableLetters(out);

  if (success) {
    out << "nice job!\n";
  } else {
    out << "better luck next time! Word was: " << selected_word_.ToString() << "\n";
  }
}
}  // namespace game
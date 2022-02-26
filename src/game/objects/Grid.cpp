#include "game/objects/Grid.h"

#include <algorithm>
#include <sstream>

namespace game::objects {

Grid::Grid(int word_size) : kWordSize(word_size), kNumRows(word_size + 1) { grid_ = new Space[kWordSize * kNumRows]; }

Grid::~Grid() { delete[] grid_; }

Space& Grid::GetSpace(int row, int col) { return grid_[Index(row, col)]; }

void Grid::UpdateSpace(int row, int col, char c) { grid_[Index(row, col)].Letter(c); }

void Grid::UpdateLine(const std::string& word) {
  for (int i = 0; i < word.size(); ++i) {
    grid_[Index(num_guess_, i)].Letter(word[i]);
  }
}

void Grid::ClearLine() { UpdateLine(std::string(kWordSize, '-')); }

std::string Grid::GetCurrentGuess() {
  std::string guess;

  for (int i = 0; i < kWordSize; ++i) {
    guess += grid_[Index(num_guess_, i)].Letter();
  }

  return guess;
}

bool Grid::CheckGuess(const std::string& exp_word) {
  bool ret = true;

  for (int i = 0; i < kWordSize; ++i) {
    auto& space = grid_[Index(num_guess_, i)];
    if (space.Check(exp_word[i])) {
      space.SetValidity(Validity::CORRECT);
    } else if (std::find(exp_word.begin(), exp_word.end(), space.Letter()) != exp_word.end()) {
      space.SetValidity(Validity::CLOSE);
      ret = false;
    } else {
      space.SetValidity(Validity::INVALID);
      ret = false;
    }
  }

  return ret;
}

bool Grid::IncrementGuess() { return ++num_guess_ < kNumRows; }

void Grid::MarkLettersUsed(std::array<Validity, 26>* alphabet) {
  for (int row = 0; row < kNumRows; ++row) {
    for (int col = 0; col < kWordSize; ++col) {
      auto& s = grid_[Index(row, col)];
      if (s.Letter() != '-') {
        // if letter is already shown as CORRECT, it cannot be demoted
        if (alphabet->at(s.Letter() - 65) == Validity::CORRECT) continue;

        alphabet->at(s.Letter() - 65) = s.GetValidity();
      }
    }
  }
}

std::pair<const int, const int> Grid::GetGridDimensions() const { return {kNumRows, kWordSize}; }

std::string Grid::Name() { return "Grid_" + std::to_string(GetID()); }

std::string Grid::to_string() {
  std::stringstream ss;

  for (int row = 0; row < kNumRows; ++row) {
    for (int col = 0; col < kWordSize; ++col) {
      ss << GetSpace(row, col).to_string() << " ";
    }
    ss << "\n";
  }
  ss << "\n";

  return ss.str();
}

}  // namespace game::objects

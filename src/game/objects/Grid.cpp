#include "game/objects/Grid.h"

#include <algorithm>

namespace game::objects {

Grid::Grid(int word_size) : kWordSize(word_size), kNumRows(word_size + 1) { grid_ = new Space[kWordSize * kNumRows]; }

Grid::~Grid() { delete[] grid_; }

Space Grid::GetSpace(int row, int col) { return grid_[Index(row, col)]; }

void Grid::UpdateSpace(int row, int col, char c) { grid_[Index(row, col)].Letter(c); }

std::string Grid::GetCurrentGuess() {
  std::string guess;

  auto start_idx = Index(num_guess_, 0);
  for (int i = 0; i < kWordSize; ++i) {
    auto space = grid_[start_idx + i];
    guess += space.Letter();
  }

  return guess;
}

bool Grid::CheckGuess(const std::string& exp_word) {
  bool ret = true;

  auto start_idx = Index(num_guess_, 0);
  for (int i = 0; i < kWordSize; ++i) {
    auto& space = grid_[start_idx + i];
    if (space.Letter() == exp_word[i]) {
      space.SetValidity(Validity::CORRECT);
    } else if (std::find(exp_word.begin(), exp_word.end(), space.Letter()) != exp_word.end()) {
      space.SetValidity(Validity::CLOSE);
    } else {
      space.SetValidity(Validity::INVALID);
    }

    ret = false;
  }

  return ret;
}

std::string Grid::Name() { return "Grid_" + std::to_string(GetID()); }

// TODO:
std::string Grid::to_string() { return ""; }

}  // namespace game::objects

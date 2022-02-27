#include "game/objects/Space.h"

#include <iostream>
#include <sstream>

#include "game/Color.h"

namespace game::objects {

Space::Space() {}

bool Space::Check(char c) { return c == letter_; }

char Space::Letter() { return letter_; }

void Space::Letter(char c) { letter_ = std::toupper(c); }

Validity Space::GetValidity() { return validity_; }

void Space::SetValidity(Validity v) { validity_ = v; }

std::string Space::Name() { return "Space_" + std::to_string(GetID()); }

std::string Space::to_string() {
  std::stringstream ss;

  std::string l(1, letter_);
  switch (validity_) {
    case Validity::EMPTY:
      ss << color::wrap(l, color::Code::FG_DEFAULT);
      break;
    case Validity::INVALID:
      ss << color::wrap(l, color::Code::FG_RED);
      break;
    case Validity::CLOSE:
      ss << color::wrap(l, color::Code::FG_BLUE);
      break;
    case Validity::CORRECT:
      ss << color::wrap(l, color::Code::FG_GREEN);
      break;
  }
  return ss.str();
}

}  // namespace game::objects

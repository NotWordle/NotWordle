#ifndef INC_GAME_VALIDITY_H
#define INC_GAME_VALIDITY_H

#include <stdexcept>
#include <string>

namespace game {

enum class Validity { EMPTY = 0, INVALID = 1, CLOSE = 2, CORRECT = 3 };

inline std::string to_string(Validity v) {
  switch (v) {
    case Validity::EMPTY:
      return "EMPTY";
    case Validity::INVALID:
      return "INVALID";
    case Validity::CLOSE:
      return "CLOSE";
    case Validity::CORRECT:
      return "CORRECT";
    default:
      throw std::invalid_argument("Invalid Validity Enum given!");
  }
}

inline Validity from_string(const std::string& s) {
  if (s == "EMPTY") {
    return Validity::EMPTY;
  } else if (s == "INVALID") {
    return Validity::INVALID;
  } else if (s == "CLOSE") {
    return Validity::CLOSE;
  } else if (s == "CORRECT") {
    return Validity::CORRECT;
  } else {
    throw std::invalid_argument(s + " is not a valid Validity enum!");
  }
}
}  // namespace game
#endif  // INC_GAME_VALIDITY_H
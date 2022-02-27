#ifndef INC_GAME_VALIDITY_H_
#define INC_GAME_VALIDITY_H_

/// \file

#include <stdexcept>
#include <string>

namespace game {

/**
 * @brief enumeration for decided how close a guessed letter
 * is to the truth
 */
enum class Validity { EMPTY = 0, INVALID = 1, CLOSE = 2, CORRECT = 3 };

/**
 * @brief to string function for Validity enumeration
 *
 * @param v enum value being converted to a std::string
 * @return std::string name of the enum
 * @throws std::invalid_argument if bad enum value is given
 */
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

/**
 * @brief from_string function to convert a specfic set of strings to
 * Validity enum values
 *
 * @param s string that will be converted to equivalent Validity value
 * @return Validity equivalent to the given string
 * @throws std::invalid_argument if the string does not match any
 * names of the Validity enums
 */
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
#endif  // INC_GAME_VALIDITY_H_

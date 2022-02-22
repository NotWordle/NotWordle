#ifndef INC_GAME_COLOR_H_
#define INC_GAME_COLOR_H_

#include <string>
/// \file

/// blah
namespace game::color {

/**
 * @brief Color code enum
 *
 */
enum class Code {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_BLUE = 34,
  FG_DEFAULT = 39,
  BG_RED = 41,
  BG_GREEN = 42,
  BG_BLUE = 44,
  BG_DEFAULT = 49
};

inline std::string wrap(const std::string& str, Code c) {
  return "\033[" + std::to_string(static_cast<int>(c)) + "m" + str + "\033[0m";
}

}  // namespace game::color

#endif  // INC_GAME_COLOR_H_
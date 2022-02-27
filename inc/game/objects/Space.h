#ifndef INC_GAME_OBJECTS_SPACE_H_
#define INC_GAME_OBJECTS_SPACE_H_

#include <string>

#include "game/Validity.h"
#include "game/objects/GameObject.h"

namespace game::objects {

/**
 * @brief Space class for managing letters within
 * the game Grid
 */
class Space : public GameObject {
 public:
  /**
   * @brief Construct a new Space object with default values
   */
  Space();

  /**
   * @brief checks if the given character matches
   * the Space's character
   *
   * @param c letter being checked
   * @return true if c matches letter, false otherwise
   */
  bool Check(char c);

  /**
   * @brief Letter Getter
   *
   * @return char letter
   */
  char Letter();

  /**
   * @brief Letter Setter
   *
   * @param c new letter of the Space
   */
  void Letter(char c);

  /**
   * @brief Get the Validity field
   *
   * @return Validity
   */
  Validity GetValidity();

  /**
   * @brief Set the Validity field
   *
   * @param v new Validity value
   */
  void SetValidity(Validity v);

  /**
   * @brief Name getter
   *
   * @return std::string name of this object
   */
  std::string Name() override;

  /**
   * @brief coverts the letter to a string based on
   * its Validity value
   *
   * @return std::string wrapped letter
   */
  std::string to_string() override;

 private:
  /// underlying letter this space holds/displays
  char letter_{'-'};

  /// validity of the letter (i.e.)
  Validity validity_{Validity::EMPTY};
};
}  // namespace game::objects
#endif  // INC_GAME_OBJECTS_SPACE_H_

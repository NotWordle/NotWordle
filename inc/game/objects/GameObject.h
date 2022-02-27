#ifndef INC_GAME_OBJECTS_GAMEOBJECT_H_
#define INC_GAME_OBJECTS_GAMEOBJECT_H_

#include <string>

/// Simple ID counter for all GameObjects
static uint32_t ID_COUNTER = 0;

namespace game::objects {

/**
 * @class GameObject
 * @brief Top-Level class that all objects of the game will inherit
 * from, this is mostly for book-keeping
 *
 */
class GameObject {
 public:
  /// pure-virtual function for naming the object
  virtual std::string Name() = 0;

  /// pure-virtual function for converting the object to a printable string
  virtual std::string to_string() = 0;

  /**
   * @brief Construct a new GameObject. Also establishes the ID of the object
   */
  GameObject() : kID(++ID_COUNTER) {}

  /**
   * @brief Getter for the ID of the object
   *
   * @return uint32_t ID
   */
  uint32_t GetID() { return kID; }

 private:
  /// unique ID of the object
  const uint32_t kID;
};
}  // namespace game::objects
#endif  // INC_GAME_OBJECTS_GAMEOBJECT_H_

#ifndef INC_GAME_OBJECTS_GAME_OBJECT_H_
#define INC_GAME_OBJECTS_GAME_OBJECT_H_

#include <string>

static uint32_t ID_COUNTER = 0;
namespace game::objects {
class GameObject {
 public:
  virtual std::string Name() = 0;
  virtual std::string to_string() = 0;

  GameObject() : kID(++ID_COUNTER) {}

  uint32_t GetID() { return kID; }

 private:
  const uint32_t kID;
};
}  // namespace game::objects
#endif  // INC_GAME_OBJECTS_GAME_OBJECT_H_
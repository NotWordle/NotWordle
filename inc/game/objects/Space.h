#ifndef INC_GAME_OBJECTS_SPACE_H_
#define INC_GAME_OBJECTS_SPACE_H_

#include "inc/game/Validity.h"
#include "inc/game/objects/GameObject.h"

namespace game::objects {
class Space : public GameObject {
 public:
  Space();

  bool check(char c);

  char Letter();
  void Letter(char c);

  Validity GetValidity();
  void SetValidity(Validity v);

  std::string Name() override;
  std::string to_string() override;

 private:
  char letter_;
  Validity validity_;
};
}  // namespace game::objects
#endif  // INC_GAME_OBJECTS_SPACE_H_
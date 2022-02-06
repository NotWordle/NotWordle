#ifndef INC_GAME_DICTIONARY_H_
#define INC_GAME_DICTIONARY_H_

#include <set>
#include <string>

namespace game {
class Dictionary {
 public:
  Dictionary();

  void LoadWords();

  bool Exists(const std::string& word) const;

 private:
  std::set<std::string> words_;
};
}  // namespace game

#endif  // INC_GAME_DICTIONARY_H_

#include <iostream>

#include "Version.h"
#include "game/Game.h"

int main() {
  std::cout << "Version " << NotWordle_VERSION_MAJOR << "." << NotWordle_VERSION_MINOR << "\n";

  game::Game g;
  g.Run(std::cout, std::cin);

  return 0;
}

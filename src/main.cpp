#include <iostream>

#include "Version.h"
#include "game/Game.h"

int main() {
  std::cout << "hello world!\n";

  std::cout << "Version " << NotWordle_VERSION_MAJOR << "."
            << NotWordle_VERSION_MINOR << "\n";

  return 0;
}
#include "game/objects/Space.h"

namespace game::objects {

Space::Space() : letter_(0), validity_(Validity::EMPTY) {}

bool Space::check(char c) { return c == letter_; }

char Space::Letter() { return letter_; }

void Space::Letter(char c) { letter_ = c; }

Validity Space::GetValidity() { return validity_; }

void Space::SetValidity(Validity v) { validity_ = v; }

std::string Space::Name() { return "Space_" + std::to_string(GetID()); }

// TODO:
std::string to_string() { return ""; }
}  // namespace game::objects
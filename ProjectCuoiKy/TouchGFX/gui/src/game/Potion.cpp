#include <game/Potion.hpp>

namespace game {

Potion::Potion(int healAmount)
    : Entity(Type::POTION, 1, 1, true), healAmount(healAmount) {}

} // namespace game

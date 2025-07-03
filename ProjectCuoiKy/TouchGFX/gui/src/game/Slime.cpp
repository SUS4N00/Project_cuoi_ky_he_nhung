#include <game/Slime.hpp>

namespace game {
constexpr int Slime::DEFAULT_HP;
constexpr int Slime::DEFAULT_ATTACK;
constexpr int Slime::DEFAULT_SPEED;

Slime::Slime(int hp, int speed)
    : Entity(hp > 3 ? Entity::BIG_SLIME : Entity::SMALL_SLIME, hp, speed, true) {}

int Slime::getAttackForType(game::Entity::Type type) {
    if (type == game::Entity::BIG_SLIME) return 3;
    else return 1;
}
} // namespace game

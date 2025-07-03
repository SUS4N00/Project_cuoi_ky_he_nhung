#include <game/Player.hpp>

namespace game {

Player::Player(int hp, int speed)
    : Entity(Entity::PLAYER, hp, speed, true) {}

} // namespace game

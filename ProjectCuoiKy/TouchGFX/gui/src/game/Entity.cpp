#include <game/Entity.hpp>

namespace game {

Entity::Entity(Type type, int hp, int speed, bool canMove)
    : type(type), hp(hp), speed(speed), canMove(canMove) {}

int Entity::getHP() const { return hp; }
int Entity::getSpeed() const { return speed; }
Entity::Type Entity::getType() const { return type; }
void Entity::setHP(int hp_) { hp = hp_; }

} // namespace game

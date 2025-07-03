#pragma once
#include <game/Entity.hpp>

namespace game {
class Goblin : public Entity {
public:
    static constexpr int DEFAULT_HP = 5;
    static constexpr int DEFAULT_ATTACK = 1;
    static constexpr int DEFAULT_SPEED = 1;
    Goblin(int hp = DEFAULT_HP, int speed = DEFAULT_SPEED)
        : Entity(Entity::GOBLIN, hp, speed, true) {}
};
} // namespace game

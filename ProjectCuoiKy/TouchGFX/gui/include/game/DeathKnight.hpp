#pragma once
#include <game/Entity.hpp>

namespace game {
class DeathKnight : public Entity {
public:
    static constexpr int DEFAULT_HP = 8;
    static constexpr int DEFAULT_ATTACK = 2;
    static constexpr int DEFAULT_SPEED = 1;

    DeathKnight(int hp = DEFAULT_HP, int speed = DEFAULT_SPEED)
        : Entity(Entity::DEATH_KNIGHT, hp, speed, true) {}
};
} // namespace game

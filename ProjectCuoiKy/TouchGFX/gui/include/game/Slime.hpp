#pragma once
#include <game/Entity.hpp>

namespace game {
class Slime : public Entity {
public:
    static constexpr int DEFAULT_HP = 3;
    static constexpr int DEFAULT_ATTACK = 1;
    static constexpr int DEFAULT_SPEED = 1;

    Slime(int hp, int speed);

    // Trả về damage theo type slime
    static int getAttackForType(game::Entity::Type type);
};
} // namespace game

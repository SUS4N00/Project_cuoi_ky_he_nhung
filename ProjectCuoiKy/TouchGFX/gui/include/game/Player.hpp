#pragma once
#include <game/Entity.hpp>

namespace game {

class Player : public Entity {
public:
    static constexpr int DEFAULT_HP = 10;
    static constexpr int DEFAULT_ATTACK = 2;
    static constexpr int DEFAULT_SPEED = 2;

    Player(int hp, int speed);
};

} // namespace game

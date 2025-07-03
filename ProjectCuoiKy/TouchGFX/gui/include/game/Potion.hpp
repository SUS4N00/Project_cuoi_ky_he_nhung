#pragma once
#include <game/Entity.hpp>

namespace game {

class Potion : public Entity {
public:
    Potion(int healAmount = 5); // có thể điều chỉnh lượng máu hồi

private:
    int healAmount;
};

} // namespace game

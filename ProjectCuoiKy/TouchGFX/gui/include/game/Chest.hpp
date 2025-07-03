#pragma once
#include <game/Entity.hpp>
#include <functional>

namespace game {
class Chest : public Entity {
public:
    static constexpr int DEFAULT_HP = 5;
    static constexpr int DEFAULT_ATTACK = 0;
    static constexpr int DEFAULT_SPEED = 0;
    Chest(int hp = DEFAULT_HP, int posX = -1, int posY = -1);
    // Xóa các hàm override không còn dùng
    std::function<void(int, int)> onReward;
    int posX = -1, posY = -1; // Vị trí của rương trên lưới
};
} // namespace game

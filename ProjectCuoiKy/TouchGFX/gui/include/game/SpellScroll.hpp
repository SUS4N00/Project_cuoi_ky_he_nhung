#pragma once
#include <game/Entity.hpp>
#include <functional>

namespace game {

class SpellScroll : public Entity {
public:
    SpellScroll();
    SpellScroll(int x, int y); // constructor có vị trí nếu cần
    void onTurnStart();

    bool damagedThisTurn;

    // Callback khi bị phá để tăng tích trữ phép
    std::function<void()> onCollect;
    int posX = -1, posY = -1;
};

} // namespace game

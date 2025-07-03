#include <gui/common/Global.hpp>

GameMode Global::gameMode = GAME_EASY; // Mặc định là chế độ EASY
int Global::DamageBonus = 0; // Khởi tạo DamageBonus

int Global::getDamageBonus() {
    return DamageBonus;
}
void Global::setDamageBonus(int bonus) {
    DamageBonus = bonus;
}
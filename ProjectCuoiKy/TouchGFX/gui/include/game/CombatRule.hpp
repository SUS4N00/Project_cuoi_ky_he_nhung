#pragma once
#include <game/Entity.hpp>
#include <game/Player.hpp>
#include <game/Goblin.hpp>
#include <game/Slime.hpp>

namespace game {
struct CombatResult {
    int attackerHP;
    int defenderHP;
    Entity::Type attackerType;
    Entity::Type defenderType;
    bool attackerHidden;
    bool defenderHidden;
    int damageToDefender; // Số máu thực nhận (cộng hoặc trừ)
    Entity::Type rewardType = Entity::NONE; // Phần thưởng sinh ra sau khi phá CHEST
};

class CombatRule {
public:
    // Xử lý toàn bộ combat, trả về kết quả đầy đủ
    // Chỉ thao tác trên dữ liệu, không gọi hàm object
    static CombatResult resolveCombat(Entity::Type attackerType, int attackerHP, int attackerAttack, Entity::Type defenderType, int defenderHP, int potionHeal = 5, bool isSpellAttack = false);
};
} // namespace game

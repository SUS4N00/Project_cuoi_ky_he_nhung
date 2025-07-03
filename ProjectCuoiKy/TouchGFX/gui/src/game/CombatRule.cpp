#include <game/CombatRule.hpp>
#include <game/RandomUtil.hpp>

namespace game {
CombatResult CombatRule::resolveCombat(Entity::Type attackerType, int attackerHP, int attackerAttack, Entity::Type defenderType, int defenderHP, int potionHeal, bool isSpellAttack) {
    CombatResult result{attackerHP, defenderHP, attackerType, defenderType, false, false, 0};
    // Nếu là phép và các loại không bị phép tác động
    if (isSpellAttack) {
        if (defenderType == Entity::SPELL_SCROLL || defenderType == Entity::POTION  ) {
            result.damageToDefender = 0;
            return result;
        }
        if (defenderType == Entity::CHEST || defenderType == Entity::ROCK) {
            result.defenderHP -= 1;
            result.damageToDefender = -1;
            if (result.defenderHP <= 0) {
                result.defenderHP = 0;
                result.defenderHidden = true;
                int r = RandomUtil::randRange(0, 1);
                if (r == 0) result.rewardType = Entity::POTION;
                else result.rewardType = Entity::SPELL_SCROLL;
            }
            return result;
        }
    }
    if ((attackerType == Entity::SMALL_SLIME || attackerType == Entity::BIG_SLIME) &&
        (defenderType == Entity::SMALL_SLIME || defenderType == Entity::BIG_SLIME)) {
        result.defenderHP += result.attackerHP;
        result.attackerHP = 0;
        result.attackerHidden = true;
        if (result.defenderHP > 3) {
            result.defenderType = Entity::BIG_SLIME;
            result.damageToDefender = result.attackerHP;
        } else {
            result.defenderType = Entity::SMALL_SLIME;
            result.damageToDefender = result.attackerHP;
        }
        return result;
    }
    if (defenderType == Entity::POTION) {
        result.defenderHP = 0;
        result.defenderHidden = true;
        if (attackerType == Entity::PLAYER) {
            result.attackerHP += potionHeal;
        }
        result.damageToDefender = -1;
        return result;
    }
    if (defenderType == Entity::SPELL_SCROLL) {
        result.defenderHP = 0;
        result.defenderHidden = true;
        result.damageToDefender = -1;
        return result;
    }
    if (defenderType == Entity::ROCK) {
        result.defenderHP -= 1;
        result.damageToDefender = -1;
        if (result.defenderHP <= 0) {
            result.defenderHP = 0;
            result.defenderHidden = true;
        }
        return result;
    }
    if (defenderType == Entity::CHEST) {
        result.defenderHP -= 1;
        result.damageToDefender = -1;
        if (result.defenderHP <= 0) {
            result.defenderHP = 0;
            result.defenderHidden = true;
            int r = RandomUtil::randRange(0, 1);
            if (r == 0) result.rewardType = Entity::POTION;
            else result.rewardType = Entity::SPELL_SCROLL;
        }
        return result;
    }
    if (defenderType == Entity::DOOR) {
        if (attackerType != Entity::PLAYER) {
            result.damageToDefender = 0;
            return result;
        }
        result.defenderHP -= 1;
        result.damageToDefender = -1;
        if (result.defenderHP <= 0) {
            result.defenderHP = 0;
            result.defenderHidden = true;
            result.rewardType = Entity::OPEN_DOOR;
        }
        return result;
    }
    if (defenderType == Entity::OPEN_DOOR) {
        result.damageToDefender = 0;
        return result;
    }
    int attack = attackerAttack;
    result.defenderHP -= attack;
    result.damageToDefender = -attack;
    if ((defenderType == Entity::SMALL_SLIME || defenderType == Entity::BIG_SLIME) && result.defenderHP > 0) {
        if (result.defenderHP > 3) result.defenderType = Entity::BIG_SLIME;
        else result.defenderType = Entity::SMALL_SLIME;
    }
    if (result.defenderHP <= 0) {
        result.defenderHP = 0;
        result.defenderHidden = true;
    }
    return result;
}
} // namespace game

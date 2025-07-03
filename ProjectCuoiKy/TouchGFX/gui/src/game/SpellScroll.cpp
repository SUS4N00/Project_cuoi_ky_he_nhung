#include <game/SpellScroll.hpp>
#include <game/Player.hpp>

namespace game {

SpellScroll::SpellScroll() : Entity(Entity::SPELL_SCROLL, 1, 0, false), damagedThisTurn(false) {}

SpellScroll::SpellScroll(int x, int y)
    : Entity(Entity::SPELL_SCROLL, 1, 0, false), damagedThisTurn(false), posX(x), posY(y) {}

void SpellScroll::onTurnStart() {
    damagedThisTurn = false;
}

} // namespace game

#include <game/Chest.hpp>
#include <game/SpellScroll.hpp>
#include <game/Potion.hpp>
#include <cstdlib>

namespace game {

Chest::Chest(int hp, int posX, int posY)
    : Entity(Type::CHEST, hp, 0, false) // Không di chuyển, không tấn công
{
    this->posX = posX;
    this->posY = posY;
}

} // namespace game

#include <game/Rock.hpp>

namespace game {

Rock::Rock(int hp)
    : Entity(Type::ROCK, hp, 0, false) // Không di chuyển, không tấn công
{
}

} // namespace game

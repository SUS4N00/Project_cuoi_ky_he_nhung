#include <game/Door.hpp>

namespace game {

Door::Door() : Entity(Entity::DOOR, 5, 0, false) {}

OpenDoor::OpenDoor() : Entity(Entity::OPEN_DOOR, 1, 0, false) {}

} // namespace game

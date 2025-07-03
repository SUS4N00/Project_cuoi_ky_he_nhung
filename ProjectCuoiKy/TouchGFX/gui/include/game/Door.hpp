#pragma once
#include <game/Entity.hpp>
#include <functional>

namespace game {
class Door : public Entity {
public:
    using DoorDestroyedCallback = std::function<void(int, int, Entity*)>;
    Door();
    void setOnDestroyedCallback(DoorDestroyedCallback cb) { onDestroyed = cb; }
    void setDoorPosition(int x, int y) { posX = x; posY = y; }
private:
    DoorDestroyedCallback onDestroyed;
    int posX = -1, posY = -1;
};
class OpenDoor : public Entity {
public:
    OpenDoor();
};
} // namespace game

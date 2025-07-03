#pragma once
#include <game/Entity.hpp>

namespace game {

class GameGrid {
public:
    static const int WIDTH = 6;
    static const int HEIGHT = 6;
    GameGrid();
    Entity* get(int x, int y) const;
    void set(int x, int y, Entity* entity);
    void move(int fromX, int fromY, int toX, int toY);
private:
    Entity* grid[WIDTH][HEIGHT];
};

} // namespace game

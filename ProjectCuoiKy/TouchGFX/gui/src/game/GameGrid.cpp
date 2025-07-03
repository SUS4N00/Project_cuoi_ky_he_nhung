#include <game/GameGrid.hpp>

namespace game {

GameGrid::GameGrid() {
    for (int x = 0; x < WIDTH; ++x)
        for (int y = 0; y < HEIGHT; ++y)
            grid[x][y] = nullptr;
}

Entity* GameGrid::get(int x, int y) const {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return nullptr;
    return grid[x][y];
}

void GameGrid::set(int x, int y, Entity* entity) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    grid[x][y] = entity;
}

void GameGrid::move(int fromX, int fromY, int toX, int toY) {
    if (get(fromX, fromY) && !get(toX, toY)) {
        grid[toX][toY] = grid[fromX][fromY];
        grid[fromX][fromY] = nullptr;
    }
}

} // namespace game

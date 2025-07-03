#include <game/EntitySpawner.hpp>
#include <game/Goblin.hpp>
#include <game/Slime.hpp>
#include <game/DeathKnight.hpp>
#include <game/Chest.hpp>
#include <game/RandomUtil.hpp>
#include <gui/containers/ContainerEntity.hpp>

namespace game {

bool EntitySpawner::spawnRandomGoblin(ContainerEntity* grid[6][6]) {
    int emptyCells[36][2];
    int n = 0;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (!grid[row][col]->isVisible() || grid[row][col]->getAvatarType() == Entity::NONE) {
                emptyCells[n][0] = row;
                emptyCells[n][1] = col;
                ++n;
            }
        }
    }
    if (n == 0) return false;
    int idx = RandomUtil::randRange(0, n-1);
    int row = emptyCells[idx][0];
    int col = emptyCells[idx][1];
    grid[row][col]->setVisible(true);
    grid[row][col]->setAvatar(Entity::GOBLIN);
    grid[row][col]->setHPText(Goblin::DEFAULT_HP);
    grid[row][col]->setSpeed(Goblin::DEFAULT_SPEED);
    grid[row][col]->fadeInAvatar();
    return true;
}

bool EntitySpawner::spawnRandomSlime(ContainerEntity* grid[6][6]) {
    int emptyCells[36][2];
    int n = 0;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (!grid[row][col]->isVisible() || grid[row][col]->getAvatarType() == Entity::NONE) {
                emptyCells[n][0] = row;
                emptyCells[n][1] = col;
                ++n;
            }
        }
    }
    if (n == 0) return false;
    int idx = RandomUtil::randRange(0, n-1);
    int row = emptyCells[idx][0];
    int col = emptyCells[idx][1];
    grid[row][col]->setVisible(true);
    grid[row][col]->setAvatar(Entity::SMALL_SLIME);
    grid[row][col]->setHPText(Slime::DEFAULT_HP);
    grid[row][col]->setSpeed(Slime::DEFAULT_SPEED);
    grid[row][col]->fadeInAvatar();
    return true;
}

bool EntitySpawner::spawnRandomDeathKnight(ContainerEntity* grid[6][6]) {
    int emptyCells[36][2];
    int n = 0;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (!grid[row][col]->isVisible() || grid[row][col]->getAvatarType() == Entity::NONE) {
                emptyCells[n][0] = row;
                emptyCells[n][1] = col;
                ++n;
            }
        }
    }
    if (n == 0) return false;
    int idx = RandomUtil::randRange(0, n-1);
    int row = emptyCells[idx][0];
    int col = emptyCells[idx][1];
    grid[row][col]->setVisible(true);
    grid[row][col]->setAvatar(Entity::DEATH_KNIGHT);
    grid[row][col]->setHPText(DeathKnight::DEFAULT_HP);
    grid[row][col]->setSpeed(DeathKnight::DEFAULT_SPEED);
    grid[row][col]->fadeInAvatar();
    return true;
}

bool EntitySpawner::spawnRandomChest(ContainerEntity* grid[6][6]) {
    int emptyCells[36][2];
    int n = 0;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (!grid[row][col]->isVisible() || grid[row][col]->getAvatarType() == Entity::NONE) {
                emptyCells[n][0] = row;
                emptyCells[n][1] = col;
                ++n;
            }
        }
    }
    if (n == 0) return false;
    int idx = RandomUtil::randRange(0, n-1);
    int row = emptyCells[idx][0];
    int col = emptyCells[idx][1];
    grid[row][col]->setVisible(true);
    grid[row][col]->setAvatar(Entity::CHEST);
    grid[row][col]->setHPText(Chest::DEFAULT_HP);
    grid[row][col]->setSpeed(Chest::DEFAULT_SPEED);
    grid[row][col]->fadeInAvatar();
    return true;
}

bool EntitySpawner::spawnRandomEntity(ContainerEntity* grid[6][6]) {
    int r = RandomUtil::randRange(1, 100);
    if (r <= 60) {
        return spawnRandomGoblin(grid);
    } else if (r <= 90) {
        return spawnRandomSlime(grid);
    } else if (r <= 100) {
        if (RandomUtil::randRange(0, 1) == 0) {
            return spawnRandomDeathKnight(grid);
        } else {
            return spawnRandomChest(grid);
        }
    }
    return false;
}

} // namespace game

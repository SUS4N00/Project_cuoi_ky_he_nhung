#include <gui/common/Global.hpp>
#include <game/EntitySpawner.hpp>
#include <game/GameStageManager.hpp>
#include <game/Entity.hpp>
#include <game/RandomUtil.hpp>
#include <utility>
#include <gui/common/Global.hpp>

namespace game {

GameStageManager::GameStageManager(ContainerEntity* (&gridRef)[6][6]) : grid(gridRef) {}

void GameStageManager::clearStageExceptPlayer() {
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (grid[row][col]->getAvatarType() != Entity::PLAYER) {
                grid[row][col]->setVisible(false);
                grid[row][col]->setAvatar(Entity::NONE);
                grid[row][col]->setHPText(0);
                grid[row][col]->setSpeed(0);
            }
        }
    }
}

void GameStageManager::setupNewStage(int stage) {
    // Set monster damage bonus based on game mode and stage
    int bonus = 0;
    if (Global::gameMode == GAME_NORMAL) {
        bonus = stage;
    } else if (Global::gameMode == GAME_HARD) {
        bonus = stage * 2;
    }
    Global::setDamageBonus(bonus);

    // Reset progress và set max_progress cho stage mới
    progress = 0;
    if (stage == 1) max_progress = 3;
    else if (stage == 2) max_progress = 4;
    else if (stage == 3) max_progress = 5;
    else max_progress = 6 + stage; // hoặc logic khác cho stage cao
    clearStageExceptPlayer();
    // Spawn entity tùy theo stage
    if (stage == 1) {
        // Stage 1: chỉ có slime nhỏ + 1 đá
        grid[2][2]->setVisible(true);
        grid[2][2]->setAvatar(Entity::SMALL_SLIME);
        grid[2][2]->setHPText(2);
        grid[2][2]->setSpeed(1);
        grid[2][2]->setAttack(Slime::DEFAULT_ATTACK + bonus);
        // Spawn đá
        grid[0][3]->setVisible(true);
        grid[0][3]->setAvatar(Entity::ROCK);
        grid[0][3]->setHPText(3);
        grid[0][3]->setSpeed(0);
    } else if (stage == 2) {
        // Stage 2: slime + goblin + 2 đá
        grid[2][2]->setVisible(true);
        grid[2][2]->setAvatar(Entity::SMALL_SLIME);
        grid[2][2]->setHPText(2);
        grid[2][2]->setSpeed(1);
        grid[2][2]->setAttack(Slime::DEFAULT_ATTACK + bonus);
        grid[4][1]->setVisible(true);
        grid[4][1]->setAvatar(Entity::GOBLIN);
        grid[4][1]->setHPText(3);
        grid[4][1]->setSpeed(1);
        grid[4][1]->setAttack(Goblin::DEFAULT_ATTACK + bonus);
        // Spawn đá
        grid[0][3]->setVisible(true);
        grid[0][3]->setAvatar(Entity::ROCK);
        grid[0][3]->setHPText(3);
        grid[0][3]->setSpeed(0);
        grid[5][2]->setVisible(true);
        grid[5][2]->setAvatar(Entity::ROCK);
        grid[5][2]->setHPText(3);
        grid[5][2]->setSpeed(0);
    } else if (stage == 3) {
        // Stage 3: slime + goblin + deathknight + 2 đá
        grid[2][2]->setVisible(true);
        grid[2][2]->setAvatar(Entity::SMALL_SLIME);
        grid[2][2]->setHPText(2);
        grid[2][2]->setSpeed(1);
        grid[2][2]->setAttack(Slime::DEFAULT_ATTACK + bonus);
        grid[4][1]->setVisible(true);
        grid[4][1]->setAvatar(Entity::GOBLIN);
        grid[4][1]->setHPText(3);
        grid[4][1]->setSpeed(1);
        grid[4][1]->setAttack(Goblin::DEFAULT_ATTACK + bonus);
        grid[1][4]->setVisible(true);
        grid[1][4]->setAvatar(Entity::DEATH_KNIGHT);
        grid[1][4]->setHPText(5);
        grid[1][4]->setSpeed(1);
        grid[1][4]->setAttack(DeathKnight::DEFAULT_ATTACK + bonus);
        // Spawn đá
        grid[0][3]->setVisible(true);
        grid[0][3]->setAvatar(Entity::ROCK);
        grid[0][3]->setHPText(3);
        grid[0][3]->setSpeed(0);
        grid[5][2]->setVisible(true);
        grid[5][2]->setAvatar(Entity::ROCK);
        grid[5][2]->setHPText(3);
        grid[5][2]->setSpeed(0);
    } else {
        // Stage khác: random hoặc nâng độ khó
        // Spawn 3 viên đá ở 3 vị trí ngẫu nhiên không trùng player, không trùng nhau
        int spawned = 0;
        while (spawned < 3) {
            int r = RandomUtil::randRange(0, 5);
            int c = RandomUtil::randRange(0, 5);
            if (grid[r][c]->getAvatarType() == Entity::NONE) {
                grid[r][c]->setVisible(true);
                grid[r][c]->setAvatar(Entity::ROCK);
                grid[r][c]->setHPText(3);
                grid[r][c]->setSpeed(0);
                spawned++;
            }
        }
        // Có thể spawn thêm quái hoặc vật phẩm khác nếu muốn
    }
}

void GameStageManager::onPlayerMove() {
    ++progress;
    spawnDoorIfNeeded();
}

void GameStageManager::spawnDoorIfNeeded() {
    // Chỉ spawn DOOR nếu chưa có DOOR trên lưới
    bool doorExists = false;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (grid[row][col]->getAvatarType() == Entity::DOOR) {
                doorExists = true;
                break;
            }
        }
        if (doorExists) break;
    }
    if (progress == max_progress && !doorExists) {
        // Tìm tất cả ô trống bằng mảng tĩnh, không dùng vector
        int emptyCells[36][2];
        int emptyCount = 0;
        for (int row = 0; row < 6; ++row) {
            for (int col = 0; col < 6; ++col) {
                if (grid[row][col]->getAvatarType() == Entity::NONE) {
                    emptyCells[emptyCount][0] = row;
                    emptyCells[emptyCount][1] = col;
                    ++emptyCount;
                }
            }
        }
        if (emptyCount > 0) {
            int idx = RandomUtil::randRange(0, emptyCount - 1);
            int doorRow = emptyCells[idx][0];
            int doorCol = emptyCells[idx][1];
            grid[doorRow][doorCol]->setVisible(true);
            grid[doorRow][doorCol]->setAvatar(Entity::DOOR);
            grid[doorRow][doorCol]->setHPText(3);
            grid[doorRow][doorCol]->setSpeed(0);
        }
    }
}

void GameStageManager::resetProgress() {
    progress = 0;
}

} // namespace game

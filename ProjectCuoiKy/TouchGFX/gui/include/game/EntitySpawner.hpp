#pragma once
#include <game/Entity.hpp>
#include <game/Goblin.hpp>
#include <game/Slime.hpp>
#include <game/DeathKnight.hpp>
#include <game/Chest.hpp>
#include <game/RandomUtil.hpp>
#include <gui/containers/ContainerEntity.hpp>

namespace game {
class EntitySpawner {
public:
    // Spawn goblin ngẫu nhiên lên lưới 6x6, tránh vị trí player
    static bool spawnRandomGoblin(ContainerEntity* grid[6][6]);

    // Spawn slime ngẫu nhiên lên lưới 6x6, tránh vị trí player
    static bool spawnRandomSlime(ContainerEntity* grid[6][6]);

    // Spawn death knight ngẫu nhiên lên lưới 6x6, tránh vị trí player
    static bool spawnRandomDeathKnight(ContainerEntity* grid[6][6]);

    // Spawn chest ngẫu nhiên lên lưới 6x6, tránh vị trí player
    static bool spawnRandomChest(ContainerEntity* grid[6][6]);

    // Spawn entity ngẫu nhiên theo tỉ lệ: 60% Goblin, 30% Slime, 10% DeathKnight, 10% Chest
    static bool spawnRandomEntity(ContainerEntity* grid[6][6]);
};
} // namespace game

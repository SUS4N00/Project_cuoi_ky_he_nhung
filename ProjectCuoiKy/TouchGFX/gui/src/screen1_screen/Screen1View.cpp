#include <gui/screen1_screen/Screen1View.hpp>
#include <game/Entity.hpp>
#include <game/EntitySpawner.hpp>
#include <game/CombatRule.hpp>
#include <game/GameStageManager.hpp>
#include <gui/common/Global.hpp>

using namespace game;

// Screen1View: Quản lý màn chơi chính, xử lý di chuyển, combat, lên cấp, cập nhật UI, và chuyển màn thắng/thua.

Screen1View::Screen1View()
    : stageManager(gridContainers) // Khởi tạo stageManager với lưới UI
{
    // Map 36 containerEntity1_x vào gridContainers[6][6] theo thứ tự hàng ngang
    ContainerEntity* allContainers[36] = {
        &containerEntity1_0, &containerEntity1_1, &containerEntity1_2, &containerEntity1_3, &containerEntity1_4, &containerEntity1_5,
        &containerEntity1_6, &containerEntity1_7, &containerEntity1_8, &containerEntity1_9, &containerEntity1_10, &containerEntity1_11,
        &containerEntity1_12, &containerEntity1_13, &containerEntity1_14, &containerEntity1_15, &containerEntity1_16, &containerEntity1_17,
        &containerEntity1_18, &containerEntity1_19, &containerEntity1_20, &containerEntity1_21, &containerEntity1_22, &containerEntity1_23,
        &containerEntity1_24, &containerEntity1_25, &containerEntity1_26, &containerEntity1_27, &containerEntity1_28, &containerEntity1_29,
        &containerEntity1_30, &containerEntity1_31, &containerEntity1_32, &containerEntity1_33, &containerEntity1_34, &containerEntity1_35
    };
    int idx = 0;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            gridContainers[row][col] = allContainers[idx++];
        }
    }
}

void Screen1View::handleGestureEvent(const GestureEvent& evt)
{   
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
        if (evt.getVelocity() > 0)
        {
            // Vuốt sang phải
             functionMoveRight();

        }
        else
        {
            // Vuốt sang trái
            functionMoveLeft();
        }
    }
    else if (evt.getType() == GestureEvent::SWIPE_VERTICAL)
    {
        if (evt.getVelocity() > 0)
        {
            // Vuốt xuống
             functionMoveDown();
        }
        else
        {
            // Vuốt lên
            functionMoveUp();
        }
    }
}

void Screen1View::setupGrid()
{
    // Lấy trạng thái player hiện tại (máu, tốc độ) để giữ lại khi sang màn mới
    int playerHP = 10, playerSpeed = 2;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (gridContainers[row][col]->isVisible() && gridContainers[row][col]->getAvatarType() == game::Entity::PLAYER) {
                playerHP = gridContainers[row][col]->getHP();
                playerSpeed = gridContainers[row][col]->getSpeed();
            }
        }
    }
    // Tìm vị trí OPEN_DOOR nếu có để đặt player đúng vị trí cửa mở
    int openDoorRow = -1, openDoorCol = -1;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (gridContainers[row][col]->isVisible() && gridContainers[row][col]->getAvatarType() == game::Entity::OPEN_DOOR) {
                openDoorRow = row;
                openDoorCol = col;
            }
        }
    }
    // Xóa toàn bộ entity trên lưới (ẩn, reset avatar, máu, speed)
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            gridContainers[row][col]->setVisible(false);
            gridContainers[row][col]->setAvatar(game::Entity::NONE);
            gridContainers[row][col]->setHPText(0);
            gridContainers[row][col]->setSpeed(0);
        }
    }
    // Thiết lập entity cho màn mới dựa trên stage hiện tại
    int currentStage = stageManager.getCurrentStage();
    stageManager.setupNewStage(currentStage);
    // Đảm bảo player luôn ở đúng vị trí cửa nếu có, nếu không thì ở vị trí mặc định (2,2)
    int playerRow = (openDoorRow != -1) ? openDoorRow : 2;
    int playerCol = (openDoorCol != -1) ? openDoorCol : 2;
    gridContainers[playerRow][playerCol]->setVisible(true);
    gridContainers[playerRow][playerCol]->setAvatar(game::Entity::PLAYER);
    gridContainers[playerRow][playerCol]->setHPText(playerHP);
    gridContainers[playerRow][playerCol]->setSpeed(playerSpeed);
    // Reset spellPoint và cập nhật UI khi qua màn mới
    spellPoint = 0;
    updateSpellCounter();
    // Reset exp/level UI khi qua màn mới
    updateLevelUI();
    // Sau khi qua màn (khi gọi setupGrid từ phá OPEN_DOOR), tăng stage
    currentStage++;
    stageManager.setCurrentStage(currentStage);
    // Kiểm tra nếu vượt quá max_stage thì chuyển sang màn hình chiến thắng
    if (stageManager.isGameWin()) {
        application().gotoScreen5ScreenBlockTransition();
        return;
    }
}

void Screen1View::setupScreen()
{
    // Khởi tạo màn hình, setup lưới và reset progress stage
    Screen1ViewBase::setupScreen();
    setupGrid();
    stageManager.resetProgress(); // Reset progress sau khi setupNewStage để logic spawn cửa vẫn hoạt động đúng
}

void Screen1View::updateGridUI() {
    // Cập nhật UI dựa trên grid: hiển thị avatar, máu, ẩn các ô không còn entity
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (gridContainers[row][col]->getHP() > 0) {
                gridContainers[row][col]->setVisible(true);
                gridContainers[row][col]->setAvatar(grid[row][col]->getType());
                gridContainers[row][col]->setHPText(grid[row][col]->getHP());
                gridContainers[row][col]->invalidate();
            } else {
                gridContainers[row][col]->setVisible(false); // Ẩn các ô không còn entity
            }
        }
    }
}

void Screen1View::moveEntities(int dx, int dy) {
    // Di chuyển toàn bộ entity trên lưới theo hướng dx, dy
    struct CellData {
        game::Entity::Type avatarType;
        int hp;
        int speed;
        bool visible;
    };
    CellData oldGrid[6][6];
    // 1. Sao chép trạng thái hiện tại vào oldGrid
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            oldGrid[row][col].visible = gridContainers[row][col]->isVisible();
            oldGrid[row][col].avatarType = gridContainers[row][col]->getAvatarType();
            oldGrid[row][col].hp = gridContainers[row][col]->getHP();
            oldGrid[row][col].speed = gridContainers[row][col]->getSpeed();
        }
    }
    // 2. Tạo lưới mới hoàn toàn rỗng
    CellData newGrid[6][6];
    for (int row = 0; row < 6; ++row)
        for (int col = 0; col < 6; ++col)
            newGrid[row][col] = {game::Entity::NONE, 0, 0, false};
    // Thêm biến cờ kiểm tra player tấn công thường vào OPEN_DOOR mà không gây damage
    bool playerAttackOpenDoorNoDamage = false;
    // 3. Di chuyển từng entity đúng số ô speed từ vị trí thực tế
    int start = (dx == 1 || dy == 1) ? 5 : 0;
    int end = (dx == 1 || dy == 1) ? -1 : 6;
    int step = (dx == 1 || dy == 1) ? -1 : 1;
    for (int i = 0; i < 6; ++i) {
        for (int j = start; j != end; j += step) {
            int row = (dy == 0) ? i : j;
            int col = (dx == 0) ? i : j;
            if (oldGrid[row][col].visible) {
                int nrow = row, ncol = col;
                int maxMove = oldGrid[row][col].speed;
                for (int s = 1; s <= maxMove; ++s) {
                    int trow = nrow + dy, tcol = ncol + dx;
                    if (trow < 0 || trow >= 6 || tcol < 0 || tcol >= 6) break;
                    if (newGrid[trow][tcol].visible) {
                        int attackerAttack = 1;
                        if (oldGrid[row][col].avatarType == game::Entity::PLAYER) {
                            attackerAttack = playerAttack;
                        } else if (oldGrid[row][col].avatarType == game::Entity::GOBLIN) {
                            attackerAttack = Goblin::DEFAULT_ATTACK + Global::getDamageBonus();
                        } else if (oldGrid[row][col].avatarType == game::Entity::BIG_SLIME) {
                            attackerAttack = Slime::getAttackForType(game::Entity::BIG_SLIME) + Global::getDamageBonus();
                        } else if (oldGrid[row][col].avatarType == game::Entity::SMALL_SLIME) {
                            attackerAttack = Slime::getAttackForType(game::Entity::SMALL_SLIME) + Global::getDamageBonus();
                        } else if (oldGrid[row][col].avatarType == game::Entity::DEATH_KNIGHT) {
                            attackerAttack = DeathKnight::DEFAULT_ATTACK + Global::getDamageBonus();
                        } else {
                            attackerAttack = 1;
                        }
                        auto result = game::CombatRule::resolveCombat(
                            oldGrid[row][col].avatarType, oldGrid[row][col].hp, attackerAttack,
                            newGrid[trow][tcol].avatarType, newGrid[trow][tcol].hp);
                        // Nếu phá vỡ spellscroll bởi player thì tăng spellPoint
                        if (newGrid[trow][tcol].avatarType == game::Entity::SPELL_SCROLL &&
                            oldGrid[row][col].avatarType == game::Entity::PLAYER && result.defenderHidden) {
                            if (spellPoint < 3) spellPoint++;
                            updateSpellCounter();
                        }
                        // EXP/LEVEL UP: Nếu player giết quái
                        if (oldGrid[row][col].avatarType == game::Entity::PLAYER && result.defenderHidden) {
                            gainExpForKill(newGrid[trow][tcol].avatarType);
                        }
                        // Nếu phá CHEST và có reward, sinh phần thưởng tại vị trí đó
                        if (newGrid[trow][tcol].avatarType == game::Entity::CHEST && result.defenderHidden && result.rewardType != game::Entity::NONE) {
                            if (result.rewardType == game::Entity::POTION) {
                                newGrid[trow][tcol].visible = true;
                                newGrid[trow][tcol].avatarType = game::Entity::POTION;
                                newGrid[trow][tcol].hp = 1;
                                newGrid[trow][tcol].speed = 0;
                            } else if (result.rewardType == game::Entity::SPELL_SCROLL) {
                                newGrid[trow][tcol].visible = true;
                                newGrid[trow][tcol].avatarType = game::Entity::SPELL_SCROLL;
                                newGrid[trow][tcol].hp = 1;
                                newGrid[trow][tcol].speed = 0;
                            }
                            break;
                        }
                        // Nếu phá DOOR và có reward (OPEN_DOOR), sinh cửa mở tại vị trí đó
                        if (newGrid[trow][tcol].avatarType == game::Entity::DOOR && result.defenderHidden && result.rewardType == game::Entity::OPEN_DOOR) {
                            newGrid[trow][tcol].visible = true;
                            newGrid[trow][tcol].avatarType = game::Entity::OPEN_DOOR;
                            newGrid[trow][tcol].hp = 1;
                            newGrid[trow][tcol].speed = 0;
                            break;
                        }
                        // Nếu tấn công vào OPEN_DOOR và bị phá, chuyển màn ngay
                        if (newGrid[trow][tcol].avatarType == game::Entity::OPEN_DOOR && (result.defenderHP <= 0 || result.defenderHidden)) {
                            stageManager.resetProgress(); // Reset progress khi qua màn mới
                            setupGrid();
                            return;
                        }
                        // Nếu player tấn công thường vào OPEN_DOOR mà không gây damage (không phải spell)
                        if (oldGrid[row][col].avatarType == game::Entity::PLAYER && newGrid[trow][tcol].avatarType == game::Entity::OPEN_DOOR && result.damageToDefender == 0) {
                            playerAttackOpenDoorNoDamage = true;
                        }
                        // Cập nhật máu, loại, ẩn/hiện dựa trên CombatResult
                        oldGrid[row][col].hp = result.attackerHP;
                        oldGrid[row][col].avatarType = result.attackerType;
                        oldGrid[row][col].visible = !result.attackerHidden;
                        newGrid[trow][tcol].hp = result.defenderHP;
                        newGrid[trow][tcol].avatarType = result.defenderType;
                        newGrid[trow][tcol].visible = !result.defenderHidden;
                        // Hiện damage
                        if (gridContainers[trow][tcol]) {
                            gridContainers[trow][tcol]->showDamageTaken(result.damageToDefender);
                        }
                        // Nếu attacker bị ẩn (slime gộp hoặc chết), dừng di chuyển
                        if (result.attackerHidden) {
                            oldGrid[row][col].hp = 0;
                            oldGrid[row][col].avatarType = game::Entity::NONE;
                            oldGrid[row][col].speed = 0;
                            oldGrid[row][col].visible = false;
                        }
                        // Nếu defender bị ẩn (bị giết), cho phép attacker tiếp tục di chuyển vào ô đó
                        if (result.defenderHidden) {
                            nrow = trow; ncol = tcol;
                            continue;
                        }
                        break;
                    }
                    nrow = trow; ncol = tcol;
                }
                // Nếu entity còn sống thì đặt vào vị trí mới
                if (oldGrid[row][col].hp > 0) {
                    newGrid[nrow][ncol].visible = true;
                    newGrid[nrow][ncol].avatarType = oldGrid[row][col].avatarType;
                    newGrid[nrow][ncol].hp = oldGrid[row][col].hp;
                    newGrid[nrow][ncol].speed = oldGrid[row][col].speed;
                }
            }
        }
    }
    // 4. Cập nhật lại UI từ newGrid và đồng bộ gridContainers
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            gridContainers[row][col]->setVisible(false);
            gridContainers[row][col]->invalidate();
            if (newGrid[row][col].visible) {
                gridContainers[row][col]->setAvatar(newGrid[row][col].avatarType);
                gridContainers[row][col]->setHPText(newGrid[row][col].hp);
                gridContainers[row][col]->setSpeed(newGrid[row][col].speed);
                gridContainers[row][col]->setVisible(true);
                gridContainers[row][col]->invalidate();
            }
        }
    }
    // Kiểm tra nếu player chết thì chuyển sang màn hình thua (Screen4View)
    bool playerAlive = false;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (newGrid[row][col].visible && newGrid[row][col].avatarType == game::Entity::PLAYER) {
                playerAlive = true;
                break;
            }
        }
        if (playerAlive) break;
    }
    if (!playerAlive) {
        application().gotoScreen4ScreenBlockTransition();
        return;
    }
    // 5. Cập nhật lại grid sau mỗi lần di chuyển
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            grid[row][col] = nullptr;
        }
    }
    // Sau khi onPlayerMove, nếu playerAttackOpenDoorNoDamage thì chuyển màn
    stageManager.onPlayerMove();
    updateLevelUI(); // Đảm bảo cập nhật thanh progress qua màn sau mỗi bước di chuyển
    if (playerAttackOpenDoorNoDamage) {
        setupGrid();
        return;
    }
    // Spawn slime ngẫu nhiên sau mỗi lượt di chuyển (chỉ slime, không goblin)
    // SỬA: Spawn entity ngẫu nhiên đúng tỉ lệ, không chỉ slime
    if (game::EntitySpawner::spawnRandomEntity(gridContainers)) {
        for (int row = 0; row < 6; ++row)
            for (int col = 0; col < 6; ++col)
                if (gridContainers[row][col]->isVisible())
                    gridContainers[row][col]->invalidate();
    }
}

void Screen1View::functionMoveLeft() { moveEntities(-1, 0); } // Di chuyển trái
void Screen1View::functionMoveRight() { moveEntities(1, 0); } // Di chuyển phải
void Screen1View::functionMoveUp() { moveEntities(0, -1); } // Di chuyển lên
void Screen1View::functionMoveDown() { moveEntities(0, 1); } // Di chuyển xuống

void Screen1View::functionSpell() {
    // Tấn công phép lên toàn bộ entity trên lưới (trừ player), xử lý sát thương và phần thưởng
    int damage = 2 * spellPoint * 3;
    if (damage <= 0) return;
    bool expGained = false;
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (gridContainers[row][col]->isVisible() && gridContainers[row][col]->getAvatarType() != game::Entity::PLAYER) {
                int hp = gridContainers[row][col]->getHP();
                auto result = game::CombatRule::resolveCombat(
                    game::Entity::PLAYER, // attacker
                    0, // attackerHP không cần thiết ở đây
                    damage, // attack = damage phép
                    gridContainers[row][col]->getAvatarType(),
                    hp,
                    5, // potionHeal mặc định
                    true // isSpellAttack = true
                );
                // Nếu là OPEN_DOOR và bị phá (defenderHidden hoặc HP <= 0), chuyển màn ngay và return, không cập nhật gì thêm
                if (gridContainers[row][col]->getAvatarType() == game::Entity::OPEN_DOOR && (result.defenderHP <= 0 || result.defenderHidden)) {
                    setupGrid();
                    return;
                }
                // EXP/LEVEL UP: Nếu spell giết quái (không phải vật bảo vệ)
                if ((result.defenderHP <= 0 || result.defenderHidden)) {
                    if (gainExpForKill(gridContainers[row][col]->getAvatarType())) {
                        expGained = true;
                    }
                }
                if (result.defenderHP <= 0 || result.defenderHidden) {
                    // Nếu là CHEST và có reward, spawn reward tại đây
                    if (gridContainers[row][col]->getAvatarType() == game::Entity::CHEST && result.rewardType != game::Entity::NONE) {
                        if (result.rewardType == game::Entity::POTION) {
                            gridContainers[row][col]->setAvatar(game::Entity::POTION);
                            gridContainers[row][col]->setHPText(1);
                            gridContainers[row][col]->setSpeed(0);
                            gridContainers[row][col]->setVisible(true);
                        } else if (result.rewardType == game::Entity::SPELL_SCROLL) {
                            gridContainers[row][col]->setAvatar(game::Entity::SPELL_SCROLL);
                            gridContainers[row][col]->setHPText(1);
                            gridContainers[row][col]->setSpeed(0);
                            gridContainers[row][col]->setVisible(true);
                        }
                    } else if (gridContainers[row][col]->getAvatarType() == game::Entity::DOOR && result.rewardType == game::Entity::OPEN_DOOR) {
                        gridContainers[row][col]->setAvatar(game::Entity::OPEN_DOOR);
                        gridContainers[row][col]->setHPText(1);
                        gridContainers[row][col]->setSpeed(0);
                        gridContainers[row][col]->setVisible(true);
                    } else {
                        gridContainers[row][col]->setVisible(false);
                        gridContainers[row][col]->setHPText(0);
                    }
                } else {
                    gridContainers[row][col]->setHPText(result.defenderHP);
                }
                gridContainers[row][col]->showDamageTaken(result.damageToDefender);
                gridContainers[row][col]->invalidate();
            }
        }
    }
    spellPoint = 0;
    updateSpellCounter();
    if (expGained) {
        updateLevelUI();
    }
}

void Screen1View::updateSpellCounter() {
    // Cập nhật UI bộ đếm spellPoint
    // Đảm bảo dùng đúng buffer và widget kế thừa từ Screen1ViewBase
    Unicode::snprintf(Screen1ViewBase::spellCounterBuffer, Screen1ViewBase::SPELLCOUNTER_SIZE, "%d", spellPoint);
    Screen1ViewBase::spellCounter.setWildcard(Screen1ViewBase::spellCounterBuffer);
    Screen1ViewBase::spellCounter.invalidate();
}

void Screen1View::updateLevelUI() {
    // Cập nhật UI level, thanh kinh nghiệm, và thanh tiến trình qua màn
    // Cập nhật textLV
    Unicode::snprintf(Screen1ViewBase::textLVBuffer, Screen1ViewBase::TEXTLV_SIZE, "%d", level);
    Screen1ViewBase::textLV.setWildcard(Screen1ViewBase::textLVBuffer);
    Screen1ViewBase::textLV.invalidate();
    // Cập nhật lineProgressLevel (thanh kinh nghiệm)
    int expToLevel = getExpToLevel(level);
    int percent = (exp * 100) / expToLevel;
    if (percent > 100) percent = 100;
    Screen1ViewBase::lineProgressLevel.setValue(percent);
    Screen1ViewBase::lineProgressLevel.invalidate();
    // Cập nhật lineProgressPass (thanh progress qua màn) nếu có
    int progress = stageManager.getProgress();
    int maxProgress = stageManager.getMaxProgress();
    int passPercent = (progress * 100) / (maxProgress > 0 ? maxProgress : 1);
    if (passPercent > 100) passPercent = 100;
    // Nếu lineProgressPass nằm trực tiếp trong Screen1ViewBase (giống lineProgressLevel)
    Screen1ViewBase::lineProgressPass.setValue(passPercent);
    Screen1ViewBase::lineProgressPass.invalidate();
}

// Sau khi tăng spellPoint khi nhặt cuộn phép hoặc phá spellscroll, hãy gọi updateSpellCounter();
// Ví dụ, trong moveEntities hoặc callback onCollect của SpellScroll:
// spellPoint++;
// updateSpellCounter();

bool Screen1View::gainExpForKill(int entityType) {
    // Tăng exp khi player tiêu diệt quái, xử lý lên cấp và tăng chỉ số tấn công
    int expGain = 0;
    if (entityType == game::Entity::GOBLIN) {
        expGain = 1;
    } else if (entityType == game::Entity::SMALL_SLIME || entityType == game::Entity::BIG_SLIME) {
        expGain = 3;
    } else if (entityType == game::Entity::DEATH_KNIGHT) {
        expGain = 5;
    }
    if (expGain > 0) {
        exp += expGain;
        int expToLevel = getExpToLevel(level);
        while (exp >= expToLevel) {
            exp -= expToLevel;
            level++;
            playerAttack++; // Tăng damage mỗi khi lên cấp
            expToLevel = getExpToLevel(level);
        }
        updateLevelUI();
        return true;
    }
    return false;
}

int Screen1View::getExpToLevel(int level) {
    // Tính số exp cần để lên cấp tiếp theo dựa trên level hiện tại
    if (level <= 5) {
        return 20 * level;
    } else if (level <= 10) {
        return 2.5 * level * level - 2.5 * level + 50; // mỗi cấp tốn thêm 5 để lên cấp
    } else {
        return 5 * level * level - 50 * level  + 275; // mỗi cấp tốn thêm 10 để lên cấp
    }
}

#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/containers/ContainerEntity.hpp>
#include <game/Entity.hpp>
#include <game/Player.hpp>
#include <game/Slime.hpp>
#include <game/GameStageManager.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual void setupScreen();
    virtual void functionMoveLeft();
    virtual void functionMoveRight();
    virtual void functionMoveUp();
    virtual void functionMoveDown();
    virtual void functionSpell();
    void setupGrid();

private:
    ContainerEntity* gridContainers[6][6];
    game::Entity* grid[6][6];
    int spellPoint = 0;
    int exp = 0;
    int level = 1;
    int playerAttack = game::Player::DEFAULT_ATTACK;
    void updateGridUI();
    void moveEntities(int dx, int dy); // Sửa prototype: nhận 2 số dx, dy
    void updateSpellCounter();
    void updateLevelUI();
    bool gainExpForKill(int entityType);
    int getExpToLevel(int level);
    game::GameStageManager stageManager;
};

#endif // SCREEN1VIEW_HPP

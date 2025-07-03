#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <stdint.h>

enum GameMode {
    GAME_EASY,
    GAME_NORMAL,
    GAME_HARD
};

class Global {
public:
    static GameMode gameMode;
    static int getDamageBonus();
    static void setDamageBonus(int bonus);
    static int DamageBonus;
};

#endif

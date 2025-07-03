#include <game/RandomUtil.hpp>

namespace game {
unsigned int RandomUtil::state = 1;

void RandomUtil::seed(unsigned int s) {
    state = s ? s : 1;
}

unsigned int RandomUtil::next() {
    // Linear Congruential Generator (LCG) parameters
    state = state * 1664525u + 1013904223u;
    return state;
}

int RandomUtil::randRange(int min, int max) {
    if (max < min) return min;
    unsigned int r = next();
    return min + (r % (max - min + 1));
}
} // namespace game

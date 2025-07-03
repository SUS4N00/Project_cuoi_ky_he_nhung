#pragma once

namespace game {
class RandomUtil {
public:
    static void seed(unsigned int s);
    static unsigned int next();
    static int randRange(int min, int max); // [min, max]
private:
    static unsigned int state;
};
}

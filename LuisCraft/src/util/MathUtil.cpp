#include "MathUtil.h"

namespace MathUtil {
    float floorMod(float a, float b) {
        return fmod(fmod(a,b) + b, b);
    }

    int floorMod(int a, int b) {
        return (a % b + b) % b;
    }
}
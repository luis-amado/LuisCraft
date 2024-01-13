#include "PixelConstraint.h"

namespace UILib {

    PixelConstraint::PixelConstraint(int _pixels): pixels(_pixels) {}

    float PixelConstraint::getValue(ConstraintType type, float parentValue) {
        return (float) pixels;
    }

}
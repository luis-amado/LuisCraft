#include "RelativeOffsetConstraint.h"

namespace UILib {

    RelativeOffsetConstraint::RelativeOffsetConstraint(float _relative, int _pixelOffset):
        relative(_relative), pixels(_pixelOffset) {}

    float RelativeOffsetConstraint::getValue(ConstraintType type, float parentValue) {
        return relative * parentValue + pixels;
    }

}
#include "AspectRatioConstraint.h"

namespace UILib {

    AspectRatioConstraint::AspectRatioConstraint(float _aspectRatio) : Constraint(true), aspectRatio(_aspectRatio) {}

    float AspectRatioConstraint::getValue(ConstraintType type, float parentValue) {
        if (type == HORIZONTAL) {
            return parentValue * aspectRatio;
        } else {
            return parentValue / aspectRatio;
        }
    }

}
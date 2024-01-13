#include "RelativeConstraint.h"

namespace UILib {

    RelativeConstraint::RelativeConstraint(float _value) : value(_value) {}

    float RelativeConstraint::getValue(ConstraintType type, float parentValue) {
        return value * parentValue;
    }


}
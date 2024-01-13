#pragma once

#include "Constraint.h"

namespace UILib {

    class RelativeOffsetConstraint : public Constraint {
    public:
        RelativeOffsetConstraint(float _relative, int _pixelOffset);

        float getValue(ConstraintType type, float parentValue) override;
    private:
        float relative;
        int pixels;
    };

}
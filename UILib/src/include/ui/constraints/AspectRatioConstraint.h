#pragma once

#include "Constraint.h"

namespace UILib {

    class AspectRatioConstraint : public Constraint {
    public:
        AspectRatioConstraint(float _aspectRatio);

        float getValue(ConstraintType type, float parentValue) override;
    private:
        float aspectRatio;
    };

}
#pragma once

#include "Constraint.h"

namespace UILib {

    class PixelConstraint : public Constraint {

    public:
        PixelConstraint(int _pixels);

        float getValue(ConstraintType type, float parentValue) override;
    private:
        int pixels;
    };

}
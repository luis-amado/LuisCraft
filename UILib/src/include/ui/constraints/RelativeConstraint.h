#pragma once

#include "Constraint.h"

namespace UILib {

    class RelativeConstraint : public Constraint {

    public:
        RelativeConstraint(float _value);

        float getValue(ConstraintType type, float parentValue) override;
    private:
        float value;
    };

}
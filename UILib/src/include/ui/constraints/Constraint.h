#pragma once

namespace UILib {

    enum ConstraintType {
        HORIZONTAL, VERTICAL
    };

    class Constraint {
    public:
        Constraint(bool ar = false) :_isAspectRatio(ar) {}

        virtual float getValue(ConstraintType type, float parentValue) = 0;

        bool isAspectRatio() {return _isAspectRatio;}
    private:
        bool _isAspectRatio;
    };

}
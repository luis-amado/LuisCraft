#pragma once

#include "Constraint.h"

namespace UILib {

    class ConstraintSet {

    public:
        ConstraintSet(float _x = 0, float _y = 0, float _w = 0, float _h = 0) : 
            x(_x), y(_y), w(_w), h(_h),
            top(nullptr), bottom(nullptr), centerV(nullptr), height(nullptr),
            left(nullptr), right(nullptr), centerH(nullptr), width(nullptr) {}
        ~ConstraintSet();

        void build(float parentX, float parentY, float parentW, float parentH);

        inline float getX() const { return x; }
        inline float getY() const { return y; }
        inline float getWidth() const { return w; }
        inline float getHeight() const { return h; }

        void setWidth(float _width) {w = _width;}
        void setHeight(float _height) {h = _height;}

        Constraint *top, *bottom, *centerV, *height;
        Constraint *left, *right, *centerH, *width;

    private:
        float x, y, w, h;

        bool validate();

        float calcDimension(Constraint* minCons, Constraint* maxCons, Constraint* dimCons, Constraint* centerCons, ConstraintType type, float parentValue, float otherDim);
    };

}
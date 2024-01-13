#include "ConstraintSet.h"

#include <iostream>

namespace UILib {

    ConstraintSet::~ConstraintSet() {
        delete top, left, right, bottom, centerH, centerV, width, height;
    }

    void ConstraintSet::build(float parentX, float parentY, float parentW, float parentH) {
#ifdef _DEBUG
        if (!validate()) {
            std::cout << "ERROR: Invalid UI constraints" << std::endl;
            return;
        }
#endif

        if (width && width->isAspectRatio()) {
            h = calcDimension(bottom, top, height, centerV, VERTICAL, parentH, 0.0f);
            w = calcDimension(left, right, width, centerH, HORIZONTAL, parentW, h);
        } else {
            w = calcDimension(left, right, width, centerH, HORIZONTAL, parentW, 0.0f);
            h = calcDimension(bottom, top, height, centerV, VERTICAL, parentH, w);
        }

        if (left) {
            x = parentX + left->getValue(HORIZONTAL, parentW);
        } else if (right) {
            x = parentX + parentW - right->getValue(HORIZONTAL, parentW) - w;
        } else {
            x = parentX + centerH->getValue(HORIZONTAL, parentW) + (parentW - w) / 2.0f;
        }

        if (bottom) {
            y = parentY + bottom->getValue(VERTICAL, parentH);
        } else if (top) {
            y = parentY + parentH - top->getValue(VERTICAL, parentH) - h;
        } else {
            y = parentY + centerV->getValue(VERTICAL, parentH) + (parentH - h) / 2.0f;
        }
        

    }

    float ConstraintSet::calcDimension(Constraint* minCons, Constraint* maxCons, Constraint* dimCons, Constraint* centerCons, ConstraintType type, float parentValue, float otherDim) {
        
        float calculatedValue;
        if (dimCons) {
            if(dimCons->isAspectRatio())
                calculatedValue = dimCons->getValue(type, otherDim);
            else
                calculatedValue = dimCons->getValue(type, parentValue);
        } else {

            if (centerCons) {

                if (minCons) {
                    calculatedValue = parentValue + (centerCons->getValue(type, parentValue) - minCons->getValue(type, parentValue)) * 2.0f;
                } else {
                    calculatedValue = parentValue + (-centerCons->getValue(type, parentValue) - maxCons->getValue(type, parentValue)) * 2.0f;
                }

            } else {

                calculatedValue = parentValue - minCons->getValue(type, parentValue) - maxCons->getValue(type, parentValue);

            }

        }
        calculatedValue = std::max(calculatedValue, 0.0f);

        return calculatedValue;
    }

    bool ConstraintSet::validate() {
        // theres exactly 2 horizontal and 2 vertical constraints
        int hCount = 0, vCount = 0;
        if(top) vCount++;
        if(bottom) vCount++;
        if(centerV) vCount++;
        if(height) vCount++;

        if(left) hCount++;
        if(right) hCount++;
        if(centerH) hCount++;
        if(width) hCount++;

        //only width or height can be aspect ratio
        //can only have one or the other
        if ((top && top->isAspectRatio()) || (bottom && bottom->isAspectRatio()) || (left && left->isAspectRatio()) || (right && right->isAspectRatio()) || (centerV && centerV->isAspectRatio()) || (centerH && centerH->isAspectRatio())) {
            return false;
        } else if (width && width->isAspectRatio() && height && height->isAspectRatio()) {
            return false;
        }

        return hCount == 2 && vCount == 2;
    }

}
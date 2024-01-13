#pragma once

#include <vector>
#include <iostream>
#include <glm/vec3.hpp>

#include "UIQuad.h"
#include "constraints/ConstraintSet.h"

namespace UILib {

    class UIBlock : public UIQuad {

    public:
        UIBlock(float x, float y, float w, float h);
        UIBlock(glm::vec4 _color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        ~UIBlock();

        virtual void addChild(UIBlock* newChild);

        virtual void renderAdditional(UIShader& shader, const glm::mat4& projection, const UIBlock& parent) {}
        void renderBlock(UIShader& shader, const glm::mat4& projection, const UIBlock& parent);
        virtual void updateBlock(UIBlock& parent);
        void updateChildren();

        virtual void onBoxUpdated() {};

        UIBlock& fillParent(int padding = 0);
        UIBlock& fillParent(int paddingV, int paddingH);
        UIBlock& fillParent(int paddingT, int paddingR, int paddingB, int paddingL);

        UIBlock& setTop(Constraint* _top);
        UIBlock& setLeft(Constraint* _left);
        UIBlock& setRight(Constraint* _right);
        UIBlock& setBottom(Constraint* _bottom);
        UIBlock& setCenterH(Constraint* _centerH);
        UIBlock& setCenterV(Constraint* _centerV);
        UIBlock& setWidth(Constraint* _width);
        UIBlock& setHeight(Constraint* _height);

        ConstraintSet constraints;
    protected:
        std::vector<UIBlock*> children;

    private:
        glm::vec4 color;

    };

}
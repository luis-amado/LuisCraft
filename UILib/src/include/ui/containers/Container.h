#pragma once

#include "../UIBlock.h"

namespace UILib {

    class Container : public UIBlock {

    public:
        Container(glm::vec4 _color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        void addChild(UIBlock* newChild) override;
        void updateBlock(UIBlock& parent) override;

    protected:
        virtual void organizeChildren() = 0;

    };


}
#pragma once

#include "Container.h"

namespace UILib {

    class RowContainer : public Container {

    public:
        RowContainer(float _rowHeight, float _padding, float _rowGap, glm::vec4 _color = { 1.0f, 0.0f, 0.0f, 1.0f });

        void organizeChildren() override;

    private:
        float rowHeight;
        float padding;
        float rowGap;

    };


}
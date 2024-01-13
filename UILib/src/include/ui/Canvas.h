#pragma once

#include "../../Shader.h"
#include "UIBlock.h"

namespace UILib {

    class Canvas : public UIBlock {

    public:

        Canvas(float x, float y, float width, float height);
        ~Canvas();

        void render();

        void updateSize(float newWidth, float newHeight);

        inline const glm::mat4& getProjectionMatrix() { return projection; }

    private:
        UIShader uiShader;
        glm::mat4 projection;
    };

}


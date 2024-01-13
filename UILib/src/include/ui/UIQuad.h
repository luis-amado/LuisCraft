#pragma once

#include "../../Shader.h"

#include <glad/glad.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace UILib {

    class UIQuad {

    public:
        UIQuad(float _x, float _y, float _width, float _height);

        UIQuad(const UIQuad& quad) = delete;

        void draw(UIShader& shader, const glm::mat4& projection);

        static void destroy();

        float x, y, width, height;

    private:
        static unsigned int vao, vbo;
        static bool initialized;

        void initialize();

    };


}
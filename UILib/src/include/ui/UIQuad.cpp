#include "UIQuad.h"

namespace UILib {

    unsigned int UIQuad::vao, UIQuad::vbo;
    bool UIQuad::initialized = false;

    UIQuad::UIQuad(float _x, float _y, float _width, float _height)
        : x(_x), y(_y), width(_width), height(_height) {

        if (!initialized) {
            initialize();
        }

    }

    void UIQuad::initialize() {
        float vertices[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        initialized = true;
    }

    void UIQuad::draw(UIShader& shader, const glm::mat4& projection) {

#ifdef _DEBUG
        if (!initialized) {
            std::cout << "ERROR: UIQuad not initialized" << std::endl;
            return;
        }
#endif
        glm::mat4 model = glm::mat4(1.0f);

        // transformation order: scale -> rotate -> translate
        // however, transformations are applied in reverse order
        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        model = glm::scale(model, glm::vec3(width, height, 1.0f));

        shader.setUniformMatrix("projection", projection);
        shader.setUniformMatrix("model", model);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    }

    void UIQuad::destroy() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        initialized = false;
    }

}
#include <iostream>

#include <stb_image.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderEngine/Shader.h"
#include "renderEngine/Window.h"
#include "renderEngine/Mesh.h"
#include "renderEngine/Texture.h"

int main() {

    Window window("LuisCraft", 600, 600);

    float xbase = 100.0f/256;
    float ybase = 60.0f/256;
    float w = 24.0f/256, h = 26.0f/256;

    std::vector<float> quadVerts = {
        0.0f, 1.0f, 0.0f,  xbase, ybase,
        0.0f, 0.0f, 0.0f,  xbase, ybase+h,
        1.0f, 0.0f, 0.0f,  xbase+w, ybase+h,
        1.0f, 1.0f, 0.0f,  xbase+w, ybase
    };

    std::vector<unsigned int> quadIndices = {
        0, 1, 2,
        2, 3, 0
    };

    Mesh quad(quadVerts, quadIndices);
    Shader fontShader("res/shaders/font.vs", "res/shaders/font.fs");
    Texture minecraftFont("res/fonts/minecraft.png");

    fontShader.use();

    glm::vec3 pos(10, 10, 0.0f);
    glm::vec3 size(24.0f, 26.0f, 1.0f);
    float scale = 12.0f / 26.0f;
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, pos);
    transform = glm::scale(transform, glm::vec3(scale,scale,1.0f));
    transform = glm::scale(transform, size);
    fontShader.setUniformMatrix("transform", transform);

    glm::mat4 projection = glm::ortho(0.0f, 600.0f, 0.0f, 600.0f);
    fontShader.setUniformMatrix("projection", projection);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    while (!window.shouldClose()) {

        glClear(GL_COLOR_BUFFER_BIT);

        fontShader.use();
        quad.bind();
        minecraftFont.bind();
        glDrawElements(GL_TRIANGLES, quad.indexCount(), GL_UNSIGNED_INT, nullptr);

        window.update();
    }
    
    return 0;
}
#include <iostream>

#include <stb_image.h>
#include <glm/vec3.hpp>

#include "renderEngine/Shader.h"
#include "renderEngine/Window.h"
#include "renderEngine/Mesh.h"
#include "renderEngine/Texture.h"

int main() {

    Window window("LuisCraft", 600, 600);

    std::vector<float> vertices = {
        // position           // colors           // tex coords
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // top left
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
         0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f    // top right
    };
    std::vector<unsigned int> indices = {
        0, 1, 2, // bottom left tri
        2, 3, 0  // top right tri
    };

    Mesh mesh(vertices, indices);

    Shader shader("res/shaders/basic.vs", "res/shaders/basic.fs");

    Texture texture("res/textures/andesite.png");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        mesh.bind();
        texture.bind();
        glDrawElements(GL_TRIANGLES, mesh.indexCount(), GL_UNSIGNED_INT, nullptr);

        window.update();
    }
    
    return 0;
}
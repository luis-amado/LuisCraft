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

    std::vector<float> vertices = {
        // position           // tex coords
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,   // top left
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f    // top right
    };
    std::vector<unsigned int> indices = {
        0, 1, 2, // bottom left tri
        2, 3, 0  // top right tri
    };

    Mesh mesh(vertices, indices);

    Shader shader("res/shaders/basic.vs", "res/shaders/basic.fs");

    Texture texture("res/textures/andesite.png");

    glm::vec3 cameraPos(0.0f, 0.0f, 2.0f);


    shader.use();
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setUniformMatrix("model", model);

    glm::mat4 view(1.0f);
    view = glm::translate(view, -cameraPos);
    shader.setUniformMatrix("view", view);

    glm::mat4 persp;
    persp = glm::perspective(glm::radians(70.0f), 1.0f, 0.1f, 100.0f);
    shader.setUniformMatrix("projection", persp);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    while (!window.shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);


        mesh.bind();
        texture.bind();
        glDrawElements(GL_TRIANGLES, mesh.indexCount(), GL_UNSIGNED_INT, nullptr);

        window.update();
    }
    
    return 0;
}
#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderEngine/Window.h"
#include "renderEngine/Mesh.h"
#include "renderEngine/Shader.h"
#include "renderEngine/Texture.h"
#include "entity/player/Camera.h"
#include "world/World.h"

#include "ui/Canvas.h"
#include "ui/constraints/Constraints.h"
#include "ui/containers/RowContainer.h"
#include "ui/text/font/Font.h"
#include "ui/text/Text.h"
#include "ui/text/TextBox.h"

void framebuffer_callback(GLFWwindow* window, int width, int height);

double mouseDX = 0, mouseDY = 0, prevMouseX = 0, prevMouseY = 0;

bool fullscreen = false, toggledFullscreen = false;
int windowPosX, windowPosY, windowWidth, windowHeight;

double mouseScrollDX = 0, mouseScrollDY = 0;

struct UserPointerData {
    glm::mat4* projectionMatrix;
    UILib::Canvas* uiCanvas;
};

int main() {

    Window window("LuisCraft", 600, 600);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    window.update();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glfwSetFramebufferSizeCallback(window.handle(), framebuffer_callback);

    Texture texture("res/textures/block_atlas.png");
    Texture lightMap("res/textures/lightMap.png");
    Shader shader("res/shaders/basic.vs", "res/shaders/basic.fs");

    UILib::Font pixelFont("res/fonts/pixel_regular.json");

    World world;

    Camera camera;

    camera.position = {0.0f, 70.0f, 0.0f};
    
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);

    UILib::Canvas uiCanvas(0, 0, 600, 600);

    UILib::RowContainer* rowContainer = new UILib::RowContainer(20, 2, 2, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
    rowContainer->fillParent(10);

    uiCanvas.addChild(rowContainer);

    //UILib::UIBlock* row1 = new UILib::UIBlock(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    //UILib::UIBlock* row2 = new UILib::UIBlock(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    UILib::UIBlock* row3 = new UILib::UIBlock(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

    UILib::TextBox* textBox1 = new UILib::TextBox("Wow, this is significantly larger", pixelFont, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
    UILib::TextBox* textBox2 = new UILib::TextBox("This is a second line", pixelFont, glm::vec4(1.0f, 1.0f, 1.0f, 0.0f));
    textBox1->setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    textBox2->setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    rowContainer->addChild(textBox1);
    rowContainer->addChild(textBox2);

    //row1->addChild(textBox);

    UserPointerData userPointerData(&projectionMatrix, &uiCanvas);

    glfwSetWindowUserPointer(window.handle(), &userPointerData);

    glm::mat4 model(1.0f);

    double currentTime = glfwGetTime(), deltaTime, prevTime = glfwGetTime();

    glfwGetCursorPos(window.handle(), &prevMouseX, &prevMouseY);

    glfwSetScrollCallback(window.handle(), [](GLFWwindow* window, double xoffset, double yoffset) {
        mouseScrollDX += xoffset;
        mouseScrollDY += yoffset;
    });

    glfwSetCursorPosCallback(window.handle(), [](GLFWwindow* window, double xpos, double ypos) {
        if(!toggledFullscreen) {
            mouseDX += xpos - prevMouseX;
            mouseDY += ypos - prevMouseY;
        } else {
            toggledFullscreen = false;
        }
        prevMouseX = xpos;
        prevMouseY = ypos;
    });

    glfwSetKeyCallback(window.handle(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS && key == GLFW_KEY_F11) {

            if (!fullscreen) {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);

                glfwGetWindowPos(window, &windowPosX, &windowPosY);
                glfwGetWindowSize(window, &windowWidth, &windowHeight);

                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

                fullscreen = true;
            } else {
                glfwSetWindowMonitor(window, NULL, windowPosX, windowPosY, windowWidth, windowHeight, 0);
                fullscreen = false;
            }
            
            toggledFullscreen = true;
            glfwSwapInterval(1);
        }
    });

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glfwSwapInterval(1);

    shader.use();
    shader.setUniform1i("tex", 0);
    shader.setUniform1i("lightMap", 1);

    while (!window.shouldClose()) {

        currentTime = glfwGetTime();
        deltaTime = currentTime - prevTime;
        prevTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.move(window.handle(), deltaTime, mouseDX, mouseDY, mouseScrollDY);

        textBox1->setText(std::to_string(camera.position.x) + " " + std::to_string(camera.position.y) + " " + std::to_string(camera.position.z));
        textBox2->setText(std::to_string(camera.yaw) + " " + std::to_string(camera.pitch));

        shader.use();

        texture.bind(GL_TEXTURE0);
        lightMap.bind(GL_TEXTURE1);

        shader.setUniformMatrix("projection", projectionMatrix);
        shader.setUniformMatrix("view", camera.viewMatrix());

        for (auto & [coord, chunk] : world.chunks) {
            for (int i = 0; i < Chunk::CHUNK_HEIGHT_IN_SECTIONS; i++) {
                if(chunk->sections[i].mesh.indexCount() == 0) continue;
                glm::vec3 sectionPos = glm::vec3(chunk->coord.x * Chunk::CHUNK_WIDTH, chunk->sections[i].yPos, chunk->coord.z * Chunk::CHUNK_WIDTH);
                chunk->sections[i].mesh.bind();
                model = glm::identity<glm::mat4>();
                model = glm::translate(model, sectionPos);
                shader.setUniformMatrix("model", model);
                glDrawElements(GL_TRIANGLES, chunk->sections[i].mesh.indexCount(), GL_UNSIGNED_INT, nullptr);
            }
        }

        uiCanvas.render();

        mouseDX = 0;
        mouseDY = 0;
        mouseScrollDX = 0;
        mouseScrollDY = 0;
        window.update();
    }
    
    return 0;
}

void framebuffer_callback(GLFWwindow* window, int width, int height) {
    if(width == 0) return;
    UserPointerData& data = *(UserPointerData*)(glfwGetWindowUserPointer(window));
    
    glm::mat4& projectionMatrix = *data.projectionMatrix;
    projectionMatrix = glm::perspective(glm::radians(90.0f), (float)width/height, 0.1f, 1000.0f);

    UILib::Canvas& canvas = *data.uiCanvas;
    canvas.updateSize(width, height);

    glViewport(0, 0, width, height);
}
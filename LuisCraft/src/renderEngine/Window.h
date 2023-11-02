#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Window {
public:
    Window(std::string title, int width, int height);
    ~Window();

    void update() const;
    bool shouldClose() const;
private:
    GLFWwindow* window;
};
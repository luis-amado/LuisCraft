#include <GLFW/glfw3.h>
#include <iostream>

int main() {

    GLFWwindow* window;
    glfwInit();

    window = glfwCreateWindow(600, 480, "Hello, World!", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
#include "Window.h"

Window::Window(std::string title, int width, int height) {

    if (!glfwInit())
        std::cout << "Failed to initialize GLFW" << std::endl;

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

}

Window::~Window() {
    glfwTerminate();
}

void Window::update() const {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}
#include <iostream>

#include <glm/vec3.hpp>

#include "renderEngine/Shader.h"
#include "renderEngine/Window.h"

int main() {

    Window window("LuisCraft", 600, 400);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    while (!window.shouldClose()) {

        glClear(GL_COLOR_BUFFER_BIT);

        window.update();
    }
    
    return 0;
}
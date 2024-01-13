#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:

    Camera();

    void move(GLFWwindow* window, double deltaTime, double mouseDX, double mouseDY, double mouseScroll);
    glm::mat4 viewMatrix() const;

    glm::vec3 position;

    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp
        ;
    float yaw, pitch;
private:
    float speed = 5.0f;

    void updateCameraVectors();
};
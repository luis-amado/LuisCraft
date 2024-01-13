#include "Camera.h"

#include <iostream>

#include "MathUtil.h"

Camera::Camera() {
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    position = glm::vec3(0.0f, 0.0f, 1.0f);
    yaw = 0;
    pitch = 0;

    updateCameraVectors();
}

void Camera::move(GLFWwindow* window, double deltaTime, double mouseDX, double mouseDY, double mouseScroll) {

    speed += mouseScroll;
    speed = std::max(speed, 0.1f);

    yaw += mouseDX * 0.1f;
    pitch += mouseDY * 0.1f;

    pitch = std::max(pitch, -90.0f);
    pitch = std::min(pitch, 90.0f);

    yaw = MathUtil::floorMod(yaw, 360.0f);

    glm::vec3 forward = {sin(glm::radians(yaw)), 0.0f, -cos(glm::radians(yaw))};
    glm::vec3 right = glm::cross(forward, worldUp);

    if (glfwGetKey(window, GLFW_KEY_W)) {
        position += forward * (speed * (float)deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        position -= forward * (speed * (float)deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        position -= right * (speed * (float)deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        position += right * (speed * (float)deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE)) {
        position.y += speed * (float)deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        position.y -= speed * (float)deltaTime;
    }

    updateCameraVectors();
}

glm::mat4 Camera::viewMatrix() const {
    glm::mat4 view(1.0f);

    view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, -position);

    return view;
}

void Camera::updateCameraVectors() {
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
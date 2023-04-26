#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
/*
Camera::Camera(glm::vec3 position, float yaw, float pitch)
    : cameraPosition(position), yaw(yaw), pitch(pitch), cameraAcceleration(0.0f), cameraVelocity(0.0f), accelerationAmount(5.0f) {
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    updateCameraVectors();
}
*/
Camera::Camera(glm::vec3 position, float yaw, float pitch)
    : cameraPosition(position), yaw(yaw), pitch(pitch),
    cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraRight(glm::vec3(1.0f, 0.0f, 0.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)), cameraAcceleration(glm::vec3(0.0f, 0.0f, 0.0f)),
    cameraVelocity(glm::vec3(0.0f, 0.0f, 0.0f)), accelerationAmount(5.0f) {
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    updateCameraVectors();
}


glm::vec3 Camera::getCameraPosition() const {
    return cameraPosition;
}

glm::vec3 Camera::getCameraFront() const {
    return cameraFront;
}

glm::vec3 Camera::getCameraUp() const {
    return cameraUp;
}

void Camera::setCameraAcceleration(float acceleration) {
    accelerationAmount = acceleration;
}

void Camera::processKeyboardInput(GLFWwindow* window, float deltaTime) {
    glm::vec3 acceleration(0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        acceleration = accelerationAmount * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        acceleration = -accelerationAmount * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        acceleration = -accelerationAmount * cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        acceleration = accelerationAmount * cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        acceleration = accelerationAmount * cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        acceleration = -accelerationAmount * cameraUp;
    }

    cameraAcceleration = acceleration;
    cameraVelocity += cameraAcceleration * deltaTime;
    cameraPosition += cameraVelocity * deltaTime;
    cameraVelocity *= 0.99f;
}

void Camera::processMouseMovement(float xOffset, float yOffset) {
    float sensitivity = 0.05f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(cameraPosition,
        cameraPosition + cameraFront, cameraUp);
}

void Camera::updateCameraVectors() {
    // Calculate the new cameraFront vector
    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);

    // Update the cameraRight and cameraUp vectors
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

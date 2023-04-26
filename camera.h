#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    Camera(glm::vec3 position, float yaw, float pitch);

    glm::vec3 getCameraPosition() const;
    glm::vec3 getCameraFront() const;
    glm::vec3 getCameraUp() const;
    void setCameraAcceleration(float acceleration);
    void processKeyboardInput(GLFWwindow* window, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);
    glm::mat4 getViewMatrix() const;

private:
    void updateCameraVectors();

    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 cameraAcceleration;
    glm::vec3 cameraVelocity;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float accelerationAmount;
};

#endif // CAMERA_H

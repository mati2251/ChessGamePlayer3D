#include <cstdio>
#include "rotate_controller.h"

void RotateController::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_LEFT) this->speedZ = -M_PI_2;
        if (key == GLFW_KEY_RIGHT) this->speedZ = M_PI_2;
        if (key == GLFW_KEY_UP) this->speedY = M_PI_2;
        if (key == GLFW_KEY_DOWN) this->speedY = -M_PI_2;
        if (key == GLFW_KEY_ESCAPE){
            this->M = this->M_orginal;
        }
    }
    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_LEFT) speedZ = 0;
        if (key == GLFW_KEY_RIGHT) speedZ = 0;
        if (key == GLFW_KEY_UP) speedY = 0;
        if (key == GLFW_KEY_DOWN) speedY = 0;
    }
}

void RotateController::rotateM() {
    this->angleZ = this->speedZ * glfwGetTime();
    this->angleY = this->speedY * glfwGetTime();
    glfwSetTime(0);
    M=glm::rotate(M, this->angleZ, glm::vec3(0.0f, 0.0f, 1.0f));
    M=glm::rotate(M,this->angleY,glm::vec3(0.0f,1.0f,0.0f));
}

RotateController::RotateController(glm::mat4 &M) : M(M) {
    this->M_orginal = M;

}
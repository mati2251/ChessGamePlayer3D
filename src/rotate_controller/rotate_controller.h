#ifndef ASTEROID_3D_ROTATE_CONTROLLER_H
#define ASTEROID_3D_ROTATE_CONTROLLER_H
#include <GLFW/glfw3.h>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"


class RotateController{
    float speedZ = 0;
    float speedY = 0;
    float angleZ = 0;
    float angleY = 0;
    glm::mat4 &M;
public:
    void keyCallback(GLFWwindow* window,int key,int scancode,int action,int mods);
    void rotateM();
    RotateController(glm::mat4 &M);
};


#endif //ASTEROID_3D_ROTATE_CONTROLLER_H

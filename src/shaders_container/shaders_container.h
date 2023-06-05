#ifndef ASTEROID_3D_SHADER_PROGRAM_CONTAINER_H
#define ASTEROID_3D_SHADER_PROGRAM_CONTAINER_H

#include "../shaderprogram/shaderprogram.h"
#include "shaders_type.h"
#include "../../include/glm/gtc/type_ptr.hpp"

class ShadersContainer {
    ShaderProgram *textured;
    glm::mat4 P;
    glm::mat4 V;
    void initShader(ShaderProgram *shader);
public:
    ShadersContainer(glm::mat4 P, glm::mat4 V);
    ShaderProgram *getShader(ShadersType type);
    ~ShadersContainer();
};

#endif //ASTEROID_3D_SHADER_PROGRAM_CONTAINER_H

#ifndef ASTEROID_3D_COLORED_MODEL_H
#define ASTEROID_3D_COLORED_MODEL_H


#include "model/model.h"
#include "../shaders_container/shaders_container.h"

class ColoredModel{
public:
    ShaderProgram *shader;
    float *colors;
    float *vertices;
    int vertexCount;
    GLenum mode;

    ColoredModel(ShadersContainer *container, float *vertices, float *colors, int vertexCount,
                 GLenum mode);

    void draw(glm::mat4 M);
};


#endif //ASTEROID_3D_COLORED_MODEL_H

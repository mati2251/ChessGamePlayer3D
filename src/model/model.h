#ifndef ASTEROID_3D_MODEL_H
#define ASTEROID_3D_MODEL_H


#include "shaderprogram/shaderprogram.h"
#include "../../include/glm/glm.hpp"

class Model {
public:
    virtual void draw(glm::mat4 M) {};
};

#endif //ASTEROID_3D_MODEL_H

#ifndef ASTEROID_3D_VEC4_TO_ARRAY_H
#define ASTEROID_3D_VEC4_TO_ARRAY_H


#include <vector>
#include "../../include/glm/vec4.hpp"

class VecOperation {
public:
    static float *toArray(glm::vec4 vec4);
    static void appendToVector(glm::vec4 vec4, std::vector<float> *vector);
};


#endif

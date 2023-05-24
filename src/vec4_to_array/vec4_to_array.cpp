#include "vec4_to_array.h"

float *VecOperation::toArray(glm::vec4 vec4) {
    auto *array = new float[4];
    array[0] = vec4.x;
    array[1] = vec4.y;
    array[2] = vec4.z;
    array[3] = vec4.w;
    return array;
}

void VecOperation::appendToVector(glm::vec4 vec4, std::vector<float> *vector) {
    vector->push_back(vec4.x);
    vector->push_back(vec4.y);
    vector->push_back(vec4.z);
    vector->push_back(vec4.w);
}

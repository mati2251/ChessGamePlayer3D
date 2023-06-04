#ifndef ASTEROID_3D_VERTEX_H
#define ASTEROID_3D_VERTEX_H

#include "../../include/glm/glm.hpp"

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

#endif //ASTEROID_3D_VERTEX_H

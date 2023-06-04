#ifndef ASTEROID_3D_MESH_H
#define ASTEROID_3D_MESH_H


#include <vector>
#include "structurs/texture.h"
#include "structurs/vertex.h"
#include "shaderprogram/shaderprogram.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    Texture texture;
    std::vector<unsigned int> indices;

    Mesh(std::vector <Vertex> vertices,Texture texture, std::vector<unsigned int> indices);

    void Draw(ShaderProgram &shader);

private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};


#endif //ASTEROID_3D_MESH_H

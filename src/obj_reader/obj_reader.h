#ifndef ASTEROID_3D_OBJ_READER_H
#define ASTEROID_3D_OBJ_READER_H

#include <iostream>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "shaderprogram/shaderprogram.h"
#include "../../include/glm/glm.hpp"
#include "obj_reader/mesh/mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ObjReader {
public:
    ObjReader(const std::string &filePath, const char *texturePath);
    void draw(glm::mat4 M);
private:
    ShaderProgram *shader;
    std::vector<Mesh> meshes;
    std::string directory;
    Texture *texture;

    void loadModel(const std::string &filePath);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif //ASTEROID_3D_OBJ_READER_H

#ifndef ASTEROID_3D_MODEL_H
#define ASTEROID_3D_MODEL_H


class Model {
public:
    int vertexCount;
    float *vertices;
    float *normals;
    float *texCoords;
    float *colors;

    virtual void draw() {};
};

#endif //ASTEROID_3D_MODEL_H

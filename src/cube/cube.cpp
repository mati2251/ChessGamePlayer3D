#include <GL/glew.h>
#include "cube.h"

Cube::~Cube() {
}

void Cube::draw() {
    glEnableVertexAttribArray(sp->a("vertex"));
    glEnableVertexAttribArray(sp->a("normal"));
    glEnableVertexAttribArray(sp->a("texCoord"));


    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertices);
    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normals);
    glVertexAttribPointer(sp->a("texCoord"), 4, GL_FLOAT, false, 0, texCoords);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("normal"));
    glDisableVertexAttribArray(sp->a("texCoord"));
}


float g_vertices[] = {
        1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,


        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,

        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        -1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 1.0f,

};

float g_colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
};

float g_normals[] = {
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,

        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, -1.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,

        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, 0.0f,

        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,

        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
};

float g_vertexNormals[] = {
        1.0f, -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f,

        1.0f, -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f,


        -1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,

        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f,

        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f,

        -1.0f, -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f,

        -1.0f, -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f,
};

float g_texCoords[] = {
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
};

Cube::Cube(ShaderProgram *sp) {
    this->sp = sp;
    this->vertices = g_vertices;
    this->normals = g_normals;
    this->texCoords = g_texCoords;
    this->colors = g_colors;
    this->vertexCount = 36;
}

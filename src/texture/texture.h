#ifndef ASTEROID_3D_TEXTURE_H
#define ASTEROID_3D_TEXTURE_H


#include <GL/gl.h>
#include "shaderprogram/shaderprogram.h"
#include <vector>
#include <GL/glew.h>
#include "lodepng/lodepng.h"
#include "shaderprogram/shaderprogram.h"

class Texture {
public:
    Texture(const char *path);

    void bind(ShaderProgram *shader);

private:
    GLuint texture;
};


#endif //ASTEROID_3D_TEXTURE_H

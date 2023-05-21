#ifndef CUBE_H
#define CUBE_H

#include "model/model.h"
#include "../shaderprogram/shaderprogram.h"

class Cube : public Model {
    ShaderProgram *sp;
public:
    Cube(ShaderProgram *sp);

    virtual ~Cube();

    void draw() override;
};


#endif

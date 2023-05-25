#ifndef ASTEROID_3D_PROGRAMSTATE_H
#define ASTEROID_3D_PROGRAMSTATE_H
#include "../../include/glm/gtc/type_ptr.hpp"
#include "../shaders_container/shaders_container.h"
#include "rotate_controller/rotate_controller.h"

class ProgramState {
private:
    ProgramState();
    static ProgramState *instance;
public:
    ~ProgramState();
    glm::mat4 P;
    glm::mat4 V;
    glm::mat4 M;
    RotateController *rotateController;
    ShadersContainer *shadersContainer;
    static ProgramState *getInstance();
};


#endif //ASTEROID_3D_PROGRAMSTATE_H

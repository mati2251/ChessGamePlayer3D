#include "program_state.h"

ProgramState *ProgramState::instance = nullptr;

ProgramState::ProgramState(){
    this->V = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f);
    this->M = glm::mat4(1.0f);
    this->rotateController = new RotateController(this->M);
    this->shadersContainer = new ShadersContainer(this->P, this->V);
}

ProgramState *ProgramState::getInstance() {
    if (instance == nullptr) {
        instance = new ProgramState();
    }
    return instance;
}

ProgramState::~ProgramState() {
    delete this->shadersContainer;
    delete instance;
    delete this;
}

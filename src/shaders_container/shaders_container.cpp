#include "shaders_container.h"

ShaderProgram *ShadersContainer::getShader(ShadersType type) {
    switch (type) {
        case ShadersType::COLORED :
            return this->colored;
    }
    return nullptr;
}

ShadersContainer::ShadersContainer(glm::mat4 P, glm::mat4 V) {
    this->P = P;
    this->V = V;
    this->colored = new ShaderProgram("../src/shaders/colored/v_colored.glsl", NULL, "../src/shaders/colored/f_colored.glsl");
    this->initShader(this->colored);
}

void ShadersContainer::initShader(ShaderProgram *shader) {
    shader->use();
    glUniformMatrix4fv(shader->u("P"), 1, false, glm::value_ptr(this->P));
    glUniformMatrix4fv(shader->u("V"), 1, false, glm::value_ptr(this->V));
}

ShadersContainer::~ShadersContainer() {
    delete this->colored;
}

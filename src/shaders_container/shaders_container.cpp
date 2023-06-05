#include "shaders_container.h"

ShaderProgram *ShadersContainer::getShader(ShadersType type) {
    switch (type) {
        case ShadersType::TEXTURED :
            return this->textured;
    }
    return nullptr;
}

ShadersContainer::ShadersContainer(glm::mat4 P, glm::mat4 V) {
    this->P = P;
    this->V = V;
    this->textured = new ShaderProgram("../src/shaders/textured/v_textured.glsl", NULL,
                                       "../src/shaders/textured/f_textured.glsl");
    this->initShader(this->textured);
}

void ShadersContainer::initShader(ShaderProgram *shader) {
    shader->use();
    glUniformMatrix4fv(shader->u("P"), 1, false, glm::value_ptr(this->P));
    glUniformMatrix4fv(shader->u("V"), 1, false, glm::value_ptr(this->V));
}

ShadersContainer::~ShadersContainer() {
    delete this->textured;
}

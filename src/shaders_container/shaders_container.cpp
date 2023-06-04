#include "shaders_container.h"

ShaderProgram *ShadersContainer::getShader(ShadersType type) {
    switch (type) {
        case ShadersType::COLORED :
            return this->colored;
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
    this->colored = new ShaderProgram("../src/shaders/colored/v_colored.glsl", NULL,
                                      "../src/shaders/colored/f_colored.glsl");
    this->initShader(this->colored);
    this->initShader(this->textured);
}

void ShadersContainer::initShader(ShaderProgram *shader) {
    shader->use();
    glUniformMatrix4fv(shader->u("P"), 1, false, glm::value_ptr(this->P));
    glUniformMatrix4fv(shader->u("V"), 1, false, glm::value_ptr(this->V));
}

ShadersContainer::~ShadersContainer() {
    delete this->colored;
    delete this->textured;
}

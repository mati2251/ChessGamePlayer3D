#include <vector>
#include "shaders_container.h"

ShaderProgram *ShadersContainer::getShader(ShadersType type) {
    switch (type) {
        case ShadersType::TEXTURED :
            return this->textured;
    }
    return nullptr;
}

struct PointLight
{
    glm::vec3 position;  // Pozycja światła
    glm::vec3 color;     // Kolor światła
};

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
    std::vector<PointLight> pointLights = {
            {glm::vec3(-5.0f, -5.0f, 5.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  // Czerwone światło
            {glm::vec3(5.0f, -5.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // Zielone światło
            {glm::vec3(5.0f, 5.0f, 5.0f), glm::vec3(0.0f, 0.0f, 1.0f)},   // Niebieskie światło
            {glm::vec3(-5.0f, 5.0f, 5.0f), glm::vec3(1.0f, 1.0f, 0.0f)}   // Żółte światło
    };

    unsigned int lightsBuffer;
    glGenBuffers(1, &lightsBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, lightsBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(PointLight) * pointLights.size(), pointLights.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glUniformBlockBinding(shader->u("pointLights"), lightsBuffer, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsBuffer);
}

ShadersContainer::~ShadersContainer() {
    delete this->textured;
}

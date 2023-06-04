#include "colored_model.h"

void ColoredModel::draw(glm::mat4 M) {
    this->shader->use();

    glUniformMatrix4fv(this->shader->u("M"), 1, false, glm::value_ptr(M));
    glEnableVertexAttribArray(this->shader->a("vertex"));
    glVertexAttribPointer(this->shader->a("vertex"), 4, GL_FLOAT, false, 0, this->vertices);

    glEnableVertexAttribArray(this->shader->a("color"));
    glVertexAttribPointer(this->shader->a("color"), 4, GL_FLOAT, false, 0, this->colors);

    glDrawArrays(this->mode, 0, this->vertexCount);

    glDisableVertexAttribArray(this->shader->a("vertex"));
    glDisableVertexAttribArray(this->shader->a("color"));
}


ColoredModel::ColoredModel(ShadersContainer *container, float *vertices, float *colors, int vertexCount,
                           GLenum mode) {
    this->shader = container->getShader(ShadersType::COLORED);
    this->vertexCount = vertexCount;
    this->vertices = vertices;
    this->colors = colors;
    this->mode = mode;
}

#include "colored_model.h"

void ColoredModel::draw(glm::mat4 M) {
    glUniformMatrix4fv(this->shader->u("M"), 1, false, glm::value_ptr(M));
    glEnableVertexAttribArray(this->shader->a("vertex"));
    glVertexAttribPointer(this->shader->a("vertex"), 4, GL_FLOAT, false, 0, this->vertices);

    glEnableVertexAttribArray(this->shader->a("color"));
    glVertexAttribPointer(this->shader->a("color"), 4, GL_FLOAT, false, 0, this->colors);

    glEnableVertexAttribArray(this->shader->a("normal"));
    glVertexAttribPointer(this->shader->a("normal"), 4, GL_FLOAT, false, 0, this->normals);

    glDrawArrays(this->mode, 0, this->vertexCount);

    glDisableVertexAttribArray(this->shader->a("vertex"));
    glDisableVertexAttribArray(this->shader->a("normal"));
    glDisableVertexAttribArray(this->shader->a("color"));
}


ColoredModel::ColoredModel(ShadersContainer *container, float *vertices, float *colors, float *normals, int vertexCount,
                           GLenum mode) {
    this->shader = container->getShader(ShadersType::COLORED);
    this->vertexCount = vertexCount;
    this->vertices = vertices;
    this->colors = colors;
    this->normals = normals;
    this->mode = mode;
}

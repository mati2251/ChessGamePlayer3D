#include "chessboard.h"

void Chessboard::draw(glm::mat4 M) {
    this->copyMandTransform(M);
    this->mesh->draw();
}

Chessboard::Chessboard() {
    this->texture = new Texture("../resources/chessboard.png");
    this->addChessboardToDraw();
    this->mesh = new Mesh(this->vertices, this->texture, {1, 2, 3, 1, 3, 0});
}

void Chessboard::addChessboardToDraw() {
    auto v = Vertex{
            glm::vec3(0.0f, -4.5f, -4.5f),
            glm::vec3(18.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 0.0f)
    };
    this->vertices.push_back(v);
    v = Vertex{
            glm::vec3(0.0f, 4.5f, -4.5f),
            glm::vec3(18.0f, 0.0f, 0.0f),
            glm::vec2(0.0f, 1.0f)
    };
    this->vertices.push_back(v);
    v = Vertex{
            glm::vec3(0.0f, 4.5f, 4.5f),
            glm::vec3(18.0f, 0.0f, 0.0f),
            glm::vec2(1.0f, 1.0f)
    };
    this->vertices.push_back(v);
    v = Vertex{
            glm::vec3(0.0f, -4.5f, 4.5f),
            glm::vec3(18.0f, 0.0f, 0.0f),
            glm::vec2(1.0f, 0.0f)
    };
    this->vertices.push_back(v);
}

void Chessboard::copyMandTransform(glm::mat4 M) {
    ShaderProgram *sp = ProgramState::getInstance()->shadersContainer->getShader(ShadersType::TEXTURED);
    sp->use();
    this->obj = glm::rotate(M, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
    this->obj = glm::rotate(this->obj, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0));
    this->obj = glm::rotate(this->obj, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0));
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(this->obj));
}

#include "figure.h"
#include "program_state/program_state.h"

Figure::Figure(std::string pathToObjFile, Figure::Position position, bool white) {
    this->position = position;
    TextureContainer *textureContainer = ProgramState::getInstance()->textureContainer;
    this->texture = white ? textureContainer->whiteWood : textureContainer->blackWood;
    this->objReader = new ObjReader(pathToObjFile, this->texture);
}

void Figure::draw() {
    glm::mat4 M = glm::translate(ProgramState::getInstance()->M, glm::vec3(-3.5, -3.5, 0));
    M = positionTranslate(M);
    M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
    M = glm::rotate(M, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0));
    objReader->draw(M);
}

glm::mat4 Figure::positionTranslate(glm::mat4 M) {
    int x = this->position.x - 97;
    int y = this->position.y - 49;
    M = glm::translate(M, glm::vec3(x, y, 0));
    return M;
}

void Figure::makeMove(Figure::Position position) {
    this->position = position;
}

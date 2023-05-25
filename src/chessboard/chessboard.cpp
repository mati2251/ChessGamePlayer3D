#include "chessboard.h"

void Chessboard::draw(glm::mat4 M) {
    this->copyMandTransform(M);
    this->coloredModel->draw(obj);
}

Chessboard::Chessboard() {
    ShadersContainer *container = ProgramState::getInstance()->shadersContainer;
    this->addChessboardToDraw();
    this->addCaseToDraw();
    this->coloredModel = new ColoredModel(container, this->vertices.data(), this->colors.data(), this->vertexCount,
                                          GL_TRIANGLES);
}

void Chessboard::addSquareToDraw(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, glm::vec4 color) {
    VecOperation::appendToVector(p1, &this->vertices);
    VecOperation::appendToVector(p2, &this->vertices);
    VecOperation::appendToVector(p3, &this->vertices);
    VecOperation::appendToVector(p3, &this->vertices);
    VecOperation::appendToVector(p4, &this->vertices);
    VecOperation::appendToVector(p2, &this->vertices);
    for (int i = 0; i < 6; i++) {
        VecOperation::appendToVector(color, &this->colors);
    }
    this->vertexCount += 6;
}

void Chessboard::addRowToDraw(float y, bool startFromBlack) {
    float x = -4;
    float width = 1;
    float z = 0;
    for (int i = 0; i < 8; i++) {
        this->addSquareToDraw(
                glm::vec4(x, y, z, 1),
                glm::vec4(x + width, y, z, 1),
                glm::vec4(x, y + width, z, 1),
                glm::vec4(x + width, y + width, z, 1),
                glm::vec4((i + startFromBlack) % 2, (i + startFromBlack) % 2, (i + startFromBlack) % 2, 0)
        );
        x += width;
    }
}

void Chessboard::addChessboardToDraw() {
    float y = -4;
    for (int i = 0; i < 8; i++) {
        this->addRowToDraw(y, i % 2 == 0);
        y += 1;
    }
}

void Chessboard::addCaseToDraw() {
    float width = 0.5;
    glm::vec4 color = glm::vec4(0.2, 0.2, 0.2, 0);
    glm::vec4 chessboardLim1 = glm::vec4(-4, -4, 0, 1);
    glm::vec4 chessboardLim2 = glm::vec4(4, -4, 0, 1);
    glm::vec4 chessboardLim3 = glm::vec4(4, 4, 0, 1);
    glm::vec4 chessboardLim4 = glm::vec4(-4, 4, 0, 1);
    glm::vec4 caseLim1 = glm::vec4(chessboardLim1.x - width, chessboardLim1.y - width, 0, 1);
    glm::vec4 caseLim2 = glm::vec4(chessboardLim2.x + width, chessboardLim2.y - width, 0, 1);
    glm::vec4 caseLim3 = glm::vec4(chessboardLim3.x + width, chessboardLim3.y + width, 0, 1);
    glm::vec4 caseLim4 = glm::vec4(chessboardLim4.x - width, chessboardLim4.y + width, 0, 1);
    glm::vec4 bottomCaseLim1 = glm::vec4(caseLim1.x, caseLim1.y, caseLim1.z - width, 1);
    glm::vec4 bottomCaseLim2 = glm::vec4(caseLim2.x, caseLim2.y, caseLim2.z - width, 1);
    glm::vec4 bottomCaseLim3 = glm::vec4(caseLim3.x, caseLim3.y, caseLim3.z - width, 1);
    glm::vec4 bottomCaseLim4 = glm::vec4(caseLim4.x, caseLim4.y, caseLim4.z - width, 1);
    this->addSquareToDraw(chessboardLim1, chessboardLim2, caseLim1, caseLim2, color);
    this->addSquareToDraw(caseLim1, caseLim2, bottomCaseLim1, bottomCaseLim2, color);
    this->addSquareToDraw(chessboardLim1, chessboardLim4, caseLim1, caseLim4, color);
    this->addSquareToDraw(caseLim1, caseLim4, bottomCaseLim1, bottomCaseLim4, color);
    this->addSquareToDraw(chessboardLim4, chessboardLim3, caseLim4, caseLim3, color);
    this->addSquareToDraw(caseLim4, caseLim3, bottomCaseLim4, bottomCaseLim3, color);
    this->addSquareToDraw(chessboardLim3, chessboardLim2, caseLim3, caseLim2, color);
    this->addSquareToDraw(caseLim2, caseLim3, bottomCaseLim2, bottomCaseLim3, color);
    this->addSquareToDraw(bottomCaseLim1, bottomCaseLim2, bottomCaseLim4, bottomCaseLim3, color);
}

void Chessboard::copyMandTransform(glm::mat4 M) {
    this->obj = M;
}

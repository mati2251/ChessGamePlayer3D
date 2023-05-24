#ifndef ASTEROID_3D_CHESSBOARD_H
#define ASTEROID_3D_CHESSBOARD_H


#include <vector>
#include "model/model.h"
#include "../colored_model/colored_model.h"
#include "../program_state/program_state.h"
#include "../vec4_to_array/vec4_to_array.h"

class Chessboard: Model {
    ColoredModel *coloredModel;
    std::vector<float> vertices;
    std::vector<float> colors;
    std::vector<float> normals = {};
    int vertexCount = 36;
    void addSquareToDraw(glm::vec4 p1, glm::vec4 p2, glm::vec4 p3, glm::vec4 p4, glm::vec4 color);
    void addRowToDraw(float y, bool startFromBlack = false);
    void addChessboardToDraw();
    void addCaseToDraw();
public:
    Chessboard();
    void draw(glm::mat4 M) override;
};


#endif //ASTEROID_3D_CHESSBOARD_H

#ifndef ASTEROID_3D_CHESSBOARD_H
#define ASTEROID_3D_CHESSBOARD_H


#include "model/model.h"
#include "../colored_model/colored_model.h"
#include "../program_state/program_state.h"

class Chessboard: Model {
    ColoredModel *coloredModel;
public:
    Chessboard();
    void draw(glm::mat4 M) override;

};


#endif //ASTEROID_3D_CHESSBOARD_H

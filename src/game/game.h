#ifndef ASTEROID_3D_GAME_H
#define ASTEROID_3D_GAME_H


#include "figure/figure.h"
#include "../constants.h"

class Game {
public:
    Game();
    std::vector<Figure> figures;
    void draw();
    void nextMove();
    void makeMove(Figure::Position from, Figure::Position to);
};


#endif //ASTEROID_3D_GAME_H

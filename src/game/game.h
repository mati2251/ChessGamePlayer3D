#ifndef ASTEROID_3D_GAME_H
#define ASTEROID_3D_GAME_H

#include <vector>
#include <queue>
#include "figure/figure.h"
#include "../constants.h"
#include "chessmove/chessmove.h"

class Game {
public:
    Game();
    std::vector<Figure> figures;
    std::queue<ChessMove> moves;
    void draw();
    void nextMove();
    void makeMove(Figure::Position from, Figure::Position to);
    void loadPGNFile(const std::string& filePath);
};

#endif //ASTEROID_3D_GAME_H

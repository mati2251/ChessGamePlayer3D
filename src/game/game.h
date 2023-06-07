#ifndef ASTEROID_3D_GAME_H
#define ASTEROID_3D_GAME_H

#include <stack>
#include <vector>
#include "figure/figure.h"
#include "chessmove.h"
#include "../constants.h"

class Game {
public:
    Game();
    std::vector<Figure> figures;
    std::stack<ChessMove> moves;
    void draw();
    void nextMove();
    void makeMove(Figure::Position from, Figure::Position to);
    void loadPGNFile(const std::string& filePath);
};

#endif //ASTEROID_3D_GAME_H

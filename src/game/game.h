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
    void makeMove(ChessMove move);
    void loadGameFile(const std::string& filePath);
};

#endif //ASTEROID_3D_GAME_H

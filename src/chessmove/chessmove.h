#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <string>
#include "../figure/figure.h"

class ChessMove {
public:
    Figure::Position from;
    Figure::Position to;
    bool isCapture;

    ChessMove(std::string  from, std::string  to, bool isCapture);
};

#endif // CHESS_MOVE_H

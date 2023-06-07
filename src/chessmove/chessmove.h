#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <string>

class ChessMove {
public:
    std::string from;
    std::string to;
    bool isCapture;

    ChessMove(std::string  from, std::string  to, bool isCapture);
};

#endif // CHESS_MOVE_H

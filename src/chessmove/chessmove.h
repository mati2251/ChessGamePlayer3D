#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <string>

class ChessMove {
public:
    std::string from;
    std::string to;
    bool isCapture;
    char piece;

    ChessMove(const std::string& from, const std::string& to, bool isCapture, char piece);
};

#endif // CHESS_MOVE_H

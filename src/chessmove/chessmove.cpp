#include "ChessMove.h"

ChessMove::ChessMove(const std::string& from, const std::string& to, bool isCapture, char piece)
    : from(from), to(to), isCapture(isCapture), piece(piece) {}

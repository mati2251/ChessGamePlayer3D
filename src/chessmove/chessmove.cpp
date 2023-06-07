#include "chessmove.h"

#include <utility>

ChessMove::ChessMove(std::string from, std::string to, bool isCapture)
        : from{from[0], from[1]}, to{to[0], to[1]}, isCapture(isCapture) {}

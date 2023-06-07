#include "chessmove.h"

#include <utility>

ChessMove::ChessMove(std::string  from, std::string  to, bool isCapture)
    : from(std::move(from)), to(std::move(to)), isCapture(isCapture) {}

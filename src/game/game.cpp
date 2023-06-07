#include "game.h"
#include <fstream>
#include <sstream>

Game::Game() {
    this->figures.emplace_back(TOWER, Figure::Position{'a', '1'}, true);
    this->figures.emplace_back(HORSE, Figure::Position{'b', '1'}, true);
    this->figures.emplace_back(RUNNER, Figure::Position{'c', '1'}, true);
    this->figures.emplace_back(KING, Figure::Position{'d', '1'}, true);
    this->figures.emplace_back(QUEEN, Figure::Position{'e', '1'}, true);
    this->figures.emplace_back(RUNNER, Figure::Position{'f', '1'}, true);
    this->figures.emplace_back(HORSE, Figure::Position{'g', '1'}, true);
    this->figures.emplace_back(TOWER, Figure::Position{'h', '1'}, true);
    for (char i = 'a'; i <= 'h'; i++) {
        this->figures.emplace_back(PAWN, Figure::Position{i, '2'}, true);
    }

    this->figures.emplace_back(TOWER, Figure::Position{'a', '8'}, false);
    this->figures.emplace_back(HORSE, Figure::Position{'b', '8'}, false);
    this->figures.emplace_back(RUNNER, Figure::Position{'c', '8'}, false);
    this->figures.emplace_back(KING, Figure::Position{'d', '8'}, false);
    this->figures.emplace_back(QUEEN, Figure::Position{'e', '8'}, false);
    this->figures.emplace_back(RUNNER, Figure::Position{'f', '8'}, false);
    this->figures.emplace_back(HORSE, Figure::Position{'g', '8'}, false);
    this->figures.emplace_back(TOWER, Figure::Position{'h', '8'}, false);
    for (char i = 'a'; i <= 'h'; i++) {
        this->figures.emplace_back(PAWN, Figure::Position{i, '7'}, false);
    }
}

void Game::draw() {
    for(auto &figure : this->figures) {
        figure.draw();
    }
}

void Game::nextMove() {
    if (!moves.empty()) {
        ChessMove move = moves.top();
        moves.pop();
        makeMove(Figure::Position{move.from[0], move.from[1]}, Figure::Position{move.to[0], move.to[1]});
    }
}

void Game::makeMove(Figure::Position from, Figure::Position to) {
    for (auto &figure : this->figures) {
        if (figure.position.x == to.x && figure.position.y == to.y) {
            this->figures.erase(std::remove(this->figures.begin(), this->figures.end(), figure), this->figures.end());
            break;
        }
    }
    for (auto &figure : this->figures) {
        if (figure.position.x == from.x && figure.position.y == from.y) {
            figure.makeMove(to);
            break;
        }
    }
}

void Game::loadPGNFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string moveNumber, whiteMove, blackMove;

        iss >> moveNumber >> whiteMove >> blackMove;

        if (whiteMove.find('x') != std::string::npos) { 
            moves.push(ChessMove(whiteMove.substr(0, 2), whiteMove.substr(3, 2), true, whiteMove[0]));
        } else {
            moves.push(ChessMove(whiteMove.substr(0, 2), whiteMove.substr(2, 2), false, whiteMove[0]));
        }

        if (blackMove.find('x') != std::string::npos) { 
            moves.push(ChessMove(blackMove.substr(0, 2), blackMove.substr(3, 2), true, blackMove[0]));
        } else { 
            moves.push(ChessMove(blackMove.substr(0, 2), blackMove.substr(2, 2), false, blackMove[0]));
        }
    }

    file.close();
}

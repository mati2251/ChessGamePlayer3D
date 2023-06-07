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
    for (auto &figure: this->figures) {
        figure.draw();
    }
}

void Game::nextMove() {
    if (!moves.empty()) {
        ChessMove move = moves.front();
        moves.pop();
        makeMove(move);
    }
}

void Game::makeMove(ChessMove move) {
    bool toCapture = move.isCapture;
    for (auto &figure: this->figures) {
        if (figure.position.x == move.to.x && figure.position.y == move.to.y) {
            this->figures.erase(std::remove(this->figures.begin(), this->figures.end(), figure), this->figures.end());
            toCapture = false;
            break;
        }
    }
    if (toCapture) {
        for (auto &figure: this->figures) {
            if (figure.position.x == move.to.x && figure.position.y == move.to.y - 1) {
                this->figures.erase(std::remove(this->figures.begin(), this->figures.end(), figure),
                                    this->figures.end());
                break;
            }
        }
    }
    for (auto &figure: this->figures) {
        if (figure.position.x == move.from.x && figure.position.y == move.from.y) {
            figure.makeMove(move.to);
            break;
        }
    }
}

void Game::loadGameFile(const std::string &filePath) {
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string move;

        iss >> move;

        if (move.find('x') != std::string::npos) {
            moves.emplace(move.substr(0, 2), move.substr(3, 2), true);
        } else {
            moves.emplace(move.substr(0, 2), move.substr(3, 2), false);
        }
    }

    file.close();
}

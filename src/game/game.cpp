#include "game.h"

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
    this->makeMove(Figure::Position{'a', '2'}, Figure::Position{'a', '7'});
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

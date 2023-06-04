#ifndef ASTEROID_3D_FIGURE_H
#define ASTEROID_3D_FIGURE_H


#include "obj_reader/obj_reader.h"

class Figure {
private:
    ObjReader *objReader;
    Texture *texture;
    glm::mat4 positionTranslate(glm::mat4 M);
public:
    struct Position {
        char x;
        char y;
    };
    Position position;
    Figure(std::string pathToObjFile, Figure::Position position, bool white = true);
    void makeMove(Figure::Position position);
    void draw();
    bool operator==(const Figure& other) const {
        return position.x == other.position.x && position.y == other.position.y;
    }
};


#endif //ASTEROID_3D_FIGURE_H

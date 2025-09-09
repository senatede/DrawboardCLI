#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Shape.h"

class Board {
public:
    int width, height;
    std::vector<std::vector<char> > grid;

    Board(int w, int h);
    void print();
    void addShape(const std::shared_ptr<Shape>& shape);
private:
    std::vector<std::shared_ptr<Shape>> shapes;
    void drawAllShapes();
};



#endif

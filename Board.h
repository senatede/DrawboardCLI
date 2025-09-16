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

    void clear();
    // void addShape(const std::shared_ptr<Shape>& shape);
    void addTriangle(const std::string& fill, const std::string& color, int x, int y, int height);
    void addBox(const std::string& fill, const std::string& color, int x, int y, int width, int height);
private:
    std::vector<std::shared_ptr<Shape>> shapes;
    void drawAllShapes();
};



#endif

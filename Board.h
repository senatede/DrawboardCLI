#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Shapes/Shape.h"

class Board {
public:
    int width, height;

    Board(int w, int h);
    ~Board() = default;

    void print();
    void clear();
    std::vector<std::string> listShapes() const;
    int addTriangle(bool fill, const std::string& color, int x, int y, int height);
    int addBox(bool fill, const std::string& color, int x, int y, int width, int height);
private:
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::vector<char> > grid;
    void drawAllShapes();
};



#endif

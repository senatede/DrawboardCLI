#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Shapes/Shape.h"

class Board {
public:
    int width, height;

    Board(int w, int h);
    Board() = default;

    ~Board() = default;

    void print();
    void clear();
    std::vector<std::string> listShapes() const;
    int selectShape(int id);
    int selectShape(int x, int y);
    int removeShape();
    int paintShape(const std::string& color) const;
    int editShape(const std::vector<int>& parameters) const;
    int moveShape(const std::vector<int>& parameters);
    int addTriangle(bool fill, const std::string& color, int x, int y, int height);
    int addBox(bool fill, const std::string& color, int x, int y, int width, int height);
    int addCircle(bool fill, const std::string& color, int x, int y, int radius);
    int addLine(bool fill, const std::string& color, int x, int y, int x2, int y2);

    int saveToFile(const std::string& filepath) const;
    static std::unique_ptr<Board> loadFromFile(const std::string& filepath);
private:
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::vector<char> > grid;
    int selectedShapeIndex = -1;
    void drawAllShapes();
    int isShapeValid(const std::shared_ptr<Shape>& shape) const;
};



#endif

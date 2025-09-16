#include <utility>
#include <vector>

#ifndef SHAPE_H
#define SHAPE_H

class Board;

class Shape {
protected:
    int boardWidth, boardHeight;
    static int nextId;

    void setPixel(std::vector<std::pair<int, int>>& coordinates, const int row, const int col) const {
        if (col >= 0 && col < boardWidth && row >= 0 && row < boardHeight) coordinates.emplace_back(row, col);
    }
public:
    int x, y;
    int id;
    bool fill;
    std::string color;

    Shape(const int boardWidth, const int boardHeight, const bool fill, std::string color, const int x, const int y) :
        x(x), y(y), boardWidth(boardWidth), boardHeight(boardHeight), fill(fill), color(std::move(color)), id(nextId++) {}
    virtual ~Shape() = default;

    virtual std::string info() = 0;
    virtual std::vector<std::pair<int, int>> getCoordinates() = 0;

    static void setStartingId(const int id) {nextId = id;}
    // [[nodiscard]] int getId() const { return id; }
};

#endif //SHAPE_H
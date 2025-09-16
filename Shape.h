#include <utility>

//
// Created by Bohdan Hupalo on 08.09.2025.
//

#ifndef SHAPE_H
#define SHAPE_H

class Board;

class Shape {
protected:
    Board& board;
    int x, y;
    std::string color;
    std::string fill;
public:
    Shape(Board& board, std::string fill, std::string color, const int x, const int y) :
        board(board), x(x), y(y), fill(std::move(fill)), color(std::move(color)) {}
    virtual ~Shape() = default;

    virtual void draw() = 0;
};

#endif //SHAPE_H

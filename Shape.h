//
// Created by Bohdan Hupalo on 08.09.2025.
//

#ifndef SHAPE_H
#define SHAPE_H

class Board;

class Shape {
protected:
    Board& board;
public:
    Shape(Board& board) : board(board) {}
    virtual ~Shape() = default;

    virtual void draw() = 0;
};

#endif //SHAPE_H

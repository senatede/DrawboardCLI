#include "Board.h"

#include <iostream>
#include <vector>

Board::Board(const int w, const int h) : width(w), height(h), grid(height, std::vector<char>(width, ' ')), shapes(0) {}

void Board::drawAllShapes() {
    for (auto& shape : this->shapes) {
        shape->draw();
    }
}

void Board::print() {
    drawAllShapes();
    for (auto& row : grid) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << "\n";
    }
}

void Board::addShape(const std::shared_ptr<Shape>& shape) {
    shapes.push_back(shape);
}
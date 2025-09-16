#include "Board.h"
#include "Triangle.cpp"
#include "Box.cpp"

#include <iostream>
#include <vector>

Board::Board(const int w, const int h) : width(w), height(h), grid(height, std::vector<char>(width, ' ')), shapes(0) {}

void Board::drawAllShapes() {
    for (auto& shape : this->shapes) {
        shape->draw();
    }
}

void Board::print() {
    std::string result;
    drawAllShapes();
    std::cout << "\033[2J\033[H";
    for (auto& row : grid) {
        for (char c : row) {
            switch (c) {
                case 'R':   std::cout << "\033[31m"; break;
                case 'G':   std::cout << "\033[32m"; break;
                case 'B':   std::cout << "\033[34m"; break;
                default:    std::cout << "\033[0m"; break;
            }
            std::cout << c;
        }
        std::cout << "\n";
    }
    std::cout << "\033[0m";
}

void Board::clear() {
    shapes.clear();
    grid = std::vector<std::vector<char>>(this->height, std::vector<char>(this->width, ' '));
}

// void Board::addShape(const std::shared_ptr<Shape>& shape) {
//     shapes.push_back(shape);
// }

void Board::addTriangle(const std::string& fill, const std::string& color, int x, int y, int height) {
    shapes.push_back(std::make_shared<Triangle>(*this, fill, color, x, y, height));
}

void Board::addBox(const std::string& fill, const std::string& color, int x, int y, int width, int height) {
    shapes.push_back(std::make_shared<Box>(*this, fill, color, x, y, width, height));
}
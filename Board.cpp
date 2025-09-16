#include "Board.h"
#include "Shapes/Triangle.cpp"
#include "Shapes/Box.cpp"

#include <iostream>
#include <vector>

int Shape::nextId = 0;

Board::Board(const int w, const int h) : width(w), height(h), grid(height, std::vector(width, ' ')), shapes(0) {}

void Board::drawAllShapes() {
    for (auto& shape : this->shapes) {
        auto coordinates = shape->getCoordinates();
        if (!coordinates.empty()) {
            for (auto coord : coordinates) {
                grid[coord.first][coord.second] = shape->color[0];
            }
        }
    }
}

void Board::print() {
    std::string result;
    drawAllShapes();
    std::cout << "\033[2J\033[H";
    for (auto& row : grid) {
        for (const char c : row) {
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
    grid = std::vector(this->height, std::vector(this->width, ' '));
}

std::vector<std::string> Board::listShapes() const {
    std::vector<std::string> result;
    result.reserve(this->shapes.size());
    for (const auto& shape : this->shapes) {
            result.emplace_back(shape->info());
    }
    return result;
}

int Board::addTriangle(const bool fill, const std::string& color, int x, int y, int height) {
    const auto tr = std::make_shared<Triangle>(this->width, this->height, fill, color, x, y, height);
    if (tr->getCoordinates().empty()) return 1;
    shapes.push_back(tr);
    return 0;
}

int Board::addBox(const bool fill, const std::string& color, int x, int y, int width, int height) {
    const auto box = std::make_shared<Box>(this->width, this->height, fill, color, x, y, width, height);
    if (box->getCoordinates().empty()) return 1;
    shapes.push_back(box);
    return 0;
}
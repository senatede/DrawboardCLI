#include "Board.h"
#include "Shapes/Triangle.cpp"
#include "Shapes/Box.cpp"
#include "Shapes/Circle.cpp"
#include "Shapes/Line.cpp"

#include <iostream>
#include <vector>

int Shape::nextId = 0;

Board::Board(const int w, const int h) : width(w), height(h), grid(height, std::vector(width, ' ')), shapes(0) {}

void Board::drawAllShapes() {
    grid = std::vector(this->height, std::vector(this->width, ' '));
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
    char lastChar = ' ';
    drawAllShapes();
    std::cout << "\033[2J\033[H";
    for (auto& row : grid) {
        for (const char c : row) {
            if (c != lastChar) {
                switch (c) {
                    case 'R':   std::cout << "\033[31m"; break;
                    case 'G':   std::cout << "\033[32m"; break;
                    case 'B':   std::cout << "\033[34m"; break;
                    default:    std::cout << "\033[0m"; break;
                }
                lastChar = c;
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

int Board::selectShape(int id) {
    auto it = [&] {
        for (int i = 0; i < static_cast<int>(shapes.size()); i++) if (shapes[i]->id == id) return i;
        return -1;
    };
    const int index = it();
    if (index == -1) return 1;
    selectedShapeIndex = index;
    std::cout << "You have selected shape with id:" << shapes[selectedShapeIndex]->info() << std::endl;
    return 0;
}

int Board::selectShape(int x, int y) {
    auto it = [&] {
        for (int i = static_cast<int>(shapes.size()) - 1; i >= 0; i--)
            if (std::ranges::any_of(shapes[i]->getCoordinates(), [&](const auto& c){ return c.first == y && c.second == x; })) {
                return i;
            }
        return -1;
    };
    const int index = it();
    if (index == -1) return 1;
    selectedShapeIndex = index;
    std::cout << "You have selected shape with id:" << shapes[selectedShapeIndex]->info() << std::endl;
    return 0;
}

int Board::removeShape() {
    if (selectedShapeIndex == -1) return 1;
    shapes.erase(shapes.begin() + selectedShapeIndex);
    selectedShapeIndex = -1;
    return 0;
}

int Board::paintShape(const std::string& color) const {
    if (selectedShapeIndex == -1) return 1;
    shapes[selectedShapeIndex]->color = color;
    return 0;
}

int Board::isShapeValid(const std::shared_ptr<Shape>& shape) const {
    const size_t n_coord = shape->getCoordinates().size();
    if (n_coord == 0) return 1;
    if (n_coord == width * height) return 2;
    for (const auto& sh : this->shapes) {
        if (shape->equals(*sh)) return 3;
    }
    return 0;
}

int Board::editShape(const std::vector<int>& parameters) const {
    if (selectedShapeIndex == -1) return -1;

    switch (auto shape = shapes[selectedShapeIndex]; shape->type) {
        case ShapeType::Triangle: {
            if (parameters.size() != 1) return -2;

            const auto tr = std::dynamic_pointer_cast<Triangle>(shape);
            const int old_height = tr->height;
            const int new_height = parameters[0];
            tr->height = new_height;

            const int valid = isShapeValid(tr);
            if (valid == 0) return 0;
            tr->height = old_height;
            return valid;
        }
        case ShapeType::Box:{
            if (parameters.size() != 2) return -2;

            const auto box = std::dynamic_pointer_cast<Box>(shape);
            const int old_width = box->width;
            const int new_width = parameters[0];
            const int old_height = box->height;
            const int new_height = parameters[1];
            box->width = new_width;
            box->height = new_height;

            const int valid = isShapeValid(box);
            if (valid == 0) return 0;
            box->width = old_width;
            box->height = old_height;
            return valid;
        }
        case ShapeType::Circle: {
            if (parameters.size() != 1) return -2;

            const auto cir = std::dynamic_pointer_cast<Circle>(shape);
            const int old_radius = cir->radius;
            const int new_radius = parameters[0];
            cir->radius = new_radius;

            const int valid = isShapeValid(cir);
            if (valid == 0) return 0;
            cir->radius = old_radius;
            return valid;
        }
        case ShapeType::Line: {
            if (parameters.size() != 2) return -2;

            const auto lin = std::dynamic_pointer_cast<Line>(shape);
            const int old_dx = lin->dx;
            const int new_dx = parameters[0]-lin->x;
            const int old_dy = lin->y;
            const int new_dy = parameters[1]-lin->y;
            lin->dx = new_dx;
            lin->dy = new_dy;

            const int valid = isShapeValid(lin);
            if (valid == 0) return 0;
            lin->dx = old_dx;
            lin->dy = old_dy;
            return valid;
        }
    }
}

int Board::moveShape(const std::vector<int>& parameters) {
    int x, y;
    if (selectedShapeIndex == -1) return -1;
    auto shape = shapes[selectedShapeIndex];
    switch (parameters.size()) {
        case 0:
            x = shape->x; y = shape->y; break;
        case 2:
            x = parameters[0]; y = parameters[1]; break;
        default:
            return -2;
    }
    const int old_x = shape->x;
    const int old_y = shape->y;
    shape->x = x;
    shape->y = y;
    int valid = isShapeValid(shape);
    if (x == old_x && y == old_y || valid == 0) {
        shapes.emplace_back(shape);
        shapes.erase(shapes.begin() + selectedShapeIndex);
        selectedShapeIndex = static_cast<int>(shapes.size()) - 1;
        return 0;
    }
    shape->x = old_x;
    shape->y = old_y;
    return valid;
}


int Board::addTriangle(const bool fill, const std::string& color, int x, int y, int height) {
    const auto tr = std::make_shared<Triangle>(this->width, this->height, fill, color, x, y, height);
    const int valid = isShapeValid(tr);
    if (valid == 0) {
        shapes.emplace_back(tr); return 0;
    }
    return valid;
}

int Board::addBox(const bool fill, const std::string& color, int x, int y, int width, int height) {
    const auto box = std::make_shared<Box>(this->width, this->height, fill, color, x, y, width, height);
    const int valid = isShapeValid(box);
    if (valid == 0) {
        shapes.emplace_back(box); return 0;
    }
    return valid;
}

int Board::addCircle(const bool fill, const std::string& color, int x, int y, int radius) {
    const auto cir = std::make_shared<Circle>(this->width, this->height, fill, color, x, y, radius);
    const int valid = isShapeValid(cir);
    if (valid == 0) {
        shapes.emplace_back(cir); return 0;
    }
    return valid;
}

int Board::addLine(bool fill, const std::string &color, int x, int y, int x2, int y2) {
    const auto lin = std::make_shared<Line>(this->width, this->height, fill, color, x, y, x2, y2);
    const int valid = isShapeValid(lin);
    if (valid == 0) {
        shapes.emplace_back(lin); return 0;
    }
    return valid;
}

int Board::saveBoard() const {
    return 0;
}

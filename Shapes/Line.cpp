#include "Shape.h"
#include "Shape.h"

class Line final : public Shape {
    public:
    int dx, dy;
    Line(const int boardWidth, const int boardHeight, const bool fill, const std::string &color,
        const int x, const int y, const int x2, const int y2)
        : Shape(boardWidth, boardHeight, ShapeType::Line, fill, color, x, y), dx(x2-x), dy(y2-y) {};
    ~Line() override = default;

    bool equals(const Shape& other) const override {
        if (this->type != other.type) return false;
        auto& t = dynamic_cast<const Line&>(other);
        return Shape::equals(other) && dx == t.dx && dy == t.dy;
    }

    std::string info() override {
        std::string result;
        result += std::to_string(id);
        result += " line ";
        result += std::tolower(color[0]);
        result += color.substr(1);
        result += " x:";
        result += std::to_string(x);
        result += " y:";
        result += std::to_string(y);
        result += " x2:";
        result += std::to_string(x+dx);
        result += " y2:";
        result += std::to_string(y+dy);
        return result;
    }

    std::vector<std::pair<int, int>> getCoordinates() override {
        std::vector<std::pair<int, int>> coordinates;
        int x2 = x + dx;
        int y2 = y + dy;

        int dx = std::abs(x2 - x);
        int dy = std::abs(y2 - y);

        int sx = (x < x2) ? 1 : -1;
        int sy = (y < y2) ? 1 : -1;

        int err = dx - dy;
        int currentX = x;
        int currentY = y;

        while (true) {
            setPixel(coordinates, currentY, currentX);
            if (currentX == x2 && currentY == y2) break;

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                currentX += sx;
            }
            if (e2 < dx) {
                err += dx;
                currentY += sy;
            }
        }

        return coordinates;
    }
};

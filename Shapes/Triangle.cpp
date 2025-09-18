#include "Shape.h"

class Triangle final : public Shape {
public:
    int height;

    Triangle(const int boardWidth, const int boardHeight, const bool fill, const std::string &color,
        const int x, const int y, const int h)
        : Shape(boardWidth, boardHeight, ShapeType::Triangle, fill, color, x, y), height(h) {}
    ~Triangle() override = default;

    bool equals(const Shape& other) const override {
        if (this->type != other.type) return this->id == other.id;
        auto& t = dynamic_cast<const Triangle&>(other);
        return Shape::equals(other) && height == t.height;
    }

    std::string info() override {
        std::string result;
        result += std::to_string(id);
        result += " triangle ";
        if (fill) result += "fill ";
        else result += "frame ";
        result += std::tolower(color[0]);
        result += color.substr(1);
        result += " x:";
        result += std::to_string(x);
        result += " y:";
        result += std::to_string(y);
        result += " h:";
        result += std::to_string(height);
        return result;
    }

    std::vector<std::pair<int, int>> getCoordinates() override {
        std::vector<std::pair<int, int>> coordinates;
        for (int i = 0; i < height; ++i) {
            int numStars = 2 * i + 1;
            int leftMost = x - i;
            int row = y + i;
            if (row >= 0 && row < boardHeight) {
                if (fill) {
                    for (int j = 0; j < numStars; ++j) {
                        if (leftMost + j >= 0 && leftMost + j < boardWidth)
                            setPixel(coordinates, row, leftMost + j);
                    }
                }
                else {
                    setPixel(coordinates, row, leftMost);
                    setPixel(coordinates, row, leftMost + numStars - 1);
                    if (i == height - 1) {
                        for (int j = 0; j < numStars; ++j) {
                            setPixel(coordinates, row, leftMost + j);
                        }
                    }
                }
            }
        }
        return coordinates;
    }
};

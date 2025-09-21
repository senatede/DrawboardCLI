#include "Shape.h"

class Circle final : public Shape {
    public:
    int radius;
    Circle(const int boardWidth, const int boardHeight, const bool fill, const std::shared_ptr<Color> &color,
        const int x, const int y, const int r)
        : Shape(boardWidth, boardHeight, ShapeType::Circle, fill, color, x, y), radius(r) {};
    ~Circle() override = default;

    bool equals(const Shape& other) const override {
        if (this->type != other.type) return this->id == other.id;
        auto& t = dynamic_cast<const Circle&>(other);
        return Shape::equals(other) && radius == t.radius;
    }

    std::string info() override {
        std::string result;
        result += "id:";
        result += std::to_string(id);
        result += " circle ";
        if (fill) result += "fill ";
        else result += "frame ";
        result += color->name;
        result += " x:";
        result += std::to_string(x);
        result += " y:";
        result += std::to_string(y);
        result += " r:";
        result += std::to_string(radius);
        return result;
    }

    std::vector<std::pair<int, int>> getCoordinates() override {
        std::vector<std::pair<int, int>> coordinates;

        if (radius <= 0) return coordinates;
        if (!fill) {
            auto bresenham = [&](const int x_, const int y_){
                setPixel(coordinates, y+y_, x+x_);
                setPixel(coordinates, y+y_, x-x_);
                setPixel(coordinates, y-y_, x+x_);
                setPixel(coordinates, y-y_, x-x_);
                setPixel(coordinates, y+x_, x+y_);
                setPixel(coordinates, y+x_, x-y_);
                setPixel(coordinates, y-x_, x+y_);
                setPixel(coordinates, y-x_, x-y_);
            };

            int x_ = 0, y_ = radius;
            int d = 3 - 2 * radius;
            bresenham(x_, y_);
            while (y_ >= x_){
                if (d > 0) {
                    y_--;
                    d = d + 4 * (x_ - y_) + 10;
                }
                else d = d + 4 * x_ + 6;
                x_++;
                bresenham(x_, y_);
            }
        } else {
            int x_ = 0;
            int y_ = radius;
            int d = 1 - radius;

            while (y_ >= x_) {
                for (int xi = -x_; xi <= x_; ++xi) {
                    setPixel(coordinates, y + y_, x + xi);
                    setPixel(coordinates, y - y_, x + xi);
                }
                for (int xi = -y_; xi <= y_; ++xi) {
                    setPixel(coordinates, y + x_, x + xi);
                    setPixel(coordinates, y - x_, x + xi);
                }

                if (d < 0) d += 2 * x_ + 3;
                else {
                    d += 2 * (x_ - y_) + 5;
                    y_--;
                }
                x_++;
            }
        }

        return coordinates;
    }
};
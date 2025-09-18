class Box final : public Shape {
public:
    int width, height;

    Box(const int boardWidth, const int boardHeight, const bool fill, std::string color,
        const int x, const int y, const int w, const int h)
        : Shape(boardWidth, boardHeight, ShapeType::Box, fill, color, x, y), width(w), height(h) {}

    ~Box() override = default;

    bool equals(const Shape& other) const override {
        if (this->type != other.type) return false;
        auto& b = dynamic_cast<const Box&>(other);
        return Shape::equals(other) && width == b.width && height == b.height;
    }

    std::string info() override {
        std::string result;
        result += std::to_string(id);
        result += " box ";
        if (fill) result += "fill ";
        else result += "frame ";
        result += std::tolower(color[0]);
        result += color.substr(1);
        result += " x:";
        result += std::to_string(x);
        result += " y:";
        result += std::to_string(y);
        result += " w:";
        result += std::to_string(width);
        result += " h:";
        result += std::to_string(height);
        return result;
    }

    std::vector<std::pair<int, int>> getCoordinates() override {
        std::vector<std::pair<int, int>> coordinates;
        for (int i = y; i < y + height; i++) {
            if (i >= 0 && i < boardHeight) {
                if (i == y || i == y + height - 1 || fill) {
                    for (int j = x; j < x + width; j++)
                        if (j >= 0 && j < boardWidth)
                            setPixel(coordinates, i, j);
                }
                else {
                    setPixel(coordinates,i, x);
                    setPixel(coordinates, i, x + width - 1);
                }
            }
        }
        return coordinates;
    }
};

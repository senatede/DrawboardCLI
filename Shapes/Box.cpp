class Box final : public Shape {
    int width, height;

public:
    Box(const int boardWidth, const int boardHeight, const bool fill, std::string color,
        const int x, const int y, const int w, const int h)
        : Shape(boardWidth, boardHeight, fill, color, x, y), width(w), height(h) {}

    ~Box() override = default;

    std::string info() override {
        std::string result;
        result += std::to_string(id);
        result += " box ";
        if (fill) result += "fill ";
        else result += "frame ";
        result += std::tolower(color[0]);
        result += color.substr(1);
        result += " ";
        result += std::to_string(x);
        result += " ";
        result += std::to_string(y);
        result += " ";
        result += std::to_string(width);
        result += " ";
        result += std::to_string(height);
        return result;
    }

    std::vector<std::pair<int, int>> getCoordinates() override {
        std::vector<std::pair<int, int>> coordinates;
        for (int i = y; i < y + height; i++) {
            if (i == y || i == y + height - 1 || fill) {
                for (int j = x; j < x + width; j++)
                    setPixel(coordinates, i, j);
            }
            else {
                setPixel(coordinates,i, x);
                setPixel(coordinates, i, x + width - 1);
            }
        }
        return coordinates;
    }
};

class Triangle final : public Shape {
    int height;

public:
    Triangle(const int boardWidth, const int boardHeight, const bool fill, const std::string &color,
        const int x, const int y, const int h)
        : Shape(boardWidth, boardHeight, fill, color, x, y), height(h) {}
    ~Triangle() override = default;

    std::string info() override {
        std::string result;
        result += std::to_string(id);
        result += " triangle ";
        if (fill) result += "fill ";
        else result += "frame ";
        result += color;
        result += " ";
        result += std::to_string(x);
        result += " ";
        result += std::to_string(y);
        result += " ";
        result += std::to_string(height);
        return result;
    }

    std::vector<std::pair<int, int>> getCoordinates() override {
        std::vector<std::pair<int, int>> coordinates;
        for (int i = 0; i < height; ++i) {
            int numStars = 2 * i + 1;
            int leftMost = x - i;
            int row = y + i;

            if (fill) {
                for (int j = 0; j < numStars; ++j) {
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
        return coordinates;
    }
};
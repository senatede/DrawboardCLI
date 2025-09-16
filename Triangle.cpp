class Triangle final : public Shape {
    int height;

    void setPixel(const int row, const int col) const {
        if (col >= 0 && col < board.width && row >= 0 && row < board.height)
            board.grid[row][col] = color[0];
    }

public:
    Triangle(Board& board, const std::string& fill, const std::string& color, int x, int y, int h)
        : Shape(board, fill, color, x, y), height(h) {}

    ~Triangle() override = default;

    void draw() override {
        for (int i = 0; i < height; ++i) {
            int numStars = 2 * i + 1;
            int leftMost = x - i;
            int row = y + i;

            if (fill == "fill") {
                for (int j = 0; j < numStars; ++j) {
                    setPixel(row, leftMost + j);
                }
            } 
            else if (fill == "frame") {
                setPixel(row, leftMost);
                setPixel(row, leftMost + numStars - 1);
                if (i == height - 1) {
                    for (int j = 0; j < numStars; ++j) {
                        setPixel(row, leftMost + j);
                    }
                }
            }
        }
    }
};
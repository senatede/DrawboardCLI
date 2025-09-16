#include <vector>


class Box final : public Shape {
    int width, height;

    void setPixel(const int row, const int col) const {
        if (col >= 0 && col < board.width && row >= 0 && row < board.height)
            board.grid[row][col] = color[0];
    }
public:
    Box(Board& board, const std::string& fill, const std::string& color, int x, int y, int w, int h)
        : Shape(board, fill, color, x, y), width(w), height(h) {}

    ~Box() override = default;

    void draw() override {
        for (int i = y; i < y + height; i++) {
                if (i == y || i == y + height - 1 || fill == "fill") {
                    for (int j = x; j < x + width; j++)
                        setPixel(i, j);
                }
                else {
                    setPixel(i, x);
                    setPixel(i, x + width - 1);
                }
            }
        }
    }
};

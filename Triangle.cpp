#include <vector>

#include "Shape.h"

class Triangle final : public Shape {
    int x, y, height;
public:
    Triangle(Board& board, int x, int y, int h)
        : Shape(board), x(x), y(y), height(h) {}

    ~Triangle() override = default;

    void draw() override {
        for (int i = 0; i < height; ++i) {
            int numStars = 2 * i + 1;
            int leftMost = x - i;
            for (int j = 0; j < numStars; ++j) {
                int position = leftMost + j;
                if (position >= 0 && position < board.width &&
                    (y + i) < board.height && (y + i) >= 0) {
                    board.grid[y + i][position] = '*';
                    }
            }
        }
    }
};

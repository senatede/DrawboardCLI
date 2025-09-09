#include "Board.h"
#include "Triangle.cpp"

int main() {
    const int BOARD_WIDTH = 80;
    const int BOARD_HEIGHT = 25;

    Board board(BOARD_WIDTH, BOARD_HEIGHT);
    auto triangle = std::make_shared<Triangle>(board, 15, 1, 15);
    board.addShape(triangle);
    board.addShape(std::make_shared<Triangle>(board, 55, 10, 5));
    board.print();
    return 0;
}
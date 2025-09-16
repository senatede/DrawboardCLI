#include <sstream>
#include <iostream>
#include <string>
#include "Board.h"

class CLI {
    int term_height;
    Board* board;
public:
    [[noreturn]] explicit CLI(int h) : term_height(h) {
        std::cout << "\033[2J\033[H";
        std::cout << "> ";
        board = nullptr;
        while (true) {
            command_handling(command_input());
        }
    }

    static std::string command_input() {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    void command_handling(const std::string& input) {
        int lines_taken = 1;
        std::string result;
        if (input == "help") {
            result = "Available commands: help, exit\n";
        } else if (input == "exit") {
            std::cout << "Exiting CLI...\n";
            exit(0);
        } else if (input.rfind("create", 0) == 0) {
            std::istringstream iss(input);
            std::string cmd;
            int w, h;
            iss >> cmd >> w >> h;
            if (iss && !iss.fail()) {
                delete board;
                board = new Board(w, h);
                result = "Created board " + std::to_string(w) + "x" + std::to_string(h) + "\n";
            } else {
                result = "Error: use create <width> <height>\n";
            }
        } else if (input == "clear") {
            if (board == nullptr) {
                result = "Error: board doesn't exits.\n";
            } else {
                board->clear();
            }
        } else if (input == "draw") {
            if (board == nullptr) {
                result = "Error: board doesn't exits.\n";
            } else {
                lines_taken = board->height;
                board->print();
            }
        } else if (input.rfind("add", 0) == 0) {
            std::istringstream iss(input);
            std::string cmd, shape, fill, color;
            int x, y;

            iss >> cmd >> shape >> fill >> color >> x >> y;
            if (board == nullptr) result = "Error: board doesn't exits.\n";
            else if (iss.fail()) result = "Error: use add <shape: triangle|box> <fill|frame> <color: red|green|blue|white|yellow> <x> <y> [extra parameters]\n";
            else if (shape != "triangle" && shape != "box") result = "Error: unknown shape " + shape + "\n";
            else if (fill != "fill" && fill != "frame") result = "Error: unknown fill " + fill + "\n";
            else if (color != "red" && color != "green" && color != "blue" && color != "white" && color != "yellow") result = "Error: unknown color " + color + "\n";
            else {
                color[0] = std::toupper(color[0]);

                std::vector<int> extraParameters;
                int value;
                while (iss >> value) {
                    extraParameters.push_back(value);
                }

                if (shape == "triangle") {
                    if (extraParameters.size() == 1) {
                        board->addTriangle(fill, color, x, y, extraParameters[0]);
                        lines_taken = board->height;
                        board->print();
                    }
                    else result = "Error: incorrect number of parameters\n";
                }
                else if (shape == "box") {
                    if (extraParameters.size() == 2) {
                        board->addBox(fill, color, x, y, extraParameters[0], extraParameters[1]);
                        lines_taken = board->height;
                        board->print();
                    }
                    else result = "Error: incorrect number of parameters\n";
                }
            }
        } else
        {
            result = "Unknown command: " + input + "\n";
        }
        if (!result.empty()) {
            std::cout << "\033[2J\033[H";
            std::cout << result << std::endl;
        }
        for (int i = lines_taken; i < term_height - 1; ++i)
            std::cout << std::endl;
        std::cout << "> ";
    }

};

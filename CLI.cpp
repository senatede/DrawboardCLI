#include "CLI.h"

CLI::CLI(const int h) : term_height(h) {
    std::cout << "\033[2J\033[H";
    std::cout << "> ";
    board = nullptr;
    while (true) {
        command_handling(command_input());
    }
}

std::string CLI::command_input() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void CLI::command_handling(const std::string& input) {
    std::string result;
    if (input == "help") help();
    else if (input == "exit") exit_();
    else if (input.starts_with("create")) create(input);
    else if (input == "clear") clear();
    else if (input == "draw") draw();
    else if (input.starts_with("add")) add(input);
    else if (input == "list") list();
    else if (input == "shapes") shapes();
    else unknown(input);

}

void CLI::help() const {
    std::cout << "\033[2J\033[H";

    std::cout << "Available commands:" << std::endl;
    std::cout << " - help" << std::endl;
    std::cout << " - exit" << std::endl;
    std::cout << " - create <width> <height> - create board" << std::endl;
    std::cout << " - draw - draw board" << std::endl;
    std::cout << " - add <shape: triangle|box> <fill|frame> <color: red|green|blue> <x> <y> [extra parameters]" << std::endl;

    for (int i = 6; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

void CLI::exit_() {
    std::cout << "Exiting CLI..." << std::endl;
    exit(0);
}

void CLI::create(const std::string& input) {
    std::cout << "\033[2J\033[H";

    std::istringstream iss(input);
    std::string cmd;
    int w, h;
    iss >> cmd >> w >> h;
    if (iss && !iss.fail()) {
        delete board;
        board = new Board(w, h);
        std::cout << "Created board " + std::to_string(w) + "x" + std::to_string(h) << std::endl;
    } else {
        std::cout << "Error: use create <width> <height>" << std::endl;
    }

    for (int i = 1; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

void CLI::clear() const {
    std::cout << "\033[2J\033[H";

    if (board == nullptr) std::cout << "Error: board doesn't exist." << std::endl;
    else board->clear();

    for (int i = board == nullptr; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

void CLI::draw() const {
    int lines_taken = 1;
    std::cout << "\033[2J\033[H";

    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl;
    } else {
        lines_taken = board->height;
        board->print();
    }
    for (int i = lines_taken; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

void CLI::add(const std::string& input) const {
    int lines_taken = 1;
    std::cout << "\033[2J\033[H";

    std::istringstream iss(input);
    std::string cmd, shape, fill_word, color;
    int x, y;


    iss >> cmd >> shape >> fill_word >> color >> x >> y;
    if (board == nullptr) std::cout << "Error: board doesn't exist." << std::endl;
    else if (iss.fail()) std::cout << "Error: use add <shape: triangle|box> <fill|frame> <color: red|green|blue|white|yellow> <x> <y> [extra parameters]" << std::endl;
    else if (shape != "triangle" && shape != "box") std::cout << "Error: unknown shape " + shape << std::endl;
    else if (fill_word != "fill" && fill_word != "frame") std::cout << "Error: unknown fill " + fill_word << std::endl;
    else if (color != "red" && color != "green" && color != "blue") std::cout << "Error: unknown color " + color << std::endl;
    else {
        color[0] = static_cast<char>(std::toupper(color[0]));
        int fill = (fill_word == "fill");

        std::vector<int> extraParameters;
        int value;
        while (iss >> value) {
            extraParameters.push_back(value);
        }

        auto tryAddShape = [&](const int size, auto addFunc) {
            if (extraParameters.size() != size) {
                std::cout << "Error: incorrect number of parameters" << std::endl;
                return;
            }
            if (addFunc()) {
                std::cout << "Error: shape doesn't fit on the board" << std::endl;
            } else {
                lines_taken = board->height;
                board->print();
            }
        };

        if (shape == "triangle") {
            tryAddShape(1, [&] {
                return board->addTriangle(fill, color, x, y, extraParameters[0]);
            });
        }
        else if (shape == "box") {
            tryAddShape(2, [&] {
                return board->addBox(fill, color, x, y, extraParameters[0], extraParameters[1]);
            });
        }
    }
    for (int i = lines_taken; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

void CLI::unknown(const std::string& input) const {
    std::cout << "\033[2J\033[H";

    std::cout << "Unknown command: " << input << std::endl;
    std::cout << "Use >help for clarification" << std::endl;

    for (int i = 2; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

void CLI::list() const {
    std::cout << "\033[2J\033[H";
    size_t lines_taken = 1;

    if (board == nullptr) std::cout << "Error: board doesn't exist." << std::endl;
    else {
        std::cout << "All figures on board:" << std::endl;
        auto shapes = board->listShapes();
        for (const auto& shape : shapes) {
            std::cout << "  id:" << shape << std::endl;
        }
        lines_taken = shapes.size();
    }
    for (auto i = lines_taken; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

void CLI::shapes() const {
    std::cout << "\033[2J\033[H";

    std::cout << "Available shapes:" << std::endl;
    std::cout << "  triangle <fill|frame> <color: red|green|blue> <x> <y> <height>"<<  std::endl;
    std::cout << "  box <fill|frame> <color: red|green|blue> <x> <y> <width> <height>"<<  std::endl;
    for (auto i = 3; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}
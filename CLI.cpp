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
    std::cout << "\033[2J\033[H";
    int n = 0;

    if (input == "help") n = help();
    else if (input == "exit") n = exit_();
    else if (input.starts_with("create")) n = create(input);
    else if (input == "clear") n = clear();
    else if (input == "draw") n = draw();
    else if (input.starts_with("add")) n = add(input);
    else if (input == "list") n = list();
    else if (input.starts_with("select")) n = select(input);
    else if (input == "shapes") n = shapes();
    else if (input == "remove") n = remove();
    else if (input.starts_with("paint")) n = paint(input);
    else if (input.starts_with("edit")) n = edit(input);
    else if (input.starts_with("move")) n = move(input);
    else n = unknown(input);

    for (int i = n; i < term_height - 1; ++i)
        std::cout << std::endl;
    std::cout << "> ";
}

int CLI::help() {
    std::cout << "Available commands:" << std::endl;
    std::cout << " - help" << std::endl;
    std::cout << " - exit" << std::endl;
    std::cout << " - create <width> <height> - create board" << std::endl;
    std::cout << " - draw - draw board" << std::endl;
    std::cout << " - add <shape: triangle|box> <fill|frame> <color: red|green|blue> <x> <y> [extra parameters]" << std::endl;
    return 6;
}

int CLI::exit_() {
    std::cout << "Exiting CLI..." << std::endl;
    exit(0);
}

int CLI::create(const std::string& input) {
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
    return 1;
}

int CLI::clear() const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl;
        return 1;
    }
    board->clear();
    return 0;
}

int CLI::draw() const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl;
        return 1;
    }
    board->print();
    return board->height;
}

int CLI::add(const std::string& input) const {
    std::istringstream iss(input);
    std::string cmd, shape, fill_word, color;
    int x, y;

    iss >> cmd >> shape >> fill_word >> color >> x >> y;
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl; return 1;
    }
    if (iss.fail()) {
        std::cout << "Error: use add <shape: triangle|box> <fill|frame> <color: red|green|blue|white|yellow> <x> <y> [extra parameters]" << std::endl; return 1;
    }
    if (shape != "triangle" && shape != "box") {
        std::cout << "Error: unknown shape " + shape << std::endl; return 1;
    }
    if (fill_word != "fill" && fill_word != "frame") {
        std::cout << "Error: unknown fill " + fill_word << std::endl; return 1;
    }
    if (color != "red" && color != "green" && color != "blue") {
        std::cout << "Error: unknown color " + color << std::endl; return 1;
    }
    color[0] = static_cast<char>(std::toupper(color[0]));
    int fill = (fill_word == "fill");

    std::vector<int> parameters;
    int value;
    while (iss >> value) parameters.push_back(value);

    auto tryAddShape = [&](const int size, auto addFunc) {
        if (parameters.size() != size) {
            std::cout << "Error: incorrect number of parameters" << std::endl;
            return 1;
        }
        switch (addFunc()) {
            case 1:
                std::cout << "Error: shape won't be visible." << std::endl; return 1;
            case 2:
                std::cout << "Error: shape will cover all screen." << std::endl; return 1;
            case 3:
                std::cout << "Error: shape will be a duplicate." << std::endl; return 1;
            default:
                board->print(); return board->height;
        }
    };

    if (shape == "triangle") {
        return tryAddShape(1, [&] {
            return board->addTriangle(fill, color, x, y, parameters[0]);
        });
    }
    if (shape == "box") {
        return tryAddShape(2, [&] {
            return board->addBox(fill, color, x, y, parameters[0], parameters[1]);
        });
    }
    return 0;
}

int CLI::unknown(const std::string& input) {
    std::cout << "Unknown command: " << input << std::endl;
    std::cout << "Use >help for clarification" << std::endl;
    return 2;
}

int CLI::list() const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl;
        return 1;
    }
    const auto shapes = board->listShapes();
    if (shapes.empty()) {
        std::cout << "No figures on board" << std::endl;
        return 1;
    }
    std::cout << "All figures on board:" << std::endl;
    for (const auto& shape : shapes) {
        std::cout << "  id:" << shape << std::endl;
    }
    return shapes.size();
}

int CLI::shapes() {
    std::cout << "Available shapes:" << std::endl;
    std::cout << "  triangle <fill|frame> <color: red|green|blue> <x> <y> <height>"<<  std::endl;
    std::cout << "  box <fill|frame> <color: red|green|blue> <x> <y> <width> <height>"<<  std::endl;
    return 3;
}

int CLI::select(const std::string &input) const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl; return 1;
    }
    std::istringstream iss(input);
    std::string cmd;
    iss >> cmd;
    std::vector<int> parameters;
    int value;
    while (iss >> value) parameters.push_back(value);
    switch (parameters.size()) {
        case 1:
            if (board->selectShape(parameters[0])) std::cout << "Error: shape with such id does not exist." << std::endl; break;
        case 2:
            if (board->selectShape(parameters[0], parameters[1])) std::cout << "Error: shape with such id does not exist." << std::endl; break;
        default:
            std::cout << "Error: wrong parameters" << std::endl;
    }
    return 1;
}

int CLI::remove() const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl; return 1;
    }
    if (board->removeShape()) {
        std::cout << "Error: select a shape first." << std::endl; return 1;
    }
    return draw();
}

int CLI::paint(const std::string& input) const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl; return -1;
    }
    std::istringstream iss(input);
    std::string cmd, color;
    iss >> cmd >> color;
    if (color != "red" && color != "green" && color != "blue") {
        std::cout << "Error: unknown color - " << color << std::endl; return 1;
    }
    color[0] = static_cast<char>(std::toupper(color[0]));
    if (board->paintShape(color)) {
        std::cout << "Error: select a shape first." << std::endl; return 1;
    }
    return draw();
}

int CLI::edit(const std::string& input) const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl; return 1;
    }
    std::istringstream iss(input);
    std::string cmd;
    iss >> cmd;
    std::vector<int> parameters;
    int value;
    while (iss >> value) parameters.push_back(value);
    switch (board->editShape(parameters)) {
        case -1:
            std::cout << "Error: select a shape first." << std::endl; return 1;
        case -2:
            std::cout << "Error: invalid argument count." << std::endl; return 1;
        case 1:
            std::cout << "Error: shape won't be visible." << std::endl; return 1;
        case 2:
            std::cout << "Error: shape will cover all screen" << std::endl; return 1;
        case 3:
            std::cout << "Error: shape will be a duplicate." << std::endl; return 1;
        default:
            return draw();
    }
}

int CLI::move(const std::string& input) const {
    if (board == nullptr) {
        std::cout << "Error: board doesn't exist." << std::endl; return 1;
    }
    std::istringstream iss(input);
    std::string cmd;
    iss >> cmd;
    std::vector<int> parameters;
    int value;
    while (iss >> value) parameters.push_back(value);
    switch (board->moveShape(parameters)) {
        case -1:
            std::cout << "Error: select a shape first." << std::endl; return 1;
        case -2:
            std::cout << "Error: invalid argument count." << std::endl; return 1;
        case 1:
            std::cout << "Error: shape won't be visible." << std::endl; return 1;
        case 2:
            std::cout << "Error: shape will cover all screen" << std::endl; return 1;
        case 3:
            std::cout << "Error: shape will be a duplicate." << std::endl; return 1;
        default:
            return draw();
    }
}
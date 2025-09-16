#ifndef CLI_H
#define CLI_H

#include <sstream>
#include <iostream>
#include <string>
#include "Board.h"

class CLI {
    int term_height;
    Board* board;

    static std::string command_input();
    void command_handling(const std::string& input);
    void help() const;
    static void exit_() ;
    void create(const std::string& input);
    void clear() const;
    void draw() const;
    void list() const;
    void shapes() const;
    void add(const std::string& input) const;
    void unknown(const std::string& input) const;

public:
    [[noreturn]] explicit CLI(int h);
};

#endif //CLI_H

//#define DEBUG

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#ifndef PROJETO_AB1_TOKENIZER_H
#define PROJETO_AB1_TOKENIZER_H

#include <iostream>
#include <fstream>
#include <regex>

#include "Category.hpp"

typedef struct Token {
    Category categ;
    std::string lex;
    int line, col;
}Token;

class Tokenizer {

private:
    Token tk{};

    std::ifstream source;
    std::string buffer;
    const std::vector<std::string> RegExList = {
            "\\(", "\\)",
            "\\+", "-", "\\*", "/", "%", "\\*\\*",
            "\\=",
            "-?([0-9]+)", "-?([0-9]+)\\.([0-9]+)"
    };
    std::regex re;

    int current_position;

    int nextLine();
    int nextLex();
    int findRegex();

public:
    explicit Tokenizer(std::string expression);
    Token nextToken();
    bool empty();
};


#endif //PROJETO_AB1_TOKENIZER_H

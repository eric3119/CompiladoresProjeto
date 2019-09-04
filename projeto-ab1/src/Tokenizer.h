#ifndef PROJETO_AB1_TOKENIZER_H
#define PROJETO_AB1_TOKENIZER_H

#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

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
            "init", "int", "float", "char", "string", "bool",
            ";", ":", ",", "\\(", "\\)", "\\[", "\\]", "\\{", "\\}",
            "proc", "return", "break",
            "input", "print",
            "for", "in", "step", "while", "if", "else if", "else",
            "==", ">", "<", ">=", "<=", "!=", "and", "or", "!",
            "\\+", "-", "\\*", "/", "%",
            "\\=", "\\+\\+",
            "[_a-zA-Z][_a-zA-Z0-9]*", "const", "-?([0-9]+)", "-?([0-9]+)\\.([0-9]+)", "\'.\'", "true|false", "\"(.*)\""
    };
    std::regex re;

    int current_position;

    int nextLine();
    int nextLex();
    int findRegex();

public:
    explicit Tokenizer(const std::string& filename);
    Token nextToken();
    bool empty();
};


#endif //PROJETO_AB1_TOKENIZER_H


#ifndef PROJETO_AB1_TOKENIZER_H
#define PROJETO_AB1_TOKENIZER_H

#include <iostream>
#include <fstream>
#include <regex>

#include "Category.hpp"

const int MAX_STRING = 100;

typedef struct Token {
    Category categ;
    char lex[MAX_STRING];
    int line, col;
}Token;

class Tokenizer {

private:
    Token tk{};
    std::ifstream source;
    std::string buffer;

    void readLine();

public:
    explicit Tokenizer(const std::string& filename);
    Token nextToken();
    bool empty();
};


#endif //PROJETO_AB1_TOKENIZER_H


#ifndef PROJETO_AB1_TOKENIZER_H
#define PROJETO_AB1_TOKENIZER_H

#include <iostream>
#include "CategoryEnum.hpp"
#include <regex>

const int MAX_STRING = 100;

typedef struct Token {
    CategoryEnum categ;
    char lex[MAX_STRING];
    int line, col;
}Token;

class Tokenizer {

private:
    Token tk;
    FILE *source;
    char buffer[MAX_STRING];

    char* readLine();

public:
    explicit Tokenizer(FILE *c_source);
    Token nextToken();
};


#endif //PROJETO_AB1_TOKENIZER_H

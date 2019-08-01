
#ifndef PROJETO_AB1_TOKENIZER_H
#define PROJETO_AB1_TOKENIZER_H

#include <iostream>
#include <fstream>
#include <regex>

#include "Category.hpp"

const std::string RegExList =   "(int)|"
                                "(init)|"
                                "([(])|"
                                "([)])|"
                                "([{])|"
                                "([}])|"
                                "(input)|"
                                "(print)|"
                                "(return)|"
                                "(\"(.)\")|"
                                "(;)|"
                                "([0-9])";

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

    std::regex re;
    std::sregex_iterator current;

    void readLine();
    bool nextLex();

public:
    explicit Tokenizer(const std::string& filename);
    Token nextToken();
    bool empty();
};


#endif //PROJETO_AB1_TOKENIZER_H


#ifndef PROJETO_AB1_TOKENIZER_H
#define PROJETO_AB1_TOKENIZER_H

#include <iostream>
#include <fstream>
#include <regex>

#include "Category.hpp"

const std::string RegExList =   "(init)|"
                                "(;)|"
                                "(:)|"
                                "(,)|"
                                "(int)|"
                                "(float)|"
                                "(char)|"
                                "(string)|"
                                "(bool)|"
                                "(proc)|"
                                "(return)|"
                                "(break)|"
                                "([(])|"
                                "([)])|"
                                "([)|"
                                "(])|"
                                "([{])|"
                                "([}])|"
                                "(input)|"
                                "(print)|"
                                "(for)|"
                                "(while)|"
                                "(if)|"
                                "(else if)|"
                                "(else)|"
                                "([==])|"
                                "([>])|"
                                "([<])|"
                                "([>=])|"
                                "([<=])|"
                                "([!=])|"
                                "([+])|"
                                "([-])|"
                                "([*])|"
                                "([/])|"
                                "([%])|"
                                "([=])|"
                                "([++])|"
                                "([_a-zA-Z][_a-zA-Z0-9]*)|"
                                "(-?([0-9]+))|"
                                "(-?([0-9]+)\\.([0-9]+))|"
                                "(\'.\')|"
                                "(true|false)|"
                                "(\"(.*)\")|"
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
    void nextLex();

    void init_map();
    std::map<std::string, Category> map_lex_categ;

public:
    explicit Tokenizer(const std::string& filename);
    Token nextToken();
    bool empty();
};


#endif //PROJETO_AB1_TOKENIZER_H

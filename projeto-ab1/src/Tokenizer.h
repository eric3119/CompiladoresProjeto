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

//const std::string RegExList =   "(init)|"
//                                "(;)|"
//                                "(:)|"
//                                "(,)|"
//                                "(int)|"
//                                "(float)|"
//                                "(char)|"
//                                "(string)|"
//                                "(bool)|"
//                                "(proc)|"
//                                "(return)|"
//                                "(break)|"
//                                "([(])|"
//                                "([)])|"
//                                "([)|"
//                                "(])|"
//                                "([{])|"
//                                "([}])|"
//                                "(input)|"
//                                "(print)|"
//                                "(for)|"
//                                "(while)|"
//                                "(if)|"
//                                "(else if)|"
//                                "(else)|"
//                                "([==])|"
//                                "([>])|"
//                                "([<])|"
//                                "([>=])|"
//                                "([<=])|"
//                                "([!=])|"
//                                "([+])|"
//                                "([-])|"
//                                "([*])|"
//                                "([/])|"
//                                "([%])|"
//                                "([=])|"
//                                "([++])|"
//                                "([_a-zA-Z][_a-zA-Z0-9]*)|"
//                                "(-?([0-9]+))|"
//                                "(-?([0-9]+)\\.([0-9]+))|"
//                                "(\'.\')|"
//                                "(true|false)|"
//                                "(\"(.*)\")|"
//                                "(;)|"
//                                "([0-9])";
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
            "for", "while", "if", "else if", "else",
            "==", ">", "<", ">=", "<=", "!=",
            "\\+", "-", "\\*", "/", "%",
            "\\=", "\\+\\+",
            "[_a-zA-Z][_a-zA-Z0-9]*", "-?([0-9]+)", "-?([0-9]+)\\.([0-9]+)", "\'.\'", "true|false", "\"(.*)\"",
    };
    std::regex re;
    std::sregex_iterator current;

    int current_position;

    void nextLine();
    int nextLex();

    void init_map();
    std::map<std::string, Category> map_lex_categ;

public:
    explicit Tokenizer(const std::string& filename);
    Token nextToken();
    bool empty();

    int findRegex();
};


#endif //PROJETO_AB1_TOKENIZER_H

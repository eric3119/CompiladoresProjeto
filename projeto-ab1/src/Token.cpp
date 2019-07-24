#include "Category.hpp"

#define MAX_STRING 100

struct Token {
    Category categ;
    char lex[MAX_STRING];
    int line, col;
};
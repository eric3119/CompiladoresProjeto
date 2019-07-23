#define MAX_STRING 100

struct Token {
    Categoria categ;
    char lexema[MAX_STRING];
    int linha, coluna;    
};
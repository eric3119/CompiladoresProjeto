#include <iostream>
#include "src/Tokenizer.h"

using namespace std;

int main(int argc, const char **argv){

    Tokenizer *tokenizer;

    if (argc != 2){

        cout << "use: main prog.lang" << endl;

        exit(0);
    }

    string s(argv[1]);

    tokenizer = new Tokenizer(s);
    Token teste = tokenizer->nextToken();

    do{
        printf("          [%04d, %04d] (%04d, %20s) {%s}\n", teste.line, teste.col, teste.categ, categ_name(teste.categ), teste.lex);
    }while(!tokenizer->empty());

    return 0;
}
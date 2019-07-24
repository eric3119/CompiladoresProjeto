#include <iostream>
#include "src/Tokenizer.h"

using namespace std;

int main(int argc, const char **argv){

    FILE *source;
    Tokenizer *tokenizer;

    if (argc != 2){

        cout << "use: main prog.lang" << endl;

        exit(0);
    }

    source = fopen(argv[1],"r");

    if (!source){
        cout << "file not found" << endl;
        exit(0);
    }

    tokenizer = new Tokenizer(source);

    while(!tokenizer->empty()){
        Token teste = tokenizer->nextToken();

        printf("          [%04d, %04d] (%04d, %20s) {%s}", teste.line, teste.col, teste.categ, categ_name(teste.categ), teste.lex);
    }

    fclose(source);

    return 0;
}
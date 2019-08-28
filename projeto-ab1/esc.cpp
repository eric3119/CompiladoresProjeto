#include <iostream>
#include "src/Tokenizer.h"

using namespace std;

int main(int argc, const char **argv){

    Tokenizer *tokenizer;

    if (argc != 2){

        cout << "use: esc prog.esc" << endl;

        exit(0);
    }

    string s(argv[1]);

    ifstream fileTest(s);
    if (!fileTest.is_open()){
        cout << "File not found" << endl;
        exit(0);
    }
    fileTest.close();

    tokenizer = new Tokenizer(s);
    Token teste;

    do{
        teste = tokenizer->nextToken();
        printf("          [%04d, %04d] (%04d, %20s) ", teste.line, teste.col, teste.categ, categ_name(teste.categ));
        cout << "{"+teste.lex+"}" << endl;
    }while(!tokenizer->empty());

    return 0;
}
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

    fclose(source);

    return 0;
}
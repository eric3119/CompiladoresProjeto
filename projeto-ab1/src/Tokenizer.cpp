#include "Tokenizer.h"

Tokenizer::Tokenizer(FILE *c_source) : tk() {
    source = c_source;
    tk = {};
}

Token Tokenizer::nextToken(){

    if (!feof(source)){
        readLine();//TODO return

        //TODO regex

    }else{
        tk.categ = CategoryEnum ::Eof;
        tk.lex[0] = '\0';
    }

    return tk;
}

char* Tokenizer::readLine(){
    return fgets(buffer,MAX_STRING,source);
}
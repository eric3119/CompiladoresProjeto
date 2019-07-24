#include "Tokenizer.h"

Tokenizer::Tokenizer(FILE *c_source) : tk() {
    source = c_source;
    tk = {};
    buffer[0] = '\0';
}

Token Tokenizer::nextToken(){

    if (!feof(source)){
        readLine();//TODO return

        //TODO regex

    }else{
        tk.categ = Category ::Eof;
        tk.lex[0] = '\0';
    }

    return tk;
}

bool Tokenizer::empty(){
    return tk.categ == Category ::Eof;
}

char* Tokenizer::readLine(){
    return fgets(buffer,MAX_STRING,source);
}
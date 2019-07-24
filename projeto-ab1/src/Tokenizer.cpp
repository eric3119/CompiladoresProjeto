#include "Tokenizer.h"

Tokenizer::Tokenizer(FILE *c_source) : tk() {
    source = c_source;
    tk = {};
}

Token Tokenizer::nextToken(){
    return tk;
}

void Tokenizer::readLine(){

}

// uma linha de cada vez
//Erros léxicos devem ser enviados para o analisador sintático
//
#include "Tokenizer.h"
#include "Category.hpp"

Tokenizer::Tokenizer(const std::string& filename) : source(filename) {
    tk = {};
    buffer[0] = '\0';
    re.assign(RegExList);
}

Token Tokenizer::nextToken(){

    if(source.eof()){
        tk.categ = Category ::Eof;
        tk.lex = "\0";
    }else{
        nextLex();
    }

    return tk;
}

bool Tokenizer::empty(){
    return tk.categ == Category ::Eof;
}

void Tokenizer::readLine(){
    std::getline(source, buffer);
}

void Tokenizer::nextLex(){

    std::sregex_iterator end;

    if(current != end){
        std::smatch match = *current;
        tk.lex = match.str();
        current++;
        tk.col = match.position(0);
        tk.categ = Category ::Integer;//name_categ(tk.lex);
    }else{
        readLine();
        tk.line++;

        printf("%4d  ", tk.line);
        std::cout << buffer << std::endl;

        current = std::sregex_iterator(buffer.begin(), buffer.end(), re);
        nextLex();
    }
}
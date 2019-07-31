#include "Tokenizer.h"

Tokenizer::Tokenizer(const std::string& filename) : source(filename) {
    tk = {};
    buffer[0] = '\0';
    re.assign(RegExList);
}

Token Tokenizer::nextToken(){

    if(source.eof()){
        tk.categ = Category ::Eof;
        tk.lex = "\0";
        std::cout << buffer << std::endl;
    }else{
        if (nextLex()){
            tk.categ = Category ::AbPar;
        }else{
            readLine();
        }

    }

    return tk;
}

bool Tokenizer::empty(){
    return tk.categ == Category ::Eof;
}

void Tokenizer::readLine(){
    std::getline(source, buffer);
}

bool Tokenizer::nextLex(){

    try {
        // std::regex re("(int)|(init)|(\\()|(\\))");
        //std::sregex_iterator next(buffer.begin(), buffer.end(), re);
        std::sregex_iterator end;
        if (current != end){
            std::smatch match = *current;
            std::cout << match.str() << "\n";
            tk.lex = match.str();
            current++;
            return true;
        }else{
            return false;
        }
//        while (next != end) {
//            std::smatch match = *next;
//            std::cout << match.str() << "\n";
//            next++;
//        }
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
        return false;
    }
}
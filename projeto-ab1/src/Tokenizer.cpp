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
        std::cout << buffer << std::endl;
    }else{
        if (nextLex()){
            tk.line = -1;
            tk.col = -1;
            tk.categ = Category ::Integer;//name_categ(tk.lex);
        }else{
            tk.categ = (Category)0;//erro
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

    std::sregex_iterator end;

    if(current != end){
        std::smatch match = *current;
        tk.lex = match.str();
        current++;
        return true;
    }else{
        readLine();
        buffer.erase(std::remove_if(buffer.begin(), buffer.end(), ::isspace), buffer.end());
        current = std::sregex_iterator(buffer.begin(), buffer.end(), re);
        return false;
    }
}

//void regteste2(){
//    string str = "The ape was at the apex";
//    regex reg("(ape[^ ]?)");
//
//    sregex_iterator currentMatch(str.begin(), str.end(), reg);
//    sregex_iterator lastMatch;
//
//    while (currentMatch!= lastMatch){
//        smatch match = *currentMatch;
//        cout << match.str() << endl;
//        currentMatch++;
//    }cout << endl;
//
//}
//
//void regteste(){
//    string str = "The ape was at the apex";
//    smatch matches;
//    regex reg("(ape[^ ]?)");
//
//    while (regex_search(str, matches, reg)){
//        cout << "Match: " << matches.ready() << endl;
//        cout << "No match: " << matches.empty() << endl;
//        cout << "# matches: " << matches.size() << endl;
//        cout << "match: " << matches.str(1) << endl << endl;
//        str = matches.suffix().str();
//    }
//
//    regteste2();
//
//}

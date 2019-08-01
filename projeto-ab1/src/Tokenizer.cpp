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
        std::sregex_iterator end;
        while(current != end){
            std::smatch match = *current;
            std::cout << "saida" << match.str() << std::endl;

            tk.lex = match.str();
            current++;
        }
        if (current != end){
            std::smatch match = *current;
            std::cout << "saida >> " << match.str() << "\n";
            tk.lex = match.str();
            current++;
            return true;
        }else{
            std::sregex_iterator new_regex(buffer.begin(), buffer.end(), re);
            current = new_regex;
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

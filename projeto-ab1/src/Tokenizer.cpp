#include "Tokenizer.h"
#include "Category.hpp"

#define REGEX_NOT_FOUND 0
#define REGEX_FOUND 1
#define END_OF_STRING 2
#define END_OF_FILE 3
#define ERRO_ANALIZE 4

Tokenizer::Tokenizer(const std::string& filename) : source(filename) {
    tk = {};
    tk.col = 0;
    current_position = -1;
    buffer.clear();
    init_map();
}

Token Tokenizer::nextToken(){

    if(current_position == -1)current_position++;
    int result = nextLex();

    if(result != REGEX_FOUND){
        if(result == END_OF_FILE){
            tk.categ = Category ::Eof;
            tk.lex.clear();
        }else{
            tk.categ = (Category)0;
        }
    }

    return tk;
}

bool Tokenizer::empty(){
    return tk.categ == Category ::Eof;
}

int Tokenizer::nextLine(){
    if(source.eof())return EOF;
    std::getline(source, buffer);
    tk.line++;
    tk.col = 0;
    current_position = -1;

    printf("%4d  ", tk.line);
    std::cout << buffer << std::endl;
    return 1;
}

int Tokenizer::nextLex(){
    int result = findRegex();

    switch (result){
        case REGEX_FOUND: return REGEX_FOUND;

        case REGEX_NOT_FOUND: return REGEX_NOT_FOUND;

        case END_OF_STRING:
            if(nextLine() == EOF) return END_OF_FILE;
            current_position++;
            return nextLex();

        default: return ERRO_ANALIZE;
    }
}

void Tokenizer::init_map() {
    map_lex_categ["init"] = Category::Init;
    map_lex_categ[";"] = Category::PtVg;
    map_lex_categ[":"] = Category::Pt2;
    map_lex_categ[","] = Category::Vg;
    map_lex_categ["int"] = Category::Integer;
    map_lex_categ["float"] = Category::Float;
    map_lex_categ["char"] = Category::Char;
    map_lex_categ["string"] = Category::String;
    map_lex_categ["bool"] = Category::Boolean;
    map_lex_categ["proc"] = Category::Procedure;
    map_lex_categ["return"] = Category::Return;
    map_lex_categ["break"] = Category::Break;
    map_lex_categ["("] = Category::AbPar;
    map_lex_categ[")"] = Category::FePar;
    map_lex_categ["["] = Category::AbCol;
    map_lex_categ["]"] = Category::FeCol;
    map_lex_categ["{"] = Category::AbChav;
    map_lex_categ["}"] = Category::FeChav;
    map_lex_categ["input"] = Category::Input;
    map_lex_categ["print"] = Category::Print;
    map_lex_categ["for"] = Category::For;
    map_lex_categ["while"] = Category::While;
    map_lex_categ["if"] = Category::If;
    map_lex_categ["else if"] = Category::ElseIf;
    map_lex_categ["else"] = Category::Else;
    map_lex_categ["=="] = Category::OpEq;
    map_lex_categ[">"] = Category::OpMaior;
    map_lex_categ["<"] = Category::OpMenor;
    map_lex_categ[">="] = Category::OpMaiorEq;
    map_lex_categ["<="] = Category::OpMenorEq;
    map_lex_categ["!="] = Category::OpDifer;
    map_lex_categ["+"] = Category::OpMais;
    map_lex_categ["-"] = Category::OpMenos;
    map_lex_categ["*"] = Category::OpMult;
    map_lex_categ["/"] = Category::OpDiv;
    map_lex_categ["%"] = Category::OpMod;
    map_lex_categ["="] = Category::OpAtr;
    map_lex_categ["++"] = Category::OpConcat;
    map_lex_categ["id"] = Category::Id;
    map_lex_categ["ctei"] = Category::CteInt;
    map_lex_categ["ctef"] = Category::CteFloat;
    map_lex_categ["ctec"] = Category::CteChar;
    map_lex_categ["cteb"] = Category::CteBool;
    map_lex_categ["ctes"] = Category::CteStr;
}

bool is_delim(char a){
    if( a == ' '||
        a == ';'||
        a == ':'||
        a == ','||
        a == '('||
        a == ')'||
        a == '['||
        a == ']'||
        a == '{'||
        a == '}')
        return true;

    return a == '<' ||
           a == '>' ||
           a == '+' ||
           a == '-' ||
           a == '*' ||
           a == '/' ||
           a == '%' ||
           a == '=' ||
           a == '"' ||
           a == '\''
           ;
}

bool is_compound(char a){
    return a == '=' || a == '+';
}

int Tokenizer::findRegex(){

    std::smatch m;
    std::regex e;

    std::string temp;

    int str_len = buffer.length();

    if (current_position < str_len) {

        while(current_position < str_len && buffer[current_position] == ' ')current_position++;
        tk.col = current_position;

        if (current_position >= str_len) return END_OF_STRING;

        if(is_delim(buffer[current_position])){

            temp += buffer[current_position];

            if(current_position+1 < str_len && is_compound(buffer[current_position+1])){// teste operadores compostos
                current_position++;
                temp+=buffer[current_position];
            }else if(temp == "\"" || temp == "'"){// teste string ou char
                char delim_temp = temp[0];
                current_position++;

                while(current_position < str_len){
                    temp+=buffer[current_position];

                    if (buffer[current_position] == delim_temp) break;

                    current_position++;
                }
            }

            D(std::cout << "found delim" + buffer.substr(current_position, 1) +"\n" << "temp buffer is: "+temp +"\n";)

            current_position++;
            for (int i = 0; i < 44; ++i) {
                e.assign(RegExList[i]);
                if(std::regex_match(temp, m, e)){
                    D(std::cout << temp + " match_RegEx_name " << categ_name((Category)(i+1)) << " pos " << i+1 << std::endl;)
                    tk.lex = temp;
                    tk.categ = (Category)(i+1);
                    return REGEX_FOUND;
                }
                if(i == 43){
                    tk.lex = temp;
                    return REGEX_NOT_FOUND;
                }
            }
            temp.clear();
            D(puts("");)
        }

        while (current_position < str_len && !is_delim(buffer[current_position])){
            temp += buffer[current_position];
            current_position++;
        }

        D(std::cout << "found delim" + buffer.substr(current_position, 1) +"\n" << "temp buffer is: "+temp +"\n";)
        for (int i = 0; i < 44; ++i) {
            e.assign(RegExList[i]);
            if(std::regex_match(temp, m, e)){
                D(std::cout << temp + " match_RegEx_name " << categ_name((Category)(i+1)) << " pos " << i+1 << std::endl;)
                tk.lex = temp;
                tk.categ = (Category)(i+1);
                return REGEX_FOUND;
            }
        }
        D(puts("");)
        tk.lex = temp;
        return REGEX_NOT_FOUND;
    }else{
        return END_OF_STRING;
    }
}
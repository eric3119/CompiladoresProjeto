#include "Parser.h"

using namespace std;

void Parser::parse() {

    queue<string> Q;

    Q.push("Inicio");

    while(!Q.empty()){
        string s = Q.front();
        Q.pop();
    }

}

Parser::Parser(const std::string& filename) : tokenizer(filename) {}


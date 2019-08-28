#ifndef PROJETO_AB2_PARSER_H
#define PROJETO_AB2_PARSER_H

#include <vector>
#include <queue>
#include <string>
#include "../../projeto-ab1/src/Tokenizer.h"

class Parser {
private:
    Token tk{};

    std::ifstream source;
public:
    Tokenizer tokenizer;
    static std::vector<int> table;
    void parse();

    Parser(const std::string& filename);

};


#endif //PROJETO_AB2_PARSER_H

#ifndef PROJETO_AB2_PARSER_H
#define PROJETO_AB2_PARSER_H

#include <vector>
#include <queue>
#include <string>
#include "../../projeto-ab1/src/Tokenizer.h"

#define ERRO 0
#define OK 1

class Parser {
private:
    Token tk{};
    void nextToken();

    std::ifstream source;
public:
    Tokenizer tokenizer;
    static std::vector<int> table;
    void parse();

    Parser(const std::string& filename);

    int inicio();
    int inicioF();
    int bloco();
    int blocoF();
    int funcao();
    int funcaoF();
    int variavel();
    int listaId();
    int listaIdR();
    int listaAtr();
    int listaAtrR();
    int array();
    int arrayF();
    int sentencas();
    int comando();
    int entrada();
    int saida();
    int fIf();
    int fElseIf();
    int fElse();
    int fWhile();
    int fFor();
    int desvio();
    int atribuicao();
    int listaParam();
    int listaParamR();
    int listaArgs();
    int listaArgsR();
    int tipo();
    int expressao();
    int exprAritm();
    int exprAritR();
    int exprBool();
    int exprBoolR();
    int exprConcat();
    int exprConcatR();
    int termoAritm();
    int termoAritmR();
    int termoBool();
    int termoBoolR();
    int termoConcat();
    int termoConcatR();
    int fatorAritm();
    int fatorAritmF();
    int fatorBool();
    int fatorConcat();
    int listaArray();
    int listaArrayR();
    int unario();
    int relac();
    int igual();
    int logico();
    int adit();
    int mult();
    int opEq();
    int opMaior();
    int opMenor();
    int opMaiorEq();
    int opMenorEq();
    int opDifer();
    int opAnd();
    int opOr();
    int opNot();
    int opMais();
    int opMenos();
    int opMult();
    int opDiv();
    int opMod();
    int opAtr();
    int opConcat();

};


#endif //PROJETO_AB2_PARSER_H

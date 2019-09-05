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
    void printToken();

    std::ifstream source;
public:
    Tokenizer tokenizer;
    void parse();

    Parser(const std::string& filename);

    int inicio();
    int listaFunc();
    int listaProc();
    int listaVar();
    int funcao();
    int funcaoF();
    int proc();
    int procF();
    int variavel();
    int listaAtr();
    int listaAtrR();
    int listaAtrF();
    int listaId();
    int listaIdR();
    int id();
    int idF();
    int idFF();
    int array();
    int arrayF();
    int bloco();
    int listaSentencas();
    int sentenca();
    int entrada();
    int saida();
    int fIf();
    int fElseIf();
    int fElse();
    int fWhile();
    int fFor();
    int desvio();
    int fReturn();
    int atribuicao();
    int chamadaProc();
    int parametros();
    int listaParam();
    int listaParamR();
    int argumentos();
    int listaArgs();
    int listaArgsR();
    int tipo();
    int exprBool();
    int exprBoolR();
    int termoBool();
    int exprConcat();
    int exprConcatR();
    int exprAritm();
    int exprAritmR();
    int termoAritm();
    int termoAritmR();
    int fatorAritm();
    int fatorAtirmF();
    int listaArray();
    int listaArrayR();
    int opUnario();
    int opRelac();
    int opLogic();
    int opAdit();
    int opMult();
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
    int opAster();
    int opDiv();
    int opMod();
    int opAtr();
    int opConcat();

};


#endif //PROJETO_AB2_PARSER_H

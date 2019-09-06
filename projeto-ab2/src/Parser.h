#ifndef PROJETO_AB2_PARSER_H
#define PROJETO_AB2_PARSER_H

#include <vector>
#include <queue>
#include <string>
#include "../../projeto-ab1/src/Tokenizer.h"

#define ERRO 0
#define OK 1

class Parser {
public:
    Tokenizer tokenizer;
    void parse();

    Parser(const std::string& filename);
private:
    Token tk{};
    void nextToken();
    void printToken();

    bool printAndNext(Category c);
    void printAndNext();
    void printRule(const std::string &r);
    bool cmpCateg(Category c);
    void printErr(const std::string &s);

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
    int termoBoolF();
    int exprConcat();
    int exprConcatR();
    int exprAritm();
    int exprAritmR();
    int termoAritm();
    int termoAritmR();
    int fatorAritm();
    int fatorAritmF();
    int listaArray();
    int listaArrayR();
};


#endif //PROJETO_AB2_PARSER_H

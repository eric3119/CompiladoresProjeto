#include "Parser.h"

using namespace std;

void Parser::parse() {
    tk = tokenizer.nextToken();
    int res = inicio();
    cout << "\nParse " << (res == OK? "OK":"ERROR") << endl;
}

Parser::Parser(const std::string& filename) : tokenizer(filename) {}

int Parser::inicio(){
    int res = ERRO;

    if(tk.categ == Category::Func){
        res = listaFunc();
    }else if(tk.categ == Category::Proc){
        res = listaProc();
    }else if(
        tk.categ == Category::Integer ||
        tk.categ == Category::Float ||
        tk.categ == Category::Char ||
        tk.categ == Category::String ||
        tk.categ == Category::Boolean ||
        tk.categ == Category::Const
        ){
        res = listaVar();
    }else return ERRO;
}
int Parser::listaFunc(){}
int Parser::listaProc(){}
int Parser::listaVar(){}
int Parser::funcao(){}
int Parser::funcaoF(){}
int Parser::proc(){}
int Parser::procF(){}
int Parser::variavel(){}
int Parser::listaAtr(){}
int Parser::listaAtrR(){}
int Parser::listaAtrF(){}
int Parser::listaId(){}
int Parser::listaIdR(){}
int Parser::id(){}
int Parser::idF(){}
int Parser::idFF(){}
int Parser::array(){}
int Parser::arrayF(){}
int Parser::bloco(){}
int Parser::listaSentencas(){}
int Parser::sentenca(){}
int Parser::entrada(){}
int Parser::saida(){}
int Parser::fIf(){}
int Parser::fElseIf(){}
int Parser::fElse(){}
int Parser::fWhile(){}
int Parser::fFor(){}
int Parser::desvio(){}
int Parser::fReturn(){}
int Parser::atribuicao(){}
int Parser::chamadaProc(){}
int Parser::parametros(){}
int Parser::listaParam(){}
int Parser::listaParamR(){}
int Parser::argumentos(){}
int Parser::listaArgs(){}
int Parser::listaArgsR(){}
int Parser::tipo(){}
int Parser::exprBool(){}
int Parser::exprBoolR(){}
int Parser::termoBool(){}
int Parser::exprConcat(){}
int Parser::exprConcatR(){}
int Parser::exprAritm(){}
int Parser::exprAritmR(){}
int Parser::termoAritm(){}
int Parser::termoAritmR(){}
int Parser::fatorAritm(){}
int Parser::fatorAtirmF(){}
int Parser::listaArray(){}
int Parser::listaArrayR(){}
int Parser::opUnario(){}
int Parser::opRelac(){}
int Parser::opLogic(){}
int Parser::opAdit(){}
int Parser::opMult(){}
int Parser::opEq(){}
int Parser::opMaior(){}
int Parser::opMenor(){}
int Parser::opMaiorEq(){}
int Parser::opMenorEq(){}
int Parser::opDifer(){}
int Parser::opAnd(){}
int Parser::opOr(){}
int Parser::opNot(){}
int Parser::opMais(){}
int Parser::opMenos(){}
int Parser::opAster(){}
int Parser::opDiv(){}
int Parser::opMod(){}
int Parser::opAtr(){}
int Parser::opConcat(){}

void Parser::nextToken() {
    tk = tokenizer.nextToken();
}

void Parser::printToken() {
    printf("          [%04d, %04d] (%04d, %20s) ", tk.line, tk.col, tk.categ, categ_name(tk.categ));
    cout << "{"+tk.lex+"}" << endl;
}


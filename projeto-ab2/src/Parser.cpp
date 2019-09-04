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

    if(
        tk.categ == Category::Integer ||
        tk.categ == Category::Float ||
        tk.categ == Category::Char ||
        tk.categ == Category::Boolean ||
        tk.categ == Category::String ||
        tk.categ == Category::Procedure){
        cout << "          Início = Tipo ‘id’ InícioF\n";
        res = tipo();
        if(res == ERRO)
            return res;

        if (tk.categ == Category::Id){
            printToken();
            nextToken();
            res = inicioF();
            if(res == ERRO)
                return res;
        } else
            return ERRO;
    }else if (tk.categ == Category::Const){
        cout << "          Início = ‘const’ Tipo ‘id’ ListaAtr ‘;’ Início\n";
        printToken();
        nextToken();
        res = tipo();
        if(res == ERRO)
            return res;

        res = listaAtr();
        if(res == ERRO)
            return res;

        if(tk.categ == Category::PtVg){
            printToken();
            nextToken();
            res = inicio();
            if(res == ERRO)
                return res;
        }
    }else if(tk.categ == Category::Eof)
        cout << "          Início = epsilon\n";
    return res;
}
int Parser::inicioF(){
    int res = OK;
    if(tk.categ == Category::AbPar){
        cout << "          InícioF = Função Início\n";
        res = funcao();
    }else if(
            tk.categ == Category::AbCol||
            tk.categ == Category::Vg||
            tk.categ == Category::PtVg||
            tk.categ == Category::OpAtr
            ) {
        cout << "          InícioF = Variável Início\n";
        res = variavel();
    }
    if (res == ERRO) return res;

    return inicio();
}
int Parser::bloco(){

}
int Parser::blocoF(){}
int Parser::funcao(){
    int res = OK;

    if (tk.categ == Category::AbPar){
        printToken();
        nextToken();

        res = listaParam();
        if (tk.categ == Category::FePar){
            printToken();
            nextToken();
            res = funcaoF();
        } else return ERRO;
    }else return ERRO;

    return res;
}
int Parser::funcaoF(){
    int res = OK;

    if (tk.categ == Category::AbChav){
        printToken();
        nextToken();

        res = bloco();
        if (tk.categ == Category::FeChav){
            printToken();
            nextToken();
            if (tk.categ == Category::PtVg){
                printToken();
                nextToken();
            }
        } else return ERRO;
    }else if (tk.categ == Category::PtVg){
        printToken();
        nextToken();
    }else return ERRO;

    return res;
}
int Parser::variavel(){

}
int Parser::listaId(){}
int Parser::listaIdR(){}
int Parser::listaAtr(){}
int Parser::listaAtrR(){}
int Parser::array(){
    int res = ERRO;
    if(tk.categ == Category::AbCol){
        cout << "          Array = ‘[‘ ArrayF\n";
        printToken();
        nextToken();
        res = arrayF();
        if (res == ERRO) return res;
    }
    return OK;
}
int Parser::arrayF(){

}
int Parser::sentencas(){}
int Parser::comando(){}
int Parser::entrada(){}
int Parser::saida(){}
int Parser::fIf(){}
int Parser::fElseIf(){}
int Parser::fElse(){}
int Parser::fWhile(){}
int Parser::fFor(){}
int Parser::desvio(){}
int Parser::atribuicao(){}
int Parser::listaParam(){}
int Parser::listaParamR(){}
int Parser::listaArgs(){}
int Parser::listaArgsR(){}
int Parser::tipo(){
    int res = OK;

    switch(tk.categ){
        case Category::Integer:
            cout << "          Tipo = ‘int’\n";break;
        case Category::Float:
            cout << "          Tipo = ‘float’\n";break;
        case Category::Char:
            cout << "          Tipo = ‘char’\n";break;
        case Category::Boolean:
            cout << "          Tipo = ‘bool’\n";break;
        case Category::String:
            cout << "          Tipo = ‘string’\n";break;
        case Category::Procedure:
            cout << "          Tipo = ‘proc’\n";break;
        default:
            return ERRO;
    }
    printToken();
    nextToken();
    return res;
}
int Parser::expressao(){}
int Parser::exprAritm(){}
int Parser::exprAritR(){}
int Parser::exprBool(){}
int Parser::exprBoolR(){}
int Parser::exprConcat(){}
int Parser::exprConcatR(){}
int Parser::termoAritm(){}
int Parser::termoAritmR(){}
int Parser::termoBool(){}
int Parser::termoBoolR(){}
int Parser::termoConcat(){}
int Parser::termoConcatR(){}
int Parser::fatorAritm(){
    int res = ERRO;

    if(tk.categ == Category::AbPar){
        cout << "          FatorAritm  = ‘(‘ FatorAritmF\n";
        printToken();
        nextToken();
    }else if(tk.categ == Category::AbPar){
        cout << "          FatorAritm  = ‘id’\n";
        printToken();
        nextToken();
    }else if(tk.categ == Category::AbPar){
        cout << "          FatorAritm  = CteInt\n";
        printToken();
        nextToken();
    }else if(tk.categ == Category::AbPar){
        cout << "          FatorAritm  = CteFloat\n";
        printToken();
        nextToken();
    }else return ERRO;
}
int Parser::fatorAritmF(){
    int res = ERRO;

    if(
            tk.categ == Category::Integer ||
            tk.categ == Category::Float ||
            tk.categ == Category::Char ||
            tk.categ == Category::Boolean ||
            tk.categ == Category::String ||
            tk.categ == Category::Procedure) {
        cout << "          Início = Tipo ‘id’ InícioF\n";
        res = tipo();
        if (res == ERRO)
            return res;

        if (tk.categ == Category::AbPar){
            printToken();
            nextToken();
            res = exprAritm();
        }else return ERRO;
    }
}
int Parser::fatorBool(){}
int Parser::fatorConcat(){}
int Parser::listaArray(){}
int Parser::listaArrayR(){}
int Parser::unario(){}
int Parser::relac(){}
int Parser::igual(){}
int Parser::logico(){}
int Parser::adit(){}
int Parser::mult(){}
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
int Parser::opMult(){}
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


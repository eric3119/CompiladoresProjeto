#include "Parser.h"

using namespace std;

void Parser::parse() {
    tk = tokenizer.nextToken();
    int res = inicio();
    cout << "\nParse " << (res == OK? "OK":"ERROR") << endl;
}

Parser::Parser(const std::string& filename) : tokenizer(filename) {}

int Parser::inicio(){

    int res = OK;

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
            nextToken();
            res = inicioF();
            if(res == ERRO)
                return res;
        } else
            return ERRO;
    }else if (tk.categ == Category::Const){
        cout << "          Início = ‘const’ Tipo ‘id’ ListaAtr ‘;’ Início\n";
        nextToken();
        res = tipo();
        if(res == ERRO)
            return res;

        res = listaAtr();
        if(res == ERRO)
            return res;

        if(tk.categ == Category::PtVg){
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
        nextToken();

        res = listaParam();
        if (tk.categ == Category::FePar){
            nextToken();
            res = funcaoF();
        } else return ERRO;
    }else return ERRO;

    return res;
}
int Parser::funcaoF(){
    int res = OK;

    if (tk.categ == Category::AbChav){
        nextToken();

        res = bloco();
        if (tk.categ == Category::FeChav){
            nextToken();
            if (tk.categ == Category::PtVg){
                nextToken();
            }
        } else return ERRO;
    }else if (tk.categ == Category::PtVg){
        nextToken();
    }else return ERRO;

    return res;
}
int Parser::variavel(){}
int Parser::listaId(){}
int Parser::listaIdR(){}
int Parser::listaAtr(){}
int Parser::listaAtrR(){}
int Parser::array(){}
int Parser::arrayF(){}
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

    /*switch(tk.categ){
        case Category::Integer:
        case Category::Float:
        case Category::Char:
        case Category::Boolean:
        case Category::String:
        case Category::Procedure:
        default:
    }*/
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
int Parser::fatorAritm(){}
int Parser::fatorAritmF(){}
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


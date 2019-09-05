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
        cout << "          Início = ListaFunc Início\n";
        res = listaFunc();
        if(res == ERRO) {return res;}
        if(tk.categ != Category::Eof) {return inicio();}
        else {return ERRO;}
    }else if(tk.categ == Category::Procedure){
        cout << "          Início = ListaProc Início\n";
        res = listaProc();
        if(res == ERRO) {return res;}
        if(tk.categ != Category::Eof) {return inicio();}
        else {return ERRO;}
    }else if(
        tk.categ == Category::Integer ||
        tk.categ == Category::Float ||
        tk.categ == Category::Char ||
        tk.categ == Category::String ||
        tk.categ == Category::Boolean ||
        tk.categ == Category::Const
        ){
        cout << "          Início = ListaVar Início\n";
        res = listaVar();
        if(res == ERRO) {return res;}
        if(tk.categ != Category::Eof) {return inicio();}
        else {return ERRO;}
    }else return ERRO;
    return res;
}
int Parser::listaFunc(){
    int res = ERRO;
    if(tk.categ == Category::Func){
        cout << "          ListaFunc = Função ListaFunc\n";
        res = funcao();
        if(res == ERRO) {return res;}
        if(tk.categ == Category::Func) {return funcao();}
        else {return OK;}
    }
    return res;
}
int Parser::listaProc(){
    int res = ERRO;

    if(tk.categ == Category::Procedure){
        cout << "          ListaProc = Proc ListaProc\n";
        res = proc();
        if(res == ERRO) {return res;}
        if(tk.categ == Category::Procedure) {return proc();}
        else {return OK;}
    }

    return res;
}
int Parser::listaVar(){
    int res = ERRO;

    if(
            tk.categ == Category::Integer ||
            tk.categ == Category::Float ||
            tk.categ == Category::Char ||
            tk.categ == Category::String ||
            tk.categ == Category::Boolean ||
            tk.categ == Category::Const
            ){
        cout << "          ListaVar = Variável ListaVar\n";
        res = variavel();
        if(res == ERRO) {return res;}
        if(
                tk.categ == Category::Integer ||
                tk.categ == Category::Float ||
                tk.categ == Category::Char ||
                tk.categ == Category::String ||
                tk.categ == Category::Boolean ||
                tk.categ == Category::Const
                ) {return variavel();}
        else {return OK;}
    }

    return res;
}
int Parser::funcao(){
    int res = ERRO;
    cout << "          Função = ‘func’ Tipo ‘id’ ‘(‘ Parâmetros ‘)’ FunçãoF\n";

    if(tk.categ == Category::Func){
        printToken();
        nextToken();
        res = tipo();
        if(res == ERRO) {return res;}
        if(tk.categ == Category::Id){
            printToken();
            nextToken();
            if(tk.categ == Category::AbPar){
                printToken();
                nextToken();
                res = parametros();
                if(res == ERRO) {return res;}
                if(tk.categ == Category::FePar){
                    printToken();
                    nextToken();
                    return funcaoF();
                }else return ERRO;
            }else return ERRO;
        }else return ERRO;
    } else return ERRO;

    return res;
}
int Parser::funcaoF(){
    int res = ERRO;

    if(tk.categ == Category::AbChav){
        cout << "         FunçãoF = Bloco\n";
        return bloco();
    }else if(tk.categ == Category::PtVg){
        cout << "         FunçãoF = ‘;’\n";
        printToken();
        nextToken();
        return OK;
    }else return ERRO;

    return res;
}
int Parser::proc(){
    int res = ERRO;
    
    return res;
}
int Parser::procF(){
    int res = ERRO;
    
    return res;
}
int Parser::variavel(){
    int res = ERRO;
    
    return res;
}
int Parser::listaAtr(){
    int res = ERRO;
    
    return res;
}
int Parser::listaAtrR(){
    int res = ERRO;
    
    return res;
}
int Parser::listaAtrF(){
    int res = ERRO;
    
    return res;
}
int Parser::listaId(){
    int res = ERRO;
    
    return res;
}
int Parser::listaIdR(){
    int res = ERRO;
    
    return res;
}
int Parser::id(){
    int res = ERRO;
    
    return res;
}
int Parser::idF(){
    int res = ERRO;
    
    return res;
}
int Parser::idFF(){
    int res = ERRO;
    
    return res;
}
int Parser::array(){
    int res = ERRO;
    
    return res;
}
int Parser::arrayF(){
    int res = ERRO;
    
    return res;
}
int Parser::bloco(){
    int res = ERRO;
    
    return res;
}
int Parser::listaSentencas(){
    int res = ERRO;
    
    return res;
}
int Parser::sentenca(){
    int res = ERRO;
    
    return res;
}
int Parser::entrada(){
    int res = ERRO;
    
    return res;
}
int Parser::saida(){
    int res = ERRO;
    
    return res;
}
int Parser::fIf(){
    int res = ERRO;
    
    return res;
}
int Parser::fElseIf(){
    int res = ERRO;
    
    return res;
}
int Parser::fElse(){
    int res = ERRO;
    
    return res;
}
int Parser::fWhile(){
    int res = ERRO;
    
    return res;
}
int Parser::fFor(){
    int res = ERRO;
    
    return res;
}
int Parser::desvio(){
    int res = ERRO;
    
    return res;
}
int Parser::fReturn(){
    int res = ERRO;
    
    return res;
}
int Parser::atribuicao(){
    int res = ERRO;
    
    return res;
}
int Parser::chamadaProc(){
    int res = ERRO;
    
    return res;
}
int Parser::parametros(){
    int res = ERRO;
    
    return res;
}
int Parser::listaParam(){
    int res = ERRO;
    
    return res;
}
int Parser::listaParamR(){
    int res = ERRO;
    
    return res;
}
int Parser::argumentos(){
    int res = ERRO;
    
    return res;
}
int Parser::listaArgs(){
    int res = ERRO;
    
    return res;
}
int Parser::listaArgsR(){
    int res = ERRO;
    
    return res;
}
int Parser::tipo(){
    int res = ERRO;

    if(tk.categ == Category::Integer){
        cout << "          Tipo = ‘int’\n";
        printToken();
        nextToken();
        return OK;
    }else if(tk.categ == Category::Float){
        cout << "          Tipo = ‘float’\n";
        printToken();
        nextToken();
        return OK;
    }else if(tk.categ == Category::Char){
        cout << "          Tipo = ‘char’\n";
        printToken();
        nextToken();
        return OK;
    }else if(tk.categ == Category::Boolean){
        cout << "          Tipo = ‘bool’\n";
        printToken();
        nextToken();
        return OK;
    }else if(tk.categ == Category::String){
        cout << "          Tipo = ‘string’\n";
        printToken();
        nextToken();
        return OK;
    }else return ERRO;

    return res;
}
int Parser::exprBool(){
    int res = ERRO;
    
    return res;
}
int Parser::exprBoolR(){
    int res = ERRO;
    
    return res;
}
int Parser::termoBool(){
    int res = ERRO;
    
    return res;
}
int Parser::exprConcat(){
    int res = ERRO;
    
    return res;
}
int Parser::exprConcatR(){
    int res = ERRO;
    
    return res;
}
int Parser::exprAritm(){
    int res = ERRO;
    
    return res;
}
int Parser::exprAritmR(){
    int res = ERRO;
    
    return res;
}
int Parser::termoAritm(){
    int res = ERRO;
    
    return res;
}
int Parser::termoAritmR(){
    int res = ERRO;
    
    return res;
}
int Parser::fatorAritm(){
    int res = ERRO;
    
    return res;
}
int Parser::fatorAtirmF(){
    int res = ERRO;
    
    return res;
}
int Parser::listaArray(){
    int res = ERRO;
    
    return res;
}
int Parser::listaArrayR(){
    int res = ERRO;
    
    return res;
}
int Parser::opUnario(){
    int res = ERRO;
    
    return res;
}
int Parser::opRelac(){
    int res = ERRO;
    
    return res;
}
int Parser::opLogic(){
    int res = ERRO;
    
    return res;
}
int Parser::opAdit(){
    int res = ERRO;
    
    return res;
}
int Parser::opMult(){
    int res = ERRO;
    
    return res;
}
int Parser::opEq(){
    int res = ERRO;
    
    return res;
}
int Parser::opMaior(){
    int res = ERRO;
    
    return res;
}
int Parser::opMenor(){
    int res = ERRO;
    
    return res;
}
int Parser::opMaiorEq(){
    int res = ERRO;
    
    return res;
}
int Parser::opMenorEq(){
    int res = ERRO;
    
    return res;
}
int Parser::opDifer(){
    int res = ERRO;
    
    return res;
}
int Parser::opAnd(){
    int res = ERRO;
    
    return res;
}
int Parser::opOr(){
    int res = ERRO;
    
    return res;
}
int Parser::opNot(){
    int res = ERRO;
    
    return res;
}
int Parser::opMais(){
    int res = ERRO;
    
    return res;
}
int Parser::opMenos(){
    int res = ERRO;
    
    return res;
}
int Parser::opAster(){
    int res = ERRO;
    
    return res;
}
int Parser::opDiv(){
    int res = ERRO;
    
    return res;
}
int Parser::opMod(){
    int res = ERRO;
    
    return res;
}
int Parser::opAtr(){
    int res = ERRO;
    
    return res;
}
int Parser::opConcat(){
    int res = ERRO;
    
    return res;
}

void Parser::nextToken() {
    tk = tokenizer.nextToken();
}

void Parser::printToken() {
    printf("          [%04d, %04d] (%04d, %20s) ", tk.line, tk.col, tk.categ, categ_name(tk.categ));
    cout << "{"+tk.lex+"}" << endl;
}


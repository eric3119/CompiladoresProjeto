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
    }else if(cmpCateg(Category::Eof)) return OK;

    return ERRO;
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
    cout << "          Função = 'func' Tipo 'id' '(' Parâmetros ')' FunçãoF\n";

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
        cout << "         FunçãoF = ';'\n";
        printToken();
        nextToken();
        return OK;
    }else return ERRO;

    return res;
}
int Parser::proc(){
    int res = ERRO;

    cout << "          Proc = 'proc' Tipo 'id' '(' Parâmetros ')' ProcF\n";

    if(tk.categ == Category::Procedure){
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
                    return procF();
                }else return ERRO;
            }else return ERRO;
        }else return ERRO;
    } else return ERRO;
    
    return res;
}
int Parser::procF(){
    int res = ERRO;

    if(tk.categ == Category::AbChav){
        cout << "         ProcF = Bloco\n";
        return bloco();
    }else if(tk.categ == Category::PtVg){
        cout << "         ProcF = ';'\n";
        printToken();
        nextToken();
        return OK;
    }else return ERRO;

    return res;
}
int Parser::variavel(){
    int res = ERRO;

    if(tk.categ == Category::Const){
        cout << "          Variável = 'const' Tipo ListaAtr ';'\n";
        if (tk.categ == Category::Const){
            printToken();
            nextToken();

            res = tipo();
            if (res == ERRO) return res;

            res = listaAtr();
            if (res == ERRO) return res;

            if(tk.categ == Category::PtVg){
                printToken();
                nextToken();
                return OK;
            }else return ERRO;
        }
    }else if(
            tk.categ == Category::Integer ||
            tk.categ == Category::Float ||
            tk.categ == Category::Char ||
            tk.categ == Category::String ||
            tk.categ == Category::Boolean
            ){
        cout << "          Variável = Tipo ListaId ';'\n";
        res = tipo();
        if (res == ERRO) return res;

        res = listaId();
        if (res == ERRO) return res;

        if(tk.categ == Category::PtVg){
            printToken();
            nextToken();
            return OK;
        }else return ERRO;
    }else return ERRO;

    return res;
}
int Parser::listaAtr(){
    int res = ERRO;

    if(tk.categ == Category::Id){
        cout << "          ListaAtr = 'id' ListaAtrF ListaAtrR\n";
        printToken();
        nextToken();
        res = listaAtrF();
        if (res == ERRO) return res;
        return listaAtrR();
    }
    return res;
}
int Parser::listaAtrR(){
    int res = OK;

    if(tk.categ == Category::Vg){
        cout << "          ListaAtrR = ',' 'id' ListaAtrF ListaAtrR\n";
        printToken();
        nextToken();
        if(tk.categ == Category::Id){
            printToken();
            nextToken();
            res = listaAtrF();
            if (res == ERRO) return res;
            return listaAtrR();
        }else return ERRO;
    }
    cout << "          ListaAtrR = EPSILON\n";
    return res;
}
int Parser::listaAtrF(){
    int res = ERRO;

    if(tk.categ == Category::OpAtr){
        cout << "          ListaAtrF = Atribuição\n";
        return atribuicao();
    }else if(tk.categ == Category::AbCol){
        cout << "          ListaAtrF = Array Atribuição\n";
        res = array();
        if (res == ERRO) return res;
        return atribuicao();
    }

    return res;
}
int Parser::listaId(){
    int res = ERRO;

    if(tk.categ == Category::Id){
        cout << "          ListaId = Id ListaIdR\n";
        res = id();
        if(res == ERRO) return res;
        return listaIdR();
    }

    return res;
}
int Parser::listaIdR(){
    int res = ERRO;

    if(tk.categ == Category::Vg){
        cout << "          ListaIdR = ',' Id ListaIdR\n";
        printToken();
        nextToken();
        if(tk.categ == Category::Id){
            printToken();
            nextToken();
            res = id();
            if (res == ERRO) return res;
            return listaIdR();
        }else return ERRO;
    }
    cout << "          ListaIdR = EPSILON\n";
    
    return res;
}
int Parser::id(){
    int res = ERRO;

    if(tk.categ == Category::Id){
        cout << "          Id = 'id' IdF\n";
        printToken();
        nextToken();

        return idF();
    }
    
    return res;
}
int Parser::idF(){
    int res = OK;

    if(tk.categ == Category::AbPar){
        cout << "          IdF = '(' Argumentos ')'\n";
        printToken();
        nextToken();
        res = argumentos();
        if (res == ERRO) return res;

        if(tk.categ == Category::FePar){
            printToken();
            nextToken();

            return OK;
        } else return ERRO;
    }else if(tk.categ == Category::OpAtr){
        cout << "          IdF = Atribuição\n";
        return atribuicao();
    }else if(tk.categ == Category::AbCol){
        cout << "          IdF = Array IdFF\n";
        res = array();
        if(res == ERRO) return res;

        return idFF();
    }

    cout << "          IdF = EPSILON\n";

    return res;
}
int Parser::idFF(){

    if(tk.categ == Category::OpAtr){
        cout << "          IdFF = Atribuição\n";
        return atribuicao();
    }

    cout << "          IdFF = EPSILON\n";
    return OK;
}
int Parser::array(){
    int res = ERRO;

    if(tk.categ == Category::AbCol){
        cout << "          Array  = '[' ArrayF\n";
        printToken();
        nextToken();

        return arrayF();
    }

    return res;
}
int Parser::arrayF(){
    int res = ERRO;

    if(tk.categ == Category ::FeCol){
        cout << "          ArrayF = ']'\n";
        printToken();
        nextToken();
    }else if(
            tk.categ == Category ::OpNot ||
            tk.categ == Category ::OpMenos ||
            tk.categ == Category ::Id ||
            tk.categ == Category ::CteInt ||
            tk.categ == Category ::CteFloat ||
            tk.categ == Category ::CteBool ||
            tk.categ == Category ::CteStr ||
            tk.categ == Category ::AbCol
            ){
        cout << "          ArrayF = ExprBool ']'\n";
        res = exprBool();
        if(res == ERRO) return res;

        if(tk.categ == Category::FeCol){
            printToken();
            nextToken();
            return OK;
        }else return ERRO;
    }

    return res;
}
int Parser::bloco(){
    int res = ERRO;

    if(tk.categ == Category::AbChav){
        cout << "          Bloco = '{' ListaSentenças '}'\n";
        printToken();
        nextToken();
        res = listaSentencas();
        if (res == ERRO) return res;

        if(tk.categ == Category::FeChav){
            printToken();
            nextToken();
            return OK;
        }else return ERRO;
    }
    
    return res;
}
int Parser::listaSentencas(){
    int res = ERRO;

    cout << "          ListaSentenças = Sentença ListaSentenças\n";

    res = sentenca();
    if(res == ERRO) return res;

    if(
            tk.categ == Category::If ||
            tk.categ == Category::While ||
            tk.categ == Category::For ||
            tk.categ == Category::Break ||
            tk.categ == Category::Return ||
            tk.categ == Category::Input ||
            tk.categ == Category::Print ||
            tk.categ == Category::Id
            ){
        return listaSentencas();
    }

    return res;
}
int Parser::sentenca(){

    if(tk.categ == Category::If){
        cout << "          Sentença = If\n";
        return fIf();
    } else if(tk.categ == Category::While){
        cout << "          Sentença = While\n";
        return fWhile();
    } else if(tk.categ == Category::For){
        cout << "          Sentença = For\n";
        return fFor();
    } else if(tk.categ == Category::Break){
        cout << "          Sentença = Desvio\n";
        return desvio();
    }else if(tk.categ == Category::Return){
        cout << "          Sentença = Return\n";
        return fReturn();
    }else if(tk.categ == Category::Input){
        cout << "          Sentença = Entrada\n";
        return entrada();
    }else if(tk.categ == Category::Print){
        cout << "          Sentença = Saída\n";
        return saida();
    }else if(tk.categ == Category::Id){
        cout << "          Sentença = Id ';'\n";
        if(id() == ERRO) return ERRO;
        if(tk.categ == Category::PtVg){
            printToken();
            nextToken();
            return OK;
        }else return ERRO;
    }

    cout << "          Sentença = EPSILON\n";
    return OK;
}
int Parser::entrada(){
    int res = ERRO;

    cout << "          Entrada = 'input' Argumentos ';'\n";

    if(tk.categ == Category::Input){
        printToken();
        nextToken();
        res = argumentos();
        if(res == ERRO) return res;

        if(tk.categ == Category::PtVg){
            printToken();
            nextToken();
            return OK;
        }else return ERRO;
    }else return ERRO;

    return res;
}
int Parser::saida(){
    int res = ERRO;

    if(tk.categ == Category::Print){
        cout << "          Saída = 'print' CteStr Argumentos ';'\n";
        printToken();
        nextToken();
        if(tk.categ == Category::CteStr){
            printToken();
            nextToken();
        }else return ERRO;

        res = argumentos();
        if(res == ERRO) return res;

        if(tk.categ == Category::PtVg){
            printToken();
            nextToken();
            return OK;
        }else return ERRO;
    }else return ERRO;
    
    return res;
}
int Parser::fIf(){
    int res = ERRO;

    if(tk.categ == Category::If){
        cout << "          If    = 'if' '(' ExprBool ')' Bloco ElseIf Else\n";
        printToken();
        nextToken();
        if(tk.categ == Category::AbPar){
            printToken();
            nextToken();
        }else return ERRO;

        res = exprBool();
        if(res == ERRO) return res;

        if(tk.categ == Category::FePar){
            printToken();
            nextToken();
        }else return ERRO;

        res = bloco();
        if(res == ERRO) return res;
        res = fElseIf();
        if(res == ERRO) return res;
        return fElse();
    }
    
    return res;
}
int Parser::fElseIf(){
    int res = OK;

    if(tk.categ == Category::ElseIf){
        cout << "          ElseIf = 'else if' '(' ExprBool ')' Bloco ElseIf\n";
        printToken();
        nextToken();
        if(tk.categ == Category::AbPar){
            printToken();
            nextToken();
        }else return ERRO;

        res = exprBool();
        if(res == ERRO) return res;

        if(tk.categ == Category::FePar){
            printToken();
            nextToken();
        } else return ERRO;

        res = bloco();
        if(res == ERRO) return res;
        return fElseIf();
    }

    cout << "          ElseIf = EPSILON\n";
    return res;
}
int Parser::fElse(){
    int res = OK;

    if(tk.categ == Category::Else){
        cout << "          Else = 'else' Bloco\n";
        printToken();
        nextToken();

        return bloco();
    }

    cout << "          Else = EPSILON\n";
    return res;
}
int Parser::fWhile(){
    int res = ERRO;

    if(tk.categ == Category::While){
        cout << "          While = 'while' '(' ExprBool ')' Bloco\n";

        printToken();
        nextToken();
        if(tk.categ == Category::AbPar){
            printToken();
            nextToken();
        }else return ERRO;

        res = exprBool();
        if(res == ERRO) return res;

        if(tk.categ == Category::FePar){
            printToken();
            nextToken();
        }else return ERRO;
        return bloco();
    }
    
    return res;
}
int Parser::fFor(){
    int res = ERRO;

    if(tk.categ == Category::For){
        cout << "          For ='for' Id 'in' '(' ExprBool ',' ExprBool ')' 'step' ExprBool Bloco\n";
        printToken();
        nextToken();

        res = id();
        if(res == ERRO) return res;

        if(tk.categ == Category::In){
            printToken();
            nextToken();
        }else return ERRO;

        if(tk.categ == Category::AbPar){
            printToken();
            nextToken();
        }else return ERRO;

        res = exprBool();
        if(res == ERRO) return res;

        if(tk.categ == Category::Vg){
            printToken();
            nextToken();
        }else return ERRO;

        res = exprBool();
        if(res == ERRO) return res;

        if(tk.categ == Category::FePar){
            printToken();
            nextToken();
        }else return ERRO;

        if(tk.categ == Category::Step){
            printToken();
            nextToken();
        }else return ERRO;

        res = exprBool();
        if(res == ERRO) return res;

        return bloco();
    }

    return res;
}
int Parser::desvio(){
    int res = ERRO;

    if(tk.categ == Category::Break){
        printRule("Desvio = 'break' ';'");
        printToken();
        nextToken();
        if(!printAndNext(Category::PtVg)){
            return ERRO;
        }
    }

    return res;
}
int Parser::fReturn(){
    int res = ERRO;

    if(tk.categ == Category::Return){
        printRule("Return = 'return' ExprBool ';'");
        printToken();
        nextToken();
        res = exprBool();
        if(res == ERRO) return res;

        if(printAndNext(Category::PtVg))
            return OK;
        return ERRO;
    }

    return res;
}
int Parser::atribuicao(){
    int res = ERRO;

    printRule("Atribuição = OpAtribuição ExprBool ';'");

    if(!printAndNext(Category::OpAtr)){return ERRO;}
    res = exprBool();
    if(res == ERRO) return res;

    if(printAndNext(Category::PtVg)) return OK;
    else return ERRO;
}
int Parser::parametros(){
    int res = OK;

    if(
            tk.categ == Category::Integer ||
            tk.categ == Category::Float ||
            tk.categ == Category::Char ||
            tk.categ == Category::String ||
            tk.categ == Category::Boolean
            ){
        printRule("Parâmetros = ListaParam");
        return listaParam();
    }

    printRule("Parâmetros = EPSILON");
    return res;
}
int Parser::listaParam(){
    int res = OK;

    printRule("ListaParam  = Tipo Id ListaParamR");

    res = tipo();
    if(res == ERRO) return res;

    res = id();
    if(res == ERRO) return res;

    return listaParamR();
}
int Parser::listaParamR(){
    if(cmpCateg(Category::Vg)){
        printRule("ListaParamR = ',' Tipo Id ListaParamR");
        printAndNext();
        if(tipo() == ERRO) return ERRO;
        if (id() == ERRO) return ERRO;
        return listaParamR();
    }

    printRule("ListaParamR = EPSILON");
    return OK;
}
int Parser::argumentos(){

    if(
            cmpCateg(Category::OpNot) ||
            cmpCateg(Category::AbPar) ||
            cmpCateg(Category::Id) ||
            cmpCateg(Category::CteInt) ||
            cmpCateg(Category::CteFloat) ||
            cmpCateg(Category::CteChar) ||
            cmpCateg(Category::CteBool) ||
            cmpCateg(Category::CteStr) ||
            cmpCateg(Category::AbCol)
            ){
        printRule("Argumentos = ListaArgs");
        return listaArgs();
    }

    printRule("Argumentos = EPSILON");
    return OK;
}
int Parser::listaArgs(){

    printRule("ListaArgs  = ExprBool ListaArgsR");

    if(exprBool() == ERRO) return ERRO;

    return listaArgsR();
}
int Parser::listaArgsR(){

    if(cmpCateg(Category::Vg)){
        printRule("ListaArgsR = ',' ExprBool ListaArgsR");
        printAndNext();
        if(exprBool() == ERRO) return ERRO;

        return listaArgsR();
    }

    printRule("ListaArgsR = EPSILON");
    return OK;
}
int Parser::tipo(){
    int res = ERRO;

    if(tk.categ == Category::Integer){
        printRule("Tipo = 'int'");
        printAndNext();
        return OK;
    }else if(tk.categ == Category::Float){
        printRule("Tipo = 'float'");
        printAndNext();
        return OK;
    }else if(tk.categ == Category::Char){
        printRule("Tipo = 'char'");
        printAndNext();
        return OK;
    }else if(tk.categ == Category::Boolean){
        printRule("Tipo = 'bool'");
        printAndNext();
        return OK;
    }else if(tk.categ == Category::String){
        printRule("Tipo = 'string'");
        printAndNext();
        return OK;
    }else return ERRO;
}
int Parser::exprBool(){
    printRule("ExprBool = TermoBool ExprBoolR");
    if(termoBool() == ERRO) return ERRO;
    return exprBoolR();
}
int Parser::exprBoolR(){
    if(cmpCateg(Category::OpAnd) || cmpCateg(Category::OpOr)){
        printRule("ExprBoolR = OpLogic TermoBool ExprBoolR");
        if(opLogic() == ERRO) return ERRO;
        if(termoBool() == ERRO) return ERRO;
        return exprBoolR();
    }

    printRule("ExprBoolR = EPSILON");
    return OK;
}
int Parser::termoBool(){
    if(cmpCateg(Category::OpNot)){
        printRule("TermoBool = '!' TermoBool");
        printAndNext();

        return termoBool();
    } else if (
            cmpCateg(Category::AbPar) ||
            cmpCateg(Category::Id) ||
            cmpCateg(Category::CteInt) ||
            cmpCateg(Category::CteFloat) ||
            cmpCateg(Category::CteChar) ||
            cmpCateg(Category::CteBool) ||
            cmpCateg(Category::CteStr) ||
            cmpCateg(Category::AbCol)
            ){
        printRule("TermoBool = ExprConcat TermoBoolF");

        if(exprConcat() == ERRO) return ERRO;
        return termoBoolF();
    } else return ERRO;

}
int Parser::termoBoolF() {
    if(
            cmpCateg(Category::OpEq)||
            cmpCateg(Category::OpDifer)||
            cmpCateg(Category::OpMaior)||
            cmpCateg(Category::OpMaiorEq)||
            cmpCateg(Category::OpMenor)||
            cmpCateg(Category::OpMenorEq)
            ){
        printRule("TermoBoolF = OpRelac ExprConcat");
        printAndNext();
        return exprConcat();
    }
    printRule("TermoBoolF = EPSILON");
    return OK;
}
int Parser::exprConcat(){
    printRule("ExprConcat = ExprAritm ExprConcatR;");
    if(exprAritm() == ERRO) return ERRO;
    return exprConcatR();
}
int Parser::exprConcatR(){
    if(cmpCateg(Category::OpConcat)){
        printRule("ExprConcatR = OpConcat ExprAritm ExprConcatR");
        printAndNext();
        if(exprAritm() == ERRO) return ERRO;

        return exprConcatR();
    }

    printRule("ExprConcatR = EPSILON");
    return OK;
}
int Parser::exprAritm(){
    if(termoAritm() == ERRO) return ERRO;
    printRule("ExprAritm = TermoAritm ExprAritmR");
    return exprAritmR();
}
int Parser::exprAritmR(){
    if(cmpCateg(Category::OpMenos)||
       cmpCateg(Category::OpMais)){
        printRule("ExprAritmR = OpAritm TermoAritm ExprAritmR");
        printAndNext();
        if(termoAritm() == ERRO) return ERRO;

        return exprAritmR();
    }

    printRule("ExprAritmR = EPSILON");
    return OK;
}
int Parser::termoAritm(){
    if(cmpCateg(Category::AbPar) ||
       cmpCateg(Category::Id) ||
       cmpCateg(Category::CteInt) ||
       cmpCateg(Category::CteFloat) ||
       cmpCateg(Category::CteChar) ||
       cmpCateg(Category::CteBool) ||
       cmpCateg(Category::CteStr) ||
       cmpCateg(Category::AbCol)){
        printRule("TermoAritm = FatorAritm TermoAritmR");
        if(fatorAritm() == ERRO) return ERRO;
        return termoAritmR();
    }else return ERRO;
}
int Parser::termoAritmR(){
    if( cmpCateg(Category::OpMod)||
        cmpCateg(Category::OpMult)||
        cmpCateg(Category::OpDiv)){
        printRule("TermoAritmR = OpMult FatorAritm TermoAritmR");
        printAndNext();

        if(fatorAritm() == ERRO) return ERRO;
        return termoAritmR();
    }

    printRule("TermoAritmR = EPSILON");
    return OK;
}
int Parser::fatorAritm(){
    if(cmpCateg(Category::AbPar)){
        printRule("FatorAritm = '(' FatorAritmF");
        printAndNext();
        return fatorAritmF();
    }else if(cmpCateg(Category::Id)){
        printRule("FatorAritm = Id");
        return id();
    }else if(cmpCateg(Category::CteInt)){
        printRule("FatorAritm = CteInt");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::CteFloat)){
        printRule("FatorAritm = CteFloat");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::CteChar)){
        printRule("FatorAritm = CteChar");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::CteBool)){
        printRule("FatorAritm = CteBool");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::CteStr)){
        printRule("FatorAritm = CteStr");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::AbCol)){
        printRule("FatorAritm = '[' ListaArray ']'");
        printAndNext();
        if(listaArray() ==ERRO) return ERRO;
        if(!printAndNext(Category::FeCol)) return ERRO;
        return OK;
    }
}
int Parser::fatorAritmF(){
    if(tk.categ == Category::Integer ||
       tk.categ == Category::Float ||
       tk.categ == Category::Char ||
       tk.categ == Category::String ||
       tk.categ == Category::Boolean){
        printRule("FatorAtirmF = Tipo ')' ExprBool");
        if(tipo() ==ERRO)return ERRO;

        if(!printAndNext(Category::FePar)) return ERRO;

        return exprBool();
    }else if(tk.categ == Category ::OpNot ||
             tk.categ == Category ::OpMenos ||
             tk.categ == Category ::Id ||
             tk.categ == Category ::CteInt ||
             tk.categ == Category ::CteFloat ||
             tk.categ == Category ::CteBool ||
             tk.categ == Category ::CteStr ||
             tk.categ == Category ::AbCol){
        printRule("FatorAtirmF = ExprBool ')'");
        if(exprBool() == ERRO) return ERRO;

        if(printAndNext(Category::FePar)) return OK;
        else return ERRO;
    }
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

bool Parser::printAndNext(Category c){
    if(cmpCateg(c)){
        printToken();
        nextToken();
        return true;
    }
    return false;
}

bool Parser::cmpCateg(Category c){
    return tk.categ == c;
}

void Parser::printAndNext(){
    printToken();
    nextToken();
}

void Parser::printRule(string r){
    cout << "          " << r << endl;
}
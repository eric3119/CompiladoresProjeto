#include "Parser.h"

using namespace std;

Parser::Parser(const std::string& filename) : tokenizer(filename) {}

void Parser::parse() {
    tk = tokenizer.nextToken();
    cout << endl << (inicio() == OK? "Parse OK":"Parse ERROR") << endl;
}

int Parser::inicio(){
    if(cmpCateg(Category::Func)){
        printRule("Início = ListaFunc Início");

        if(listaFunc() == ERRO) return ERRO;
        return inicio();
    }else if(cmpCateg(Category::Procedure)){
        printRule("Início = ListaProc Início");

        if(listaProc() == ERRO) return ERRO;
        return inicio();
    }else if(
        cmpCateg(Category::Integer) ||
        cmpCateg(Category::Float) ||
        cmpCateg(Category::Char) ||
        cmpCateg(Category::String) ||
        cmpCateg(Category::Boolean) ||
        cmpCateg(Category::Const)
        ){
        printRule("Início = ListaVar Início");

        if(listaVar() == ERRO) return ERRO;
        return inicio();
    }else if(cmpCateg(Category::Eof)){
        printRule("Início = EPSILON");
        return OK;
    } else return ERRO;
}
int Parser::listaFunc(){
    if(cmpCateg(Category::Func)){
        printRule("ListaFunc = Função ListaFunc");
        if(funcao() == ERRO) return ERRO;
        return listaFunc();
    }

    printRule("ListaFunc = EPSILON");
    return OK;
}
int Parser::listaProc(){
    if(cmpCateg(Category::Procedure)){
        printRule("ListaProc = Proc ListaProc");

        if(proc() == ERRO) return ERRO;
        return listaProc();
    }

    printRule("ListaProc = EPSILON");
    return OK;
}
int Parser::listaVar(){
    if(
            cmpCateg(Category::Integer) ||
            cmpCateg(Category::Float) ||
            cmpCateg(Category::Char) ||
            cmpCateg(Category::String) ||
            cmpCateg(Category::Boolean) ||
            cmpCateg(Category::Const)
            ){
        printRule("ListaVar = Variável ListaVar");

        if(variavel() == ERRO) return ERRO;
        return listaVar();
    }

    printRule("ListaVar = EPSILON");
    return OK;
}
int Parser::funcao(){
    if(cmpCateg(Category::Func)){
        printRule("Função = 'func' Tipo 'id' '(' Parâmetros ')' FunçãoF");
        printToken();
        nextToken();

        if(tipo() == ERRO) return ERRO;

        if(!printAndNext(Category::Id)) return ERRO;
        if(!printAndNext(Category::AbPar)) return ERRO;

        if(parametros() == ERRO) return ERRO;
        if(!printAndNext(Category::FePar)) return ERRO;

        return funcaoF();
    } else return ERRO;
}
int Parser::funcaoF(){
    if(cmpCateg(Category::AbChav)){
        printRule("FunçãoF = Bloco");
        return bloco();
    }else if(cmpCateg(Category::PtVg)){
        printRule("FunçãoF = ';'");
        printAndNext();
        return OK;
    }else return ERRO;
}
int Parser::proc(){

    if(cmpCateg(Category::Procedure)){
        printRule("Proc = 'proc' 'id' '(' Parâmetros ')' ProcF");
        printAndNext();
        if(!printAndNext(Category::Id)) return ERRO;
        if(!printAndNext(Category::AbPar)) return ERRO;

        if(parametros() == ERRO) return ERRO;

        if(!printAndNext(Category::FePar)) return ERRO;

        return procF();
    } else return ERRO;
}
int Parser::procF(){
    if(cmpCateg(Category::AbChav)){
        printRule("ProcF = Bloco");
        return bloco();
    }else if(cmpCateg(Category::PtVg)){
        printRule("ProcF = ';'");
        printAndNext();
        return OK;
    }else return ERRO;
}
int Parser::variavel(){
    if(cmpCateg(Category::Const)){
        printRule("Variável = 'const' Tipo ListaAtr ';'");
        printAndNext();

        if(tipo() == ERRO) return ERRO;
        if(listaAtr() == ERRO) return ERRO;

        if(!printAndNext(Category::PtVg)) return ERRO;

        return OK;
    }else if(
            cmpCateg(Category::Integer) ||
            cmpCateg(Category::Float) ||
            cmpCateg(Category::Char) ||
            cmpCateg(Category::String) ||
            cmpCateg(Category::Boolean)
            ){
        printRule("Variável = Tipo ListaId ';'");

        if (tipo() == ERRO) return ERRO;
        if (listaId() == ERRO) return ERRO;
        if (!printAndNext(Category::PtVg)) return ERRO;

        return OK;
    }else return ERRO;
}
int Parser::listaAtr(){
    if(cmpCateg(Category::Id)){
        printRule("ListaAtr = 'id' ListaAtrF ListaAtrR");
        printAndNext();
        if (listaAtrF() == ERRO) return ERRO;
        return listaAtrR();
    }else return ERRO;
}
int Parser::listaAtrR(){
    if(cmpCateg(Category::Vg)){
        printRule("ListaAtrR = ',' 'id' ListaAtrF ListaAtrR");
        printAndNext();

        if(!printAndNext(Category::Id)) return ERRO;
        if(listaAtrF() == ERRO) return ERRO;
        return listaAtrR();
    }
    printRule("ListaAtrR = EPSILON");
    return OK;
}
int Parser::listaAtrF(){
    if(cmpCateg(Category::OpAtr)){
        printRule("ListaAtrF = Atribuição");
        return atribuicao();
    }else if(cmpCateg(Category::AbCol)){
        printRule("ListaAtrF = Array Atribuição");
        if (array() == ERRO) return ERRO;
        return atribuicao();
    }

    return ERRO;
}
int Parser::listaId(){
    if(cmpCateg(Category::Id)){
        printRule("ListaId = Id ListaIdR");
        if(id() == ERRO) return ERRO;
        return listaIdR();
    }
    return ERRO;
}
int Parser::listaIdR(){
    if(cmpCateg(Category::Vg)){
        printRule("ListaIdR = ',' Id ListaIdR");
        printAndNext();
        if (id() == ERRO) return ERRO;
        return listaIdR();
    }

    printRule("ListaIdR = EPSILON");
    return OK;
}
int Parser::id(){
    if(cmpCateg(Category::Id)){
        printRule("Id = 'id' IdF");
        printAndNext();

        return idF();
    }

    return ERRO;
}
int Parser::idF(){
    if(cmpCateg(Category::AbPar)){
        printRule("IdF = '(' Argumentos ')'");
        printAndNext();

        if (argumentos() == ERRO) return ERRO;

        if(printAndNext(Category::FePar)) return OK;
        else return ERRO;
    }else if(cmpCateg(Category::OpAtr)){
        printRule("IdF = Atribuição");
        return atribuicao();
    }else if(cmpCateg(Category::AbCol)){
        printRule("IdF = Array IdFF");
        if(array() == ERRO) return ERRO;

        return idFF();
    }

    printRule("IdF = EPSILON");
    return OK;
}
int Parser::idFF(){

    if(cmpCateg(Category::OpAtr)){
        printRule("IdFF = Atribuição");
        return atribuicao();
    }

    printRule("IdFF = EPSILON");
    return OK;
}
int Parser::array(){
    if(cmpCateg(Category::AbCol)){
        printRule("Array  = '[' ArrayF");
        printAndNext();

        return arrayF();
    }

    return ERRO;
}
int Parser::arrayF(){
    if(cmpCateg(Category ::FeCol)){
        printRule("ArrayF = ']'");
        printAndNext();
        return OK;
    }else if(
            cmpCateg(Category ::OpNot) ||
            cmpCateg(Category ::OpMenos) ||
            cmpCateg(Category ::Id) ||
            cmpCateg(Category ::CteInt) ||
            cmpCateg(Category ::CteFloat) ||
            cmpCateg(Category ::CteBool) ||
            cmpCateg(Category ::CteStr) ||
            cmpCateg(Category ::AbCol)
            ){
        printRule("ArrayF = ExprBool ']'");
        if(exprBool() == ERRO) return ERRO;

        if(printAndNext(Category::FeCol)) return OK;
        else return ERRO;
    }

    printErr("']' ou Expressão");
    return ERRO;
}
int Parser::bloco(){
    if(cmpCateg(Category::AbChav)){
        printRule("Bloco = '{' ListaSentenças '}'");
        printAndNext();
        if (listaSentencas() == ERRO) return ERRO;

        if(printAndNext(Category::FeChav)) return OK;
        else return ERRO;
    }
    return ERRO;
}
int Parser::listaSentencas(){

    if(
            cmpCateg(Category::If)||
            cmpCateg(Category::While) ||
            cmpCateg(Category::For) ||
            cmpCateg(Category::Break) ||
            cmpCateg(Category::Return) ||
            cmpCateg(Category::Input) ||
            cmpCateg(Category::Print) ||
            cmpCateg(Category::Id) ||
            cmpCateg(Category::Integer) ||
            cmpCateg(Category::Float) ||
            cmpCateg(Category::Char) ||
            cmpCateg(Category::String) ||
            cmpCateg(Category::Boolean)
            ){
        printRule("ListaSentenças = Sentença ListaSentenças");
        if(sentenca() == ERRO) return ERRO;
        return listaSentencas();
    }

    printRule("ListaSentenças = EPSILON");
    return OK;
}
int Parser::sentenca(){

    if(cmpCateg(Category::If)){
        printRule("Sentença = If");
        return fIf();
    } else if(cmpCateg(Category::While)){
        printRule("Sentença = While");
        return fWhile();
    } else if(cmpCateg(Category::For)){
        printRule("Sentença = For");
        return fFor();
    } else if(cmpCateg(Category::Break)){
        printRule("Sentença = Desvio");
        return desvio();
    }else if(cmpCateg(Category::Return)){
        printRule("Sentença = Return");
        return fReturn();
    }else if(cmpCateg(Category::Input)){
        printRule("Sentença = Entrada");
        return entrada();
    }else if(cmpCateg(Category::Print)){
        printRule("Sentença = Saída");
        return saida();
    }else if(cmpCateg(Category::Id)){
        printRule("Sentença = Id ';'");
        if(id() == ERRO) return ERRO;
        if(printAndNext(Category::PtVg)) return OK;
        else return ERRO;
    }else if(cmpCateg(Category::Integer) ||
             cmpCateg(Category::Float) ||
             cmpCateg(Category::Char) ||
             cmpCateg(Category::String) ||
             cmpCateg(Category::Boolean) ||
             cmpCateg(Category::Const)){
        printRule("Sentença = ListaVar");
        return listaVar();
    }
    return ERRO;
}
int Parser::entrada(){
    printRule("Entrada = 'input' Argumentos ';'");

    if(cmpCateg(Category::Input)){
        printAndNext();
        if(argumentos() == ERRO) return ERRO;

        if(printAndNext(Category::PtVg)) return OK;
        else return ERRO;
    }
    return ERRO;
}
int Parser::saida(){
    if(cmpCateg(Category::Print)){
        printRule("Saída = 'print' CteStr Argumentos ';'");
        printAndNext();
        if(!printAndNext(Category::CteStr)) return ERRO;

        if(argumentos() == ERRO) return ERRO;

        if(printAndNext(Category::PtVg)) return OK;
        else return ERRO;
    }
    return ERRO;
}
int Parser::fIf(){
    if(cmpCateg(Category::If)){
        printRule("If    = 'if' '(' ExprBool ')' Bloco ElseIf Else");
        printAndNext();
        if(!printAndNext(Category::AbPar)) return ERRO;
        if(exprBool() == ERRO) return ERRO;
        if(!printAndNext(Category::FePar)) return ERRO;
        if(bloco() == ERRO) return ERRO;
        if(fElseIf() == ERRO) return ERRO;
        return fElse();
    }
    return ERRO;
}
int Parser::fElseIf(){
    if(cmpCateg(Category::ElseIf)){
        printRule("ElseIf = 'else if' '(' ExprBool ')' Bloco ElseIf");
        printAndNext();
        if(!printAndNext(Category::AbPar)) return ERRO;
        if(exprBool() == ERRO) return ERRO;
        if(!printAndNext(Category::FePar)) return ERRO;
        if(bloco() == ERRO) return ERRO;
        return fElseIf();
    }
    printRule("ElseIf = EPSILON");
    return OK;
}
int Parser::fElse(){
    if(cmpCateg(Category::Else)){
        printRule("Else = 'else' Bloco");
        printAndNext();
        return bloco();
    }
    printRule("Else = EPSILON");
    return OK;
}
int Parser::fWhile(){
    if(cmpCateg(Category::While)){
        printRule("While = 'while' '(' ExprBool ')' Bloco");
        printAndNext();
        if(!printAndNext(Category::AbPar)) return ERRO;
        if(exprBool() == ERRO) return ERRO;
        if(!printAndNext(Category::FePar)) return ERRO;
        return bloco();
    }

    return ERRO;
}
int Parser::fFor(){

    if(cmpCateg(Category::For)){
        printRule("For = 'for' Id 'in' '(' ExprBool ',' ExprBool ')' 'step' ExprBool Bloco");
        printAndNext();

        if(id() == ERRO) return ERRO;
        if(!printAndNext(Category::In)) return ERRO;
        if(!printAndNext(Category::AbPar)) return ERRO;
        if(exprBool() == ERRO) return ERRO;
        if(!printAndNext(Category::Vg)) return ERRO;
        if(exprBool() == ERRO) return ERRO;
        if(!printAndNext(Category::FePar)) return ERRO;
        if(!printAndNext(Category::Step)) return ERRO;
        if(exprBool() == ERRO) return ERRO;
        return bloco();
    }

    return ERRO;
}
int Parser::desvio(){
    if(cmpCateg(Category::Break)){
        printRule("Desvio = 'break' ';'");
        printAndNext();
        if(!printAndNext(Category::PtVg)) return ERRO;
        else return OK;
    }
    return ERRO;
}
int Parser::fReturn(){
    if(cmpCateg(Category::Return)){
        printRule("Return = 'return' ExprBool ';'");
        printAndNext();
        if(exprBool() == ERRO) return ERRO;

        if(printAndNext(Category::PtVg)) return OK;
        else return ERRO;
    }
    return ERRO;
}
int Parser::atribuicao(){
    printRule("Atribuição = OpAtribuição ExprBool");

    if(!printAndNext(Category::OpAtr)){return ERRO;}

    return exprBool();
}
int Parser::parametros(){
    if(
            cmpCateg(Category::Integer) ||
            cmpCateg(Category::Float) ||
            cmpCateg(Category::Char) ||
            cmpCateg(Category::String) ||
            cmpCateg(Category::Boolean)
            ){
        printRule("Parâmetros = ListaParam");
        return listaParam();
    }

    printRule("Parâmetros = EPSILON");
    return OK;
}
int Parser::listaParam(){
    printRule("ListaParam  = Tipo Id ListaParamR");

    if(tipo() == ERRO) return ERRO;
    if(id() == ERRO) return ERRO;

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
    if(cmpCateg(Category::Integer)){
        printRule("Tipo = 'int'");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::Float)){
        printRule("Tipo = 'float'");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::Char)){
        printRule("Tipo = 'char'");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::Boolean)){
        printRule("Tipo = 'bool'");
        printAndNext();
        return OK;
    }else if(cmpCateg(Category::String)){
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
        printAndNext();
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
    }else return ERRO;
}
int Parser::fatorAritmF(){
    if(cmpCateg(Category::Integer) ||
       cmpCateg(Category::Float) ||
       cmpCateg(Category::Char) ||
       cmpCateg(Category::String) ||
       cmpCateg(Category::Boolean)){
        printRule("FatorAtirmF = Tipo ')' ExprBool");
        if(tipo() ==ERRO)return ERRO;

        if(!printAndNext(Category::FePar)) return ERRO;

        return exprBool();
    }else if(cmpCateg(Category ::OpNot) ||
             cmpCateg(Category ::OpMenos) ||
             cmpCateg(Category ::Id) ||
             cmpCateg(Category ::CteInt) ||
             cmpCateg(Category ::CteFloat) ||
             cmpCateg(Category ::CteBool) ||
             cmpCateg(Category ::CteStr) ||
             cmpCateg(Category ::AbCol)){
        printRule("FatorAtirmF = ExprBool ')'");
        if(exprBool() == ERRO) return ERRO;

        if(printAndNext(Category::FePar)) return OK;
        else return ERRO;
    }
    printErr("Tipo ou Expressão");
    return ERRO;
}
int Parser::listaArray(){
    printRule("ListaArray = ExprBool ListaArrayR");

    if(exprBool() == ERRO) return ERRO;

    return listaArrayR();
}
int Parser::listaArrayR(){
    if(cmpCateg(Category::Vg)){
        printRule("ListaArrayR = ‘,’ ExprBool ListaArrayR");
        printAndNext();

        if(exprBool() == ERRO) return ERRO;

        return listaArrayR();
    }

    printRule("ListaArrayR = EPSILON");
    return OK;
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
    printErr(categ_name(c));
    return false;
}

void Parser::printErr(const string &s){
    cout << "\tErro: '" << tk.lex << "' na posição (" << tk.line << ", " << tk.col << ")" << endl
         << "\tEsperado " << s << "\n";
}

bool Parser::cmpCateg(Category c){
    return tk.categ == c;
}

void Parser::printAndNext(){
    printToken();
    nextToken();
}

void Parser::printRule(const string& r){
    cout << "          " << r << endl;
}
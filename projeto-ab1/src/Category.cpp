#include "Category.hpp"

char* categ_name(Category anEnum){
    switch (anEnum){
        case Category::PtVg:return (char*)"PtVg";
        case Category::Pt2:return (char*)"Pt2";
        case Category::Vg:return (char*)"Vg";
        case Category::Integer:return (char*)"Integer";
        case Category::Float:return (char*)"Float";
        case Category::Char:return (char*)"Char";
        case Category::String:return (char*)"String";
        case Category::Boolean:return (char*)"Boolean";
        case Category::Procedure:return (char*)"Procedure";
        case Category::Func:return (char*)"Func";
        case Category::Return:return (char*)"Return";
        case Category::Break:return (char*)"Break";
        case Category::AbPar:return (char*)"AbPar";
        case Category::FePar:return (char*)"FePar";
        case Category::AbCol:return (char*)"AbCol";
        case Category::FeCol:return (char*)"FeCol";
        case Category::AbChav:return (char*)"AbChav";
        case Category::FeChav:return (char*)"FeChav";
        case Category::Input:return (char*)"Input";
        case Category::Print:return (char*)"Print";
        case Category::For:return (char*)"For";
        case Category::In:return (char*)"In";
        case Category::Step:return (char*)"Step";
        case Category::While:return (char*)"While";
        case Category::If:return (char*)"If";
        case Category::ElseIf:return (char*)"ElseIf";
        case Category::Else:return (char*)"Else";
        case Category::OpEq:return (char*)"OpEq";
        case Category::OpMaior:return (char*)"OpMaior";
        case Category::OpMenor:return (char*)"OpMenor";
        case Category::OpMaiorEq:return (char*)"OpMaiorEq";
        case Category::OpMenorEq:return (char*)"OpMenorEq";
        case Category::OpDifer:return (char*)"OpDifer";
        case Category::OpAnd:return (char*)"OpAnd";
        case Category::OpOr:return (char*)"OpOr";
        case Category::OpNot:return (char*)"OpNot";
        case Category::OpMais:return (char*)"OpMais";
        case Category::OpMenos:return (char*)"OpMenos";
        case Category::OpMult:return (char*)"OpMult";
        case Category::OpDiv:return (char*)"OpDiv";
        case Category::OpMod:return (char*)"OpMod";
        case Category::OpAtr:return (char*)"OpAtr";
        case Category::OpConcat:return (char*)"OpConcat";
        case Category::Id:return (char*)"Id";
        case Category::Const:return (char*)"Const";
        case Category::CteInt:return (char*)"CteInt";
        case Category::CteFloat:return (char*)"CteFloat";
        case Category::CteChar:return (char*)"CteChar";
        case Category::CteBool:return (char*)"CteBool";
        case Category::CteStr:return (char*)"CteStr";
        case Category::Eof:return (char*)"Eof";
        default:return (char*)"ERRO NA ANALIZE";
    }
}

char* categ_lex(Category anEnum){
    switch (anEnum){
        case Category::PtVg:return (char*)";";
        case Category::Pt2:return (char*)":";
        case Category::Vg:return (char*)",";
        case Category::Integer:return (char*)"int";
        case Category::Float:return (char*)"float";
        case Category::Char:return (char*)"char";
        case Category::String:return (char*)"string";
        case Category::Boolean:return (char*)"bool";
        case Category::Procedure:return (char*)"proc";
        case Category::Func:return (char*)"func";
        case Category::Return:return (char*)"return";
        case Category::Break:return (char*)"break";
        case Category::AbPar:return (char*)"(";
        case Category::FePar:return (char*)")";
        case Category::AbCol:return (char*)"[";
        case Category::FeCol:return (char*)"]";
        case Category::AbChav:return (char*)"{";
        case Category::FeChav:return (char*)"}";
        case Category::Input:return (char*)"input";
        case Category::Print:return (char*)"print";
        case Category::For:return (char*)"for";
        case Category::In:return (char*)"in";
        case Category::Step:return (char*)"step";
        case Category::While:return (char*)"while";
        case Category::If:return (char*)"if";
        case Category::ElseIf:return (char*)"else if";
        case Category::Else:return (char*)"else";
        case Category::OpEq:return (char*)"==";
        case Category::OpMaior:return (char*)">";
        case Category::OpMenor:return (char*)"<";
        case Category::OpMaiorEq:return (char*)">=";
        case Category::OpMenorEq:return (char*)"<=";
        case Category::OpDifer:return (char*)"!=";
        case Category::OpAnd:return (char*)"and";
        case Category::OpOr:return (char*)"or";
        case Category::OpNot:return (char*)"not";
        case Category::OpMais:return (char*)"+";
        case Category::OpMenos:return (char*)"-";
        case Category::OpMult:return (char*)"*";
        case Category::OpDiv:return (char*)"/";
        case Category::OpMod:return (char*)"%";
        case Category::OpAtr:return (char*)"=";
        case Category::OpConcat:return (char*)"++";
        case Category::Id:return (char*)"identifier";
        case Category::Const:return (char*)"const";
        case Category::CteInt:return (char*)"CteInt";
        case Category::CteFloat:return (char*)"CteFloat";
        case Category::CteChar:return (char*)"CteChar";
        case Category::CteBool:return (char*)"CteBool";
        case Category::CteStr:return (char*)"CteStr";
        case Category::Eof:return (char*)"EOF";
        default:return (char*)"ERRO NA ANALIZE";
    }
}
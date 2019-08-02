#include "Category.hpp"

char* categ_name(Category anEnum){
    switch (anEnum){
        case Category::Init:return (char*)"Init";
        case Category::PtVg:return (char*)"PtVg";
        case Category::Pt2:return (char*)"Pt2";
        case Category::Vg:return (char*)"Vg";
        case Category::Integer:return (char*)"Integer";
        case Category::Float:return (char*)"Float";
        case Category::Char:return (char*)"Char";
        case Category::String:return (char*)"String";
        case Category::Boolean:return (char*)"Boolean";
        case Category::Procedure:return (char*)"Procedure";
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
        case Category::OpMais:return (char*)"OpMais";
        case Category::OpMenos:return (char*)"OpMenos";
        case Category::OpMult:return (char*)"OpMult";
        case Category::OpDiv:return (char*)"OpDiv";
        case Category::OpMod:return (char*)"OpMod";
        case Category::OpAtr:return (char*)"OpAtr";
        case Category::OpConcat:return (char*)"OpConcat";
        case Category::Id:return (char*)"Id";
        case Category::CteInt:return (char*)"CteInt";
        case Category::CteFloat:return (char*)"CteFloat";
        case Category::CteChar:return (char*)"CteChar";
        case Category::CteBool:return (char*)"CteBool";
        case Category::CteStr:return (char*)"CteStr";
        case Category::Eof:return (char*)"Eof";
        default:return (char*)"********ERRO********";
    }
}
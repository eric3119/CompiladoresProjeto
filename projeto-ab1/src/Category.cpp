#include "Category.hpp"

char* categ_name(Category anEnum){
    switch (anEnum){
        case Category::Init:return (char*)"init";
        case Category::Pt:return (char*)"Pt";
        case Category::Begin:return (char*)"Begin";
        case Category::End:return (char*)"End";
        case Category::Var:return (char*)"Var";
        case Category::PtVg:return (char*)"PtVg";
        case Category::Pt2:return (char*)"Pt2";
        case Category::Vg:return (char*)"Vg";
        case Category::Integer:return (char*)"Integer";
        case Category::Float:return (char*)"Float";//TODO update float
        case Category::Procedure:return (char*)"Procedure";
        case Category::Function:return (char*)"Function";
        case Category::AbPar:return (char*)"AbPar";
        case Category::FePar:return (char*)"FePar";
        case Category::Read:return (char*)"Read";
        case Category::Write:return (char*)"Write";
        case Category::For:return (char*)"For";
        case Category::To:return (char*)"To";
        case Category::Do:return (char*)"Do";
        case Category::Repeat:return (char*)"Repeat";
        case Category::Until:return (char*)"Until";
        case Category::If:return (char*)"If";
        case Category::Then:return (char*)"Then";
        case Category::Else:return (char*)"Else";
        case Category::Eq:return (char*)"Eq";
        case Category::Maior:return (char*)"Maior";
        case Category::Menor:return (char*)"Menor";
        case Category::MaiorEq:return (char*)"MaiorEq";
        case Category::MenorEq:return (char*)"MenorEq";
        case Category::Difer:return (char*)"Difer";
        case Category::Mais:return (char*)"Mais";
        case Category::Menos:return (char*)"Menos";
        case Category::Mult:return (char*)"Mult";
        case Category::Div:return (char*)"Div";
        case Category::Id:return (char*)"Id";
        case Category::CteI:return (char*)"CteI";
        case Category::CteR:return (char*)"CteR";//TODO update float
        case Category::Eof:return (char*)"Eof";
        default:return (char*)"erro";
    }
}
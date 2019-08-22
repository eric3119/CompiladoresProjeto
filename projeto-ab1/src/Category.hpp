#ifndef PROJETO_AB1_CATEGORY_HPP
#define PROJETO_AB1_CATEGORY_HPP

enum class Category {
    Init=1, Integer, Float, Char, String, Boolean,
    PtVg, Pt2, Vg, AbPar, FePar, AbCol, FeCol, AbChav, FeChav,
    Procedure, Return, Break,
    Input, Print,
    For, In, Step, While, If, ElseIf, Else,
    OpEq, OpMaior, OpMenor, OpMaiorEq, OpMenorEq, OpDifer, OpAnd, OpOr, OpNot,
    OpMais, OpMenos, OpMult, OpDiv, OpMod,
    OpAtr, OpConcat,
    Id, CteInt, CteFloat, CteChar, CteBool, CteStr, Eof
};

char* categ_name(Category);

#endif //PROJETO_AB1_CATEGORY_HPP
#ifndef PROJETO_AB1_CATEGORY_HPP
#define PROJETO_AB1_CATEGORY_HPP

const int MAX_CAT_LEN = 10;

enum class Category {
    Init=1, Integer, Float, Char, Boolean,
    PtVg, Pt2, Vg, AbPar, FePar, AbCol, FeCol, AbChav, FeChav,
    Procedure, Return, Break,
    Read, Write,
    For, While, If, ElseIf, Else,
    OpEq, OpMaior, OpMenor, OpMaiorEq, OpMenorEq, OpDifer,
    OpMais, OpMenos, OpMult, OpDiv, OpMod,
    OpAtr,
    Id, CteInt, CteFloat, CteChar, CteBool, CteStr, Eof
};

char* categ_name(Category anEnum);

#endif //PROJETO_AB1_CATEGORY_HPP
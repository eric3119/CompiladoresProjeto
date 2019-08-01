#ifndef PROJETO_AB1_CATEGORY_HPP
#define PROJETO_AB1_CATEGORY_HPP

enum class Category { Init=1, Var, PtVg,
    Pt2, Vg, Integer, Float, Char, Boolean, Procedure,
    AbPar, FePar, Read, Write, For, To, Do, Repeat, Until,
    If, Then, Else, Eq, Maior, Menor, MaiorEq, MenorEq, Difer,
    Mais, Menos, Mult, Div, Id, CteI, CteR,
    Eof
};

char* categ_name(Category anEnum);

#endif //PROJETO_AB1_CATEGORY_HPP

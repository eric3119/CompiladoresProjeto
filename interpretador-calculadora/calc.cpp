#include <iostream>
#include <cmath>
#include "src/Tokenizer.cpp"

using namespace std;

Token tk;
Tokenizer *tokenizer;
void fRes();
double fEa();
double fEar(double);
double fTa();
double fTar(double);
double fFa();

void fRes(){
    double Eaval;
    tk = tokenizer->nextToken();
    Eaval = fEa();
    if(tk.categ == Category::OpResult) cout << Eaval;
    else cout << "'=' esperado" << endl;
}

double fEa(){
//    double Taval,Earvh, Earvs,Eaval;
//    Taval = fTa();
//    Earvh = Taval;
//    Earvs = fEar(Earvh);
//    Eaval = Earvs;
//    return Eaval;

    return fEar(fTa());
}

double fEar(double Earvh){
//    double Taval, Ear1vh, Earvs, Ear1vs;
//    if(tk.categ == Category::OpMais){
//        tk = tokenizer->nextToken();
//        Taval = fTa();
//        Ear1vh = Earvh + Taval;
//        Ear1vs = fEar(Ear1vh);
//        Earvs = Ear1vs;
//    }else if(tk.categ == Category::OpMenos){
//        tk = tokenizer->nextToken();
//        Taval = fTa();
//        Ear1vh = Earvh - Taval;
//        Ear1vs = fEar(Ear1vh);
//        Earvs = Ear1vs;
//    } else Earvs = Earvh;
//
//    return Earvs;

    if(tk.categ == Category::OpMais){
        tk = tokenizer->nextToken();
        return fEar(Earvh + fTa());
    }else
        return Earvh;
}

double fTa(){
    double Faval, Tarvh, Tarvs, Taval;
    Faval = fFa();
    Tarvh = Faval;
    Tarvs = fTar(Tarvh);
    Taval = Tarvs;
    return Taval;
}

double fTar(double Tarvh){

    double Faval, Tar1vh, Tar1vs, Tarvs;
    if (tk.categ == Category::OpMult){
        tk = tokenizer->nextToken();

        Faval = fFa();
        Tar1vh = Tarvh * Faval;
        Tar1vs = fTar(Tar1vh);
        Tarvs = Tar1vs;

        return Tarvs;

    }else if(tk.categ == Category::OpDiv){
        tk = tokenizer->nextToken();

        Faval = fFa();
        Tar1vh = Tarvh / Faval;
        Tar1vs = fTar(Tar1vh);
        Tarvs = Tar1vs;

    }else if(tk.categ == Category::OpPot){
        tk = tokenizer->nextToken();

        Faval = fFa();
        Tar1vh = pow(Tarvh, Faval);
        Tar1vs = fTar(Tar1vh);
        Tarvs = Tar1vs;

    }else Tarvs = Tarvh;

    return Tarvs;
}

double fFa(){
    double Faval;
    if(tk.categ == Category::AbPar){
        tk = tokenizer->nextToken();
        Faval = fEa();
        if (tk.categ != Category::FePar){
            cout << "')' esperado\n";
            exit(0);
        }else{
            tk = tokenizer->nextToken();
            return Faval;
        }
    }else if(tk.categ == Category::CteFloat){
        Faval = stof(tk.lex);
        tk = tokenizer->nextToken();
        return Faval;
    }else{
        cout << "'(' ou 'CteF' esperados\n";
        exit(0);
    }
}

int main(int argc, const char* argv[]) {

    if(argc != 2){
        cout << "use: calc expr=\n";
        exit(0);
    }

    tokenizer = new Tokenizer(argv[1]);

    fRes();

    return 0;
}
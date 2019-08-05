#include <iostream>
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
double fFar();

void fRes(){
    double Eaval;
    tk = tokenizer->nextToken();
    Eaval = fEa();
    if(tk.categ == Category::OpResult) cout << Eaval;
    else cout << "'=' esperado" << endl;
}

double fEa(){
    double Taval,Earvh, Earvs,Eaval;
    Taval = fTa();
    Earvh = Taval;
    Earvs = fEar(Earvh);
    Eaval = Earvs;
    return Eaval;

    //return fEar(fTa);
}

double fEar(double Earvh){
    double Taval, Ear1vh, Earvs, Ear1vs;
    if(tk.categ == Category::OpMais){
        tk = tokenizer->nextToken();
        Taval = fTa();
        Ear1vh = Earvh + Taval;
        Ear1vs = fEar(Ear1vh);
        Earvs = Ear1vs;
    }else if(tk.categ == Category::OpMenos){
        tk = tokenizer->nextToken();
        Taval = fTa();
        Ear1vh = Earvh - Taval;
        Ear1vs = fEar(Ear1vh);
        Earvs = Ear1vs;
    } else Earvs = Earvh;

    return Earvs;

    // if(tk.categ == Category::OpMais){tk.next();return fEar(Earvh + fTa());else return Earvh;
}

double fTa(){
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

//double fTar(double Tarvh){
//    if (tk.categ == Category::OpMult){
//
//    }else if(tk.categ == Category::OpDiv){
//
//    }else if(tk.categ == Category::OpMod){//TODO '**'
//
//    }
//    return Tarvh;
//}

int main(int argc, const char* argv[]) {

    if(argc != 2){
        cout << "use: calc expr=\n";
        exit(0);
    }

    tokenizer = new Tokenizer(argv[1]);

    fRes();

    return 0;
}
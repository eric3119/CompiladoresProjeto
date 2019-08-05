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
    return fEar(fTa());
}

double fEar(double Earvh){
    if(tk.categ == Category::OpMais){
        tk = tokenizer->nextToken();
        return fEar(Earvh + fTa());
    }else
        return Earvh;
}

double fTa(){
    return fTar(fFa());
}

double fTar(double Tarvh){

    if (tk.categ == Category::OpMult){

        tk = tokenizer->nextToken();
        return fTar(Tarvh * fFa());

    }else if(tk.categ == Category::OpDiv){

        tk = tokenizer->nextToken();
        return fTar(Tarvh / fFa());

    }else if(tk.categ == Category::OpPot){
        tk = tokenizer->nextToken();
        return fTar(pow(Tarvh, fFa()));

    }else return Tarvh;
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
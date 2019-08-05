#include <iostream>
#include "../projeto-ab1/src/Tokenizer.h"

using namespace std;

Token tk;
void fRes();
double fEa();
double fEar(double);
double fTa();
double fTar();
double fFa();
double fFar();

void fRes(){
    double Eaval;
    Eaval = fEa();
    if(tk.categ == Category::OpAtr) cout << Eaval;
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
        //Tokenizer::nextToken();
        Taval = fTa();
        Ear1vh = Earvh + Taval;
        Ear1vs = fEar(Ear1vh);
        Earvs = Ear1vs;
    }else Earvs = Earvh;

    return Earvs;

    // if(tk.categ == Category::OpMais){tk.next();return fEar(Earvh + fTa());else return Earvh;
}

int main(int argc, const char* argv[]) {

    if(argc != 2){
        cout << "use: calc expr=\n";
        exit(0);
    }

    return 0;
}
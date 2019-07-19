class Token {
private:
    void verif_token(){
        while (strcmp(lexema, "\n") == 0){
            linha++;
            get_next_token();
        }

        if(feof(file)){
            categ = Eof;
            memset(lexema, 0, MAX_STRING);
            return;
        }
        if (strcmp(lexema, "se") == 0){
            categ = Se;
        }else if (strcmp(lexema, "então") == 0){
            categ = Entao;
        }else if (strcmp(lexema, "fim") == 0){
            categ = Fim;
        }else if (strcmp(lexema, ".") == 0){
            categ = Pt;
        }else if (strcmp(lexema, ";") == 0){
            categ = PtVg;
        }else if (strcmp(lexema, "para") == 0){
            categ = Para;
        }else if (strcmp(lexema, "até") == 0){
            categ = Ate;
        }else if (strcmp(lexema, "repita") == 0){
            categ = Repita;
        }else if (strcmp(lexema, "=") == 0){
            categ = Atr;
        }else if (strcmp(lexema, "opl") == 0){
            categ = Opl;
        }else if (strcmp(lexema, "opm") == 0){
            categ = Opm;
        }else if (strcmp(lexema, "opa") == 0){
            categ = Opa;
        }else if (strcmp(lexema, "(") == 0){
            categ = AbPar;
        }else if (strcmp(lexema, ")") == 0){
            categ = FePar;
        }else if (strcmp(lexema, "não") == 0){
            categ = Nao;
        }else if (strcmp(lexema, "verd") == 0){
            categ = Verd;
        }else if (strcmp(lexema, "falso") == 0){
            categ = Falso;
        }
    }

    void get_next_token(){
        fscanf(file, "%s", this->lexema);
    }

public:
    Category categ;
    char lexema[MAX_STRING];
    int linha=1, coluna=1;

    void next(){
        get_next_token();
        verif_token();
    }

    Token(){
        strcpy(this->lexema, "");
        get_next_token();
        verif_token();
    }
};
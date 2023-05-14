#include <bits/stdc++.h>
#include "no.h"

using namespace std;

typedef struct{
    Item item;
    string palavra;
}Palavras;

class VO{
    protected:
        int max; // quantidade máxima de palavras que podem ser guardadas no vetor
        int qntPalavras; // guarda a quantidade de palavras no vetor
        Palavras *palavras; // bloco com as palavras + suas informações
    public:
        VO();
        ~VO();
        void resize();
        int getQntPalavras();
        void insere(string key, Item val);
        Item busca(string key);
};

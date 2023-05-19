#include <iostream>
#include <string>
#include "no.h"

using namespace std;

struct Palavras{
    Item item;
    string palavra;
};

class VO{
    protected:
        int max; // quantidade máxima de palavras que podem ser guardadas no vetor
        int qntPalavras; // guarda a quantidade de palavras no vetor
        string *palavras;
        Item *itens;
    public:
        VO();
        ~VO();
        void resize();
        int getQntPalavras();
        void insere(string key, Item val);
        Item busca(string key);
        void inorder();
        void add(string key, Item val);
        void imprime();
        void ajudaPalavrasFrequentes(pFrequentesVetor* pf);
};


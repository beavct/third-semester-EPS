#include <bits/stdc++.h>
#include "no.h"

using namespace std;

typedef struct No{
    Item item;
    string palavra;
    int cor; 
    // 1: preto
    // 0: vermelho
    No* esq;
    No* dir;
};

class ARN{
    protected:
        int tam;
        No* raiz;
    public:
        ARN();
        ~ARN();
        No* getRaiz();
        void daFree(No* raiz);
        void setRaiz(No* raiz);
        No* rodaEsq(No* raiz);
        No* rodaDir(No* raiz);
        No* insereARN(No* raiz, string key, Item item);
        No* buscaARN(No *raiz, string key);
        void inorder(No* raiz);
};
#include <bits/stdc++.h>
#include "no.h"

using namespace std;

typedef struct No{
    Item item;
    string palavra;
    int prioridade;
    No* esq;
    No* dir;
};

class TR{
    protected:
        int tam;
        No* raiz;

    public:
        TR();
        ~TR();
        No* getRaiz();
        void daFree(No* raiz);
        void setRaiz(No* raiz);
        No* rodaEsq(No* raiz);
        No* rodaDir(No* raiz);
        No* insereTR(No* raiz, string key, Item item);
        No* buscaTR(No *raiz, string key);
        void inorder(No* raiz);
};